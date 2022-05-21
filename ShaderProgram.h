#ifndef _SHADER_PROGRAM
#define _SHADER_PROGRAM

namespace GayCubes
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		unsigned int shaderProgram;

		// TODO: anything but this
		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		// SIIIIN
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n\0";

	private:
		void CreateShader(unsigned int shader, const char* source);
	};
}

#endif //_SHADER_PROGRAM

