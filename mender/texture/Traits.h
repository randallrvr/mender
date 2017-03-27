//******************************************************************************
//render/texture/Traits.hpp*****************************************************
//******************************************************************************

#pragma once

#include <render/gl.h>

namespace render
{
namespace texture
{

	template<typename T> struct traits
	{
		static const string texName;
		static const string formatName;
	};

	template<typename T>
	const string traits<T>::texName = "unknown texture name";

	template<typename T>
	const string traits<T>::formatName = "unknown texture format";

//#define OPENGL_TEXTURE_DIM(a, b, c) template<> struct traits<a>{ enum{ target = b }; static const string texName; }; const string traits<a>::texName = c;
#define OPENGL_TEXTURE_DIM(a, b) template<> struct traits<a>{ enum{ target = b }; static const string texName; };

	OPENGL_TEXTURE_DIM(struct tex1D,			 GL_TEXTURE_1D					);
	OPENGL_TEXTURE_DIM(struct tex1D_Array,		 GL_TEXTURE_1D_ARRAY			);
	OPENGL_TEXTURE_DIM(struct tex2D,			 GL_TEXTURE_2D					);
	OPENGL_TEXTURE_DIM(struct tex2D_Array,		 GL_TEXTURE_2D_ARRAY			);
	OPENGL_TEXTURE_DIM(struct tex2D_Multi,		 GL_TEXTURE_2D_MULTISAMPLE		);
	OPENGL_TEXTURE_DIM(struct tex2D_Mutli_Array, GL_TEXTURE_2D_MULTISAMPLE_ARRAY);
	OPENGL_TEXTURE_DIM(struct tex3D,			 GL_TEXTURE_3D					);
	OPENGL_TEXTURE_DIM(struct texRect,			 GL_TEXTURE_RECTANGLE			);
	OPENGL_TEXTURE_DIM(struct texBuffer,		 GL_TEXTURE_BUFFER				);
	OPENGL_TEXTURE_DIM(struct texCube,			 GL_TEXTURE_CUBE_MAP			);
	OPENGL_TEXTURE_DIM(struct texCube_Array,	 GL_TEXTURE_CUBE_MAP_ARRAY		);

//#define OPENGL_TEXTURE_STRING(a, b) template<> struct traits<a>{ static string texName; }; string traits<a>::texName = b;
//
//OPENGL_TEXTURE_STRING(struct tex3D, "tex3D");

#define OPENGL_TEXTURE_TYPE(a, b) template<> struct traits<a>{ enum{ type = b }; };

	OPENGL_TEXTURE_TYPE(unsigned char,		GL_UNSIGNED_BYTE	);
	OPENGL_TEXTURE_TYPE(struct ubyte,		GL_UNSIGNED_BYTE	);
	OPENGL_TEXTURE_TYPE(char,				GL_BYTE				);
	OPENGL_TEXTURE_TYPE(struct byte,		GL_BYTE				);
	OPENGL_TEXTURE_TYPE(unsigned short,		GL_UNSIGNED_SHORT	);
	OPENGL_TEXTURE_TYPE(short,				GL_SHORT			);
	OPENGL_TEXTURE_TYPE(unsigned int,		GL_UNSIGNED_INT		);
	OPENGL_TEXTURE_TYPE(int,				GL_INT				);
	OPENGL_TEXTURE_TYPE(float,				GL_FLOAT			);
	OPENGL_TEXTURE_TYPE(struct uint24_8,	GL_UNSIGNED_INT_24_8);


#define OPENGL_TEXTURE_INTERNAL_FORMAT(a, b, c) template<> struct traits<a>{ enum{ internal_format = b, channels = c }; };

//	OPENGL_TEXTURE_INTERNAL_FORMAT(struct alpha,				GL_ALPHA,				1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct alpha4,				GL_ALPHA4,				1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct alpha8,				GL_ALPHA8,				1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct alpha12,				GL_ALPHA12,				1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct alpha16,				GL_ALPHA16,				1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct alpha16f,				GL_ALPHA16F_ARB,		1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct alpha32f,				GL_ALPHA32F_ARB,		1);

	
//	OPENGL_TEXTURE_INTERNAL_FORMAT(struct luminance_alpha,		GL_LUMINANCE_ALPHA,		2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct luminance4_alpha4,	GL_LUMINANCE4_ALPHA4,	2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct luminance6_alpha2,	GL_LUMINANCE6_ALPHA2,	2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct luminance8_alpha8,	GL_LUMINANCE8_ALPHA8,	2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct luminance12_alpha4,	GL_LUMINANCE12_ALPHA4,	2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct luminance12_alpha12,	GL_LUMINANCE12_ALPHA12,	2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct luminance16_alpha16,	GL_LUMINANCE16_ALPHA16,	2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct intensity,			GL_INTENSITY,			1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct intensity4,			GL_INTENSITY4,			1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct intensity8,			GL_INTENSITY8,			1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct intensity12,			GL_INTENSITY12,			1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct intensity16,			GL_INTENSITY16,			1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct r3g3b2,				GL_R3_G3_B2,			3);
//	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb,					GL_RGB,					3);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb4,					GL_RGB4,				3);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb5,					GL_RGB5,				3);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb8,					GL_RGB8,				3);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb10,				GL_RGB10,				3);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb12,				GL_RGB12,				3);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb16,				GL_RGB16,				3);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb32f,				GL_RGB32F,				3);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb32ui,				GL_RGB32UI,				3);
//	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgba,					GL_RGBA,				4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgba2,				GL_RGBA2,				4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgba4,				GL_RGBA4,				4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb5a1,				GL_RGB5_A1,				4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgba8,				GL_RGBA8,				4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgb10a2,				GL_RGB10_A2,			4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgba12,				GL_RGBA12,				4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgba16,				GL_RGBA16,				4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgba32f,				GL_RGBA32F,				4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgba32i,				GL_RGBA32I,				4);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rgba32ui,				GL_RGBA32UI,			4);

	OPENGL_TEXTURE_INTERNAL_FORMAT(struct r32f,					GL_R32F,				1);

	OPENGL_TEXTURE_INTERNAL_FORMAT(struct r8,					GL_R8,					1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct r8i,					GL_R8I,					1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct r8ui,					GL_R8UI,				1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct r16i,					GL_R16I,				1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct r16ui,				GL_R16UI,				1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct r32i,					GL_R32I,				1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct r32ui,				GL_R32UI,				1);
	
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rg8i,					GL_RG8I,				2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rg8ui,				GL_RG8UI,				2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rg16i,				GL_RG16I,				2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rg16ui,				GL_RG16UI,				2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rg32i,				GL_RG32I,				2);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct rg32ui,				GL_RG32UI,				2);

	OPENGL_TEXTURE_INTERNAL_FORMAT(struct depth16,				GL_DEPTH_COMPONENT16,	1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct depth24,				GL_DEPTH_COMPONENT24,	1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct depth32,				GL_DEPTH_COMPONENT32,	1);
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct depth32f,				GL_DEPTH_COMPONENT32F,	1);


	OPENGL_TEXTURE_INTERNAL_FORMAT(struct depth24stencil8,		GL_DEPTH24_STENCIL8,	2);		//Serious question of whether or not channels should be 2 or 1, as stencil is merely
	OPENGL_TEXTURE_INTERNAL_FORMAT(struct depth32fstencil8,		GL_DEPTH32F_STENCIL8,	2);		//"packed" in with the depth texture. Only depth is accessible in shader implying
																								//only a single channel




#define OPENGL_TEXTURE_PIXEL_FORMAT(a, b) template<> struct traits<a>{ enum{ pixel_format = b }; };


	OPENGL_TEXTURE_PIXEL_FORMAT(struct color_index,		GL_COLOR_INDEX);
	OPENGL_TEXTURE_PIXEL_FORMAT(struct red,				GL_RED);
	OPENGL_TEXTURE_PIXEL_FORMAT(struct green,			GL_GREEN);
	OPENGL_TEXTURE_PIXEL_FORMAT(struct blue,			GL_BLUE);
	OPENGL_TEXTURE_PIXEL_FORMAT(struct rg,				GL_RG);
	OPENGL_TEXTURE_PIXEL_FORMAT(struct rg_int,			GL_RG_INTEGER);
	OPENGL_TEXTURE_PIXEL_FORMAT(struct red_int,			GL_RED_INTEGER);
	OPENGL_TEXTURE_PIXEL_FORMAT(struct alpha,			GL_ALPHA);
	OPENGL_TEXTURE_PIXEL_FORMAT(struct depthStencil,	GL_DEPTH_STENCIL);
//	OPENGL_TEXTURE_PIXEL_FORMAT(struct red_float,		GL_FLOAT_R_NV);
//	OPENGL_TEXTURE_PIXEL_FORMAT(struct rgb,				GL_RGB);
//	OPENGL_TEXTURE_PIXEL_FORMAT(struct rgba,			GL_RGBA);
//	OPENGL_TEXTURE_PIXEL_FORMAT(struct luminance,		GL_LUMINANCE);
//	OPENGL_TEXTURE_PIXEL_FORMAT(struct luminance_alpha,	GL_LUMINANCE_ALPHA);


#define OPENGL_TEXTURE_PIXEL_AND_INTENAL_FORMAT(a, b, c) template<> struct traits<a>{ enum{ internal_format = b, pixel_format = b, channels = c }; };

	OPENGL_TEXTURE_PIXEL_AND_INTENAL_FORMAT(struct depth,			GL_DEPTH_COMPONENT, 1);
//	OPENGL_TEXTURE_PIXEL_AND_INTENAL_FORMAT(struct alpha,			GL_ALPHA,			1);
	OPENGL_TEXTURE_PIXEL_AND_INTENAL_FORMAT(struct rgb,				GL_RGB,				3);
	OPENGL_TEXTURE_PIXEL_AND_INTENAL_FORMAT(struct rgba,			GL_RGBA,			4);
	OPENGL_TEXTURE_PIXEL_AND_INTENAL_FORMAT(struct luminance_alpha,	GL_LUMINANCE_ALPHA,	2);
	OPENGL_TEXTURE_PIXEL_AND_INTENAL_FORMAT(struct luminance,		GL_LUMINANCE,		1);

};
//End namespace texture
};
//End namespace render

