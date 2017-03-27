//*****************************************************************************
//render/render/gl.h***********************************************************
//*****************************************************************************

#pragma once

//GLEW Library Include
#include "../gl/glew.h"

namespace render
{
	//Put in Textures namespace?
	struct TexUnit  { GLuint val;   TexUnit(GLuint val_) : val(val_) {} };	//short for TEXTURE_IMAGE_UNIT
	struct ImageUnit{ GLuint val; ImageUnit(GLuint val_) : val(val_) {} };
	struct MipLevel { GLuint val;  MipLevel(GLuint val_) : val(val_) {} };
	struct Layer    { GLuint val;     Layer(GLuint val_) : val(val_) {} };

	struct MipRange { GLuint min,max; MipRange(GLuint min_,GLuint max_) { min = min_; max = max_; } };


	struct Access { GLenum val; Access() : val(GL_READ_WRITE) {}; Access(GLenum val_) : val(val_) {}; };
	struct AccessReadWrite : public Access { AccessReadWrite() : Access(GL_READ_WRITE) {} };
	struct AccessReadOnly  : public Access { AccessReadOnly()  : Access(GL_READ_ONLY)  {} };
	struct AccessWriteOnly : public Access { AccessWriteOnly() : Access(GL_WRITE_ONLY) {} };


	//Put in buffers namespace?
	struct Usage { GLenum val; Usage() : val(GL_STATIC_DRAW) {}; Usage(GLenum val_) : val(val_) {}; };
	struct UsageStreamDraw  : public Usage { UsageStreamDraw()  : Usage(GL_STREAM_DRAW)  {} };
	struct UsageStreamRead  : public Usage { UsageStreamRead()  : Usage(GL_STREAM_READ)  {} };
	struct UsageStreamCopy  : public Usage { UsageStreamCopy()  : Usage(GL_STREAM_COPY)  {} };
	struct UsageStaticDraw  : public Usage { UsageStaticDraw()  : Usage(GL_STATIC_DRAW)  {} };
	struct UsageStaticRead  : public Usage { UsageStaticRead()  : Usage(GL_STATIC_READ)  {} };
	struct UsageStaticCopy  : public Usage { UsageStaticCopy()  : Usage(GL_STATIC_COPY)  {} };
	struct UsageDynamicDraw : public Usage { UsageDynamicDraw() : Usage(GL_DYNAMIC_DRAW) {} };
	struct UsageDynamicRead : public Usage { UsageDynamicRead() : Usage(GL_DYNAMIC_READ) {} };
	struct UsageDynamicCopy : public Usage { UsageDynamicCopy() : Usage(GL_DYNAMIC_COPY) {} };

	struct BindingPoint{ GLuint val; BindingPoint(GLuint val_) : val(val_) {} };

};


#include "../gl/Camera.h"

