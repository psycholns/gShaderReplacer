#include <windows.h>
#include <gl/gl.h>
#include "glext.h"

const static PIXELFORMATDESCRIPTOR pfd={0,0,PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

char *fsrc="asl<0.05)|	gl_Te<0.3&fract   ædkas .bw adæasd.bw aSK\n";
void ShaderSetup()
{
int s, p;
  p = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))();
 // s = ((PFNGLCREATESHADERPROC)(wglGetProcAddress("glCreateShader")))(GL_VERTEX_SHADER);
  //((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(s, 1, (const char**)&vsrc, 0);
 // ((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(s);
 // ((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(p,s);
  s = ((PFNGLCREATESHADERPROC)(wglGetProcAddress("glCreateShader")))(GL_FRAGMENT_SHADER);	
  ((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))(s, 1, (const char**)&fsrc, 0);
  ((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))(s);
  ((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))(p,s);
  ((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))(p);
  ((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(p);
}

int WINAPI WinMain(HINSTANCE i, HINSTANCE p, LPSTR cmd, int n)
{
  HDC hDC = GetDC( CreateWindow("edit", 0, WS_POPUP|WS_VISIBLE, 0,0,0,0,0,0,0,0) );
  SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
  wglMakeCurrent(hDC, wglCreateContext(hDC));

  ShowCursor(FALSE); 
  
  glGetString(GL_VENDOR);
  ShaderSetup();

  //do
  { glRects(-1,-1,1,1);
    SwapBuffers(hDC);
  }
  //while ( !GetAsyncKeyState(VK_ESCAPE) ); 
}


/*
int main(int argc, char* argv[])
{
	//HMODULE module = LoadLibrary("opengl32.dll");

	glRects(-1,-1,1,1);
}*/
