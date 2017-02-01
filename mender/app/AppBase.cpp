//*****************************************************************************
//render/AppBase.cpp************************************************************
//*****************************************************************************

//Header Include
#include "AppBase.h"

//Render Library Include
//#include <render/system.h>
//#include <render/gl.h>


#include <algorithm>
#include <sstream>

//Namespaces
using namespace render;
//using namespace gl;

FILE *ffmpeg;

//******************************************************************************
//Constructor*******************************************************************
//******************************************************************************
//AppBase::AppBase(const string &title, int width, int height, bool resizable)
//{
//	this->init(title, width, height, resizable);
////	this->title(title);
//}
//******************************************************************************
//Initialize********************************************************************
//******************************************************************************
void AppBase::init(const string &title, int width, int height, bool resizable)
{
	w = width;
	h = height;


	running   = true;
	paused    = false;
	focus     = true;
	highDPI   = false;

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	system_init(title.c_str(), w, h);



	//Initialize OpenGL
	this->init_gl();


#if 0
	// start ffmpeg telling it to expect raw rgba 720p-60hz frames
	// -i - tells it to read frames from stdin

	std::stringstream cmdStream;

	cmdStream << "ffmpeg -re -f rawvideo -pix_fmt rgba -s " << width << "x" << height << " -i - -threads 0 -preset fast -y -crf 21 -vf vflip output.mp4";

	// open pipe to ffmpeg's stdin in binary write mode
	ffmpeg = _popen(cmdStream.str().c_str(), "wb");

	buffer = new int[width*height];
#endif
}
//******************************************************************************
//OpenGL Initialization*********************************************************
//******************************************************************************
void AppBase::init_gl()
{
/*
	//Face Culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//Z-Buffering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);

	//Set the clear color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	//Enable blending
	glEnable(GL_BLEND);

	//Set blend function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Set blending function to nicest
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	//Enable line smoothing
	glEnable(GL_LINE_SMOOTH);

	//Enable point smoothing
	glEnable(GL_POINT_SMOOTH);

	//Enable normalization
	glEnable(GL_NORMALIZE);

	//Set Point Size
	glPointSize(10);

	//Set filled polygon mode as default (not wireframe)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

//	timer = new GPUTimings("All", Root(false));	// not explicitly included in list of timers
 */
}
//******************************************************************************
//Run***************************************************************************
//******************************************************************************
void AppBase::run()
{
	while(running && !paused)
	{
	//	timer->begin();
		{
			system_poll();
			system_update();
			step();
			swap();
		}
	//	timer->end();
	//	timer->update();
	//	GPUTimings::updateAll();
	//	cerr << "dt: " << timer->time() << endl;
	}
}
//******************************************************************************
//Step**************************************************************************
//******************************************************************************
void AppBase::step()
{
	update();
	render();	//call virtual functions (implemented in subclass)
}
//******************************************************************************
//Resize OpenGL*****************************************************************
//******************************************************************************
void AppBase::resize_gl(int w, int h)
{
	//Prevent a divide by zero error
	h = (h == 0) ? 1 : h;

//    cerr << "resize" << endl;

/*	//Set the viewport size
	glViewport(0, 0, w, h);

	//Select the projection matrix
	glMatrixMode(GL_PROJECTION);

	//Reset the projection matrix
	glLoadIdentity();
*/
	float aspect     = (float)w/(float)h;
	float fov        =   45.0f;
	float near_plane =    0.01f;
	float far_plane  = 1000.0f;
	
	float y_max =  near_plane * tan(fov * 3.14159265358979323846f / 360.0f);
	float y_min = -y_max;
	float x_min =  y_min * aspect;
	float x_max =  y_max * aspect;

/*
	glFrustum(x_min, x_max, y_min, y_max, near_plane, far_plane);

//	mat4f proj;
//	glGetFloatv(GL_PROJECTION_MATRIX, proj);
//	cerr << proj << endl;

	//Select the modelview matrix
	glMatrixMode(GL_MODELVIEW);

	//Reset the modelview matrix
	glLoadIdentity();
 */
}
//******************************************************************************
//Time**************************************************************************
//******************************************************************************
double AppBase::dt()
{
//	return timer->time();
	return 0.0001;
}
//******************************************************************************
//Swap**************************************************************************
//******************************************************************************
void AppBase::swap()
{
#if 0
	glReadPixels(0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	fwrite(buffer, sizeof(int)*_width*_height, sizeof(buffer), ffmpeg);
#endif
	system_swap();
}
//******************************************************************************
//Get/Set Title*****************************************************************
//******************************************************************************
string AppBase::title()
{
	return(_title);
}
//------------------------------------------------------------------------------
void AppBase::title(const string &title)
{
	_title = title;

	system_title(title);
}
