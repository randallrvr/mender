//*****************************************************************************
//ShaderTexture.hpp************************************************************
//*****************************************************************************



//*****************************************************************************
//Set Uniform Textures*********************************************************
//*****************************************************************************
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniformSampler(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex)
{
	glActiveTexture(GL_TEXTURE0 + activeTex.val);
	glBindTexture(texture::traits<TexTarget>::target, tex->id());

//	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_BASE_LEVEL,    0);
//	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_MAX_LEVEL,  1000);

	glProgramUniform1i(program_id, getUniformLoc(name), activeTex.val);
}
//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniformSampler(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex, MipLevel mipLevel)
{
	glActiveTexture(GL_TEXTURE0 + activeTex.val);
	glBindTexture(texture::traits<TexTarget>::target, tex->id());
	
	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_BASE_LEVEL, mipLevel.val);
	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_MAX_LEVEL,  mipLevel.val);
	
//	GLint uniformLoc = getUniformLoc(name);	if(uniformLoc == -1) return;
	glProgramUniform1i(program_id, getUniformLoc(name), activeTex.val);
}
//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniformSampler(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex, MipRange mipRange)
{
	glActiveTexture(GL_TEXTURE0 + activeTex.val);
	glBindTexture(texture::traits<TexTarget>::target, tex->id());

	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_BASE_LEVEL, mipRange.min);
	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_MAX_LEVEL,  mipRange.max);

	glProgramUniform1i(program_id, getUniformLoc(name), activeTex.val);
}



template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex)
{
	glActiveTexture(GL_TEXTURE0 + activeTex.val);
	glBindTexture(texture::traits<TexTarget>::target, tex->id());

	//	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_BASE_LEVEL,    0);
	//	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_MAX_LEVEL,  1000);

	glProgramUniform1i(program_id, getUniformLoc(name), activeTex.val);
}
//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex, MipLevel mipLevel)
{
	glActiveTexture(GL_TEXTURE0 + activeTex.val);
	glBindTexture(texture::traits<TexTarget>::target, tex->id());

	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_BASE_LEVEL, mipLevel.val);
	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_MAX_LEVEL,  mipLevel.val);

	//	GLint uniformLoc = getUniformLoc(name);	if(uniformLoc == -1) return;
	glProgramUniform1i(program_id, getUniformLoc(name), activeTex.val);
}
//-----------------------------------------------------------------------------
template<class TexTarget, class TexType, class IntFormat, class PixFormat>
void ShaderProgram::uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex, MipRange mipRange)
{
	glActiveTexture(GL_TEXTURE0 + activeTex.val);
	glBindTexture(texture::traits<TexTarget>::target, tex->id());

	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_BASE_LEVEL, mipRange.min);
	glTexParameteri(texture::traits<TexTarget>::target, GL_TEXTURE_MAX_LEVEL,  mipRange.max);

	glProgramUniform1i(program_id, getUniformLoc(name), activeTex.val);
}


//template<class TexTarget, class TexType, class IntFormat, class PixFormat>
//void uniformTextureHandle(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex)
