//******************************************************************************
//render/AppMacOS.h*************************************************************
//******************************************************************************

#pragma once

// Mender Library Includes
#include <mender/math.h>

// Metal Include
#include <mtlpp/mtlpp.hpp>

//Standard Library Includes
#include <iostream>
#include <vector>

//Parent Include
#include "AppBase.h"

//Namespaces
using namespace std;

namespace render
{

class AppMacOS //: public AppBase
{
private:
//	GLFWwindow *window;

private:

	// Metal View Class
	class MtlView : public ns::Object
	{
	public:
		MtlView() { }
		MtlView(const ns::Handle& handle) : ns::Object(handle) { }
	};

	MtlView mtlView;

	// Create Metal device
	mtlpp::Device mtlDevice;

//	class WindowViewController : NSViewController<MTKViewDelegate>
//	{
//	@public void (*m_render)(const Window&);	// Render function
//	@public const render::AppMacOS::Window* m_window;				// Window
//	}


public:
	// Constructor
    AppMacOS(const string &title, int w, int h, bool resizable = false);

	// Destructor
   ~AppMacOS();

protected:

	void system_init(const char *, unsigned int, unsigned int);
	void system_poll();
	void system_swap();
	void system_quit();
	void system_title(const string &title);
	void system_update();

//	bool keyDown(Key key) const;
//	bool keyUp(Key key) const;
//	bool keyPressed(Key key) const;
//	bool keyReleased(Key key) const;
//
//	bool mouseDown(MouseButton button) const;
//	bool mouseUp(MouseButton button) const;
//	bool mousePressed(MouseButton button) const;
//	bool mouseReleased(MouseButton button) const;
};
// End class AppMacOS

};
// End namespace render
