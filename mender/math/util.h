//******************************************************************************
//render/math/util.h************************************************************
//******************************************************************************

#pragma once

//Standard Library Includes
#include <cmath>
#include <climits>
#include <cfloat>

//Namespaces
using namespace std;

namespace render
{
	namespace math
	{
		#define RAD2DEG 57.2957f
		#define DEG2RAD 0.0174532f

		typedef unsigned int uint;

		double const eps     = 1e-6;
		double const eps_sqr = eps*eps;

		double const pi           = 2*std::acos(0.0);
		double const inv_pi       = 1/pi;
		double const two_pi       = 2*pi;
		double const half_pi      = pi/2;
		double const root_two     = sqrt(2.0);
		double const pi_over_180  = pi / 180.0 ;
		double const inv_root_two = 1/root_two;

		inline float  tan(const float  &radians)	{ return(tanf(radians)); }
		inline double tan(const double &radians)	{ return( tan(radians)); }

		template<class T>
		inline T radians(const T &degrees)
		{
			return(degrees * (T)pi_over_180);
		}

		template<class T>
		inline T degrees(const T &radians)
		{
			return(radians * (T)(180 * inv_pi));
		}

		template<class T>
		inline T clamp(T x, T min, T max)
		{
			return (x < min) ? min : (x > max) ? max : x;
		}

		template<class T>
		inline int round(T t)
		{
			return int(t + 0.5);
		}

		inline bool equal(const double &a, const double &b, const float &Eps = eps)	{	return(abs(a-b) <= Eps);	}
		inline bool equal(const float  &a, const float  &b, const float &Eps = eps)	{	return(abs(a-b) <= Eps);	}

#ifndef max
		inline int    max(int    &)		{	return(INT_MAX);	}
		inline float  max(float  &)		{ 	return(FLT_MAX);	}
		inline double max(double &)		{ 	return(DBL_MAX);	}
#endif

#ifndef min
		inline int    min(const int    &)		{ 	return(INT_MIN);	}
		inline float  min(const float  &)		{ 	return(FLT_MIN);	}
		inline double min(const double &)		{	return(DBL_MIN);	}
#endif

#ifndef max
		template<class T>
		inline T max(const T &a, const T &b)
		{
			return((a > b) ? a : b);
		}
#endif

#ifndef min
		template<class T>
		inline T min(const T &a, const T &b)
		{
			return((a < b) ? a : b);
		}
#endif

#ifndef max
		template<class T>
		inline T max(const T &a, const T &b, const T &c)
		{
			return(math::max(a, math::max(b, c)));

		}
#endif

#ifndef max
		template<class T>
		inline T max(const T &a, const T &b, const T &c, const T &d)
		{
			return(math::max(a, math::max(b, math::max(c, d))));
		}
#endif

#ifndef min
		template<class T>
		inline T min(const T &a, const T &b, const T &c)
		{
			return(math::min(a, math::min(b, c)));
		}
#endif

#ifndef min
		template<class T>
		inline T min(const T &a, const T &b, const T &c, const T &d)
		{
			return(math::min(a, math::min(b, math::min(c, d))));
		}
#endif
		template<class T>
		inline T smoothstep(const T &edge1, const T &edge2, const T &x)
		{
			T t = clamp<T>(((x - edge1) / (edge2 - edge1)), 0, 1);
			return(t*t*(3-2*t));
		}

		inline float Q_rsqrt( float number )
		{
			long i;
			float x2, y;
			const float threehalfs = 1.5F;

			x2 = number * 0.5F;
			y  = number;
			i  = * ( long * ) &y;                       // evil floating point bit level hacking
			i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
			y  = * ( float * ) &i;
			y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
		//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

			return y;
		}


	};
};

