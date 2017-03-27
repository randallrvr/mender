//******************************************************************************
//ShaderPrograms.cpp************************************************************
//******************************************************************************

//Header Include
#include "ShaderPrograms.h"


//Initialize Static Members
map<GLuint, ShaderProgram *> ShaderPrograms::shaderPrograms;
Timer ShaderPrograms::timer;

//******************************************************************************
//Initialize Shaders (must be called before shaders can be used)****************
//******************************************************************************
void ShaderPrograms::add( ShaderProgram *shaderProgram )
{
	shaderPrograms[shaderProgram->id()] = shaderProgram;
}
//******************************************************************************
//Refresh Shaders (recompiles all shaders)**************************************
//******************************************************************************
void ShaderPrograms::refresh()
{
	cerr << endl;
	cerr << "*******************************************************************************" << endl;
	cerr << "* RECOMPILING SHADERS *********************************************************" << endl;
	cerr << "*******************************************************************************" << endl;
	cerr << endl;

	timer.start();

	map<GLuint, ShaderProgram *>::iterator itr;
	for(itr = shaderPrograms.begin(); itr != shaderPrograms.end(); itr++)
	{
		ShaderProgram *shaderProgram = itr->second;
		shaderProgram->refresh();
	}

	timer.stop();

	cerr << "Recompilation time (ms): " << timer.ms() << endl;
}
//******************************************************************************
//Removes a shaders (Usually when deleted)**************************************
//******************************************************************************
void ShaderPrograms::remove(GLuint shaderID )
{
	shaderPrograms.erase(shaderID);
}
//-----------------------------------------------------------------------------
void ShaderPrograms::remove(ShaderProgram *shaderProgram)
{
	shaderPrograms.erase(shaderProgram->id());
}
