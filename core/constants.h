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
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\0"
	};

	inline const char* fragShaderSource
	{
		"#version 420 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(ourColor, 1.0);\n"
		"}\0"
	};
};

#endif
