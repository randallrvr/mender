//*****************************************************************************
//ShaderProgram.cpp************************************************************
//*****************************************************************************

//Header Include
#include "ShaderProgram.h"

//Project Includes
#include "ShaderPrograms.h"

//Standard Library Includes
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

//Namespaces
using namespace render;
using namespace std;


template <typename T, typename U>
class create_map
{
private:
	std::map<T, U> m_map;
public:
	create_map(const T& key, const U& val)
	{
		m_map[key] = val;
	}

	create_map<T, U>& operator()(const T& key, const U& val)
	{
		m_map[key] = val;
		return *this;
	}

	operator std::map<T, U>()
	{
		return m_map;
	}
};

map<GLenum, string> ShaderProgram::shaderStageNames = create_map<GLenum, string>(GL_VERTEX_SHADER,          "vertShader")
																				(GL_FRAGMENT_SHADER,        "fragShader")
																				(GL_GEOMETRY_SHADER,        "geomShader")
																				(GL_TESS_EVALUATION_SHADER, "evalShader")
																				(GL_TESS_CONTROL_SHADER,    "ctrlShader")
																				(GL_COMPUTE_SHADER,         "compShader");

map<GLenum, string> ShaderProgram::shaderUniformTypes = create_map<GLenum, string>
(GL_FLOAT,										"float"						)
(GL_FLOAT_VEC2,									"vec2"						)
(GL_FLOAT_VEC3,									"vec3"						)
(GL_FLOAT_VEC4,									"vec4"						)
(GL_DOUBLE,										"double"					)
(GL_DOUBLE_VEC2,								"dvec2"						)
(GL_DOUBLE_VEC3,								"dvec3"						)
(GL_DOUBLE_VEC4,								"dvec4"						)
(GL_INT,										"int"						)
(GL_INT_VEC2,									"ivec2"						)
(GL_INT_VEC3,									"ivec3"						)
(GL_INT_VEC4,									"ivec4"						)
(GL_UNSIGNED_INT,								"unsigned int"				)
(GL_UNSIGNED_INT_VEC2,							"uvec2"						)
(GL_UNSIGNED_INT_VEC3,							"uvec3"						)
(GL_UNSIGNED_INT_VEC4,							"uvec4"						)
(GL_BOOL,										"bool"						)
(GL_BOOL_VEC2,									"bvec2"						)
(GL_BOOL_VEC3,									"bvec3"						)
(GL_BOOL_VEC4,									"bvec4"						)
(GL_FLOAT_MAT2,									"mat2"						)
(GL_FLOAT_MAT3,									"mat3"						)
(GL_FLOAT_MAT4,									"mat4"						)
(GL_FLOAT_MAT2x3,								"mat2x3"					)
(GL_FLOAT_MAT2x4,								"mat2x4"					)
(GL_FLOAT_MAT3x2,								"mat3x2"					)
(GL_FLOAT_MAT3x4,								"mat3x4"					)
(GL_FLOAT_MAT4x2,								"mat4x2"					)
(GL_FLOAT_MAT4x3,								"mat4x3"					)
(GL_DOUBLE_MAT2,								"dmat2"						)
(GL_DOUBLE_MAT3,								"dmat3"						)
(GL_DOUBLE_MAT4,								"dmat4"						)
(GL_DOUBLE_MAT2x3,								"dmat2x3"					)
(GL_DOUBLE_MAT2x4,								"dmat2x4"					)
(GL_DOUBLE_MAT3x2,								"dmat3x2"					)
(GL_DOUBLE_MAT3x4,								"dmat3x4"					)
(GL_DOUBLE_MAT4x2,								"dmat4x2"					)
(GL_DOUBLE_MAT4x3,								"dmat4x3"					)
(GL_SAMPLER_1D,									"sampler1D"					)
(GL_SAMPLER_2D,									"sampler2D"					)
(GL_SAMPLER_3D,									"sampler3D"					)
(GL_SAMPLER_CUBE,								"samplerCube"				)
(GL_SAMPLER_1D_SHADOW,							"sampler1DShadow"			)
(GL_SAMPLER_2D_SHADOW,							"sampler2DShadow"			)
(GL_SAMPLER_1D_ARRAY,							"sampler1DArray"			)
(GL_SAMPLER_2D_ARRAY,							"sampler2DArray"			)
(GL_SAMPLER_CUBE_MAP_ARRAY,						"samplerCubeArray"			)
(GL_SAMPLER_1D_ARRAY_SHADOW,					"sampler1DArrayShadow"		)
(GL_SAMPLER_2D_ARRAY_SHADOW,					"sampler2DArrayShadow"		)
(GL_SAMPLER_2D_MULTISAMPLE,						"sampler2DMS"				)
(GL_SAMPLER_2D_MULTISAMPLE_ARRAY,				"sampler2DMSArray"			)
(GL_SAMPLER_CUBE_SHADOW,						"samplerCubeShadow"			)
(GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW,				"samplerCubeArrayShadow"	)
(GL_SAMPLER_BUFFER,								"samplerBuffer"				)
(GL_SAMPLER_2D_RECT,							"sampler2DRect"				)
(GL_SAMPLER_2D_RECT_SHADOW,						"sampler2DRectShadow"		)
(GL_INT_SAMPLER_1D,								"isampler1D"				)
(GL_INT_SAMPLER_2D,								"isampler2D"				)
(GL_INT_SAMPLER_3D,								"isampler3D"				)
(GL_INT_SAMPLER_CUBE,							"isamplerCube"				)
(GL_INT_SAMPLER_1D_ARRAY,						"isampler1DArray"			)
(GL_INT_SAMPLER_2D_ARRAY,						"isampler2DArray"			)
(GL_INT_SAMPLER_CUBE_MAP_ARRAY,					"isamplerCubeArray"			)
(GL_INT_SAMPLER_2D_MULTISAMPLE,					"isampler2DMS"				)
(GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,			"isampler2DMSArray"			)
(GL_INT_SAMPLER_BUFFER,							"isamplerBuffer"			)
(GL_INT_SAMPLER_2D_RECT,						"isampler2DRect"			)
(GL_UNSIGNED_INT_SAMPLER_1D,					"usampler1D"				)
(GL_UNSIGNED_INT_SAMPLER_2D,					"usampler2D"				)
(GL_UNSIGNED_INT_SAMPLER_3D,					"usampler3D"				)
(GL_UNSIGNED_INT_SAMPLER_CUBE,					"usamplerCube"				)
(GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,				"usampler1DArray"			)
(GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,				"usampler2DArray"			)
(GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY,		"usamplerCubeArray"			)
(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,		"usampler2DMS"				)
(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,	"usampler2DMSArray"			)
(GL_UNSIGNED_INT_SAMPLER_BUFFER,				"usamplerBuffer"			)
(GL_UNSIGNED_INT_SAMPLER_2D_RECT,				"usampler2DRect"			)
(GL_IMAGE_1D,									"image1D"					)
(GL_IMAGE_2D,									"image2D"					)
(GL_IMAGE_3D,									"image3D"					)
(GL_IMAGE_2D_RECT,								"image2DRect"				)
(GL_IMAGE_CUBE,									"imageCube"					)
(GL_IMAGE_BUFFER,								"imageBuffer"				)
(GL_IMAGE_1D_ARRAY,								"image1DArray"				)
(GL_IMAGE_2D_ARRAY,								"image2DArray"				)
(GL_IMAGE_CUBE_MAP_ARRAY,						"imageCubeArray"			)
(GL_IMAGE_2D_MULTISAMPLE,						"image2DMS"					)
(GL_IMAGE_2D_MULTISAMPLE_ARRAY,					"image2DMSArray"			)
(GL_INT_IMAGE_1D,								"iimage1D"					)
(GL_INT_IMAGE_2D,								"iimage2D"					)
(GL_INT_IMAGE_3D,								"iimage3D"					)
(GL_INT_IMAGE_2D_RECT,							"iimage2DRect"				)
(GL_INT_IMAGE_CUBE,								"iimageCube"				)
(GL_INT_IMAGE_BUFFER,							"iimageBuffer"				)
(GL_INT_IMAGE_1D_ARRAY,							"iimage1DArray"				)
(GL_INT_IMAGE_2D_ARRAY,							"iimage2DArray"				)
(GL_INT_IMAGE_CUBE_MAP_ARRAY,					"iimageCubeArray"			)
(GL_INT_IMAGE_2D_MULTISAMPLE,					"iimage2DMS"				)
(GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,				"iimage2DMSArray"			)
(GL_UNSIGNED_INT_IMAGE_1D,						"uimage1D"					)
(GL_UNSIGNED_INT_IMAGE_2D,						"uimage2D"					)
(GL_UNSIGNED_INT_IMAGE_3D,						"uimage3D"					)
(GL_UNSIGNED_INT_IMAGE_2D_RECT,					"uimage2DRect"				)
(GL_UNSIGNED_INT_IMAGE_CUBE,					"uimageCube"				)
(GL_UNSIGNED_INT_IMAGE_BUFFER,					"uimageBuffer"				)
(GL_UNSIGNED_INT_IMAGE_1D_ARRAY,				"uimage1DArray"				)
(GL_UNSIGNED_INT_IMAGE_2D_ARRAY,				"uimage2DArray"				)
(GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY,			"uimageCubeArray"			)
(GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,			"uimage2DMS"				)
(GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,	"uimage2DMSArray"			)
(GL_UNSIGNED_INT_ATOMIC_COUNTER,				"atomic_uint"				);


string getExtension(const string &filename)
{
	string extension = "";
	string::size_type index = filename.find_last_of(".");
	if(index != string::npos)
	{
		string extension = filename.substr(index);
		if((extension == ".vert") || (extension == ".frag") || (extension == ".eval") || (extension == ".ctrl") || (extension == ".geom") || (extension == ".comp"))
		{
			return extension;
		}
	}
	cerr << "Please use the appropriate Shader extension" << endl;
	cerr << "  .vert == VERTex shader" << endl;
	cerr << "  .geom == GEOMetry shader" << endl;
	cerr << "  .frag == FRAGment shader" << endl;
	cerr << "  .eval == Tesselation EVALuation shader" << endl;
	cerr << "  .ctrl == Tesselation ConTRoL shader" << endl;
	return extension;
}


//*****************************************************************************
//Constructors*****************************************************************
//*****************************************************************************
ShaderProgram::ShaderProgram()
{
	program_id = glCreateProgram();
	this->vert_shader = NULL;
	this->frag_shader = NULL;
	this->geom_shader = NULL;
	this->eval_shader = NULL;
	this->ctrl_shader = NULL;
	this->comp_shader = NULL;
}
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram(VertShader *vert_shader, FragShader *frag_shader)
{
	program_id = glCreateProgram();
	this->init(vert_shader, NULL, NULL, NULL, frag_shader);
}
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( VertShader *vert_shader, GeomShader *geom_shader, FragShader *frag_shader)
{
	program_id = glCreateProgram();
	this->init(vert_shader, NULL, NULL, geom_shader, frag_shader);
}
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( VertShader *vert_shader, CtrlShader *tess_ctrl_shader, EvalShader *tess_eval_shader, FragShader *frag_shader)
{
	program_id = glCreateProgram();
	this->init(vert_shader, tess_ctrl_shader, tess_eval_shader, NULL, frag_shader);
}
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( VertShader *vert_shader, CtrlShader *tess_ctrl_shader, EvalShader *tess_eval_shader, GeomShader *geom_shader, FragShader *frag_shader)
{
	program_id = glCreateProgram();
	this->init(vert_shader, tess_ctrl_shader, tess_eval_shader, geom_shader, frag_shader);
}
//-----------------------------------------------------------------------------
render::ShaderProgram::ShaderProgram( VertShader *vert_shader )
{
	program_id = glCreateProgram();
	this->init(vert_shader, NULL, NULL, NULL, NULL, NULL);
}
//-----------------------------------------------------------------------------
render::ShaderProgram::ShaderProgram( CompShader *comp_shader )
{
	program_id = glCreateProgram();
	this->init(NULL, NULL, NULL, NULL, NULL, comp_shader);
}
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( VertShader *vert_shader, GeomShader *geom_shader)
{
	this->init(vert_shader, NULL, NULL, geom_shader, NULL);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( const VertFile &vert_file, const FragFile &frag_file )
{
	program_id = glCreateProgram();
	this->init(new VertShader(vert_file), NULL, NULL, NULL, new FragShader(frag_file));
}
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( const VertFile &vert_file, const GeomFile &geom_file, const FragFile &frag_file )
{
	program_id = glCreateProgram();
	this->init(new VertShader(vert_file),  NULL, NULL, new GeomShader(geom_file), new FragShader(frag_file));
}
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( const VertFile &vert_file, const CtrlFile &ctrl_file, const EvalFile &eval_file, const FragFile &frag_file )
{
	program_id = glCreateProgram();
	this->init(new VertShader(vert_file), new CtrlShader(ctrl_file), new EvalShader(eval_file), NULL, new FragShader(frag_file));
}
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( const VertFile &vert_file, const CtrlFile &ctrl_file, const EvalFile &eval_file, const GeomFile &geom_file, const FragFile &frag_file )
{
	program_id = glCreateProgram();
	this->init(new VertShader(vert_file), new CtrlShader(ctrl_file), new EvalShader(eval_file), new GeomShader(geom_file), new FragShader(frag_file));
}
//-----------------------------------------------------------------------------
render::ShaderProgram::ShaderProgram( const VertFile &comp_file )
{
	program_id = glCreateProgram();
	this->init(new VertShader(comp_file), NULL, NULL, NULL, NULL, NULL);
}
//-----------------------------------------------------------------------------
render::ShaderProgram::ShaderProgram( const CompFile &comp_file )
{
	program_id = glCreateProgram();
	this->init(NULL, NULL, NULL, NULL, NULL, new CompShader(comp_file));
}
//-----------------------------------------------------------------------------
ShaderProgram::ShaderProgram( const VertFile &vert_file, const GeomFile &geom_file )
{
	program_id = glCreateProgram();
	this->init(new VertShader(vert_file), NULL, NULL, new GeomShader(geom_file), NULL);
}
//*****************************************************************************
//Load*************************************************************************
//*****************************************************************************
void ShaderProgram::load( const VertFile &vert_file, const FragFile &frag_file )
{
	this->init(new VertShader(vert_file), NULL, NULL, NULL, new FragShader(frag_file));
}
//-----------------------------------------------------------------------------
void ShaderProgram::load( const VertFile &vert_file, const GeomFile &geom_file, const FragFile &frag_file )
{
	this->init(new VertShader(vert_file), NULL, NULL, new GeomShader(geom_file), new FragShader(frag_file));
}
//-----------------------------------------------------------------------------
void ShaderProgram::load( const VertFile &vert_file, const CtrlFile &ctrl_file, const EvalFile &eval_file, const FragFile &frag_file )
{
	this->init(new VertShader(vert_file), new CtrlShader(ctrl_file), new EvalShader(eval_file), NULL, new FragShader(frag_file));
}
//-----------------------------------------------------------------------------
void ShaderProgram::load( const VertFile &vert_file, const CtrlFile &ctrl_file, const EvalFile &eval_file, const GeomFile &geom_file, const FragFile &frag_file )
{
	this->init(new VertShader(vert_file), new CtrlShader(ctrl_file), new EvalShader(eval_file), new GeomShader(geom_file), new FragShader(frag_file));
}
//-----------------------------------------------------------------------------
void ShaderProgram::load( const VertFile &comp_file )
{
	this->init(new VertShader(comp_file), NULL, NULL, NULL, NULL, NULL);
}
//-----------------------------------------------------------------------------
void ShaderProgram::load( const CompFile &comp_file )
{
	this->init(NULL, NULL, NULL, NULL, NULL, new CompShader(comp_file));
}
//-----------------------------------------------------------------------------
void ShaderProgram::load( const VertFile &vert_file, const GeomFile &geom_file )
{
	GeomShader *geomShader = new GeomShader(geom_file);
	this->init(new VertShader(vert_file), NULL, NULL, geomShader, NULL);
}
//*****************************************************************************
//Load*************************************************************************
//*****************************************************************************
void ShaderProgram::load(VertShader *vertShader, FragShader *fragShader )
{
	this->init(vertShader, NULL, NULL, NULL, fragShader);
}
//-----------------------------------------------------------------------------
void ShaderProgram::load(VertShader *vertShader, GeomShader *geomShader, FragShader *fragShader )
{
	this->init(vertShader, NULL, NULL, geomShader, fragShader);
}
//-----------------------------------------------------------------------------
void ShaderProgram::load(VertShader *vertShader, CtrlShader *ctrlShader, EvalShader *evalShader, FragShader *fragShader )
{
	this->init(vertShader, ctrlShader, evalShader, NULL, fragShader);
}
//-----------------------------------------------------------------------------
void ShaderProgram::load(VertShader *vertShader, CtrlShader *ctrlShader, EvalShader *evalShader, GeomShader *geomShader, FragShader *fragShader )
{
	this->init(vertShader, ctrlShader, evalShader, geomShader, fragShader);
}
//-----------------------------------------------------------------------------
void ShaderProgram::load(VertShader *vertShader)
{
	this->init(vertShader, NULL, NULL, NULL, NULL, NULL);
}
//-----------------------------------------------------------------------------
void ShaderProgram::load(CompShader *compShader)
{
	this->init(NULL, NULL, NULL, NULL, NULL, compShader);
}
//-----------------------------------------------------------------------------
void ShaderProgram::load(VertShader *vertShader, GeomShader *geomShader)
{
	this->init(vertShader, NULL, NULL, geomShader, NULL);
}
//*****************************************************************************
//Load*************************************************************************
//*****************************************************************************
void render::ShaderProgram::load(const ShaderFile &shaderFile)
{
	string::size_type index = shaderFile.filename.find_last_of(".");
	if(index != string::npos)
	{
		string extension = shaderFile.filename.substr(index);

		if     (extension == ".vert")
		{
			VertFile vertFile(shaderFile.filename);
			vertFile.includes = shaderFile.includes;
			this->init(new VertShader(vertFile), NULL, NULL, NULL, NULL);
			return;
		}
		else if(extension == ".frag")
		{
			cerr << "Can't have a fragment shader by itself" << endl;
			return;
		}
		else if(extension == ".eval")
		{
			cerr << "Can't have a tessellation evaluation shader by itself" << endl;
			return;
		}
		else if(extension == ".ctrl")
		{
			cerr << "Can't have a tessellation control shader by itself" << endl;
			return;
		}
		else if(extension == ".geom")
		{
			cerr << "Can't have a geometry shader by itself" << endl;
			return;
		}
		else if(extension == ".comp")
		{
			CompFile compFile(shaderFile.filename);
			compFile.includes = shaderFile.includes;
			this->init(NULL, NULL, NULL, NULL, NULL, new CompShader(compFile));
			return;
		}
	}


}
//*****************************************************************************
//Initialize*******************************************************************
//*****************************************************************************
void ShaderProgram::init( VertShader *vert_shader, CtrlShader *ctrl_shader, EvalShader *eval_shader, GeomShader *geom_shader, FragShader *frag_shader, CompShader *comp_shader )
{
	this->vert_shader = vert_shader;
	this->ctrl_shader = ctrl_shader;
	this->eval_shader = eval_shader;
	this->geom_shader = geom_shader;
	this->frag_shader = frag_shader;
	this->comp_shader = comp_shader;

	if(vert_shader)		glAttachShader(program_id, vert_shader->id());
	if(ctrl_shader)		glAttachShader(program_id, ctrl_shader->id());
	if(eval_shader)		glAttachShader(program_id, eval_shader->id());
	if(geom_shader)		glAttachShader(program_id, geom_shader->id());
	if(frag_shader)		glAttachShader(program_id, frag_shader->id());
	if(comp_shader)		glAttachShader(program_id, comp_shader->id());

	bool linked = link();

	if(linked)
	{
		mapSubroutineUniforms();
		mapSubroutines();
		mapAttributes();
		mapUniforms();
		mapBlocks();
	}

	ShaderPrograms::add(this);
}
//*****************************************************************************
//Validate*********************************************************************
//*****************************************************************************
void ShaderProgram::validateState()
{
	glValidateProgram(program_id);

	GLint valid;
	glGetProgramiv(program_id, GL_VALIDATE_STATUS, &valid);

	if(valid != 1)
	{
		cerr << "ERROR: The shader program with shader(s): " << endl;
		if(vert_shader)		cerr << "\t" << vert_shader->file << endl;
		if(ctrl_shader)		cerr << "\t" << ctrl_shader->file << endl;
		if(eval_shader)		cerr << "\t" << eval_shader->file << endl;
		if(geom_shader)		cerr << "\t" << geom_shader->file << endl;
		if(comp_shader)		cerr << "\t" << comp_shader->file << endl;
		if(frag_shader)		cerr << "\t" << frag_shader->file << endl;
		cerr << "could not be validated" << endl;
		log();
	}
}
//*****************************************************************************
//Destructor*******************************************************************
//*****************************************************************************
ShaderProgram::~ShaderProgram()
{
	this->clearShaders();

	//Delete this ShaderProgram
	glDeleteProgram(program_id);

	ShaderPrograms::remove(this);
}
//-----------------------------------------------------------------------------
void ShaderProgram::clearShaders()
{
	if(vert_shader)		{ glDetachShader(program_id, vert_shader->id()); delete vert_shader; }
	if(ctrl_shader)		{ glDetachShader(program_id, ctrl_shader->id()); delete ctrl_shader; }
	if(eval_shader)		{ glDetachShader(program_id, eval_shader->id()); delete eval_shader; }
	if(geom_shader)		{ glDetachShader(program_id, geom_shader->id()); delete geom_shader; }
	if(frag_shader)		{ glDetachShader(program_id, frag_shader->id()); delete frag_shader; }
	if(comp_shader)		{ glDetachShader(program_id, comp_shader->id()); delete comp_shader; }
}
//*****************************************************************************
//Link*************************************************************************
//*****************************************************************************
bool ShaderProgram::link()
{
	glLinkProgram(program_id);

	//Check to see if it linked
	GLint linked;
	glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		cerr << "ERROR: The shader program with shader(s): " << endl;
		if(vert_shader)		cerr << "\t" << vert_shader->file << endl;
		if(ctrl_shader)		cerr << "\t" << ctrl_shader->file << endl;
		if(eval_shader)		cerr << "\t" << eval_shader->file << endl;
		if(geom_shader)		cerr << "\t" << geom_shader->file << endl;
		if(frag_shader)		cerr << "\t" << frag_shader->file << endl;
		if(comp_shader)		cerr << "\t" << comp_shader->file << endl;
		cerr << "could not be linked" << endl;
		this->log();
		return false;
	}

	return true;
}
//*****************************************************************************
//Log**************************************************************************
//*****************************************************************************
void ShaderProgram::log()
{
	GLint blen;
	GLsizei size;
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH , &blen);
	if(blen > 1)
	{
		char *log = new char[blen];
		if(log == NULL)
		{
			cerr << "Could not allocate compiler log buffer" << endl;
		}
		glGetProgramInfoLog(program_id, blen, &size, log);

		cerr << log << endl;
		delete [] log;
	}
}
//*****************************************************************************
//Begin/End********************************************************************
//*****************************************************************************
void ShaderProgram::begin()
{
//	this->validateState();
	glUseProgram(program_id);
}
//-----------------------------------------------------------------------------
void ShaderProgram::end()
{
	glUseProgram(0);
}
//*****************************************************************************
//refresh the shaders (reloads files for interactive editing)******************
//*****************************************************************************
void ShaderProgram::refresh()
{
	if(vert_shader)		glDetachShader(program_id, vert_shader->id());
	if(ctrl_shader)		glDetachShader(program_id, ctrl_shader->id());
	if(eval_shader)		glDetachShader(program_id, eval_shader->id());
	if(geom_shader)		glDetachShader(program_id, geom_shader->id());
	if(frag_shader)		glDetachShader(program_id, frag_shader->id());
	if(comp_shader)		glDetachShader(program_id, comp_shader->id());

	if(vert_shader)		vert_shader->refresh();
	if(ctrl_shader)		ctrl_shader->refresh();
	if(eval_shader)		eval_shader->refresh();
	if(geom_shader)		geom_shader->refresh();
	if(frag_shader)		frag_shader->refresh();
	if(comp_shader)		comp_shader->refresh();

	if(vert_shader)		glAttachShader(program_id, vert_shader->id());
	if(ctrl_shader)		glAttachShader(program_id, ctrl_shader->id());
	if(eval_shader)		glAttachShader(program_id, eval_shader->id());
	if(geom_shader)		glAttachShader(program_id, geom_shader->id());
	if(frag_shader)		glAttachShader(program_id, frag_shader->id());
	if(comp_shader)		glAttachShader(program_id, comp_shader->id());

	bool linked = link();

	if(linked)
	{
		mapSubroutineUniforms();
		mapSubroutines();
		mapAttributes();
		mapUniforms();
		mapBlocks();
	}
}
//-----------------------------------------------------------------------------
void render::ShaderProgram::refreshSource()
{
	if(vert_shader)		glDetachShader(program_id, vert_shader->id());
	if(ctrl_shader)		glDetachShader(program_id, ctrl_shader->id());
	if(eval_shader)		glDetachShader(program_id, eval_shader->id());
	if(geom_shader)		glDetachShader(program_id, geom_shader->id());
	if(frag_shader)		glDetachShader(program_id, frag_shader->id());
	if(comp_shader)		glDetachShader(program_id, comp_shader->id());

	if(vert_shader)		vert_shader->refreshSource();
	if(ctrl_shader)		ctrl_shader->refreshSource();
	if(eval_shader)		eval_shader->refreshSource();
	if(geom_shader)		geom_shader->refreshSource();
	if(frag_shader)		frag_shader->refreshSource();
	if(comp_shader)		comp_shader->refreshSource();

	if(vert_shader)		glAttachShader(program_id, vert_shader->id());
	if(ctrl_shader)		glAttachShader(program_id, ctrl_shader->id());
	if(eval_shader)		glAttachShader(program_id, eval_shader->id());
	if(geom_shader)		glAttachShader(program_id, geom_shader->id());
	if(frag_shader)		glAttachShader(program_id, frag_shader->id());
	if(comp_shader)		glAttachShader(program_id, comp_shader->id());

	bool linked = link();

	if(linked)
	{
		mapSubroutineUniforms();
		mapSubroutines();
		mapAttributes();
		mapUniforms();
		mapBlocks();
	}
}
//*****************************************************************************
//ID***************************************************************************
//*****************************************************************************
unsigned int ShaderProgram::id()
{
	return(program_id);
}
//*****************************************************************************
//Bind FragData, Attributes, and Blocks****************************************
//*****************************************************************************
void ShaderProgram::bindFragData(const char *name, GLuint colorNumber)
{
	glBindFragDataLocation(program_id, colorNumber, name);
}
//-----------------------------------------------------------------------------
void ShaderProgram::bindFragData(const string &name, GLuint colorNumber)
{
	glBindFragDataLocation(program_id, colorNumber, name.c_str());
}
//-----------------------------------------------------------------------------
void ShaderProgram::bindAttribute(const char *name, GLuint index)
{
	glBindAttribLocation(program_id, index, name);
}
//-----------------------------------------------------------------------------
void ShaderProgram::bindAttribute(const string &name, GLuint index)
{
	glBindAttribLocation(program_id, index, name.c_str());
}
//-----------------------------------------------------------------------------
void ShaderProgram::bindBlock(const char *name, GLuint index)
{
	glUniformBlockBinding(program_id, locateBlock(name), index);
}
//-----------------------------------------------------------------------------
void ShaderProgram::bindBlock(const string &name, GLuint index)
{
	glUniformBlockBinding(program_id, locateBlock(name), index);
}
//*****************************************************************************
//Set Tranform Feedback Outputs************************************************
//*****************************************************************************
void ShaderProgram::setFeedbackOut( const string &outputName )
{
//	const char *outputNames[] = { outputName.c_str() };
	char **outputNames = new char *[1];
	outputNames[0] = (char *)outputName.c_str();
	glTransformFeedbackVaryings(program_id, 1, (const GLchar **)outputNames, GL_SEPARATE_ATTRIBS);
	delete [] outputNames;
}
//*****************************************************************************
//Get Uniform Subroutine Location**********************************************
//*****************************************************************************
//GLint ShaderProgram::locateSubroutine(const string &name)
//{
//	GLint loc = glGetSubroutineUniformLocation(program_id, name.c_str());
//
//	if(loc < 0)
//	{
//		cerr << "Uniform variable \"" << name << "\" not found" << endl;
//	}
//
//	return(loc);
//}
////-----------------------------------------------------------------------------
//GLint ShaderProgram::locateUniform(const char *name)
//{
//	GLint loc = glGetUniformLocation(program_id, name);
//
//	if(loc < 0)
//	{
//		cerr << "Uniform variable \"" << name << "\" not found" << endl;
//	}
//
//	return(loc);
//}
//*****************************************************************************
//Get Uniform Variable Location************************************************
//*****************************************************************************
GLint ShaderProgram::locateUniform(const string &name)
{
	GLint loc = glGetUniformLocation(program_id, name.c_str());

	if(loc < 0)
	{
		cerr << "Uniform variable \"" << name << "\" not found" << endl;
	}

	return(loc);
}
//-----------------------------------------------------------------------------
GLint ShaderProgram::locateUniform(const char *name)
{
	GLint loc = glGetUniformLocation(program_id, name);

	if(loc < 0)
	{
		cerr << "Uniform variable \"" << name << "\" not found" << endl;
	}

	return(loc);
}
//-----------------------------------------------------------------------------
//Get Attribute Variable Location----------------------------------------------
//-----------------------------------------------------------------------------
GLint ShaderProgram::locateAttribute(const string &name)
{
	GLint loc = glGetAttribLocation(program_id, name.c_str());

	if(loc < 0)
	{
		cerr << "Attribute \"" << name << "\" not found" << endl;
	}

	return(loc);
}
//-----------------------------------------------------------------------------
GLint ShaderProgram::locateAttribute(const char *name)
{
	GLint loc = glGetAttribLocation(program_id, name);

	if(loc < 0)
	{
		cerr << "Attribute \"" << name << "\" not found" << endl;
	}

	return(loc);
}
//-----------------------------------------------------------------------------
//Get Uniform Block Index------------------------------------------------------
//-----------------------------------------------------------------------------
GLuint ShaderProgram::locateBlock(const string &name)
{
	GLuint index = glGetUniformBlockIndex(program_id, name.c_str());

	if(index == GL_INVALID_INDEX)
	{
		cerr << "Uniform block \"" << name << "\" not found" << endl;
	}

	return(index);
}
//-----------------------------------------------------------------------------
GLuint ShaderProgram::locateBlock(const char *name)
{
	GLuint index = glGetUniformBlockIndex(program_id, name);

	if(index == GL_INVALID_INDEX)
	{
		cerr << "Uniform block \"" << name << "\" not found" << endl;
	}

	return(index);
}
//*****************************************************************************
//Receive Uniform Variables****************************************************
//*****************************************************************************
void ShaderProgram::getUniformfv(const string &varname, float *values)
{
	glGetUniformfv(program_id, locateUniform(varname), values);
}
//----------------------------------------------------------------------------- 
void ShaderProgram::getUniformiv(const string &varname, int *values)
{
	glGetUniformiv(program_id, locateUniform(varname), (GLint *)(values));
}
//-----------------------------------------------------------------------------
void ShaderProgram::getUniformuiv(const string &varname, unsigned int *values)
{
	glGetUniformuiv(program_id, locateUniform(varname), (GLuint *)(values));
}
//*****************************************************************************
//Create Subroutine/Attribute/Uniform/Blocks maps******************************
//*****************************************************************************
void ShaderProgram::mapSubroutineUniforms()
{
	mapStageSubroutineUniforms(GL_VERTEX_SHADER,          vertSubroutineUniformMap);
	mapStageSubroutineUniforms(GL_TESS_CONTROL_SHADER,    ctrlSubroutineUniformMap);
	mapStageSubroutineUniforms(GL_TESS_EVALUATION_SHADER, evalSubroutineUniformMap);
	mapStageSubroutineUniforms(GL_GEOMETRY_SHADER,        geomSubroutineUniformMap);
	mapStageSubroutineUniforms(GL_FRAGMENT_SHADER,        fragSubroutineUniformMap);
	mapStageSubroutineUniforms(GL_COMPUTE_SHADER,         compSubroutineUniformMap);
}
//-----------------------------------------------------------------------------
void ShaderProgram::mapStageSubroutineUniforms( GLenum shaderType, map<string, GLint> &subroutineUniformMap)
{
	GLint maxSubroutineUniformLength, numSubroutineUniforms, numSubroutineUniformLocations;
	GLsizei subroutineUniformSize;

	glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORMS,           &numSubroutineUniforms        );
	glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, &maxSubroutineUniformLength   );
	glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS,  &numSubroutineUniformLocations);

	GLchar *subroutineUniformName = new GLchar[maxSubroutineUniformLength];

	for(GLint i = 0; i < numSubroutineUniforms; i++)
	{
		glGetActiveSubroutineUniformName(program_id, shaderType, i, maxSubroutineUniformLength, &subroutineUniformSize, subroutineUniformName);

		subroutineUniformMap[string(subroutineUniformName)] = i;
	}

	delete [] subroutineUniformName;
}
//-----------------------------------------------------------------------------
void ShaderProgram::mapSubroutines()
{
	mapStageSubroutines(GL_VERTEX_SHADER,          vertSubroutineMap);
	mapStageSubroutines(GL_TESS_CONTROL_SHADER,    ctrlSubroutineMap);
	mapStageSubroutines(GL_TESS_EVALUATION_SHADER, evalSubroutineMap);
	mapStageSubroutines(GL_GEOMETRY_SHADER,        geomSubroutineMap);
	mapStageSubroutines(GL_FRAGMENT_SHADER,        fragSubroutineMap);
	mapStageSubroutines(GL_COMPUTE_SHADER,         compSubroutineMap);
}
//-----------------------------------------------------------------------------
void render::ShaderProgram::mapStageSubroutines( GLenum shaderType, map<string, GLint> &subroutineMap)
{
	GLint maxSubroutineLength, numSubroutines;
	GLuint subroutineIndex;
	GLsizei subroutineSize;

	glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINES,           &numSubroutines     );
	glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_MAX_LENGTH, &maxSubroutineLength);

	GLchar *subroutineName = new GLchar[maxSubroutineLength];

	for( int i = 0; i < numSubroutines; i++ ) 
	{
		glGetActiveSubroutineName( program_id, shaderType, i, maxSubroutineLength, &subroutineSize, subroutineName );

		subroutineIndex = glGetSubroutineIndex(program_id, shaderType, subroutineName);

		subroutineMap[string(subroutineName)] = subroutineIndex;
	}

	delete [] subroutineName;
}
//-----------------------------------------------------------------------------
void ShaderProgram::mapAttributes()
{
	GLint written, size, location, maxLength, numAttribs;
	GLenum type;

	glGetProgramiv(program_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength );
	glGetProgramiv(program_id, GL_ACTIVE_ATTRIBUTES,           &numAttribs);

	GLchar *name = new GLchar[maxLength];
	for( int i = 0; i < numAttribs; i++ ) 
	{
		glGetActiveAttrib( program_id, i, maxLength, &written, &size, &type, name );
		location = glGetAttribLocation(program_id, name);
		if(location >= 0)
		{
			attributeMap[string(name)] = location;
		}
	}
	delete [] name;
}
//-----------------------------------------------------------------------------
void ShaderProgram::mapUniforms()
{
	GLint numUniforms, size, location, maxLength;
	GLsizei written;
	GLenum type;

	glGetProgramiv( program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength  );
	glGetProgramiv( program_id, GL_ACTIVE_UNIFORMS,           &numUniforms);

	GLchar *name = new GLchar[maxLength];
	for( int uniformIndex = 0; uniformIndex < numUniforms; ++uniformIndex )
	{
		glGetActiveUniform( program_id, uniformIndex, maxLength, &written, &size, &type, name );
		location = glGetUniformLocation(program_id, name);
		if(location >= 0)
		{
			uniformLocationMap[string(name)] = location;
		}
	}
	delete [] name;

	for(int i = 0; i < 6; i++)
	{
		Shader *shader = shaders[i];
		if(shader)
		{
			for(auto itr = shader->uniformMap.begin(); itr != shader->uniformMap.end(); itr++)
			{
				Shader::Uniform uniform = itr->second;
		
				if(uniformLocationMap.find(uniform.name) == uniformLocationMap.end())	//if parsed uniform not found amongst active uniforms
				{
					uniformLocationMap[uniform.name] = -1;	//There! Now I finally have a way to check for uniform that exists, but were removed by the compiler
				}
			}
		//	for(auto itr = shader->uniformSet.begin(); itr != shader->uniformSet.end(); itr++)
		//	{
		//		string uniformName = *itr;
		//
		//		if(uniformLocationMap.find(uniformName) == uniformLocationMap.end())	//if parsed uniform not found amongst active uniforms
		//		{
		//			uniformLocationMap[uniformName] = -1;	//There! Now I finally have a way to check for uniform that exists, but were removed by the compiler
		//		}
		//
		//	}
		}
	}
}
//-----------------------------------------------------------------------------
void ShaderProgram::mapAtomics()
{
	GLint maxLength, numBuffers;

	glGetProgramiv(program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH,     &maxLength );
	glGetProgramiv(program_id, GL_ACTIVE_ATOMIC_COUNTER_BUFFERS, &numBuffers);

	GLchar *name = new GLchar[maxLength];

	for( int atomicBufferIndex = 0; atomicBufferIndex < numBuffers; atomicBufferIndex++ ) 
	{
		GLint binding;
		GLint dataSize;
		GLint activeCounters;
		GLint activeCountersIndices;
		
		glGetActiveAtomicCounterBufferiv( program_id, atomicBufferIndex, GL_ATOMIC_COUNTER_BUFFER_BINDING,                       &binding               );
		glGetActiveAtomicCounterBufferiv( program_id, atomicBufferIndex, GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE,                     &dataSize              );
		glGetActiveAtomicCounterBufferiv( program_id, atomicBufferIndex, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS,        &activeCounters        );
		glGetActiveAtomicCounterBufferiv( program_id, atomicBufferIndex, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES, &activeCountersIndices );

		GLint vert, ctrl, eval, frag, geom;

		glGetActiveAtomicCounterBufferiv( program_id, atomicBufferIndex, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER,          &vert );
		glGetActiveAtomicCounterBufferiv( program_id, atomicBufferIndex, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER,    &ctrl );
		glGetActiveAtomicCounterBufferiv( program_id, atomicBufferIndex, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER, &eval );
		glGetActiveAtomicCounterBufferiv( program_id, atomicBufferIndex, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER,        &geom );
		glGetActiveAtomicCounterBufferiv( program_id, atomicBufferIndex, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER,        &frag );

//		GLuint index = glGetUniformBlockIndex(program_id, blockName);

//		if(index != GL_INVALID_INDEX)
//		{
//			blockMap[string(blockName)] = index;
//
//			//Set default block binding to location
//			glUniformBlockBinding(program_id, index, index);
//		}
	}

	delete [] name;
}
//-----------------------------------------------------------------------------
void ShaderProgram::mapBlocks()
{
	GLint written, maxBlockLength, numBlocks;

	glGetProgramiv(program_id, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &maxBlockLength);
	glGetProgramiv(program_id, GL_ACTIVE_UNIFORM_BLOCKS,                &numBlocks     );

	if(maxBlockLength <= 0 || numBlocks <= 0)
		return;

	GLchar *blockName = new GLchar[maxBlockLength];

	for( int blockIndex = 0; blockIndex < numBlocks; blockIndex++ ) 
	{
		glGetActiveUniformBlockName( program_id, blockIndex, maxBlockLength, &written, blockName );
		GLuint index = glGetUniformBlockIndex(program_id, blockName);

		if(index != GL_INVALID_INDEX)
		{
			blockMap[string(blockName)] = index;

			//Set default block binding to location
			glUniformBlockBinding(program_id, index, index);
		}
	}

	delete [] blockName;
}
//*****************************************************************************
//set #define (across all shader stages)***************************************
//*****************************************************************************
void ShaderProgram::setDefine( const string &var, const string &val )
{
	vertDefine(var, val);
	fragDefine(var, val);
	geomDefine(var, val);
	evalDefine(var, val);
	ctrlDefine(var, val);
	compDefine(var, val);

	this->refreshSource();
}
//*****************************************************************************
//Print/debug output***********************************************************
//*****************************************************************************
void ShaderProgram::printAll()
{
	cerr << "The shader program has the following shader(s): " << endl;
	if(vert_shader)		cerr << "\t" << vert_shader->file << endl;
	if(frag_shader)		cerr << "\t" << frag_shader->file << endl;
	if(geom_shader)		cerr << "\t" << geom_shader->file << endl;
	if(eval_shader)		cerr << "\t" << eval_shader->file << endl;
	if(ctrl_shader)		cerr << "\t" << ctrl_shader->file << endl;
	if(comp_shader)		cerr << "\t" << comp_shader->file << endl;
	printUniforms();
	printAttributes();
	printSubroutines();
	printSubroutineUniforms();
}
//-----------------------------------------------------------------------------
void ShaderProgram::printSubroutines()
{
	cerr << endl << "Subroutines (compatible SubroutineUniforms not listed)" << endl;

	GLint maxSubroutineLength, maxSubroutineUniformLength, numSubroutines, numSubroutineUniforms, numSubroutineUniformLocations;
	GLuint subroutineIndex;
	GLsizei subroutineSize;

	printf(" Program #: %d\n", program_id);
	printf(" Shader         | Index | Name\n");
	printf("------------------------------------------------\n");

	map<GLenum, string>::iterator itr;

	for(itr = shaderStageNames.begin(); itr != shaderStageNames.end(); itr++) 
	{
		GLenum shaderType = itr->first;
		string shaderName = itr->second;

		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINES,                   &numSubroutines               );
		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_MAX_LENGTH,         &maxSubroutineLength          );
		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORMS,           &numSubroutineUniforms        );
		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, &maxSubroutineUniformLength   );
		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS,  &numSubroutineUniformLocations);

		if(numSubroutines > 0)
		{
			GLchar *subroutineName = new GLchar[maxSubroutineLength];

			for( int i = 0; i < numSubroutines; i++ ) 
			{
				glGetActiveSubroutineName( program_id, shaderType, i, maxSubroutineLength, &subroutineSize, subroutineName );
		
				subroutineIndex = glGetSubroutineIndex(program_id, shaderType, subroutineName);
				printf(" %-14s | %5d | %s\n", shaderName.c_str(), subroutineIndex, subroutineName);
			}

			delete [] subroutineName;
		}
	}
	printf("\n");
}
//-----------------------------------------------------------------------------
void ShaderProgram::printSubroutineUniforms()
{
	cerr << endl << "Subroutine Uniforms (plus compatible Subroutines)" << endl;
	GLint maxSubroutineLength, maxSubroutineUniformLength, numSubroutines, numSubroutineUniforms, numSubroutineUniformLocations;
	GLsizei subroutineUniformSize, subroutineSize;


	printf(" Program #: %d\n", program_id);
	printf(" Shader         | subroutineUniformIndex | subroutineUniformName\n");
	printf(" Shader         |       |- subroutineIndex | subroutineName\n", (char)192);
	printf("------------------------------------------------\n");

	map<GLenum, string>::iterator itr;

	for(itr = shaderStageNames.begin(); itr != shaderStageNames.end(); itr++)
	{
		GLenum shaderType = itr->first;
		string shaderName = itr->second;

		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_MAX_LENGTH,         &maxSubroutineLength          );
		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINES,                   &numSubroutines               );
		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORMS,           &numSubroutineUniforms        );
		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, &maxSubroutineUniformLength   );
		glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS,  &numSubroutineUniformLocations);

		GLchar *subroutineName        = new GLchar[maxSubroutineLength];
		GLchar *subroutineUniformName = new GLchar[maxSubroutineUniformLength];

		for(GLint i = 0; i < numSubroutineUniforms; i++)
		{
			glGetActiveSubroutineUniformName(program_id, shaderType, i, maxSubroutineUniformLength, &subroutineUniformSize, subroutineUniformName);

			printf(" %-10s | %22d | %s\n", shaderName.c_str(), i, subroutineUniformName);

			GLint numCompatibleSubroutines;
			glGetActiveSubroutineUniformiv(program_id, shaderType, i, GL_NUM_COMPATIBLE_SUBROUTINES, &numCompatibleSubroutines);

			GLint *compatibleSubroutines= new GLint[numCompatibleSubroutines];
			glGetActiveSubroutineUniformiv(program_id, shaderType, i, GL_COMPATIBLE_SUBROUTINES,      compatibleSubroutines);

			for(int j = 0; j < numCompatibleSubroutines; j++)
			{
				GLuint subroutineIndex = compatibleSubroutines[j];

				glGetActiveSubroutineName( program_id, shaderType, subroutineIndex, maxSubroutineLength, &subroutineSize, subroutineName );

				printf(" %-10s | %24d | %s\n", shaderName.c_str(),  subroutineIndex, subroutineName);
			}
			delete [] compatibleSubroutines;
		}

		delete [] subroutineName;
		delete [] subroutineUniformName;
	}
	printf("\n");
}
//-----------------------------------------------------------------------------
void ShaderProgram::printAttributes()
{
	cout << endl << "Attributes" << endl;

	GLint written, size, location, maxLength, numAttribs;
	GLenum type;

	glGetProgramiv(program_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength );
	glGetProgramiv(program_id, GL_ACTIVE_ATTRIBUTES,           &numAttribs);

	GLchar *name = new GLchar[maxLength];

	GLint maxTypeLength = 4;
	for( int i = 0; i < numAttribs; i++ ) 
	{
		glGetActiveAttrib( program_id, i, maxLength, &written, &size, &type, name );
		location = glGetAttribLocation(program_id, name);
		string attribType = shaderUniformTypes[type];
		maxTypeLength = ((GLint)attribType.size() > maxTypeLength) ? (GLint)attribType.size() : (GLint)maxTypeLength;
	}

	cout << " Program #: " <<  program_id << endl;
	cout << " Location | " << setw(maxTypeLength) << "Type" << " | " << setw(maxLength-1) << "Name" << " | Size" << endl;
	cout << "------------------------------------------------" << endl;

	for( int i = 0; i < numAttribs; i++ )
	{
		glGetActiveAttrib( program_id, i, maxLength, &written, &size, &type, name );
		location = glGetAttribLocation(program_id, name);
		string attribType = shaderUniformTypes[type];
		maxTypeLength = ((int)attribType.size() > maxTypeLength) ? (int)attribType.size() : maxTypeLength;
		cout << setw(9) << location << " | " << setw(maxTypeLength) << attribType << " | " << setw(maxLength-1) << name << " | " << setw(4) << size << endl;
	}

	delete [] name;

	cout << endl;
}
//-----------------------------------------------------------------------------
void ShaderProgram::printUniforms()
{
	cout << endl << "Uniforms" << endl;
	
	GLint numUniforms, size, location, maxLength;
	GLsizei written;
	GLenum type;

	glGetProgramiv( program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength   );
	glGetProgramiv( program_id, GL_ACTIVE_UNIFORMS,           &numUniforms );

	GLchar *name = new GLchar[maxLength];

	GLint maxTypeLength = 4;
	for( int uniformIndex = 0; uniformIndex < numUniforms; ++uniformIndex )
	{	
		glGetActiveUniform( program_id, uniformIndex, maxLength, &written, &size, &type, name );
		location = glGetUniformLocation(program_id, name);
		string uniformType = shaderUniformTypes[type];
		maxTypeLength = ((GLint)uniformType.size() > maxTypeLength) ? (GLint)uniformType.size() : maxTypeLength;
	}

	cout << " Program #: " <<  program_id << endl;
	cout << " Location | " << setw(maxTypeLength) << "Type" << " | " << setw(maxLength-1) << "Name" << " | Size" << endl;
	cout << "------------------------------------------------" << endl;

	for( int uniformIndex = 0; uniformIndex < numUniforms; ++uniformIndex )
	{	
		glGetActiveUniform( program_id, uniformIndex, maxLength, &written, &size, &type, name );
		location = glGetUniformLocation(program_id, name);
		string uniformType = shaderUniformTypes[type];
		maxTypeLength = ((GLint)uniformType.size() > maxTypeLength) ? (GLint)uniformType.size() : maxTypeLength;
		cout << setw(9) << location << " | " << setw(maxTypeLength) << uniformType << " | " << setw(maxLength-1) << name << " | " << setw(4) << size << endl;
	}

	delete [] name;

	cout << endl;
}
//-----------------------------------------------------------------------------
void ShaderProgram::printBlocks()
{
	cout << endl << "Blocks" << endl;
	GLint written, size, location, maxBlockLength, maxUniformLength, numBlocks, numBlockUniforms;
	GLenum type;

	glGetProgramiv(program_id, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &maxBlockLength  );
	glGetProgramiv(program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH,            &maxUniformLength);
	glGetProgramiv(program_id, GL_ACTIVE_UNIFORM_BLOCKS,                &numBlocks       );

	GLchar *  blockName = new GLchar[maxBlockLength  ];
	GLchar *uniformName = new GLchar[maxUniformLength];

	cout << " Program #: " <<  program_id << endl;
	printf(" Index | Name\n");
	printf("------------------------------------------------\n");
	for( int blockIndex = 0; blockIndex < numBlocks; blockIndex++ ) 
	{
		glGetActiveUniformBlockName( program_id, blockIndex, maxBlockLength, &written, blockName );
		location = glGetUniformBlockIndex (program_id, blockName);
		printf(" %-5d | %s\n", location, blockName);

		glGetActiveUniformBlockiv(program_id, blockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numBlockUniforms);

		int *blockActiveUniforms = new int[numBlockUniforms];
		glGetActiveUniformBlockiv(program_id, blockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES , blockActiveUniforms);

		for( int blockUniformIndex = 0; blockUniformIndex < numBlockUniforms; blockUniformIndex++ ) 
		{
			int uniformIndex = blockActiveUniforms[blockUniformIndex];

			glGetActiveUniform( program_id, uniformIndex, maxUniformLength, &written, &size, &type, uniformName );
			location = glGetUniformLocation(program_id, uniformName);

			printf(" %-8d | %s\n", location, uniformName);

			//	string blockUniformNameStr = string(blockName) + "." + string(uniformName);
			//	location = glGetUniformLocation(program_id, (GLchar *)blockUniformNameStr.c_str());
			//	printf(" %-8d | %s\n", location, blockUniformNameStr.c_str());
		}

		delete [] blockActiveUniforms;
	}

	delete [] blockName;
	delete [] uniformName;
	printf("\n");
}
//*****************************************************************************
//Set Subroutines**************************************************************
//*****************************************************************************
void ShaderProgram::vertSubroutine(const string &subroutine)
{
	GLuint index = vertSubroutineMap[subroutine];
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &index);
}
//-----------------------------------------------------------------------------
void ShaderProgram::fragSubroutine(const string &subroutine)
{
	GLuint index = fragSubroutineMap[subroutine];
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &index);
}
//-----------------------------------------------------------------------------
void ShaderProgram::geomSubroutine(const string &subroutine)
{
	GLuint index = geomSubroutineMap[subroutine];
	glUniformSubroutinesuiv(GL_GEOMETRY_SHADER, 1, &index);
}
//-----------------------------------------------------------------------------
void ShaderProgram::evalSubroutine(const string &subroutine)
{
	GLuint index = evalSubroutineMap[subroutine];
	glUniformSubroutinesuiv(GL_TESS_EVALUATION_SHADER, 1, &index);
}
//-----------------------------------------------------------------------------
void ShaderProgram::ctrlSubroutine(const string &subroutine)
{
	GLuint index = compSubroutineMap[subroutine];
	glUniformSubroutinesuiv(GL_TESS_CONTROL_SHADER, 1, &index);
}
//-----------------------------------------------------------------------------
void ShaderProgram::compSubroutine(const string &subroutine)
{
	GLuint index = compSubroutineMap[subroutine];
	glUniformSubroutinesuiv(GL_COMPUTE_SHADER, 1, &index);
}
//*****************************************************************************
//Get Subroutines**************************************************************
//*****************************************************************************
vector<string> ShaderProgram::getStageSubroutines(GLenum shaderType)
{
	vector<string> subroutines;

	GLint maxSubroutineLength, numSubroutines;
	GLsizei subroutineSize;

	glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINES,           &numSubroutines     );
	glGetProgramStageiv(program_id, shaderType, GL_ACTIVE_SUBROUTINE_MAX_LENGTH, &maxSubroutineLength);

	GLchar *subroutineName = new GLchar[maxSubroutineLength];

	for( int i = 0; i < numSubroutines; i++ ) 
	{
		glGetActiveSubroutineName( program_id, shaderType, i, maxSubroutineLength, &subroutineSize, subroutineName );

		subroutines.push_back(string(subroutineName));
	}

	delete [] subroutineName;

	return subroutines;
}
//-----------------------------------------------------------------------------
vector<string> ShaderProgram::getVertSubroutines()
{
	return getStageSubroutines(GL_VERTEX_SHADER);
}
//-----------------------------------------------------------------------------
vector<string> ShaderProgram::getFragSubroutines()
{
	return getStageSubroutines(GL_FRAGMENT_SHADER);
}
//-----------------------------------------------------------------------------
vector<string> ShaderProgram::getGeomSubroutines()
{
	return getStageSubroutines(GL_GEOMETRY_SHADER);
}
//-----------------------------------------------------------------------------
vector<string> ShaderProgram::getEvalSubroutines()
{
	return getStageSubroutines(GL_TESS_EVALUATION_SHADER);
}
//-----------------------------------------------------------------------------
vector<string> ShaderProgram::getCtrlSubroutines()
{
	return getStageSubroutines(GL_TESS_CONTROL_SHADER);
}
//-----------------------------------------------------------------------------
vector<string> ShaderProgram::getCompSubroutines()
{
	return getStageSubroutines(GL_COMPUTE_SHADER);
}


void render::ShaderProgram::programBinary()
{
	GLsizei bufferSize;
	GLsizei binaryLength;
	GLenum  binaryFormat;

	glGetProgramiv(program_id, GL_PROGRAM_BINARY_LENGTH, &bufferSize);

	GLubyte *binaryBuffer = new GLubyte[bufferSize];
	glGetProgramBinary(program_id, bufferSize, &binaryLength, &binaryFormat, binaryBuffer);

	stringstream shaderBinaryNameStream;

	shaderBinaryNameStream << "shader_" << program_id << ".glslBin";

	ofstream binaryOut;
	binaryOut.open(shaderBinaryNameStream.str().c_str(), ios_base::binary);
	if(!binaryOut.is_open())
	{
		cerr << "Failed to output shader binary \"" << shaderBinaryNameStream.str() << "\"!" << endl;
		return;
	}
	binaryOut.write((const char *)binaryBuffer, binaryLength);
	binaryOut.close();
}
