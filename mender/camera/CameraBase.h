//******************************************************************************
//render/camera/CameraBase.h****************************************************
//******************************************************************************

#pragma once

#define VELOCITY_DAMPING 0.01

//Render Library Includes
#include <render/math.h>

namespace render
{

class CameraBase
{
public:
	vec3f _pos;		//Where you are
	vec3f _up;		//"Up" vector
	vec3f _dir;		//Direction Looking "at" (relative to position)

protected:

	//Increment Amount & Current Amount
	float _yaw,      _curr_yaw;
	float _roll,     _curr_roll;
	float _pitch,    _curr_pitch;
	float _strafe,   _curr_strafe;
	float _velocity, _curr_velocity;

public:
	//Constructors
	CameraBase();
	
	//Destructor
	virtual ~CameraBase();
	
	void update();
//	mat4<float> render();

	void render(vec3f &, vec3f &, vec3f &);
	
	void yaw(float);
	void roll(float);
	void pitch(float);
	void strafe(float);
	void velocity(float);

	//Yaw Left/Right
	void yaw_left(float, float = 1.0f);
	void yaw_right(float, float = 1.0f);

	//Roll Left/Right
	void roll_left(float, float = 1.0f);
	void roll_right(float, float = 1.0f);

	//Pitch Up/Down
	void pitch_up(float, float = 1.0f);
	void pitch_down(float, float = 1.0f);

	//Strafe Left/Right
	void strafe_left(float, float = 1.0f);
	void strafe_right(float, float = 1.0f);

	//Forward/Back
	void forward(float, float = 1.0f);
	void back(float, float = 1.0f);

	//Rotate
	void rotate(const vec3f &);

	//Emergency Stop
	void stop();

	void pos(const vec3f &);
	void dir(const vec3f &);

	void setPosDirUp(const vec3f &pos, const vec3f &dir, const vec3f &up);

	vec3f &pos() { return(_pos); }
	vec3f &dir() { return(_dir); }
	vec3f &up()  { return(_up);  }
};
//End class CameraBase


};
//End namespace render


