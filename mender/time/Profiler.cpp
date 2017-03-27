//*****************************************************************************
//render/time/Profiler.cpp*****************************************************
//*****************************************************************************

//Header Include
#include "Profiler.h"

//Render Library Includes
#include <render/shader.h>

#include <algorithm>

//Namespaces
using namespace render;

// All timings (in a map!)
map<string, GPUTimings *> GPUTimings::timingsMap;

// Base level timers
vector<GPUTimings *> GPUTimings::rootTimings;

int   GPUTimings::colorIndex       = 0;
bool  GPUTimings::initShaders      = false;
float GPUTimings::maxTimeAllTimers = 0.0f;

ShaderProgram *GPUTimings::graphShader = NULL;
ShaderProgram *GPUTimings::stackShader = NULL;
ShaderProgram *GPUTimings::lineShader  = NULL;
GLuint GPUTimings::pointlessVAO = 0;

const float invFPS = 1 / (33.33333333333f / 1000.0f); //33 milliseconds for 30 fps


vec3f GPUTimings::colorTable[maxColors]= {
	vec3f(1.0f, 0.0f, 0.0f),
	vec3f(0.0f, 1.0f, 0.0f),
	vec3f(0.0f, 0.0f, 1.0f),
	vec3f(1.0f, 1.0f, 0.0f),
	vec3f(1.0f, 0.0f, 1.0f),
	vec3f(0.0f, 1.0f, 1.0f),
	vec3f(1.0f, 1.0f, 1.0f),
	vec3f(0.5f, 0.0f, 0.0f),
	vec3f(0.0f, 0.5f, 0.0f),
	vec3f(0.0f, 0.0f, 0.5f),
	vec3f(0.5f, 0.5f, 0.0f),
	vec3f(0.5f, 0.0f, 0.5f),
	vec3f(0.0f, 0.5f, 0.5f),
	vec3f(1.0f, 0.5f, 0.0f),
	vec3f(0.5f, 1.0f, 0.0f),
	vec3f(1.0f, 0.0f, 0.5f),
	vec3f(0.5f, 0.0f, 1.0f),
	vec3f(0.0f, 1.0f, 0.5f),
	vec3f(0.0f, 0.5f, 1.0f),
	vec3f(0.5f, 0.5f, 0.5f),
	vec3f(0.5f, 1.0f, 1.0f),
	vec3f(1.0f, 0.5f, 1.0f),
	vec3f(1.0f, 1.0f, 0.5f),
	vec3f(1.0f, 0.5f, 0.5f),
	vec3f(0.5f, 1.0f, 0.5f),
	vec3f(0.5f, 0.5f, 1.0f),
};

static Source graph_shader_vert = string("								\n\
#version 410															\n\
																		\n\
layout(location = 0) in float time;										\n\
flat out uint i;														\n\
																		\n\
uniform mat4  orthoMatrix;												\n\
uniform float yScale;													\n\
uniform float xInc;														\n\
uniform uint  Index;													\n\
uniform uint  Max;														\n\
																		\n\
																		\n\
void main()																\n\
{																		\n\
	i = ((gl_VertexID - Index)%Max);									\n\
	float x = i * xInc;													\n\
	float y = time * yScale;											\n\
	gl_Position = orthoMatrix * vec4(x,y,0,1);							\n\
}																		\n");

static Source graph_shader_frag = string("								\n\
#version 410															\n\
																		\n\
flat in uint i;															\n\
layout(location = 0) out vec4 FragColor;								\n\
																		\n\
uniform vec3 color;														\n\
																		\n\
void main()																\n\
{ 																		\n\
	if(i == 0)															\n\
		discard;														\n\
	FragColor.rgb = color;												\n\
	FragColor.a = 1.0f;													\n\
}																		\n");

static Source line_shader_vert = string("								\n\
#version 410															\n\
																		\n\
uniform mat4 orthoMatrix;												\n\
uniform vec2 p0;														\n\
uniform vec2 p1;														\n\
																		\n\
void main()																\n\
{																		\n\
	vec2 xy = (gl_VertexID == 0) ? p0 : p1;								\n\
	gl_Position = orthoMatrix * vec4(xy,0,1);							\n\
}																		\n");

static Source line_shader_frag = string("								\n\
#version 410															\n\
																		\n\
layout(location = 0) out vec4 FragColor;								\n\
																		\n\
void main()																\n\
{																		\n\
	FragColor.rgba = vec4(1);											\n\
}																		\n");


static Source stack_shader_frag = string("								\n\
#version 410															\n\
																		\n\
layout(location = 0) out vec4 FragColor;								\n\
uniform vec3 color;														\n\
																		\n\
void main()																\n\
{ 																		\n\
	FragColor.rgb = color;												\n\
	FragColor.a = 1.0f;													\n\
}																		\n");

static Source stack_shader_vert = string("								\n\
#version 410															\n\
																		\n\
uniform mat4 orthoMatrix;												\n\
uniform vec2 bl;	//bottom left										\n\
uniform vec2 tr;	//top right											\n\
																		\n\
void main()																\n\
{																		\n\
	vec2 pos;															\n\
	pos.x = (gl_VertexID == 0 || gl_VertexID == 1) ? bl.x : tr.x;		\n\
	pos.y = (gl_VertexID == 0 || gl_VertexID == 2) ? bl.y : tr.y;		\n\
	gl_Position = orthoMatrix * vec4(pos.x,pos.y,0,1);					\n\
}																		\n");










//-----------------------------------------------------------------------------
//GPUTimings-------------------------------------------------------------------
//-----------------------------------------------------------------------------
GPUTimings::GPUTimings(const string &name, GPUTimings *parent)
{
	timingsMap[name] = this;

	color      = colorTable[colorIndex];
	colorIndex = colorIndex+1 % maxColors;

	active   = true;
	display  = true;
	this->name  = name;
	
	init();

	if(parent)
	{
		parent->add(this);
	}
}
//-----------------------------------------------------------------------------
GPUTimings::GPUTimings(const string &name, Root root)
{
	timingsMap[name] = this;

	parent   = NULL;

	color      = colorTable[colorIndex];
	colorIndex = colorIndex+1 % maxColors;

	active   = true;
	display  = root.val;
	this->name  = name;
	
	init();

	if(root.val)
		rootTimings.push_back(this);
}
//-----------------------------------------------------------------------------
GPUTimings::GPUTimings(const string &name, vec3f color)
{
	timingsMap[name] = this;

	parent   = NULL;
	active   = true;
	display  = true;

	this->name  = name;
	this->color = color;
	
	init();
}
//-----------------------------------------------------------------------------
GPUTimings::GPUTimings(const string &name, Root root, vec3f color)
{
	timingsMap[name] = this;

	parent   = NULL;
	active   = true;
	display  = root.val;

	this->name  = name;
	this->color = color;
	
	init();

	if(root.val)
		rootTimings.push_back(this);
}
//-----------------------------------------------------------------------------
GPUTimings::GPUTimings(const string &name, GPUTimings *parent, vec3f color)
{
	timingsMap[name] = this;

	active   = true;
	display  = true;
	
	this->name   = name;
	this->color  = color;
	this->parent = parent;

	init();
	
	if(parent)
		parent->add(this);
}
//-----------------------------------------------------------------------------
void render::GPUTimings::init()
{
	if(initShaders == false)
	{
		graphShader = new ShaderProgram(new VertShader(graph_shader_vert), new FragShader(graph_shader_frag));
		stackShader = new ShaderProgram(new VertShader(stack_shader_vert), new FragShader(stack_shader_frag));
		lineShader  = new ShaderProgram(new VertShader(line_shader_vert),  new FragShader(line_shader_frag));
		glGenVertexArrays(1, &pointlessVAO);	//another pointless VAO
		initShaders = true;
	}

	glGenQueries(MAX_STACKED_QUERIES, &startQueries[0]);
	glGenQueries(MAX_STACKED_QUERIES, &stopQueries[0]);
	currQueryIndex = 0;

	vector<float> zeros(MAX_TIMING_HISTORY, 0.0f);

	timeBuffer.setData(MAX_TIMING_HISTORY, &zeros[0], GL_DYNAMIC_DRAW);
	currTimingIndex = 0;
	maxTime = 0;
	movingAverage = 0;

	firstIteration = true;
	firstIndex = 0;

	timeBufferObject.addBuffer(&timeBuffer);

	elapsedTime = 0;

}
//-----------------------------------------------------------------------------
void render::GPUTimings::begin()
{
	active = true;
	glQueryCounter(startQueries[currQueryIndex], GL_TIMESTAMP);
}
//-----------------------------------------------------------------------------
void render::GPUTimings::end()
{
	glQueryCounter(stopQueries[currQueryIndex], GL_TIMESTAMP);
	currQueryIndex = (currQueryIndex+1) % MAX_STACKED_QUERIES;
}
//-----------------------------------------------------------------------------
float render::GPUTimings::updatePrivate()
{
	lastActive = active;
	if(active == false)
		return 0.0f;
	active = false;

	if(firstIndex < MAX_STACKED_QUERIES)
	{
		firstIndex++;
		return maxTime;
	}

	GLint  startReady(0), stopReady(0);
	GLuint earliestIndex = (currQueryIndex - MAX_STACKED_QUERIES) % MAX_STACKED_QUERIES;
	glGetQueryObjectiv(startQueries[earliestIndex], GL_QUERY_RESULT_AVAILABLE, &startReady);
	glGetQueryObjectiv( stopQueries[earliestIndex], GL_QUERY_RESULT_AVAILABLE, &stopReady );

	if(startReady && stopReady)
	{
		uint64_t startTime, stopTime;
		glGetQueryObjectui64v(startQueries[earliestIndex], GL_QUERY_RESULT, &startTime);
		glGetQueryObjectui64v( stopQueries[earliestIndex], GL_QUERY_RESULT, &stopTime );

		elapsedTime = float(stopTime - startTime) / 1000000000.0f;	//convert to seconds

		float *timingHistory = timeBuffer.map(GL_READ_WRITE);
		{
			timingHistory[currTimingIndex] = elapsedTime;
			maxTime = std::max<float>(maxTime, elapsedTime);

			size_t oldestIndex = (currTimingIndex - AVERAGED_SAMPLES) % MAX_TIMING_HISTORY;
			float  oldestTime  = timingHistory[oldestIndex];
			
			movingAverage = movingAverage + (-oldestTime + elapsedTime) / AVERAGED_SAMPLES;

			currTimingIndex = (currTimingIndex+1) % MAX_TIMING_HISTORY;
		}
		timeBuffer.unmap();
	}
	else
	{
		cerr << "Query results not available try increasing MAX_STACKED_QUERIES" << endl;
	}
	return maxTime;
}
//-----------------------------------------------------------------------------
void render::GPUTimings::update()
{
	for(auto itr = children.begin(); itr != children.end(); itr++)
	{
		GPUTimings *child = *itr;
		child->update();
	}
	this->updatePrivate();
}
//-----------------------------------------------------------------------------
//void render::GPUTimings::updateAll()
//{
//	for(auto itr = children.begin(); itr != children.end(); itr++)
//	{
//		GPUTimings *child = *itr;
//		child->updateAll();
//	}
//	this->update();
//}

//-----------------------------------------------------------------------------
//Calculate Orthographic Matrix------------------------------------------------
//-----------------------------------------------------------------------------
mat4f render::GPUTimings::calcOrthoMatrix(int appW, int appH, int xMin, int yMin, int xMax, int yMax)
{
	float w = (float)appW;
	float h = (float)appH;

	float l = 0.0f;	//left
	float b = 0.0f;	//bottom
	float n = 1.0f;	//near

	float r = w;	//right
	float t = h;	//top
	float f =-1.0f;	//far

	float inv_dx = 1.0f / (r-l);
	float inv_dy = 1.0f / (t-b);
	float inv_dz = 1.0f / (f-n);

	mat4f orthoMatrix = mat4f( 2*inv_dx,        0,               0,              0,
	                           0,               2*inv_dy,        0,              0,
	                           0,               0,               2*inv_dz,       0,
	                          -1*(r+l)*inv_dx, -1*(t+b)*inv_dy, -1*(f+n)*inv_dz, 1);

	return orthoMatrix;
}
//-----------------------------------------------------------------------------
//Update All Timers *STATIC*---------------------------------------------------
//-----------------------------------------------------------------------------
void render::GPUTimings::updateAll()
{
	for(auto itr = timingsMap.begin(); itr != timingsMap.end(); itr++)
	{
		GPUTimings *timing = itr->second;
		maxTimeAllTimers = std::max<float>(maxTimeAllTimers, timing->updatePrivate());
	}
}
//-----------------------------------------------------------------------------
void render::GPUTimings::render()
{
	if(firstIteration && currTimingIndex < MAX_STACKED_QUERIES)
	{
		return;
	}
	else
	{
		firstIteration = false;
	}

	timeBufferObject.renderArrays(GL_LINE_LOOP, 0, MAX_TIMING_HISTORY);
}
//-----------------------------------------------------------------------------
void render::GPUTimings::add(GPUTimings *child)
{
	children.push_back(child);
	child->parent = this;
}
//*****************************************************************************
//Render Functions*************************************************************
//*****************************************************************************
void GPUTimings::renderGraph(int appW, int appH, int xMin, int yMin, int xMax, int yMax)
{
	float w = (float)appW;
	float h = (float)appH;

	float l = 0.0f;	//left
	float b = 0.0f;	//bottom
	float n = 1.0f;	//near

	float r = w;	//right
	float t = h;	//top
	float f =-1.0f;	//far

	float inv_dx = 1.0f / (r-l);
	float inv_dy = 1.0f / (t-b);
	float inv_dz = 1.0f / (f-n);

	mat4f orthoMatrix = mat4f( 2*inv_dx,        0,               0,              0,
	                           0,               2*inv_dy,        0,              0,
	                           0,               0,               2*inv_dz,       0,
	                          -1*(r+l)*inv_dx, -1*(t+b)*inv_dy, -1*(f+n)*inv_dz, 1);

	float graphW = (float)(xMax - xMin);
	float graphH = (float)(yMax - yMin);

	const float invFPS = 1 / (33.33333333333f / 1000.0f); //33 milliseconds for 30 fps

	float x_inc   = graphW / float(GPUTimings::MAX_TIMING_HISTORY);
	float y_scale = graphH * invFPS;

	vec2f p0(0,0);
	vec2f p1;

	p0.y = graphH*0.5f;
	p1.y = graphH*0.5f;
	p1.x = graphW;

	lineShader->begin();
	lineShader->uniform("orthoMatrix", orthoMatrix);
	lineShader->uniform("p0",   vec2f(     0,graphH*0.5f));
	lineShader->uniform("p1",   vec2f(graphW,graphH*0.5f));
	{
		glBindVertexArray(pointlessVAO);
		glDrawArrays( GL_LINES, 0, 2 );
	}
	lineShader->uniform("p0",   vec2f(     0,graphH));
	lineShader->uniform("p1",   vec2f(graphW,graphH));
	{
		glBindVertexArray(pointlessVAO);
		glDrawArrays( GL_LINES, 0, 2 );
	}
	lineShader->end();


	graphShader->begin();
	graphShader->uniform("orthoMatrix", orthoMatrix);
	graphShader->uniform("yScale", y_scale);
	graphShader->uniform("xInc",   x_inc);
	graphShader->uniform("Max",    (GLuint)GPUTimings::MAX_TIMING_HISTORY);
	graphShader->uniform("color", this->color);
	graphShader->uniform("Index", (GLuint)this->currTimingIndex);
	{
		this->render();
	}


//	for(auto itr = timingSections.begin(); itr != timingSections.end(); itr++)
//	{
//		GPUTimings *timing = itr->second;
//		if(timing->active && timing->display)
//		{
//			graphShader->uniform("color", timing->color);
//			graphShader->uniform("Index", (GLuint)timing->currTimingIndex);
//			timing->render();
//		}
//	}
	graphShader->end();
}
//-----------------------------------------------------------------------------
//Render Stack(s)--------------------------------------------------------------
//-----------------------------------------------------------------------------
void renderStackHelper(GPUTimings *parent, ShaderProgram *stackShader, GLuint vao, vec2f &bl, vec2f &tr, float yScale)
{
	if(parent->display && parent->isActive())
	{
		// update bar height
		tr.y += parent->getAverage() * yScale;

		stackShader->uniform("bl", bl);
		stackShader->uniform("tr", tr);
		stackShader->uniform("color", parent->color);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

//	float parentHeight = tr.y;
//	float parentBase   = bl.y;
	vec2f parentTR = tr;
	vec2f parentBL = bl;
	for(int i = 0; i < parent->numChildren(); i++)
	{
		// Reset top to base of the previous (parent or sibling)
		tr.y = bl.y;

		// Nest sub-stacks (squeeze x-coords)
		bl.x = parentBL.x+2;
		tr.x = parentTR.x-2;

		GPUTimings *child = parent->getChild(i);
		renderStackHelper(child, stackShader, vao, bl, tr, yScale);

		// Set the base to the top of the previous sibling
		bl.y = tr.y;
	}
}
//-----------------------------------------------------------------------------
void render::GPUTimings::renderStack(const mat4f &orthoMatrix, vec2f &bl, vec2f &tr)
{
	float graphH = tr.y; //pull graph height out of tr (super hacky)
	tr.y = 0;			 //reset to zero               (super hacky)


	stackShader->begin();
	stackShader->uniform("orthoMatrix", orthoMatrix);
	{
		// Recursive stack render
		renderStackHelper(this, stackShader, pointlessVAO, bl, tr, invFPS * graphH);
	}
	stackShader->end();
}
//-----------------------------------------------------------------------------
void render::GPUTimings::renderStack(int appW, int appH, int xMin, int yMin, int xMax, int yMax )
{
	float w = (float)appW;
	float h = (float)appH;

	float l = 0.0f;	//left
	float b = 0.0f;	//bottom
	float n = 1.0f;	//near

	float r = w;	//right
	float t = h;	//top
	float f =-1.0f;	//far

	float inv_dx = 1.0f / (r-l);
	float inv_dy = 1.0f / (t-b);
	float inv_dz = 1.0f / (f-n);

	mat4f orthoMatrix = mat4f( 2*inv_dx,        0,               0,              0,
	                           0,               2*inv_dy,        0,              0,
	                           0,               0,               2*inv_dz,       0,
	                          -1*(r+l)*inv_dx, -1*(t+b)*inv_dy, -1*(f+n)*inv_dz, 1);

	float graphW = (float)(xMax - xMin);
	float graphH = (float)(yMax - yMin);

	vec2f bl(xMin,yMin);
	vec2f tr;

	tr.x = bl.x+30;

	stackShader->begin();
	stackShader->uniform("orthoMatrix", orthoMatrix);
	{
		// Recursive stack render
		renderStackHelper(this, stackShader, pointlessVAO, bl, tr, invFPS * graphH);
	}
	stackShader->end();
}
//-----------------------------------------------------------------------------
//Render all Lines (STATIC)----------------------------------------------------
//-----------------------------------------------------------------------------
void render::GPUTimings::renderLines(int appW, int appH, int xMin, int yMin, int xMax, int yMax)
{
	for(auto itr = timingsMap.begin(); itr != timingsMap.end(); itr++)
	{
		GPUTimings *timing = itr->second;
		if(timing->display && timing->lastActive)
			timing->renderGraph(appW, appH, xMin, yMin, xMax, yMax);
	}
}
//-----------------------------------------------------------------------------
//Render all stacks (STATIC)----------------------------------------------------
//-----------------------------------------------------------------------------
void render::GPUTimings::renderStacks(int appW, int appH, int xMin, int yMin, int xMax, int yMax)
{
	vec2f bl( 0, 0);
	vec2f tr(30, (float)(yMax - yMin));

	mat4f orthoMatrix = GPUTimings::calcOrthoMatrix(appW, appH, xMin, yMin, xMax, yMax);

	for(auto itr = rootTimings.begin(); itr != rootTimings.end(); itr++)
	{
		GPUTimings *timing = *itr;
		if(timing->display && timing->lastActive)
			timing->renderStack(orthoMatrix, bl, tr);
	}
}

