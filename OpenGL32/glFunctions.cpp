#include <stdio.h>
#include <stdlib.h>
#include <msxml2.h>

#include "glfunctions.h"
#include "configuration.h"

PFNGLSHADERSOURCEPROC orig_glShaderSource = 0;
PFNGLCOMPILESHADERPROC orig_glCompileShader = 0;
PFNGLLINKPROGRAMPROC orig_glLinkProgram = 0;
PFNGLCREATESHADERPROGRAMVPROC orig_glCreateShaderProgramv = NULL;

PFNGLGETPROGRAMIVPROC			glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC		glGetProgramInfoLog = NULL;
PFNGLGETSHADERIVPROC			glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC		glGetShaderInfoLog = NULL;
PFNGLGETSHADERSOURCEPROC		glGetShaderSource = NULL;
PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv = NULL;

/////////////////// helpers /////////////////////////////
static char dirname[501], filename[501];
static FILE *logfile;
void openLog(const char* type, int shader)
{
	GetModuleFileName(GetModuleHandle(0), filename, 500);
	sprintf_s(dirname, 500, "%s_shaders", filename);
	CreateDirectory(dirname, 0);
	sprintf_s(filename, 500, "%s/%s_%d.log", dirname, type, shader);
	fopen_s(&logfile, filename, "wb");
}

////////////////////////////////////////////////////////

void __stdcall my_glShaderSource(unsigned shader, int count, const char **string, const int *length)
{
	const char *newstring = Configuration::GetInstance()->ReplaceShader(count, string, length);
	orig_glShaderSource(shader, 1, &newstring, 0);
}

void __stdcall my_glCompileShader(unsigned shader)
{
	openLog("shader", shader);
	if (logfile)
	{
		fprintf(logfile, "Compiling...");
		fflush(logfile);
	}

	orig_glCompileShader(shader);

	Configuration *conf = Configuration::GetInstance();
	if (!conf->_dumpAllShaders && !conf->_dumpErrorShaders)
		return;

	if (logfile)
	{
		fprintf(logfile, "Getting info...");
		fflush(logfile);
	}

	int compileStatus, infoLogLength;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (compileStatus == 0 || Configuration::GetInstance()->_dumpAllShaders)
	{
		if (logfile)
		{
			fprintf(logfile, "Dumping...\n");
			fflush(logfile);
		}

		const int buffersize = 50000;
		static char buffer[buffersize];
		int length = 0;
		glGetShaderSource(shader, buffersize, &length, &buffer[0]);

		sprintf_s(filename, 500, "%s/shader_%d.glsl", dirname, shader);
		FILE *shaderfile;
		fopen_s(&shaderfile, filename, "wb");
		if (shaderfile)
		{
			fwrite(buffer, 1, length, shaderfile);
			fclose(shaderfile);
		}

		if (logfile)
		{
			fprintf(logfile, "Compile status:%d\n", compileStatus);
			if (infoLogLength)
			{
				char *infoLog = (char*)malloc(infoLogLength);
				glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
				fprintf(logfile, "Info Log:%s\n\n", infoLog);
				free(infoLog);
			}
			fclose(logfile);
		}
	}
}

void __stdcall my_glLinkProgram(unsigned program)
{
	orig_glLinkProgram(program);

	openLog("program", program);
	int linkStatus, infoLogLength;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (linkStatus == 0 || Configuration::GetInstance()->_dumpAllShaders)
	{
		if (logfile)
		{
			fprintf(logfile, "Dumping...\n");
			fflush(logfile);
		}
		if (logfile)
		{
			fprintf(logfile, "Link status:%d\n", linkStatus);
			if (infoLogLength)
			{
				char *infoLog = (char*)malloc(infoLogLength);
				glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
				fprintf(logfile, "Info Log:%s\n\n", infoLog);
				free(infoLog);
			}
			fclose(logfile);
		}
	}
}

unsigned __stdcall my_glCreateShaderProgramv(unsigned type, unsigned count, const char *const*strings)
{
	const char *newstring = Configuration::GetInstance()->ReplaceShader(count, strings, 0);

	unsigned program = orig_glCreateShaderProgramv(type, 1, &newstring);
	//unsigned program=orig_glCreateShaderProgramv(type,count,strings);

	openLog("program", program);
	if (logfile)
	{
		fprintf(logfile, "Compiling...");
		fflush(logfile);
	}

	Configuration *conf = Configuration::GetInstance();
	if (!conf->_dumpAllShaders && !conf->_dumpErrorShaders)
		return program;

	if (logfile)
	{
		fprintf(logfile, "Getting info...");
		fflush(logfile);
	}

	int linkStatus, infoLogLength;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (linkStatus == 0 || Configuration::GetInstance()->_dumpAllShaders)
	{
		if (logfile)
		{
			fprintf(logfile, "Dumping...\n");
			fflush(logfile);
		}

		sprintf_s(filename, 500, "%s/program_%d.glsl", dirname, program);
		FILE *shaderfile;
		fopen_s(&shaderfile, filename, "wb");
		if (shaderfile)
		{
			fwrite(newstring, 1, strlen(newstring), shaderfile);
			fclose(shaderfile);
		}

		if (logfile)
		{
			fprintf(logfile, "Link status:%d\n", linkStatus);
			if (infoLogLength)
			{
				char *infoLog = (char*)malloc(infoLogLength);
				glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
				fprintf(logfile, "Info Log:%s\n\n", infoLog);
				free(infoLog);
			}
			fclose(logfile);
		}
	}

	return program;
}