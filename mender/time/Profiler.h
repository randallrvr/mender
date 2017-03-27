//*****************************************************************************
//render/time/Profiler.h*******************************************************
//*****************************************************************************

#pragma once


//Standard Library Includes
#include <cassert>
#include <cstdint>
#include <vector>
#include <map>

#include <render/buffer.h>
#include <render/math.h>
#include <render/gl.h>

//Local Includes
//#include "glTimerAsynch.h"

//Namespaces
using namespace std;
using namespace render::buffer;


namespace render
{

class ShaderProgram;

struct Root
{
	bool val;
	Root(bool val_) : val(val_) {}
};

class GPUTimings
{
private:
	typedef ArrayBufferT<vec2f> PointBuffer;
	typedef ArrayBufferT<float> TimeBuffer;

	static bool initShaders;
	static ShaderProgram *graphShader;
	static ShaderProgram *stackShader;
	static ShaderProgram *lineShader;
	static GLuint pointlessVAO;

private:

	       GPUTimings *  parent;
	vector<GPUTimings *> children;

public:
	void add(GPUTimings *child);

	static map<string, GPUTimings *> timingsMap;
	static vector<GPUTimings *>      rootTimings;

	static const size_t MAX_STACKED_QUERIES = 16;
	static const size_t MAX_TIMING_HISTORY  = 512;
	static const size_t AVERAGED_SAMPLES    = 128;

	static       int colorIndex;
	static const int maxColors  = 26;
	static vec3f colorTable[maxColors];
	static float maxTimeAllTimers;

	GLuint startQueries[MAX_STACKED_QUERIES];
	GLuint stopQueries[MAX_STACKED_QUERIES];
	GLuint currQueryIndex;

	size_t currTimingIndex;
	float maxTime;

	float movingAverage;

	bool   firstIteration;
	size_t firstIndex;
	
	string name;

	vec3f color;

private:
	TimeBuffer   timeBuffer;
	BufferObject timeBufferObject;

	float elapsedTime;

	void init();

	static mat4f calcOrthoMatrix(int appW, int appH, int xMin, int yMin, int xMax, int yMax);

	void renderStack(const mat4f &orthoMatrix, vec2f &bl, vec2f &tr);


public:
	bool display;
private:
	bool active;
	bool lastActive;

	float updatePrivate();
public:

	GPUTimings(const string &name, GPUTimings *parent = NULL);
	GPUTimings(const string &name, Root root = false);
	GPUTimings(const string &name, vec3f color);
	GPUTimings(const string &name, Root root, vec3f color);
	GPUTimings(const string &name, GPUTimings *parent, vec3f color);

	void begin();
	void end();

	bool        hasChildren()   { return children.size() > 0; }
	int         numChildren()   { return (int)children.size(); }
	GPUTimings *getChild(int i) { return children[i]; }
	vec3f       getColor()      { return color; }

	static void updateAll();
	       void update();
//	       float update();
//	       void  updateAll();

	void render();

	bool isActive()     { return lastActive; }

	float time()        { return elapsedTime; }

	float getAverage()  { return movingAverage;	}
	float getMax()      { return maxTime;		}

	void renderGraph(int appW, int appH, int xMin, int yMin, int xMax, int yMax);
	void renderStack(int appW, int appH, int xMin, int yMin, int xMax, int yMax);

	static void renderStacks(int appW, int appH, int xMin, int yMin, int xMax, int yMax);
	static void renderLines(int appW, int appH, int xMin, int yMin, int xMax, int yMax);
};
// End class Timings

};
// End namespace render
