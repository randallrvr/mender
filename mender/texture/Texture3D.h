//******************************************************************************
//render/texture/Texture3D.h****************************************************
//******************************************************************************

#pragma once

//Parent Include
#include "TextureT.h"


namespace render
{
namespace texture
{



template<class TexType, class IntFormat, class PixFormat>
class Texture3D : public TextureT<tex3D, TexType, IntFormat, PixFormat>
{
public:
	union
	{
		struct { GLuint w, h, d; };
		struct { GLuint width, height, depth; };
	};
	GLuint levels;

	GLuint wrap_s;
	GLuint wrap_t;
	GLuint wrap_r;
private:
	//Private load
	void _load(TexType *);	//from file

	//Initialize texture storage (immutable)
	void _alloc(GLuint w, GLuint h, GLuint d, GLuint levels);

public:
	//Constructors
	Texture3D();
	Texture3D(GLuint w, GLuint h, GLuint d, GLuint levels = 1);
	
	Texture3D(Texture3D *tex3D, GLuint mipmap_level);

	void init(GLuint w, GLuint h, GLuint d, GLuint levels = 1);
	void initHandles();

	void makeImageResident();
	void makeTextureResident();

	//Load
	void load_data(TexType *);		//from data

	void fill(TexType);

	//Image Data
	TexType *getData();
	TexType *getDataMipmapLevel(GLuint mipmap_level);

	GLuint numLevels()	{ return levels; }
	void mipmap();

	void clearAllLevels()	//All Levels
	{
		GLenum pixFormat = traits<PixFormat>::pixel_format;
		GLenum pixType   = traits<TexType>::type;

		for(GLuint mipLevel= 0; mipLevel < levels; mipLevel++)
		{
			glClearTexImage(Texture::tex_id, mipLevel, pixFormat, pixType, NULL);
		}
	}

	void clearAllLevels(const void *data)	//All Levels
	{
		GLenum pixFormat = traits<PixFormat>::pixel_format;
		GLenum pixType   = traits<TexType>::type;

		for(GLuint mipLevel= 0; mipLevel < levels; mipLevel++)
		{
			glClearTexImage(Texture::tex_id, mipLevel, pixFormat, pixType, &data);
		}
	}

	template<class clearType, class clearPixFormat>
	void clearAllLevels()
	{
		clearType zero = (clearType)0;

		GLenum pixFormat = traits<clearPixFormat>::pixel_format;
		GLenum pixType   = traits<clearType>::type;

		for(GLuint mipLevel= 0; mipLevel < levels; mipLevel++)
		{
			glClearTexImage(Texture::tex_id, mipLevel, pixFormat, pixType, &zero);
		}
	}



};
//End class Texture

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
Texture3D<TexType, IntFormat, PixFormat>::Texture3D() : TextureT<tex3D, TexType, IntFormat, PixFormat>()
{
	//Nothing, let parent classes generate id, but useless until initialized
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
Texture3D<TexType, IntFormat, PixFormat>::Texture3D(GLuint w, GLuint h, GLuint d, GLuint levels) : TextureT<tex3D, TexType, IntFormat, PixFormat>()
{
	this->init(w,h,d,levels);
}
//------------------------------------------------------------------------------
//Construct Texture View from Texture3D based on mipmapLevel--------------------
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
Texture3D<TexType, IntFormat, PixFormat>::Texture3D(Texture3D *texture3D, GLuint mipmap_level)  : TextureT<tex3D, TexType, IntFormat, PixFormat>()
{
	glTextureView(Texture::tex_id,
				  traits<tex3D>::target,
				  texture3D->id(),
				  traits<IntFormat>::internal_format,
				  mipmap_level,
				  1,
				  0,
				  1);

	this->w = texture3D->w >> mipmap_level;
	this->h = texture3D->h >> mipmap_level;
	this->d = texture3D->d >> mipmap_level;

	this->levels = 1;

	wrap_s = GL_CLAMP_TO_BORDER;
	wrap_t = GL_CLAMP_TO_BORDER;
	wrap_r = GL_CLAMP_TO_BORDER;

	this->bind();
	{
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_MIN_FILTER, TextureT<tex3D, TexType, IntFormat, PixFormat>::min_filter);
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_MAG_FILTER, TextureT<tex3D, TexType, IntFormat, PixFormat>::mag_filter);
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_WRAP_T, wrap_r);
	}
	this->unbind();
}
//------------------------------------------------------------------------------
//Initialize--------------------------------------------------------------------
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture3D<TexType, IntFormat, PixFormat>::init(GLuint w, GLuint h, GLuint d, GLuint levels)
{
	this->w = w;
	this->h = h;
	this->d = d;

	this->levels = levels;

	wrap_s = GL_CLAMP_TO_BORDER;
	wrap_t = GL_CLAMP_TO_BORDER;
	wrap_r = GL_CLAMP_TO_BORDER;

	this->bind();
	{
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_MIN_FILTER, TextureT<tex3D, TexType, IntFormat, PixFormat>::min_filter);
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_MAG_FILTER, TextureT<tex3D, TexType, IntFormat, PixFormat>::mag_filter);
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(traits<tex3D>::target, GL_TEXTURE_WRAP_T, wrap_r);

		//		this->_load(NULL);
		this->_alloc(w, h, d, levels);
	}
	this->unbind();
}
//------------------------------------------------------------------------------
//Init Handles------------------------------------------------------------------
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture3D<TexType, IntFormat, PixFormat>::initHandles()
{
//	texHandle = 0;
//#if OPENGL_VER >= 44
//	texHandle = glGetTextureHandleARB(tex_id);
//	glMakeTextureHandleResidentARB(texHandle);
//#elif OPENGL_VER >= 40
//	texHandle = glGetTextureHandleNV(tex_id);
//	glMakeTextureHandleResidentNV(texHandle);
//#endif
//
//	GLenum format = traits<IntFormat>::internal_format;
//	for(int level = 0; level < (int)levels; level++)
//	{
//		GLuint64 imgHandle = 0;
//#if OPENGL_VER >= 44
//		imgHandle = glGetImageHandleARB(tex_id, level, GL_TRUE, 0, format);
//		glMakeImageHandleResidentARB(imgHandle, GL_READ_WRITE);
//#elif OPENGL_VER >= 40
//		imgHandle = glGetImageHandleNV(tex_id, level, GL_TRUE, 0, format);
//		glMakeImageHandleResidentNV(imgHandle, GL_READ_WRITE);
//#endif
//		imgHandles.push_back(imgHandle);
//	}
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture3D<TexType, IntFormat, PixFormat>::makeImageResident()
{
//	if(glIsTextureHandleResidentARB(this->texHandle))
//	{
//		glMakeTextureHandleNonResidentARB(this->texHandle);
//	}
//
//	GLenum format = traits<IntFormat>::internal_format;
//	for(int level = 0; level < (int)levels; level++)
//	{
//		glMakeImageHandleResidentARB(this->imgHandles[level], GL_READ_WRITE);
//	}
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture3D<TexType, IntFormat, PixFormat>::makeTextureResident()
{
//	GLenum format = traits<IntFormat>::internal_format;
//	for(int level = 0; level < (int)levels; level++)
//	{
//		if(glIsTextureHandleResidentARB(this->imgHandles[level]))
//			glMakeImageHandleNonResidentARB(this->imgHandles[level]);
//	}
//
//	if(!glIsTextureHandleResidentARB(this->texHandle))
//	{
//		glMakeTextureHandleResidentARB(this->texHandle);
//	}


}

//------------------------------------------------------------------------------
//Allocate----------------------------------------------------------------------
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void Texture3D<TexType, IntFormat, PixFormat>::_alloc(GLuint w, GLuint h, GLuint d, GLuint levels)
{
	GLenum texTarget = traits<tex3D>::target;
	GLenum intFormat = traits<IntFormat>::internal_format;
	GLenum pixFormat = traits<PixFormat>::pixel_format;
	GLenum pixType   = traits<TexType>::type;

	this->bind();
	{
		glTexStorage3D(texTarget,
					   levels,
					   intFormat,
					   w,
					   h,
					   d);



		int channels = traits<IntFormat>::channels;

		int lw = w;
		int lh = h;
		int ld = d;

		for(int level = 0; level < (int)levels; level++)
		{
			TexType *data = new TexType[channels*w*h*d];
			glTexSubImage3D(texTarget,
							GLint(level),
							0, 0, 0,
							GLsizei(lw),
							GLsizei(lh),
							GLsizei(ld),
							pixFormat,
							pixType,
							data);

			lw /= 2;
			lh /= 2;
			ld /= 2;

			delete [] data;
		}
	}
	this->unbind();
}
//******************************************************************************
//Load**************************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void Texture3D<TexType, IntFormat, PixFormat>::load_data(TexType *data)
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
void Texture3D<TexType, IntFormat, PixFormat>::_load(TexType *data)
{
	GLenum texTarget = traits<tex3D>::target;
	GLenum pixFormat = traits<PixFormat>::pixel_format;
	GLenum pixType   = traits<TexType>::type;

	//New
	glTexSubImage3D(texTarget,
					GLint(0),
					0, 0, 0,	//offsets
					GLsizei(w),
					GLsizei(h),
					GLsizei(d),
					pixFormat,
					pixType,
					data);

	//Old
//	glTexImage3D(traits<tex3D>::target,
//		0,
//		traits<IntFormat>::internal_format,
//		w,
//		h,
//		d,
//		0,
//		traits<PixFormat>::pixel_format,
//		traits<TexType>::type,
//		data);
}

template<class TexType, class IntFormat, class PixFormat>
void Texture3D<TexType, IntFormat, PixFormat>::fill(TexType val)
{
	GLuint channels  = traits<IntFormat>::channels;
	GLenum texTarget = traits<tex3D>::target;
	GLenum pixFormat = traits<PixFormat>::pixel_format;
	GLenum pixType   = traits<TexType>::type;

	TexType *data = new TexType[channels*w*h*d];

	memset(data, val, sizeof(TexType)*channels*w*h*d);

	this->bind();

	//New
	glTexSubImage3D(texTarget,
					GLint(0),
					0, 0, 0,	//offsets
					GLsizei(w),
					GLsizei(h),
					GLsizei(d),
					pixFormat,
					pixType,
					data);

	this->unbind();

	delete [] data;

	//Old
//	glTexImage3D(traits<tex3D>::target,
//		0,
//		traits<IntFormat>::internal_format,
//		w,
//		h,
//		d,
//		0,
//		traits<PixFormat>::pixel_format,
//		traits<TexType>::type,
//		data);
}
//******************************************************************************
//Generate Mipmap***************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void Texture3D<TexType, IntFormat, PixFormat>::mipmap()
{
	this->bind();
	{
		glGenerateMipmap(GL_TEXTURE_3D);
	}
	this->unbind();
}
//******************************************************************************
//Get Data**********************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
TexType *Texture3D<TexType, IntFormat, PixFormat>::getData()
{
	GLuint channels  = traits<IntFormat>::channels;
	GLenum texTarget = traits<tex3D>::target;
	GLenum pixFormat = traits<PixFormat>::pixel_format;
	GLenum pixType   = traits<TexType>::type;

	TexType *data = new TexType[channels*w*h*d];
	this->bind();
	{
		glGetTexImage(texTarget,		//target
					  0,				//mipmap level
					  pixFormat,		//pixel format
					  pixType,			//type
					  data);			//data
	}
	this->unbind();

	return data;
}
//------------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
TexType *Texture3D<TexType, IntFormat, PixFormat>::getDataMipmapLevel(GLuint mipLevel)
{
	GLuint w = this->w >> mipLevel;
	GLuint h = this->h >> mipLevel;
	GLuint d = this->d >> mipLevel;

	GLuint channels  = traits<IntFormat>::channels;
	GLenum texTarget = traits<tex3D>::target;
	GLenum pixFormat = traits<PixFormat>::pixel_format;
	GLenum pixType   = traits<TexType>::type;

	TexType *data = new TexType[channels*w*h*d];
	this->bind();
	{
		glGetTexImage(texTarget,		//target
					  mipLevel,			//mipmap level
					  pixFormat,		//pixel format
					  pixType,			//type
					  data);			//data
	}
	this->unbind();

	return data;
}

};
//End namespace texture
};
//End namespace render


