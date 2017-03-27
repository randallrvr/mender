//******************************************************************************
//render/texture/Texture1D_Array.h**********************************************
//******************************************************************************

#pragma once

//Parent Include
#include "TextureT.h"


namespace render {
namespace texture {

template<class TexType, class IntFormat, class PixFormat>
class Texture1D_Array : public TextureT<tex1D_Array, TexType, IntFormat, PixFormat>
{
protected:

public:
	//Constructors
	Texture1D_Array();
};
//End class Texture

//******************************************************************************
//Constructors******************************************************************
//******************************************************************************
template<class TexType, class IntFormat, class PixFormat>
Texture1D_Array<TexType, IntFormat, PixFormat>::Texture1D_Array() : TextureT<tex1D_Array, TexType, IntFormat, PixFormat>()
{
}

};
//End namespace texture
};
//End namespace render

