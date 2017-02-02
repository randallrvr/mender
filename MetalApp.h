//*****************************************************************************
// MetalApp.h *****************************************************************
//*****************************************************************************

#pragma once

// Standard Library Includes
#include <iostream>
#include <vector>

// Render Library Includes
#include <mender/app.h>


//Namespaces
using namespace std;
using namespace render;

class MetalApp : public AppMacOS
{
private:


public:

	//Constructor
	MetalApp(string, int, int, const std::vector<string> &);

	//Implementations
	void init();
	void initCam();
	void render();
	void update();

};


