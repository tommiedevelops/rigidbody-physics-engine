#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants
{
	inline int windowWidth{ 500 };
	inline int windowHeight{ 500 };

	inline const char* vertShaderSource
	{
		"#version 420 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0"
	};

	inline const char* fragShaderSource
	{
		"#version 420 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
		"}\0"
	};
};

#endif
