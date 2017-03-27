//******************************************************************************
//render/texture/Texture2D_Array.h**********************************************
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
class Texture2D_Array : public TextureT<tex2D_Array, TexType, IntFormat, PixFormat>
{
public:
	GLuint w, h;
	union
	{
		GLuint layers;
		GLuint d;
	};
	
	GLuint wrap_s;
	GLuint wrap_t;

private:
	//Private load
	void _load(TexType *);			//The whole enchilada
	void _load(TexType *, GLuint);	//Just one layer
public:
	//Constructors
	Texture2D_Array(GLuint, GLuint, GLuint);

//	void load(const string &, GLuint);

};
//End class Texture

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
Texture2D_Array<TexType, IntFormat, PixFormat>::Texture2D_Array(GLuint w, GLuint h, GLuint layers) : TextureT<tex2D_Array, TexType, IntFormat, PixFormat>()
{
	this->w = w;
	this->h = h;
	this->d = layers;

	wrap_s = GL_CLAMP_TO_BORDER;
	wrap_t = GL_CLAMP_TO_BORDER;

	this->bind();
	{
		glTexParameteri(traits<tex2D_Array>::target, GL_TEXTURE_MIN_FILTER, TextureT<tex2D_Array, TexType, IntFormat, PixFormat>::min_filter);
		glTexParameteri(traits<tex2D_Array>::target, GL_TEXTURE_MAG_FILTER, TextureT<tex2D_Array, TexType, IntFormat, PixFormat>::mag_filter);
		glTexParameteri(traits<tex2D_Array>::target, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(traits<tex2D_Array>::target, GL_TEXTURE_WRAP_T, wrap_t);
		this->_load(NULL);
	}
	this->unbind();
}
//******************************************************************************
//Load**************************************************************************
//******************************************************************************

//void Texture2D_Array<TexType, IntFormat, PixFormat>::load(const string &filename, GLuint layer)
//{
//	render::Image *image = new render::Image();
//
//	if(!image->load(filename))
//	{
//		cerr << "Could not load Texture2D file: " << filename << endl;
//		return;
//	}
//
//	w = image->w();
//	h = image->h();
//
//	this->bind();
//	{
//		this->_load(image->data(), layer);
//	}
//	this->unbind();
//
//	delete(image);
//}

//------------------------------------------------------------------------------
//Private load------------------------------------------------------------------
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture2D_Array<TexType, IntFormat, PixFormat>::_load(TexType *data)
{
	glTexImage3D(traits<tex2D_Array>::target,
				 0,
				 GL_DEPTH_COMPONENT24,
				 w,
				 h,
				 layers,
				 0,
				 GL_DEPTH_COMPONENT,
				 GL_FLOAT,
				 data);
//	gl::error();
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture2D_Array<TexType, IntFormat, PixFormat>::_load(TexType *data, GLuint layer)
{
	//Is this correct?
	glTexSubImage3D(traits<tex2D_Array>::target,												//Target
					0,																			//level
					0,																			//x-offset
					0,																			//y-offset
					layer,																		//z-offset
					w,																			//width
					h,																			//height
					1,																			//depth
					TextureT<tex2D_Array, TexType, IntFormat, PixFormat>::_pixel_format,		//pixel format
					traits<TexType>::type,														//type
					data);																		//data
//	gl::error();
}

};
//End namespace texture
};
//End namespace render


