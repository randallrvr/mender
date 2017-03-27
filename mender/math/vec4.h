//******************************************************************************
//render/math/vec4.h************************************************************
//******************************************************************************

#pragma once

#include <iostream>
#include "vec3.h"

namespace render
{
template<class T>
class vec4
{
public:

	static const vec4<T> zero;
	static const vec4<T> one;

public:
	union
	{
		struct{ T x,y,z,w; };
		struct{ T s,t,p,q; };
		struct{ T r,g,b,a; };
		T vec_array[4];			// array access
	};
public:

	//Constructors
	vec4<T>();
	vec4<T>(const T &);
	vec4<T>(const T &, const T &, const T &);
	vec4<T>(const T &, const T &, const T &, const T &);
	vec4<T>(const vec4<T> &);
	vec4<T>(const vec3<T> &, const T & = 1);
	vec4<T>(const T *ptr);

	//Set
	void set(const vec3<T> &, const T & = 1);
	void set(const T &, const T &, const T &, const T &);

	inline operator const T*() const;
	inline operator T*();

	inline const T operator[](int) const;
	inline T &operator[](int);

	//Assignment Operators
	inline vec4<T> &operator=(const vec4<T> &);
	inline vec4<T> &operator=(const vec3<T> &);

	//Arithmetic Operators
	inline vec4<T>  operator+ (const vec4<T> &);
	inline vec4<T>  operator- (const vec4<T> &);
	inline vec4<T>  operator* (const      T  &);
	inline vec4<T>  operator/ (const      T  &);
	inline vec4<T> &operator+=(const vec4<T> &);
	inline vec4<T>  operator-=(const vec4<T> &);
	inline vec4<T>  operator*=(const      T  &);
	inline vec4<T>  operator/=(const      T  &);

	inline vec4<T> clamp(const T, const T);

	void cross(vec4<T>, vec4<T>);

	//Equality Operators
	inline bool operator==(const vec4<T> &);
	inline bool operator!=(const vec4<T> &);

	inline const T length_sqr() const;
	inline const T length() const;

	//Normalize
	inline vec4<T> &normalize();

};

template<class T> const vec4<T> vec4<T>::zero(0, 0, 0, 0);
template<class T> const vec4<T> vec4<T>::one(1, 1, 1, 1);

//Arithmetic Operators
template<class T> vec4<T> operator*(const      T  &, const vec4<T> &);
template<class T> vec4<T> operator*(const vec4<T> &, const      T  &);
template<class T> vec4<T> operator*(const vec4<T> &, const vec4<T> &);
template<class T> vec4<T> operator/(const      T  &, const vec4<T> &);
template<class T> vec4<T> operator/(const vec4<T> &, const      T  &);
template<class T> vec4<T> operator/(const vec4<T> &, const vec4<T> &);
template<class T> vec4<T> operator+(const vec4<T> &, const vec4<T> &);
template<class T> vec4<T> operator-(const vec4<T> &, const vec4<T> &);
template<class T> vec4<T> operator-(const vec4<T> &);

//Input/Output
template<class T> ostream &operator<<(ostream &, const vec4<T> &);
template<class T> istream &operator>>(istream &,       vec4<T> &);


//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class T>
vec4<T>::vec4()
{
	x = y = z = w = 0;
}
//------------------------------------------------------------------------------
template<class T>
vec4<T>::vec4(const T &t)
{
	this->set(t, t, t, t);
}
//------------------------------------------------------------------------------
template<class T>
vec4<T>::vec4(const T &x, const T &y, const T &z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 0;
}
//------------------------------------------------------------------------------
template<class T>
vec4<T>::vec4(const T &x, const T &y, const T &z, const T &w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
//------------------------------------------------------------------------------
template<class T>
vec4<T>::vec4(const vec4<T> &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}
//------------------------------------------------------------------------------
template<class T>
vec4<T>::vec4(const vec3<T> &v, const T &w)
{
	x = v.x;
	y = v.y;
	z = v.z;
	this->w = w;
}
//------------------------------------------------------------------------------
template<class T>
vec4<T>::vec4(const T *ptr)
{
	memcpy(&x, ptr, sizeof(vec4<T>));
//	x = ptr[0];
//	y = ptr[1];
//	z = ptr[2];
//	w = ptr[3];
}
//******************************************************************************
//Set***************************************************************************
//******************************************************************************
template<class T>
void vec4<T>::set(const T &x, const T &y, const T &z, const T &w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
//------------------------------------------------------------------------------
template<class T>
void vec4<T>::set(const vec3<T> &v, const T &w)
{
	x = v.x;
	y = v.y;
	z = v.z;
	this->w = w;
}
//******************************************************************************
//Pointer & Array Operators*****************************************************
//******************************************************************************
template<class T>
inline vec4<T>::operator const T*() const
{
	return(&x);
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T>::operator T*()
{
	return(&x);
}
//------------------------------------------------------------------------------
template<class T>
inline const T vec4<T>::operator[](int i) const
{
	return ((T*)&x)[i];
}
//------------------------------------------------------------------------------
template<class T>
inline T &vec4<T>::operator[](int i)
{
	return ((T*)&x)[i];
}
//******************************************************************************
//Assignment Operators**********************************************************
//******************************************************************************
template<class T>
inline vec4<T> &vec4<T>::operator=(const vec4<T> &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T> &vec4<T>::operator=(const vec3<T> &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = 1;
	return(*this);
}
//******************************************************************************
//Arithmetic Operators**********************************************************
//******************************************************************************
template<class T>
inline vec4<T> vec4<T>::operator+(const vec4<T> &v)
{
	return vec4<T>(v.x + x, v.y + y, v.z + z, v.w + w);
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T> vec4<T>::operator-(const vec4<T> &v)
{
	return vec4<T>(-v.x + x, -v.y + y, -v.z + z, -v.w + w);
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T> vec4<T>::operator*(const T &t)
{
	return vec4<T>(x*t, y*t, z*t, w*t);
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T> vec4<T>::operator/(const T &t)
{
	return(t ? vec4<T>(x/t, y/t, z/t, w/t) : vec4<T>(0, 0, 0, 0));
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T> &vec4<T>::operator+=(const vec4<T> &right)
{
	x +=right.x;
	y +=right.y;
	z +=right.z;
	w +=right.w;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T> vec4<T>::operator-=(const vec4<T> &right)
{
	x-=right.x;
	y-=right.y;
	z-=right.z;
	w-=right.w;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T> vec4<T>::clamp(const T min, const T max)
{
	x = x < min ? min : x > max ? max : x;
	y = y < min ? min : y > max ? max : y;
	z = z < min ? min : z > max ? max : z;
	w = w < min ? min : w > max ? max : w;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T> vec4<T>::operator*=(const T &t)
{
	x *= t;
	y *= t;
	z *= t;
	w *= t;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec4<T> vec4<T>::operator/=(const T &t)
{
	if(t)
	{
		x /= t;
		y /= t;
		z /= t;
		w /= t;
	}
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
void vec4<T>::cross(vec4<T> v1, vec4<T> v2)
{
	// Get the cross product of v1 and v2 and store it in this vector.
	x = ((v1.y * v2.z) - (v1.z * v2.y));
	y = ((v1.z * v2.x) - (v1.x * v2.z));
	z = ((v1.x * v2.y) - (v1.y * v2.x));
}
//******************************************************************************
//Arithmetic Operators**********************************************************
//******************************************************************************
template<class T>
vec4<T> operator*(const T &c, const vec4<T> &v)
{
	return vec4<T>(c*v.x, c*v.y, c*v.z, c*v.w);
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator*(const vec4<T> &v, const T &c)
{
	return vec4<T>(c*v.x, c*v.y, c*v.z, c*v.w);
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator*(const vec4<T> &v0, const vec4<T> &v1)
{
	return(vec4<T>(v0.x*v1.x, v0.y*v1.y, v0.z*v1.z, v0.w*v1.w));
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator/(const T &c, const vec4<T> &v)
{
	return vec4<T>(c/v.x, c/v.y, c/v.z, c/v.w);
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator/(const vec4<T> &v, const T &c)
{
	return vec4<T>(v.x/c, v.y/c, v.z/c, v.w/c);
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator/(const vec4<T> &v0, const vec4<T> &v1)
{
	return(vec4<T>(v0.x/v1.x, v0.y/v1.y, v0.z/v1.z, v0.w/v1.w));
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator+(const vec4<T> &v1, const vec4<T> &v2)
{
	return vec4<T>(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z, v1.w+v2.w);
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator-(const vec4<T> &v1, const vec4<T> &v2)
{
	return vec4<T>(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z, v1.w-v2.w);
}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator-(const vec4<T> &v)
{
	return(vec4<T>(-v.x, -v.y, -v.z, -v.w));
}
//******************************************************************************
//Comparison Operators**********************************************************
//******************************************************************************
template<class T>
inline bool vec4<T>::operator==(const vec4<T> &right)
{
	return(x == right.x && y == right.y && z == right.z && w == right.w);
}
//------------------------------------------------------------------------------
template<class T>
inline bool vec4<T>::operator!=(const vec4<T> &right)
{
	return(!(x == right.x && y == right.y && z == right.z && w == right.w));
}
//******************************************************************************
//Length************************************************************************
//******************************************************************************
template<class T>
inline const T vec4<T>::length_sqr() const
{
	return(x*x + y*y + z*z + w*w);
}
//------------------------------------------------------------------------------
template<class T>
inline const T vec4<T>::length() const
{
	return(sqrt(x*x + y*y + z*z + w*w));
}
//******************************************************************************
//Normalize*********************************************************************
//******************************************************************************
template<class T>
inline vec4<T> &vec4<T>::normalize()
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
//Input/Output******************************************************************
//******************************************************************************
template<class T>
ostream &operator<<(ostream &out, const vec4<T> &v)
{
	return(out << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")");
}
//------------------------------------------------------------------------------
template<class T>
istream &operator>>(istream &in, vec4<T> &v)
{
	return(in >> v.x >> v.y >> v.z >> v.w);
}

typedef vec4<int>                vec4i;
typedef vec4<float>              vec4f;
typedef vec4<double>             vec4d;
typedef vec4<unsigned int>       vec4u;
typedef vec4<unsigned int>       vec4ui;
typedef vec4<char>               vec4b;
typedef vec4<unsigned char>      vec4ub;
typedef vec4<short int>          vec4s;
typedef vec4<unsigned short int> vec4us;
};

