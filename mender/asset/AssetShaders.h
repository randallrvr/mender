//*****************************************************************************
//AssetShaders.h***************************************************************
//*****************************************************************************

#pragma once

#include <string>

static std::string asset_vert_shader = "										\n\
#version 410																	\n\
																				\n\
layout (std140) uniform Matrices												\n\
{																				\n\
	mat4 projMatrix;															\n\
	mat4 viewMatrix;															\n\
	mat4 modelMatrix;															\n\
};																				\n\
																				\n\
layout(location = 0) in vec3 position;											\n\
layout(location = 1) in vec3 normal;											\n\
layout(location = 2) in vec2 texCoord;											\n\
																				\n\
out vec4 vertexPos;																\n\
out vec2 TexCoord;																\n\
out vec3 Normal;																\n\
																				\n\
void main()																		\n\
{																				\n\
	Normal      = normalize(vec3(viewMatrix * modelMatrix * vec4(normal,0.0)));	\n\
	TexCoord    = vec2(texCoord);												\n\
	gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(position,1.0);	\n\
}																				\n";


static std::string asset_frag_shader = "										\n\
#version 410																	\n\
																				\n\
layout (std140) uniform Material												\n\
{																				\n\
	vec4  diffuse;																\n\
	vec4  ambient;																\n\
	vec4  specular;																\n\
	vec4  emissive;																\n\
	float shininess;															\n\
	int   texCount;																\n\
};																				\n\
																				\n\
uniform sampler2D texUnit;														\n\
																				\n\
in  vec3 Normal;																\n\
in  vec2 TexCoord;																\n\
layout(location = 0) out vec4 colorOut;																\n\
layout(location = 1) out vec4 normalOut;																\n\
																				\n\
void main()																		\n\
{																				\n\
	vec3 color;																	\n\
	vec3 amb;																	\n\
																				\n\
	vec3  lightDir  = normalize(vec3(1.0, 1.0, 1.0));							\n\
	vec3  n         = normalize(Normal);										\n\
	float intensity = max(dot(lightDir, n), 0.0);								\n\
																				\n\
	if(texCount == 0)															\n\
	{																			\n\
		color = diffuse.xyz;													\n\
		amb   = ambient.xyz;													\n\
	}																			\n\
	else																		\n\
	{																			\n\
		color = texture(texUnit, TexCoord).xyz;									\n\
		amb   = color.xyz * 0.33;												\n\
	}																			\n\
	colorOut.xyz = (color * intensity) + amb;									\n\
	colorOut.a = 1.0;															\n\
	normalOut  = vec4(n, 1.0);													\n\
}																				\n";

