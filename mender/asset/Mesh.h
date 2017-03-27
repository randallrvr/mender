//*****************************************************************************
//Mesh.h***********************************************************************
//*****************************************************************************

#pragma once

//Standard Library Includes
#include <vector>
#include <map>

//Render Library Includes
#include <render/math.h>
#include <render/gl.h>
#include <render/texture.h>
#include <render/shader.h>
#include <render/buffer.h>
#include <render/texture.h>

//Assimp Includes
//#include <aiVector3D.h>
//#include <aiMatrix4x4.h>
//#include <aiScene.h>
#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>
#include <assimp/scene.h>

using namespace std;
using namespace buffer;

typedef unsigned int uint;

namespace render {
namespace asset {

typedef texture::Texture2D<GLubyte, texture::rgba,   texture::rgba > SpecularTex;
typedef texture::Texture2D<GLubyte, texture::rgba,   texture::rgba > DiffuseTex;
typedef texture::Texture2D<GLubyte, texture::rgba,   texture::rgba > AmbientTex;
typedef texture::Texture2D<GLubyte, texture::rgba,   texture::rgba > NormalTex;
typedef texture::Texture2D<GLubyte, texture::alpha8, texture::alpha> MaskTex;

class Mesh
{
public:
	struct Material {
		vec4f diffuse;
		vec4f ambient;
		vec4f specular;
		vec4f emissive;
		float shininess;
		GLuint hasDiffuseTex;
//		GLuint hasAmbientTex;
		GLuint hasSpecularTex;
		GLuint hasNormalTex;
		GLuint texCount;

		DiffuseTex *diffuse_tex;
//		AmbientTex  *ambient_tex;
		SpecularTex *specular_tex;
		NormalTex *normal_tex;
//		MaskTex     *mask_tex;

		Material() {
			diffuse_tex = NULL;
//			ambient_tex  = NULL;
			specular_tex = NULL;
			normal_tex = NULL;
//			mask_tex     = NULL;
		}
	};


	typedef ArrayBufferT<vec3f> VertexBuffer;
	typedef ArrayBufferT<vec3f> NormalBuffer;
	typedef ArrayBufferT<vec3f> TangentBuffer;
	typedef ArrayBufferT<vec3f> BitangentBuffer;
	typedef ArrayBufferT<vec2f> TextureBuffer;
	typedef ElementBufferT<GLuint> IndexBuffer;
	typedef UniformBufferT<Material> MaterialBuffer;
	typedef UniformBufferT<mat4f> MatrixBuffer;


public:
	string name;
	mat4f transform;
public:
	//Constructor
	Mesh();

	//Buffer Object
	BufferObject *buffer_object;

	//Element Buffer
	IndexBuffer *index_buffer;

	//Material Buffer
	MaterialBuffer *material_buffer;

	//Data Buffers
	VertexBuffer *vertex_buffer;
	NormalBuffer *normal_buffer;
	TangentBuffer *tangent_buffer;
	BitangentBuffer *bitangent_buffer;
	TextureBuffer *texture_buffer;


	DiffuseTex *diffuseTex;
	AmbientTex *ambientTex;
	NormalTex *normalTex;
	SpecularTex *specularTex;
//	MaskTex     *maskTex;

	void loadIndices(const aiMesh *ai_mesh);

	void loadPositions(const aiMesh *ai_mesh);

	void loadNormals(const aiMesh *ai_mesh);

	void loadTangents(const aiMesh *ai_mesh);

	void loadBitangents(const aiMesh *ai_mesh);

	void loadTexCoords(const aiMesh *ai_mesh);

	GLuint numFaces;
	GLuint numVerts;

};	// End class Mesh
};	// End namespace asset
};	// End namespace render

