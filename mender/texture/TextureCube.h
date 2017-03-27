//******************************************************************************
//render/texture/TextureCube.h**************************************************
//******************************************************************************

#pragma once

//Parent Include
#include "TextureT.h"

//Local Includes
#include "Traits.h"

namespace render
{
namespace texture
{
template<class TexType, class IntFormat, class PixFormat>
class TextureCube : public TextureT<texCube, TexType, IntFormat, PixFormat>
{
protected:

	unsigned int w, h;
	
	unsigned int wrap_s;
	unsigned int wrap_t;
	unsigned int wrap_r;


protected:

	//Load faces of the cube
	void _load_pos_x(TexType *);
	void _load_neg_x(TexType *);
	void _load_pos_y(TexType *);
	void _load_neg_y(TexType *);
	void _load_pos_z(TexType *);
	void _load_neg_z(TexType *);

	TexType *_get_data(const string &);

public:

	//Constructors
	TextureCube(const unsigned int &, const unsigned int &);

	//Load
	void load_cross(const string &);

	//Load faces of the cube
	void load_pos_x(const string &);
	void load_neg_x(const string &);
	void load_pos_y(const string &);
	void load_neg_y(const string &);
	void load_pos_z(const string &);
	void load_neg_z(const string &);
};
//End class Texture

//******************************************************************************
//render/texture/TextureCube.hpp********************************************
//******************************************************************************

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
TextureCube<TexType, IntFormat, PixFormat>::TextureCube(const unsigned int &w, const unsigned int &h) : TextureT<texCube, TexType, IntFormat, PixFormat>()
{
	this->w = w;
	this->h = h;

	wrap_s = GL_CLAMP_TO_EDGE;
	wrap_t = GL_CLAMP_TO_EDGE;
	wrap_r = GL_CLAMP_TO_EDGE;

	//ADD GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT at some point

	this->bind();
	{
		glTexParameteri(traits<texCube>::target, GL_TEXTURE_MIN_FILTER, TextureT<texCube, TexType, IntFormat, PixFormat>::min_filter);
		glTexParameteri(traits<texCube>::target, GL_TEXTURE_MAG_FILTER, TextureT<texCube, TexType, IntFormat, PixFormat>::mag_filter);
		glTexParameteri(traits<texCube>::target, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(traits<texCube>::target, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(traits<texCube>::target, GL_TEXTURE_WRAP_R, wrap_r);
		this->_load_pos_x(NULL);
		this->_load_neg_x(NULL);
		this->_load_pos_y(NULL);
		this->_load_neg_y(NULL);
		this->_load_pos_z(NULL);
		this->_load_neg_z(NULL);
	}
	this->unbind();
}
//******************************************************************************
//Load Cross********************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::load_cross(const string &filename)
{
//	id = SOIL_load_OGL_single_cubemap(filename.c_str(), "EWUDNS", SOIL_LOAD_AUTO, _tex_id, SOIL_FLAG_MIPMAPS);

/*
	nv::Image image;

	if(!image.loadImageFromFile(filename.c_str()))
	{
		cerr << "Error loading image file \"" << filename << "\"" << endl;
		exit(-1);
	}
	if(!image.convertCrossToCubemap())
	{
		cerr <<  "Error converting image to cubemap" << endl;
		exit(-1);
	};

	w = image.getWidth();
	h = image.getHeight();

	this->bind();
	{
		this->_load_pos_x((TexType *)image.getLevel(0, GL_TEXTURE_CUBE_MAP_POSITIVE_X));
		this->_load_neg_x((TexType *)image.getLevel(0, GL_TEXTURE_CUBE_MAP_NEGATIVE_X));
		this->_load_pos_y((TexType *)image.getLevel(0, GL_TEXTURE_CUBE_MAP_POSITIVE_Y));
		this->_load_neg_y((TexType *)image.getLevel(0, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y));
		this->_load_pos_z((TexType *)image.getLevel(0, GL_TEXTURE_CUBE_MAP_POSITIVE_Z));
		this->_load_neg_z((TexType *)image.getLevel(0, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z));
	}
	this->end();

*/
}



template<class TexType, class IntFormat, class PixFormat>
TexType *TextureCube<TexType, IntFormat, PixFormat>::_get_data(const string &filename)
{
//	render::Image *image = new render::Image();
//	if(!image->load(filename))
//	{
//		cerr << "Could not load Texture2D file: " << filename << endl;
//		return(NULL);
//	}
//	w = image->w();
//	h = image->h();
//
//	return((TexType *)image->data());
	return NULL;
}


//******************************************************************************
//Load faces of the cube********************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::load_pos_x(const string &filename)
{
	this->bind();
	{
		_load_pos_x(_get_data(filename));
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::load_neg_x(const string &filename)
{
	this->bind();
	{
		_load_neg_x(_get_data(filename));
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::load_pos_y(const string &filename)
{
	this->bind();
	{
		_load_pos_y(_get_data(filename));
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::load_neg_y(const string &filename)
{
	this->bind();
	{
		_load_neg_y(_get_data(filename));
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::load_pos_z(const string &filename)
{
	this->bind();
	{
		_load_pos_z(_get_data(filename));
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::load_neg_z(const string &filename)
{
	this->bind();
	{
		_load_neg_z(_get_data(filename));
	}
	this->unbind();
}
//------------------------------------------------------------------------------
//Private load------------------------------------------------------------------
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::_load_pos_x(TexType *data)
{
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_internal_format,
				 w,
				 h,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_pixel_format,
				 traits<TexType>::type,
				 data);
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::_load_neg_x(TexType *data)
{
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_internal_format,
				 w,
				 h,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_pixel_format,
				 traits<TexType>::type,
				 data);
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::_load_pos_y(TexType *data)
{
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_internal_format,
				 w,
				 h,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_pixel_format,
				 traits<TexType>::type,
				 data);
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::_load_neg_y(TexType *data)
{
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_internal_format,
				 w,
				 h,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_pixel_format,
				 traits<TexType>::type,
				 data);
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::_load_pos_z(TexType *data)
{
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_internal_format,
				 w,
				 h,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_pixel_format,
				 traits<TexType>::type,
				 data);
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCube<TexType, IntFormat, PixFormat>::_load_neg_z(TexType *data)
{
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_internal_format,
				 w,
				 h,
				 0,
				 TextureT<texCube, TexType, IntFormat, PixFormat>::_pixel_format,
				 traits<TexType>::type,
				 data);
}

};
//End namespace texture
};
//End namespace render


