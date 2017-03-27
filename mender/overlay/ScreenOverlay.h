//*****************************************************************************
//ScreenOverlay.h**************************************************************
//*****************************************************************************

#pragma once

//Render includes
#include <render/shader.h>

using namespace render;

class ScreenOverlay
{
public:

	ShaderProgram overlayShader;
	ShaderProgram normalShader;
	ShaderProgram depthShader;
	GLuint vao;

public:
	ScreenOverlay();

	template<class TexType, class IntFormat, class PixFormat>
	void render(texture::Texture2D<TexType, IntFormat, PixFormat> *tex)
	{
	//	cerr << "other" << endl;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		glBindVertexArray(vao);
		overlayShader.begin();
		overlayShader.uniformSampler("tex", tex, TexUnit(0));
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		overlayShader.end();
	}

	template<class TexType, class IntFormat, class PixFormat, class dTexType, class dIntFormat, class dPixFormat>
	void render(texture::Texture2D<TexType, IntFormat, PixFormat> *tex, texture::Texture2D<dTexType, dIntFormat, dPixFormat> *depthTex, float nearPlane, float farPlane)
	{
		//	cerr << "other" << endl;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		glBindVertexArray(vao);
		overlayShader.begin();
		overlayShader.uniformSampler(     "tex",      tex, TexUnit(0));
		overlayShader.uniformSampler("depthTex", depthTex, TexUnit(1));
		overlayShader.uniform("nearPlane", nearPlane);
		overlayShader.uniform("farPlane",  farPlane);
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		overlayShader.end();
	}


	template<class TexType, class IntFormat, class PixFormat>
	void renderNormal(texture::Texture2D<TexType, IntFormat, PixFormat> *tex)
	{
		//	cerr << "other" << endl;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		normalShader.begin();
		normalShader.uniformSampler("tex", tex, TexUnit(0));
		{
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		normalShader.end();
	}

	template<class TexType, class PixFormat>
	void render(texture::Texture2D<TexType, texture::depth, PixFormat> *depthTex, float nearPlane, float farPlane)
	{
	//	cerr << "depth" << endl;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		depthShader.begin();
		depthShader.uniform("depthTex",  depthTex, TexUnit(0));
		depthShader.uniform("nearPlane", nearPlane);
		depthShader.uniform("farPlane",  farPlane);
		{
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		depthShader.end();
	}

	template<class TexType, class PixFormat>
	void render(texture::Texture2D<TexType, texture::depth32, PixFormat> *depthTex, float nearPlane, float farPlane)
	{
	//	cerr << "depth32" << endl;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		depthShader.begin();
		depthShader.uniform("depthTex",  depthTex, TexUnit(0));
		depthShader.uniform("nearPlane", nearPlane);
		depthShader.uniform("farPlane",  farPlane);
		{
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		depthShader.end();
	}


	template<class TexType, class PixFormat>
	void render(texture::Texture2D<TexType, texture::depth32f, PixFormat> *depthTex, float nearPlane, float farPlane)
	{
	//	cerr << "depth32f" << endl;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		depthShader.begin();
		depthShader.uniform("depthTex",  depthTex, TexUnit(0));
		depthShader.uniform("nearPlane", nearPlane);
		depthShader.uniform("farPlane",  farPlane);
		{
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		depthShader.end();
	}


	void render2D(GLuint texID)
	{
		overlayShader.begin();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);
		glProgramUniform1i(overlayShader.id(), overlayShader.getUniformLoc("tex"), 0);
		{
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		overlayShader.end();
	}

};

