//******************************************************************************
//render/math/vec2.h************************************************************
//******************************************************************************

#pragma once

//Standard Library Includes
#include <iostream>

//Namespaces
using namespace std;

namespace render
{
template<class T>
class vec3;

template<class T>
class vec2
{
public:

	union
	{
		struct{ T x,y; };	//point coords
		struct{ T s,t; };	//texture coords
		struct{ T w,h; };	//dimensions
		T vec_array[2];
	};

	static const vec2<T> zero;

public:

	//Constructors
	vec2();
	vec2(const T &);
	vec2(const T &, const T &);
	vec2(const vec2<T> &);
	vec2(const vec3<T> &);

	//Set
	void set(const T &, const T &);

	//Assignment Operator
	vec2<T> &operator=(const vec2<T> &);
	vec2<T> &operator=(const vec3<T> &);

	//Inline Arithmetic Operators
	inline vec2<T>  operator+ (const vec2<T> &);
	inline vec2<T>  operator+ (const      T  &);
	inline vec2<T>  operator- (const vec2<T> &);
	inline vec2<T>  operator- (const      T  &);
	inline vec2<T>  operator* (const vec2<T> &);
	inline vec2<T>  operator* (const      T  &);
	inline vec2<T>  operator/ (const vec2<T> &);
	inline vec2<T>  operator/ (const      T  &);
	inline vec2<T> &operator+=(const vec2<T> &);
	inline vec2<T> &operator+=(const      T  &);
	inline vec2<T> &operator-=(const vec2<T> &);
	inline vec2<T> &operator-=(const      T  &);
	inline vec2<T> &operator*=(const vec2<T> &);
	inline vec2<T> &operator*=(const      T  &);
	inline vec2<T> &operator/=(const vec2<T> &);
	inline vec2<T> &operator/=(const      T  &);
	inline vec2<T> &operator- ();

	//Normalize
	inline vec2<T> &normalize();

	//Length
	inline const T length_sqr() const;
	inline const T length()     const;

	inline operator const T*() const;
	inline operator       T*();

	inline const T  operator[](const int &i) const;
	inline       T &operator[](const int &i);

	bool operator==(const vec2<T> &);
	bool operator!=(const vec2<T> &);

	inline void clamp(const T &, const T &);

	//Typecast
	template<class U> operator vec2<U>() { return(vec2<U>((U)x, (U)y)); }

};
//End class vec2<T>

template<class T> const vec2<T> vec2<T>::zero(0, 0);

//Arithmetic Operators
template<class T> vec2<T> operator*(const      T  &, const vec2<T> &);
template<class T> vec2<T> operator*(const vec2<T> &, const      T  &);
template<class T> vec2<T> operator+(const vec2<T> &, const vec2<T> &);
template<class T> vec2<T> operator-(const vec2<T> &, const vec2<T> &);

//Dot Product/Perpendicular Dot Product
template<class T> T  dot(const vec2<T> &, const vec2<T> &);
template<class T> T perp(const vec2<T> &, const vec2<T> &);

//Input/Output
template<class T> ostream &operator<<(ostream &, const vec2<T> &);
template<class T> istream &operator>>(istream &,       vec2<T> &);


//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class T>
vec2<T>::vec2()
{
	x = y = 0;
}
//------------------------------------------------------------------------------
template<class T>
vec2<T>::vec2(const T &t)
{
	this->x = t;
	this->y = t;
}
//------------------------------------------------------------------------------
template<class T>
vec2<T>::vec2(const T &x, const T &y)
{
	this->x = x;
	this->y = y;
}
//------------------------------------------------------------------------------
template<class T>
vec2<T>::vec2(const vec2<T> &v)
{
	x = v.x;
	y = v.y;
}
//------------------------------------------------------------------------------
template<class T>
vec2<T>::vec2(const vec3<T> &v)
{
	x = v.x;
	y = v.y;
}
//******************************************************************************
//Set***************************************************************************
//******************************************************************************
template<class T>
void vec2<T>::set(const T &x, const T &y)
{
	this->x = x;
	this->y = y;
}
//******************************************************************************
//Assignment Operator***********************************************************
//******************************************************************************
template<class T>
vec2<T> &vec2<T>::operator=(const vec2<T> &v)
{
	x = v.x;
	y = v.y;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
vec2<T> &vec2<T>::operator=(const vec3<T> &v)
{
	x = v.x;
	y = v.y;
	return(*this);
}
//******************************************************************************
//Arithmetic Operators**********************************************************
//******************************************************************************
template<class T>
inline vec2<T> vec2<T>::operator+(const vec2<T> &v)
{
	return vec2<T>(v.x + x, v.y + y);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec2<T>::operator+(const T &t)
{
	return(vec2<T>(x + t, y + t));
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec2<T>::operator-(const vec2<T> &v)
{
	return vec2<T>(-v.x + x, -v.y + y);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec2<T>::operator-(const T &t)
{
	return(vec2<T>(x - t, y - t));
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec2<T>::operator*(const T &scale)
{
	return vec2<T>(x*scale, y*scale);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec2<T>::operator*(const vec2<T> &v)
{
	return vec2<T>(v.x * x, v.y * y);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec2<T>::operator/(const vec2<T> &v)
{
	return vec2<T>(x / v.x, y / v.y);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> vec2<T>::operator/(const T &scale)
{
	if(scale)
	{
		return vec2<T>(x/scale, y/scale);
	}
	return vec2<T>(0, 0);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> &vec2<T>::operator+=(const T &t)
{
	x += t;
	y += t;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> &vec2<T>::operator+=(const vec2<T> &v)
{
	x += v.x;
	y += v.y;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> &vec2<T>::operator-=(const T &t)
{
	x -= t;
	y -= t;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> &vec2<T>::operator-=(const vec2<T> &v)
{
	x -= v.x;
	y -= v.y;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> &vec2<T>::operator*=(const T &scale)
{
	x *= scale;
	y *= scale;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> &vec2<T>::operator*=(const vec2<T> &v)
{
	x *= v.x;
	y *= v.y;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> &vec2<T>::operator/=(const T &scale)
{
	if(scale)
	{
		x /= scale;
		y /= scale;
	}
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> &vec2<T>::operator/=(const vec2<T> &v)
{
	x /= v.x;
	y /= v.y;
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> &vec2<T>::operator-()
{
	x = -x;
	y = -y;

	return(*this);
}
//******************************************************************************
//Friend Arithmetic Operators***************************************************
//******************************************************************************
template<class T>
vec2<T> operator*(const T &c, const vec2<T> &v)
{
	return vec2<T>(c*v.x, c*v.y);
}
//------------------------------------------------------------------------------
template<class T>
vec2<T> operator*(const vec2<T> &v, const T &c)
{
	return vec2<T>(c*v.x, c*v.y);
}
//------------------------------------------------------------------------------
template<class T>
vec2<T> operator+(const vec2<T> &l, const vec2<T> &r)
{
	return vec2<T>(l.x+r.x, l.y+r.y);
}
//------------------------------------------------------------------------------
template<class T>
vec2<T> operator-(const vec2<T> &l, const vec2<T> &r)
{
	return vec2<T>(l.x-r.x, l.y-r.y);
}
//******************************************************************************
//Dot product*******************************************************************
//******************************************************************************
template<class T>
T dot(const vec2<T> &v1, const vec2<T> &v2)
{
	return(v1.x * v2.x + v1.y * v2.y);
}
//******************************************************************************
//Perp product******************************************************************
//******************************************************************************
template<class T>
T perp(const vec2<T> &v1, const vec2<T> &v2)
{
	return(v1.x * v2.y - v1.y * v2.x);
}
//******************************************************************************
//Normalize*********************************************************************
//******************************************************************************
template<class T>
inline vec2<T> &vec2<T>::normalize()
{
	T len = length();

	if(!len)
	{
		x = y = 0;
		return(*this);
	}
	x /= len;
	y /= len;

	return(*this);
}
//******************************************************************************
//Length************************************************************************
//******************************************************************************
template<class T>
inline const T vec2<T>::length_sqr() const
{
	return(x*x + y*y);
}
//------------------------------------------------------------------------------
template<class T>
inline const T vec2<T>::length() const
{
	return(sqrt(x*x + y*y));
}
//******************************************************************************
//Pointer Reference*************************************************************
//******************************************************************************
template<class T>
inline vec2<T>::operator const T*() const
{
	return &x;
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T>::operator T*()
{
	return &x;
}
//******************************************************************************
//Array Access******************************************************************
//******************************************************************************
template<class T>
inline const T  vec2<T>::operator[](const int &i) const
{
	return ((T*)&x)[i];
}
//------------------------------------------------------------------------------
template<class T>
inline T &vec2<T>::operator[](const int &i)
{
	return ((T*)&x)[i];
}
//******************************************************************************
//Equality Operators************************************************************
//******************************************************************************
template<class T>
bool vec2<T>::operator==(const vec2<T> &v)
{
	return(x == v.x && y == v.y);
}
//------------------------------------------------------------------------------
template<class T>
bool vec2<T>::operator!=(const vec2<T> &v)
{
	return !(x == v.x && y == v.y);
}
//******************************************************************************
//Clamp*************************************************************************
//******************************************************************************
template<class T>
inline void vec2<T>::clamp(const T &min, const T &max)
{
	x = x > max ? max : x < min ? min  : x;
	y = y > max ? max : y < min ? min  : y;
}
//******************************************************************************
//Input/Output******************************************************************
//******************************************************************************
template<class T>
ostream &operator<<(ostream &out, const vec2<T> &v)
{
	return out << "vec2(" << v.x << ", " << v.y << ")";
}
//------------------------------------------------------------------------------
template<class T>
istream &operator>>(istream &in, vec2<T> &v)
{
	return in >> v.x >> v.y;
}


typedef vec2<int>                vec2i;
typedef vec2<float>              vec2f;
typedef vec2<double>             vec2d;
typedef vec2<unsigned int>       vec2u;
typedef vec2<unsigned int>       vec2ui;
typedef vec2<char>               vec2b;
typedef vec2<unsigned char>      vec2ub;
typedef vec2<short int>          vec2s;
typedef vec2<unsigned short int> vec2us;

};
//End namespace render


