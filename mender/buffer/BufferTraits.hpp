//******************************************************************************
//render/buffer/BufferTraits.h**************************************************
//******************************************************************************

	template<typename T>
	struct traits
	{
		enum
		{
			target     = GL_NONE,
			components = 0,
			type       = GL_NONE,
			size       = 0,
		};
	};

#define BUFFER_TARGET(a, b) template<> struct traits<a>{ enum{ target = b }; };

	BUFFER_TARGET(struct BufTarget_Array,            GL_ARRAY_BUFFER             );
	BUFFER_TARGET(struct BufTarget_Element,          GL_ELEMENT_ARRAY_BUFFER     );
	BUFFER_TARGET(struct BufTarget_Uniform,          GL_UNIFORM_BUFFER           );
	BUFFER_TARGET(struct BufTarget_Indirect,         GL_DRAW_INDIRECT_BUFFER     );
	BUFFER_TARGET(struct BufTarget_DispatchIndirect, GL_DISPATCH_INDIRECT_BUFFER );
	BUFFER_TARGET(struct BufTarget_AtomicCounter,    GL_ATOMIC_COUNTER_BUFFER    );
	

#define BUFFER_TYPE(a, b, c) template<> struct traits<a>{ enum{ components = b, type = c}; };

	BUFFER_TYPE(char,  1, GL_BYTE);
	BUFFER_TYPE(vec2b, 2, GL_BYTE);
	BUFFER_TYPE(vec3b, 3, GL_BYTE);
	BUFFER_TYPE(vec4b, 4, GL_BYTE);

	BUFFER_TYPE(unsigned char,  1, GL_UNSIGNED_BYTE);
	BUFFER_TYPE(vec2ub,         2, GL_UNSIGNED_BYTE);
	BUFFER_TYPE(vec3ub,         3, GL_UNSIGNED_BYTE);
	BUFFER_TYPE(vec4ub,         4, GL_UNSIGNED_BYTE);


	BUFFER_TYPE(int,   1, GL_INT);
	BUFFER_TYPE(vec2i, 2, GL_INT);
	BUFFER_TYPE(vec3i, 3, GL_INT);
	BUFFER_TYPE(vec4i, 4, GL_INT);

	BUFFER_TYPE(unsigned int, 1, GL_UNSIGNED_INT);
	BUFFER_TYPE(vec2ui,       2, GL_UNSIGNED_INT);
	BUFFER_TYPE(vec3ui,       3, GL_UNSIGNED_INT);
	BUFFER_TYPE(vec4ui,       4, GL_UNSIGNED_INT);

	BUFFER_TYPE(float, 1, GL_FLOAT);
	BUFFER_TYPE(vec2f, 2, GL_FLOAT);
	BUFFER_TYPE(vec4f, 4, GL_FLOAT);
	BUFFER_TYPE(vec3f, 3, GL_FLOAT);
	
	BUFFER_TYPE(short int, 1, GL_SHORT);
	BUFFER_TYPE(vec2s,     2, GL_SHORT);
	BUFFER_TYPE(vec3s,     3, GL_SHORT);
	BUFFER_TYPE(vec4s,     4, GL_SHORT);

	BUFFER_TYPE(unsigned short int, 1, GL_UNSIGNED_SHORT);
	BUFFER_TYPE(vec2us,             2, GL_UNSIGNED_SHORT);
	BUFFER_TYPE(vec3us,             3, GL_UNSIGNED_SHORT);
	BUFFER_TYPE(vec4us,             4, GL_UNSIGNED_SHORT);

	BUFFER_TYPE(double, 1, GL_DOUBLE);
	BUFFER_TYPE(vec2d,  2, GL_DOUBLE);
	BUFFER_TYPE(vec3d,  3, GL_DOUBLE);
	BUFFER_TYPE(vec4d,  4, GL_DOUBLE);






