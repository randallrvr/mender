//******************************************************************************
//render/texture/Texture2D.h****************************************************
//******************************************************************************

#pragma once

//Parent Include
#include "TextureT.h"

#include "stb_image.h"

#include <iomanip>

namespace render
{
namespace texture
{

template<class TexType, class IntFormat, class PixFormat>
class Texture2D : public TextureT<tex2D, TexType, IntFormat, PixFormat>
{
public:

	typedef TextureT<tex2D, TexType, IntFormat, PixFormat> texture_base;

	GLuint  w, h;
	
	GLuint wrap_s;
	GLuint wrap_t;

private:
	//Private load
	void _load(TexType *);

public:

	//Constructors
	Texture2D(GLuint, GLuint);
	Texture2D(const string &);

	//Load
	void load_data(TexType *);		//from data

	//Image Data
	TexType *image(GLuint = 0);

	void resize(GLuint w, GLuint h);

	//Set wrap parameters
	void set_wrap(GLuint);
	void set_wrap_s(GLuint);
	void set_wrap_t(GLuint);

	//Generate mipmap
	void mipmap();

	
	void parameter(GLenum pname, GLint param)
	{
		glBindTexture(GL_TEXTURE_2D, Texture::tex_id);
		glTexParameteri(GL_TEXTURE_2D, pname, param);
	}

	void parameter(GLenum pname, GLfloat param)
	{
		glBindTexture(GL_TEXTURE_2D, Texture::tex_id);
		glTexParameterf(GL_TEXTURE_2D, pname, param);
	}


	//Print
	template<int I>
	void print(GLuint mipmap_level = 0)
	{
		TexType *data = this->image(mipmap_level);
		int channels = traits<IntFormat>::channels;
		int cols = this->w / (int)(pow(2.0, (int)mipmap_level));
		int rows = this->h / (int)(pow(2.0, (int)mipmap_level));
		for(int i = rows-1; i >= 0; i--)
		{
			for(int j = 0; j < cols; j++)
			{
				cout << std::setprecision(5) << std::setfill(' ') << std::setw(4) << data[(i*cols + j)*channels + I] << " ";
			}
			cout << endl;
		}
		delete [] data;
		cout << endl;
	}

	template<int I, int J>
	void print(GLuint mipmap_level = 0)
	{
		float *data = this->image(mipmap_level);
		int channels = traits<IntFormat>::channels;
		int cols = this->w / (int)(pow(2.0, (int)mipmap_level));
		int rows = this->h / (int)(pow(2.0, (int)mipmap_level));	
		for(int i = rows-1; i >= 0; i--)
		{
			for(int j = 0; j < cols; j++)
			{
				cout << setprecision(5) << setfill(' ') << setw(4) << "(" << data[(i*cols + j)*channels + I] << ", " << data[(i*cols + j)*channels + J] << ") ";
			}
			cout << endl;
		}
		delete [] data;
		cout << endl;
	}

	template<int I, int J, int K>
	void print(GLuint mipmap_level = 0)
	{
		float *data = this->image(mipmap_level);
		int channels = traits<IntFormat>::channels;
		int cols = this->w / (int)(pow(2.0, (int)mipmap_level));
		int rows = this->h / (int)(pow(2.0, (int)mipmap_level));		
		for(int i = rows-1; i >= 0; i--)
		{
			for(int j = 0; j < cols; j++)
			{
				cout << setprecision(5) << setfill(' ') << "(" << setw(2) << data[(i*cols + j)*channels + I] << "," << setw(2) << data[(i*cols + j)*channels + J] << "," << setw(2) << data[(i*cols + j)*channels + K] << ") ";
			}
			cout << endl;
		}
		delete [] data;
		cout << endl;
	}

	template<int I, int J, int K, int L>
	void print(GLuint mipmap_level = 0)
	{
		float *data = this->image(mipmap_level);
		int channels = traits<IntFormat>::channels;
		int cols = this->w / (int)(pow(2.0, (int)mipmap_level));
		int rows = this->h / (int)(pow(2.0, (int)mipmap_level));
		for(int i = rows-1; i >= 0; i--)
		{
			for(int j = 0; j < cols; j++)
			{
				cout << setprecision(5) << setfill(' ') << setw(6) << "(" << data[(i*cols + j)*channels + I] << ", " << data[(i*cols + j)*channels + J] << ", " << data[(i*cols + j)*channels + K] << ", " << data[(i*cols + j)*channels + L]<< ") ";
			}
			cout << endl;
		}
		delete [] data;
		cout << endl;
	}
};
//End class Texture

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
Texture2D<TexType, IntFormat, PixFormat>::Texture2D(GLuint w, GLuint h) : TextureT<tex2D, TexType, IntFormat, PixFormat>()
{
	this->w = w;
	this->h = h;

	wrap_s = GL_REPEAT;
	wrap_t = GL_REPEAT;

	this->bind();
	{
		glTexParameteri(traits<tex2D>::target, GL_TEXTURE_MIN_FILTER, texture_base::min_filter);
		glTexParameteri(traits<tex2D>::target, GL_TEXTURE_MAG_FILTER, texture_base::mag_filter);
		glTexParameteri(traits<tex2D>::target, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(traits<tex2D>::target, GL_TEXTURE_WRAP_T, wrap_t);
		this->_load(NULL);
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
Texture2D<TexType, IntFormat, PixFormat>::Texture2D(const string &file) : TextureT<tex2D, TexType, IntFormat, PixFormat>()
{
	wrap_s = GL_REPEAT;
	wrap_t = GL_REPEAT;

	int width, height, bpp;

	stbi_set_flip_vertically_on_load(true);
	unsigned char *rgba = stbi_load( file.c_str(), &width, &height, &bpp, 4 );
	// rgb is now four bytes per pixel, width*height size. Or NULL if load failed.
	// Do something with it...

	if(rgba != NULL)
	{
		// Get width & height
		this->w = width;
		this->h = height;

		this->bind();
		{
			glTexParameteri(traits<tex2D>::target, GL_TEXTURE_MIN_FILTER, texture_base::min_filter);
			glTexParameteri(traits<tex2D>::target, GL_TEXTURE_MAG_FILTER, texture_base::mag_filter);
			glTexParameteri(traits<tex2D>::target, GL_TEXTURE_WRAP_S, wrap_s);
			glTexParameteri(traits<tex2D>::target, GL_TEXTURE_WRAP_T, wrap_t);
			this->_load(rgba);
		}
		this->unbind();
	}
	else
	{
		cerr << "error: " << stbi_failure_reason() << " " << file << endl;
	}

	stbi_image_free(rgba);
}
//******************************************************************************
//Load***************** *********************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void Texture2D<TexType, IntFormat, PixFormat>::load_data(TexType *data)
{
	this->bind();
	{
		this->_load(data);
	}
	this->unbind();
}
//------------------------------------------------------------------------------
//Private load------------------------------------------------------------------
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture2D<TexType, IntFormat, PixFormat>::_load(TexType *data)
{
	glTexImage2D(traits<tex2D>::target,
				 0,
				 traits<IntFormat>::internal_format,
				 w,
				 h,
				 0,
				 traits<PixFormat>::pixel_format,
				 traits<TexType>::type,
				 data);
}
//******************************************************************************
//Resize************************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void Texture2D<TexType, IntFormat, PixFormat>::resize( GLuint w, GLuint h )
{
	this->w = w;
	this->h = h;

	load_data(NULL);
}
//******************************************************************************
//Image Data********************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
TexType *Texture2D<TexType, IntFormat, PixFormat>::image(GLuint mipmap_level)
{
	GLuint w = this->w / (int)(pow(2.0, (int)mipmap_level));
	GLuint h = this->h / (int)(pow(2.0, (int)mipmap_level));

	int channels = traits<IntFormat>::channels;

	TexType *data = new TexType[channels*w*h];
	this->bind();
	{
		glGetTexImage(traits<tex2D>::target,			//target
					  mipmap_level,						//level
					  traits<PixFormat>::pixel_format,	//pixel format
					  traits<TexType>::type,			//type
					  data);							//data
	}
	this->unbind();

	return(data);
}
//******************************************************************************
//Generate Mipmap***************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void Texture2D<TexType, IntFormat, PixFormat>::mipmap()
{
	this->bind();
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	this->unbind();
}
//******************************************************************************
//Set wrap parameters***********************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void Texture2D<TexType, IntFormat, PixFormat>::set_wrap(GLuint wrap)
{
	wrap_s = wrap_t = wrap;
	this->bind();
	{
		glTexParameteri(traits<tex2D>::target, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(traits<tex2D>::target, GL_TEXTURE_WRAP_T, wrap_t);
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture2D<TexType, IntFormat, PixFormat>::set_wrap_s(GLuint wrap)
{
	wrap_s = wrap;
	this->bind();
	{
		glTexParameteri(traits<tex2D>::target, GL_TEXTURE_WRAP_S, wrap_s);
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture2D<TexType, IntFormat, PixFormat>::set_wrap_t(GLuint wrap)
{
	wrap_t = wrap;
	this->bind();
	{
		glTexParameteri(traits<tex2D>::target, GL_TEXTURE_WRAP_T, wrap_t);
	}
	this->unbind();
}



};
//End namespace texture
};
//End namespace render

