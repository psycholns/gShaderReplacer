typedef void(__stdcall *PFNGLSHADERSOURCEPROC)(unsigned shader, int count, const char **string, const int *length);
typedef void(__stdcall *PFNGLCOMPILESHADERPROC)(unsigned shader);
typedef void(__stdcall *PFNGLLINKPROGRAMPROC)(unsigned program);

typedef void(__stdcall *PFNGLGETPROGRAMIVPROC)(unsigned program, int pname, int *params);
typedef void(__stdcall *PFNGLGETPROGRAMINFOLOGPROC)(unsigned program, int bufSize, int *length, char *infoLog);
typedef void(__stdcall *PFNGLGETSHADERIVPROC)(unsigned shader, int pname, int *params);
typedef void(__stdcall *PFNGLGETSHADERINFOLOGPROC)(unsigned shader, int bufSize, int *length, char *infoLog);
typedef void(__stdcall *PFNGLGETSHADERSOURCEPROC)(unsigned shader, int bufSize, int *length, char *source);

typedef void(__stdcall *PFNGLSHADERSOURCEARBPROC)(unsigned shaderObj, int count, const char **string, const int *length);

typedef unsigned(__stdcall *PFNGLCREATESHADERPROGRAMVPROC) (unsigned type, unsigned count, const char *const*strings);

#define GL_COMPILE_STATUS                    0x8B81
#define GL_LINK_STATUS                       0x8B82
#define GL_VALIDATE_STATUS                   0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_LINK_STATUS                    0x8B82

extern PFNGLSHADERSOURCEPROC orig_glShaderSource;
extern PFNGLCOMPILESHADERPROC orig_glCompileShader;
extern PFNGLLINKPROGRAMPROC orig_glLinkProgram;
extern PFNGLCREATESHADERPROGRAMVPROC orig_glCreateShaderProgramv;

extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC	glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETSHADERSOURCEPROC glGetShaderSource;
extern PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv;

void __stdcall my_glShaderSource(unsigned shader, int count, const char **string, const int *length);
void __stdcall my_glCompileShader(unsigned shader);
void __stdcall my_glLinkProgram(unsigned program);
unsigned __stdcall my_glCreateShaderProgramv(unsigned type, unsigned count, const char *const*strings);

