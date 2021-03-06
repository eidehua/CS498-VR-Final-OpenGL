#include "load_file.h"

using namespace std;

std::string loadFile(const char *fname)
{
	std::ifstream file(fname);
	if (!file.is_open())
	{
		cout << "Unable to open file " << fname << endl;
		exit(1);
	}

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();

	return fileData.str();
}

// printShaderInfoLog
// From OpenGL Shading Language 3rd Edition, p215-216
// Display (hopefully) useful error messages if shader fails to compile
void printShaderInfoLog(GLint shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
		debug.write(infoLog);
		delete[] infoLog;
	}
}

int LoadShader(const char *pfilePath_vs, const char *pfilePath_fs, bool bindTexCoord0, bool bindNormal, bool bindColor, GLuint &shaderProgram, GLuint &vertexShader, GLuint &fragmentShader)
{
	shaderProgram = 0;
	vertexShader = 0;
	fragmentShader = 0;

	// load shaders & get length of each
	int vlen;
	int flen;
	std::string vertexShaderString = loadFile(pfilePath_vs);
	std::string fragmentShaderString = loadFile(pfilePath_fs);
	vlen = vertexShaderString.length();
	flen = fragmentShaderString.length();

	if (vertexShaderString.empty())
	{
		return -1;
	}

	if (fragmentShaderString.empty())
	{
		return -1;
	}

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char *vertexShaderCStr = vertexShaderString.c_str();
	const char *fragmentShaderCStr = fragmentShaderString.c_str();
	glShaderSource(vertexShader, 1, (const GLchar **)&vertexShaderCStr, &vlen);
	glShaderSource(fragmentShader, 1, (const GLchar **)&fragmentShaderCStr, &flen);

	GLint compiled;

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == FALSE)
	{
		debug.write("Vertex shader not compiled.");
		printShaderInfoLog(vertexShader);

		glDeleteShader(vertexShader);
		vertexShader = 0;
		glDeleteShader(fragmentShader);
		fragmentShader = 0;

		return -1;
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == FALSE)
	{
		cout << "Fragment shader not compiled." << endl;
		printShaderInfoLog(fragmentShader);

		glDeleteShader(vertexShader);
		vertexShader = 0;
		glDeleteShader(fragmentShader);
		fragmentShader = 0;

		return -1;
	}

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindAttribLocation(shaderProgram, 0, "InVertex");

	if (bindTexCoord0)
		glBindAttribLocation(shaderProgram, 1, "InTexCoord0");

	if (bindNormal)
		glBindAttribLocation(shaderProgram, 2, "InNormal");

	if (bindColor)
		glBindAttribLocation(shaderProgram, 3, "InColor");

	glLinkProgram(shaderProgram);

	GLint IsLinked;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (GLint *)&IsLinked);
	if (IsLinked == FALSE)
	{
		cout << "Failed to link shader." << endl;

		GLint maxLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
		if (maxLength>0)
		{
			char *pLinkInfoLog = new char[maxLength];
			glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, pLinkInfoLog);
			cout << pLinkInfoLog << endl;
			delete[] pLinkInfoLog;
		}

		glDetachShader(shaderProgram, vertexShader);
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(vertexShader);
		vertexShader = 0;
		glDeleteShader(fragmentShader);
		fragmentShader = 0;
		glDeleteProgram(shaderProgram);
		shaderProgram = 0;

		return -1;
	}

	return 1;		//Success
}