#ifndef _SHADER_PROGRAM
#define _SHADER_PROGRAM

namespace GayCubes
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		void SetGlobalValue(float value, const char name[]);

		unsigned int shaderProgram;

		// TODO: anything but this
		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aColor;\n"
			"out vec4 vertexColor;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(aPos, 1.0);\n"
			"	vertexColor = vec4(aColor, 1.0);\n"
			" };\n\0";

		// SIIIIN
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec4 vertexColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vertexColor;\n"
			"}\n\0";

	private:
		void CreateShader(unsigned int shader, const char* source);
	};
}

#endif //_SHADER_PROGRAM

