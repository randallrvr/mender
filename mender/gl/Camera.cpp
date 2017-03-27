//******************************************************************************
//render/gl/Camera.h************************************************************
//******************************************************************************

//Header Include
#include "Camera.h"

//Render Library Includes
#include <render/gl.h>

//namespaces
using namespace render;
using namespace gl;


//******************************************************************************
//Constructor*******************************************************************
//******************************************************************************
gl::Camera::Camera() : render::CameraBase()
{
	this->fov        =   45.0f;
	this->near_plane =    0.01f;
	this->far_plane  = 1000.0f;

	this->set_matrices();
}
//******************************************************************************
//Render************************************************************************
//******************************************************************************
void gl::Camera::render()
{
	this->update();
	this->project();
	this->look_at();
}
//******************************************************************************
//Project***********************************************************************
//******************************************************************************
void gl::Camera::project()
{
	//Prevent a divide by zero error
	if(viewport.h == 0)
	{
		//Make the height equal one
		viewport.h = 1;
	}

	//Set the viewport size
	glViewport(0, 0, (int)viewport.w, (int)viewport.h);
}
//******************************************************************************
//Look at***********************************************************************
//******************************************************************************
void gl::Camera::look_at()
{
	vec3f pos, at, up;
	render::CameraBase::render(pos, at, up);

	view_mat.look_at(pos, at, up);
}
//******************************************************************************
//Render Frustum****************************************************************
//******************************************************************************
void gl::Camera::render_frustum()
{
	float aspect = (float)viewport.w/(float)viewport.h;

	float near_h = 2.0f * tan(math::radians(fov) *0.5f) * near_plane;
	float near_w = near_h * aspect;

	float far_h = 2.0f * tan(math::radians(fov) *0.5f) * far_plane;
	float far_w = far_h * aspect;

	vec3f right = cross(_up, _dir);

	vec3f far_center  = _pos + _dir * far_plane;
	vec3f near_center = _pos + _dir * near_plane;

	vec3f far_tl = far_center + (_up * far_h*0.5f) - (right * far_w*0.5f);
	vec3f far_tr = far_center + (_up * far_h*0.5f) + (right * far_w*0.5f);
	vec3f far_bl = far_center - (_up * far_h*0.5f) - (right * far_w*0.5f);
	vec3f far_br = far_center - (_up * far_h*0.5f) + (right * far_w*0.5f);

	vec3f near_tl = near_center + (_up * near_h*0.5f) - (right * near_w*0.5f);
	vec3f near_tr = near_center + (_up * near_h*0.5f) + (right * near_w*0.5f);
	vec3f near_bl = near_center - (_up * near_h*0.5f) - (right * near_w*0.5f);
	vec3f near_br = near_center - (_up * near_h*0.5f) + (right * near_w*0.5f);
}
//------------------------------------------------------------------------------
void gl::Camera::render_frustum_normalized()
{
	float aspect = (float)viewport.w/(float)viewport.h;

	float near_h = 2.0f * tan(math::radians(fov) *0.5f) * near_plane;
	float near_w = near_h * aspect;

	float far_h = 2.0f * tan(math::radians(fov) *0.5f) * far_plane;
	float far_w = far_h * aspect;

	 _up.normalize();
	_dir.normalize();

	vec3f right = cross(_up, _dir).normalize();

	vec3f far_center  = _pos + _dir * far_plane;
	vec3f near_center = _pos + _dir * near_plane;

	vec3f far_tl = far_center + (_up * far_h*0.5f) - (right * far_w*0.5f);
	vec3f far_tr = far_center + (_up * far_h*0.5f) + (right * far_w*0.5f);
	vec3f far_bl = far_center - (_up * far_h*0.5f) - (right * far_w*0.5f);
	vec3f far_br = far_center - (_up * far_h*0.5f) + (right * far_w*0.5f);

	vec3f near_tl = near_center + (_up * near_h*0.5f) - (right * near_w*0.5f);
	vec3f near_tr = near_center + (_up * near_h*0.5f) + (right * near_w*0.5f);
	vec3f near_bl = near_center - (_up * near_h*0.5f) - (right * near_w*0.5f);
	vec3f near_br = near_center - (_up * near_h*0.5f) + (right * near_w*0.5f);
}
//------------------------------------------------------------------------------
void gl::Camera::render_frustum_again()
{
	float aspect = (float)viewport.w/(float)viewport.h;

	float near_h = 2.0f * tan(math::radians(fov) *0.5f) * near_plane;
	float near_w = near_h * aspect;

	float far_h = 2.0f * tan(math::radians(fov) *0.5f) * far_plane;
	float far_w = far_h * aspect;

	 _up.normalize();
	_dir.normalize();

	vec3f right = cross(_up, _dir).normalize();

	vec3f far_center  = _pos + _dir * far_plane;
	vec3f near_center = _pos + _dir * near_plane;

	vec3f far_tl = far_center + (_up * far_h*0.5f) - (right * far_w*0.5f);
	vec3f far_tr = far_center + (_up * far_h*0.5f) + (right * far_w*0.5f);
	vec3f far_bl = far_center - (_up * far_h*0.5f) - (right * far_w*0.5f);
	vec3f far_br = far_center - (_up * far_h*0.5f) + (right * far_w*0.5f);

	vec3f near_tl = near_center + (_up * near_h*0.5f) - (right * near_w*0.5f);
	vec3f near_tr = near_center + (_up * near_h*0.5f) + (right * near_w*0.5f);
	vec3f near_bl = near_center - (_up * near_h*0.5f) - (right * near_w*0.5f);
	vec3f near_br = near_center - (_up * near_h*0.5f) + (right * near_w*0.5f);

	far_tl = inv_proj_mat * far_tl;
	far_tr = inv_proj_mat * far_tr;
	far_bl = inv_proj_mat * far_bl;
	far_tl = inv_proj_mat * far_tl;

	near_tl = inv_proj_mat * near_tl;
	near_tr = inv_proj_mat * near_tr;
	near_bl = inv_proj_mat * near_bl;
	near_tl = inv_proj_mat * near_tl;
}
//******************************************************************************
//Set Matrices******************************************************************
//******************************************************************************
void gl::Camera::set_matrices()
{
	float f = 1.0f / math::tan(math::radians(fov) * 0.5f);

	float aspect = (float)viewport.w/(float)viewport.h;
	float a = f / aspect;
	float b = f;
	float c =   (far_plane + near_plane)/(near_plane - far_plane);
	float d = 2*(far_plane * near_plane)/(near_plane - far_plane);
	float e = -1.0f;

	proj_mat.set(a, 0, 0, 0,
	             0, b, 0, 0,
	             0, 0, c, e,
	             0, 0, d, 0);

	inv_proj_mat.set(1/a,   0,   0,       0,
	                   0, 1/b,   0,       0,
	                   0,   0,   0,     1/d,
	                   0,   0, 1/e, -c/(d*e));
}
//------------------------------------------------------------------------------
void gl::Camera::set_ndc_matrix()
{
	float aspect = (float)viewport.w/(float)viewport.h;

	float t = near_plane * tan(fov * (float)math::pi / 360.0f);
	float b = -t;
	float l =  b * aspect;
	float r =  t * aspect;
	float n = near_plane;
	float f = far_plane;

	ndc_mat.set((2*n)/(r-l),           0,    (r+l)/(r-l),  0,
	                      0, (2*n)/(t-b),    (t+b)/(t-b),  0,
	                      0,           0,   -(f+n)/(f-n), -1,
	                      0,           0, -(2*f*n)/(f-n),  0);

	cerr << "NDC mat" << endl;
	cerr << ndc_mat << endl;
}
//******************************************************************************
//Set Camera Parameters*********************************************************
//******************************************************************************
void gl::Camera::set_fov(const float &fov)
{
	this->fov = fov;
	this->set_matrices();
}
//------------------------------------------------------------------------------
void gl::Camera::set_near(const float &near)
{
	this->near_plane = near;
	this->set_matrices();
}
//------------------------------------------------------------------------------
void gl::Camera::set_far(const float &far_plane)
{
	this->far_plane = far_plane;
	this->set_matrices();
}
//------------------------------------------------------------------------------
void render::gl::Camera::setNearFar( float near, float far)
{
	this->near_plane = near;
	this->far_plane  = far;
	this->set_matrices();
}
//------------------------------------------------------------------------------
void gl::Camera::set_clipping(const float &near, const float &far_plane)
{
	this->near_plane = near;
	this->far_plane  = far_plane;
	this->set_matrices();
}
//------------------------------------------------------------------------------
void gl::Camera::set_viewport(const vec2f &viewport)
{
	this->viewport = viewport;
	this->set_matrices();
}
//------------------------------------------------------------------------------
void gl::Camera::setViewport(uint viewW, uint viewH)
{
	this->viewport = vec2f(float(viewW), float(viewH));
	this->set_matrices();
}
//******************************************************************************
//Mouse Movement****************************************************************
//******************************************************************************
void gl::Camera::mouse_move( float dt, float del_x, float del_y, float modifier)
{
	//del_x = x pixels over screen width
	//del_y = y pixels over screen height

	//same as yaw_left and pitch_up, but does not modify _up
	quatf q;
	q.rotate(_up, (float)(_yaw * del_x * dt * modifier));	//left/right
	_dir = q.transform(_dir).normalize();

	q.rotate(cross(_dir, _up), (float)(_pitch * del_y * dt * modifier));	//up/down
	_dir = q.transform(_dir).normalize();
}
