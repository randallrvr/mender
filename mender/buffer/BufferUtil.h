//*****************************************************************************
//BufferUtil.h*****************************************************************
//*****************************************************************************

#pragma once

#include <string>
#include <functional>

using namespace render;
using namespace buffer;

//-----------------------------------------------------------------------------
// Index Buffer (with texture proxy) ------------------------------------------
//-----------------------------------------------------------------------------
class IndexBufferTex : public ElementBufferT<GLuint>
{
private:
	GLuint proxyTex;

	void createProxyTex()
	{
		// Create the texture proxy
		glGenTextures(1, &proxyTex);
		glBindTexture(GL_TEXTURE_BUFFER, proxyTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffer_id);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

public:
	//Constructors
	IndexBufferTex()                               : ElementBufferT<GLuint>()						{ createProxyTex(); }
	IndexBufferTex(int num_elements)               : ElementBufferT<GLuint>(num_elements)			{ createProxyTex(); }
	IndexBufferTex(int num_elements, GLuint *data) : ElementBufferT<GLuint>(num_elements, data)		{ createProxyTex(); }

	//Destructor
	~IndexBufferTex()	{	glDeleteTextures(1, &proxyTex);		}

	//Get proxy texture id;
	GLuint texID()	{	return proxyTex;	}
};



//-----------------------------------------------------------------------------
// Indirect Array Buffer (with texture proxy) ---------------------------------
//-----------------------------------------------------------------------------
class IndirectArrayBufferTex : public IndirectArrayBuffer
{
private:
	GLuint proxyTex;

	void createProxyTex()
	{
		// Create the texture proxy
		glGenTextures(1, &proxyTex);
		glBindTexture(GL_TEXTURE_BUFFER, proxyTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffer_id);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

public:
	//Constructors
	IndirectArrayBufferTex(Usage usage = GL_STATIC_DRAW)                                                       : IndirectArrayBuffer(usage)							{ createProxyTex(); }
	IndirectArrayBufferTex(int num_elements, Usage usage = GL_STATIC_DRAW)                                     : IndirectArrayBuffer(num_elements, usage)			{ createProxyTex(); }
	IndirectArrayBufferTex(int num_elements, DrawArraysIndirectCommand *command, Usage usage = GL_STATIC_DRAW) : IndirectArrayBuffer(num_elements, command, usage)	{ createProxyTex(); }

	//Destructor
	~IndirectArrayBufferTex()	{	glDeleteTextures(1, &proxyTex);		}

	//Get proxy texture id;
	GLuint texID()	{	return proxyTex;	}
};


//-----------------------------------------------------------------------------
// Indirect Element Buffer (with texture proxy) -------------------------------
//-----------------------------------------------------------------------------
class IndirectElementBufferTex : public IndirectElementBuffer
{
private:
	GLuint proxyTex;

	void createProxyTex()
	{
		// Create the texture proxy
		glGenTextures(1, &proxyTex);
		glBindTexture(GL_TEXTURE_BUFFER, proxyTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffer_id);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

public:
	//Constructors
	IndirectElementBufferTex(Usage usage = GL_STATIC_DRAW)                                                         : IndirectElementBuffer(usage)							{ createProxyTex(); }
	IndirectElementBufferTex(int num_elements, Usage usage = GL_STATIC_DRAW)                                       : IndirectElementBuffer(num_elements, usage)				{ createProxyTex(); }
	IndirectElementBufferTex(int num_elements, DrawElementsIndirectCommand *command, Usage usage = GL_STATIC_DRAW) : IndirectElementBuffer(num_elements, command, usage)	{ createProxyTex(); }

	//Destructor
	~IndirectElementBufferTex()	{	glDeleteTextures(1, &proxyTex);		}

	//Get proxy texture id;
	GLuint texID()	{	return proxyTex;	}
};


//-----------------------------------------------------------------------------
// Voxel Position Buffer (with texture proxy) ---------------------------------
//-----------------------------------------------------------------------------
#if 1
class VoxelPosBufferTex : public ArrayBufferT<vec3ui>
{
private:
	GLuint   proxyTex;
public:
	GLuint64 texHandle;
	GLuint64 imgHandle;
private:

	void createProxyTex()
	{
		// Create the texture proxy
		glGenTextures(1, &proxyTex);
		glBindTexture(GL_TEXTURE_BUFFER, proxyTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffer_id);
		glBindTexture(GL_TEXTURE_BUFFER, 0);

//		if(glewIsSupported("GL_ARB_bindless_texture"))
//		{
//			texHandle = glGetTextureHandleARB(proxyTex);
//			glMakeTextureHandleResidentARB(texHandle);
//
//			imgHandle = glGetImageHandleARB(proxyTex, 0, GL_TRUE, 0, GL_R32UI);
//			glMakeImageHandleResidentARB(imgHandle, GL_READ_WRITE);
//		}
	}

public:
	//Constructors
	VoxelPosBufferTex(Usage usage = GL_STATIC_DRAW)                                 : ArrayBufferT<vec3ui>(usage)						{ createProxyTex(); }
	VoxelPosBufferTex(int num_elements, Usage usage = GL_STATIC_DRAW)               : ArrayBufferT<vec3ui>(num_elements, usage)			{ createProxyTex(); }
	VoxelPosBufferTex(int num_elements, vec3ui *data, Usage usage = GL_STATIC_DRAW) : ArrayBufferT<vec3ui>(num_elements, data, usage)	{ createProxyTex(); }

	//Destructor
	~VoxelPosBufferTex()	{	glDeleteTextures(1, &proxyTex);		}

	//Get proxy texture id;
	GLuint texID()	{	return proxyTex;	}
};
#else
class VoxelPosBufferTex : public ArrayBufferT<GLuint>
{
private:
	GLuint proxyTex;

	void createProxyTex()
	{
		// Create the texture proxy
		glGenTextures(1, &proxyTex);
		glBindTexture(GL_TEXTURE_BUFFER, proxyTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffer_id);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

public:
	//Constructors
	VoxelPosBufferTex(Usage usage = GL_STATIC_DRAW)                                 : ArrayBufferT<GLuint>(usage)						{ createProxyTex(); }
	VoxelPosBufferTex(int num_elements, Usage usage = GL_STATIC_DRAW)               : ArrayBufferT<GLuint>(num_elements, usage)			{ createProxyTex(); }
	VoxelPosBufferTex(int num_elements, GLuint *data, Usage usage = GL_STATIC_DRAW) : ArrayBufferT<GLuint>(num_elements, data, usage)	{ createProxyTex(); }

	//Destructor
	~VoxelPosBufferTex()	{	glDeleteTextures(1, &proxyTex);		}

	//Get proxy texture id;
	GLuint texID()	{	return proxyTex;	}
};
#endif

//-----------------------------------------------------------------------------
// Position Buffer (with texture proxy) ---------------------------------------
//-----------------------------------------------------------------------------
class PositionBufferTex : public ArrayBufferT<vec3ui>
{
private:
	GLuint proxyTex;

	void createProxyTex()
	{
		// Create the texture proxy
		glGenTextures(1, &proxyTex);
		glBindTexture(GL_TEXTURE_BUFFER, proxyTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffer_id);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

public:
	//Constructors
	PositionBufferTex()                               : ArrayBufferT<vec3ui>()							{ createProxyTex(); }
	PositionBufferTex(int num_elements)               : ArrayBufferT<vec3ui>(num_elements)				{ createProxyTex(); }
	PositionBufferTex(int num_elements, vec3ui *data) : ArrayBufferT<vec3ui>(num_elements, data)		{ createProxyTex(); }

	//Destructor
	~PositionBufferTex()	{	glDeleteTextures(1, &proxyTex);		}

	//Get proxy texture id;
	GLuint texID()	{	return proxyTex;	}
};


//-----------------------------------------------------------------------------
// Color Buffer (with texture proxy) ------------------------------------------
//-----------------------------------------------------------------------------
class ColorBufferTex : public ArrayBufferT<vec3f>
{
private:
	GLuint proxyTex;

	void createProxyTex()
	{
		// Create the texture proxy
		glGenTextures(1, &proxyTex);
		glBindTexture(GL_TEXTURE_BUFFER, proxyTex);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, buffer_id);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

public:
	//Constructors
	ColorBufferTex()                              : ArrayBufferT<vec3f>()						{ createProxyTex(); }
	ColorBufferTex(int num_elements)              : ArrayBufferT<vec3f>(num_elements)			{ createProxyTex(); }
	ColorBufferTex(int num_elements, vec3f *data) : ArrayBufferT<vec3f>(num_elements, data)		{ createProxyTex(); }

	//Destructor
	~ColorBufferTex()	{	glDeleteTextures(1, &proxyTex);		}

	//Get proxy texture id;
	GLuint texID()	{	return proxyTex;	}
};

