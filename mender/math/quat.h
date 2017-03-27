//******************************************************************************
//render/math/quat.h************************************************************
//******************************************************************************

#pragma once

#include <mender/math.h>

#define PI 3.141592654f                                       // Define for PI.
#define GET_RADIANS(degree) (float)((degree * PI) / 180.0f)   // Will convert degrees to radians.

#include "mat4.h"
#include "vec4.h"
#include "vec3.h"

namespace render
{
template<class T>
class quat
{
public:
	union
	{
		struct{ T x,y,z,w; };
		T comp[4];
	};
public:

	//Constructors
	quat();
	quat(const vec3<T> &, const T &);
	quat(const mat4<T> &);

	//Normalize
	inline quat<T> &normalize();

	//Length
	inline const T length_sqr() const;
	inline const T length()     const;

	//Assignment Operators
	quat<T> &operator=(const mat4<T> &);
	quat<T> &operator=(const quat<T> &);

	quat<T>  operator+ (const quat<T> &);
	quat<T>  operator* (const quat<T> &);
	quat<T> &operator+=(const quat<T> &);
	quat<T> &operator*=(const quat<T> &);

	void slerp(quat<T> &, quat<T> &, T);

	quat<T> conjugate();

	quat<T> &rotate(vec3<T>, const T &);
	quat<T> &rotate_x(const T &);
	quat<T> &rotate_y(const T &);
	quat<T> &rotate_z(const T &);

	vec3<T> transform(const vec3<T> &) const;			// Transforms a vec3

	quat<T> trackball(vec2<T>, vec2<T>, T);

	void axis_angle(vec3<T> &, T &);

	T project_to_sphere(const vec2<T> &, const T &);

	mat4<T> matrix();

	mat4<T> matrix(vec3<T>);

};

//Input/Output
template<class T> ostream &operator<<(ostream &, const quat<T> &);
template<class T> istream &operator>>(istream &,       quat<T> &);


//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class T>
quat<T>::quat()
{
	//Initialize each member variables.
	x = y = z = 0;
	w = 1;
}
//------------------------------------------------------------------------------
//Quaternion from axis angle----------------------------------------------------
//------------------------------------------------------------------------------
template<class T>
quat<T>::quat(const vec3<T> &axis, const T &angle)
{
	vec3<T> a = axis;
	a.normalize();

	T rads = math::radians(angle) * (T)0.5;
	T sine = sin(rads);

	x = a.x * sine;
	y = a.y * sine;
	z = a.z * sine;
	w = cos(rads);

}
//------------------------------------------------------------------------------
template<class T>
quat<T>::quat(const mat4<T> &m)
{
	quat<T> q;
	T s;

	T trace = m.m00 + m.m11 + m.m22;

	if(trace > 0)
	{
		s = sqrt(trace + 1.0f);
		w = s/2;
		s = 1/(2*s);
		x = (m.m21 - m.m12)*s;
		y = (m.m02 - m.m20)*s;
		z = (m.m10 - m.m01)*s;
	}
	else
	{
		unsigned int i = 0;

		if(m.m11 > m.m00 )	i = 1;
		if(m.m22 > m(i,i))	i = 2;

		unsigned int j = (i+1)%3;
		unsigned int k = (j+1)%3;

		s = sqrt(1 + m(i,i) - m(j,j) - m(k,k));

		comp[i] = s * 0.5f;
		s = 1/(2*s);

		q.w     = (m(k,j) - m(j,k))*s;
		comp[j] = (m(k,i) + m(i,j))*s;
		comp[k] = (m(k,i) + m(i,k))*s;
	}
}
//******************************************************************************
//Length************************************************************************
//******************************************************************************
template<class T>
inline const T quat<T>::length_sqr() const
{
	return(x*x + y*y + z*z + w*w);
}
//------------------------------------------------------------------------------
template<class T>
inline const T quat<T>::length() const
{
	return(sqrt(x*x + y*y + z*z + w*w));
}
//******************************************************************************
//Normalize*********************************************************************
//******************************************************************************
template<class T>
inline quat<T> &quat<T>::normalize()
{
	T len = length();
	if(!len)
	{
		x = y = z = w = 0;
		return(*this);
	}
	x /= len;
	y /= len;
	z /= len;
	w /= len;
	return(*this);
}
//******************************************************************************
//Assignment Operator***********************************************************
//******************************************************************************
template<class T>
quat<T> &quat<T>::operator=(const mat4<T> &m)
{
	w = sqrt(m.m00 + m.m11 + m.m22 + m.m33) / 2;

	w  = w  < 0.0001f ? 0.0004f : 4.0f*w;

	x  = (m[6] - m[9])/w;
	y  = (m[8] - m[2])/w;
	z  = (m[1] - m[4])/w;
	w /= 4.0f;

	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
quat<T> &quat<T>::operator=(const quat<T> &q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	return(*this);
}
//******************************************************************************
//Arithmetic Operators**********************************************************
//******************************************************************************
template<class T>
quat<T> quat<T>::operator+(const quat<T> &q)
{
	quat<T> result;

	vec3<T> v1(  x,   y,   z);
	vec3<T> v2(q.x, q.y, q.z);

	vec3<T> v3 = v1*q.w + v2*w + cross(v2, v1);

	result.x = v3.x;
	result.y = v3.y;
	result.z = v3.z;
	result.w = w*q.w - (x*q.x + y*q.y + z*q.z);

	return result;
}
//------------------------------------------------------------------------------
template<class T>
quat<T> &quat<T>::operator+=(const quat<T> &q)
{
	(*this) = (*this) + q;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
quat<T> quat<T>::operator*(const quat<T> &q)
{
	//To multiply a quat you must first do the dot and cross product
	//of the 2 quats then add/subract them to a result.
	quat<T> result;

	result.x = w*q.x + x*q.w + y*q.z - z*q.y;
	result.y = w*q.y - x*q.z + y*q.w + z*q.x;
	result.z = w*q.z + x*q.y - y*q.x + z*q.w;
	result.w = w*q.w - x*q.x - y*q.y - z*q.z;

	return result;
}
//------------------------------------------------------------------------------
template<class T>
quat<T> &quat<T>::operator*=(const quat<T> &q)
{
	(*this) = (*this) * q;
	return(*this);
}
//******************************************************************************
//Spherical Linear Interpolation************************************************
//******************************************************************************
template<class T>
void quat<T>::slerp(quat<T> &q1, quat<T> &q2, T t)
{
	T o, co, so, scale0, scale1;
	T qi[4];

	//Do a linear interpolation between two quats (0 <= t <= 1).
	co = q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;  //dot product

	if(co < 0)
	{
		co = -co;
		qi[0] = -q2.x;
		qi[1] = -q2.y;
		qi[2] = -q2.z;
		qi[3] = -q2.w;
	}
	else
	{
		qi[0] = q2.x;
		qi[1] = q2.y;
		qi[2] = q2.z;
		qi[3] = q2.w;
	}

	// If the quats are really close, do a simple linear interpolation.
	if((1 - co) <= 0.0001f)
	{
		scale0 = 1 - t;
		scale1 = t;
	}
	else
	{
		// Otherwise SLERP.
		o      = (T)acos(co);
		so     = sin(o);
		scale0 = sin((1 - t) * o) / so;
		scale1 = sin(t * o) / so;
	}

	//Calculate interpolated quat:
	x = scale0*q1.x + scale1*qi[0];
	y = scale0*q1.y + scale1*qi[1];
	z = scale0*q1.z + scale1*qi[2];
	w = scale0*q1.w + scale1*qi[3];
}
//******************************************************************************
//Conjugate*********************************************************************
//******************************************************************************
template<class T>
quat<T> quat<T>::conjugate()
{
	quat new_quat;

	new_quat.x = -x;
	new_quat.y = -y;
	new_quat.z = -z;
	new_quat.w =  w;

	//The Conjugate is basically all axis negated but the w.
	return(new_quat);
}
//******************************************************************************
//Rotate************************************************************************
//******************************************************************************
template<class T>
quat<T> &quat<T>::rotate(vec3<T> axis, const T &angle)
{
	//Pretty much what is going on here is that if there is any axis that is not
	//a 0 or a 1 (meaning its not normalized) then we want to normalize it.
	//I created a if statement because I thought this would be better than normalizing
	//it every time this function is called, which would result in a lot of expensive
	//sqrt() call.  This is just in case the user forgot to use only normalized values.
	if((axis.x != 0 && axis.x != 1) || (axis.y != 0 && axis.y != 1) || (axis.z != 0 && axis.z != 1))
	{
		this->normalize();
	}

	T rads = math::radians(angle) * (T)0.5;
	T sine = sin(rads);

	x = axis.x * sine;
	y = axis.y * sine;
	z = axis.z * sine;
	w = cos(rads);

	//Normalize the quat
	this->normalize();

	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
quat<T> &quat<T>::rotate_x(const T &angle)
{
	rotate(vec3<T>(1.0, 0.0, 0.0), angle);
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
quat<T> &quat<T>::rotate_y(const T &angle)
{
	rotate(vec3<T>(0.0, 1.0, 0.0), angle);
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
quat<T> &quat<T>::rotate_z(const T &angle)
{
	rotate(vec3<T>(0.0, 0.0, 1.0), angle);
	return(*this);
}
//******************************************************************************
//Trackball*********************************************************************
//******************************************************************************
template<class T>
quat<T> quat<T>::trackball(vec2<T> p1, vec2<T> p2, T radius)
{
	//First we take the last moust pos point and make it 3D.
	vec3<T> v1(p1.x, p1.y,  project_to_sphere(p1, radius));

	//Same as with the last point with the current point.
	vec3<T> v2(p2.x, p2.y,  project_to_sphere(p2, radius));

	//Length of the difference.
	T length = (v1 - v2).length() / (2*radius);

	//Clamp between -1 and 1.
	length = math::clamp((T)length, (T)-1.0, (T)1.0);

	//Calculate the rotation amount.
	T phi = 2.0f * (T)asin(length);

	//Get the cross product between the two 3D points.
	vec3<T> axis = cross(v2, v1);

	//return the new quaternion rotation.
	return quat<T>(axis, phi);
}
//******************************************************************************
//Axis Angle********************************************************************
//******************************************************************************
template<class T>
void quat<T>::axis_angle(vec3<T> &axis, T &angle)
{
	T scale = sqrt(x * x + y * y + z * z);
	axis.x = x / scale;
	axis.y = y / scale;
	axis.z = z / scale;
	angle = acos(w) * (T)2.0;
}
//******************************************************************************
//Project to Sphere*************************************************************
//******************************************************************************
template<class T>
T quat<T>::project_to_sphere(const vec2<T> &p, const T &radius)
{
	//This function is used to calculate a z axis from 2 mouse pos.
	//First we need the lenght of the positions, if it is greater or smaller
	//than the radius will determine how the z is calculated.
	T r = radius;
	T d = sqrt(p.x*p.x + p.y*p.y);
	if(d < r*math::inv_root_two)
	{
//		cerr << "inside the sphere" << endl;
		//Inside the sphere.
		return(sqrt(r*r - d*d));
	}
	//Else, on hyperbola.
//	cerr << "on hyperbola" << endl;
	r /= (T)math::root_two;
	return(r*r / d);
}
//******************************************************************************
//Matrix************************************************************************
//******************************************************************************
template<class T>
mat4<T> quat<T>::matrix()
{
	mat4<T> m;

	//Calculate the first row.
	m.m00 = -2*(y*y + z*z) + 1;
	m.m01 =  2*(x*y - z*w);
	m.m02 =  2*(x*z + y*w);
	m.m03 =  0;

	//Calculate the second row.
	m.m10 =  2*(x*y + z*w);
	m.m11 = -2*(x*x + z*z) + 1;
	m.m12 =  2*(z*y - x*w);
	m.m13 =  0;

	//Calculate the third row.
	m.m20 =  2*(x*z - y*w);
	m.m21 =  2*(y*z + x*w);
	m.m22 = -2*(x*x + y*y) + 1;
	m.m23 =  0;

	//Calculate the fourth row.
	m.m30 = 0;
	m.m31 = 0;
	m.m32 = 0;
	m.m33 = 1;

	return m;
}
//------------------------------------------------------------------------------
template<class T>
mat4<T> quat<T>::matrix(vec3<T> v)
{
	mat4<T> m;

	//Calculate the first row.
	m.m00 = -2*(y*y + z*z) + 1;
	m.m01 =  2*(x*y - z*w);
	m.m02 =  2*(x*z + y*w);
	m.m03 =  0;

	//Calculate the second row.
	m.m10 =  2*(x*y + z*w);
	m.m11 = -2*(x*x + z*z) + 1;
	m.m12 =  2*(z*y - x*w);
	m.m13 =  0;

	//Calculate the third row.
	m.m20 =  2*(x*z - y*w);
	m.m21 =  2*(y*z + x*w);
	m.m22 = -2*(x*x + y*y) + 1;
	m.m23 =  0;

	// Calculate the fourth row.
	m.m30 = v.x;
	m.m31 = v.y;
	m.m32 = v.z;
	m.m33 = 1;

	return m;
}
//******************************************************************************
//Transform*********************************************************************
//******************************************************************************
template<class T>
vec3<T> quat<T>::transform(const vec3<T> &v) const
{
	vec3<T> result;
	T rX = y*v.z - z*v.y + w*v.x;
	T rY = z*v.x - x*v.z + w*v.y;
	T rZ = x*v.y - y*v.x + w*v.z;
	T rW =-x*v.x - y*v.y - z*v.z;
	T l  = x*x + y*y + z*z + w*w;
	result.x = (rZ*y - rY*z - rW*x + rX*w) / l;
	result.y = (rX*z - rZ*x - rW*y + rY*w) / l;
	result.z = (rY*x - rX*y - rW*z + rZ*w) / l;
	return(result);
}
//******************************************************************************
//Input/Output******************************************************************
//******************************************************************************
template<class T>
ostream &operator<<(ostream &out, const quat<T> &q)
{
	return out << "quat(<" << q.x << ", " << q.y << ", " << q.z << ">, " << q.w << ")";
}
//------------------------------------------------------------------------------
template<class T>
istream &operator>>(istream &in, quat<T> &q)
{
	return in >> q.x >> q.y >> q.z >> q.w;
}

typedef quat<float>  quatf;
typedef quat<double> quatd;
};


