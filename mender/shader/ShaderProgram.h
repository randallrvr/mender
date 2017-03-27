//*****************************************************************************
//render/shader/ShaderProgram.h************************************************
//*****************************************************************************

#pragma once

//Render Library Includes
#include <render/texture.h>
#include <render/buffer.h>
#include <render/math.h>

//Project Includes
#include "Shader.h"

//Standard Library Includes
#include <cassert>
#include <vector>
#include <string>
#include <map>

//Namespaces
using namespace std;

namespace render
{


/*
struct VertFile : public string { VertFile(const string &filename) : string(filename) {} };
struct FragFile : public string { FragFile(const string &filename) : string(filename) {} };
struct GeomFile : public string { GeomFile(const string &filename) : string(filename) {} };
struct EvalFile : public string { EvalFile(const string &filename) : string(filename) {} };
struct CtrlFile : public string { CtrlFile(const string &filename) : string(filename) {} };
struct CompFile : public string { CompFile(const string &filename) : string(filename) {} };
*/


class ShaderProgram
{
protected:

	//ShaderProgram ID
	GLuint program_id;

public:
	union
	{
		struct 
		{
			VertShader *vert_shader;
			FragShader *frag_shader;
			GeomShader *geom_shader;
			EvalShader *eval_shader;
			CtrlShader *ctrl_shader;
			CompShader *comp_shader;
		};

		Shader *shaders[6];	//generic way of accessing all shaders without caring about their type
	};
protected:

	map<string, GLint> attributeMap;	
	map<string, GLint> uniformLocationMap;
	map<string, GLint> uniformBindingMap;
	map<string, GLint> atomicMap;
	map<string, GLint> blockMap;

	map<string, GLint> vertSubroutineMap;
	map<string, GLint> fragSubroutineMap;
	map<string, GLint> geomSubroutineMap;
	map<string, GLint> evalSubroutineMap;
	map<string, GLint> ctrlSubroutineMap;
	map<string, GLint> compSubroutineMap;

	map<string, GLint> vertSubroutineUniformMap;
	map<string, GLint> fragSubroutineUniformMap;
	map<string, GLint> geomSubroutineUniformMap;
	map<string, GLint> evalSubroutineUniformMap;
	map<string, GLint> ctrlSubroutineUniformMap;
	map<string, GLint> compSubroutineUniformMap;

	void mapSubroutineUniforms();
	void mapSubroutines();
	void mapAttributes();
	void mapUniforms();
	void mapAtomics();
	void mapBlocks();

	void mapStageSubroutineUniforms(GLenum, map<string, GLint> &);
	void mapStageSubroutines(GLenum, map<string, GLint> &);

	static map<GLenum, string> shaderStageNames;
	static map<GLenum, string> shaderUniformTypes;

public:
	//Locate Uniforms, Attributes, and Blocks
//	GLint  locateSubroutine(const string &);
	GLint  locateAttribute (const string &);
	GLint  locateUniform   (const string &);
	GLuint locateBlock     (const string &);

//	GLint  locateSubroutine(const string &);
	GLint  locateAttribute (const char *);
	GLint  locateUniform   (const char *);
	GLuint locateBlock     (const char *);

	void printAll();
	void printSubroutineUniforms();
	void printSubroutines();
	void printAttributes();
	void printUniforms();
	void printBlocks();


	void validateState();


	void setFeedbackOut(const string &);


private:
	//Load
	void read_source_from_glsl(const string &, string &, string &, string &);

	void init(VertShader *, CtrlShader *, EvalShader *, GeomShader *, FragShader *, CompShader * = NULL);

public:

	//Constructors
	ShaderProgram();
	ShaderProgram(VertShader *, FragShader *);
	ShaderProgram(VertShader *, GeomShader *, FragShader *);	//pipeline order
	ShaderProgram(VertShader *, CtrlShader *, EvalShader *, FragShader *);	//pipeline order (Tess, No Geom)
	ShaderProgram(VertShader *, CtrlShader *, EvalShader *, GeomShader *, FragShader *);	//pipeline order
	ShaderProgram(VertShader *);
	ShaderProgram(CompShader *);
	ShaderProgram(VertShader *, GeomShader *);

	ShaderProgram(const VertFile &, const FragFile &);
	ShaderProgram(const VertFile &, const GeomFile &, const FragFile &);	//pipeline order
	ShaderProgram(const VertFile &, const CtrlFile &, const EvalFile &, const FragFile &);	//pipeline order (Tess, No Geom)
	ShaderProgram(const VertFile &, const CtrlFile &, const EvalFile &, const GeomFile &, const FragFile &);	//pipeline order
	ShaderProgram(const VertFile &);
	ShaderProgram(const CompFile &);
	ShaderProgram(const VertFile &, const GeomFile &);

	void load(const VertFile &, const FragFile &);
	void load(const VertFile &, const GeomFile &, const FragFile &);	//pipeline order
	void load(const VertFile &, const CtrlFile &, const EvalFile &, const FragFile &);	//pipeline order (Tess, No Geom)
	void load(const VertFile &, const CtrlFile &, const EvalFile &, const GeomFile &, const FragFile &);	//pipeline order
	void load(const VertFile &);
	void load(const CompFile &);
	void load(const VertFile &, const GeomFile &);

	void load(const ShaderFile &);
//	void load(const ShaderFile &, const ShaderFile &);

	void load(VertShader *, FragShader *);
	void load(VertShader *, GeomShader *, FragShader *);	//pipeline order
	void load(VertShader *, CtrlShader *, EvalShader *, FragShader *);	//pipeline order (Tess, No Geom)
	void load(VertShader *, CtrlShader *, EvalShader *, GeomShader *, FragShader *);	//pipeline order
	void load(VertShader *);
	void load(CompShader *);
	void load(VertShader *, GeomShader *);


	//Destructor
	virtual ~ShaderProgram();
	void clearShaders();

	//Link
	bool link();

	//Log
	void log();

	//Begin/End
	void begin();
	static void end();

	//Refresh
	void refresh();
	void refreshSource();
	
	//ID
	GLuint id();

	//Bind FragData, Attribute, and Blocks
	void bindFragData (const char *, GLuint);
	void bindAttribute(const char *, GLuint);
	void bindBlock    (const char *, GLuint);

	void bindFragData (const string &, GLuint);
	void bindAttribute(const string &, GLuint);
	void bindBlock    (const string &, GLuint);

	///////////////////////////
	//Set Subroutine Uniforms//
	///////////////////////////
	void vertSubroutine(const string &);
	void fragSubroutine(const string &);
	void geomSubroutine(const string &);
	void evalSubroutine(const string &);
	void ctrlSubroutine(const string &);
	void compSubroutine(const string &);

	/////////////////
	//Set #define's//
	/////////////////

	void setDefine(const string &var, const string &val);
	void vertDefine(const string &var, const string &val) { if(vert_shader) { glDetachShader(program_id, vert_shader->id()); vert_shader->setDefine(var, val); glAttachShader(program_id, vert_shader->id()); } }
	void fragDefine(const string &var, const string &val) { if(frag_shader) { glDetachShader(program_id, frag_shader->id()); frag_shader->setDefine(var, val); glAttachShader(program_id, frag_shader->id()); } }
	void geomDefine(const string &var, const string &val) { if(geom_shader) { glDetachShader(program_id, geom_shader->id()); geom_shader->setDefine(var, val); glAttachShader(program_id, geom_shader->id()); } }
	void evalDefine(const string &var, const string &val) { if(eval_shader) { glDetachShader(program_id, eval_shader->id()); eval_shader->setDefine(var, val); glAttachShader(program_id, eval_shader->id()); } }
	void ctrlDefine(const string &var, const string &val) { if(ctrl_shader) { glDetachShader(program_id, ctrl_shader->id()); ctrl_shader->setDefine(var, val); glAttachShader(program_id, ctrl_shader->id()); } }
	void compDefine(const string &var, const string &val) { if(comp_shader) { glDetachShader(program_id, comp_shader->id()); comp_shader->setDefine(var, val); glAttachShader(program_id, comp_shader->id()); } }

	///////////////////
	//Get Subroutines//
	///////////////////
	vector<string> getStageSubroutines(GLenum);
	vector<string> getVertSubroutines();
	vector<string> getFragSubroutines();
	vector<string> getGeomSubroutines();
	vector<string> getEvalSubroutines();
	vector<string> getCtrlSubroutines();
	vector<string> getCompSubroutines();



	///////////////////////////////////////////////////////////////////////////////////////
	//Note About Uniforms                                                                //
	//===================================================================================//
	//Be very careful to cast whatever your passing to the uniform function to the       //
	//correct type, i.e. the type defined in the shader otherwise you WILL have problems,//
	//just not any error messages.                                                       //
	///////////////////////////////////////////////////////////////////////////////////////
	
	//Set Uniform Floats
	void uniform(const string &, GLfloat);
	void uniform(const string &, GLfloat, GLfloat);
	void uniform(const string &, GLfloat, GLfloat, GLfloat);
	void uniform(const string &, GLfloat, GLfloat, GLfloat, GLfloat);
	
	//Set Uniform Integers
	void uniform(const string &, int);
	void uniform(const string &, int, int);
	void uniform(const string &, int, int, int);
	void uniform(const string &, int, int, int, int);
	
	//Set Uniform Unsigned Integers (requires GL_EXT_gpu_shader4)
	void uniform(const string &, GLuint);
	void uniform(const string &, GLuint, GLuint);
	void uniform(const string &, GLuint, GLuint, GLuint);
	void uniform(const string &, GLuint, GLuint, GLuint, GLuint);
	
	/////////////////////////////
	//Set math library uniforms//
	/////////////////////////////

	//Set Integer Vectors
	void uniform(const string &, vec2i);
	void uniform(const string &, vec3i);
	void uniform(const string &, vec4i);

	//Set Floating Point Vectors
	void uniform(const string &, vec2f);
	void uniform(const string &, vec3f);
	void uniform(const string &, vec4f);

	//Set Double Vectors
	void uniform(const string &, vec2d);
	void uniform(const string &, vec3d);
	void uniform(const string &, vec4d);

	//Set Integer Vectors Arrays
	void uniform(const string &, GLsizei, vec2i *);
	void uniform(const string &, GLsizei, vec3i *);
	void uniform(const string &, GLsizei, vec4i *);

	//Set Floating Point Vectors Arrays
	void uniform(const string &, GLsizei, vec2f *);
	void uniform(const string &, GLsizei, vec3f *);
	void uniform(const string &, GLsizei, vec4f *);

	//Set Double Vectors Arrays
	void uniform(const string &, GLsizei, vec2d *);
	void uniform(const string &, GLsizei, vec3d *);
	void uniform(const string &, GLsizei, vec4d *);

	//Set Floating Point Quaternions
	void uniform(const string &, quatf);


	//Set Floating Point Matrices
	void uniform(const string &, mat3f, bool = false);

	//Set Floating Point Matrices
	void uniform(const string &, mat4f, bool = false);

	///////////////////////
	//Set buffer uniforms//
	///////////////////////

	void uniformBlock(const string &name, buffer::Buffer *buffer)
	{
		auto itr = blockMap.find(name);
		if(itr != blockMap.end())
		{
			//This works because I set the bindingPoint to the location by default
			buffer->bindBase(itr->second);
		}
		else
		{
		//	cerr << "uniformBlock \"" << name << "\" doesn't exist!" << endl;
		}
	}

	void uniformBlock(const string &name, buffer::Buffer *buffer, BindingPoint bindingPoint)
	{
		auto itr = blockMap.find(name);
		if(itr != blockMap.end())
		{
			glUniformBlockBinding(program_id, itr->second, bindingPoint.val);
			buffer->bindBase(bindingPoint.val);
		}
		else
		{
		//	cerr << "uniformBlock \"" << name << "\" doesn't exist!" << endl;
		}
	}



	////////////////////////////////////////////
	//Set texture library uniforms as samplers//
	////////////////////////////////////////////

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniformSampler(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniformSampler(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex, MipLevel mipLevel);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniformSampler(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex, MipRange mipRange);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex, MipLevel mipLevel);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, TexUnit activeTex, MipRange mipRange);



	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniformTextureHandle(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex)
	{
	//	if(!glIsTextureHandleResidentARB(tex->texHandle))
	//	{
	//		glMakeTextureHandleResidentARB(tex->texHandle);
	//	}

		glProgramUniformHandleui64ARB(program_id, getUniformLoc(name), tex->texHandle);
	}



	//////////////////////////////////////////
	//Set texture library uniforms as images//
	//////////////////////////////////////////


	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniformImage(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, GLenum access = GL_READ_WRITE);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniformImage(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, MipLevel mipLevel, GLenum access = GL_READ_WRITE);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniformImage(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, Layer layer, GLenum access = GL_READ_WRITE);

	void uniformImage(const string &name, GLuint image_id, ImageUnit imageUnit, GLenum format, GLuint mipmap_level = 0, GLenum access = GL_READ_WRITE)
	{
		string avoidWarning = name;	//This is dumb do something about it
		glBindImageTexture(imageUnit.val, image_id, mipmap_level, GL_TRUE, 0, access, format);
	}

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniformImageAtomicRGBA32F(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, GLenum access = GL_READ_WRITE);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, Access access = GL_READ_WRITE);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, MipLevel mipLevel, Access access = GL_READ_WRITE);

	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
	void uniform(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, ImageUnit imageUnit, Layer layer, Access access = GL_READ_WRITE);


//	template<class TexTarget, class TexType, class IntFormat, class PixFormat>
//	void uniformImageHandle(const string &name, texture::TextureT<TexTarget, TexType, IntFormat, PixFormat> *tex, MipLevel mipLevel = 0, Access access = GL_READ_WRITE)
//	{
//	//	if(!glIsImageHandleResidentARB(tex->imgHandles[mipLevel.val]))
//	//	{
//	//		glMakeImageHandleResidentARB(tex->imgHandles[mipLevel.val], access.val);
//	//	}
//#if OPENGL_VER >= 44
//		glProgramUniformHandleui64ARB(program_id, getUniformLoc(name), tex->imgHandles[mipLevel.val]);
//#elif OPENGL_VER >= 40
//		glProgramUniformHandleui64NV(program_id, getUniformLoc(name), tex->imgHandles[mipLevel.val]);
//#endif
//	}



	// Receive Uniform variables:
	void getUniformfv(const string &, GLfloat *);
	void getUniformiv(const string &, int *);
	void getUniformuiv(const string &, GLuint *);
	
	//Set Float Vertex Attributes
	void attribute(const string &, GLfloat);
	void attribute(const string &, GLfloat, GLfloat);
	void attribute(const string &, GLfloat, GLfloat, GLfloat);
	void attribute(const string &, GLfloat, GLfloat, GLfloat, GLfloat);
	
	//Set Double Vertex Attributes
	void attribute(const string &, double);
	void attribute(const string &, double, double);
	void attribute(const string &, double, double, double);
	void attribute(const string &, double, double, double, double);
	
	//Set Short Vertex Attributes
	void attribute(const string &, short int);
	void attribute(const string &, short int, short int);
	void attribute(const string &, short int, short int, short int);
	void attribute(const string &, short int, short int, short int, short int);
	
	//Set Integer Vertex Attributes (Requires GL_EXT_gpu_shader4)
	void attribute(const string &, int);
	void attribute(const string &, int, int);
	void attribute(const string &, int, int, int);
	void attribute(const string &, int, int, int, int);
	
	//Set Unsigned Integer Vertex Attributes (Requires GL_EXT_gpu_shader4)
	void attribute(const string &, GLuint);
	void attribute(const string &, GLuint, GLuint);
	void attribute(const string &, GLuint, GLuint, GLuint);
	void attribute(const string &, GLuint, GLuint, GLuint, GLuint);

	const vec3i getComputeGroupSize() const { vec3i groupSize; glGetProgramiv(program_id, GL_COMPUTE_WORK_GROUP_SIZE, &groupSize.x); return groupSize; }

	void programBinary();


	GLint getUniformLoc(const string &name)
	{
		auto itr = uniformLocationMap.find(name);
		if(itr != uniformLocationMap.end())
		{
			return itr->second;
		}
		cerr << "Uniform \"" << name << "\" not found!" << endl;
		return -1;
	}

};
//End class ShaderProgram

#include "ShaderTexture.hpp"
#include "ShaderImage.hpp"



};
//End namespace render
