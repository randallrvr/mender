//******************************************************************************
//render/math/math.cpp**********************************************************
//******************************************************************************


#include <cmath>


#include "vec3.h"


using namespace render;

//template class vec3<int>;		//sqrt can't handle int "ambiguous call to overloaded function"
template class render::vec3<float>;
//template class render::vec3<double>;

#include "vec4.h"

//template class vec4<int>;		//sqrt can't handle int "ambiguous call to overloaded function"
template class render::vec4<float>;
//template class render::vec4<double>;

//
//#include "vecN.h"
//
////template class vecN<int>;
//template class vecN<float>;
//template class vecN<double>;

#include "mat2.h"

//template class mat2<int>;
//template class mat2<float>;
//template class mat2<double>;

#include "mat3.h"

//template class mat3<int>;
template class render::mat3<float>;
//template class render::mat3<double>;


#include "mat4.h"
//
//template class mat4<int>;
template class render::mat4<float>;
//template class render::mat4<double>;

//template<class T>
//const T mat4<T>::* mat4<T>::t[16] = 
////const mat4<T>::T_ptr mat4<T>::t[16] = 
//{
//	&mat4<T>::m00, &mat4<T>::m10, &mat4<T>::m20, &mat4<T>::m30,
//	&mat4<T>::m01, &mat4<T>::m11, &mat4<T>::m21, &mat4<T>::m31,
//	&mat4<T>::m02, &mat4<T>::m12, &mat4<T>::m22, &mat4<T>::m32,
//	&mat4<T>::m03, &mat4<T>::m13, &mat4<T>::m23, &mat4<T>::m33
//};


//
//#include "matN.h"
//
//template class matN<int>;
//template class matN<float>;
//template class matN<double>;
//
//#include "matS.h"
//
//template class matS<float>;
//template class matS<double>;

#include "quat.h"

template class render::quat<float>;
//template class render::quat<double>;
