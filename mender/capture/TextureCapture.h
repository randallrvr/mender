//******************************************************************************
//TextureCapture.h**************************************************************
//******************************************************************************

#pragma once

//Render Library Includes
#include <render/texture.h>

//Standard Library includes
#include <vector>

//Namespaces
using namespace std;

namespace render  {
namespace capture {

// This is a FrameBuffer class but I use it as a mechanism to "capture" 
// textures, so that is what it is called

class TextureCapture
{
private:
	//FrameBuffer ID
	GLuint frameBufferID;
	
	//FrameBuffer Dimensions
	GLuint w, h;

	//FrameBuffer DrawBuffers
	vector<GLenum> drawBuffers;

	//Use in asserts
	bool checkDimensions(GLuint w, GLuint h);

public:

	//Constructor
	TextureCapture();
//	FrameBuffer(texture::tex2 *, RenderBuffer *);

	//Destructor
	~TextureCapture();

	//////////
	//Attach//
	//////////

	/////////////////////
	//Attach 2D texture//
	/////////////////////
	template<class TexType, class IntFormat, class PixFormat>
	void attach(texture::Texture2D<TexType, IntFormat, PixFormat> *texture);

	template<class TexType, class IntFormat, class PixFormat>
	void attachDepth(texture::Texture2D<TexType, IntFormat, PixFormat> *texture);

	template<class TexType, class IntFormat, class PixFormat>
	void attachDepthStencil(texture::Texture2D<TexType, IntFormat, PixFormat> *texture);

	//2D - Attach texture @ mipmap_level
	template<class TexType, class IntFormat, class PixFormat>
	void attach(texture::Texture2D<TexType, IntFormat, PixFormat> *texture, MipLevel mipLevel);

	//Array - Attach layer
	template<class TexType, class IntFormat, class PixFormat>
	void attach(texture::Texture2D_Array<TexType, IntFormat, PixFormat> *texture, Layer layer);

	/////////////////////////////////
	//Attach 2D Multisample texture//
	/////////////////////////////////
	template<class TexType, class IntFormat, class PixFormat>
	void attach(texture::Texture2D_Multi<TexType, IntFormat, PixFormat> *texture);

	template<class TexType, class IntFormat, class PixFormat>
	void attachDepth(texture::Texture2D_Multi<TexType, IntFormat, PixFormat> *texture);

	template<class TexType, class IntFormat, class PixFormat>
	void attachDepthStencil(texture::Texture2D_Multi<TexType, IntFormat, PixFormat> *texture);

	/////////////////////
	//Attach 3D texture//
	/////////////////////

	//3D - Attach ENTIRE 3D texture
	template<class TexType, class IntFormat, class PixFormat>
	void attach(texture::Texture3D<TexType, IntFormat, PixFormat> *texture);

	//3D - Attach texture @ mipmap level
	template<class TexType, class IntFormat, class PixFormat>
	void attach(texture::Texture3D<TexType, IntFormat, PixFormat> *texture, MipLevel mipLevel);

	//3D - Attach layer
	template<class TexType, class IntFormat, class PixFormat>
	void attach(texture::Texture3D<TexType, IntFormat, PixFormat> *texture, Layer layer);

	/////////////
	//Begin/End//
	////////////

	void begin();
	void end();

	//Clear the FrameBuffer
	void clear();

	//ID's
	const unsigned int id() const;

	//Error Checking
	static const bool error(const string & = "");

};
//End class FrameBuffer


//*****************************************************************************
// Attach 2D Texture **********************************************************
//*****************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attach(texture::Texture2D<TexType, IntFormat, PixFormat> *texture)
{
	assert(texture != NULL);
	assert(checkDimensions(texture->w, texture->h) && "ERROR: FrameBuffer and 2D texture size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		size_t index = drawBuffers.size();
		GLenum attachPoint = (GLenum)(GL_COLOR_ATTACHMENT0 + index);
		glFramebufferTexture2D(GL_FRAMEBUFFER,					//Target
							   attachPoint,						//Attachment point
							   GL_TEXTURE_2D,					//Texture target
							   texture->id(),					//Texture
							   0);								//Mipmap level
		drawBuffers.push_back(attachPoint);
		glDrawBuffers((GLsizei)drawBuffers.size(), &drawBuffers[0]);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
//-----------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attachDepth(texture::Texture2D<TexType, IntFormat, PixFormat> *depthTex)
{
	assert(depthTex != NULL);
	assert(checkDimensions(depthTex->w, depthTex->h) && "ERROR: FrameBuffer and depth texture size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER,					//Target
							   GL_DEPTH_ATTACHMENT,				//Attachment point
							   GL_TEXTURE_2D,					//Texture target
							   depthTex->id(), 					//Texture
							   0);								//Mipmap level
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//-----------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attachDepthStencil(texture::Texture2D<TexType, IntFormat, PixFormat> *depthStencilTex)
{
	assert(depthStencilTex != NULL);
	assert(checkDimensions(depthStencilTex->w, depthStencilTex->h) && "ERROR: FrameBuffer and depth/stencil texture size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER,					//Target
							   GL_DEPTH_STENCIL_ATTACHMENT,		//Attachment point
							   GL_TEXTURE_2D,					//Texture target
							   depthStencilTex->id(), 			//Texture
							   0);								//Mipmap level
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//-----------------------------------------------------------------------------
// Attach 2D texture @ mipmap_level -------------------------------------------
//-----------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attach(texture::Texture2D<TexType, IntFormat, PixFormat> *texture, MipLevel mipLevel)
{
	assert(texture != NULL);

	GLuint mipLevelW = texture->w >> mipLevel;
	GLuint mipLevelH = texture->h >> mipLevel;

	assert(checkDimensions(mipLevelW, mipLevelH) && "ERROR: FrameBuffer and 2D texture mipmap level size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		size_t index = drawBuffers.size();
		glFramebufferTexture2D(GL_FRAMEBUFFER,					//Target
							   GL_COLOR_ATTACHMENT0 + index,	//Attachment point
							   GL_TEXTURE_2D,					//Texture target
							   texture->id(),					//Texture
							   mipLevel.val);					//Mipmap level
		drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + index);
		glDrawBuffers(drawBuffers.size(), &drawBuffers[0]);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
//-----------------------------------------------------------------------------
// Attach layer of 2D Texture Array -------------------------------------------
//-----------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attach(texture::Texture2D_Array<TexType, IntFormat, PixFormat> *texture, Layer layer)
{
	assert(texture != NULL);
	assert(checkDimensions(texture->w, texture->h) && "ERROR: FrameBuffer and 2D texture array size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		size_t index = drawBuffers.size();
		glFramebufferTextureLayer(GL_FRAMEBUFFER,					//Target
								  GL_COLOR_ATTACHMENT0 + index,		//Attachment point
								  texture->id(),					//Texture
								  0,								//Mipmap level
								  layer.val);						//Array layer
		drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + index);
		glDrawBuffers(drawBuffers.size(), &drawBuffers[0]);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//*****************************************************************************
// Attach 2D Texture Multisample **********************************************
//*****************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attach(texture::Texture2D_Multi<TexType, IntFormat, PixFormat> *texture)
{
	assert(texture != NULL);
	assert(checkDimensions(texture->w, texture->h) && "ERROR: FrameBuffer and 2D texture size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		size_t index = drawBuffers.size();
		GLenum attachPoint = (GLenum)(GL_COLOR_ATTACHMENT0 + index);
		glFramebufferTexture2D(GL_FRAMEBUFFER,					//Target
							   attachPoint,						//Attachment point
							   GL_TEXTURE_2D_MULTISAMPLE,		//Texture target
							   texture->id(),					//Texture
							   0);								//Mipmap level
		drawBuffers.push_back(attachPoint);
		glDrawBuffers((GLsizei)drawBuffers.size(), &drawBuffers[0]);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
//-----------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attachDepth(texture::Texture2D_Multi<TexType, IntFormat, PixFormat> *depthTex)
{
	assert(depthTex != NULL);
	assert(checkDimensions(depthTex->w, depthTex->h) && "ERROR: FrameBuffer and depth texture size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER,					//Target
							   GL_DEPTH_ATTACHMENT,				//Attachment point
							   GL_TEXTURE_2D_MULTISAMPLE,					//Texture target
							   depthTex->id(), 					//Texture
							   0);								//Mipmap level
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//-----------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attachDepthStencil(texture::Texture2D_Multi<TexType, IntFormat, PixFormat> *depthStencilTex)
{
	assert(depthStencilTex != NULL);
	assert(checkDimensions(depthStencilTex->w, depthStencilTex->h) && "ERROR: FrameBuffer and depth/stencil texture size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER,					//Target
							   GL_DEPTH_STENCIL_ATTACHMENT,		//Attachment point
							   GL_TEXTURE_2D_MULTISAMPLE,		//Texture target
							   depthStencilTex->id(), 			//Texture
							   0);								//Mipmap level
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//*****************************************************************************
// Attach 3D Texture **********************************************************
//*****************************************************************************
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attach(texture::Texture3D<TexType, IntFormat, PixFormat> *texture)
{
	assert(texture != NULL);
	assert(checkDimensions(texture->w, texture->h) && "ERROR: FrameBuffer and 3D texture size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		size_t index = drawBuffers.size();
		//Generic (non-3D (which attaches the whole volume)) glFrameBufferTexture function
		glFramebufferTexture(GL_FRAMEBUFFER,					//Target
							 GL_COLOR_ATTACHMENT0 + index,		//Attachment point
							 texture->id(),						//Texture target
							 0);								//Mipmap level
		drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + index);
		glDrawBuffers(drawBuffers.size(), &drawBuffers[0]);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//-----------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attach(texture::Texture3D<TexType, IntFormat, PixFormat> *texture, MipLevel mipLevel)
{
	assert(texture != NULL);

	GLuint mipLevelW = texture->w >> mipLevel;
	GLuint mipLevelH = texture->h >> mipLevel;

	assert(checkDimensions(mipLevelW, mipLevelH) && "ERROR: FrameBuffer and 3D texture mipmap level size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		size_t index = drawBuffers.size();
		//Generic (non-3D (which attaches the whole volume)) glFrameBufferTexture function
		glFramebufferTexture(GL_FRAMEBUFFER,					//Target
							 GL_COLOR_ATTACHMENT0 + index,		//Attachment point
							 texture->id(),						//Texture
							 mipLevel.val);						//Mipmap level
		drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + index);
		glDrawBuffers(drawBuffers.size(), &drawBuffers[0]);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


//-----------------------------------------------------------------------------
template<class TexType, class IntFormat, class PixFormat>
void TextureCapture::attach(texture::Texture3D<TexType, IntFormat, PixFormat> *texture, Layer layer)
{
	assert(texture != NULL);
	assert(checkDimensions(texture->w, texture->h) && "ERROR: FrameBuffer and 3D texture (layer) size mismatch");

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		size_t index = drawBuffers.size();
		glFramebufferTexture3D(GL_FRAMEBUFFER,					//Target
							   GL_COLOR_ATTACHMENT0 + index,	//Attachment
							   GL_TEXTURE_3D,					//Texture Target
							   texture->id(),					//Texture ID
							   0,								//Mipmap level
							   layer.val);						//Texture Layer
		drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + index);
		glDrawBuffers(drawBuffers.size(), &drawBuffers[0]);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}; //End namespace buffers
}; //End namespace render


