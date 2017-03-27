//*****************************************************************************
//AssetBufferObjects.h*********************************************************
//*****************************************************************************

#include "AssetBase.h"

class AssetBufferObjects : public AssetBase
{
public:

	void generate();
	void render()	{}
	void render(const mat4f &, const mat4f &);
	void render(const mat4f &, const mat4f &, const mat4f &);
	void render_shaderless();

protected:
	void render_iterative(const mat4f &, const mat4f &, const mat4f &);
};