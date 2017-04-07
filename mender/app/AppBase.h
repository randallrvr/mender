//******************************************************************************
//render/gl/App.h***************************************************************
//******************************************************************************

#pragma once

//Render Library Includes
#include <mender/math.h>
//#include <mender/time.h>
//#include <mender/gl.h>

//Standard Library Includes
#include <iostream>
#include <vector>

//Namespaces
using namespace std;

namespace render
{

enum class Key
{

	NUM_0        = 0,//= GLFW_KEY_0,
	NUM_1           ,//= GLFW_KEY_1,
	NUM_2           ,//= GLFW_KEY_2,
	NUM_3           ,//= GLFW_KEY_3,
	NUM_4           ,//= GLFW_KEY_4,
	NUM_5           ,//= GLFW_KEY_5,
	NUM_6           ,//= GLFW_KEY_6,
	NUM_7           ,//= GLFW_KEY_7,
	NUM_8           ,//= GLFW_KEY_8,
	NUM_9           ,//= GLFW_KEY_9,
	A               ,//= GLFW_KEY_A,
	B               ,//= GLFW_KEY_B,
	C               ,//= GLFW_KEY_C,
	D               ,//= GLFW_KEY_D,
	E               ,//= GLFW_KEY_E,
	F               ,//= GLFW_KEY_F,
	G               ,//= GLFW_KEY_G,
	H               ,//= GLFW_KEY_H,
	I               ,//= GLFW_KEY_I,
	J               ,//= GLFW_KEY_J,
	K               ,//= GLFW_KEY_K,
	L               ,//= GLFW_KEY_L,
	M               ,//= GLFW_KEY_M,
	N               ,//= GLFW_KEY_N,
	O               ,//= GLFW_KEY_O,
	P               ,//= GLFW_KEY_P,
	Q               ,//= GLFW_KEY_Q,
	R               ,//= GLFW_KEY_R,
	S               ,//= GLFW_KEY_S,
	T               ,//= GLFW_KEY_T,
	U               ,//= GLFW_KEY_U,
	V               ,//= GLFW_KEY_V,
	W               ,//= GLFW_KEY_W,
	X               ,//= GLFW_KEY_X,
	Y               ,//= GLFW_KEY_Y,
	Z               ,//= GLFW_KEY_Z,
	F1              ,//= GLFW_KEY_F1,
	F2              ,//= GLFW_KEY_F2,
	F3              ,//= GLFW_KEY_F3,
	F4              ,//= GLFW_KEY_F4,
	F5              ,//= GLFW_KEY_F5,
	F6              ,//= GLFW_KEY_F6,
	F7              ,//= GLFW_KEY_F7,
	F8              ,//= GLFW_KEY_F8,
	F9              ,//= GLFW_KEY_F9,
	F10             ,//= GLFW_KEY_F10,
	F11             ,//= GLFW_KEY_F11,
	F12             ,//= GLFW_KEY_F12,
	BACKSPACE       ,//= GLFW_KEY_BACKSPACE,
	TAB             ,//= GLFW_KEY_TAB,
	ENTER           ,//= GLFW_KEY_ENTER,
	CAPSLOCK        ,//= GLFW_KEY_CAPS_LOCK,
	ESCAPE          ,//= GLFW_KEY_ESCAPE,
	SPACE           ,//= GLFW_KEY_SPACE,
	SEMICOLON       ,//= GLFW_KEY_SEMICOLON,
	ADD             ,//= GLFW_KEY_EQUAL,
	COMMA           ,//= GLFW_KEY_COMMA,
	SUBTRACT        ,//= GLFW_KEY_MINUS,
	PERIOD          ,//= GLFW_KEY_PERIOD,
	FWDSLASH        ,//= GLFW_KEY_SLASH,
	TILDE           ,//= GLFW_KEY_GRAVE_ACCENT,
	LBRACKET        ,//= GLFW_KEY_LEFT_BRACKET,
	RBRACKET        ,//= GLFW_KEY_RIGHT_BRACKET,
	BACKSLASH       ,//= GLFW_KEY_BACKSLASH,
	APOSTROPHE      ,//= GLFW_KEY_APOSTROPHE,
	LSHIFT          ,//= GLFW_KEY_LEFT_SHIFT,
	RSHIFT          ,//= GLFW_KEY_RIGHT_SHIFT,
	LCTRL           ,//= GLFW_KEY_LEFT_CONTROL,
	RCTRL           ,//= GLFW_KEY_RIGHT_CONTROL,
	LSPECIAL        ,//= GLFW_KEY_LEFT_SUPER,
	RSPECIAL        ,//= GLFW_KEY_RIGHT_SUPER,
	LALT            ,//= GLFW_KEY_LEFT_ALT,
	RALT            ,//= GLFW_KEY_RIGHT_ALT,
	INSERT          ,//= GLFW_KEY_INSERT,
	DELETE          ,//= GLFW_KEY_DELETE,
	HOME            ,//= GLFW_KEY_HOME,
	END             ,//= GLFW_KEY_END,
	PAGEUP          ,//= GLFW_KEY_PAGE_UP,
	PAGEDOWN        ,//= GLFW_KEY_PAGE_DOWN,
	UP              ,//= GLFW_KEY_UP,
	DOWN            ,//= GLFW_KEY_DOWN,
	RIGHT           ,//= GLFW_KEY_RIGHT,
	LEFT            ,//= GLFW_KEY_LEFT,
	NUMLOCK         ,//= GLFW_KEY_NUM_LOCK,
	NUMPAD_DIVIDE   ,//= GLFW_KEY_KP_DIVIDE,
	NUMPAD_MULTIPLY ,//= GLFW_KEY_KP_MULTIPLY,
	NUMPAD_SUBTRACT ,//= GLFW_KEY_KP_SUBTRACT,
	NUMPAD_ADD      ,//= GLFW_KEY_KP_ADD,
	NUMPAD_DECIMAL  ,//= GLFW_KEY_KP_DECIMAL,
	NUMPAD_0        ,//= GLFW_KEY_KP_0,
	NUMPAD_1        ,//= GLFW_KEY_KP_1,
	NUMPAD_2        ,//= GLFW_KEY_KP_2,
	NUMPAD_3        ,//= GLFW_KEY_KP_3,
	NUMPAD_4        ,//= GLFW_KEY_KP_4,
	NUMPAD_5        ,//= GLFW_KEY_KP_5,
	NUMPAD_6        ,//= GLFW_KEY_KP_6,
	NUMPAD_7        ,//= GLFW_KEY_KP_7,
	NUMPAD_8        ,//= GLFW_KEY_KP_8,
	NUMPAD_9        ,//= GLFW_KEY_KP_9,
	MENU            ,//= GLFW_KEY_MENU,
	LAST            ,//= GLFW_KEY_MENU+1,

};
enum class MouseButton : int
{
	LEFT   = 0,
	RIGHT  = 1,
	MIDDLE = 2,
	LAST   = 3,
};

class AppBase
{
protected:

	bool running;
	bool paused;

//	GPUTimings *timer;

	string _title;

public:

	bool highDPI;
	bool focus;	//True if window has focus

	int   w,  h;			// window dim (w,h)
	int   fw, fh;			// frame buffer dim (w, h);
	int   px, py;			// prev mouse (x,y)
	int   mx, my;			// curr mouse (x,y)
	float sw, sh;			// scale for highDPI (fw,fh) / (w,h)
	float dx, dy;			// delta curr-prev (x,y) / (w, h)

public:

	//Virtual event functions to be overloaded
	virtual void keyEvent()		{}
	virtual void mousedown()	{}
	virtual void mouseup()		{}
	virtual void mousewheel()	{}
	virtual void mousemove()	{}
	virtual void resize()		{}

public:

	//Run
	void run();

	//Step
	void step();

	//Initialize to avoid duplicating code in constructors
	void init(const string &, int, int, bool);

	//OpenGL Initialize
	void init_gl();

	//Resize OpenGL
	void resize_gl(int, int);

	//Virtual functions
	virtual void update()	{}			//Update
	virtual void render()	{}			//Render
	virtual void kill()		{}			//Kill

	double dt();

	void swap();

	//Get/Set Title
	string title(              );
	void   title(const string &);

	void quit() { running = false; }

	int width()  { return highDPI ? fw : w; }
	int height() { return highDPI ? fh : h; }


	virtual void system_init(const char *, unsigned int, unsigned int) = 0;
	virtual void system_poll()                                         = 0;
	virtual void system_swap()                                         = 0;
	virtual void system_quit()                                         = 0;
	virtual void system_title(const string &title)                     = 0;
	virtual void system_update()                                       = 0;

	//Keyboard functions
	virtual bool keyDown(Key key) const     = 0;
	virtual bool keyUp(Key key) const       = 0;
	virtual bool keyPressed(Key key) const  = 0;
	virtual bool keyReleased(Key key) const = 0;

	virtual bool       mouseUp(MouseButton button) const = 0;
	virtual bool     mouseDown(MouseButton button) const = 0;
	virtual bool  mousePressed(MouseButton button) const = 0;
	virtual bool mouseReleased(MouseButton button) const = 0;
};
// End class AppBase

};
// End namespace render
