//******************************************************************************
//render/buffer/Buffer.hpp******************************************************
//******************************************************************************

//Render Library Includes
#include <render/gl.h>

//******************************************************************************
//Constructor*******************************************************************
//******************************************************************************
template<class BufTarget, class BufType>
BufferT<BufTarget, BufType>::BufferT(Usage usage) : Buffer(0)
{
	this->setData(0, NULL, usage.val);
}
//------------------------------------------------------------------------------
template<class BufTarget, class BufType>
BufferT<BufTarget, BufType>::BufferT(int num_elements, Usage usage) : Buffer(num_elements)
{
	this->setData(num_elements, NULL, usage.val);
}
//------------------------------------------------------------------------------
template<class BufTarget, class BufType>
BufferT<BufTarget, BufType>::BufferT(int num_elements, BufType *data, Usage usage) : Buffer(num_elements)
{
	this->setData(num_elements, data, usage.val);
}
//******************************************************************************
//Destructor********************************************************************
//******************************************************************************
template<class BufTarget, class BufType>
BufferT<BufTarget, BufType>::~BufferT()
{
	glDeleteBuffers(1, &buffer_id);
}
//******************************************************************************
//Bind/Unbind*******************************************************************
//******************************************************************************
template<class BufTarget, class BufType>
void BufferT<BufTarget, BufType>::bind()
{
	glBindBuffer(traits<BufTarget>::target, buffer_id);
}
//-----------------------------------------------------------------------------
template<class BufTarget, class BufType>
void BufferT<BufTarget, BufType>::bindBase( GLuint index )
{
	glBindBufferBase(traits<BufTarget>::target, index, buffer_id);
}
//-----------------------------------------------------------------------------
template<class BufTarget, class BufType>
void BufferT<BufTarget, BufType>::bindRange( GLuint index, int start_index, int end_index)
{
	glBindBufferRange(traits<BufTarget>::target, index, buffer_id, start_index * sizeof(BufType), end_index * sizeof(BufType));
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
template<class BufTarget, class BufType>
void BufferT<BufTarget, BufType>::unbind()
{
	glBindBuffer(traits<BufTarget>::target, 0);
}
//******************************************************************************
//Map/Unmap*********************************************************************
//******************************************************************************
template<class BufTarget, class BufType>
BufType *BufferT<BufTarget, BufType>::map(GLenum access)
{
	this->bind();
	
	BufType *bufferData = (BufType *)glMapBuffer(traits<BufTarget>::target, access);

	return bufferData;
}
//-----------------------------------------------------------------------------
template<class BufTarget, class BufType>
void BufferT<BufTarget, BufType>::unmap()
{
	this->bind();

	glUnmapBuffer(traits<BufTarget>::target);

//	this->unbind();
}
//******************************************************************************
//Buffer Data*******************************************************************
//******************************************************************************
template<class BufTarget, class BufType>
void BufferT<BufTarget, BufType>::setData(int num_elements, const BufType *data, Usage usage)
{
	this->num_elements = num_elements;
	this->bind();
	{
		glBufferData(traits<BufTarget>::target, sizeof(BufType) * num_elements, data, usage.val);
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class BufTarget, class BufType>
void BufferT<BufTarget, BufType>::setElement(int index, const BufType *data)
{
	this->bind();
	{
		glBufferSubData(traits<BufTarget>::target, sizeof(BufType) * index, sizeof(BufType), data);
	}
	this->unbind();
}
//------------------------------------------------------------------------------
template<class BufTarget, class BufType>
BufType *BufferT<BufTarget, BufType>::getData()
{
	BufType *data = new BufType[num_elements];
	this->bind();
	{
		glGetBufferSubData(traits<BufTarget>::target, 0, sizeof(BufType)*num_elements, data);
	}
	this->unbind();

	return data;
}
//------------------------------------------------------------------------------
template<class BufTarget, class BufType>
BufType *BufferT<BufTarget, BufType>::getSubData(int start_index, int end_index)
{
	int range = end_index - start_index + 1;
	BufType *data = new BufType[range];
	this->bind();
	{
		glGetBufferSubData(traits<BufTarget>::target, sizeof(BufType)*start_index, sizeof(BufType)*range, data);
	}
	this->unbind();

	return data;
}
//******************************************************************************
//Set Attribute*****************************************************************
//******************************************************************************
template<class BufTarget, class BufType>
void BufferT<BufTarget, BufType>::attribPointer(GLuint index, GLsizei stride)
{
	GLenum bufType = traits<BufType>::type;

	//The necessity of this if statement pains me greatly
	if(bufType == GL_BYTE || bufType == GL_UNSIGNED_BYTE || bufType == GL_SHORT || bufType == GL_UNSIGNED_SHORT || bufType == GL_INT || bufType == GL_UNSIGNED_INT)
	{
		glVertexAttribIPointer(index, traits<BufType>::components, traits<BufType>::type, stride, 0);
	}
	else if(bufType == GL_DOUBLE)
	{
		glVertexAttribLPointer(index, traits<BufType>::components, traits<BufType>::type, stride, 0);
	}
	else
	{
		glVertexAttribPointer(index, traits<BufType>::components, traits<BufType>::type, GL_FALSE, stride, 0);
	}

}
