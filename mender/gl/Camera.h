//******************************************************************************
//render/gl/Camera.h************************************************************
//******************************************************************************

#pragma once

//Render Library Includes
#include "camera/CameraBase.h"

#include <iostream>

using namespace std;

namespace render
{
namespace gl
{
class Camera : public render::CameraBase
{
public:

	vec2f viewport;

	mat4f view_mat, inv_view_mat;
	mat4f proj_mat, inv_proj_mat;

	mat4f ndc_mat;

	float fov;
	float near_plane;
	float far_plane;

	typedef unsigned int uint;

public:
	Camera();

	void render();

	void project();
	void look_at();
	
	void render_frustum();
	void render_frustum_normalized();
	void render_frustum_again();

	void computeFrustrum(vec3f (&N)[4], vec3f (&F)[4]);

	//Set Camera Parameters
	void set_fov(const float &);
	void set_near(const float &);
	void setNearFar(float, float);
	void set_far(const float &);
	void set_clipping(const float &, const float &);
	void set_viewport(const vec2f &);
	void setViewport(uint, uint);

	//Set Matrices
	void set_matrices();
	void set_ndc_matrix();

	void mouse_move(float, float, float, float = 1.0f);
};
//End Class Camera



};
//End namespace gl
};
//End namespace render


