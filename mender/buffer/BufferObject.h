//******************************************************************************
//render/buffer/BufferObject.h**************************************************
//******************************************************************************

#pragma once

//Standard Library Includes
#include <iostream>
#include <string>
#include <map>


//Render includes
#include <render/texture.h>

//Project Includes
#include "Buffer.h"


//Namespaces
using namespace std;

namespace render
{
namespace buffer
{

class BufferObject	//Wraps a Vertex Array Object with a different (less stupid?) name, probably about as stupid...
{
public:

	//Vertex Array Object ID
	GLuint id;

protected:
	map<GLuint, Buffer *> per_element_buffers;		//I guess you could say per vert
	map<GLuint, Buffer *> per_instance_buffers;

	Buffer *element_buffer;

	//Variables to keep track of attribute & uniform binding/attachment points
	GLuint attribute_loc;
	GLuint   uniform_loc;
	GLuint   texture_loc;	//texture index

	GLuint num_elements;
	GLuint num_instances;

public:

	//Constructors
	BufferObject()
	{
		glGenVertexArrays(1, &id);
		attribute_loc = 0;
		uniform_loc   = 0;
		texture_loc   = 0;

		num_elements  = 0;
		num_instances = 0;

		element_buffer = NULL;
	}

	//Destructor
	~BufferObject()
	{
		glDeleteVertexArrays(1, &id);
	}

	//Bind/Unbind
	       void   bind()	{	glBindVertexArray(id);	}
	static void unbind()	{	glBindVertexArray(0);	}

	template<class BufType>
	void addBuffer(ArrayBufferT<BufType> *array_buffer)
	{
		this->bind();
		{
		//	BufType *bufType;	//just for the overload
			array_buffer->bind();
			array_buffer->attribPointer(attribute_loc);
			glEnableVertexAttribArray(  attribute_loc);
			array_buffer->unbind();
		}
		this->unbind();
		per_element_buffers[attribute_loc] = array_buffer;
		attribute_loc++;
	}

	template<class BufType>
	void addBufferStride(ArrayBufferT<BufType> *array_buffer, GLuint stride)
	{
		this->bind();
		{
			BufType *bufType;	//just for the overload
			array_buffer->bind();
			array_buffer->attribPointer(attribute_loc, stride, bufType);
			glEnableVertexAttribArray(  attribute_loc);
			array_buffer->unbind();
		}
		this->unbind();
		per_element_buffers[attribute_loc] = array_buffer;
		attribute_loc++;
	}


	template<class BufType>
	void addBuffer(ArrayBufferT<BufType> *array_buffer, int location)
	{
		this->bind();
		{
			array_buffer->bind();
			array_buffer->attribPointer(location);
			glEnableVertexAttribArray(  location);
			array_buffer->unbind();
		}
		this->unbind();
	}

	template<class BufType>
	void addBuffer(ElementBufferT<BufType> *element_buffer)
	{
		this->bind();
		{
			element_buffer->bind();
		}
		this->unbind();
		this->element_buffer = element_buffer;
		this->num_elements   = element_buffer->numElements();
	}

	template<class BufType>
	void addBuffer(UniformBufferT<BufType> *uniform_buffer)
	{
		this->bind();
		{
			uniform_buffer->bindBase(uniform_loc);
		}
		this->unbind();
		uniform_loc++;
	}

	template<class BufType>
	void addBuffer(UniformBufferT<BufType> *uniform_buffer, int location)
	{
		this->bind();
		{
			uniform_buffer->bindBase(location);
		}
		this->unbind();
	}

	void addTexture(texture::Texture *texture)
	{
		this->bind();
		{
			texture->bind();
		}
		this->unbind();
	//	texture_loc++;
	}

//	template<class BufType>
//	void addInstanceBuffer(ArrayBufferT<BufType> *array_buffer)	
//	{										
	void addInstanceBuffer(Buffer *buffer)	//Not sure if its appropriated for an
	{										//instanced buffer to be anything other
											//than an ArrayBuffer (GL_ARRAY_BUFFER)
		this->bind();
		{

			buffer->bind();
			buffer->attribPointer(    attribute_loc);
			glEnableVertexAttribArray(attribute_loc);
			glVertexAttribDivisor(    attribute_loc, 1);
		}
		this->unbind();
		per_instance_buffers[attribute_loc] = buffer;
		num_instances = buffer->numElements();
		attribute_loc++;
	}

	void addInstanceBuffer(Buffer &buffer)	//Not sure if its appropriated for an
	{										//instanced buffer to be anything other
											//than an ArrayBuffer (GL_ARRAY_BUFFER)
		this->bind();
		{

			buffer.bind();
			buffer.attribPointer(    attribute_loc);
			glEnableVertexAttribArray(attribute_loc);
			glVertexAttribDivisor(    attribute_loc, 1);
		}
		this->unbind();
		per_instance_buffers[attribute_loc] = &buffer;
		num_instances = buffer.numElements();
		attribute_loc++;
	}


	inline void renderArrays(GLenum mode)
	{
		this->bind();
		{
			glDrawArrays(mode, 0, num_elements);
		}
		this->unbind();
	}

	inline void renderArrays(GLenum mode, GLint first, GLsizei count)
	{
		this->bind();
		{
			glDrawArrays(mode, first, count);
		}
		this->unbind();
	}


	inline void renderFeedback(GLenum mode, GLuint feedback_id)
	{
		this->bind();
		{
			glDrawTransformFeedback(mode, feedback_id);
		}
		this->unbind();
	}

	inline void renderFeedbackTriangles(GLuint feedback_id)		{	renderFeedback(GL_TRIANGLES, feedback_id);		}
	inline void renderFeedbackPoints(GLuint feedback_id)		{	renderFeedback(GL_POINTS,    feedback_id);		}

	inline void renderFeedbackStream(GLenum mode, GLuint feedback_id, GLuint stream)
	{
		this->bind();
		{
			glDrawTransformFeedbackStream(mode, feedback_id, stream);
		}
		this->unbind();
	}

	template<class BufType>
	void render(GLenum mode, ElementBufferT<BufType> *new_element_buffer)	//Render with a specific element buffer
	{
		this->bind();
		{
			new_element_buffer->bind();
			glDrawElements(mode, new_element_buffer->numElements(), traits<BufType>::type, 0);
			element_buffer->bind();
		}
		this->unbind();
	}

	template<class BufType>
	void render(GLenum mode, ElementBufferT<BufType> *new_element_buffer, GLsizei count)	//Render with a specific element buffer
	{
		this->bind();
		{
			new_element_buffer->bind();
			glDrawElements(mode, count, traits<BufType>::type, 0);
			element_buffer->bind();
		}
		this->unbind();
	}

	inline void renderElements(GLenum mode)
	{
		assert(element_buffer && "Element Buffer not defined");
		this->bind();
		{
//			element_buffer->bind();
			glDrawElements(mode, element_buffer->numElements(), element_buffer->getType(), 0);
		}
		this->unbind();
	}

	inline void renderElementsUnclosed(GLenum mode) //i.e. not unbound
	{
		assert(element_buffer && "Element Buffer not defined");
		this->bind();
		{
			glDrawElements(mode, element_buffer->numElements(), element_buffer->getType(), 0);
		}
	//	this->unbind();
	}

	inline void renderArraysIndirect(GLenum mode)			//Assume an IndirectBuffer is bound
	{
	//	assert(element_buffer && "Element Buffer not defined");
		glBindVertexArray(id);
		{
			glDrawArraysIndirect(mode, 0);
		}
		this->unbind();
	}

	inline void renderArraysInstanced(GLenum mode, GLint first, GLsizei numIndices, GLsizei numInstances)
	{
		this->bind();
		{
			glDrawArraysInstanced(mode, first, numIndices, numInstances);
		}
		this->unbind();
	}

	
	inline void renderElementsIndirect(GLenum mode)			//Assume an IndirectBuffer is bound
	{
		assert(element_buffer && "Element Buffer not defined");
		this->bind();
		{
			glDrawElementsIndirect(mode, element_buffer->getType(), 0);
		}
		this->unbind();
	}

	template<class BufType>
	inline void renderElementsIndirect(GLenum mode, ElementBufferT<BufType> *new_element_buffer)	//Render with a specific element buffer
	{
		assert(new_element_buffer && "New Element Buffer not defined");
		this->bind();
		{
			new_element_buffer->bind();
			glDrawElementsIndirect(mode, new_element_buffer->getType(), 0);
			if(element_buffer)				//if there was a element_buffer previously
				element_buffer->bind();		//rebind it
		}
		this->unbind();
	}

	inline void renderElementsIndirectUnclosed(GLenum mode)			//Assume an IndirectBuffer is bound 
	{
		assert(element_buffer && "Element Buffer not defined");
		this->bind();
		{
			glDrawElementsIndirect(mode, element_buffer->getType(), 0);
		}
	//	this->unbind();
	}

	void renderIndirect(GLenum mode, IndirectElementBuffer *indirect_element_buffer)
	{
		this->bind();
		{
			indirect_element_buffer->bind();
			glDrawElementsIndirect(mode, element_buffer->getType(), 0);
			indirect_element_buffer->unbind();
		}
		this->unbind();
	}

	void renderIndirect(GLenum mode, IndirectArrayBuffer *indirect_array_buffer)
	{
		this->bind();
		{
			indirect_array_buffer->bind();
			glDrawElementsIndirect(mode, element_buffer->getType(), 0);
			indirect_array_buffer->unbind();
		}
		this->unbind();
	}

	template<class BufType>
	void renderIndirect(GLenum mode, IndirectElementBuffer *indirect_element_buffer, ElementBufferT<BufType> *new_element_buffer)		//Render with a specific element buffer
	{
		this->bind();
		{
			indirect_element_buffer->bind();
			new_element_buffer->bind();
			glDrawElementsIndirect(mode, traits<BufType>::type, 0);
			element_buffer->bind();
			indirect_element_buffer->unbind();
		}
		this->unbind();
	}


	template<class BufType>
	void renderIndirect(GLenum mode, ElementBufferT<BufType> *new_element_buffer)		//Assume indirect buffer already bound
	{																					//Render with a specific element buffer
		this->bind();
		{
			new_element_buffer->bind();
			glDrawElementsIndirect(mode, traits<BufType>::type, 0);
			element_buffer->bind();
		}
		this->unbind();
	}

	inline void renderElementsRange(GLenum mode, GLuint start, GLuint end)
	{
		assert(element_buffer && "Element Buffer not defined");

		GLsizei count = end - start + 1;
		this->bind();
		{
			glDrawRangeElements(mode, start, end, count, element_buffer->getType(), 0);
		}
		this->unbind();
	}

	inline void renderElementsInstanced(GLenum mode)
	{
		assert(element_buffer && "Element Buffer not defined");
		this->bind();
		{
			glDrawElementsInstanced(mode, element_buffer->numElements(), element_buffer->getType(), 0, num_instances);
		}
		this->unbind();
	}

	inline void renderElementsInstanced(GLenum mode, GLsizei num_instances)
	{
		assert(element_buffer                                && "Element Buffer not defined"                );
		assert((GLuint)num_instances <= this->num_instances && "Too many instances for instanced rendering");
		this->bind();
		{
			glDrawElementsInstanced(mode, element_buffer->numElements(), element_buffer->getType(), 0, num_instances);
		}
		this->unbind();
	}

	inline void renderElementsInstancedUnsafe(GLenum mode, GLsizei num_instances)
	{
		assert(element_buffer && "Element Buffer not defined");
		this->bind();
		{
			element_buffer->bind();
			glDrawElementsInstanced(mode, element_buffer->numElements(), element_buffer->getType(), 0, num_instances);
		}
		this->unbind();
	}

	inline void renderElementsTriangles()				{	renderElements(GL_TRIANGLES);				}
    inline void renderElementsPatches()				    {	renderElements(GL_PATCHES);				}
	inline void renderElementsPoints()					{	renderElements(GL_POINTS);					}

	inline void renderElementsTrianglesUnclosed()		{	renderElementsUnclosed(GL_TRIANGLES);		}
    inline void renderElementsPatchesUnclosed()		    {	renderElementsUnclosed(GL_PATCHES);		}
	inline void renderElementsPointsUnclosed()			{	renderElementsUnclosed(GL_POINTS);			}

	void renderElementsTrianglesRange(GLuint start_tri, GLuint end_tri)
	{
		assert(element_buffer && "Element Buffer not defined");

		GLuint start_index = start_tri*3;
		GLuint   end_index =   end_tri*3+2;
		GLuint      offset = start_index * element_buffer->getSize();
		GLsizei      count = end_index - start_index + 1;

		this->bind();
		{
			glDrawRangeElements(GL_TRIANGLES, start_index, end_index, count, element_buffer->getType(), (GLvoid *)offset);
		}
		this->unbind();
	}
	inline void renderElementsPointsRange(GLuint start, GLuint end)				{	renderElementsRange(GL_POINTS,    start, end);		}

	inline void renderElementsTrianglesInstanced()								{	renderElementsInstanced(GL_TRIANGLES);		}
	inline void renderElementsPointsInstanced()									{	renderElementsInstanced(GL_POINTS);			}

	inline void renderElementsTrianglesInstanced(GLsizei num_instances)			{	renderElementsInstanced(GL_TRIANGLES, num_instances);	}
	inline void renderElementsPointsInstanced(GLsizei num_instances)			{	renderElementsInstanced(GL_POINTS,    num_instances);	}

	inline void renderElementsTrianglesInstancedUnsafe(GLsizei num_instances)	{	renderElementsInstancedUnsafe(GL_TRIANGLES, num_instances);	}
	inline void renderElementsPointsInstancedUnsafe(GLsizei num_instances)		{	renderElementsInstancedUnsafe(GL_POINTS,    num_instances);	}
};

//BufferState::BufferState()
//{
//
//}


//End class BufferState
};
//End namespace buffers
};
//End namespace render



