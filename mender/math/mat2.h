//******************************************************************************
//render/math/mat2.h************************************************************
//******************************************************************************

#pragma once

//Project Includes
#include "vec2.h"

//Standard Library Includes
#include <iostream>
#include <cassert>

namespace render
{
template<class T>
class mat3;

template<class T>
class mat2
{
public:
union
{
	struct
	{
		T m00, m01;
		T m10, m11;
	};
	struct
	{
		T _11, _12;
		T _21, _22;
	};
	T m[4];    //array access
};

private:

	void tridiagonalize(mat2<T> &, vec2<T> &, vec2<T> &) const;
	bool   ql_factorize(mat2<T> &, vec2<T> &, vec2<T> &) const;

public:

	//Constructors
	mat2<T>();
	mat2<T>(const T &, const T &, const T &, const T &);
	mat2(const vec2<T> &, const vec2<T> &);
	mat2<T>(const mat2<T> &);
	mat2<T>(const mat3<T> &);
	mat2<T>(const T *);

	//Set
	void set(const T &, const T &, const T &, const T &);
	void set(const T *);
	void set(const mat2<T> &);
	void set(const mat3<T> &);

	//Set Rows/Cols
	inline void row(      const vec2<T> &, const unsigned int &);
	inline void row(const T &, const T  &, const unsigned int &);
	inline void col(      const vec2<T> &, const unsigned int &);
	inline void col(const T &, const T  &, const unsigned int &);

	//Get Rows/Cols
	inline vec2<T> row(const unsigned int &);
	inline vec2<T> col(const unsigned int &);

	//Zero/Clean
	void zero();
	void clean();

	//Operator()
	inline const T &operator()(const unsigned int &, const unsigned int &) const;
	inline       T &operator()(const unsigned int &, const unsigned int &);

	//Operator[]
	inline const T &operator[](const unsigned int &) const;
	inline       T &operator[](const unsigned int &);

	//Arithmetic Operators
	inline mat2<T>  operator+ (const mat2<T> &);
	inline mat2<T>  operator- (const mat2<T> &);
	inline mat2<T>  operator* (const mat2<T> &);
	inline mat2<T>  operator* (const      T  &);
	inline mat2<T> &operator+=(const mat2<T> &);
	inline mat2<T> &operator-=(const mat2<T> &);
	inline mat2<T> &operator*=(const      T  &);
	inline mat2<T> &operator*=(const mat2<T> &);

	//Equality Operators
	inline bool operator==(const mat2<T> &);
	inline bool operator!=(const mat2<T> &);

	//Assignment Operator
	inline mat2 &operator=(const mat2<T> &);

	inline operator const T*() const;
	inline operator       T*();

	//Determinant
	T determinant();

	//Invert
	bool invert();

	inline void transpose();

	inline void identity();

	inline void setInverseTranspose();


	//rotate
	inline void rotate(const T &);

	//Eigenize
	bool eigenize(mat2<T> &, vec2<T> &) const;
	bool eigenize(vec2<T> &, vec2<T> &, T &, T &) const;

};//end class mat2<T>

//Arithmetic Operators
template<class T> vec2<T> operator* (const vec2<T> &, const mat2<T> &);
template<class T> vec2<T> operator* (const mat2<T> &, const vec2<T> &);
template<class T> void    operator*=(      vec2<T> &, const mat2<T> &);

template<class T> vec2<T> operator* (const mat2<T> &, const mat2<T> &);

//Output
template<class T> ostream &operator<<(ostream &, const mat2<T> &);


//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class T>
mat2<T>::mat2()
{
	m00 = 1; m01 = 0;
	m10 = 0; m11 = 1;
}
//------------------------------------------------------------------------------
template<class T>
mat2<T>::mat2(const T *elements)
{
	memcpy(m, elements, sizeof(T)*4);
}
//------------------------------------------------------------------------------
template<class T>
mat2<T>::mat2(const vec2<T> &vx, const vec2<T> &vy)
{
	m00 = vx.x; m01 = vx.y;
	m10 = vy.x; m11 = vy.y;
}
//------------------------------------------------------------------------------
template<class T>
mat2<T>::mat2(const T &m00, const T &m01,
			  const T &m10, const T &m11)
{
	this->m00 = m00;
	this->m01 = m01;
	this->m10 = m10;
	this->m11 = m11;
}
//------------------------------------------------------------------------------
template<class T>
mat2<T>::mat2(const mat2<T> &mat)
{
	memcpy(m, mat.m, sizeof(T)*4);
}
//------------------------------------------------------------------------------
template<class T>
mat2<T>::mat2(const mat3<T> &mat)
{
	m00 = mat.m00;
	m01 = mat.m01;
	m10 = mat.m10;
	m11 = mat.m11;
}
//******************************************************************************
//Set***************************************************************************
//******************************************************************************
template<class T>
inline void mat2<T>::set(const T* elements)
{
	memcpy(m, elements, sizeof(T)*4);
}
//------------------------------------------------------------------------------
template<class T>
void mat2<T>::set(const T &m00, const T &m01,
				  const T &m10, const T &m11)
{
	this->m00 = m00;
	this->m01 = m01;
	this->m10 = m10;
	this->m11 = m11;
}
//******************************************************************************
//Set rows/columns**************************************************************
//******************************************************************************
template<class T>
inline void mat2<T>::row(const vec2<T> &v, const unsigned int &i)
{
	(*this)(i, 0) = v.x;
	(*this)(i, 1) = v.y;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat2<T>::row(const T &x, const T &y, const unsigned int &i)
{
	(*this)(i, 0) = x;
	(*this)(i, 1) = y;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat2<T>::col(const vec2<T> &v, const unsigned int &j)
{
	(*this)(0, j) = v.x;
	(*this)(1, j) = v.y;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat2<T>::col(const T &x, const T &y, const unsigned int &j)
{
	(*this)(0, j) = x;
	(*this)(1, j) = y;
}
//******************************************************************************
//Get rows/columns**************************************************************
//******************************************************************************
template<class T>
inline vec2<T> mat2<T>::row(const unsigned int &i)
{
	return(vec2<T>((*this)(i, 0), (*this)(i, 1)));
}
//------------------------------------------------------------------------------
template<class T>
inline vec2<T> mat2<T>::col(const unsigned int &j)
{
	return(vec2<T>((*this)(0, j), (*this)(1, j)));
}
//******************************************************************************
//Operator()********************************************************************
//******************************************************************************
template<class T>
inline const T &mat2<T>::operator()(const unsigned int &i, const unsigned int &j) const
{
	assert((0 <= i) && (i < 2) && (0 <= j) && (j < 2));
	return(m[i*2 + j]);
}
//------------------------------------------------------------------------------
template<class T>
inline T &mat2<T>::operator()(const unsigned int &i, const unsigned int &j)
{
	assert((0 <= i) && (i < 2) && (0 <= j) && (j < 2));
	return(m[i*2 + j]);
}
//******************************************************************************
//Operator[]********************************************************************
//******************************************************************************
template<class T>
inline const T &mat2<T>::operator[](const unsigned int &i) const
{
	assert((0 <= i) && (i < 4));
	return(m[i]);
}
//------------------------------------------------------------------------------
template<class T>
inline T &mat2<T>::operator[](const unsigned int &i)
{
	assert((0 <= i) && (i < 4));
	return(m[i]);
}
//******************************************************************************
//Arithmetic Operators**********************************************************
//******************************************************************************
template<class T>
inline mat2<T> mat2<T>::operator+(const mat2<T> &mat)
{
	return mat2(m00 + mat.m00, m01 + mat.m01,
				m10 + mat.m10, m11 + mat.m11);
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T> mat2<T>::operator-(const mat2<T> &mat)
{
	return mat2(m00 - mat.m00, m01 - mat.m01,
				m10 - mat.m10, m11 - mat.m11);
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T> mat2<T>::operator*(const mat2<T> &mat)
{
	mat2<T> matrix;

	//First Row
	matrix.m00 = m00 * mat.m00 + m01 * mat.m10;
	matrix.m01 = m00 * mat.m01 + m01 * mat.m11;

	//Second Row
	matrix.m10 = m10 * mat.m00 + m11 * mat.m10;
	matrix.m11 = m10 * mat.m01 + m11 * mat.m11;

	return matrix;
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T> &mat2<T>::operator+=(const mat2<T> &mat)
{
	m00 += mat.m00;
	m01 += mat.m01;
	m10 += mat.m10;
	m11 += mat.m11;

	return *this;
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T> &mat2<T>::operator-=(const mat2<T> &mat)
{
	m00 -= mat.m00;
	m01 -= mat.m01;
	m10 -= mat.m10;
	m11 -= mat.m11;

	return *this;
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T> &mat2<T>::operator*=(const T &t)
{
	m00 *= t;
	m01 *= t;
	m10 *= t;
	m11 *= t;

	return *this;
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T> &mat2<T>::operator*=(const mat2<T> &mat)
{
	T tmp;
	tmp = m00 * mat.m00 + m01 * mat.m10;
	m01 = m00 * mat.m01 + m01 * mat.m11;
	m00 = tmp;

	tmp = m10 * mat.m00 + m11 * mat.m10;
	m11 = m10 * mat.m01 + m11 * mat.m11;
	m10 = tmp;

	return *this;
}
//------------------------------------------------------------------------------
template<class T>
inline bool mat2<T>::operator==(const mat2<T> &m)
{
	return((this == &m) || (m00 == m.m00 && m10 == m.m10 && m01 == m.m01 && m11 == m.m11));
}
//------------------------------------------------------------------------------
template<class T>
inline bool mat2<T>::operator!=(const mat2<T> &mat)
{
	return !((*this) == mat );
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T> &mat2<T>::operator=(const mat2<T> &mat)
{
	memcpy(m, mat.m, sizeof(T)*4);
	return *this;
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T>::operator const T*() const
{
	return m;
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T>::operator T*()
{
	return m;
}
//------------------------------------------------------------------------------
template<class T>
vec2<T> operator*(const vec2<T> &v, const mat2<T> &m)
{
	return vec2<T>(m.m00 * v.x + m.m01 * v.y,
				   m.m10 * v.x + m.m11 * v.y);
}
//------------------------------------------------------------------------------
template<class T>
vec2<T> operator*(const mat2<T> &m, const vec2<T> &v)
{
	return vec2<T>(m.m00 * v.x + m.m01 * v.y,
				   m.m10 * v.x + m.m11 * v.y);
}
//------------------------------------------------------------------------------
template<class T>
void operator*=(vec2<T> &v, const mat2<T> &mat)
{
	v = v * mat;
}
//------------------------------------------------------------------------------
template<class T>
inline T mat2<T>::determinant()
{
	return(m00*m11 - m01*m10);
}
//------------------------------------------------------------------------------
template<class T>
inline bool mat2<T>::invert()
{
	T det = this->determinant();

//	if(!zero(det))
	if(det != 0.0)
	{
		return false;
	}

	det = 1 / det;

	mat2<T> c(*this);

	this->m00 =  det * c.m11;
	this->m10 = -det * c.m10;
	this->m01 = -det * c.m01;
	this->m11 =  det * c.m00;

	return true;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat2<T>::transpose()
{
	T temp = m10;
	m10 = m01;
	m01 = temp;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat2<T>::identity()
{
	m00 = 1; m01 = 0;
	m10 = 0; m11 = 1;
}
//------------------------------------------------------------------------------
template<class T>
inline void mat2<T>::setInverseTranspose()
{
	if(!invert())
	{
		return;
	}
	transpose();
}
//------------------------------------------------------------------------------
template<class T>
void mat2<T>::zero()
{
	m00 = 0; m01 = 0;
	m10 = 0; m11 = 0;
}
//------------------------------------------------------------------------------
template<class T>
void mat2<T>::set(const mat2<T> &mat)
{
	memcpy(m, mat.m, sizeof(T)*4);
}
//------------------------------------------------------------------------------
template<class T>
void mat2<T>::set(const mat3<T> &mat)
{
	m00 = mat.m00; m01 = mat.m01;
	m10 = mat.m11; m11 = mat.m[4];
}
//------------------------------------------------------------------------------
template<class T>
inline void mat2<T>::rotate(const T &angle)
{
	identity();
	m01 =  sin(angle);
	m10 = -m01;
	m11 =  m00;
}
//******************************************************************************
//Output************************************************************************
//******************************************************************************
template<class T>
ostream &operator<<(ostream &out, const mat2<T> &m)
{
	out << "mat2[" << m.m00 << ", " << m.m01 << "]" << endl;
	out << "    [" << m.m10 << ", " << m.m11 << "]" << endl;
	return(out);
}
//------------------------------------------------------------------------------
template<class T>
inline mat2<T> mat2<T>::operator*(const T &t)
{
	return mat2(m00*t, m01*t,
				m10*t, m11*t);
}

//******************************************************************************
//Eigenize**********************************************************************
//******************************************************************************
template<class T>
bool mat2<T>::eigenize(mat2<T> &ev, vec2<T> &ew) const
{
	ev = *this;
	vec2<T> subd;
	tridiagonalize(ev, ew, subd);
	if(ql_factorize(ev, ew, subd))
	{
		//sort them
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
template<class T>
bool mat2<T>::eigenize(vec2<T> &evec1, vec2<T> &evec2, T &eval1, T &eval2) const
{
	mat2<T> emat;
	vec2<T> eval;

	if(!eigenize(emat, eval))
	{
		cerr << "eigenize failed" << endl;
		return false;
	}

	if(abs(eval.x) > abs(eval.y))
	{
		evec1 = emat.col(0);
		evec2 = emat.col(1);

		eval1 = eval.x;
		eval2 = eval.y;
	}
	else
	{
		evec1 = emat.col(1);
		evec2 = emat.col(0);

		eval1 = eval.y;
		eval2 = eval.x;
	}

	return(true);
}
//------------------------------------------------------------------------------
template<class T>
void mat2<T>::tridiagonalize(mat2<T> &mat, vec2<T> &diag, vec2<T> &subd) const
{
	diag.x = mat.m00;
	diag.y = mat.m11;

	subd.x = mat.m01;
	subd.y = 0.0;

//	mat.Identity();
	mat.m00 = 1; mat.m10 = 0;
	mat.m01 = 0; mat.m11 = 1;
}
//------------------------------------------------------------------------------
template<class T>
bool mat2<T>::ql_factorize(mat2<T> &mat, vec2<T> &diag, vec2<T> &subd) const
{
	const int iMaxIter = 32;

	unsigned int i, i4;
	for(i = 0; i < iMaxIter; ++i)
	{
		if(subd[0] == 0)
		{
			break;
		}

		T g = (diag[1] - diag[0]) / (2 * subd[0]);
		T r = sqrt(g*g + 1);

		if(g < 0)
		{
			g = diag[1] - diag[0] + subd[0] / (g - r);
		}
		else
		{
			g = diag[1] - diag[0] + subd[0] / (g + r);
		}

		T fSin = (T)1;
		T fCos = (T)1;
		T p = (T)0;
		T f = fSin * subd[0];
		T b = fCos * subd[0];
		if(abs(f) >= abs(g))
		{
			fCos = g / f;
			r = sqrt(fCos * fCos + (T)1);
			fSin = ((T)1) / r;
			fCos *= fSin;
		}
		else
		{
			fSin = f / g;
			r = sqrt(fSin * fSin + (T)1);
			fCos = ((T)1) / r;
			fSin *= fCos;
		}

		g = diag[1] - p;
		r = (diag[0] - g) * fSin + ((T)2) * b * fCos;
		p = fSin * r;
		diag[1] = g + p;
		g = fCos * r - b;

		for(i4 = 0; i4 < 2; i4++)
		{
			f = mat(i4, 1);
			mat(i4, 1) = fSin * mat(i4, 0) + fCos * f;
			mat(i4, 0) = fCos * mat(i4, 0) - fSin * f;
		}

		diag[0] -= p;
		subd[0] = g;
	}

	if(i == iMaxIter)
	{
		return false;
	}

	return true;
}


typedef mat2<int>    mat2i;
typedef mat2<float>  mat2f;
typedef mat2<double> mat2d;

};//End namespace render


