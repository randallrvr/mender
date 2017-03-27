//*****************************************************************************
//render/shader/Shader.hpp**************************************************
//*****************************************************************************



//*****************************************************************************
//Constructor******************************************************************
//*****************************************************************************
template<class ShaderType>
ShaderT<ShaderType>::ShaderT(const ShaderFile &shaderFile)
{
	//Separate path from filename
	const string &filename = shaderFile.filename;
	int index = math::max((int)filename.find_last_of('/'), (int)filename.find_last_of('\\'));
	path = filename.substr(0, index) + "/";
	file = filename.substr(index + 1);

	shader_id = glCreateShader(traits<ShaderType>::type);

	additionalIncludes = shaderFile.includes;

	init(loadSource(shaderFile.filename));
}
//-----------------------------------------------------------------------------
template<class ShaderType>
ShaderT<ShaderType>::ShaderT(const Source &source)
{
	path = file = "";
	shader_id = glCreateShader(traits<ShaderType>::type);

	init(source);
}
//*****************************************************************************
//Destructor*******************************************************************
//*****************************************************************************
template<class ShaderType>
ShaderT<ShaderType>::~ShaderT()
{
	glDeleteShader(shader_id);
}
//*****************************************************************************
//Refresh**********************************************************************
//*****************************************************************************
template<class ShaderType>
void ShaderT<ShaderType>::refresh()
{
	if(file.length() > 0)	//If loaded from a file
	{
		glDeleteShader(shader_id);
		shader_id = glCreateShader(traits<ShaderType>::type);
		init(loadSource(path+file));
	}
}
//-----------------------------------------------------------------------------
template<class ShaderType>
void ShaderT<ShaderType>::refreshSource()
{
	glDeleteShader(shader_id);
	shader_id = glCreateShader(traits<ShaderType>::type);
	reinit();

//	this->compile();
//	this->log(); 
}


