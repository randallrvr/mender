//*****************************************************************************
//render/AppGLFW.cpp***********************************************************
//*****************************************************************************

//Header Include
//#include <render/imgui.h>
#include "AppMacOS.h"

static bool keyState[2][(int)render::Key::LAST];

// Key state pointers
static bool *curr_keyState = keyState[0];
static bool *prev_keyState = keyState[1];

static bool mouseState[2][(int)render::MouseButton::LAST];

// Mouse state pointers
static bool *curr_mouseState = keyState[0];
static bool *prev_mouseState = keyState[1];

// GLFW callbacks to get events
static void glfw_error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
/*
static void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {}
static void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}
static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {}
*/

static bool  glfw_highDPI;
static int   glfw_w;
static int   glfw_h;
static int   glfw_fw;
static int   glfw_fh;
static float glfw_sw;
static float glfw_sh;

/*
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetWindowSize(window, &glfw_w, &glfw_h);
	glfwGetFramebufferSize(window, &glfw_fw, &glfw_fh);

	glfw_highDPI = (glfw_w != glfw_fw && glfw_h != glfw_fh);

	cerr << glfw_w << " " << glfw_h << " : " << glfw_fw << " " << glfw_fh << endl;

	if(glfw_highDPI)
	{
		glfw_sw = glfw_fw / glfw_w;
		glfw_sh = glfw_fh / glfw_h;

		glfw_w = glfw_fw;
		glfw_h = glfw_fh;
	}
	else
	{
		glfw_sw = 1.0f;
		glfw_sh = 1.0f;
	}

	cerr << glfw_w << " " << glfw_h << " : " << glfw_fw << " " << glfw_fh << endl;

//	imguiSetScaleForHighDPI(glfw_sw, glfw_sh);

	glViewport(0, 0, glfw_w, glfw_h);

}
*/
//******************************************************************************
//Constructor*******************************************************************
//******************************************************************************
render::AppMacOS::AppMacOS(const string &title, int width, int height, bool resizable)
{
	//Call system dependent init function
	this->init(title, width, height, resizable);

	//Initialize keyboard state
	curr_keyState = keyState[0];
	prev_keyState = keyState[1];

	memset(curr_keyState, 0, (int)Key::LAST);
	memset(prev_keyState, 0, (int)Key::LAST);

	//Initialize mouse button state
	curr_mouseState = mouseState[0];
	prev_mouseState = mouseState[1];

	memset(curr_mouseState, 0, 3);
	memset(prev_mouseState, 0, 3);
}
//******************************************************************************
//Destructor********************************************************************
//******************************************************************************
render::AppMacOS::~AppMacOS()
{
	this->kill();
}



//******************************************************************************
//System Initialize*************************************************************
//******************************************************************************
void render::AppMacOS::system_init(const char *name, unsigned int width, unsigned int height)
{
/*
	if (!glfwInit())
		exit(1);

	GLint majorVersion = 4;
	GLint minorVersion = 1;

//	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion); // major = 3
//	glGetIntegerv(GL_MINOR_VERSION, &minorVersion); // minor = 2

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(width, height, name, NULL, NULL);

//	glfwSetInputMode(window, GLFW_STICKY_KEYS,          GL_TRUE);
//	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);

	glfwGetWindowSize(window, &w, &h);
	glfwGetFramebufferSize(window, &fw, &fh);
*/
	highDPI = (w != fw && h != fh);

	if(highDPI)
	{
		sw = fw / w;
		sh = fh / h;

		w = fw;
		h = fh;
	}
	else
	{
		sw = 1.0f;
		sh = 1.0f;
	}
/*
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, glfw_key_callback);
	glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
	glfwSetScrollCallback(window, glfw_scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	framebuffer_size_callback(window, fw, fh);

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		cerr << "Error: " << glewGetErrorString(err) << endl;
	}


	// Setup ImGui binding
	ImGui_ImplGlfwGL3_Init(window, true);
*/
//	glfwSetCharCallback(window, glfw_char_callback);

//	GLenum err = glewInit();
//	if (GLEW_OK != err)
//		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));



}

//******************************************************************************
//Message polling***************************************************************
//******************************************************************************
void render::AppMacOS::system_poll()
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
void render::AppMacOS::system_swap()
{
//	glfwSwapBuffers(window);
}
//******************************************************************************
//Swap Buffers******************************************************************
//******************************************************************************
void render::AppMacOS::system_quit()
{
/*	glfwTerminate();*/
	running = false;
}
//******************************************************************************
//Set Window Title**************************************************************
//******************************************************************************
void render::AppMacOS::system_title(const string &title)
{
/*	glfwSetWindowTitle(window, title.c_str());*/
}
//******************************************************************************
//System Update*****************************************************************
//******************************************************************************
void render::AppMacOS::system_update()
{
	highDPI = glfw_highDPI;
	w  = glfw_w;
	h  = glfw_h;
	fw = glfw_fw;
	fh = glfw_fh;
	sw = glfw_sw;
	sh = glfw_sh;

	px = mx;	// prev (x,y)
	py = my;	// prev (x,y)

	// Swap keyboard state
	bool *temp_keyState = prev_keyState;
	prev_keyState = curr_keyState;
	curr_keyState = temp_keyState;

	//Update keystate
	for(int i = 0; i < (int)Key::LAST; i++)
	{
		/*
		curr_keyState[i] = glfwGetKey(window, i) != GLFW_RELEASE;
		 */
	}

	// Swap mouse state
	bool *temp_mouseState = prev_mouseState;
	prev_mouseState = curr_mouseState;
	curr_mouseState = temp_mouseState;

	//Update mouse state
	curr_mouseState[(int)MouseButton::LEFT]  ;// = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)   != GLFW_RELEASE;
	curr_mouseState[(int)MouseButton::MIDDLE];// = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) != GLFW_RELEASE;
	curr_mouseState[(int)MouseButton::RIGHT] ;// = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)  != GLFW_RELEASE;

	double mouse_x, mouse_y;
//	glfwGetCursorPos(window, &mouse_x, &mouse_y);

	if(highDPI)
	{
		mouse_x *= sw;
		mouse_y *= sh;
	}

	mx = (int)round(mouse_x);
	my = (int)round(mouse_y);

	// Screen Normalized deltas
	dx = (float)(mx - px) / w;
	dy = (float)(my - py) / h;

	mousemove();
}
//******************************************************************************
//Keyboard State Queries********************************************************
//******************************************************************************
bool render::AppMacOS::keyDown(Key key) const
{
	return curr_keyState[(int)key];
}
//-----------------------------------------------------------------------------
bool render::AppMacOS::keyUp(Key key) const
{
	return !curr_keyState[(int)key];
}
//-----------------------------------------------------------------------------
bool render::AppMacOS::keyPressed(Key key) const
{
	return curr_keyState[(int)key] && !prev_keyState[(int)key];
}
//-----------------------------------------------------------------------------
bool render::AppMacOS::keyReleased(Key key) const
{
	return !curr_keyState[(int)key] && prev_keyState[(int)key];
}
//******************************************************************************
//MouseButton State Queries*****************************************************
//******************************************************************************
bool render::AppMacOS::mouseDown(MouseButton button) const
{
	return curr_mouseState[(int)button];
}
//-----------------------------------------------------------------------------
bool render::AppMacOS::mouseUp(MouseButton button) const
{
	return !curr_mouseState[(int)button];
}
//-----------------------------------------------------------------------------
bool render::AppMacOS::mousePressed(MouseButton button) const
{
	return curr_mouseState[(int)button] && !prev_keyState[(int)button];
}
//-----------------------------------------------------------------------------
bool render::AppMacOS::mouseReleased(MouseButton button) const
{
	return !curr_mouseState[(int)button] && prev_keyState[(int)button];
}