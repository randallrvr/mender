//*****************************************************************************
// Mesh.cpp *******************************************************************
//*****************************************************************************

// Header Include
#include "Mesh.h"

#include <cmath>

//*****************************************************************************
//Constructors*****************************************************************
//*****************************************************************************
asset::Mesh::Mesh()
{
	buffer_object    = new BufferObject();
	vertex_buffer    = NULL;
	normal_buffer    = NULL;
	tangent_buffer   = NULL;
	bitangent_buffer = NULL;
	texture_buffer   = NULL;
	index_buffer     = NULL;
	material_buffer  = NULL;


	diffuseTex        = NULL;
//	ambientTex        = NULL;
	normalTex         = NULL;
//	maskTex           = NULL;

	numFaces = 0;
	numVerts = 0;
}
//*****************************************************************************
//Load Indices*****************************************************************
//*****************************************************************************
void asset::Mesh::loadIndices( const aiMesh *ai_mesh )
{
	// create array with faces
	// have to convert from Assimp format to array
	GLuint *faceArray = new GLuint[ai_mesh->mNumFaces * 3];

	GLuint faceIndex = 0;
	for(uint t = 0; t < ai_mesh->mNumFaces; ++t)
	{
		aiFace *ai_face = &ai_mesh->mFaces[t];
		memcpy(&faceArray[faceIndex], ai_face->mIndices, 3*sizeof(GLuint));
		faceIndex += 3;
	}

	this->index_buffer = new asset::Mesh::IndexBuffer(ai_mesh->mNumFaces*3, faceArray);
	this->buffer_object->addBuffer(this->index_buffer);



	delete [] faceArray;
}
//*****************************************************************************
//Load Positions***************************************************************
//*****************************************************************************
void asset::Mesh::loadPositions( const aiMesh *ai_mesh )
{
	this->vertex_buffer = new asset::Mesh::VertexBuffer(ai_mesh->mNumVertices, (vec3f *)(&ai_mesh->mVertices[0]));
	this->buffer_object->addBuffer(this->vertex_buffer);
}
//*****************************************************************************
//Load Normals*****************************************************************
//*****************************************************************************
void asset::Mesh::loadNormals( const aiMesh *ai_mesh )
{
	this->normal_buffer = new asset::Mesh::NormalBuffer(ai_mesh->mNumVertices, (vec3f *)(&ai_mesh->mNormals[0]));
	this->buffer_object->addBuffer(this->normal_buffer);
}
//*****************************************************************************
//Load Texture Coordinates*****************************************************
//*****************************************************************************
void asset::Mesh::loadTexCoords( const aiMesh *ai_mesh )
{
	vec2f *texCoords = new vec2f[ai_mesh->mNumVertices];
	for(uint k = 0; k < ai_mesh->mNumVertices; ++k)
	{
		aiVector3D ai_vec = ai_mesh->mTextureCoords[0][k];
		texCoords[k] = vec2f(ai_vec.x, ai_vec.y);
	}
	this->texture_buffer = new asset::Mesh::TextureBuffer(ai_mesh->mNumVertices, (vec2f *)(&texCoords[0]));
	this->buffer_object->addBuffer(this->texture_buffer);
	delete [] texCoords;
}
//*****************************************************************************
//Load Tangents and Bitangents*************************************************
//*****************************************************************************
void asset::Mesh::loadTangents( const aiMesh *ai_mesh )
{
	this->tangent_buffer = new asset::Mesh::TangentBuffer(ai_mesh->mNumVertices, (vec3f *)(&ai_mesh->mTangents[0]));
	this->buffer_object->addBuffer(this->tangent_buffer);
}
//*****************************************************************************
//Load Bitangents**************************************************************
//*****************************************************************************
void asset::Mesh::loadBitangents( const aiMesh *ai_mesh )
{
	this->bitangent_buffer = new asset::Mesh::BitangentBuffer(ai_mesh->mNumVertices, (vec3f *)(&ai_mesh->mBitangents[0]));
	this->buffer_object->addBuffer(this->bitangent_buffer);
}
