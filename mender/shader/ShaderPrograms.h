//******************************************************************************
//render/shader/ShaderPrograms.h************************************************
//******************************************************************************

#pragma once

//Project Includes
#include "ShaderProgram.h"

//Standard Library Includes
#include <map>

//Render Library Includes
#include <render/time.h>

//Namespaces
using namespace render;
using namespace std;

//ShaderProgram Management Class
class ShaderPrograms
{
private:

	//ShaderProgram Manager
	static map<GLuint, ShaderProgram *> shaderPrograms;

	static Timer timer;

public:

	static void add(ShaderProgram *shaderProgram);

	static void remove(GLuint shaderID);
	static void remove(ShaderProgram *shaderProgram);

	static void refresh();

};


