//*****************************************************************************
//ShaderUniforms.cpp***********************************************************
//*****************************************************************************

//Header Include
#include "ShaderProgram.h"

//Namespaces
using namespace render;

//*****************************************************************************
//Set Uniform Floats***********************************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &varname, float v0)
{
	glProgramUniform1f(program_id, uniformLocationMap[varname], v0);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &varname, float v0, float v1)
{
	glProgramUniform2f(program_id, uniformLocationMap[varname], v0, v1);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &varname, float v0, float v1, float v2)
{
	glProgramUniform3f(program_id, uniformLocationMap[varname], v0, v1, v2);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &varname, float v0, float v1, float v2, float v3)
{
	glProgramUniform4f(program_id, uniformLocationMap[varname], v0, v1, v2, v3);
}
//-----------------------------------------------------------------------------
//void ShaderProgram::uniform(const string &varname, Signal<> signal)
//{
//	glProgramUniform1f(locate(varname), signal());
//}
//*****************************************************************************
//Set Uniform Integers*********************************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &varname, int v0)
{
	glProgramUniform1i(program_id, uniformLocationMap[varname], v0);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &varname, int v0, int v1)
{
	glProgramUniform2i(program_id, uniformLocationMap[varname], v0, v1);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &varname, int v0, int v1, int v2)
{
	glProgramUniform3i(program_id, uniformLocationMap[varname], v0, v1, v2);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &varname, int v0, int v1, int v2, int v3)
{
	glProgramUniform4i(program_id, uniformLocationMap[varname], v0, v1, v2, v3);
}
//*****************************************************************************
//Set Uniform Unsigned Integers************************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &varname, unsigned int v0)
{
	glProgramUniform1ui(program_id, uniformLocationMap[varname], v0);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &varname, unsigned int v0, unsigned int v1)
{
	glProgramUniform2ui(program_id, uniformLocationMap[varname], v0, v1);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &varname, unsigned int v0, unsigned int v1, unsigned int v2)
{
	glProgramUniform3ui(program_id, uniformLocationMap[varname], v0, v1, v2);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &varname, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
{
	glProgramUniform4ui(program_id, uniformLocationMap[varname], v0, v1, v2, v3);
}
