//*****************************************************************************
//render/shader/Shader.cpp*****************************************************
//*****************************************************************************

//Header Include
#include "Shader.h"

//Standard Library Includes
#include <sstream>
#include <fstream>

//Namespaces
using namespace render;

//Explicit Template Instantiation
template class render::ShaderT<vertex>;
template class render::ShaderT<fragment>;
template class render::ShaderT<geometry>;
template class render::ShaderT<tessEval>;
template class render::ShaderT<tessCtrl>;


//*****************************************************************************
//Initialize*******************************************************************
//*****************************************************************************
void Shader::init(const string &source)
{
	this->source = source;

	this->parse();
	this->compile();
	this->log(); 
}
//-----------------------------------------------------------------------------
//Initialize for recompiled shaders--------------------------------------------
//-----------------------------------------------------------------------------
void Shader::reinit()
{
	//re-Initialize (from stored source), basically the same but don't re-include
	//#includes

	this->parseDefines();
	this->compile();
	this->log();	
}
//*****************************************************************************
//Compile**********************************************************************
//*****************************************************************************
void Shader::compile()
{
	size_t len = source.length();

	//Load source code into shaders
	const char *source_array = source.c_str();
	glShaderSource(shader_id, 1, (const char **)&source_array, (GLint *)(&len));
	
	//Compile Shader
	glCompileShader(shader_id);
	
	//Check to see if it compiled
	GLint compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
		cerr << "ERROR: The shader \"" << file << "\" could not be compiled" << endl;
		return;
	}
}
//*****************************************************************************
//Parse************************************************************************
//*****************************************************************************
void Shader::parse()
{
	this->parseIncludes(this->source);
	this->parseDefines();
	this->parseUniforms();
}
//-----------------------------------------------------------------------------
//Parse Include Files----------------------------------------------------------
//-----------------------------------------------------------------------------
void Shader::parseIncludes(string &shaderSource)
{
	includeVec.clear();
	istringstream sourceStream(shaderSource);
	string line;
	int lineNum = 1, endOfLine, begOfLine;
	while(getline(sourceStream, line))
	{
		endOfLine = (int)sourceStream.tellg();				//get current stream position
		begOfLine = endOfLine - (int)line.size();
		sourceStream.seekg(-(int)line.size(),ios::cur);		//move it back so we don't need a separate line stream

		if(line.find("#include") == 0)
		{
			Shader::Include include;
			
			//              #include        filename
			sourceStream >> include.file >> include.file;

			include.lineNum = lineNum;
			include.file    = include.file.substr(1, include.file.length()-2);	//remove leading and trailing "
			include.source  = loadIncludeSource(path+include.file, include.numLines);

			if( !(include.source.size() > 0))
			{
				cerr << "ERROR: unable to open shader include \"" << path << include.file << "\"" << endl;
				return;
			}

			parseInclude(include);

			//Replace #include line with the included source
			shaderSource.replace(endOfLine-line.length()-1, line.length(), include.source);
			sourceStream.str(shaderSource);

			sourceStream.seekg(begOfLine + include.source.size());

			includeVec.push_back(include);

			lineNum += include.numLines+1;
		}
		else
		{
			sourceStream.seekg(endOfLine);				//move stream position back forward
			lineNum++;
		}
	}
}
//-----------------------------------------------------------------------------
void Shader::parseInclude( Include &parentInclude )
{
	istringstream parentSourceStream(parentInclude.source);
	string line;
	int lineNum = parentInclude.lineNum;
	while(getline(parentSourceStream, line))
	{
		int endOfLine = (int)parentSourceStream.tellg();			//get current stream position
		int begOfLine = endOfLine - (int)line.size();
		parentSourceStream.seekg(-(int)line.size(),ios::cur);		//move it back so we don't need a separate line stream

		if(line.find("#include") == 0)
		{
			Shader::Include childInclude;

			//                    #include             filename
			parentSourceStream >> childInclude.file >> childInclude.file;

			childInclude.lineNum = lineNum;
			childInclude.file    = childInclude.file.substr(1, childInclude.file.length()-2);	//remove leading and trailing "
			childInclude.source  = loadIncludeSource(path+childInclude.file, childInclude.numLines);

			if( !(childInclude.source.size() > 0))
			{
				cerr << "ERROR: unable to open shader include \"" << path << childInclude.file << "\"" << endl;
				return;
			}

			parseInclude(childInclude);

			//Replace #include line with the included source
			parentInclude.source.replace(endOfLine-line.length()-1, line.length(), childInclude.source);
			parentSourceStream.str(parentInclude.source);

			parentSourceStream.seekg(begOfLine + childInclude.source.size());

			parentInclude.includeVec.push_back(childInclude);
			parentInclude.numLines += childInclude.numLines;
			lineNum                += childInclude.numLines+1;
		}
		else
		{
			parentSourceStream.seekg(endOfLine);				//move stream position back forward
			lineNum++;
		}
	}
}
//-----------------------------------------------------------------------------
//Parse Defines----------------------------------------------------------------
//-----------------------------------------------------------------------------
void Shader::parseDefines()
{
	istringstream sourceStream(source);
	istringstream lineStream;
	string line;
	int lineNum = 0;//, endOfLine;
	while(getline(sourceStream, line))
	{
		if(line.find("#define") == 0)
		{
			lineStream.clear();
			lineStream.str(line);

			Shader::Define define;
			define.lineNum = lineNum;
			lineStream >> define.var >> define.var >> define.val;

			int lineSize   = (int)line.size();
			int linePos    = (int)lineStream.tellg();
			int sourcePos  = (int)sourceStream.tellg();
			int valSize    = (int)define.val.size();

			define.valPos = (linePos == -1) ? (sourcePos - valSize - 1) : (sourcePos - (lineSize - linePos) - valSize - 1);

			map<string, Define>::iterator defineItr = defineMap.find(define.var);
			if(defineItr != defineMap.end())		//found, use existing value
			{
				Define foundDef = defineItr->second;
				if(foundDef.val != define.val)
				{
					source.replace(define.valPos, define.val.length(), foundDef.val);
				}
				define.val = foundDef.val;
			}
			defineMap[define.var] = define;
		}

		lineNum++;
	}
}
//-----------------------------------------------------------------------------
//Parse Uniforms---------------------------------------------------------------
//-----------------------------------------------------------------------------
void Shader::parseUniforms()
{
	istringstream sourceStream(source);
	istringstream lineStream;
	string line;
	int lineNum = 0;//, endOfLine;
	while(getline(sourceStream, line))
	{
		size_t uniformPos = line.find("uniform");
		if(uniformPos != string::npos && !(line.find("#") == 0) && !(line.find("//") == 0))	//has uniform but is not in a comment or define/extension
		{																					//clearly many robustness issues with this approach, but
			lineStream.clear();																//serves for present purposes
			lineStream.str(line);

			lineStream.seekg(uniformPos + 7); // +7 for length of "uniform" string

			Uniform uniform;
			lineStream >> uniform.type >> uniform.name;

			size_t bindingPos = line.find("binding");
			if(bindingPos != string::npos)
			{
				lineStream.clear();
				lineStream.str(line);
				lineStream.seekg(bindingPos + 7); // +7 for length of "binding" string

				string equals;
				lineStream >> equals >> uniform.binding;
			}

			if(line.back() != ';')		//again this isn't super robust, but prevents us form having to deal with multi-line weirdness
				return;

			if(uniform.name.back() == ';')										//Removes the semicolon from the uniform's name
				uniform.name = uniform.name.substr(0, uniform.name.size()-1);		//Removes the semicolon from the uniform's name

			uniformSet.insert(uniform.name);
			uniformMap[uniform.name] = uniform;
		}

		lineNum++;
	}
}
//*****************************************************************************
//Log**************************************************************************
//*****************************************************************************
void Shader::log()
{
	GLint blen;
	GLsizei size;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH , &blen);
	if(blen > 1)
	{
		char *log = new char[blen];
		if(log == NULL)
		{
			cerr << "Could not allocate compiler log buffer" << endl;
		}
		glGetShaderInfoLog(shader_id, blen, &size, log);

		istringstream logStream(log);

		string line;
		while(getline(logStream, line))
		{
//			cerr << line << endl;

			int lineNum;
			int pos = (int)line.find_first_of("(") + 1;
			int len = (int)line.find_first_of(")") - pos;

			string lineNumStr = line.substr(pos, len);
			std::stringstream lineNumStrStream(lineNumStr);

			lineNumStrStream >> lineNum;

			string file;
			lineNum = getActualLineNum(lineNum, file);

			line = line.substr(pos+len+1, string::npos);
			cerr << file << "(" << lineNum << ")" << line << endl;
		}

//		cerr << log << endl;
		delete [] log;
	}
}
//*****************************************************************************
//Change a #define (and recompile)*********************************************
//*****************************************************************************
void Shader::setDefine( const string &var, const string &newVal )
{
	map<string, Define>::iterator itr = defineMap.find(var);

	if(itr != defineMap.end())
	{
		Shader::Define &define = itr->second;

		if(define.val != newVal)	//don't bother with update if the same
		{
			//     replace                   old val    with   new val
			source.replace(define.valPos, define.val.length(), newVal);

			//Update stored define
			define.val = newVal;

			this->refreshSource();
		}
	}
}
//*****************************************************************************
//Load Source from file********************************************************
//*****************************************************************************
string Shader::loadSource(const string &filename)
{
	int numLines;
	return loadSource(filename, numLines);
}
//-----------------------------------------------------------------------------
string Shader::loadSource(const string &filename, int &numLines)
{
	int lineNum = 1;
	string source;

	ifstream inStream(filename.c_str());
	if(inStream.is_open())
	{
		string line;
		while(getline(inStream, line, '\n'))
		{
			line   += "\n";
			source += line;
			lineNum++;

			if(line.find("#version") == 0)	//wait until after #version string to add in extra includes
			{
				for(size_t i = 0; i < additionalIncludes.size(); i++)
				{
					source += "#include \"" + additionalIncludes[i] + "\"\n";
					lineNum++;
				}
			}

		}
		inStream.close();
	}
	else
	{
		cerr << "Could not open file: \"" << filename << "\"" << endl;
	}
	numLines = lineNum-1;
	return source;
}
//-----------------------------------------------------------------------------
string Shader::loadIncludeSource(const string &filename, int &numLines)
{
	//same as above without additional includes
	int lineNum = 1;
	string source;

	ifstream inStream(filename.c_str());
	if(inStream.is_open())
	{
		string line;
		while(getline(inStream, line, '\n'))
		{
			line   += "\n";
			source += line;
			lineNum++;
		}
		inStream.close();
	}
	else
	{
		cerr << "Could not open file: \"" << filename << "\"" << endl;
	}
	numLines = lineNum-1;
	return source;
}
//*****************************************************************************
//Get Actual Line Number*******************************************************
//*****************************************************************************
int Shader::getActualLineNum( int origLine, string &file)
{
	vector<Include>::iterator itr = includeVec.begin();

	file = this->file;
	int lineNum = origLine;
	int offset = 0;
	while(itr != includeVec.end())
	{
		Include &include = *itr;
		if(lineNum < include.lineNum)
		{
			return lineNum;
		}
		else if(lineNum >= include.lineNum && lineNum < include.lineNum + include.numLines)
		{
			return getActualLineNum(origLine, file, include);
		}
		offset += include.numLines;

		itr++;
	}
	return lineNum - offset;
}
//-----------------------------------------------------------------------------
int Shader::getActualLineNum( int origLine, string &file, Include &parentInclude )
{
	vector<Include>::iterator itr = parentInclude.includeVec.begin();

	file = parentInclude.file;
	int lineNum = origLine+1;
	int offset = parentInclude.lineNum;
	while(itr != parentInclude.includeVec.end())
	{
		Include &childInclude = *itr;
		if(lineNum < childInclude.lineNum)
		{
			return lineNum;
		}
		else if(lineNum >= childInclude.lineNum && lineNum < childInclude.lineNum + childInclude.numLines)
		{
			return getActualLineNum(origLine, file, childInclude);
		}
		offset += childInclude.numLines;

		itr++;
	}
	return lineNum - offset;
}
