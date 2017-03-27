//******************************************************************************
//TextureCapture.cpp************************************************************
//******************************************************************************

//Include Header
#include "TextureCapture.h"


//Standard Library includes
#include <iostream>


//Namespaces
using namespace render;
using namespace capture;


//*****************************************************************************
//Constructor******************************************************************
//*****************************************************************************
TextureCapture::TextureCapture()
{
	w = 0;
	h = 0;

	//Generate frame buffer id
	glGenFramebuffers(1, &frameBufferID);
}
//*****************************************************************************
//Destructor*******************************************************************
//*****************************************************************************
TextureCapture::~TextureCapture()
{
	glDeleteFramebuffers(1, &frameBufferID);
}
//*****************************************************************************
//Validate*********************************************************************
//*****************************************************************************
const bool TextureCapture::error(const string &note)
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	//Our FrameBuffer is perfect, return true
	if(status == GL_FRAMEBUFFER_COMPLETE)
	{
		cerr << note << ": NO ERROR with FrameBuffer" << endl;
		return(false);
	}

	switch(status)
	{
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:			cerr << note << ": GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << endl;	return(true);
		case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:			cerr << note << ": FrameBuffer has one or several image attachments with different internal formats" << endl;	return(true);
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:		cerr << note << ": FrameBuffer has one or several image attachments with different dimensions" << endl; return(true);
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:	cerr << note << ": FrameBuffer missing an image attachment" << endl; return(true);
		case GL_FRAMEBUFFER_UNSUPPORTED:					cerr << note << ": FrameBuffer format unsupported" << endl; return(true);
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:			cerr << note << ": GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << endl; return(true);
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:			cerr << note << ": GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << endl; return(true);
	}
	cerr << note << ": Unknown FrameBuffer error" << endl;
	return(true);
}
//*****************************************************************************
//Begin/End********************************************************************
//*****************************************************************************
void TextureCapture::begin()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
}
//-----------------------------------------------------------------------------
void TextureCapture::end()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//******************************************************************************
//Clear*************************************************************************
//******************************************************************************
void TextureCapture::clear()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//*****************************************************************************
//Interface Buffer ID**********************************************************
//*****************************************************************************
const unsigned int TextureCapture::id() const
{
	return frameBufferID;
}
//*****************************************************************************
//Check Dimensions*************************************************************
//*****************************************************************************
bool TextureCapture::checkDimensions(GLuint w_, GLuint h_)
{
	if(w == 0 && h == 0)	//w & h are unset (no attachments yet)
	{
		w = w_;
		h = h_;
		return true;
	}
	return (w == w_ && h == h_);
}
