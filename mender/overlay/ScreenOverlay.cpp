//*****************************************************************************
//ScreenOverlay.h**************************************************************
//*****************************************************************************

//Header include
#include "ScreenOverlay.h"

static std::string vert_shader = "												\n\
#version 410																	\n\
																				\n\
out vec4 vertexPos;																\n\
out vec2 texCoord;																\n\
																				\n\
void main()																		\n\
{																				\n\
	float x = -1.0 + float((gl_VertexID & 1) << 2);								\n\
	float y = -1.0 + float((gl_VertexID & 2) << 1);								\n\
	vertexPos = vec4(x, y, 0, 1);												\n\
	x = (x + 1.0f) * 0.5f;														\n\
	y = (y + 1.0f) * 0.5f;														\n\
	texCoord = vec2(x, y);														\n\
	gl_Position = vertexPos;													\n\
}																				\n";

static std::string vert_test_shader = "											\n\
#version 410																	\n\
																				\n\
void main()																		\n\
{																				\n\
	if(gl_VertexID == 0) gl_Position = vec4(-1.0,-1.0,0.0,1.0);					\n\
	if(gl_VertexID == 1) gl_Position = vec4( 3.0,-1.0,0.0,1.0);					\n\
	if(gl_VertexID == 2) gl_Position = vec4(-1.0, 3.0,0.0,1.0);					\n\
}																				\n";


static std::string vert_shader2 = "												\n\
const int VertexCount = 3;														\n\
const vec2 Position[VertexCount] = vec2[](										\n\
	vec2(-1.0,-1.0),															\n\
	vec2( 3.0,-1.0),															\n\
	vec2(-1.0, 3.0));															\n\
																				\n\
void main()																		\n\
{																				\n\
	gl_Position = vec4(Position[gl_VertexID], 0.0, 1.0);						\n\
}																				\n";

static std::string passThru_vert = "											\n\
#version 410																	\n\
																				\n\
in vec4 vertexPos;																\n\
in vec4 vertexTex;																\n\
																				\n\
smooth out vec4 fragPos;														\n\
smooth out vec4 texCoord;														\n\
																				\n\
void main()																		\n\
{																				\n\
	texCoord    = vertexTex;													\n\
	fragPos     = vertexPos;													\n\
	gl_Position = vertexPos;													\n\
}																				\n";


static std::string frag_shader = "												\n\
#version 410																	\n\
																				\n\
in vec4 vertexPos;																\n\
in vec2 texCoord;																\n\
																				\n\
layout (location = 0) out vec4 FragColor;										\n\
																				\n\
uniform sampler2D tex;															\n\
uniform sampler2D depthTex;														\n\
uniform float     nearPlane;													\n\
uniform float     farPlane;														\n\
																				\n\
void main()																		\n\
{																				\n\
	vec4 texColor = texture(tex, texCoord);										\n\
//	FragColor = vec4(vec3(1) - texColor.xyz, texColor.a);						\n\
	FragColor = vec4(texColor.xyz,1);											\n\
	float depth = texture(depthTex, texCoord).x;								\n\
	float z = (2 * nearPlane) / (farPlane + nearPlane - depth * (farPlane - nearPlane));\n\
	gl_FragDepth = z;															\n\
}																				\n";

static std::string normal_frag_shader = "										\n\
#version 410																	\n\
																				\n\
in vec4 vertexPos;																\n\
in vec2 texCoord;																\n\
																				\n\
layout (location = 0) out vec4 FragColor;										\n\
																				\n\
uniform sampler2D tex;															\n\
																				\n\
void main()																		\n\
{																				\n\
	vec4 texColor = texture(tex, texCoord);										\n\
	texColor.xyz = (texColor.xyz + 1)/2;										\n\
//	FragColor = vec4(vec3(1) - texColor.xyz, texColor.a);						\n\
	FragColor = vec4(texColor.xyz,1);											\n\
}																				\n";


static std::string depth_frag_shader = "										\n\
#version 410																	\n\
																				\n\
in vec4 vertexPos;																\n\
in vec2 texCoord;																\n\
																				\n\
layout (location = 0) out vec4 FragColor;										\n\
																				\n\
uniform sampler2D depthTex;														\n\
uniform float     nearPlane;													\n\
uniform float     farPlane;														\n\
void main()																		\n\
{																				\n\
	float depth = texture(depthTex, texCoord).x;								\n\
	float z = (2 * nearPlane) / (farPlane + nearPlane - depth * (farPlane - nearPlane));\n\
	FragColor = vec4(z,z,z,1);													\n\
}																				\n";


//*****************************************************************************
//Overlay.h********************************************************************
//*****************************************************************************
ScreenOverlay::ScreenOverlay()
{
	overlayShader.load(new VertShader(Source(vert_shader)), new FragShader(Source(frag_shader)));
	depthShader.load(new VertShader(Source(vert_shader)), new FragShader(Source(depth_frag_shader)));
	normalShader.load(new VertShader(Source(vert_shader)), new FragShader(Source(normal_frag_shader)));

	glGenVertexArrays(1, &vao);
}
//
//void ScreenOverlay::render()
//{
//	overlay_shader->begin();
//	{
//		glDrawArrays( GL_TRIANGLES, 0, 3 );
//	}
//	overlay_shader->end();
//
//}
