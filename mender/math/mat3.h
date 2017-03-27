//******************************************************************************
//render/math/mat3.h************************************************************
//******************************************************************************

#pragma once

//Project Includes
#include "vec3.h"

//Standard Library Includes
#include <iostream>
#include <cstring>

namespace render
{
	template<class T> 
	class mat2;

	template<class T> 
	class mat3
	{
	public:

		static const mat3<T> identity;
		static const mat3<T> zero;

	public:
		union
		{
			struct
			{
				T m00, m01, m02;
				T m10, m11, m12;
				T m20, m21, m22;
			};
			struct
			{
				T _11, _12, _13;
				T _21, _22, _23;
				T _31, _32, _33;
			};
			T m[9];    // array access
		};
	public:

		//Constructors
		mat3<T>();
		mat3<T>(const T &, const T &, const T &, const T &, const T &, const T &, const T &, const T &, const T &);
		mat3<T>(const vec3<T> &, const vec3<T> &, const vec3<T> &);
		mat3<T>(const mat2<T> &);
		mat3<T>(const mat3<T> &);
		mat3<T>(const T *);

		//Set
		void set(const T *);
		void set(const T &, const T &, const T &, const T &, const T &, const T &, const T &, const T &, const T &);
		void set(const vec3<T> &, const vec3<T> &, const vec3<T> &);
		void set(const mat3<T> &);

		//Set Rows/Cols
		inline void row(                 const vec3<T> &, const unsigned int &);
		inline void row(const T &, const T &, const T  &, const unsigned int &);
		inline void col(                 const vec3<T> &, const unsigned int &);
		inline void col(const T &, const T &, const T  &, const unsigned int &);

		//Get Rows/Cols
		inline vec3<T> row(const unsigned int &);
		inline vec3<T> col(const unsigned int &);

		//Operator()
		inline const T &operator()(const unsigned int &, const unsigned int &) const;
		inline       T &operator()(const unsigned int &, const unsigned int &);

		//Operator[]
		inline const T &operator[](const unsigned int &) const;
		inline       T &operator[](const unsigned int &);

		//Arithmetic Operators
		inline mat3<T>  operator+ (const mat3<T> &);
		inline mat3<T>  operator- (const mat3<T> &);
		inline mat3<T>  operator* (const mat3<T> &);
		inline mat3<T>  operator* (const      T  &);
		inline mat3<T>  operator/ (const      T  &);
		inline mat3<T> &operator+=(const mat3<T> &);
		inline mat3<T> &operator-=(const mat3<T> &);
		inline mat3<T> &operator*=(const      T  &);
		inline mat3<T> &operator*=(const mat3<T> &);
		inline mat3<T> &operator/=(const      T  &);

		//Equality Operators
		inline bool operator==(const mat3<T> &);
		inline bool operator!=(const mat3<T> &);

		inline mat3 &operator= (const mat3<T> &);

		inline operator const T*() const;
		inline operator T*();

		//Determinant
		inline T determinant();


		inline void scales(const vec3<T> &);
		inline void scales(T, T, T);

		//Transpose/Invert
		inline void transpose();
		inline bool invert();
		inline void setInverseTranspose();

		//Rotations
		inline void rotate_axis(T, const vec3<T> &);
		inline void rotateX(const T &);
		inline void rotateY(const T &);
		inline void rotateZ(const T &);
		inline void rotateXYZ(const vec3<T> &);
		inline void rotateXYZ(const T &, const T &, const T &);

		//Eigen Stuff
		bool    eigenvalues(vec3<T> &, vec3<T> &, vec3<T> &, T &, T &, T &);
		vec3<T> eigenvector(const T &);
	   
	};

	template<class T>
	const mat3<T> mat3<T>::identity(1, 0, 0,
	                                0, 1, 0,
	                                0, 0, 1);

	template<class T>
	const mat3<T> mat3<T>::zero(0, 0, 0,
	                            0, 0, 0,
	                            0, 0, 0);



	template<class T> mat3<T> adjugate(const mat3<T> &m);
	template<class T> mat3<T> inverse(const mat3<T> &m);


	template<class T> ostream &operator<<(ostream &, const mat3<T> &);

//******************************************************************************
//render/math/mat3.hpp**********************************************************
//******************************************************************************

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class T>
mat3<T>::mat3()
{
	*this = mat3<T>::identity;
}
//------------------------------------------------------------------------------
template<class T>
mat3<T>::mat3(const T *elements)
{
	memcpy(m, elements, sizeof(T)*9);
}
//------------------------------------------------------------------------------
template<class T>
mat3<T>::mat3(const vec3<T> &vx, const vec3<T> &vy, const vec3<T> &vz)
{
	m00 = vx.x; m01 = vx.y; m02 = vx.z;
	m10 = vy.x; m11 = vy.y; m12 = vy.z;
	m20 = vz.x; m21 = vz.y; m22 = vz.z;
}
//------------------------------------------------------------------------------
template<class T>
mat3<T>::mat3(const mat2<T> &mat)
{
	m00 = mat.m00; m01 = mat.m01; m02 = 0;
	m10 = mat.m10; m11 = mat.m11; m12 = 0;
	m20 = 0      ; m21 = 0      ; m22 = 0;
}
//------------------------------------------------------------------------------
template<class T>
mat3<T>::mat3(const T &m00, const T &m01, const T &m02,
			  const T &m10, const T &m11, const T &m12,
			  const T &m20, const T &m21, const T &m22)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02;
	this->m10 = m10; this->m11 = m11; this->m12 = m12;
	this->m20 = m20; this->m21 = m21; this->m22 = m22;
}
//------------------------------------------------------------------------------
template<class T>
mat3<T>::mat3(const mat3<T> &mat)
{
	memcpy(m, mat.m, sizeof(T)*9);
}
//******************************************************************************
//Set***************************************************************************
//******************************************************************************
template<class T>
inline void mat3<T>::set(const T* elements)
{
	memcpy(m, elements, sizeof(T)*9);
}
//------------------------------------------------------------------------------
template<class T>
void mat3<T>::set(const T &m00, const T &m01, const T &m02,
				  const T &m10, const T &m11, const T &m12,
				  const T &m20, const T &m21, const T &m22)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02;
	this->m10 = m10; this->m11 = m11; this->m12 = m12;
	this->m20 = m20; this->m21 = m21; this->m22 = m22;
}
//------------------------------------------------------------------------------
template<class T>
void mat3<T>::set(const vec3<T> &vx, const vec3<T> &vy, const vec3<T> &vz)
{
	m00 = vx.x; m01 = vx.y; m02 = vx.z;
	m10 = vy.x; m11 = vy.y; m12 = vy.z;
	m20 = vz.x; m21 = vz.y; m22 = vz.z;
}
//******************************************************************************
//Set rows/columns**************************************************************
//******************************************************************************
template<class T>
inline void mat3<T>::row(const vec3<T> &v, const unsigned int &i)
{
	(*this)(i, 0) = v.x;
	(*this)(i, 1) = v.y;
	(*this)(i, 2) = v.z;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::row(const T &x, const T &y, const T &z, const unsigned int &i)
{
	(*this)(i, 0) = x;
	(*this)(i, 1) = y;
	(*this)(i, 2) = z;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::col(const vec3<T> &v, const unsigned int &j)
{
	(*this)(0, j) = v.x;
	(*this)(1, j) = v.y;
	(*this)(2, j) = v.z;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::col(const T &x, const T &y, const T &z, const unsigned int &j)
{
	(*this)(0, j) = x;
	(*this)(1, j) = y;
	(*this)(2, j) = z;
}
//******************************************************************************
//Get rows/columns**************************************************************
//******************************************************************************
template<class T>
inline vec3<T> mat3<T>::row(const unsigned int &i)
{
	return(vec3<T>((*this)(i, 0), (*this)(i, 1), (*this)(i, 2)));
}
//------------------------------------------------------------------------------
template<class T>
inline vec3<T> mat3<T>::col(const unsigned int &j)
{
	return(vec3<T>((*this)(0, j), (*this)(1, j), (*this)(2, j)));
}
//******************************************************************************
//Operator()********************************************************************
//******************************************************************************
template<class T>
inline const T &mat3<T>::operator()(const unsigned int &i, const unsigned int &j) const
{
	assert(/*(0 <= i) &&*/ (i < 3) && /*(0 <= j) &&*/ (j < 3));
	return(m[i*3 + j]);
}
//------------------------------------------------------------------------------
template<class T>
inline T &mat3<T>::operator()(const unsigned int &i, const unsigned int &j)
{
	assert(/*(0 <= i) &&*/ (i < 3) && /*(0 <= j) &&*/ (j < 3));
	return(m[i*3 + j]);
}
//******************************************************************************
//Operator[]********************************************************************
//******************************************************************************
template<class T>
inline const T &mat3<T>::operator[](const unsigned int &i) const
{
	assert(/*(0 <= i) &&*/ (i < 9));
	return(m[i]);
}
//------------------------------------------------------------------------------
template<class T>
inline T &mat3<T>::operator[](const unsigned int &i)
{
	assert(/*(0 <= i) &&*/ (i < 9));
	return(m[i]);
}
//******************************************************************************
//Arithmetic Operators**********************************************************
//******************************************************************************
template<class T>
inline mat3<T> mat3<T>::operator+(const mat3<T> &mat)
{
	return mat3(m00 + mat.m00, m01 + mat.m01, m02 + mat.m02,
				m10 + mat.m10, m11 + mat.m11, m12 + mat.m12,
				m20 + mat.m20, m21 + mat.m21, m22 + mat.m22);
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> mat3<T>::operator-(const mat3<T> &mat)
{
	return mat3(m00 - mat.m00, m01 - mat.m01, m02 - mat.m02,
				m10 - mat.m10, m11 - mat.m11, m12 - mat.m12,
				m20 - mat.m20, m21 - mat.m21, m22 - mat.m22);
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> mat3<T>::operator*(const mat3<T> &mat)
{
	mat3<T> matrix;

	//First Row
	matrix.m00 = m00 * mat.m00 + m01 * mat.m10 + m02 * mat.m20;
	matrix.m01 = m00 * mat.m01 + m01 * mat.m11 + m02 * mat.m21;
	matrix.m02 = m00 * mat.m02 + m01 * mat.m12 + m02 * mat.m22;

	//Second Row
	matrix.m10 = m10 * mat.m00 + m11 * mat.m10 + m12 * mat.m20;
	matrix.m11 = m10 * mat.m01 + m11 * mat.m11 + m12 * mat.m21;
	matrix.m12 = m10 * mat.m02 + m11 * mat.m12 + m12 * mat.m22;

	//Third Row
	matrix.m20 = m20 * mat.m00 + m21 * mat.m10 + m22 * mat.m20;
	matrix.m21 = m20 * mat.m01 + m21 * mat.m11 + m22 * mat.m21;
	matrix.m22 = m20 * mat.m02 + m21 * mat.m12 + m22 * mat.m22;

	return matrix;
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> &mat3<T>::operator+=(const mat3<T> &mat)
{
	for(unsigned int i = 0; i < 9; i++)
	{
		m[i] += mat.m[i];
	}
	return *this;
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> &mat3<T>::operator-=(const mat3<T> &mat)
{
	for(unsigned int i = 0; i < 9; i++)
	{
		m[i] -= mat.m[i];
	}
	return *this;
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> &mat3<T>::operator*=(const T &t)
{
	for(unsigned int i = 0; i < 9; i++)
	{
		m[i] *= t;
	}
	return *this;
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> &mat3<T>::operator/=(const T &t)
{
	for(unsigned int i = 0; i < 9; i++)
	{
		m[i] /= t;
	}
	return *this;
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> mat3<T>::operator*(const T &t)
{
	return mat3(m00*t, m01*t, m02*t,
				m10*t, m11*t, m12*t,
				m20*t, m21*t, m22*t);
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> mat3<T>::operator/(const T &t)
{
	return mat3(m00/t, m01/t, m02/t,
				m10/t, m11/t, m12/t,
				m20/t, m21/t, m22/t);
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> &mat3<T>::operator*=(const mat3<T> &mat)
{
	mat3<T> m;
	m.m00 = m00*mat.m00 + m01*mat.m10 + m02*mat.m20;
	m.m01 = m00*mat.m01 + m01*mat.m11 + m02*mat.m21;
	m.m02 = m00*mat.m02 + m01*mat.m12 + m02*mat.m22;

	m.m10 = m10*mat.m00 + m11*mat.m10 + m12*mat.m20;
	m.m11 = m10*mat.m01 + m11*mat.m11 + m12*mat.m21;
	m.m12 = m10*mat.m02 + m11*mat.m12 + m12*mat.m22;

	m.m20 = m20*mat.m00 + m21*mat.m10 + m22*mat.m20;
	m.m21 = m20*mat.m01 + m21*mat.m11 + m22*mat.m21;
	m.m22 = m20*mat.m02 + m21*mat.m12 + m22*mat.m22;

	memcpy(m, mat.m, sizeof(T)*9);
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline bool mat3<T>::operator==(const mat3<T> &mat)
{
	return memcmp(m, mat.m, sizeof(T)*9) == 0;
}
//------------------------------------------------------------------------------
template<class T>
inline bool mat3<T>::operator!=(const mat3<T> &mat)
{
	return memcmp(m, mat.m, sizeof(T)*9) != 0;
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T> &mat3<T>::operator=(const mat3<T> &mat)
{
	memcpy(m, mat.m, sizeof(T)*9);
	return(*this);
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T>::operator const T*() const
{
	return(m);
}
//------------------------------------------------------------------------------
template<class T>
inline mat3<T>::operator T*()
{
	return(m);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator*(const vec3<T> &v, const mat3<T> &mat)
{
	return vec3<T>(mat.m00*v.x + mat.m10*v.y + mat.m20*v.z,
				   mat.m01*v.x + mat.m11*v.y + mat.m21*v.z,
				   mat.m02*v.x + mat.m12*v.y + mat.m22*v.z);
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> operator*(const mat3<T> &mat,const vec3<T> &v)
{
	return vec3<T>(v.x * mat.m00 + v.y * mat.m01 + v.z * mat.m02,
				   v.x * mat.m10 + v.y * mat.m11 + v.z * mat.m12,
				   v.x * mat.m20 + v.y * mat.m21 + v.z * mat.m22);

}
//------------------------------------------------------------------------------
template<class T>
vec4<T> operator*(const mat3<T> &mat, const vec4<T> &v)
{
	return vec4<T>(v.x * mat.m00 + v.y * mat.m01 + v.z * mat.m02,
				   v.x * mat.m10 + v.y * mat.m11 + v.z * mat.m12,
				   v.x * mat.m20 + v.y * mat.m21 + v.z * mat.m22,
				   v.w);
}
//------------------------------------------------------------------------------
template<class T>
void operator*=(vec3<T> &v, const mat3<T> &mat)
{
	v.set(mat.m00*v.x + mat.m10*v.y + mat.m20*v.z,
		  mat.m01*v.x + mat.m11*v.y + mat.m21*v.z,
		  mat.m02*v.x + mat.m12*v.y + mat.m22*v.z);
}
//------------------------------------------------------------------------------
template<class T>
inline T mat3<T>::determinant()
{
	return(m00*(m11*m22 - m21*m12) + m01*(m20*m12 - m10*m22) + m02*(m10*m21 - m20*m11));
}
//------------------------------------------------------------------------------
template<class T>
inline bool mat3<T>::invert()
{
	int i, j, k, swap;
	T p[9], t;

	memcpy(p, m, 9*sizeof(T));

	for(i = 0; i < 3; i++)
	{
		swap = i;
		for (j = i + 1; j < 3; j++)
		{
			if (fabs(p[j*3 + i]) >  fabs(p[i*3 + i]))
			{
				swap = j;
			}
		}
		if(swap != i)
		{
			for (k = 0; k < 3; k++)
			{
				t             = p[   i*3 + k];
				p[   i*3 + k] = p[swap*3 + k];
				p[swap*3 + k] = t;

				t             = m[   i*3 + k];
				m[   i*3 + k] = m[swap*3 + k];
				m[swap*3 + k] = t;
			}
		}

		if(!p[i*3 + i])
		{
			return false;
		}

		t = p[i*3 + i];

		for(k = 0; k < 3; k++)
		{
			p[i*3 + k] /= t;
			m[i*3 + k]  = m[i*3 + k] / t;
		}

		for (j = 0; j < 3; j++)
		{
			if (j != i)
			{
				t = p[j*3 + i];
				for(k = 0; k < 3; k++)
				{
					p[j*3 + k] -= p[i*3 + k] * t;
					m[j*3 + k]  = m[j*3 + k] - m[i*3 + k] * t;
				}
			}
		}
	}
	return true;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::scales(const vec3<T> &axis)
{
	m00 = axis.x;
	m11 = axis.y;
	m22 = axis.z;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::scales(T x, T y, T z)
{
	m00 = x;
	m11 = y;
	m22 = z;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::rotate_axis(T angle, const vec3<T> &axis)
{
	T sinAngle = sin(angle);
	T cosAngle = cos(angle);

	T oneMinusCosAngle = static_cast<T>(1.0) - cosAngle;


	m00 = (axis.x)*(axis.x) + cosAngle*(1-(axis.x)*(axis.x));
	m10 = (axis.x)*(axis.y)*(oneMinusCosAngle) - sinAngle*axis.z;
	m20 = (axis.x)*(axis.z)*(oneMinusCosAngle) + sinAngle*axis.y;

	m01 = (axis.x)*(axis.y)*(oneMinusCosAngle) + sinAngle*axis.z;
	m11 = (axis.y)*(axis.y) + cosAngle*(1-(axis.y)*(axis.y));
	m21 = (axis.y)*(axis.z)*(oneMinusCosAngle) - sinAngle*axis.x;

	m02 = (axis.x)*(axis.z)*(oneMinusCosAngle) - sinAngle*axis.y;
	m12 = (axis.y)*(axis.z)*(oneMinusCosAngle) + sinAngle*axis.x;
	m22 = (axis.z)*(axis.z) + cosAngle*(1-(axis.z)*(axis.z));
}

//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::transpose()
{
	T temp;
	temp = m10;	m10 = m01;	m01 = temp;
	temp = m20;	m20 = m02;	m02 = temp;
	temp = m21;	m21 = m12;	m12 = temp;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::setInverseTranspose()
{
	if(!invert())
	{
		return;
	}
	transpose();
}
//------------------------------------------------------------------------------
template<class T>
void mat3<T>::set(const mat3<T> &matrix)
{
	memcpy(m, matrix.m, sizeof(T)*9);
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::rotateX(const T &angle)
{
	m11 =  cos(angle);
	m12 =  sin(angle);
	m21 = -m20;
	m22 =  m12;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::rotateY(const T &angle)
{
	m00 =  cos(angle);
	m02 =  sin(angle);
	m20 = -m02;
	m22 =  m00;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::rotateZ(const T &angle)
{
	m00 =  cos(angle);
	m01 =  sin(angle);
	m10 = -m01;
	m11 =  m00;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::rotateXYZ(const vec3<T> &v)
{
	rotateXYZ(v.x, v.y, v.z);
}
//------------------------------------------------------------------------------
template<class T>
inline void mat3<T>::rotateXYZ(const T &x, const T &y,const T &z)
{
	T cosX = cos(x);
	T cosY = cos(y);
	T cosZ = cos(z);

	T sinX = sin(x);
	T sinY = sin(y);
	T sinZ = sin(z);

	set(cosY * cosZ + sinX * sinY * sinZ,   -cosX * sinZ,    sinX * cosY * sinZ - sinY * cosZ,
		cosY * sinZ - sinX * sinY * cosZ,    cosX * cosZ,   -sinY * sinZ - sinX * cosY * cosZ,
		cosX * sinY,                         sinX,           cosX * cosY                     );
}
//******************************************************************************
//Adjugate**********************************************************************
//******************************************************************************
template<class T>
inline mat3<T> adjugate(const mat3<T> &m)
{
	return mat3<T>(m.m[4]*m.m[8]-m.m[5]*m.m[7], m.m[2]*m.m[7]-m.m[1]*m.m[8], m.m[1]*m.m[5]-m.m[2]*m.m[4],
	               m.m[5]*m.m[6]-m.m[3]*m.m[8], m.m[0]*m.m[8]-m.m[2]*m.m[6], m.m[2]*m.m[3]-m.m[0]*m.m[5],
	               m.m[3]*m.m[7]-m.m[4]*m.m[6], m.m[1]*m.m[6]-m.m[0]*m.m[7], m.m[0]*m.m[4]-m.m[1]*m.m[3]);
}
//******************************************************************************
//Inverse***********************************************************************
//******************************************************************************
template<class T>
inline mat3<T> inverse(const mat3<T> &m)
{
//	mat3<T> mInv = m;
//	mInv.invert();
//	return mInv;


	T OneOverDeterminant = static_cast<T>(1) / (
			+ m.m00 * (m.m11 * m.m22 - m.m21 * m.m12)
			- m.m10 * (m.m01 * m.m22 - m.m21 * m.m02)
			+ m.m20 * (m.m01 * m.m12 - m.m11 * m.m02));

	mat3<T> Inverse;
	Inverse.m00 = + (m.m11 * m.m22 - m.m21 * m.m12) * OneOverDeterminant;
	Inverse.m10 = - (m.m10 * m.m22 - m.m20 * m.m12) * OneOverDeterminant;
	Inverse.m20 = + (m.m10 * m.m21 - m.m20 * m.m11) * OneOverDeterminant;
	Inverse.m01 = - (m.m01 * m.m22 - m.m21 * m.m02) * OneOverDeterminant;
	Inverse.m11 = + (m.m00 * m.m22 - m.m20 * m.m02) * OneOverDeterminant;
	Inverse.m21 = - (m.m00 * m.m21 - m.m20 * m.m01) * OneOverDeterminant;
	Inverse.m02 = + (m.m01 * m.m12 - m.m11 * m.m02) * OneOverDeterminant;
	Inverse.m12 = - (m.m00 * m.m12 - m.m10 * m.m02) * OneOverDeterminant;
	Inverse.m22 = + (m.m00 * m.m11 - m.m10 * m.m01) * OneOverDeterminant;

	return Inverse;
}

//******************************************************************************
//Eigen Value/Vector Stuff******************************************************
//******************************************************************************
template<class T>
bool mat3<T>::eigenvalues(vec3<T> &evec1, vec3<T> &evec2, vec3<T> &evec3, T &eval1, T &eval2, T &eval3)
{
	T a = -1;
	T b = m00 + m11 + m22;
	T c = m10*m01 + m20*m02 + m12*m21 - m00*m11 - m00*m22 - m11*m22;
	T d = m00*(m11*m22 - m21*m12) + m01*(m20*m12 - m10*m22) + m02*(m10*m21 - m20*m11);
	T f = (((T)3.0*c / a) - (b*b / (a*a))) / (T)3.0;
	T g = (((T)2.0*b*b*b / (a*a*a)) - ((T)9.0*b*c / (a*a)) + ((T)27.0*d / a)) / (T)27.0;
	T h = (g*g / (T)4.0) + (f*f*f) / (T)27.0;

	if(h > 0)
	{
		return false;
	}
	else
	{
		if( h != 0 )
		{
			T i = sqrt(-(f*f*f) / (T)27.0);
			T j = pow(static_cast<T>(i), static_cast<T>(1.0/3.0));

			T k = acos(-(g / ((T)2.0*i)));
			//T l = j * -1.0;
			T m = cos(k / 3.0f);
			T n = sqrt(3.0f) * sin(k / 3.0f);
			T p = (b / 3.0f*a) * -1;
			eval1 = static_cast<T>(2.0 * j * cos(k / 3.0f) - (b / (3.0f * a)));
			eval2 = -j * (m + n) + p;
			eval3 = -j * (m - n) + p;
		}
		else
		{
			eval1 = eval2 = eval3 = pow(static_cast<T>(d / a), static_cast<T>(1.0 / 3.0)) * -1;
		}

		//find the eigenvectors now that we have the three eigenvalues
		evec1 = eigenvector(eval1);
		evec2 = eigenvector(eval2);
		evec3 = eigenvector(eval3);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
template<class T>
vec3<T> mat3<T>::eigenvector(const T &eval)
{
	vec3<T> evec;

	T den1 = (m11 - eval) * (m22 - eval);
	T den2 =  m12 * m21;

	if(den1 != den2)
	{
		evec.x = 1;
		evec.y = (m12 * m20 - m10 * (m22 - eval)) / (den1 - den2);
		evec.z = (m21 * m10 - m20 * (m11 - eval)) / (den1 - den2);
	}
	else
	{
		den1 = (m00 - eval) * (m11 - eval);
		den2 =  m01 * m10;

		//try just replacing z - should almost always pass this test
		if(den1 != den2)
		{
			evec.x = (m01*m12 - m02 * (m11 - eval)) / (den1 - den2);
			evec.y = (m10*m02 - m12 * (m00 - eval)) / (den1 - den2);
			evec.z = 1;
		}
		else
		{
			//if z didn't work, now try y
			den1 = (m00 - eval) * (m22 - eval);
			den2 =  m02 * m20;
			if(den1 != den2)
			{
				evec.x = (m02 * m21 - m01 * (m22 - eval)) / (den1 - den2);
				evec.y = 1;
				evec.z = (m20 * m01 - m21 * (m00 - eval)) / (den1 - den2);
			}
			else
			{
				evec.x = 1;
				evec.y = 0;
				evec.z = 0;
			}
		}
	}
	evec.normalize();
	return(evec);
}

//******************************************************************************
//Output************************************************************************
//******************************************************************************
template<class T>
ostream &operator<<(ostream &out, const mat3<T> &m)
{
	out << "mat3[" << m.m00 << ", " << m.m01 << ", "<< m.m02 << "]" << endl;
	out << "    [" << m.m10 << ", " << m.m11 << ", "<< m.m12 << "]" << endl;
	out << "    [" << m.m20 << ", " << m.m21 << ", "<< m.m22 << "]" << endl;
	return(out);
}


	typedef mat3<int>    mat3i;
	typedef mat3<float>  mat3f;
	typedef mat3<double> mat3d;
};

