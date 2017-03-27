//*****************************************************************************
//AssetBase.cpp****************************************************************
//*****************************************************************************

#include "AssetBase.h"

// include DevIL for image loading
//#include <IL\il.h>

//Standard Library Includes
#include <fstream>

//Shader Header Include
#include "AssetShaders.h"

//Namespaces
using namespace std;

// Uniform Bindings Points
static const GLuint matricesUniLoc = 1;
static const GLuint materialUniLoc = 2;

//*****************************************************************************
//Constructor******************************************************************
//*****************************************************************************
AssetBase::AssetBase()
{
	//initialize
	init();
}
//-----------------------------------------------------------------------------
AssetBase::AssetBase(const string &fullname)
{
	//initialize
	init();

	//load
	load(fullname);
}
//-----------------------------------------------------------------------------
void AssetBase::init()
{
	num_verts = 0;
	num_faces = 0;

	max_verts = 0;
	max_faces = 0;

	mat4f *matrices = new mat4f[3];
	matrixBuffer = new MatrixBuffer(3, matrices);
	delete [] matrices;

	assetShader = new ShaderProgram(new VertShader(Source(asset_vert_shader)), new FragShader(Source(asset_frag_shader)));
//	assetShader->bindBlock("Material",  materialUniLoc);
//	assetShader->bindBlock("Matrices",  matricesUniLoc);


	defaultNormalTex   = new NormalTex(1,1);
	defaultSpecularTex = new SpecularTex(1,1);


	GLubyte normalData[4]   = {128, 128, 128, 255};
	GLubyte specularData[4] = {128, 128, 128, 255};

	defaultNormalTex->load_data(&normalData[0]);
	defaultSpecularTex->load_data(&specularData[0]);

//	texUnit = shader->locateUniform("texUnit");
}
//*****************************************************************************
//Destructor*******************************************************************
//*****************************************************************************
AssetBase::~AssetBase()
{	
	// clear meshes stuff
	for(uint i = 0; i < meshes.size(); ++i)
	{
	}

	path.clear();
	file.clear();
}
//*****************************************************************************
//Load*************************************************************************
//*****************************************************************************
void AssetBase::load( const string &fullname )
{
	int index = std::max((int)fullname.find_last_of('/'), (int)fullname.find_last_of('\\'));

	//Separate path from filename
	path = fullname.substr( 0, index);
	file = fullname.substr(index + 1);

	ai_scene = NULL;

	//Import the asset
	importAsset();

	//Load Textures
	loadMaterials();

	//Generate buffers
	generate();
}
//*****************************************************************************
//Normalize********************************************************************
//*****************************************************************************
void AssetBase::normalize()		//shift everything to (0,0,0) -> (1,1,1)
{
	get_bounding_box(min, max);

	d      =  max - min;
	center = (max + min) * 0.5f;

	float scale_factor = 1 / (1.01f*std::max(d.x, std::max(d.y, d.z)));
	
//	transform.translate_by(vec3f(0.5f, 0.5f, 0.5f));
	transform.scale_by(vec3f(scale_factor));
	transform.translate_by(-center);
}
//*****************************************************************************
//Get Bounding Box*************************************************************
//*****************************************************************************
void AssetBase::get_bounding_box(vec3f &min, vec3f &max)
{
	min.x = min.y = min.z =  1e10f;
	max.x = max.y = max.z = -1e10f;
	get_bounding_box_for_node(ai_scene->mRootNode, min, max);
}
// ----------------------------------------------------------------------------
void AssetBase::get_bounding_box_for_node(const aiNode *ai_node, vec3f &min, vec3f &max)
{
	for(uint n = 0; n < ai_node->mNumMeshes; ++n)
	{
		aiMesh* ai_mesh = this->ai_scene->mMeshes[ai_node->mMeshes[n]];
		for(uint t = 0; t < ai_mesh->mNumVertices; ++t)
		{
			aiVector3D tmp = ai_mesh->mVertices[t];

			min.x = std::min(min.x, tmp.x);
			min.y = std::min(min.y, tmp.y);
			min.z = std::min(min.z, tmp.z);

			max.x = std::max(max.x, tmp.x);
			max.y = std::max(max.y, tmp.y);
			max.z = std::max(max.z, tmp.z);
		}
	}

	for(uint n = 0; n < ai_node->mNumChildren; ++n)
	{
		get_bounding_box_for_node(ai_node->mChildren[n], min, max);
	}
}
//*****************************************************************************
//Import Asset*****************************************************************
//*****************************************************************************
void AssetBase::importAsset()
{
	//reconstruct filename
	string fullname = path + '/' + file;

	ai_scene = (aiScene *)importer.ReadFile(fullname, aiProcessPreset_TargetRealtime_Quality |
	                                                  aiProcess_PreTransformVertices);

	// If the import failed, report it
	if(!ai_scene)	cerr << "Import failed with error: \"" << importer.GetErrorString() << "\"" << endl;
	else			cerr << "Import of scene \"" << fullname << "\"  succeeded." << endl;

}
//-----------------------------------------------------------------------------
void AssetBase::importOpenGEX()
{

}
//*****************************************************************************
//Load Textures****************************************************************
//*****************************************************************************
void AssetBase::loadMaterials()
{
	// initialization of DevIL
//	ilInit();

	// create material uniform buffer
//	aiMaterial *ai_material = ai_scene->mMaterials[ai_mesh->mMaterialIndex];


	if(ai_scene->HasTextures())
	{
		cerr << "Has textures" << endl;
	}
	else
	{
		cerr << "Has no (embedded) textures" << endl;
	}

	cerr << "mNumTextures: " << ai_scene->mNumTextures << endl;


	// scan scene's materials for textures
	for(uint m = 0; m < ai_scene->mNumMaterials; ++m)
	{
		aiMaterial *ai_material = ai_scene->mMaterials[m];

		aiString ai_name;
		ai_material->Get(AI_MATKEY_NAME, ai_name);

//		cerr << "\nloading material #" << m << ": " << ai_name.data << endl;

		Mesh::Material material = loadMaterial(ai_material);
		materialMap[ai_material] = material;
		materialNameMap[string(ai_name.data)] = material;
	}
}
//*****************************************************************************
//Get Material*****************************************************************
//*****************************************************************************
Mesh::Material AssetBase::loadMaterial(aiMaterial *ai_material)
{
	Mesh::Material material;

	aiString path;	// filename
	int texIndex = 0;

	// Can use ai_material->GetTextureCount(aiTextureType_DIFFUSE) and increment texIndex
	// To find and load multiple textures of each type, for now I don't want to deal with
	// that

	aiColor4D ai_color;
	aiString ai_string;

//	cerr << endl;
//	if(ai_material->Get(AI_MATKEY_NAME,                    ai_string) == AI_SUCCESS)	cerr << "AI_MATKEY_NAME,                   " << string(ai_string.data) << endl;
//	if(ai_material->GetTexture(aiTextureType_NONE,         texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_NONE,        " << endl;
//	if(ai_material->GetTexture(aiTextureType_DIFFUSE,      texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_DIFFUSE,     " << endl;
//	if(ai_material->GetTexture(aiTextureType_SPECULAR,     texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_SPECULAR,    " << endl;
//	if(ai_material->GetTexture(aiTextureType_AMBIENT,      texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_AMBIENT,     " << endl;
//	if(ai_material->GetTexture(aiTextureType_EMISSIVE,     texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_EMISSIVE,    " << endl;
//	if(ai_material->GetTexture(aiTextureType_HEIGHT,       texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_HEIGHT,      " << endl;
//	if(ai_material->GetTexture(aiTextureType_NORMALS,      texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_NORMALS,     " << endl;
//	if(ai_material->GetTexture(aiTextureType_SHININESS,    texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_SHININESS,   " << endl;
//	if(ai_material->GetTexture(aiTextureType_OPACITY,      texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_OPACITY,     " << endl;
//	if(ai_material->GetTexture(aiTextureType_DISPLACEMENT, texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_DISPLACEMENT," << endl;
//	if(ai_material->GetTexture(aiTextureType_LIGHTMAP,     texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_LIGHTMAP,    " << endl;
//	if(ai_material->GetTexture(aiTextureType_REFLECTION,   texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_REFLECTION,  " << endl;
//	if(ai_material->GetTexture(aiTextureType_UNKNOWN,      texIndex, &path) == AI_SUCCESS) cerr << "aiTextureType_UNKNOWN,     " << endl;

	material.diffuse  = vec4f(0.8f, 0.8f, 0.8f, 1.0f);	//default values
	material.ambient  = vec4f(0.2f, 0.2f, 0.2f, 1.0f);	//default values
	material.specular = vec4f(0.0f, 0.0f, 0.0f, 1.0f);	//default values
	material.emissive = vec4f(0.0f, 0.0f, 0.0f, 1.0f);	//default values

	cerr << endl;
	if(ai_material->Get(AI_MATKEY_NAME,                    ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_NAME,                   " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_TWOSIDED,                ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_TWOSIDED,               " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_SHADING_MODEL,           ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_SHADING_MODEL,          " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_ENABLE_WIREFRAME,        ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_ENABLE_WIREFRAME,       " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_BLEND_FUNC,              ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_BLEND_FUNC,             " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_OPACITY,                 ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_OPACITY,                " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_BUMPSCALING,             ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_BUMPSCALING,            " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_SHININESS,               ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_SHININESS,              " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_REFLECTIVITY,            ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_REFLECTIVITY,           " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_SHININESS_STRENGTH,      ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_SHININESS_STRENGTH,     " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_REFRACTI,                ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_REFRACTI,               " << string(ai_string.data) << endl;		}
	if(ai_material->Get(AI_MATKEY_COLOR_DIFFUSE,           ai_color)  == AI_SUCCESS)	{	cerr << "AI_MATKEY_COLOR_DIFFUSE,          " << vec4f(&(ai_color[0]))  << endl;		}
	if(ai_material->Get(AI_MATKEY_COLOR_AMBIENT,           ai_color)  == AI_SUCCESS)	{	cerr << "AI_MATKEY_COLOR_AMBIENT,          " << vec4f(&(ai_color[0]))  << endl;		}
	if(ai_material->Get(AI_MATKEY_COLOR_SPECULAR,          ai_color)  == AI_SUCCESS)	{	cerr << "AI_MATKEY_COLOR_SPECULAR,         " << vec4f(&(ai_color[0]))  << endl;		}
	if(ai_material->Get(AI_MATKEY_COLOR_EMISSIVE,          ai_color)  == AI_SUCCESS)	{	cerr << "AI_MATKEY_COLOR_EMISSIVE,         " << vec4f(&(ai_color[0]))  << endl;		}
	if(ai_material->Get(AI_MATKEY_COLOR_TRANSPARENT,       ai_color)  == AI_SUCCESS)	{	cerr << "AI_MATKEY_COLOR_TRANSPARENT,      " << vec4f(&(ai_color[0]))  << endl;		}
	if(ai_material->Get(AI_MATKEY_COLOR_REFLECTIVE,        ai_color)  == AI_SUCCESS)	{	cerr << "AI_MATKEY_COLOR_REFLECTIVE,       " << vec4f(&(ai_color[0]))  << endl;		}
	if(ai_material->Get(AI_MATKEY_GLOBAL_BACKGROUND_IMAGE, ai_string) == AI_SUCCESS)	{	cerr << "AI_MATKEY_GLOBAL_BACKGROUND_IMAGE," << string(ai_string.data) << endl;		}

	if(ai_material->Get(AI_MATKEY_COLOR_DIFFUSE,  ai_color) == AI_SUCCESS)	material.diffuse  = vec4f(&(ai_color[0]));
	if(ai_material->Get(AI_MATKEY_COLOR_AMBIENT,  ai_color) == AI_SUCCESS)	material.ambient  = vec4f(&(ai_color[0]));
	if(ai_material->Get(AI_MATKEY_COLOR_SPECULAR, ai_color) == AI_SUCCESS)	material.specular = vec4f(&(ai_color[0]));
	if(ai_material->Get(AI_MATKEY_COLOR_EMISSIVE, ai_color) == AI_SUCCESS)	material.emissive = vec4f(&(ai_color[0]));

//	ai_material->GetTex

	material.specular_tex = (ai_material->GetTexture(aiTextureType_SPECULAR, texIndex, &path) == AI_SUCCESS) ? loadSpecularTex(string(path.data)) : NULL;
	material.diffuse_tex  = (ai_material->GetTexture(aiTextureType_DIFFUSE,  texIndex, &path) == AI_SUCCESS) ? loadDiffuseTex(string(path.data))  : NULL;
	material.normal_tex   = (ai_material->GetTexture(aiTextureType_HEIGHT,   texIndex, &path) == AI_SUCCESS) ? loadNormalTex(string(path.data))   : NULL;

	material.hasDiffuseTex  = GLuint(material.diffuse_tex  != NULL);
	material.hasNormalTex   = GLuint(material.normal_tex   != NULL);
	material.hasSpecularTex = GLuint(material.specular_tex != NULL);
	material.texCount = material.hasDiffuseTex + material.hasNormalTex + material.hasSpecularTex;

	float shininess = 0.0;	//default value;
//	uint max;
//	if(ai_material->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
//	{
//		cerr << "shininess: " << shininess << endl;	
//	}
//	material.emissive = vec4f(&(ai_color[0]));
//	aiGetMaterialFloatArray(ai_material, AI_MATKEY_SHININESS, &shininess, &max);
	material.shininess = shininess;

	return material;
}
//*****************************************************************************
//Get Texture******************************************************************
//*****************************************************************************
asset::SpecularTex *AssetBase::loadSpecularTex(const string &filename)
{
	string fullname = path + '/' + filename;

	SpecularTex *texture = NULL;

	//May not want to create texture this way as it uses default image loading
	//methodology, Assimp may contain additional information about texture 
	//orientation, origin, etc... Could load explicitly and then load data
	//into the texture
	texture = new SpecularTex(fullname);

	texture->setMaxAnisotropy();
	texture->genMipmap();
	texture->set_filter(GL_LINEAR_MIPMAP_LINEAR);

	return texture;
}
//-----------------------------------------------------------------------------
asset::DiffuseTex *AssetBase::loadDiffuseTex(const string &filename)
{
	string fullname = path + '/' + filename;

	DiffuseTex *texture = NULL;

	//May not want to create texture this way as it uses default image loading
	//methodology, Assimp may contain additional information about texture 
	//orientation, origin, etc... Could load explicitly and then load data
	//into the texture
	texture = new DiffuseTex(fullname);

	texture->setMaxAnisotropy();
	texture->genMipmap();
	texture->set_filter(GL_LINEAR_MIPMAP_LINEAR);

	return texture;
}
//-----------------------------------------------------------------------------
asset::AmbientTex *AssetBase::loadAmbientTex(const string &filename)
{
	string fullname = path + '/' + filename;

	AmbientTex *texture = NULL;

	//May not want to create texture this way as it uses default image loading
	//methodology, Assimp may contain additional information about texture 
	//orientation, origin, etc... Could load explicitly and then load data
	//into the texture
	texture = new AmbientTex(fullname);

	texture->setMaxAnisotropy();
	texture->genMipmap();
	texture->set_filter(GL_LINEAR_MIPMAP_LINEAR);


	return texture;
}
//-----------------------------------------------------------------------------
asset::NormalTex *AssetBase::loadNormalTex(const string &filename)
{
	string fullname = path + '/' + filename;

	NormalTex *texture = NULL;

	//May not want to create texture this way as it uses default image loading
	//methodology, Assimp may contain additional information about texture 
	//orientation, origin, etc... Could load explicitly and then load data
	//into the texture
	texture = new NormalTex(fullname);

	texture->setMaxAnisotropy();
	texture->genMipmap();
	texture->set_filter(GL_LINEAR_MIPMAP_LINEAR);


	return texture;
}
//-----------------------------------------------------------------------------
asset::MaskTex *AssetBase::loadMaskTex(const string &filename)
{
	string fullname = path + '/' + filename;

	MaskTex *texture = NULL;

	//May not want to create texture this way as it uses default image loading
	//methodology, Assimp may contain additional information about texture 
	//orientation, origin, etc... Could load explicitly and then load data
	//into the texture
	texture = new MaskTex(fullname);

	texture->setMaxAnisotropy();
	texture->genMipmap();
	texture->set_filter(GL_LINEAR_MIPMAP_LINEAR);


	return texture;
}
