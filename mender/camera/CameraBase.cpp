//******************************************************************************
//render/camera/CameraBase.cpp**************************************************
//******************************************************************************

#include "CameraBase.h"


//#include <glm/glm.hpp>
//#include <glm/gtx/quaternion.hpp>

using namespace std;
//using namespace glm;

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
render::CameraBase::CameraBase()
{
	_up  = vec3f( 0,  1,  0);
	_dir = vec3f( 0,  0, -1);
	_pos = vec3f( 0,  0,  1);

	_yaw      = 1;
	_roll     = 1;
	_pitch    = 1;
	_strafe   = 1;
	_velocity = 1;

	_curr_yaw      = 0;
	_curr_roll     = 0;
	_curr_pitch    = 0;
	_curr_strafe   = 0;
	_curr_velocity = 0;
}
//******************************************************************************
//Destructor********************************************************************
//******************************************************************************
render::CameraBase::~CameraBase() 
{
}
//******************************************************************************
//Set yaw, pitch, roll, and velocity********************************************
//******************************************************************************
void render::CameraBase::yaw(float angle)
{
	_yaw = angle;
}
//------------------------------------------------------------------------------
void render::CameraBase::pitch(float angle)
{
	_pitch = angle;
}
//------------------------------------------------------------------------------
void render::CameraBase::roll(float angle)
{
	_roll = angle;
}
//------------------------------------------------------------------------------
void render::CameraBase::strafe(float strafe)
{
	_strafe = strafe;
}
//------------------------------------------------------------------------------
void render::CameraBase::velocity(float velocity)
{
	_velocity = velocity;
}
//******************************************************************************
//Stop**************************************************************************
//******************************************************************************
void render::CameraBase::stop()
{
	_curr_velocity = 0;
}
//******************************************************************************
//Yaw Left/Right****************************************************************
//******************************************************************************
void render::CameraBase::yaw_left(float dt, float modifier)
{
//	glm::fquat q_((float)(_yaw * modifier * dt), glm::vec3(_up.x, _up.y, _up.z));

	quatf q;
	q.rotate(_up, (float)(_yaw * modifier * dt));
	
//	glm::rotate(q, _yaw * modifier * dt, glm::vec3(_up.x, _up.y, _up.z));

	_dir = q.transform(_dir).normalize();
	_up  = q.transform(_up).normalize();
}
//------------------------------------------------------------------------------
void render::CameraBase::yaw_right(float dt, float modifier)
{
	quatf q;
	q.rotate(_up, (float)(-_yaw * modifier * dt));

	_dir = q.transform(_dir).normalize();
	_up  = q.transform(_up).normalize();
}
//******************************************************************************
//Roll Left/Right***************************************************************
//******************************************************************************
void render::CameraBase::roll_left(float dt, float modifier)
{
	quatf q;
	q.rotate(_dir, (float)(-_roll * modifier * dt));

	_up  = q.transform(_up).normalize();
}
//------------------------------------------------------------------------------
void render::CameraBase::roll_right(float dt, float modifier)
{
	quatf q;
	q.rotate(_dir, (float)(_roll * modifier * dt));

	_up  = q.transform(_up).normalize();
}
//******************************************************************************
//Pitch Up/Down*****************************************************************
//******************************************************************************
void render::CameraBase::pitch_up(float dt, float modifier)
{
	quatf q;
	q.rotate(cross(_dir, _up), (float)(-_pitch * modifier * dt));

	_dir = q.transform(_dir).normalize();
	_up  = q.transform(_up).normalize();
}
//------------------------------------------------------------------------------
void render::CameraBase::pitch_down(float dt, float modifier)
{
	quatf q;
	q.rotate(cross(_dir, _up), (float)(_pitch * modifier * dt));

	_dir = q.transform(_dir).normalize();
	_up  = q.transform(_up).normalize();
}
//******************************************************************************
//Strafe Left/Right*************************************************************
//******************************************************************************
void render::CameraBase::strafe_left(float dt, float modifier)
{
	vec3f move = cross(_dir, _up) * (float)(_strafe * modifier * dt);
	_pos -= move;
}
//------------------------------------------------------------------------------
void render::CameraBase::strafe_right(float dt, float modifier)
{
	vec3f move = cross(_dir, _up) *(float)(_strafe * modifier * dt);

//	cerr << "move: " << move << endl;

	_pos += move;
}
//******************************************************************************
//Forward/Back******************************************************************
//******************************************************************************
void render::CameraBase::forward(float dt, float modifier)
{
	_curr_velocity += _velocity * modifier * (float)(dt);
}
//------------------------------------------------------------------------------
void render::CameraBase::back(float dt, float modifier)
{
	_curr_velocity -= _velocity * modifier * (float)(dt);
}
//*****************************************************************************
//Rotate***********************************************************************
//*****************************************************************************
void render::CameraBase::rotate(const vec3f &rotate)
{
	quatf q;
	q.rotate(cross(_dir, _up), (float)(-_pitch * rotate.x));
//	q.rotate(_up, (float)(_yaw * rotate.y));

	_dir = q.transform(_dir).normalize();
	_up  = q.transform(_up).normalize();
}
//*****************************************************************************
//Update the camera************************************************************
//*****************************************************************************
void render::CameraBase::update()
{
	_curr_velocity *= (float)(1.0 - VELOCITY_DAMPING);
	_pos += _dir * _curr_velocity;
	vec3f that = _pos + _dir;

	//I'm not sure if this works anymore
//	_view.look_at(_pos, _dir, _up);
}
//*****************************************************************************
//Set perspective and move the camera******************************************
//*****************************************************************************
//mat4<float> CameraT::render()
//{
//	//I'm not sure if this works anymore
////	_view.look_at(_pos, _at, _up);
////	_view.transpose();
//
//	return(_view);
//}
//------------------------------------------------------------------------------
void render::CameraBase::render(vec3f &pos, vec3f &at, vec3f &up)
{
	pos = _pos;
	at  = _pos + _dir;
	up  = _up;
}
//*****************************************************************************
//Set Position*****************************************************************
//*****************************************************************************
void render::CameraBase::pos(const vec3f &pos)
{
	_pos = pos;
}

void render::CameraBase::dir(const vec3f &dir)
{
//	_dir = dir;
//	vec3f up(0,0,1);
//	vec3f right = cross(_dir, up);
//	_up = cross(right, _dir);

	_dir = dir;
	vec3f right = cross(_dir, _up);
	_up = cross(right, _dir);
}

void render::CameraBase::setPosDirUp( const vec3f &pos, const vec3f &dir, const vec3f &up )
{
	_pos = pos;
	_dir = dir;
	_up  = up;
}


