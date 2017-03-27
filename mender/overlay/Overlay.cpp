//*****************************************************************************
//Overlay.h********************************************************************
//*****************************************************************************

//Header include
#include "Overlay.h"

static std::string overlay_vert_shader = "										\n\
#version 410																	\n\
																				\n\
out vec4 vertexPos;																\n\
out vec2 texCoord;																\n\
																				\n\
uniform mat4 matrix;															\n\
																				\n\
const vec2 data[4] = vec2[](													\n\
	vec2(-1.0,  1.0),															\n\
	vec2(-1.0, -1.0),															\n\
	vec2( 1.0,  1.0),															\n\
	vec2( 1.0, -1.0));															\n\
																				\n\
void main()																		\n\
{																				\n\
	vertexPos   = matrix * vec4(data[gl_VertexID], 0, 1); 						\n\
	texCoord    = (data[gl_VertexID] + vec2(1))*0.5;  							\n\
	gl_Position = vertexPos;													\n\
}																				\n";


static std::string overlay_frag_shader2D = "									\n\
#version 410																	\n\
																				\n\
in vec4 vertexPos;																\n\
in vec2 texCoord;																\n\
																				\n\
layout(location = 0) out vec4 FragColor;										\n\
																				\n\
uniform sampler2D tex2;															\n\
																				\n\
void main()																		\n\
{																				\n\
	FragColor = texture(tex2, texCoord);										\n\
}																				\n";

static std::string overlay_frag_shader3D = "									\n\
#version 410																	\n\
																				\n\
in vec4 vertexPos;																\n\
in vec2 texCoord;																\n\
																				\n\
layout(location = 0) out vec4 FragColor;										\n\
																				\n\
uniform usampler3D tex3;														\n\
uniform float     layer;														\n\
uniform int       mipLevel;														\n\
																				\n\
vec4 textureSampleLayer()														\n\
{																				\n\
	return textureLod(tex3, vec3(texCoord,layer), mipLevel);					\n\
}																				\n\
																				\n\
void main()																		\n\
{																				\n\
	FragColor = textureSampleLayer();											\n\
}																				\n";



//*****************************************************************************
//Overlay.h********************************************************************
//*****************************************************************************
Overlay::Overlay()
{
//	shader2D.load(new VertShader(Source(overlay_vert_shader)), new FragShader(Source(overlay_frag_shader2D)));
//	shader3D.load(new VertShader(Source(overlay_vert_shader)), new FragShader(Source(overlay_frag_shader3D)));

	glGenVertexArrays(1, &vao);
}

