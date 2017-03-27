//*****************************************************************************
//ShaderImage.hpp**************************************************************
//*****************************************************************************



//*****************************************************************************
//Set Uniform Textures*********************************************************
//*****************************************************************************
//template<class TexTarget, class TexType, class IntFormat, class PixFormat>
//void ShaderProgram::uniform_image(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, GLuint image_unit, GLint mipmap_level)
//{
////	glActiveTexture(GL_TEXTURE0 + active_texture);
////	tex->bind();
////	glUniform1i(locate_uniform(name), active_texture);
//
//	glBindImageTexture(image_unit, tex->id(), mipmap_level, GL_FALSE)
//
//}

//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniformImage(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, GLenum access)
{
	GLenum format = texture::traits<IntFormat>::internal_format;
	glBindImageTexture(imageUnit.val, tex->id(), 0, GL_TRUE, 0, access, format);
}
//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniformImage(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, MipLevel mipLevel, GLenum access)
{
	GLenum format = texture::traits<IntFormat>::internal_format;
	glBindImageTexture(imageUnit.val, tex->id(), mipLevel.val, GL_TRUE, 0, access, format);
}
//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniformImage(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, Layer layer, GLenum access)
{
	GLenum format = texture::traits<IntFormat>::internal_format;
	glBindImageTexture(imageUnit.val, tex->id(), 0, GL_FALSE, layer.val, access, format);
}



template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniformImageAtomicRGBA32F(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, GLenum access)
{
	GLenum format = texture::traits<IntFormat>::internal_format;
	glBindImageTexture(imageUnit.val, tex->id(), 0, GL_TRUE, 0, access, GL_R32F);
}



//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, Access access)
{
	GLenum format = texture::traits<IntFormat>::internal_format;
	glBindImageTexture(imageUnit.val, tex->id(), 0, GL_TRUE, 0, access.val, texture::traits<IntFormat>::internal_format);
}
//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, MipLevel mipLevel, Access access)
{
	GLenum format = texture::traits<IntFormat>::internal_format;
	glBindImageTexture(imageUnit.val, tex->id(), mipLevel.val, GL_TRUE, 0, access.val, format);
}
//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, Layer layer, Access access)
{
	GLenum format = texture::traits<IntFormat>::internal_format;
	glBindImageTexture(imageUnit.val, tex->id(), 0, GL_FALSE, layer.val, access.val, texture::traits<IntFormat>::internal_format);
}


//template<class TexTarget, class TexType, class IntFormat, class PixFormat>
//void uniformImageHandle(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, MipLevel mipLevel)
//{
//	if(!glIsImageHandleResidentARB(tex->imgHandles[mipLevel]))
//	{
//		glMakeImageHandleResidentARB(tex->imgHandles[mipLevel]);
//	}
//
//	glProgramUniformHandleui64NV(program_id, getUniformLoc(name), tex->imgHandles[mipLevel]);
//}