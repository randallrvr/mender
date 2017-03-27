//******************************************************************************
//render/math/mat4.h************************************************************
//******************************************************************************

#pragma once

//Project Includes
#include "vec3.h"
#include "vec4.h"

//Standard Library Includes
#include <iostream>

namespace render
{
template<class T>
class quat;

template<class T>
class mat4
{
public:

	static const mat4<T> identity;

public:
	union
	{
		struct
		{
			T m00, m01, m02, m03;
			T m10, m11, m12, m13;
			T m20, m21, m22, m23;
			T m30, m31, m32, m33;
		};
		struct
		{
			T _11, _12, _13, _14;
			T _21, _22, _23, _24;
			T _31, _32, _33, _34;
			T _41, _42, _43, _44;
		};
		T m[16];    // array access
	};

public:

	//Constructors
	mat4<T>();
	mat4<T>(const T &, const T &, const T &, const T &,
			const T &, const T &, const T &, const T &,
			const T &, const T &, const T &, const T &,
			const T &, const T &, const T &, const T &);
	mat4<T>(const vec3<T> &, const vec3<T> &, const vec3<T> &);
	mat4<T>(const T *);
	mat4<T>(const mat4<T> &);
	mat4<T>(const quat<T> &);

	//Set
	void set(const T *);
	void set(const T &, const T &, const T &, const T &,
			 const T &, const T &, const T &, const T &,
			 const T &, const T &, const T &, const T &,
			 const T &, const T &, const T &, const T &);
	void set(const vec3<T> &, const vec3<T> &, const vec3<T> &);
	void setColumns(const vec3<T> &, const vec3<T> &, const vec3<T> &);

	static mat4<T> ortho(T left, T right, T bottom, T top)
	{
		mat4<T> orthoMatrix;
		orthoMatrix.m00 = T(2.0) / (right - left);
		orthoMatrix.m11 = T(2.0) / (top - bottom);
		orthoMatrix.m22 = - T(1.0);
		orthoMatrix.m30 = - (right + left) / (right - left);
		orthoMatrix.m31 = - (top + bottom) / (top - bottom);
		return orthoMatrix;
	}

	//Operator()
	inline const T &operator()(const unsigned int &, const unsigned int &) const;
	inline       T &operator()(const unsigned int &, const unsigned int &);

	//Arithmetic Operators
	inline mat4<T>  operator+ (const mat4<T> &);
	inline mat4<T>  operator- (const mat4<T> &);
	inline mat4<T>  operator* (const mat4<T> &);
	inline mat4<T> &operator+=(const mat4<T> &);
	inline mat4<T> &operator-=(const mat4<T> &);
	inline mat4<T> &operator*=(const      T  &);
	inline mat4<T> &operator*=(const mat4<T> &);

	inline mat4<T> &look_at(vec3<T> &, vec3<T> &, vec3<T> &);

	inline mat4<T> &setInfinitePerspective(T, T, T);

	inline mat4<T> &setInfiniteFrustum(T, T, T, T, T);

	inline mat4<T> &setPerspective(T, T, T, T);

	//Equality Operators
	inline bool operator==(const mat4<T> &);
	inline bool operator!=(const mat4<T> &);

	//Assignment Operator
	inline mat4 &operator=(const mat4<T> &);

	inline operator const T*() const;
	inline operator       T*();

	//Determinant
	inline T determinant() const;

	//Trace
	inline T trace();

	inline mat4<T> &invert();

	inline mat4<T> &scale_by_x(const T &);
	inline mat4<T> &scale_by_y(const T &);
	inline mat4<T> &scale_by_z(const T &);
	inline mat4<T> &scale_by(const vec3<T> &);

	inline mat4<T> &reflect_x();
	inline mat4<T> &reflect_y();
	inline mat4<T> &reflect_z();

	inline void transpose();

	void set(const mat4<T> &);

	inline mat4<T> &rotate_x(const T &);
	inline mat4<T> &rotate_y(const T &);
	inline mat4<T> &rotate_z(const T &);
	inline mat4<T> &rotate(const vec3<T> &);
	inline mat4<T> &rotate(const vec3<T> &, const T &);		//Axis Angle

	//Translation Functions
	inline mat4 &translate_by_x(const T &);
	inline mat4 &translate_by_y(const T &);
	inline mat4 &translate_by_z(const T &);
	inline mat4 &translate_by(const vec2<T> &);
	inline mat4 &translate_by(const vec3<T> &);

//		quat<T> quaternion();

};

template<class T>
const mat4<T> mat4<T>::identity(1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1);

//Friend Arithmetic Operators
template<class T> vec3<T> operator*(const vec3<T> &, const mat4<T> &);	//vec3
template<class T> vec3<T> operator*(const mat4<T> &, const vec3<T> &);	//vec3
template<class T> vec4<T> operator*(const mat4<T> &, const vec4<T> &);	//vec4
template<class T> vec4<T> operator*(const vec4<T> &, const mat4<T> &);	//vec4
template<class T> mat4<T> operator*(const mat4<T> &, const mat4<T> &);
template<class T> void operator*=(vec3<T> &, const mat4<T> &);
template<class T> void operator*=(vec4<T> &, const mat4<T> &);

template<class T> mat4<T> transpose(const mat4<T> &);
template<class T> mat4<T> inverse(const mat4<T> &m);

template<class T> ostream &operator<<(ostream &, const mat4<T> &);


//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class T>
mat4<T>::mat4()
{
	*this = mat4<T>::identity;
}
//------------------------------------------------------------------------------
template<class T>
mat4<T>::mat4(const T *elements)
{
	memcpy(m, elements, sizeof(T)*16);
}
//------------------------------------------------------------------------------
template<class T>
mat4<T>::mat4(const T &m00, const T &m01, const T &m02, const T &m03,
			  const T &m10, const T &m11, const T &m12, const T &m13,
			  const T &m20, const T &m21, const T &m22, const T &m23,
			  const T &m30, const T &m31, const T &m32, const T &m33)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
	this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
	this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
	this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
}
//------------------------------------------------------------------------------
template<class T>
mat4<T>::mat4(const vec3<T> &x, const vec3<T> &y, const vec3<T> &z)
{
	this->set(x, y, z);
}
//------------------------------------------------------------------------------
template<class T>
mat4<T>::mat4(const mat4<T> &mat)
{
	memcpy(m, mat.m, sizeof(T)*16);
}
//------------------------------------------------------------------------------
template<class T>
mat4<T>::mat4(const quat<T> &q)
{
	//for unit q, just set s = 2 or set xs = q.x + q.x, etc.
	T s = 2 / (q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);

	T xs = q.x*s;
	T ys = q.y*s;
	T zs = q.z*s;

	T wx = q.w*xs;
	T wy = q.w*ys;
	T wz = q.w*zs;

	T xx = q.x*xs;
	T xy = q.x*ys;
	T xz = q.x*zs;

	T yy = q.y*ys;
	T yz = q.y*zs;
	T zz = q.z*zs;

	//First row
	m00 = -yy - zz + 1;
	m01 =  xy - wz;
	m02 =  xz + wy;
	m03 =  0;

	//Second row
	m10 =  xy + wz;
	m11 = -xx - zz + 1;
	m12 =  yz - wx;
	m13 =  0;

	//Third row
	m20 =  xz - wy;
	m21 =  yz + wx;
	m22 = -xx - yy + 1;
	m23 =  0;

	//Fourth row
	m30 = 0;
	m31 = 0;
	m32 = 0;
	m33 = 1;
}
//******************************************************************************
//Set***************************************************************************
//******************************************************************************
template<class T>
inline void mat4<T>::set(const T* elements)
{
	memcpy(m, elements, sizeof(T)*16);
}
//------------------------------------------------------------------------------
template<class T>
void mat4<T>::set(const T &m00, const T &m01, const T &m02, const T &m03,
				  const T &m10, const T &m11, const T &m12, const T &m13,
				  const T &m20, const T &m21, const T &m22, const T &m23,
				  const T &m30, const T &m31, const T &m32, const T &m33)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
	this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
	this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
	this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
}
//------------------------------------------------------------------------------
template<class T>
void mat4<T>::set(const vec3<T> &x, const vec3<T> &y, const vec3<T> &z)
{
	m00 = x.x; m01 = x.y; m02 = x.z; m03 = 0.0;
	m10 = y.x; m11 = y.y; m12 = y.z; m13 = 0.0;
	m20 = z.x; m21 = z.y; m22 = z.z; m23 = 0.0;
	m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0;
}
//------------------------------------------------------------------------------
template<class T>
void mat4<T>::setColumns(const vec3<T> &x, const vec3<T> &y, const vec3<T> &z)
{
	m00 = x.x; m01 = y.x; m02 = z.x; m03 = 0.0;
	m10 = x.y; m11 = y.y; m12 = z.y; m13 = 0.0;
	m20 = x.z; m21 = y.z; m22 = z.z; m23 = 0.0;
	m30 = 0.0; m31 = 0.0; m32 = 0.0; m33 = 1.0;
}
//******************************************************************************
//Operator()********************************************************************
//******************************************************************************
template<class T>
inline const T &mat4<T>::operator()(const unsigned int &i, const unsigned int &j) const
{
//	assert((0 <= i) && (i < 4) && (0 <= j) && (j < 4));
	return(m[j*4 + i]);
}
//------------------------------------------------------------------------------
template<class T>
inline T &mat4<T>::operator()(const unsigned int &i, const unsigned int &j)
{
//	assert((0 <= i) && (i < 4) && (0 <= j) && (j < 4));
	return(m[j*4 + i]);
}
//******************************************************************************
//Arithmetic Operators**********************************************************
//******************************************************************************
template<class T>
inline mat4<T> mat4<T>::operator+(const mat4<T> &mat)
{
	return mat4(m00 + mat.m00, m01 + mat.m01, m02 + mat.m02, m03 + mat.m03,
				m10 + mat.m10, m11 + mat.m11, m12 + mat.m12, m13 + mat.m13,
				m20 + mat.m20, m21 + mat.m21, m22 + mat.m22, m23 + mat.m23,
				m30 + mat.m30, m31 + mat.m31, m32 + mat.m32, m33 + mat.m33);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> mat4<T>::operator-(const mat4<T> &mat)
{
	return mat4(m00 - mat.m00, m01 - mat.m01, m02 - mat.m02, m03 - mat.m03,
				m10 - mat.m10, m11 - mat.m11, m12 - mat.m12, m13 - mat.m13,
				m20 - mat.m20, m21 - mat.m21, m22 - mat.m22, m23 - mat.m23,
				m30 - mat.m30, m31 - mat.m31, m32 - mat.m32, m33 - mat.m33);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> mat4<T>::operator*(const mat4<T> &mat)
{
	return mat4(m00*mat.m00 + m10*mat.m01 + m20*mat.m02 + m30*mat.m03,
				m01*mat.m00 + m11*mat.m01 + m21*mat.m02 + m31*mat.m03,
				m02*mat.m00 + m12*mat.m01 + m22*mat.m02 + m32*mat.m03,
				m03*mat.m00 + m13*mat.m01 + m23*mat.m02 + m33*mat.m03,
				m00*mat.m10 + m10*mat.m11 + m20*mat.m12 + m30*mat.m13,
				m01*mat.m10 + m11*mat.m11 + m21*mat.m12 + m31*mat.m13,
				m02*mat.m10 + m12*mat.m11 + m22*mat.m12 + m32*mat.m13,
				m03*mat.m10 + m13*mat.m11 + m23*mat.m12 + m33*mat.m13,
				m00*mat.m20 + m10*mat.m21 + m20*mat.m22 + m30*mat.m23,
				m01*mat.m20 + m11*mat.m21 + m21*mat.m22 + m31*mat.m23,
				m02*mat.m20 + m12*mat.m21 + m22*mat.m22 + m32*mat.m23,
				m03*mat.m20 + m13*mat.m21 + m23*mat.m22 + m33*mat.m23,
				m00*mat.m30 + m10*mat.m31 + m20*mat.m32 + m30*mat.m33,
				m01*mat.m30 + m11*mat.m31 + m21*mat.m32 + m31*mat.m33,
				m02*mat.m30 + m12*mat.m31 + m22*mat.m32 + m32*mat.m33,
				m03*mat.m30 + m13*mat.m31 + m23*mat.m32 + m33*mat.m33);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::look_at(vec3<T> &viewPosition, vec3<T> &viewFocus, vec3<T> &upVector)
{
	vec3<T> *xaxis = (vec3<T> *)(m + 0);
	vec3<T> *up    = (vec3<T> *)(m + 4);
	vec3<T> *at    = (vec3<T> *)(m + 8);

	*at  = viewFocus;
	*at -= viewPosition;
	at->normalize();

	*xaxis = cross(*at, upVector);
	xaxis->normalize();

	*up = cross(*xaxis, *at);

	*at *= -1;

	m03 = 0;
	m13 = 0;
	m23 = 0;

	m30 = viewPosition.x;
	m31 = viewPosition.y;
	m32 = viewPosition.z;
	m33 = 1;

	invert();

	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::operator+=(const mat4<T> &mat)
{
	for(int i = 0; i < 16; i++)
	{
		m[i] += mat.m[i];
	}
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::operator-=(const mat4<T> &mat)
{
	for(int i = 0; i < 16; i++)
	{
		m[i] -= mat.m[i];
	}
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::operator*=(const T &t)
{
	for(int i = 0; i < 16; i++)
	{
		m[i] *= t;
	}
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::setInfinitePerspective(T fovy, T aspect, T zNear)
{
	T tangent = tanf(1.57f*((fovy/2.0f)/180.0f));

	T y = tangent * zNear;
	T x = aspect  * y;

	return setInfiniteFrustum(-x, x, -y, y, zNear);
}
//------------------------------------------------------------------------------
template<>
inline mat4<double> &mat4<double>::setInfinitePerspective(double fovy, double aspect, double zNear)
{
	double tangent = tan(1.57f*((fovy/2.0f)/180.0f));

	double y = tangent * zNear;
	double x = aspect  * y;

	return setInfiniteFrustum(-x, x, -y, y, zNear);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::setInfiniteFrustum(T left, T right, T  bottom, T top, T zNear)
{
	*this = mat4<T>::identity;
	m00 = (2*zNear) / (right - left);
	m02 = (right + left) / (right - left);

	m11 = (2*zNear) / (top - bottom);
	m12 = (top + bottom) / (top - bottom);

	T nudge = 1 - 1.0 / (1<<23);

	m22 = -1 * nudge;
	m23 = -2* zNear * nudge;

	m32 = -1;
	m33 =  0;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::setPerspective(T fov, T aspect, T zNear, T zFar)
{
	T sine, cotangent, deltaZ;
	T radians = fov / 2.0f * 0.017453f;

	deltaZ = zFar - zNear;
	sine   = sinf(radians);

	*this = mat4<T>::identity;
	if ((deltaZ == 0.0f) || (sine == 0.0f) || (aspect == 0.0f))
	{
		return *this;
	}

	cotangent = cosf(radians) / sine;

	m00 = cotangent / aspect;
	m11 = cotangent;
	m22 = - (zFar + zNear) / deltaZ;
	m23 = -1.0f;
	m32 = -2.0f * zNear * zFar / deltaZ;
	m33 = 0.0f;
	return(*this);
}
//------------------------------------------------------------------------------
template<>
inline mat4<double> &mat4<double>::setPerspective(double fov, double aspect, double zNear, double zFar)
{
	double sine, cotangent, deltaZ;
	double radians = fov / 2.0 * 0.017453;

	deltaZ = zFar - zNear;
	sine   = sin(radians);

	*this = mat4<double>::identity;
	if ((deltaZ == 0.0) || (sine == 0.0) || (aspect == 0.0))
	{
		return *this;
	}

	cotangent = cos(radians) / sine;

	m00 = cotangent / aspect;
	m11 = cotangent;
	m22 = - (zFar + zNear) / deltaZ;
	m23 = -1.0;
	m32 = -2.0 * zNear * zFar / deltaZ;
	m33 = 0.0;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::operator*=(const mat4<T> &mat)
{
	set(m00*mat.m00+m10*mat.m01+m20*mat.m02+ m30*mat.m03,
		m01*mat.m00+m11*mat.m01+m21*mat.m02+ m31*mat.m03,
		m02*mat.m00+m12*mat.m01+m22*mat.m02+ m32*mat.m03,
		m03*mat.m00+m13*mat.m01+m23*mat.m02+ m33*mat.m03,
		m00*mat.m10+m10*mat.m11+m20*mat.m12+ m30*mat.m13,
		m01*mat.m10+m11*mat.m11+m21*mat.m12+ m31*mat.m13,
		m02*mat.m10+m12*mat.m11+m22*mat.m12+ m32*mat.m13,
		m03*mat.m10+m13*mat.m11+m23*mat.m12+ m33*mat.m13,
		m00*mat.m20+m10*mat.m21+m20*mat.m22+ m30*mat.m23,
		m01*mat.m20+m11*mat.m21+m21*mat.m22+ m31*mat.m23,
		m02*mat.m20+m12*mat.m21+m22*mat.m22+ m32*mat.m23,
		m03*mat.m20+m13*mat.m21+m23*mat.m22+ m33*mat.m23,
		m00*mat.m30+m10*mat.m31+m20*mat.m32+ m30*mat.m33,
		m01*mat.m30+m11*mat.m31+m21*mat.m32+ m31*mat.m33,
		m02*mat.m30+m12*mat.m31+m22*mat.m32+ m32*mat.m33,
		m03*mat.m30+m13*mat.m31+m23*mat.m32+ m33*mat.m33);
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline bool mat4<T>::operator==(const mat4<T> &mat)
{
	return memcmp(m, mat.m, sizeof(T)*16) == 0;
}
//------------------------------------------------------------------------------
template<class T>
inline bool mat4<T>::operator!=(const mat4<T> &mat)
{
	return memcmp(m, mat.m, sizeof(T)*16) != 0;
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::operator=(const mat4<T> &mat)
{
	memcpy(m,mat.m, sizeof(T)*16);
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T>::operator const T*() const
{
	return(m);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T>::operator T*()
{
	return(m);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator*(const vec3<T> &v, const mat4<T> &mat)
{
	return vec3<T>(mat.m00*v.x + mat.m10*v.y + mat.m20*v.z + mat.m30,
				   mat.m01*v.x + mat.m11*v.y + mat.m21*v.z + mat.m31,
				   mat.m02*v.x + mat.m12*v.y + mat.m22*v.z + mat.m32);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator*(const mat4<T> &mat, const vec3<T> &t)
{
	return vec3<T>(mat.m00*t.x + mat.m10*t.y + mat.m20*t.z + mat.m30,
				   mat.m01*t.x + mat.m11*t.y + mat.m21*t.z + mat.m31,
				   mat.m02*t.x + mat.m12*t.y + mat.m22*t.z + mat.m32);
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator*(const mat4<T> &mat, const vec4<T> &t)
{
	return vec4<T>(mat.m00*t.x + mat.m10*t.y + mat.m20*t.z + mat.m30*t.w,
				   mat.m01*t.x + mat.m11*t.y + mat.m21*t.z + mat.m31*t.w,
				   mat.m02*t.x + mat.m12*t.y + mat.m22*t.z + mat.m32*t.w,
				   mat.m03*t.x + mat.m13*t.y + mat.m23*t.z + mat.m33*t.w);
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator*(const vec4<T> &t, const mat4<T> &mat)
{
	return vec4<T>(mat.m00*t.x + mat.m10*t.y + mat.m20*t.z + mat.m30*t.w,
				   mat.m01*t.x + mat.m11*t.y + mat.m21*t.z + mat.m31*t.w,
				   mat.m02*t.x + mat.m12*t.y + mat.m22*t.z + mat.m32*t.w,
				   mat.m03*t.x + mat.m13*t.y + mat.m23*t.z + mat.m33*t.w);
}
//------------------------------------------------------------------------------
template<class T>
mat4<T> operator*(const mat4<T> &m1, const mat4<T> &m2)
{
	mat4<T> mat = m1;
	mat *= m2;
	return(mat);
}
//------------------------------------------------------------------------------
template<class T>
void operator*=(vec3<T> &t,const mat4<T> &mat)
{
	t.set(mat.m00*t.x + mat.m10*t.y + mat.m20*t.z + mat.m30,
		  mat.m01*t.x + mat.m11*t.y + mat.m21*t.z + mat.m31,
		  mat.m02*t.x + mat.m12*t.y + mat.m22*t.z + mat.m32);
}
//------------------------------------------------------------------------------
template<class T>
void operator*=(vec4<T> &t, const mat4<T> &mat)
{
	t.set(mat.m00*t.x + mat.m10*t.y + mat.m20*t.z + mat.m30*t.w,
		  mat.m01*t.x + mat.m11*t.y + mat.m21*t.z + mat.m31*t.w,
		  mat.m02*t.x + mat.m12*t.y + mat.m22*t.z + mat.m32*t.w,
		  mat.m03*t.x + mat.m13*t.y + mat.m23*t.z + mat.m33*t.w);
}
//******************************************************************************
//Determinant*******************************************************************
//******************************************************************************
template<class T>
inline T mat4<T>::determinant() const
{
	return(m03*m12*m21*m30 - m02*m13*m21*m30 - m03*m11*m22*m30 + m01*m13*m22*m30 +
		   m02*m11*m23*m30 - m01*m12*m23*m30 - m03*m12*m20*m31 + m02*m13*m20*m31 +
		   m03*m10*m22*m31 - m00*m13*m22*m31 - m02*m10*m23*m31 + m00*m12*m23*m31 +
		   m03*m11*m20*m32 - m01*m13*m20*m32 - m03*m10*m21*m32 + m00*m13*m21*m32 +
		   m01*m10*m23*m32 - m00*m11*m23*m32 - m02*m11*m20*m33 + m01*m12*m20*m33 +
		   m02*m10*m21*m33 - m00*m12*m21*m33 - m01*m10*m22*m33 + m00*m11*m22*m33);
}
//******************************************************************************
//Trace*************************************************************************
//******************************************************************************
template<class T>
inline T mat4<T>::trace()
{
	return(m00 + m11 + m22 + m33);
}
//******************************************************************************
//Invert************************************************************************
//******************************************************************************
template<class T>
inline mat4<T> &mat4<T>::invert()
{
	*this = inverse(*this);
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> inverse(const mat4<T> &m)
{
	mat4<T> tmp;
	tmp.m00 = m.m12*m.m23*m.m31 - m.m13*m.m22*m.m31 + m.m13*m.m21*m.m32 - m.m11*m.m23*m.m32 - m.m12*m.m21*m.m33 + m.m11*m.m22*m.m33;
	tmp.m01 = m.m03*m.m22*m.m31 - m.m02*m.m23*m.m31 - m.m03*m.m21*m.m32 + m.m01*m.m23*m.m32 + m.m02*m.m21*m.m33 - m.m01*m.m22*m.m33;
	tmp.m02 = m.m02*m.m13*m.m31 - m.m03*m.m12*m.m31 + m.m03*m.m11*m.m32 - m.m01*m.m13*m.m32 - m.m02*m.m11*m.m33 + m.m01*m.m12*m.m33;
	tmp.m03 = m.m03*m.m12*m.m21 - m.m02*m.m13*m.m21 - m.m03*m.m11*m.m22 + m.m01*m.m13*m.m22 + m.m02*m.m11*m.m23 - m.m01*m.m12*m.m23;
	tmp.m10 = m.m13*m.m22*m.m30 - m.m12*m.m23*m.m30 - m.m13*m.m20*m.m32 + m.m10*m.m23*m.m32 + m.m12*m.m20*m.m33 - m.m10*m.m22*m.m33;
	tmp.m11 = m.m02*m.m23*m.m30 - m.m03*m.m22*m.m30 + m.m03*m.m20*m.m32 - m.m00*m.m23*m.m32 - m.m02*m.m20*m.m33 + m.m00*m.m22*m.m33;
	tmp.m12 = m.m03*m.m12*m.m30 - m.m02*m.m13*m.m30 - m.m03*m.m10*m.m32 + m.m00*m.m13*m.m32 + m.m02*m.m10*m.m33 - m.m00*m.m12*m.m33;
	tmp.m13 = m.m02*m.m13*m.m20 - m.m03*m.m12*m.m20 + m.m03*m.m10*m.m22 - m.m00*m.m13*m.m22 - m.m02*m.m10*m.m23 + m.m00*m.m12*m.m23;
	tmp.m20 = m.m11*m.m23*m.m30 - m.m13*m.m21*m.m30 + m.m13*m.m20*m.m31 - m.m10*m.m23*m.m31 - m.m11*m.m20*m.m33 + m.m10*m.m21*m.m33;
	tmp.m21 = m.m03*m.m21*m.m30 - m.m01*m.m23*m.m30 - m.m03*m.m20*m.m31 + m.m00*m.m23*m.m31 + m.m01*m.m20*m.m33 - m.m00*m.m21*m.m33;
	tmp.m22 = m.m01*m.m13*m.m30 - m.m03*m.m11*m.m30 + m.m03*m.m10*m.m31 - m.m00*m.m13*m.m31 - m.m01*m.m10*m.m33 + m.m00*m.m11*m.m33;
	tmp.m23 = m.m03*m.m11*m.m20 - m.m01*m.m13*m.m20 - m.m03*m.m10*m.m21 + m.m00*m.m13*m.m21 + m.m01*m.m10*m.m23 - m.m00*m.m11*m.m23;
	tmp.m30 = m.m12*m.m21*m.m30 - m.m11*m.m22*m.m30 - m.m12*m.m20*m.m31 + m.m10*m.m22*m.m31 + m.m11*m.m20*m.m32 - m.m10*m.m21*m.m32;
	tmp.m31 = m.m01*m.m22*m.m30 - m.m02*m.m21*m.m30 + m.m02*m.m20*m.m31 - m.m00*m.m22*m.m31 - m.m01*m.m20*m.m32 + m.m00*m.m21*m.m32;
	tmp.m32 = m.m02*m.m11*m.m30 - m.m01*m.m12*m.m30 - m.m02*m.m10*m.m31 + m.m00*m.m12*m.m31 + m.m01*m.m10*m.m32 - m.m00*m.m11*m.m32;
	tmp.m33 = m.m01*m.m12*m.m20 - m.m02*m.m11*m.m20 + m.m02*m.m10*m.m21 - m.m00*m.m12*m.m21 - m.m01*m.m10*m.m22 + m.m00*m.m11*m.m22;
	tmp *= 1/m.determinant();

	return(tmp);
}
//******************************************************************************
//Scale*************************************************************************
//******************************************************************************
template<class T>
inline mat4<T> &mat4<T>::scale_by_x(const T &x)
{
	mat4<T> scale;
	scale.m00 = x;
	*this *= scale;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::scale_by_y(const T &y)
{
	mat4<T> scale;
	scale.m11 = y;
	*this *= scale;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::scale_by_z(const T &z)
{
	mat4<T> scale;
	scale.m22 = z;
	*this *= scale;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::scale_by(const vec3<T> &v)
{
	mat4<T> scale;
	scale.m00 = v.x;
	scale.m11 = v.y;
	scale.m22 = v.z;
	*this *= scale;
	return(*this);
}
//******************************************************************************
//Reflect***********************************************************************
//******************************************************************************
template<class T>
inline mat4<T> &mat4<T>::reflect_x()
{
	return(this->scale_by_x(-1.0));
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::reflect_y()
{
	return(this->scale_by_y(-1.0));
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::reflect_z()
{
	return(this->scale_by_z(-1.0));
}
//******************************************************************************
//Transpose*************************************************************************
//******************************************************************************
template<class T>
inline void mat4<T>::transpose()
{
	T temp;
	temp = m10;	m10 = m01;	m01 = temp;
	temp = m20;	m20 = m02;	m02 = temp;
	temp = m30;	m30 = m03;	m03 = temp;
	temp = m21;	m21 = m12;	m12 = temp;
	temp = m31;	m31 = m13;	m13 = temp;
	temp = m32;	m32 = m23;	m23 = temp;
}
//------------------------------------------------------------------------------
template<class T>
mat4<T> transpose( const mat4<T> &matrix )
{
	mat4<T> trans = matrix;
	trans.transpose();
	return trans;
}
//------------------------------------------------------------------------------
template<class T>
void mat4<T>::set(const mat4<T> &matrix)
{
	memcpy(m, matrix.m, sizeof(T) * 16);
}
//******************************************************************************
//Rotate************************************************************************
//******************************************************************************
template<class T>
inline mat4<T> &mat4<T>::rotate_x(const T &degrees)
{
	//Rotate about Y (ie, in the YZ plane)
	mat4<T> rotate;

	T radians = math::radians(degrees);

	rotate.m11 =  cos(radians);
	rotate.m12 =  sin(radians);
	rotate.m21 = -rotate.m12;
	rotate.m22 =  rotate.m11;

	*this *= rotate;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::rotate_y(const T &degrees)
{
	//Rotate about Y (ie, in the XZ plane)
	mat4<T> rotate;

	T radians = math::radians(degrees);

	rotate.m00 =  cos(radians);
	rotate.m02 =  sin(radians);
	rotate.m20 = -rotate.m02;
	rotate.m22 =  rotate.m00;

	*this *= rotate;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::rotate_z(const T &degrees)
{
	//Rotate about Z (ie, in the XY plane)
	mat4<T> rotate;

	T radians = math::radians(degrees);

	rotate.m00 =  cos(radians);
	rotate.m01 =  sin(radians);
	rotate.m10 = -rotate.m01;
	rotate.m11 =  rotate.m00;

	*this *= rotate;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::rotate(const vec3<T> &t)
{
	T cosX = cos(t.x);	T cosY = cos(t.y);	T cosZ = cos(t.z);
	T sinX = sin(t.x);	T sinY = sin(t.y);	T sinZ = sin(t.z);

	mat4<T> rotate(cosY * cosZ + sinX * sinY * sinZ,   -cosX * sinZ,    sinX * cosY * sinZ - sinY * cosZ,  0,
				   cosY * sinZ - sinX * sinY * cosZ,    cosX * cosZ,   -sinY * sinZ - sinX * cosY * cosZ,  0,
				   cosX * sinY,                         sinX,           cosX * cosY,                       0,
				   0,                                   0,              0,                                 1);

	*this *= rotate;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat4<T> &mat4<T>::rotate(const vec3<T> &axis, const T &angle)
{
	mat4<T> rotate;

	T sine = sin(angle);
	T cose = cos(angle);

	T one_minus_cose = 1.0f - cose;

	rotate.m00 = (axis.x)*(axis.x) + cose*(1-(axis.x)*(axis.x));
	rotate.m10 = (axis.x)*(axis.y)*(one_minus_cose) - sine*axis.z;
	rotate.m20 = (axis.x)*(axis.z)*(one_minus_cose) + sine*axis.y;

	rotate.m01 = (axis.x)*(axis.y)*(one_minus_cose) + sine*axis.z;
	rotate.m11 = (axis.y)*(axis.y) + cose*(1-(axis.y)*(axis.y));
	rotate.m21 = (axis.y)*(axis.z)*(one_minus_cose) - sine*axis.x;

	rotate.m02 = (axis.x)*(axis.z)*(one_minus_cose) - sine*axis.y;
	rotate.m12 = (axis.y)*(axis.z)*(one_minus_cose) + sine*axis.x;
	rotate.m22 = (axis.z)*(axis.z) + cose*(1-(axis.z)*(axis.z));

	*this *= rotate;
	return(*this);
}
//******************************************************************************
//Translate*********************************************************************
//******************************************************************************
template<class T>
mat4<T> &mat4<T>::translate_by_x(const T &x)
{
	mat4<T> trans;
	trans.m30 = x;
	*this *= trans;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
mat4<T> &mat4<T>::translate_by_y(const T &y)
{
	mat4<T> trans;
	trans.m31 = y;
	*this *= trans;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
mat4<T> &mat4<T>::translate_by_z(const T &z)
{
	mat4<T> trans;
	trans.m32 = z;
	*this *= trans;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
mat4<T> &mat4<T>::translate_by(const vec2<T> &v)
{
	mat4<T> trans;
	trans.m30 = v.x;
	trans.m31 = v.y;

	*this *= trans;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
mat4<T> &mat4<T>::translate_by(const vec3<T> &v)
{
	mat4<T> trans;
	trans.m30 = v.x;
	trans.m31 = v.y;
	trans.m32 = v.z;

	*this *= trans;
	return(*this);
}



//******************************************************************************
//Output************************************************************************
//******************************************************************************
template<class T>
ostream &operator<<(ostream &out, const mat4<T> &m)
{
	out << "mat4[" << m.m00 << ", " << m.m01 << ", "<< m.m02 << ", "<< m.m03 << "]" << endl;
	out << "    [" << m.m10 << ", " << m.m11 << ", "<< m.m12 << ", "<< m.m13 << "]" << endl;
	out << "    [" << m.m20 << ", " << m.m21 << ", "<< m.m22 << ", "<< m.m23 << "]" << endl;
	out << "    [" << m.m30 << ", " << m.m31 << ", "<< m.m32 << ", "<< m.m33 << "]" << endl;
	return(out);
}


typedef mat4<int>    mat4i;
typedef mat4<float>  mat4f;
typedef mat4<double> mat4d;
};

