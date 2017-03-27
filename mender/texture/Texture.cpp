//******************************************************************************
//render/texture/Texture.cpp****************************************************
//******************************************************************************

//Header Include
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Namespaces
using namespace render;
using namespace texture;

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
Texture::Texture()
{
	glGenTextures(1, &tex_id);
//	textureHandle = glGetTextureHandleARB(tex_id);
}
//-----------------------------------------------------------------------------
Texture::Texture(const string &filename)
{
	string ignoreWarning = filename;
	glGenTextures(1, &tex_id);
}
//******************************************************************************
//Destructors*******************************************************************
//******************************************************************************
Texture::~Texture()
{
	glDeleteTextures(1, &tex_id);
}
