//******************************************************************************
//BufferCapture.cpp*************************************************************
//******************************************************************************

#include "BufferCapture.h"


//Namespaces
using namespace render;
using namespace capture;


//*****************************************************************************
//Constructor/Destructor*******************************************************
//*****************************************************************************
BufferCapture::BufferCapture()
{
	//Generate frame buffer id
	glGenTransformFeedbacks(1, &transformFeedbackID);
}
//-----------------------------------------------------------------------------
BufferCapture::~BufferCapture()
{
	glDeleteTransformFeedbacks(1, &transformFeedbackID);
}
//*****************************************************************************
//Bind Buffer******************************************************************
//*****************************************************************************
void BufferCapture::bindBuffer( buffer::Buffer *buffer, GLuint index )
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackID);
	{
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, index, buffer->id());
	}
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}
//*****************************************************************************
//Begin/End********************************************************************
//*****************************************************************************
void BufferCapture::beginLines()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackID);
	glBeginTransformFeedback(GL_LINES);
}
//-----------------------------------------------------------------------------
void BufferCapture::beginPoints()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackID);
	glBeginTransformFeedback(GL_POINTS);
}
//-----------------------------------------------------------------------------
void BufferCapture::beginTriangles()
{
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, transformFeedbackID);
	glBeginTransformFeedback(GL_TRIANGLES);
}
//-----------------------------------------------------------------------------
void BufferCapture::end()
{
	glEndTransformFeedback();
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}
