//*****************************************************************************
//Overlay.h********************************************************************
//*****************************************************************************

#pragma once

//Render includes
#include <render/shader.h>

using namespace render;

class Overlay
{
public:
	ShaderProgram shader2D;
	ShaderProgram shader3D;

	GLuint vao;

public:
	Overlay();
//

	template<class TexType, class IntFormat, class PixFormat>
	void render(texture::Texture2D<TexType, IntFormat, PixFormat> *tex2, const vec2f &bl, const vec2f &tr)
	{
	//	vec2f c = (bl+tr)*0.5f;		//this if already homogeneous
	//	vec2f d = (tr-bl);			//this if already homogeneous

		vec2f bl2 = bl * 2.0f - vec2f(1.0f,1.0f);	//this if 0->1
		vec2f tr2 = tr * 2.0f - vec2f(1.0f,1.0f);	//this if 0->1
		vec2f c  = (bl2+tr2)*0.5f;					//this if 0->1
		vec2f d  =  tr2-bl2;						//this if 0->1

		float w = d.x * 0.5f;
		float h = d.y * 0.5f;
		mat4f matrix(  w,   0, 0, 0,
		               0,   h, 0, 0,
		               0,   0, 1, 0,
		             c.x, c.y, 0, 1);

		shader2D.begin();
		shader2D.uniformSampler("tex2", tex2, 0);
		shader2D.uniform("matrix", matrix);
		{
			glBindVertexArray(vao);
			glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
		}
		shader2D.end();
	}

	template<class TexType, class IntFormat, class PixFormat>
	void renderLayer(texture::Texture3D<TexType, IntFormat, PixFormat> *tex3, const int layer, const vec2f &bl, const vec2f &tr)
	{
		vec2f bl2 = bl * 2.0f - vec2f(1.0f,1.0f);	//this if 0->1
		vec2f tr2 = tr * 2.0f - vec2f(1.0f,1.0f);	//this if 0->1
		vec2f c  = (bl2+tr2)*0.5f;					//this if 0->1
		vec2f d  =  tr2-bl2;						//this if 0->1

		float w = d.x * 0.5f;
		float h = d.y * 0.5f;
		mat4f matrix(  w,   0, 0, 0,
		               0,   h, 0, 0,
		               0,   0, 1, 0,
		             c.x, c.y, 0, 1);

		shader3D.begin();
		shader3D.uniformSampler("tex3",  tex3, 0);
		shader3D.uniform("layer", (layer + 0.5f) / (float)tex3->d);
		shader3D.uniform("matrix", matrix);
		{
			glBindVertexArray(vao);
			glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
		}
		shader3D.end();
	}

	template<class TexType, class IntFormat, class PixFormat>
	void renderMipmapLevelLayer(texture::Texture3D<TexType, IntFormat, PixFormat> *tex3, const int sliceNum, const int mipLevel, const vec2f &bl, const vec2f &tr)
	{
		vec2f bl2 = bl * 2.0f - vec2f(1.0f,1.0f);	//this if 0->1
		vec2f tr2 = tr * 2.0f - vec2f(1.0f,1.0f);	//this if 0->1
		vec2f c  = (bl2+tr2)*0.5f;					//this if 0->1
		vec2f d  =  tr2-bl2;						//this if 0->1

		float w = d.x * 0.5f;
		float h = d.y * 0.5f;
		mat4f matrix(  w,   0, 0, 0,
		               0,   h, 0, 0,
		               0,   0, 1, 0,
		             c.x, c.y, 0, 1);

		int   depth = tex3->d >> mipLevel;
		float layer = (sliceNum + 0.5f) / (float)depth;

		shader3D.begin();
		shader3D.uniformSampler("tex3",  tex3, TexUnit(0));
		shader3D.uniform("mipLevel", mipLevel);
		shader3D.uniform("layer",    layer);
		shader3D.uniform("matrix",   matrix);
		{
			glBindVertexArray(vao);
			glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
		}
		shader3D.end();
	}

};

