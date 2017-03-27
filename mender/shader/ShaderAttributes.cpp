//*****************************************************************************
//ShaderAttributes.cpp*********************************************************
//*****************************************************************************

//Header Include
#include "ShaderProgram.h"

//Namespaces
using namespace render;

//*****************************************************************************
//Set Float Vertex Attibutes***************************************************
//*****************************************************************************
void ShaderProgram::attribute(const string &name, float v0)
{
	glVertexAttrib1f(locateAttribute(name), v0);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, float v0, float v1)
{
	glVertexAttrib2f(locateAttribute(name), v0, v1);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, float v0, float v1, float v2)
{
	glVertexAttrib3f(locateAttribute(name), v0, v1, v2);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, float v0, float v1, float v2, float v3)
{
 	glVertexAttrib4f(locateAttribute(name), v0, v1, v2, v3);
}
//*****************************************************************************
//Set Double Vertex Attibutes**************************************************
//*****************************************************************************
void ShaderProgram::attribute(const string &name, double v0)
{
	glVertexAttrib1d(locateAttribute(name), v0);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, double v0, double v1)
{
	glVertexAttrib2d(locateAttribute(name), v0, v1);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, double v0, double v1, double v2)
{
	glVertexAttrib3d(locateAttribute(name), v0, v1, v2);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, double v0, double v1, double v2, double v3)
{
	glVertexAttrib4d(locateAttribute(name), v0, v1, v2, v3);
}
//*****************************************************************************
//Set Short Vertex Attibutes***************************************************
//*****************************************************************************
void ShaderProgram::attribute(const string &name, short int v0)
{
	glVertexAttrib1s(locateAttribute(name), v0);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, short int v0, short int v1)
{
	glVertexAttrib2s(locateAttribute(name), v0, v1);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, short int v0, short int v1, short int v2)
{
	glVertexAttrib3s(locateAttribute(name), v0, v1, v2);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, short int v0, short int v1, short int v2, short int v3)
{
	glVertexAttrib4s(locateAttribute(name), v0, v1, v2, v3);
}
//*****************************************************************************
//Set Integer Vertex Attibutes*************************************************
//*****************************************************************************
void ShaderProgram::attribute(const string &name, int v0)
{
	glVertexAttribI1i(locateAttribute(name), v0);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, int v0, int v1)
{
	glVertexAttribI2i(locateAttribute(name), v0, v1);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, int v0, int v1, int v2)
{
	glVertexAttribI3i(locateAttribute(name), v0, v1, v2);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, int v0, int v1, int v2, int v3)
{
	glVertexAttribI4i(locateAttribute(name), v0, v1, v2, v3);
}
//*****************************************************************************
//Set Unsigned Integer Vertex Attibutes****************************************
//*****************************************************************************
void ShaderProgram::attribute(const string &name, GLuint v0)
{
	glVertexAttribI1ui(locateAttribute(name), v0);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, GLuint v0, GLuint v1)
{
	glVertexAttribI2ui(locateAttribute(name), v0, v1);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, GLuint v0, GLuint v1, GLuint v2)
{
	glVertexAttribI3ui(locateAttribute(name), v0, v1, v2);
}
//-----------------------------------------------------------------------------
void ShaderProgram::attribute(const string &name, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	glVertexAttribI4ui(locateAttribute(name), v0, v1, v2, v3);
}
