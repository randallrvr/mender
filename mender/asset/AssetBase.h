//*****************************************************************************
//AssetBase.h**********************************************************************
//*****************************************************************************

#pragma once

//Render Library Includes
#include <render/math.h>
#include <render/gl.h>
#include <render/texture.h>
#include <render/shader.h>
#include <render/buffer.h>
#include <render/texture.h>

//Standard Library Includes
//#include <unordered_map>

//Assimp Library Includes
#include <assimp/Importer.hpp>	//assimp 3.0 (somewhat broken)
#include <assimp/postprocess.h>	//assimp 3.0 (somewhat broken)
#include <assimp/scene.h>		//assimp 3.0 (somewhat broken)

//Local Includes
#include "Mesh.h"

#include <render/math.h>

//Namespaces
using namespace std;
using namespace buffer;
using namespace asset;

typedef unsigned int uint;

class AssetBase
{
public:
	typedef texture::Texture2D<GLubyte, texture::rgba,   texture::rgba>  SpecularTex;
	typedef texture::Texture2D<GLubyte, texture::rgba,   texture::rgba>  DiffuseTex;
	typedef texture::Texture2D<GLubyte, texture::rgba,   texture::rgba>  AmbientTex;
	typedef texture::Texture2D<GLubyte, texture::rgba,   texture::rgba>  NormalTex;
	typedef texture::Texture2D<GLubyte, texture::alpha8, texture::alpha> MaskTex; 
	
	typedef UniformBufferT<mat4f> MatrixBuffer;

protected:
	//Create an instance of the Importer class
	Assimp::Importer importer;

	NormalTex   *defaultNormalTex;
	SpecularTex *defaultSpecularTex;

	//the global Assimp scene object
	aiScene *ai_scene;

	// images / texture
	map<aiMaterial *, asset::Mesh::Material> materialMap;

	ShaderProgram *assetShader;

	string path;
	string file;
	
	GLuint num_faces;
	GLuint num_verts;

	GLuint max_verts;
	GLuint max_faces;
private:
	void init();

public:
	// Uniform Buffer for Matrices
	// this buffer will contain 3 matrices: projection, view and model
	// each matrix is a float array with 16 components
	MatrixBuffer *matrixBuffer;
	map<string, asset::Mesh::Material> materialNameMap;

	vector<asset::Mesh *> meshes;

	mat4f transform;

	vec3f min, max;
	vec3f center;
	vec3f d;

public:
	AssetBase();
	AssetBase(const string &filename);
	~AssetBase();

	void load(const string &);

	void normalize();
	void importAsset();

	void loadMaterials();

	asset::Mesh::Material loadMaterial(aiMaterial *ai_material);

	SpecularTex *loadSpecularTex(const string &filename);
	DiffuseTex  *loadDiffuseTex(const string &filename);
	AmbientTex  *loadAmbientTex(const string &filename);
	NormalTex   *loadNormalTex(const string &filename);
	MaskTex     *loadMaskTex(const string &filename);

	virtual void generate() = 0;
	virtual void   render() = 0;
	virtual void   render(const mat4f &, const mat4f &)	= 0;
	virtual void   render(const mat4f &, const mat4f &, const mat4f &) = 0;
	virtual void   render_shaderless() = 0;

	void get_bounding_box(vec3f &min, vec3f &max);
	void get_bounding_box_for_node(const aiNode *ai_node, vec3f &min, vec3f &max);

	GLuint setupShaders();

	GLuint numMeshes()	{ return (GLuint)meshes.size(); }

	GLuint maxFaces()	{ return max_faces; }
	GLuint maxVerts()	{ return max_verts; }

	GLuint numFaces()	{ return num_faces; }
	GLuint numVerts()	{ return num_verts; }

	string name()		{ return file.substr(0, file.find_last_of(".")); }

public:

	void importOpenGEX();


};

