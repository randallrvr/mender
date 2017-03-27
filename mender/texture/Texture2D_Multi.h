//******************************************************************************
//render/texture/Texture2D_Multi.h**********************************************
//******************************************************************************

#pragma once

//Parent Include
#include "TextureT.h"

//Namespaces
using namespace std;

namespace render {
namespace texture {

#include "Traits.h"

template<class TexType, class IntFormat, class PixFormat>
class Texture2D_Multi : public TextureT<tex2D_Multi, TexType, IntFormat, PixFormat>
{
public:
	GLuint w, h;
	GLuint samples;
	GLboolean fixedsamplelocations;

	GLuint wrap_s;
	GLuint wrap_t;

public:
	// Constructors
	Texture2D_Multi(GLuint w, GLuint h, GLuint numSamples = 1, bool fixed = false);

	// Set Samples
	void setSamples(GLuint numSamples);


};
//End class Texture

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
Texture2D_Multi<TexType, IntFormat, PixFormat>::Texture2D_Multi(GLuint w, GLuint h, GLuint numSamples, bool fixed) : TextureT<tex2D_Multi, TexType, IntFormat, PixFormat>()
{
	this->w = w;
	this->h = h;
	this->samples = numSamples;
	this->fixedsamplelocations = fixed;

	wrap_s = GL_CLAMP_TO_BORDER;
	wrap_t = GL_CLAMP_TO_BORDER;

	this->bind();
	{
		glTexParameteri(traits<tex2D_Multi>::target, GL_TEXTURE_MIN_FILTER, TextureT<tex2D_Multi, TexType, IntFormat, PixFormat>::min_filter);
		glTexParameteri(traits<tex2D_Multi>::target, GL_TEXTURE_MAG_FILTER, TextureT<tex2D_Multi, TexType, IntFormat, PixFormat>::mag_filter);
		glTexParameteri(traits<tex2D_Multi>::target, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(traits<tex2D_Multi>::target, GL_TEXTURE_WRAP_T, wrap_t);

		glTexImage2DMultisample(traits<tex2D_Multi>::target,
								numSamples,
								traits<IntFormat>::internal_format,
								w,
								h,
								fixed);
	}
	this->unbind();
}

template<class TexType, class IntFormat, class PixFormat>
void Texture2D_Multi<TexType, IntFormat, PixFormat>::setSamples(GLuint numSamples)
{
	this->bind();
	{
		glTexImage2DMultisample(traits<tex2D_Multi>::target,
								numSamples,
								traits<IntFormat>::internal_format,
								w,
								h,
								fixedsamplelocations);
	}
	this->unbind();
}


};
//End namespace texture
};
//End namespace render


