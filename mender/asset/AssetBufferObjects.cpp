//*****************************************************************************
//AssetBufferObjects.cpp*******************************************************
//*****************************************************************************

#include "AssetBufferObjects.h"

#include <sstream>

using namespace asset;

//-----------------------------------------------------------------------------
//Buffer Object (i.e. VAO) per Mesh--------------------------------------------
//-----------------------------------------------------------------------------
void AssetBufferObjects::generate()
{
	asset::Mesh::Material material; 

	matrixBuffer = new MatrixBuffer(3);

	// For each mesh
	for(uint n = 0; n < ai_scene->mNumMeshes; ++n)
	{
		aiMesh *ai_mesh = ai_scene->mMeshes[n];
		Mesh      *mesh = new Mesh();

		mesh->numFaces = ai_mesh->mNumFaces;
		mesh->numVerts = ai_mesh->mNumVertices;

	//	cerr << "mesh #: "     << n << endl;
	//	cerr << "mesh faces: " << mesh->numFaces << endl;
	//	cerr << "mesh verts: " << mesh->numVerts << endl;

		if(ai_mesh->mName.length == 0)
		{
			stringstream meshNameStream;
			meshNameStream << this->name() << "_" << n;
			mesh->name = meshNameStream.str();
		}
		else
		{
			mesh->name = string(ai_mesh->mName.data);
		}

		mesh->loadIndices(ai_mesh);

		if(ai_mesh->HasPositions())				mesh->loadPositions(ai_mesh);
		if(ai_mesh->HasNormals())				mesh->loadNormals(ai_mesh);
		if(ai_mesh->HasTextureCoords(0))		mesh->loadTexCoords(ai_mesh);
		if(ai_mesh->HasTangentsAndBitangents())
		{
			mesh->loadTangents(ai_mesh);
			mesh->loadBitangents(ai_mesh);
		}

		// create material uniform buffer
		aiMaterial *ai_material = ai_scene->mMaterials[ai_mesh->mMaterialIndex];

		material = materialMap[ai_material];

		mesh->specularTex = material.specular_tex;
		mesh->diffuseTex  = material.diffuse_tex;
//		mesh->ambientTex  = material.ambient_tex;
		mesh->normalTex   = material.normal_tex;
//		mesh->maskTex     = material.mask_tex;

		mesh->material_buffer = new Mesh::MaterialBuffer(1, &material);
		mesh->buffer_object->addBuffer(mesh->material_buffer);

		num_faces += mesh->numFaces;
		num_verts += mesh->numVerts;

		max_faces = std::max(max_faces, mesh->numFaces);
		max_verts = std::max(max_verts, mesh->numVerts);

		meshes.push_back(mesh);
	}
}
//*****************************************************************************
//Render***********************************************************************
//*****************************************************************************
void AssetBufferObjects::render(const mat4f &projMatrix, const mat4f &viewMatrix)
{
	render_iterative(projMatrix, viewMatrix, transform);
}
//-----------------------------------------------------------------------------
void AssetBufferObjects::render(const mat4f &projMat, const mat4f &viewMat, const mat4f &modelMat)
{
	render_iterative(projMat, viewMat, modelMat);
}
//-----------------------------------------------------------------------------
void AssetBufferObjects::render_shaderless()
{
	for(uint i = 0; i < meshes.size(); ++i)
	{
		const Mesh &mesh = *meshes[i];
		mesh.buffer_object->renderElementsTriangles();
	}
}
//-----------------------------------------------------------------------------
void AssetBufferObjects::render_iterative(const mat4f &projMatrix, const mat4f &viewMatrix, const mat4f &modelMatrix)
{
	matrixBuffer->setElement(0,  &projMatrix);
	matrixBuffer->setElement(1,  &viewMatrix);
	matrixBuffer->setElement(2, &modelMatrix);

	assetShader->begin();
	assetShader->uniformBlock("Matrices", matrixBuffer);
	{
		for(uint i = 0; i < meshes.size(); ++i)
		{
			const Mesh &mesh = *meshes[i];

			assetShader->uniformBlock("Material", mesh.material_buffer);

			if(mesh.diffuseTex)	assetShader->uniformSampler("texUnit", mesh.diffuseTex, 0);

			mesh.buffer_object->renderElementsTriangles();
		}
	}
	assetShader->end();
}


