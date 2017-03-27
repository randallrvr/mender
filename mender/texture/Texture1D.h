//******************************************************************************
//render/texture/Texture1D.h****************************************************
//******************************************************************************

#pragma once

//Parent Include
#include "TextureT.h"


namespace render
{
namespace texture
{


template<class TexType, class IntFormat, class PixFormat>
class Texture1D : public TextureT<tex1D, TexType, IntFormat, PixFormat>
{
protected:
	GLuint l;

public:
	//Constructors
	Texture1D(GLuint);
	Texture1D(const string &);
};
//End class Texture

template<class TexType, class IntFormat, class PixFormat>
Texture1D<TexType, IntFormat, PixFormat>::Texture1D(GLuint l) : TextureT<tex1D, TexType, IntFormat, PixFormat>()
{
	this->l = l;
}


};
//End namespace texture
};
//End namespace render
