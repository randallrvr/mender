//*****************************************************************************
//render/shader/Shader.h*******************************************************
//*****************************************************************************

#pragma once

#include <unordered_set>
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include <render/gl.h>

using namespace std;

namespace render
{

template<typename T> struct traits;

#define OPENGL_SHADER_TYPE(a, b) template<> struct traits<a>{ enum{ type = b }; };

OPENGL_SHADER_TYPE(struct vertex,   GL_VERTEX_SHADER);
OPENGL_SHADER_TYPE(struct fragment, GL_FRAGMENT_SHADER);
OPENGL_SHADER_TYPE(struct geometry, GL_GEOMETRY_SHADER);
OPENGL_SHADER_TYPE(struct tessEval, GL_TESS_EVALUATION_SHADER);
OPENGL_SHADER_TYPE(struct tessCtrl, GL_TESS_CONTROL_SHADER);
OPENGL_SHADER_TYPE(struct compute,  GL_COMPUTE_SHADER);

struct ShaderFile
{
	string filename;
	vector<string> includes;

	ShaderFile() : filename("") { includes.clear(); }
	ShaderFile(const string &filename) : filename(filename) { includes.clear(); }

//	~ShaderFile() { includes.clear(); }

//	ShaderFile &include(const string &filename)
//	{
//		includes.push_back(filename);
//		return *this;
//	}

	ShaderFile include(const string &includeFile)
	{
		ShaderFile shaderFile(this->filename);
		shaderFile.includes.push_back(includeFile);
		return shaderFile;
	}
};


template<class T>
class ShaderFileT : public ShaderFile
{
public:

	ShaderFileT() : ShaderFile() { }
	ShaderFileT(const string &filename) : ShaderFile(filename) { }


//	T &include(const string &filename)
//	{
//		includes.push_back(filename);
//		return static_cast<T &>(*this);
//	}

	void includeGLSL(const string &includeFile)
	{
		includes.push_back(includeFile);
	}

	T include(const string &includeFile)
	{
		T tFile(this->filename);
		tFile.includes.push_back(includeFile);
		return tFile;
	}
};

struct VertFile : public ShaderFileT<VertFile> { VertFile(const string &filename) : ShaderFileT(filename) {}; VertFile() : ShaderFileT() {} };
struct FragFile : public ShaderFileT<FragFile> { FragFile(const string &filename) : ShaderFileT(filename) {}; FragFile() : ShaderFileT() {} };
struct GeomFile : public ShaderFileT<GeomFile> { GeomFile(const string &filename) : ShaderFileT(filename) {}; GeomFile() : ShaderFileT() {} };
struct EvalFile : public ShaderFileT<EvalFile> { EvalFile(const string &filename) : ShaderFileT(filename) {}; EvalFile() : ShaderFileT() {} };
struct CtrlFile : public ShaderFileT<CtrlFile> { CtrlFile(const string &filename) : ShaderFileT(filename) {}; CtrlFile() : ShaderFileT() {} };
struct CompFile : public ShaderFileT<CompFile> { CompFile(const string &filename) : ShaderFileT(filename) {}; CompFile() : ShaderFileT() {} };


//Types for differentiating string source (from file or direct source code)
//struct Filename : public string { Filename(const string &filename) : string(filename) {} };
struct Source   : public string { Source  (const string &source  ) : string(source  ) {} };

struct ShaderSource						//Potential Shader::Include replacement
{										//Potential Shader::Include replacement
	int lineNum;						//Potential Shader::Include replacement
	int numLines;						//Potential Shader::Include replacement
	string file;						//Potential Shader::Include replacement
	string source;						//Potential Shader::Include replacement
	vector<ShaderSource> includeVec;	//Potential Shader::Include replacement
};										//Potential Shader::Include replacement

class Shader
{
public:
	GLuint shader_id;
	string source;

	string file;
	string path;

	struct Define
	{
		int lineNum;
		int valPos;		//position of define value in the source
		string var;
		string val;
	};

	struct Include
	{
		int lineNum;
		int numLines;
		string file;
		string source;
		vector<Include> includeVec;
	};

	struct Uniform
	{
		string name;
		string type;
		string format;
		GLuint binding;
		GLuint location;
	};

	map<string, Define>   defineMap;
	vector<Include>       includeVec;

	vector<string> additionalIncludes;	//added by function (not initially in source)

public:
	unordered_set<string> uniformSet;

	map<string, Uniform> uniformMap;

	//Initialize
	void init(const string &);
	void reinit();

	//Get ID
	GLuint id()	{ return(shader_id); }

	//Compile
	void compile();

	//Parse
	void parse();
	void parseDefines();
	void parseIncludes(string &source);
	void parseInclude(Include &include);
	void parseUniforms();


	//Log
	void log();

	//Load Source string from file
	string loadSource(const string &filename);
	string loadSource(const string &filename, int &numLines);
	string loadIncludeSource(const string &filename, int &numLines);

	//Refresh
	virtual void refresh() = 0;
	virtual void refreshSource() = 0;

	//Change a #define (and recompile)
	void setDefine(const string &, const string &);

	int getActualLineNum(int lineNum, string &file);
	int getActualLineNum(int lineNum, string &file, Include &include);
};

//////////////////////////////////////////////////////////////////////////
//ShaderT/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

template<class ShaderType>
class ShaderT : public Shader
{
protected:

public:
	//Constructors
	ShaderT(const ShaderFile &);
	ShaderT(const Source   &);

	//Destructor
	~ShaderT();

	void refresh();
	void refreshSource();
};

#include "Shader.hpp"

typedef ShaderT<vertex>   VertShader;
typedef ShaderT<fragment> FragShader;
typedef ShaderT<geometry> GeomShader;
typedef ShaderT<tessEval> EvalShader;
typedef ShaderT<tessCtrl> CtrlShader;
typedef ShaderT<compute>  CompShader;



};
//End namespace render
