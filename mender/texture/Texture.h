//******************************************************************************
//render/texture/Texture.h******************************************************
//******************************************************************************

#pragma once

//Standard Library Includes
#include <string>
#include <vector>

//Render Library Includes
#include <render/gl.h>

//Namespaces
using namespace std;

namespace render
{
namespace texture
{

class Texture	//Generic parent class
{
protected:
	//ID
	GLuint   tex_id;

public:
	Texture();
	Texture(const string &);
	virtual ~Texture();

	       GLuint64  texHandle;
	vector<GLuint64> imgHandles;
public:

	GLuint id()			{	return tex_id; }

	//Bind/Unbind
	virtual void   bind() = 0;
	virtual void unbind() = 0;
//	virtual void bind_level(GLuint) = 0;

	//Enable/Disable
//	virtual void enable(GLuint)  = 0;
//	virtual void disable() = 0;

	GLuint64 getHandle();
	
};
// End class Texture
};
// End namespace texture
};
// End namespace render
