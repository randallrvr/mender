//*****************************************************************************
// mender/AppMacOS.mm *********************************************************
//*****************************************************************************
///////////////////////////////////////////////////////////////////////////////

//Header Include
//#include <render/imgui.h>

// Header Include
#include "AppMacOS.h"

// MetalKit Include
#import <MetalKit/MetalKit.h>


using namespace render;

static bool keyState[2][(int)render::Key::LAST];

// Key state pointers
static bool *curr_keyState = keyState[0];
static bool *prev_keyState = keyState[1];

static bool mouseState[2][(int)render::MouseButton::LAST];

// Mouse state pointers
static bool *curr_mouseState = keyState[0];
static bool *prev_mouseState = keyState[1];


///////////////////////////////////////////////////////////////////////////////
@interface MetalView : MTKView
{
@public AppMacOS *app;	// pointer to the app
}
@end


MetalView *metalView;
NSWindow  *metalWindow;

@implementation MetalView

-(void)drawRect:(CGRect)rect
{
	// Call AppBase::step() because we are using Apple's render loop
	app->step();
}

- (BOOL)isOpaque
{
	return YES;
}


- (BOOL)canBecomeKeyView
{
	return YES;
}

- (BOOL)acceptsFirstResponder
{
	return YES;
}


// Mouse //////////////////////////////////////////////////////////////////////
- (void)mouseDown:(NSEvent *)event
{
	curr_mouseState[(int)MouseButton::LEFT] = true;
}

- (void)mouseUp:(NSEvent *)event
{
	curr_mouseState[(int)MouseButton::LEFT] = false;
}

- (void)mouseDragged:(NSEvent *)event
{
	[self mouseMoved:event];
}


- (void)mouseMoved:(NSEvent *)event
{

//	NSPoint mouseLoc = [event mouseLocation];
//
//	float x = mouseLoc.x;
//	float y = mouseLoc.y;
//
//	cerr << x << "< " << y << endl;
}

// Right Mouse ////////////////////////////////////////////////////////////////
- (void)rightMouseDown:(NSEvent *)event
{
	curr_mouseState[(int)MouseButton::RIGHT] = true;
}

- (void)rightMouseUp:(NSEvent *)event
{
	curr_mouseState[(int)MouseButton::RIGHT] = false;
}

- (void)rightMouseDragged:(NSEvent *)event
{
	[self mouseMoved:event];
}


// Other Mouse ////////////////////////////////////////////////////////////////
- (void)otherMouseDown:(NSEvent *)event
{
}

- (void)otherMouseDragged:(NSEvent *)event
{
	[self mouseMoved:event];
}

- (void)otherMouseUp:(NSEvent *)event
{
}

// Mouse Enter/Exit ///////////////////////////////////////////////////////////
- (void)mouseEntered:(NSEvent *)event
{
}

- (void)mouseExited:(NSEvent *)event
{
}

// Keyboard ///////////////////////////////////////////////////////////////////
- (void)keyDown:(NSEvent *)event
{
	const int key = [event keyCode];

}


- (void)keyUp:(NSEvent *)event
{
	const int key = [event keyCode];

}

// Flags //////////////////////////////////////////////////////////////////////
- (void)flagsChanged:(NSEvent *)event
{
}

// Scroll /////////////////////////////////////////////////////////////////////
- (void)scrollWheel:(NSEvent *)event
{
}

@end




//******************************************************************************
//Constructor*******************************************************************
//******************************************************************************
AppMacOS::AppMacOS(const string &title, int width, int height, bool resizable)
{
	//Call system dependent init function
	this->init(title, width, height, resizable);
//	system_init(title.c_str(), width, height);

	//Initialize keyboard state
	curr_keyState = keyState[0];
	prev_keyState = keyState[1];

//	memset(curr_keyState, 0, (int)Key::LAST);
//	memset(prev_keyState, 0, (int)Key::LAST);

	//Initialize mouse button state
	curr_mouseState = mouseState[0];
	prev_mouseState = mouseState[1];

	memset(curr_mouseState, 0, 3);
	memset(prev_mouseState, 0, 3);

}
//******************************************************************************
//Destructor********************************************************************
//******************************************************************************
AppMacOS::~AppMacOS()
{
//	this->kill();
}



//******************************************************************************
//System Initialize*************************************************************
//******************************************************************************
void AppMacOS::system_init(const char *name, unsigned int width, unsigned int height)
{
	// Create Default Metal Device
	mtlDevice = mtlpp::Device::CreateSystemDefaultDevice();

	// Create Rectangle for window
	NSRect frame = NSMakeRect(0, 0, width, height);

	// Create window
	metalWindow = [[NSWindow alloc] initWithContentRect:frame
		styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
		backing:NSBackingStoreBuffered
		defer:NO];

	// Set window title
	metalWindow.title = [[NSProcessInfo processInfo] processName];


	metalView = [[MetalView alloc] initWithFrame:frame];
	metalView->app = this;
	metalView.device                = (__bridge id<MTLDevice>)mtlDevice.GetPtr();
	metalView.autoresizingMask      = NSViewWidthSizable | NSViewHeightSizable;
	metalView.paused                = NO;
	metalView.enableSetNeedsDisplay = NO;


	[metalWindow.contentView addSubview:metalView];
	[metalWindow center];
	[metalWindow orderFrontRegardless];

	metalHandle = ns::Handle{ (__bridge void *)metalView };

	// Create Application
	NSApplication *application = [NSApplication sharedApplication];
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

	[NSApp activateIgnoringOtherApps:YES];
}

//******************************************************************************
//Message polling***************************************************************
//******************************************************************************
void AppMacOS::system_poll()
{
/*
	ImGuiIO& io = ImGui::GetIO();

	glfwPollEvents();
	ImGui_ImplGlfwGL3_NewFrame();

	if(glfwWindowShouldClose(window))
	{
		system_quit();
	}
*/
}
//******************************************************************************
//Swap Buffers******************************************************************
//******************************************************************************
void AppMacOS::system_swap()
{
//	glfwSwapBuffers(window);
}
//******************************************************************************
//Swap Buffers******************************************************************
//******************************************************************************
void AppMacOS::system_quit()
{
/*	glfwTerminate();*/
//	running = false;
}
//******************************************************************************
//Set Window Title**************************************************************
//******************************************************************************
void AppMacOS::system_title(const string &title)
{
/*	glfwSetWindowTitle(window, title.c_str());*/
}
//******************************************************************************
//System Update*****************************************************************
//******************************************************************************
void AppMacOS::system_update()
{

	NSPoint pos = [metalWindow mouseLocationOutsideOfEventStream];
	cerr << "pos: " << pos.x << " " << pos.y << endl;
	
	// Swap keyboard state
	bool *temp_keyState = prev_keyState;
	prev_keyState = curr_keyState;
	curr_keyState = temp_keyState;

	// Swap mouse state
	bool *temp_mouseState = prev_mouseState;
	prev_mouseState = curr_mouseState;
	curr_mouseState = temp_mouseState;

	double mouse_x, mouse_y;
//	glfwGetCursorPos(window, &mouse_x, &mouse_y);

}
//******************************************************************************
// Run *************************************************************************
//******************************************************************************
void AppMacOS::run()
{
	[NSApp run];
//	AppBase::run();
}
//******************************************************************************
//Keyboard State Queries********************************************************
//******************************************************************************
bool AppMacOS::keyDown(Key key) const
{
	return curr_keyState[(int)key];
}
//-----------------------------------------------------------------------------
bool AppMacOS::keyUp(Key key) const
{
	return !curr_keyState[(int)key];
}
//-----------------------------------------------------------------------------
bool AppMacOS::keyPressed(Key key) const
{
	return curr_keyState[(int)key] && !prev_keyState[(int)key];
}
//-----------------------------------------------------------------------------
bool AppMacOS::keyReleased(Key key) const
{
	return !curr_keyState[(int)key] && prev_keyState[(int)key];
}
//******************************************************************************
//MouseButton State Queries*****************************************************
//******************************************************************************
bool AppMacOS::mouseDown(MouseButton button) const
{
	return curr_mouseState[(int)button];
}
//-----------------------------------------------------------------------------
bool AppMacOS::mouseUp(MouseButton button) const
{
	return !curr_mouseState[(int)button];
}
//-----------------------------------------------------------------------------
bool AppMacOS::mousePressed(MouseButton button) const
{
	return curr_mouseState[(int)button] && !prev_keyState[(int)button];
}
//-----------------------------------------------------------------------------
bool AppMacOS::mouseReleased(MouseButton button) const
{
	return !curr_mouseState[(int)button] && prev_keyState[(int)button];
}


void AppMacOS::setRender(void (*renderFunc)(const AppMacOS &) )
{
//	viewController->m_render = renderFunc;
}


mtlpp::Drawable AppMacOS::GetDrawable() const
{
	return ns::Handle{ (__bridge void*)((__bridge MTKView*)metalHandle.GetPtr()).currentDrawable };
}



mtlpp::RenderPassDescriptor AppMacOS::GetRenderPassDescriptor() const
{
	return ns::Handle{ (__bridge void*)((__bridge MTKView*)metalHandle.GetPtr()).currentRenderPassDescriptor };
}
