//*****************************************************************************
// mender/AppMacOS.mm *********************************************************
//*****************************************************************************

//Header Include
//#include <render/imgui.h>

// Header Include
#include "AppMacOS.h"

// MetalKit Include
#import <MetalKit/MetalKit.h>


using namespace render;

void Render(const AppMacOS &win)
{
}


@interface AppViewController : NSViewController<MTKViewDelegate>
{
	@public void (*m_render)(const AppMacOS &);	// Render function
	@public const AppMacOS *m_app;				// Window
}
@end

@implementation AppViewController
-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{

}

-(void)drawInMTKView:(nonnull MTKView *)view
{
	(*m_render)(*m_app);
}
@end



static bool keyState[2][(int)render::Key::LAST];

// Key state pointers
static bool *curr_keyState = keyState[0];
static bool *prev_keyState = keyState[1];

static bool mouseState[2][(int)render::MouseButton::LAST];

// Mouse state pointers
static bool *curr_mouseState = keyState[0];
static bool *prev_mouseState = keyState[1];


//******************************************************************************
//Constructor*******************************************************************
//******************************************************************************
AppMacOS::AppMacOS(const string &title, int width, int height, bool resizable)
{
	//Call system dependent init function
//	this->init(title, width, height, resizable);
	system_init(title.c_str(), width, height);

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
	NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
		styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
		backing:NSBackingStoreBuffered
		defer:NO];

	// Set window title
	window.title = [[NSProcessInfo processInfo] processName];


	// Create Window View Controller
	AppViewController *viewController = [AppViewController new];
	viewController->m_render = Render;
	viewController->m_app    = this;

	// Create Metal Kit View
	MTKView *view = [[MTKView alloc] initWithFrame:frame];
	view.device   = (__bridge id<MTLDevice>)mtlDevice.GetPtr();
	view.delegate = viewController;
	view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;

	[window.contentView addSubview:view];
	[window center];
	[window orderFrontRegardless];


	mtlView = ns::Handle{ (__bridge void*)view };

	// Create Application
	NSApplication *application = [NSApplication sharedApplication];
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

	[NSApp activateIgnoringOtherApps:YES];
	[NSApp run];


//	NSWindow *window = new NSWindow(frame,
//	styleMask(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
//	NSBackingStoreBuffered
//	NO);


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
	// Swap keyboard state
	bool *temp_keyState = prev_keyState;
	prev_keyState = curr_keyState;
	curr_keyState = temp_keyState;

	//Update keystate
//	for(int i = 0; i < (int)Key::LAST; i++)
//	{
//		/*
//		curr_keyState[i] = glfwGetKey(window, i) != GLFW_RELEASE;
//		 */
//	}

	// Swap mouse state
	bool *temp_mouseState = prev_mouseState;
	prev_mouseState = curr_mouseState;
	curr_mouseState = temp_mouseState;
//
//	//Update mouse state
//	curr_mouseState[(int)MouseButton::LEFT]  ;// = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)   != GLFW_RELEASE;
//	curr_mouseState[(int)MouseButton::MIDDLE];// = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) != GLFW_RELEASE;
//	curr_mouseState[(int)MouseButton::RIGHT] ;// = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)  != GLFW_RELEASE;
//
	double mouse_x, mouse_y;
//	glfwGetCursorPos(window, &mouse_x, &mouse_y);

}
//******************************************************************************
//Keyboard State Queries********************************************************
//******************************************************************************
//bool AppMacOS::keyDown(Key key) const
//{
//	return curr_keyState[(int)key];
//}
////-----------------------------------------------------------------------------
//bool AppMacOS::keyUp(Key key) const
//{
//	return !curr_keyState[(int)key];
//}
////-----------------------------------------------------------------------------
//bool AppMacOS::keyPressed(Key key) const
//{
//	return curr_keyState[(int)key] && !prev_keyState[(int)key];
//}
////-----------------------------------------------------------------------------
//bool AppMacOS::keyReleased(Key key) const
//{
//	return !curr_keyState[(int)key] && prev_keyState[(int)key];
//}
////******************************************************************************
////MouseButton State Queries*****************************************************
////******************************************************************************
//bool AppMacOS::mouseDown(MouseButton button) const
//{
//	return curr_mouseState[(int)button];
//}
////-----------------------------------------------------------------------------
//bool AppMacOS::mouseUp(MouseButton button) const
//{
//	return !curr_mouseState[(int)button];
//}
////-----------------------------------------------------------------------------
//bool AppMacOS::mousePressed(MouseButton button) const
//{
//	return curr_mouseState[(int)button] && !prev_keyState[(int)button];
//}
////-----------------------------------------------------------------------------
//bool AppMacOS::mouseReleased(MouseButton button) const
//{
//	return !curr_mouseState[(int)button] && prev_keyState[(int)button];
//}