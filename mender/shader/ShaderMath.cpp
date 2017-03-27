//*****************************************************************************
//ShaderMath.cpp***************************************************************
//*****************************************************************************

//Header Include
#include "ShaderProgram.h"

//Namespaces
using namespace render;

//*****************************************************************************
//Set Uniform Integer Vectors**************************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &name, vec2i v)
{
	glProgramUniform2iv(program_id, getUniformLoc(name), 1, v);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, vec3i v)
{
	glProgramUniform3iv(program_id, getUniformLoc(name), 1, v);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, vec4i v)
{

	glProgramUniform4iv(program_id, getUniformLoc(name), 1, v);
}
//*****************************************************************************
//Set Uniform Floating Point Vectors*******************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &name, vec2f v)
{
	glProgramUniform2fv(program_id, getUniformLoc(name), 1, v);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, vec3f v)
{
	glProgramUniform3fv(program_id, getUniformLoc(name), 1, v);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, vec4f v)
{
	glProgramUniform4fv(program_id, getUniformLoc(name), 1, v);
}
//*****************************************************************************
//Set Uniform Double Vectors***************************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &name, vec2d vd)
{
	glProgramUniform2dv(program_id, getUniformLoc(name), 1, vd);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, vec3d vd)
{
	glProgramUniform3dv(program_id, getUniformLoc(name), 1, vd);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, vec4d vd)
{
	glProgramUniform4dv(program_id, getUniformLoc(name), 1, vd);
}
//*****************************************************************************
//Set Uniform Integer Vector Arrays********************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &name, GLsizei count, vec2i *v)
{
	glProgramUniform2iv(program_id, getUniformLoc(name), count, v[0]);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, GLsizei count, vec3i *v)
{
	glProgramUniform3iv(program_id, getUniformLoc(name), count, v[0]);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, GLsizei count, vec4i *v)
{
	glProgramUniform4iv(program_id, getUniformLoc(name), count, v[0]);
}
//*****************************************************************************
//Set Uniform Floating Point Vectors*******************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &name, GLsizei count, vec2f *v)
{
	glProgramUniform2fv(program_id, getUniformLoc(name), count, v[0]);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, GLsizei count, vec3f *v)
{
	glProgramUniform3fv(program_id, getUniformLoc(name), count, v[0]);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, GLsizei count, vec4f *v)
{
	glProgramUniform4fv(program_id, getUniformLoc(name), count, v[0]);
}
//*****************************************************************************
//Set Uniform Double Vectors***************************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &name, GLsizei count, vec2d *v)
{
	glProgramUniform2dv(program_id, getUniformLoc(name), count, v[0]);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, GLsizei count, vec3d *v)
{
	glProgramUniform3dv(program_id, getUniformLoc(name), count, v[0]);
}
//-----------------------------------------------------------------------------
void ShaderProgram::uniform(const string &name, GLsizei count, vec4d *v)
{
	glProgramUniform4dv(program_id, getUniformLoc(name), count, v[0]);
}
//*****************************************************************************
//Set Uniform Floating Point Quaternions***************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &name, quatf q)
{
	glProgramUniform4fv(program_id, getUniformLoc(name), 1, q.comp);
}
//*****************************************************************************
//Set Uniform Floating Point Matrices******************************************
//*****************************************************************************
void ShaderProgram::uniform(const string &name, mat3f m, bool transpose)
{
//	GLint location = getUniformLoc(name);
//	glProgramUniformMatrix4fv(program_id, location, 1, transpose, &(m.m00));
	glProgramUniformMatrix3fv(program_id, getUniformLoc(name), 1, transpose, m);
}



void ShaderProgram::uniform(const string &name, mat4f m, bool transpose)
{
//	GLint location = getUniformLoc(name);
//	glProgramUniformMatrix4fv(program_id, location, 1, transpose, &(m.m00));
	glProgramUniformMatrix4fv(program_id, getUniformLoc(name), 1, transpose, m);
}

