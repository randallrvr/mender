//******************************************************************************
//render/math/vec3.h************************************************************
//******************************************************************************

#pragma once

//Project Includes
#include "vec2.h"
#include "quat.h"

//Standard Library Includes
#include <iostream>
#include <cfloat>

//Namespaces
using namespace std;

namespace render
{
template<class T>
class vec4;

template<class T>
class vec3
{
public:

	static const vec3<T> zero;
	static const vec3<T> one;

public:

	union
	{
		struct{ T x,y,z; };
		struct{ T s,t,p; };
		struct{ T r,g,b; };
		struct{ T w,h,d; };
		T vec_array[3];
	};

	//Constructors
	vec3();
	vec3(const T &);
	vec3(const T &, const T &, const T &);
	vec3(const vec3<T> &);
	vec3(const vec4<T> &);
	vec3(const vec2<T> &);
	vec3(const vec2<T> &, const T &);

	void set(const T &, const T &, const T &);
	void set(const vec3<T> &);
	void set(const vec2<T> &, const T &);

	//Assignment Operator
	inline vec3<T> &operator=(const vec3<T> &);

	//Inline Arithmetic Operators
	inline vec3<T>  operator+ (const vec3<T> &);
	inline vec3<T>  operator- (const vec3<T> &);
	inline vec3<T>  operator* (const      T  &);
	inline vec3<T>  operator/ (const      T  &);
	inline vec3<T> &operator+=(const vec3<T> &);
	inline vec3<T> &operator+=(const      T  &);
	inline vec3<T> &operator-=(const vec3<T> &);
	inline vec3<T> &operator-=(const      T  &);
	inline vec3<T> &operator*=(const vec3<T> &);
	inline vec3<T> &operator*=(const      T  &);
	inline vec3<T> &operator/=(const vec3<T> &);
	inline vec3<T> &operator/=(const      T  &);


	//Swizzle Operators
	inline vec2<T> xy();
	inline vec2<T> xz();
	inline vec2<T> yz();
	inline vec2<T> yx();
	inline vec2<T> zx();
	inline vec2<T> zy();

	//Equality Operators
	bool operator==(const vec3<T> &);
	bool operator!=(const vec3<T> &);

	inline operator const T*() const;
	inline operator       T*();

	//Operator[]
	inline const T &operator[](const int &) const;
	inline T       &operator[](const int &);

	//Normalize
	inline vec3<T> &normalize();

	//Rotate
	inline vec3<T> &rotate(const vec3<T> &, const T &);

	//Length
	inline const T length_sqr() const;
	inline const T length()     const;

	inline vec3<T>  operator^ (const vec3<T> &);
	inline vec3<T> &operator^=(const vec3<T> &);

	inline const T dist(const vec3<T> &) const;

	inline const T sum() const;

	inline vec3<T> &clamp(T, T);

	//Typecast
	template<class U> operator vec3<U>() { return(vec3<U>((U)x, (U)y, (U)z)); }
};

template<class T> const vec3<T> vec3<T>::zero(0, 0, 0);
template<class T> const vec3<T> vec3<T>::one(1, 1, 1);

//Distance
template<class T> const T distance(const vec3<T> &, const vec3<T> &);

//Arithmetic Operators
template<class T> vec3<T> operator*(const      T  &, const vec3<T> &);
template<class T> vec3<T> operator*(const vec3<T> &, const      T  &);
template<class T> vec3<T> operator*(const vec3<T> &, const vec3<T> &);
template<class T> vec3<T> operator/(const      T  &, const vec3<T> &);
template<class T> vec3<T> operator/(const vec3<T> &, const      T  &);
template<class T> vec3<T> operator+(const vec3<T> &, const vec3<T> &);
template<class T> vec3<T> operator-(const vec3<T> &, const vec3<T> &);
template<class T> vec3<T> operator-(const vec3<T> &);

//Input/Output
template<class T> ostream &operator<<(ostream &, const vec3<T> &);
template<class T> istream &operator>>(istream &,       vec3<T> &);

//Dot Product & Cross Product
template<class T> const T    dot(const vec3<T> &, const vec3<T> &);
template<class T>  vec3<T> cross(const vec3<T> &, const vec3<T> &);
template<class T>  vec3<T> cross(const vec4<T> &, const vec4<T> &);

//Angle between two vectors
template<class T> const T angle(const vec3<T> &, const vec3<T> &);

template<class T> vec3<T> HSVtoRGB(const vec3<T> &hsv);


//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class T>
vec3<T>::vec3()
{
	x = y = z = 0;
}
//------------------------------------------------------------------------------
template<class T>
vec3<T>::vec3(const T &t)
{
	this->set(t, t, t);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T>::vec3(const T &x, const T &y, const T &z)
{
	this->set((T)x, (T)y, (T)z);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T>::vec3(const vec3<T> &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
//------------------------------------------------------------------------------
template<class T>
vec3<T>::vec3(const vec4<T> &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
//------------------------------------------------------------------------------
template<class T>
vec3<T>::vec3(const vec2<T> &v)
{
	x = v.x;
	y = v.y;
	z = 0.0;
}
//------------------------------------------------------------------------------
template<class T>
vec3<T>::vec3(const vec2<T> &v, const T &t)
{
	x = v.x;
	y = v.y;
	z = t;
}
//******************************************************************************
//Set***************************************************************************
//******************************************************************************
template<class T>
void vec3<T>::set(const T &x, const T &y, const T &z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
//------------------------------------------------------------------------------
template<class T>
void vec3<T>::set(const vec3<T> &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
//------------------------------------------------------------------------------
template<class T>
void vec3<T>::set(const vec2<T> &v, const T &t)
{
	x = v.x;
	y = v.y;
	z = t;
}
//******************************************************************************
//Assignment Operator***********************************************************
//******************************************************************************
template<class T>
inline vec3<T> &vec3<T>::operator=(const vec3<T> &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return(*this);
}
//******************************************************************************
//Distance**********************************************************************
//******************************************************************************
template<class T>
const T distance(const vec3<T> &v1, const vec3<T> &v2)
{
	return sqrt((v2.x-v1.x)*(v2.x-v1.x) + (v2.y-v1.y)*(v2.y-v1.y) + (v2.z-v1.z)*(v2.z-v1.z));
}
//******************************************************************************
//Arithmetic Operators**********************************************************
//******************************************************************************
template<class T>
inline vec3<T> vec3<T>::operator+(const vec3<T> &v)
{
	return vec3<T>(x+v.x, y+v.y, z+v.z);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> vec3<T>::operator-(const vec3<T> &v)
{
	return vec3<T>(x-v.x, y-v.y, z-v.z);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> vec3<T>::operator*(const T &t)
{
	return vec3<T>(x*t, y*t, z*t);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> vec3<T>::operator/(const T &t)
{
	return t ? vec3<T>(x/t, y/t, z/t) : vec3<T>(0, 0, 0);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::operator+=(const vec3<T> &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::operator+=(const T &t)
{
	x += t;
	y += t;
	z += t;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::operator-=(const vec3<T> &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::operator-=(const T &t)
{
	x -= t;
	y -= t;
	z -= t;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::operator*=(const T &t)
{
	x *= t;
	y *= t;
	z *= t;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::operator*=(const vec3<T> &v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::operator/=(const T &t)
{
	if(t)
	{
		x /= t;
		y /= t;
		z /= t;
	}
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::operator/=(const vec3<T> &v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return(*this);
}
//******************************************************************************
//Swizzle Operators*************************************************************
//******************************************************************************
template<class T>
inline vec2<T> vec3<T>::xy()
{
	return(vec2<T>(x, y));
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec3<T>::xz()
{
	return(vec2<T>(x, z));
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec3<T>::yz()
{
	return(vec2<T>(y, z));
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec3<T>::yx()
{
	return(vec2<T>(y, x));
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec3<T>::zx()
{
	return(vec2<T>(z, x));
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec3<T>::zy()
{
	return(vec2<T>(z, y));
}
//******************************************************************************
//Arithmetic Operators**********************************************************
//******************************************************************************
template<class T>
vec3<T> operator*(const T &c, const vec3<T> &v)
{
	return(vec3<T>(c*v.x, c*v.y, c*v.z));
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator*(const vec3<T> &v, const T &c)
{
	return(vec3<T>(c*v.x, c*v.y, c*v.z));
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator*(const vec3<T> &v0, const vec3<T> &v1)
{
	return(vec3<T>(v0.x*v1.x, v0.y*v1.y, v0.z*v1.z));
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator/(const T &c, const vec3<T> &v)
{
	return vec3<T>(c/v.x, c/v.y, c/v.z);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator/(const vec3<T> &v, const T &c)
{
	return vec3<T>(v.x/c, v.y/c, v.z/c);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator+(const vec3<T> &v1, const vec3<T> &v2)
{
	return vec3<T>(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator-(const vec3<T> &v1, const vec3<T> &v2)
{
	return vec3<T>(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator-(const vec3<T> &v)
{
	return(vec3<T>(-v.x, -v.y, -v.z));
}
//******************************************************************************
//Equality Operators************************************************************
//******************************************************************************
template<class T>
bool vec3<T>::operator==(const vec3<T> &v)
{
	return (x == v.x && y == v.y &&	z == v.z);
}
//------------------------------------------------------------------------------
template<class T>
bool vec3<T>::operator!=(const vec3<T> &v)
{
	return !(x == v.x && y == v.y && z == v.z);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T>::operator const T*() const
{
	return &x;
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T>::operator T*()
{
	return &x;
}
//------------------------------------------------------------------------------
template<class T>
inline const T &vec3<T>::operator[](const int &i) const
{
	return ((T*)&x)[i];
}
//------------------------------------------------------------------------------
template<class T>
inline T &vec3<T>::operator[](const int &i)
{
	return ((T*)&x)[i];
}
//------------------------------------------------------------------------------

template<class T>
inline vec3<T> &vec3<T>::normalize()
{
	T len = length();

	if(!len)
	{
		x = y = z = 0;
		return(*this);
	}
	x /= len;
	y /= len;
	z /= len;
	return(*this);
}
//******************************************************************************
//Rotate************************************************************************
//******************************************************************************
template<class T>
inline vec3<T> &vec3<T>::rotate(const vec3<T> &normal, const T &angle)
{
	quat<T> q;
	q.rotate(normal, angle);
	*this = q.transform(*this);
	return(*this);
}
//******************************************************************************
//Length************************************************************************
//******************************************************************************
template<class T>
inline const T vec3<T>::length_sqr() const
{
	return(x*x + y*y + z*z);
}
//------------------------------------------------------------------------------
template<class T>
inline const T vec3<T>::length() const
{
	return sqrt(static_cast<T>(x*x + y*y + z*z));
}
//******************************************************************************
//Dot Product*******************************************************************
//******************************************************************************
template<class T>
const T dot(const vec3<T> &v1, const vec3<T> &v2)
{
	return(v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}
//******************************************************************************
//Cross Product*****************************************************************
//******************************************************************************
template<class T>
vec3<T> cross(const vec3<T> &v1, const vec3<T> &v2)
{
	return vec3<T>(v1.y*v2.z - v1.z*v2.y,
				   v1.z*v2.x - v1.x*v2.z,
				   v1.x*v2.y - v1.y*v2.x);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> cross(const vec4<T> &v1, const vec4<T> &v2)
{
	return vec3<T>(v1.y*v2.z - v1.z*v2.y,
				   v1.z*v2.x - v1.x*v2.z,
				   v1.x*v2.y - v1.y*v2.x);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> vec3<T>::operator^(const vec3<T> &t)
{
	return vec3<T>(y   * t.z - z   * t.y,  t.x * z   - t.z * x, x   * t.y - y   * t.x);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::operator^=(const vec3<T> &t)
{
	set(y   * t.z - z   * t.y, t.x * z   - t.z * x, x * t.y - y   * t.x);
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline const T vec3<T>::dist(const vec3<T> &v2)  const
{
	return(sqrt((v2.x - x) * (v2.x - x) + (v2.y - y) * (v2.y - y) + (v2.z - z) * (v2.z - z)));
}
//------------------------------------------------------------------------------
template<class T>
inline const T vec3<T>::sum() const
{
	return(x + y + z);
}
//------------------------------------------------------------------------------
template<class T>
inline const T angle(const vec3<T> &v1, const vec3<T> &v2)
{
	T angle = acos(dot(v1, v2) / (v1.length() * v2.length()));
	if(_isnan(angle))
	{
		return 0;
	}
	return(angle);
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> &vec3<T>::clamp(T min, T max)
{
	x = x > max ? max : x < min ? min  : x;
	y = y > max ? max : y < min ? min  : y;
	z = z > max ? max : z < min ? min  : z;
	return(*this);
}
//******************************************************************************
//Input/Output******************************************************************
//******************************************************************************
template<class T>
ostream &operator<<(ostream &out, const vec3<T> &v)
{
	return out << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
}
//------------------------------------------------------------------------------
template<class T>
istream &operator>>(istream &in, vec3<T> &v)
{
	return in >> v.x >> v.y >> v.z;
}
//******************************************************************************
//HSVtoRGB**********************************************************************
//******************************************************************************
template<class T>
vec3<T> HSVtoRGB(const vec3<T> &hsv)
{
	// guarantee valid input:
	T h = hsv.x / (T)60.0;
	while(h >= 6)	h -= 6;
	while(h <  0)	h += 6;

	T s = math::clamp((T)hsv.y, (T)0.0, (T)1.0);
	T v = math::clamp((T)hsv.z, (T)0.0, (T)1.0);

	//if sat==0, then is gray
	if(s == 0.0)
	{
		return(vec3<T>(v, v, v));
	}

	//Otherwise, get an rgb from the hue itself
	T i = floor(h);
	T f = h - i;
	T p = v * (1 - s);
	T q = v * (1 - s*f);
	T t = v * (1 - (s*(1 - f)));

	if(i == 0.0)	return(vec3<T>(v, t, p));
	if(i == 1.0)	return(vec3<T>(q, v, p));
	if(i == 2.0)	return(vec3<T>(p, v, t));
	if(i == 3.0)	return(vec3<T>(p, q, v));
	if(i == 4.0)	return(vec3<T>(t, p, v));
	if(i == 5.0)	return(vec3<T>(v, p, q));

	return(vec3<T>(0, 0, 0));
}



typedef vec3<int>                vec3i;
typedef vec3<float>              vec3f;
typedef vec3<double>             vec3d;
typedef vec3<unsigned int>       vec3u;
typedef vec3<unsigned int>       vec3ui;
typedef vec3<char>               vec3b;
typedef vec3<unsigned char>      vec3ub;
typedef vec3<short int>          vec3s;
typedef vec3<unsigned short int> vec3us;

};

