//******************************************************************************
//BufferCapture.h***************************************************************
//******************************************************************************

#pragma once


//Standard Library includes
#include <vector>

//Project Includes
#include <render/buffer.h>

//Namespaces
using namespace std;

namespace render
{
namespace capture
{

// This is a TransformFeedback class but I use it as a mechanism to "capture" 
// buffers, so that is what it is called

class BufferCapture
{
private:
	//Interface Buffer ID
	GLuint transformFeedbackID;

public:
	//Constructor & Destructor
	 BufferCapture();
	~BufferCapture();

	//Bind Buffer (other buffers)
	void bindBuffer(buffer::Buffer *buffer, GLuint index);

//	//Output calls glTransformFeedbackVaryings								// Nevermind, these go in the shader code
//	void setOutput(const string &outName);									// Nevermind, these go in the shader code
//	void setOutputsSeparate(const vector<const string &> &outNames);		// Nevermind, these go in the shader code
//	void setOutputsInterleaved(const vector<const string &> &outNames);		// Nevermind, these go in the shader code

	//Begin/End
	void beginLines();
	void beginPoints();
	void beginTriangles();
	void end();

	GLuint id()		{ return transformFeedbackID; }
};
//End class TransformFeedback

//#include "FrameBuffer.hpp"

};
//End namespace buffers
};
//End namespace render


