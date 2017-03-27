//******************************************************************************
//render/buffer/Buffer.h********************************************************
//******************************************************************************

#pragma once

//Standard Library Includes
#include <iostream>
#include <string>

//Render Includes
#include <render/gl.h>

//Namespaces
using namespace std;

namespace render
{
namespace buffer
{

struct Stride {	int stride;	Stride(int stride_) : stride(stride_) {} };

//Inline Include of Buffer Trait definitions //VERY IMPORTANT DO NOT MOVE
#include "BufferTraits.hpp"                  //VERY IMPORTANT DO NOT MOVE
//Inline Include of Buffer Trait definitions //VERY IMPORTANT DO NOT MOVE

//******************************************************************************
//Buffer base class*************************************************************
//******************************************************************************
class Buffer	//Generic parent class
{
protected:
	//ID
	GLuint buffer_id;

	int num_elements;

public:

	Buffer(int num_elements)
	{
		glGenBuffers(1, &buffer_id);
		this->num_elements = num_elements;
	}

	virtual ~Buffer()
	{
		glDeleteBuffers(1, &buffer_id);
	}

	virtual void   bind()                      = 0;
	virtual void   bindBase(GLuint)            = 0;
	virtual void   bindRange(GLuint, int, int) = 0;
	virtual void unbind()                      = 0;

	virtual GLenum getType()       = 0;
	virtual GLuint getSize()       = 0;
	virtual GLenum getTarget()     = 0;
	virtual GLuint getComponents() = 0;

	//Generic Attribute Pointer
	virtual void attribPointer(GLuint index, GLsizei stride=0) = 0;

//	//Integer Attribute Pointer overloads
//	virtual void attribPointer(GLuint index, GLsizei stride=0, GLint    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec2i    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec3i    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec4i    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, GLuint   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec2ui   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec3ui   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec4ui   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, GLshort  *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec2s    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec3s    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec4s    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, GLushort *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec2us   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec3us   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec4us   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, GLchar   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec2b    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec3b    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec4b    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, GLubyte  *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec2ub   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec3ub   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec4ub   *dataType=NULL) = 0;
//
//	//Double Attribute Pointer overloads
//	virtual void attribPointer(GLuint index, GLsizei stride=0, double   *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec2d    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec3d    *dataType=NULL) = 0;
//	virtual void attribPointer(GLuint index, GLsizei stride=0, vec4d    *dataType=NULL) = 0;

	int numElements()	{ return num_elements; }

	GLuint id()			{ return buffer_id; }

};

//******************************************************************************
//Buffer generic templated class************************************************
//******************************************************************************
template<class BufTarget, class BufType>
class BufferT : public Buffer
{
public:
	//Bind/Unbind
	void   bind();
	void   bindBase(GLuint index);
	void   bindRange(GLuint index, int start_index, int end_index);
	void unbind();

	//Safe Map/Unmap
	BufType *map(GLenum access = GL_READ_WRITE);
	BufType *mapRead()			{ return map(GL_READ_ONLY);		}
	BufType *mapWrite()			{ return map(GL_WRITE_ONLY);	}
	BufType *mapReadWrite()		{ return map(GL_READ_WRITE);	}
	void   unmap();


public:

	//Constructors
	BufferT(Usage usage = GL_STATIC_DRAW);
	BufferT(int num_elements, Usage usage = GL_STATIC_DRAW);
	BufferT(int num_elements, BufType *data, Usage usage = GL_STATIC_DRAW);

	//Destructor
	virtual ~BufferT();

	//Data
	void     setData(int num_elements, const BufType *data, Usage usage = GL_STATIC_DRAW);
	void     setElement(int index, const BufType *data);
	BufType *getData();
	BufType *getSubData(int start_index, int end_index);

	//Generic Attribute Pointer
	void attribPointer(GLuint index, GLsizei stride=0);

	GLenum getType()		{	return traits<BufType>::type;		}
//	GLuint getSize()		{	return traits<BufTarget>::
	GLuint getSize()		{	return sizeof(BufType);				}
									
	GLenum getTarget()		{	return traits<BufTarget>::target;	}
	GLuint getComponents()	{	return traits<BufType>::components; }


//	void clear()
//	{
//	//	glClearNamedBufferDataEXT(this->id(), GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT, &zeroUint);
//
//		BufType zero = (BufType)0;	//not necessary correct, because can be a vector type
//		glClearNamedBufferDataEXT(this->id(), GL_R32UI, GL_RED_INTEGER, traits<BufType>::type, &zero);
//	}

};

#include "Buffer.hpp"

//******************************************************************************
//ArrayBuffer class*************************************************************
//******************************************************************************
template<class BufType>
class ArrayBufferT : public BufferT<BufTarget_Array, BufType>
{
public:
	//Constructors
	ArrayBufferT(Usage usage = GL_STATIC_DRAW)                                  : BufferT<BufTarget_Array, BufType>(usage)						{}
	ArrayBufferT(int num_elements, Usage usage = GL_STATIC_DRAW)                : BufferT<BufTarget_Array, BufType>(num_elements, usage)		{}
	ArrayBufferT(int num_elements, BufType *data, Usage usage = GL_STATIC_DRAW) : BufferT<BufTarget_Array, BufType>(num_elements, data, usage)	{}
};

//******************************************************************************
//AtomicCounterBuffer class*****************************************************
//******************************************************************************
template<class BufType>
class AtomicCounterBufferT : public BufferT<BufTarget_AtomicCounter, BufType>
{
public:
	//Constructors
	AtomicCounterBufferT(Usage usage = GL_STATIC_DRAW)                                  : BufferT<BufTarget_AtomicCounter, BufType>(usage)						{}
	AtomicCounterBufferT(int num_elements, Usage usage = GL_STATIC_DRAW)                : BufferT<BufTarget_AtomicCounter, BufType>(num_elements, usage)		{}
	AtomicCounterBufferT(int num_elements, BufType *data, Usage usage = GL_STATIC_DRAW) : BufferT<BufTarget_AtomicCounter, BufType>(num_elements, data, usage)	{}
};

//******************************************************************************
//ElementBuffer class***********************************************************
//******************************************************************************
template<class BufType>
class ElementBufferT : public BufferT<BufTarget_Element, BufType>
{
public:
	//Constructors
	ElementBufferT(Usage usage = GL_STATIC_DRAW)                                  : BufferT<BufTarget_Element, BufType>(usage)						{}
	ElementBufferT(int num_elements, Usage usage = GL_STATIC_DRAW)                : BufferT<BufTarget_Element, BufType>(num_elements, usage)		{}
	ElementBufferT(int num_elements, BufType *data, Usage usage = GL_STATIC_DRAW) : BufferT<BufTarget_Element, BufType>(num_elements, data, usage)	{}
};

//******************************************************************************
//UniformBuffer class***********************************************************
//******************************************************************************
template<class BufType>
class UniformBufferT : public BufferT<BufTarget_Uniform, BufType>
{
public:
	//Constructors
	UniformBufferT(Usage usage = GL_STATIC_DRAW)                                  : BufferT<BufTarget_Uniform, BufType>(usage)						{}
	UniformBufferT(int num_elements, Usage usage = GL_STATIC_DRAW)                : BufferT<BufTarget_Uniform, BufType>(num_elements, usage)		{}
	UniformBufferT(int num_elements, BufType *data, Usage usage = GL_STATIC_DRAW) : BufferT<BufTarget_Uniform, BufType>(num_elements, data, usage)	{}
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Indirect Buffers-------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

struct DrawArraysIndirectCommand
{
	GLuint count;
	GLuint primCount;
	GLuint first;
	GLuint reservedMustBeZero;

	DrawArraysIndirectCommand()
	{
		count               = 1;
		primCount           = 1;
		first               = 0;
		reservedMustBeZero  = 0;
	}

	void print()
	{
		cerr << "count:     " << count     << endl;
		cerr << "primCount: " << primCount << endl;
		cerr << "first:     " << first     << endl;
	}
};
//-----------------------------------------------------------------------------
struct DrawElementsIndirectCommand
{
	GLuint count;
	GLuint primCount;
	GLuint firstIndex;
	GLuint baseVertex;
	GLuint reservedMustBeZero;

	DrawElementsIndirectCommand()
	{
		count               = 1;
		primCount           = 1;
		firstIndex          = 0;
		baseVertex          = 0;
		reservedMustBeZero  = 0;
	}

	void print()
	{
		cerr << "count:      " << count      << endl;
		cerr << "primCount:  " << primCount  << endl;
		cerr << "firstIndex: " << firstIndex << endl;
		cerr << "baseVertex: " << baseVertex << endl;
	}
};
//-----------------------------------------------------------------------------
struct DispatchIndirectCommand
{
	GLuint num_groups_x;
	GLuint num_groups_y;
	GLuint num_groups_z;

	void print()
	{
		cerr << "num_groups_x: " << num_groups_x << endl;
		cerr << "num_groups_y: " << num_groups_y << endl;
		cerr << "num_groups_z: " << num_groups_z << endl;
	}

};

//******************************************************************************
//IndirectBuffer class**********************************************************
//******************************************************************************
template<class BufType>
class IndirectBufferT : public BufferT<BufTarget_Indirect, BufType>
{
public:
	//Constructors
	IndirectBufferT(Usage usage = GL_STATIC_DRAW)                                  : BufferT<BufTarget_Indirect, BufType>(usage)						{}
	IndirectBufferT(int num_elements, Usage usage = GL_STATIC_DRAW)                : BufferT<BufTarget_Indirect, BufType>(num_elements, usage)			{}
	IndirectBufferT(int num_elements, BufType *data, Usage usage = GL_STATIC_DRAW) : BufferT<BufTarget_Indirect, BufType>(num_elements, data, usage)	{}
};

//******************************************************************************
//DispatchIndirectBuffer class**************************************************
//******************************************************************************
template<class BufType>
class DispatchIndirectBufferT : public BufferT<BufTarget_DispatchIndirect, BufType>
{
public:
	//Constructors
	DispatchIndirectBufferT(Usage usage = GL_STATIC_DRAW)                                  : BufferT<BufTarget_DispatchIndirect, BufType>(usage)						{}
	DispatchIndirectBufferT(int num_elements, Usage usage = GL_STATIC_DRAW)                : BufferT<BufTarget_DispatchIndirect, BufType>(num_elements, usage)			{}
	DispatchIndirectBufferT(int num_elements, BufType *data, Usage usage = GL_STATIC_DRAW) : BufferT<BufTarget_DispatchIndirect, BufType>(num_elements, data, usage)	{}
};


typedef IndirectBufferT<DrawArraysIndirectCommand>       IndirectArrayBuffer;
typedef IndirectBufferT<DrawElementsIndirectCommand>     IndirectElementBuffer;
typedef DispatchIndirectBufferT<DispatchIndirectCommand> IndirectDispatchBuffer;

};//End namespace buffer
};//End namespace render


