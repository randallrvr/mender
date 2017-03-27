//******************************************************************************
//render/texture/TextureT.h*****************************************************
//******************************************************************************

#pragma once

//Standard Library Includes
#include <iostream>
#include <string>
#include <map>

//Render Library Includes
#include <render/gl.h>


//Local Includes
#include "Texture.h"
#include "Traits.h"

//Namespaces
using namespace std;

namespace render
{
namespace texture
{

class filter
{
private:
	GLuint _filter;
public:
	void set_nearest()					{ _filter = GL_NEAREST; }
	void set_linear()					{ _filter = GL_LINEAR; }
	void set_nearest_mipmap_nearest()	{ _filter = GL_NEAREST_MIPMAP_NEAREST; }
	void set_linear_mipmap_nearest()	{ _filter = GL_LINEAR_MIPMAP_NEAREST; }
	void set_nearest_mipmap_linear()	{ _filter = GL_NEAREST_MIPMAP_LINEAR; }
	void set_linear_mipmap_linear()		{ _filter = GL_LINEAR_MIPMAP_LINEAR; }
};
//End class filter



template<class TexTarget, class TexType, class IntFormat, class PixFormat>
class TextureT : public Texture
{
public:
	GLuint min_filter;		//GL_NEAREST, GL_LINEAR
	GLuint mag_filter;		//GL_NEAREST, GL_LINEAR

public:
	//Bind/Unbind
	void   bind();
	void unbind();

	//Type
	GLuint type();

	//Target
	GLuint target();

private:
	//Private load
//	virtual void _load(TexType *) = 0;
public:

	//Constructors
	TextureT();

	//Begin/End
	void begin();
	void end();

	//Set
	void set_min_filter(GLuint);
	void set_mag_filter(GLuint);
	void set_filter(GLuint);

	void load_data(TexType *);

	GLuint getChannels()
	{
		return traits<IntFormat>::channels;
	}

	void setAnisotropy(const GLfloat anisotropy)
	{
		this->bind();
		{
			glTexParameterf(traits<TexTarget>::target, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
		}
		this->unbind();
	}

	void setMaxAnisotropy()
	{
		this->bind();
		{
			GLfloat maxAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
			glTexParameterf(traits<TexTarget>::target, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
		}
	}

	void genMipmap()
	{
		this->bind();
		{
			glGenerateMipmap(traits<TexTarget>::target);
		}
		this->unbind();
	}

	void clear(MipLevel mipLevel = 0)
	{
		TexType zero = (TexType)0;

		GLenum pixFormat = traits<PixFormat>::pixel_format;
		GLenum pixType   = traits<TexType>::type;

		glClearTexImage(tex_id, mipLevel.val, pixFormat, pixType, &zero);
	}

};
//End class Texture

//******************************************************************************
//render/texture/TextureT.hpp***************************************************
//******************************************************************************

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
TextureT<TexTarget, TexType, IntFormat, PixFormat>::TextureT() : Texture()
{
	min_filter = GL_LINEAR;	//GL_NEAREST;
	mag_filter = GL_LINEAR;	//GL_NEAREST;
}
//******************************************************************************
//Bind**************************************************************************
//******************************************************************************
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void TextureT<TexTarget, TexType, IntFormat, PixFormat>::bind()
{
	glBindTexture(traits<TexTarget>::target, tex_id);
}
//******************************************************************************
//Unbind************************************************************************
//******************************************************************************
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void TextureT<TexTarget, TexType, IntFormat, PixFormat>::unbind()
{
	glBindTexture(traits<TexTarget>::target, 0);
}
//******************************************************************************
//Begin*************************************************************************
//******************************************************************************
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void TextureT<TexTarget, TexType, IntFormat, PixFormat>::begin()
{
	glActiveTexture(GL_TEXTURE0/* + tex_unit*/);

	this->bind();
//	{
	glEnable(traits<TexTarget>::target);
}
//******************************************************************************
//End***************************************************************************
//******************************************************************************
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void TextureT<TexTarget, TexType, IntFormat, PixFormat>::end()
{
	glDisable(traits<TexTarget>::target);
//	}
	this->unbind();
}
//******************************************************************************
//Set***************************************************************************
//******************************************************************************
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void TextureT<TexTarget, TexType, IntFormat, PixFormat>::set_min_filter(GLuint min_filter)
{
	this->min_filter = min_filter;
	this->bind();
	{
		glTexParameteri(traits<TexTarget>::target, GL_TEXTURE_MIN_FILTER, min_filter);
	}
	this->unbind();}
//------------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void TextureT<TexTarget, TexType, IntFormat, PixFormat>::set_mag_filter(GLuint mag_filter)
{
	this->mag_filter = mag_filter;
	this->bind();
	{
		glTexParameteri(traits<TexTarget>::target, GL_TEXTURE_MAG_FILTER, mag_filter);
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void TextureT<TexTarget, TexType, IntFormat, PixFormat>::set_filter(GLuint filter)
{
	min_filter = mag_filter = filter;
	this->bind();
	{
		glTexParameteri(traits<TexTarget>::target, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(traits<TexTarget>::target, GL_TEXTURE_MAG_FILTER, mag_filter);
	}
	this->unbind();
}
//******************************************************************************
//Get Texture Target************************************************************
//******************************************************************************
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
GLuint TextureT<TexTarget, TexType, IntFormat, PixFormat>::target()
{
	return(traits<TexTarget>::target);
}

};
//End namespace texture
};
//End namespace render

