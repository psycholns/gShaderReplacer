#include <windows.h>
//#include <stdio.h>
#include "glfunctions.h"
#pragma pack(1)

static HINSTANCE hLThis = 0;
static HINSTANCE hL = 0;
FARPROC p[368] = { 0 };
static bool inited;

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		hLThis = hInst;
		inited = false;
		for (int i = 0; i < 368; i++) p[i] = (FARPROC)(0xbeef0000 + i);
	}
	if (reason == DLL_PROCESS_DETACH)
	{
		//if (hL) FreeLibrary(hL); // not safe, better leave it open
	}
	return 1;
}

const char* myglGetString(int in)
{
	typedef const char* (__stdcall *pS)(int a);
	pS pps = (pS)p[124];
	return pps(in);
}

#define INIT_GL if (!inited) InitGL();
void InitGL()
{
	char DefaultGLLibName[600];
	GetSystemDirectory(DefaultGLLibName, 600);
	char *c = DefaultGLLibName;
	while (*++c);
	static char *name = "\\opengl32.dll";
	for (int i = 0; i < 14; i++) c[i] = name[i];
	hL = LoadLibrary(DefaultGLLibName);
	if (!hL) return;
	inited = true;

	p[0] = GetProcAddress(hL, "GlmfBeginGlsBlock");
	p[1] = GetProcAddress(hL, "GlmfCloseMetaFile");
	p[2] = GetProcAddress(hL, "GlmfEndGlsBlock");
	p[3] = GetProcAddress(hL, "GlmfEndPlayback");
	p[4] = GetProcAddress(hL, "GlmfInitPlayback");
	p[5] = GetProcAddress(hL, "GlmfPlayGlsRecord");
	p[6] = GetProcAddress(hL, "glAccum");
	p[7] = GetProcAddress(hL, "glAlphaFunc");
	p[8] = GetProcAddress(hL, "glAreTexturesResident");
	p[9] = GetProcAddress(hL, "glArrayElement");
	p[10] = GetProcAddress(hL, "glBegin");
	p[11] = GetProcAddress(hL, "glBindTexture");
	p[12] = GetProcAddress(hL, "glBitmap");
	p[13] = GetProcAddress(hL, "glBlendFunc");
	p[14] = GetProcAddress(hL, "glCallList");
	p[15] = GetProcAddress(hL, "glCallLists");
	p[16] = GetProcAddress(hL, "glClear");
	p[17] = GetProcAddress(hL, "glClearAccum");
	p[18] = GetProcAddress(hL, "glClearColor");
	p[19] = GetProcAddress(hL, "glClearDepth");
	p[20] = GetProcAddress(hL, "glClearIndex");
	p[21] = GetProcAddress(hL, "glClearStencil");
	p[22] = GetProcAddress(hL, "glClipPlane");
	p[23] = GetProcAddress(hL, "glColor3b");
	p[24] = GetProcAddress(hL, "glColor3bv");
	p[25] = GetProcAddress(hL, "glColor3d");
	p[26] = GetProcAddress(hL, "glColor3dv");
	p[27] = GetProcAddress(hL, "glColor3f");
	p[28] = GetProcAddress(hL, "glColor3fv");
	p[29] = GetProcAddress(hL, "glColor3i");
	p[30] = GetProcAddress(hL, "glColor3iv");
	p[31] = GetProcAddress(hL, "glColor3s");
	p[32] = GetProcAddress(hL, "glColor3sv");
	p[33] = GetProcAddress(hL, "glColor3ub");
	p[34] = GetProcAddress(hL, "glColor3ubv");
	p[35] = GetProcAddress(hL, "glColor3ui");
	p[36] = GetProcAddress(hL, "glColor3uiv");
	p[37] = GetProcAddress(hL, "glColor3us");
	p[38] = GetProcAddress(hL, "glColor3usv");
	p[39] = GetProcAddress(hL, "glColor4b");
	p[40] = GetProcAddress(hL, "glColor4bv");
	p[41] = GetProcAddress(hL, "glColor4d");
	p[42] = GetProcAddress(hL, "glColor4dv");
	p[43] = GetProcAddress(hL, "glColor4f");
	p[44] = GetProcAddress(hL, "glColor4fv");
	p[45] = GetProcAddress(hL, "glColor4i");
	p[46] = GetProcAddress(hL, "glColor4iv");
	p[47] = GetProcAddress(hL, "glColor4s");
	p[48] = GetProcAddress(hL, "glColor4sv");
	p[49] = GetProcAddress(hL, "glColor4ub");
	p[50] = GetProcAddress(hL, "glColor4ubv");
	p[51] = GetProcAddress(hL, "glColor4ui");
	p[52] = GetProcAddress(hL, "glColor4uiv");
	p[53] = GetProcAddress(hL, "glColor4us");
	p[54] = GetProcAddress(hL, "glColor4usv");
	p[55] = GetProcAddress(hL, "glColorMask");
	p[56] = GetProcAddress(hL, "glColorMaterial");
	p[57] = GetProcAddress(hL, "glColorPointer");
	p[58] = GetProcAddress(hL, "glCopyPixels");
	p[59] = GetProcAddress(hL, "glCopyTexImage1D");
	p[60] = GetProcAddress(hL, "glCopyTexImage2D");
	p[61] = GetProcAddress(hL, "glCopyTexSubImage1D");
	p[62] = GetProcAddress(hL, "glCopyTexSubImage2D");
	p[63] = GetProcAddress(hL, "glCullFace");
	p[64] = GetProcAddress(hL, "glDebugEntry");
	p[65] = GetProcAddress(hL, "glDeleteLists");
	p[66] = GetProcAddress(hL, "glDeleteTextures");
	p[67] = GetProcAddress(hL, "glDepthFunc");
	p[68] = GetProcAddress(hL, "glDepthMask");
	p[69] = GetProcAddress(hL, "glDepthRange");
	p[70] = GetProcAddress(hL, "glDisable");
	p[71] = GetProcAddress(hL, "glDisableClientState");
	p[72] = GetProcAddress(hL, "glDrawArrays");
	p[73] = GetProcAddress(hL, "glDrawBuffer");
	p[74] = GetProcAddress(hL, "glDrawElements");
	p[75] = GetProcAddress(hL, "glDrawPixels");
	p[76] = GetProcAddress(hL, "glEdgeFlag");
	p[77] = GetProcAddress(hL, "glEdgeFlagPointer");
	p[78] = GetProcAddress(hL, "glEdgeFlagv");
	p[79] = GetProcAddress(hL, "glEnable");
	p[80] = GetProcAddress(hL, "glEnableClientState");
	p[81] = GetProcAddress(hL, "glEnd");
	p[82] = GetProcAddress(hL, "glEndList");
	p[83] = GetProcAddress(hL, "glEvalCoord1d");
	p[84] = GetProcAddress(hL, "glEvalCoord1dv");
	p[85] = GetProcAddress(hL, "glEvalCoord1f");
	p[86] = GetProcAddress(hL, "glEvalCoord1fv");
	p[87] = GetProcAddress(hL, "glEvalCoord2d");
	p[88] = GetProcAddress(hL, "glEvalCoord2dv");
	p[89] = GetProcAddress(hL, "glEvalCoord2f");
	p[90] = GetProcAddress(hL, "glEvalCoord2fv");
	p[91] = GetProcAddress(hL, "glEvalMesh1");
	p[92] = GetProcAddress(hL, "glEvalMesh2");
	p[93] = GetProcAddress(hL, "glEvalPoint1");
	p[94] = GetProcAddress(hL, "glEvalPoint2");
	p[95] = GetProcAddress(hL, "glFeedbackBuffer");
	p[96] = GetProcAddress(hL, "glFinish");
	p[97] = GetProcAddress(hL, "glFlush");
	p[98] = GetProcAddress(hL, "glFogf");
	p[99] = GetProcAddress(hL, "glFogfv");
	p[100] = GetProcAddress(hL, "glFogi");
	p[101] = GetProcAddress(hL, "glFogiv");
	p[102] = GetProcAddress(hL, "glFrontFace");
	p[103] = GetProcAddress(hL, "glFrustum");
	p[104] = GetProcAddress(hL, "glGenLists");
	p[105] = GetProcAddress(hL, "glGenTextures");
	p[106] = GetProcAddress(hL, "glGetBooleanv");
	p[107] = GetProcAddress(hL, "glGetClipPlane");
	p[108] = GetProcAddress(hL, "glGetDoublev");
	p[109] = GetProcAddress(hL, "glGetError");
	p[110] = GetProcAddress(hL, "glGetFloatv");
	p[111] = GetProcAddress(hL, "glGetIntegerv");
	p[112] = GetProcAddress(hL, "glGetLightfv");
	p[113] = GetProcAddress(hL, "glGetLightiv");
	p[114] = GetProcAddress(hL, "glGetMapdv");
	p[115] = GetProcAddress(hL, "glGetMapfv");
	p[116] = GetProcAddress(hL, "glGetMapiv");
	p[117] = GetProcAddress(hL, "glGetMaterialfv");
	p[118] = GetProcAddress(hL, "glGetMaterialiv");
	p[119] = GetProcAddress(hL, "glGetPixelMapfv");
	p[120] = GetProcAddress(hL, "glGetPixelMapuiv");
	p[121] = GetProcAddress(hL, "glGetPixelMapusv");
	p[122] = GetProcAddress(hL, "glGetPointerv");
	p[123] = GetProcAddress(hL, "glGetPolygonStipple");
	p[124] = GetProcAddress(hL, "glGetString");
	p[125] = GetProcAddress(hL, "glGetTexEnvfv");
	p[126] = GetProcAddress(hL, "glGetTexEnviv");
	p[127] = GetProcAddress(hL, "glGetTexGendv");
	p[128] = GetProcAddress(hL, "glGetTexGenfv");
	p[129] = GetProcAddress(hL, "glGetTexGeniv");
	p[130] = GetProcAddress(hL, "glGetTexImage");
	p[131] = GetProcAddress(hL, "glGetTexLevelParameterfv");
	p[132] = GetProcAddress(hL, "glGetTexLevelParameteriv");
	p[133] = GetProcAddress(hL, "glGetTexParameterfv");
	p[134] = GetProcAddress(hL, "glGetTexParameteriv");
	p[135] = GetProcAddress(hL, "glHint");
	p[136] = GetProcAddress(hL, "glIndexMask");
	p[137] = GetProcAddress(hL, "glIndexPointer");
	p[138] = GetProcAddress(hL, "glIndexd");
	p[139] = GetProcAddress(hL, "glIndexdv");
	p[140] = GetProcAddress(hL, "glIndexf");
	p[141] = GetProcAddress(hL, "glIndexfv");
	p[142] = GetProcAddress(hL, "glIndexi");
	p[143] = GetProcAddress(hL, "glIndexiv");
	p[144] = GetProcAddress(hL, "glIndexs");
	p[145] = GetProcAddress(hL, "glIndexsv");
	p[146] = GetProcAddress(hL, "glIndexub");
	p[147] = GetProcAddress(hL, "glIndexubv");
	p[148] = GetProcAddress(hL, "glInitNames");
	p[149] = GetProcAddress(hL, "glInterleavedArrays");
	p[150] = GetProcAddress(hL, "glIsEnabled");
	p[151] = GetProcAddress(hL, "glIsList");
	p[152] = GetProcAddress(hL, "glIsTexture");
	p[153] = GetProcAddress(hL, "glLightModelf");
	p[154] = GetProcAddress(hL, "glLightModelfv");
	p[155] = GetProcAddress(hL, "glLightModeli");
	p[156] = GetProcAddress(hL, "glLightModeliv");
	p[157] = GetProcAddress(hL, "glLightf");
	p[158] = GetProcAddress(hL, "glLightfv");
	p[159] = GetProcAddress(hL, "glLighti");
	p[160] = GetProcAddress(hL, "glLightiv");
	p[161] = GetProcAddress(hL, "glLineStipple");
	p[162] = GetProcAddress(hL, "glLineWidth");
	p[163] = GetProcAddress(hL, "glListBase");
	p[164] = GetProcAddress(hL, "glLoadIdentity");
	p[165] = GetProcAddress(hL, "glLoadMatrixd");
	p[166] = GetProcAddress(hL, "glLoadMatrixf");
	p[167] = GetProcAddress(hL, "glLoadName");
	p[168] = GetProcAddress(hL, "glLogicOp");
	p[169] = GetProcAddress(hL, "glMap1d");
	p[170] = GetProcAddress(hL, "glMap1f");
	p[171] = GetProcAddress(hL, "glMap2d");
	p[172] = GetProcAddress(hL, "glMap2f");
	p[173] = GetProcAddress(hL, "glMapGrid1d");
	p[174] = GetProcAddress(hL, "glMapGrid1f");
	p[175] = GetProcAddress(hL, "glMapGrid2d");
	p[176] = GetProcAddress(hL, "glMapGrid2f");
	p[177] = GetProcAddress(hL, "glMaterialf");
	p[178] = GetProcAddress(hL, "glMaterialfv");
	p[179] = GetProcAddress(hL, "glMateriali");
	p[180] = GetProcAddress(hL, "glMaterialiv");
	p[181] = GetProcAddress(hL, "glMatrixMode");
	p[182] = GetProcAddress(hL, "glMultMatrixd");
	p[183] = GetProcAddress(hL, "glMultMatrixf");
	p[184] = GetProcAddress(hL, "glNewList");
	p[185] = GetProcAddress(hL, "glNormal3b");
	p[186] = GetProcAddress(hL, "glNormal3bv");
	p[187] = GetProcAddress(hL, "glNormal3d");
	p[188] = GetProcAddress(hL, "glNormal3dv");
	p[189] = GetProcAddress(hL, "glNormal3f");
	p[190] = GetProcAddress(hL, "glNormal3fv");
	p[191] = GetProcAddress(hL, "glNormal3i");
	p[192] = GetProcAddress(hL, "glNormal3iv");
	p[193] = GetProcAddress(hL, "glNormal3s");
	p[194] = GetProcAddress(hL, "glNormal3sv");
	p[195] = GetProcAddress(hL, "glNormalPointer");
	p[196] = GetProcAddress(hL, "glOrtho");
	p[197] = GetProcAddress(hL, "glPassThrough");
	p[198] = GetProcAddress(hL, "glPixelMapfv");
	p[199] = GetProcAddress(hL, "glPixelMapuiv");
	p[200] = GetProcAddress(hL, "glPixelMapusv");
	p[201] = GetProcAddress(hL, "glPixelStoref");
	p[202] = GetProcAddress(hL, "glPixelStorei");
	p[203] = GetProcAddress(hL, "glPixelTransferf");
	p[204] = GetProcAddress(hL, "glPixelTransferi");
	p[205] = GetProcAddress(hL, "glPixelZoom");
	p[206] = GetProcAddress(hL, "glPointSize");
	p[207] = GetProcAddress(hL, "glPolygonMode");
	p[208] = GetProcAddress(hL, "glPolygonOffset");
	p[209] = GetProcAddress(hL, "glPolygonStipple");
	p[210] = GetProcAddress(hL, "glPopAttrib");
	p[211] = GetProcAddress(hL, "glPopClientAttrib");
	p[212] = GetProcAddress(hL, "glPopMatrix");
	p[213] = GetProcAddress(hL, "glPopName");
	p[214] = GetProcAddress(hL, "glPrioritizeTextures");
	p[215] = GetProcAddress(hL, "glPushAttrib");
	p[216] = GetProcAddress(hL, "glPushClientAttrib");
	p[217] = GetProcAddress(hL, "glPushMatrix");
	p[218] = GetProcAddress(hL, "glPushName");
	p[219] = GetProcAddress(hL, "glRasterPos2d");
	p[220] = GetProcAddress(hL, "glRasterPos2dv");
	p[221] = GetProcAddress(hL, "glRasterPos2f");
	p[222] = GetProcAddress(hL, "glRasterPos2fv");
	p[223] = GetProcAddress(hL, "glRasterPos2i");
	p[224] = GetProcAddress(hL, "glRasterPos2iv");
	p[225] = GetProcAddress(hL, "glRasterPos2s");
	p[226] = GetProcAddress(hL, "glRasterPos2sv");
	p[227] = GetProcAddress(hL, "glRasterPos3d");
	p[228] = GetProcAddress(hL, "glRasterPos3dv");
	p[229] = GetProcAddress(hL, "glRasterPos3f");
	p[230] = GetProcAddress(hL, "glRasterPos3fv");
	p[231] = GetProcAddress(hL, "glRasterPos3i");
	p[232] = GetProcAddress(hL, "glRasterPos3iv");
	p[233] = GetProcAddress(hL, "glRasterPos3s");
	p[234] = GetProcAddress(hL, "glRasterPos3sv");
	p[235] = GetProcAddress(hL, "glRasterPos4d");
	p[236] = GetProcAddress(hL, "glRasterPos4dv");
	p[237] = GetProcAddress(hL, "glRasterPos4f");
	p[238] = GetProcAddress(hL, "glRasterPos4fv");
	p[239] = GetProcAddress(hL, "glRasterPos4i");
	p[240] = GetProcAddress(hL, "glRasterPos4iv");
	p[241] = GetProcAddress(hL, "glRasterPos4s");
	p[242] = GetProcAddress(hL, "glRasterPos4sv");
	p[243] = GetProcAddress(hL, "glReadBuffer");
	p[244] = GetProcAddress(hL, "glReadPixels");
	p[245] = GetProcAddress(hL, "glRectd");
	p[246] = GetProcAddress(hL, "glRectdv");
	p[247] = GetProcAddress(hL, "glRectf");
	p[248] = GetProcAddress(hL, "glRectfv");
	p[249] = GetProcAddress(hL, "glRecti");
	p[250] = GetProcAddress(hL, "glRectiv");
	p[251] = GetProcAddress(hL, "glRects");
	p[252] = GetProcAddress(hL, "glRectsv");
	p[253] = GetProcAddress(hL, "glRenderMode");
	p[254] = GetProcAddress(hL, "glRotated");
	p[255] = GetProcAddress(hL, "glRotatef");
	p[256] = GetProcAddress(hL, "glScaled");
	p[257] = GetProcAddress(hL, "glScalef");
	p[258] = GetProcAddress(hL, "glScissor");
	p[259] = GetProcAddress(hL, "glSelectBuffer");
	p[260] = GetProcAddress(hL, "glShadeModel");
	p[261] = GetProcAddress(hL, "glStencilFunc");
	p[262] = GetProcAddress(hL, "glStencilMask");
	p[263] = GetProcAddress(hL, "glStencilOp");
	p[264] = GetProcAddress(hL, "glTexCoord1d");
	p[265] = GetProcAddress(hL, "glTexCoord1dv");
	p[266] = GetProcAddress(hL, "glTexCoord1f");
	p[267] = GetProcAddress(hL, "glTexCoord1fv");
	p[268] = GetProcAddress(hL, "glTexCoord1i");
	p[269] = GetProcAddress(hL, "glTexCoord1iv");
	p[270] = GetProcAddress(hL, "glTexCoord1s");
	p[271] = GetProcAddress(hL, "glTexCoord1sv");
	p[272] = GetProcAddress(hL, "glTexCoord2d");
	p[273] = GetProcAddress(hL, "glTexCoord2dv");
	p[274] = GetProcAddress(hL, "glTexCoord2f");
	p[275] = GetProcAddress(hL, "glTexCoord2fv");
	p[276] = GetProcAddress(hL, "glTexCoord2i");
	p[277] = GetProcAddress(hL, "glTexCoord2iv");
	p[278] = GetProcAddress(hL, "glTexCoord2s");
	p[279] = GetProcAddress(hL, "glTexCoord2sv");
	p[280] = GetProcAddress(hL, "glTexCoord3d");
	p[281] = GetProcAddress(hL, "glTexCoord3dv");
	p[282] = GetProcAddress(hL, "glTexCoord3f");
	p[283] = GetProcAddress(hL, "glTexCoord3fv");
	p[284] = GetProcAddress(hL, "glTexCoord3i");
	p[285] = GetProcAddress(hL, "glTexCoord3iv");
	p[286] = GetProcAddress(hL, "glTexCoord3s");
	p[287] = GetProcAddress(hL, "glTexCoord3sv");
	p[288] = GetProcAddress(hL, "glTexCoord4d");
	p[289] = GetProcAddress(hL, "glTexCoord4dv");
	p[290] = GetProcAddress(hL, "glTexCoord4f");
	p[291] = GetProcAddress(hL, "glTexCoord4fv");
	p[292] = GetProcAddress(hL, "glTexCoord4i");
	p[293] = GetProcAddress(hL, "glTexCoord4iv");
	p[294] = GetProcAddress(hL, "glTexCoord4s");
	p[295] = GetProcAddress(hL, "glTexCoord4sv");
	p[296] = GetProcAddress(hL, "glTexCoordPointer");
	p[297] = GetProcAddress(hL, "glTexEnvf");
	p[298] = GetProcAddress(hL, "glTexEnvfv");
	p[299] = GetProcAddress(hL, "glTexEnvi");
	p[300] = GetProcAddress(hL, "glTexEnviv");
	p[301] = GetProcAddress(hL, "glTexGend");
	p[302] = GetProcAddress(hL, "glTexGendv");
	p[303] = GetProcAddress(hL, "glTexGenf");
	p[304] = GetProcAddress(hL, "glTexGenfv");
	p[305] = GetProcAddress(hL, "glTexGeni");
	p[306] = GetProcAddress(hL, "glTexGeniv");
	p[307] = GetProcAddress(hL, "glTexImage1D");
	p[308] = GetProcAddress(hL, "glTexImage2D");
	p[309] = GetProcAddress(hL, "glTexParameterf");
	p[310] = GetProcAddress(hL, "glTexParameterfv");
	p[311] = GetProcAddress(hL, "glTexParameteri");
	p[312] = GetProcAddress(hL, "glTexParameteriv");
	p[313] = GetProcAddress(hL, "glTexSubImage1D");
	p[314] = GetProcAddress(hL, "glTexSubImage2D");
	p[315] = GetProcAddress(hL, "glTranslated");
	p[316] = GetProcAddress(hL, "glTranslatef");
	p[317] = GetProcAddress(hL, "glVertex2d");
	p[318] = GetProcAddress(hL, "glVertex2dv");
	p[319] = GetProcAddress(hL, "glVertex2f");
	p[320] = GetProcAddress(hL, "glVertex2fv");
	p[321] = GetProcAddress(hL, "glVertex2i");
	p[322] = GetProcAddress(hL, "glVertex2iv");
	p[323] = GetProcAddress(hL, "glVertex2s");
	p[324] = GetProcAddress(hL, "glVertex2sv");
	p[325] = GetProcAddress(hL, "glVertex3d");
	p[326] = GetProcAddress(hL, "glVertex3dv");
	p[327] = GetProcAddress(hL, "glVertex3f");
	p[328] = GetProcAddress(hL, "glVertex3fv");
	p[329] = GetProcAddress(hL, "glVertex3i");
	p[330] = GetProcAddress(hL, "glVertex3iv");
	p[331] = GetProcAddress(hL, "glVertex3s");
	p[332] = GetProcAddress(hL, "glVertex3sv");
	p[333] = GetProcAddress(hL, "glVertex4d");
	p[334] = GetProcAddress(hL, "glVertex4dv");
	p[335] = GetProcAddress(hL, "glVertex4f");
	p[336] = GetProcAddress(hL, "glVertex4fv");
	p[337] = GetProcAddress(hL, "glVertex4i");
	p[338] = GetProcAddress(hL, "glVertex4iv");
	p[339] = GetProcAddress(hL, "glVertex4s");
	p[340] = GetProcAddress(hL, "glVertex4sv");
	p[341] = GetProcAddress(hL, "glVertexPointer");
	p[342] = GetProcAddress(hL, "glViewport");
	p[343] = GetProcAddress(hL, "wglChoosePixelFormat");
	p[344] = GetProcAddress(hL, "wglCopyContext");
	p[345] = GetProcAddress(hL, "wglCreateContext");
	p[346] = GetProcAddress(hL, "wglCreateLayerContext");
	p[347] = GetProcAddress(hL, "wglDeleteContext");
	p[348] = GetProcAddress(hL, "wglDescribeLayerPlane");
	p[349] = GetProcAddress(hL, "wglDescribePixelFormat");
	p[350] = GetProcAddress(hL, "wglGetCurrentContext");
	p[351] = GetProcAddress(hL, "wglGetCurrentDC");
	p[352] = GetProcAddress(hL, "wglGetDefaultProcAddress");
	p[353] = GetProcAddress(hL, "wglGetLayerPaletteEntries");
	p[354] = GetProcAddress(hL, "wglGetPixelFormat");
	p[355] = GetProcAddress(hL, "wglGetProcAddress");
	p[356] = GetProcAddress(hL, "wglMakeCurrent");
	p[357] = GetProcAddress(hL, "wglRealizeLayerPalette");
	p[358] = GetProcAddress(hL, "wglSetLayerPaletteEntries");
	p[359] = GetProcAddress(hL, "wglSetPixelFormat");
	p[360] = GetProcAddress(hL, "wglShareLists");
	p[361] = GetProcAddress(hL, "wglSwapBuffers");
	p[362] = GetProcAddress(hL, "wglSwapLayerBuffers");
	p[363] = GetProcAddress(hL, "wglSwapMultipleBuffers");
	p[364] = GetProcAddress(hL, "wglUseFontBitmapsA");
	p[365] = GetProcAddress(hL, "wglUseFontBitmapsW");
	p[366] = GetProcAddress(hL, "wglUseFontOutlinesA");
	p[367] = GetProcAddress(hL, "wglUseFontOutlinesW");
}


// GlmfBeginGlsBlock
extern "C" __declspec(naked) void __stdcall __E__0__()
{
	__asm
	{
		jmp p[0 * 4];
	}
}

// GlmfCloseMetaFile
extern "C" __declspec(naked) void __stdcall __E__1__()
{
	__asm
	{
		jmp p[1 * 4];
	}
}

// GlmfEndGlsBlock
extern "C" __declspec(naked) void __stdcall __E__2__()
{
	__asm
	{
		jmp p[2 * 4];
	}
}

// GlmfEndPlayback
extern "C" __declspec(naked) void __stdcall __E__3__()
{
	__asm
	{
		jmp p[3 * 4];
	}
}

// GlmfInitPlayback
extern "C" __declspec(naked) void __stdcall __E__4__()
{
	__asm
	{
		jmp p[4 * 4];
	}
}

// GlmfPlayGlsRecord
extern "C" __declspec(naked) void __stdcall __E__5__()
{
	__asm
	{
		jmp p[5 * 4];
	}
}

// glAccum
extern "C" __declspec(naked) void __stdcall __E__6__()
{
	__asm
	{
		jmp p[6 * 4];
	}
}

// glAlphaFunc
extern "C" __declspec(naked) void __stdcall __E__7__()
{
	__asm
	{
		jmp p[7 * 4];
	}
}

// glAreTexturesResident
extern "C" __declspec(naked) void __stdcall __E__8__()
{
	__asm
	{
		jmp p[8 * 4];
	}
}

// glArrayElement
extern "C" __declspec(naked) void __stdcall __E__9__()
{
	__asm
	{
		jmp p[9 * 4];
	}
}

// glBegin
extern "C" __declspec(naked) void __stdcall __E__10__()
{
	__asm
	{
		jmp p[10 * 4];
	}
}

// glBindTexture
extern "C" __declspec(naked) void __stdcall __E__11__()
{
	__asm
	{
		jmp p[11 * 4];
	}
}

// glBitmap
extern "C" __declspec(naked) void __stdcall __E__12__()
{
	__asm
	{
		jmp p[12 * 4];
	}
}

// glBlendFunc
extern "C" __declspec(naked) void __stdcall __E__13__()
{
	__asm
	{
		jmp p[13 * 4];
	}
}

// glCallList
extern "C" __declspec(naked) void __stdcall __E__14__()
{
	__asm
	{
		jmp p[14 * 4];
	}
}

// glCallLists
extern "C" __declspec(naked) void __stdcall __E__15__()
{
	__asm
	{
		jmp p[15 * 4];
	}
}

// glClear
extern "C" __declspec(naked) void __stdcall __E__16__()
{
	__asm
	{
		jmp p[16 * 4];
	}
}

// glClearAccum
extern "C" __declspec(naked) void __stdcall __E__17__()
{
	__asm
	{
		jmp p[17 * 4];
	}
}

// glClearColor
extern "C" __declspec(naked) void __stdcall __E__18__()
{
	__asm
	{
		jmp p[18 * 4];
	}
}

// glClearDepth
extern "C" __declspec(naked) void __stdcall __E__19__()
{
	__asm
	{
		jmp p[19 * 4];
	}
}

// glClearIndex
extern "C" __declspec(naked) void __stdcall __E__20__()
{
	__asm
	{
		jmp p[20 * 4];
	}
}

// glClearStencil
extern "C" __declspec(naked) void __stdcall __E__21__()
{
	__asm
	{
		jmp p[21 * 4];
	}
}

// glClipPlane
extern "C" __declspec(naked) void __stdcall __E__22__()
{
	__asm
	{
		jmp p[22 * 4];
	}
}

// glColor3b
extern "C" __declspec(naked) void __stdcall __E__23__()
{
	__asm
	{
		jmp p[23 * 4];
	}
}

// glColor3bv
extern "C" __declspec(naked) void __stdcall __E__24__()
{
	__asm
	{
		jmp p[24 * 4];
	}
}

// glColor3d
extern "C" __declspec(naked) void __stdcall __E__25__()
{
	__asm
	{
		jmp p[25 * 4];
	}
}

// glColor3dv
extern "C" __declspec(naked) void __stdcall __E__26__()
{
	__asm
	{
		jmp p[26 * 4];
	}
}

// glColor3f
extern "C" __declspec(naked) void __stdcall __E__27__()
{
	__asm
	{
		jmp p[27 * 4];
	}
}

// glColor3fv
extern "C" __declspec(naked) void __stdcall __E__28__()
{
	__asm
	{
		jmp p[28 * 4];
	}
}

// glColor3i
extern "C" __declspec(naked) void __stdcall __E__29__()
{
	__asm
	{
		jmp p[29 * 4];
	}
}

// glColor3iv
extern "C" __declspec(naked) void __stdcall __E__30__()
{
	__asm
	{
		jmp p[30 * 4];
	}
}

// glColor3s
extern "C" __declspec(naked) void __stdcall __E__31__()
{
	__asm
	{
		jmp p[31 * 4];
	}
}

// glColor3sv
extern "C" __declspec(naked) void __stdcall __E__32__()
{
	__asm
	{
		jmp p[32 * 4];
	}
}

// glColor3ub
extern "C" __declspec(naked) void __stdcall __E__33__()
{
	__asm
	{
		jmp p[33 * 4];
	}
}

// glColor3ubv
extern "C" __declspec(naked) void __stdcall __E__34__()
{
	__asm
	{
		jmp p[34 * 4];
	}
}

// glColor3ui
extern "C" __declspec(naked) void __stdcall __E__35__()
{
	__asm
	{
		jmp p[35 * 4];
	}
}

// glColor3uiv
extern "C" __declspec(naked) void __stdcall __E__36__()
{
	__asm
	{
		jmp p[36 * 4];
	}
}

// glColor3us
extern "C" __declspec(naked) void __stdcall __E__37__()
{
	__asm
	{
		jmp p[37 * 4];
	}
}

// glColor3usv
extern "C" __declspec(naked) void __stdcall __E__38__()
{
	__asm
	{
		jmp p[38 * 4];
	}
}

// glColor4b
extern "C" __declspec(naked) void __stdcall __E__39__()
{
	__asm
	{
		jmp p[39 * 4];
	}
}

// glColor4bv
extern "C" __declspec(naked) void __stdcall __E__40__()
{
	__asm
	{
		jmp p[40 * 4];
	}
}

// glColor4d
extern "C" __declspec(naked) void __stdcall __E__41__()
{
	__asm
	{
		jmp p[41 * 4];
	}
}

// glColor4dv
extern "C" __declspec(naked) void __stdcall __E__42__()
{
	__asm
	{
		jmp p[42 * 4];
	}
}

// glColor4f
extern "C" __declspec(naked) void __stdcall __E__43__()
{
	__asm
	{
		jmp p[43 * 4];
	}
}

// glColor4fv
extern "C" __declspec(naked) void __stdcall __E__44__()
{
	__asm
	{
		jmp p[44 * 4];
	}
}

// glColor4i
extern "C" __declspec(naked) void __stdcall __E__45__()
{
	__asm
	{
		jmp p[45 * 4];
	}
}

// glColor4iv
extern "C" __declspec(naked) void __stdcall __E__46__()
{
	__asm
	{
		jmp p[46 * 4];
	}
}

// glColor4s
extern "C" __declspec(naked) void __stdcall __E__47__()
{
	__asm
	{
		jmp p[47 * 4];
	}
}

// glColor4sv
extern "C" __declspec(naked) void __stdcall __E__48__()
{
	__asm
	{
		jmp p[48 * 4];
	}
}

// glColor4ub
extern "C" __declspec(naked) void __stdcall __E__49__()
{
	__asm
	{
		jmp p[49 * 4];
	}
}

// glColor4ubv
extern "C" __declspec(naked) void __stdcall __E__50__()
{
	__asm
	{
		jmp p[50 * 4];
	}
}

// glColor4ui
extern "C" __declspec(naked) void __stdcall __E__51__()
{
	__asm
	{
		jmp p[51 * 4];
	}
}

// glColor4uiv
extern "C" __declspec(naked) void __stdcall __E__52__()
{
	__asm
	{
		jmp p[52 * 4];
	}
}

// glColor4us
extern "C" __declspec(naked) void __stdcall __E__53__()
{
	__asm
	{
		jmp p[53 * 4];
	}
}

// glColor4usv
extern "C" __declspec(naked) void __stdcall __E__54__()
{
	__asm
	{
		jmp p[54 * 4];
	}
}

// glColorMask
extern "C" __declspec(naked) void __stdcall __E__55__()
{
	__asm
	{
		jmp p[55 * 4];
	}
}

// glColorMaterial
extern "C" __declspec(naked) void __stdcall __E__56__()
{
	__asm
	{
		jmp p[56 * 4];
	}
}

// glColorPointer
extern "C" __declspec(naked) void __stdcall __E__57__()
{
	__asm
	{
		jmp p[57 * 4];
	}
}

// glCopyPixels
extern "C" __declspec(naked) void __stdcall __E__58__()
{
	__asm
	{
		jmp p[58 * 4];
	}
}

// glCopyTexImage1D
extern "C" __declspec(naked) void __stdcall __E__59__()
{
	__asm
	{
		jmp p[59 * 4];
	}
}

// glCopyTexImage2D
extern "C" __declspec(naked) void __stdcall __E__60__()
{
	__asm
	{
		jmp p[60 * 4];
	}
}

// glCopyTexSubImage1D
extern "C" __declspec(naked) void __stdcall __E__61__()
{
	__asm
	{
		jmp p[61 * 4];
	}
}

// glCopyTexSubImage2D
extern "C" __declspec(naked) void __stdcall __E__62__()
{
	__asm
	{
		jmp p[62 * 4];
	}
}

// glCullFace
extern "C" __declspec(naked) void __stdcall __E__63__()
{
	__asm
	{
		jmp p[63 * 4];
	}
}

// glDebugEntry
extern "C" __declspec(naked) void __stdcall __E__64__()
{
	__asm
	{
		jmp p[64 * 4];
	}
}

// glDeleteLists
extern "C" __declspec(naked) void __stdcall __E__65__()
{
	__asm
	{
		jmp p[65 * 4];
	}
}

// glDeleteTextures
extern "C" __declspec(naked) void __stdcall __E__66__()
{
	__asm
	{
		jmp p[66 * 4];
	}
}

// glDepthFunc
extern "C" __declspec(naked) void __stdcall __E__67__()
{
	__asm
	{
		jmp p[67 * 4];
	}
}

// glDepthMask
extern "C" __declspec(naked) void __stdcall __E__68__()
{
	__asm
	{
		jmp p[68 * 4];
	}
}

// glDepthRange
extern "C" __declspec(naked) void __stdcall __E__69__()
{
	__asm
	{
		jmp p[69 * 4];
	}
}

// glDisable
extern "C" __declspec(naked) void __stdcall __E__70__()
{
	__asm
	{
		jmp p[70 * 4];
	}
}

// glDisableClientState
extern "C" __declspec(naked) void __stdcall __E__71__()
{
	__asm
	{
		jmp p[71 * 4];
	}
}

// glDrawArrays
extern "C" __declspec(naked) void __stdcall __E__72__()
{
	__asm
	{
		jmp p[72 * 4];
	}
}

// glDrawBuffer
extern "C" __declspec(naked) void __stdcall __E__73__()
{
	__asm
	{
		jmp p[73 * 4];
	}
}

// glDrawElements
extern "C" __declspec(naked) void __stdcall __E__74__()
{
	__asm
	{
		jmp p[74 * 4];
	}
}

// glDrawPixels
extern "C" __declspec(naked) void __stdcall __E__75__()
{
	__asm
	{
		jmp p[75 * 4];
	}
}

// glEdgeFlag
extern "C" __declspec(naked) void __stdcall __E__76__()
{
	__asm
	{
		jmp p[76 * 4];
	}
}

// glEdgeFlagPointer
extern "C" __declspec(naked) void __stdcall __E__77__()
{
	__asm
	{
		jmp p[77 * 4];
	}
}

// glEdgeFlagv
extern "C" __declspec(naked) void __stdcall __E__78__()
{
	__asm
	{
		jmp p[78 * 4];
	}
}

// glEnable
extern "C" __declspec(naked) void __stdcall __E__79__()
{
	__asm
	{
		jmp p[79 * 4];
	}
}

// glEnableClientState
extern "C" __declspec(naked) void __stdcall __E__80__()
{
	__asm
	{
		jmp p[80 * 4];
	}
}

// glEnd
extern "C" __declspec(naked) void __stdcall __E__81__()
{
	__asm
	{
		jmp p[81 * 4];
	}
}

// glEndList
extern "C" __declspec(naked) void __stdcall __E__82__()
{
	__asm
	{
		jmp p[82 * 4];
	}
}

// glEvalCoord1d
extern "C" __declspec(naked) void __stdcall __E__83__()
{
	__asm
	{
		jmp p[83 * 4];
	}
}

// glEvalCoord1dv
extern "C" __declspec(naked) void __stdcall __E__84__()
{
	__asm
	{
		jmp p[84 * 4];
	}
}

// glEvalCoord1f
extern "C" __declspec(naked) void __stdcall __E__85__()
{
	__asm
	{
		jmp p[85 * 4];
	}
}

// glEvalCoord1fv
extern "C" __declspec(naked) void __stdcall __E__86__()
{
	__asm
	{
		jmp p[86 * 4];
	}
}

// glEvalCoord2d
extern "C" __declspec(naked) void __stdcall __E__87__()
{
	__asm
	{
		jmp p[87 * 4];
	}
}

// glEvalCoord2dv
extern "C" __declspec(naked) void __stdcall __E__88__()
{
	__asm
	{
		jmp p[88 * 4];
	}
}

// glEvalCoord2f
extern "C" __declspec(naked) void __stdcall __E__89__()
{
	__asm
	{
		jmp p[89 * 4];
	}
}

// glEvalCoord2fv
extern "C" __declspec(naked) void __stdcall __E__90__()
{
	__asm
	{
		jmp p[90 * 4];
	}
}

// glEvalMesh1
extern "C" __declspec(naked) void __stdcall __E__91__()
{
	__asm
	{
		jmp p[91 * 4];
	}
}

// glEvalMesh2
extern "C" __declspec(naked) void __stdcall __E__92__()
{
	__asm
	{
		jmp p[92 * 4];
	}
}

// glEvalPoint1
extern "C" __declspec(naked) void __stdcall __E__93__()
{
	__asm
	{
		jmp p[93 * 4];
	}
}

// glEvalPoint2
extern "C" __declspec(naked) void __stdcall __E__94__()
{
	__asm
	{
		jmp p[94 * 4];
	}
}

// glFeedbackBuffer
extern "C" __declspec(naked) void __stdcall __E__95__()
{
	__asm
	{
		jmp p[95 * 4];
	}
}

// glFinish
extern "C" __declspec(naked) void __stdcall __E__96__()
{
	__asm
	{
		jmp p[96 * 4];
	}
}

// glFlush
extern "C" __declspec(naked) void __stdcall __E__97__()
{
	__asm
	{
		jmp p[97 * 4];
	}
}

// glFogf
extern "C" __declspec(naked) void __stdcall __E__98__()
{
	__asm
	{
		jmp p[98 * 4];
	}
}

// glFogfv
extern "C" __declspec(naked) void __stdcall __E__99__()
{
	__asm
	{
		jmp p[99 * 4];
	}
}

// glFogi
extern "C" __declspec(naked) void __stdcall __E__100__()
{
	__asm
	{
		jmp p[100 * 4];
	}
}

// glFogiv
extern "C" __declspec(naked) void __stdcall __E__101__()
{
	__asm
	{
		jmp p[101 * 4];
	}
}

// glFrontFace
extern "C" __declspec(naked) void __stdcall __E__102__()
{
	__asm
	{
		jmp p[102 * 4];
	}
}

// glFrustum
extern "C" __declspec(naked) void __stdcall __E__103__()
{
	__asm
	{
		jmp p[103 * 4];
	}
}

// glGenLists
extern "C" __declspec(naked) void __stdcall __E__104__()
{
	__asm
	{
		jmp p[104 * 4];
	}
}

// glGenTextures
extern "C" __declspec(naked) void __stdcall __E__105__()
{
	__asm
	{
		jmp p[105 * 4];
	}
}

// glGetBooleanv
extern "C" __declspec(naked) void __stdcall __E__106__()
{
	__asm
	{
		jmp p[106 * 4];
	}
}

// glGetClipPlane
extern "C" __declspec(naked) void __stdcall __E__107__()
{
	__asm
	{
		jmp p[107 * 4];
	}
}

// glGetDoublev
extern "C" __declspec(naked) void __stdcall __E__108__()
{
	__asm
	{
		jmp p[108 * 4];
	}
}

// glGetError
extern "C" __declspec(naked) void __stdcall __E__109__()
{
	__asm
	{
		jmp p[109 * 4];
	}
}

// glGetFloatv
extern "C" __declspec(naked) void __stdcall __E__110__()
{
	__asm
	{
		jmp p[110 * 4];
	}
}

// glGetIntegerv
extern "C" __declspec(naked) void __stdcall __E__111__()
{
	__asm
	{
		jmp p[111 * 4];
	}
}

// glGetLightfv
extern "C" __declspec(naked) void __stdcall __E__112__()
{
	__asm
	{
		jmp p[112 * 4];
	}
}

// glGetLightiv
extern "C" __declspec(naked) void __stdcall __E__113__()
{
	__asm
	{
		jmp p[113 * 4];
	}
}

// glGetMapdv
extern "C" __declspec(naked) void __stdcall __E__114__()
{
	__asm
	{
		jmp p[114 * 4];
	}
}

// glGetMapfv
extern "C" __declspec(naked) void __stdcall __E__115__()
{
	__asm
	{
		jmp p[115 * 4];
	}
}

// glGetMapiv
extern "C" __declspec(naked) void __stdcall __E__116__()
{
	__asm
	{
		jmp p[116 * 4];
	}
}

// glGetMaterialfv
extern "C" __declspec(naked) void __stdcall __E__117__()
{
	__asm
	{
		jmp p[117 * 4];
	}
}

// glGetMaterialiv
extern "C" __declspec(naked) void __stdcall __E__118__()
{
	__asm
	{
		jmp p[118 * 4];
	}
}

// glGetPixelMapfv
extern "C" __declspec(naked) void __stdcall __E__119__()
{
	__asm
	{
		jmp p[119 * 4];
	}
}

// glGetPixelMapuiv
extern "C" __declspec(naked) void __stdcall __E__120__()
{
	__asm
	{
		jmp p[120 * 4];
	}
}

// glGetPixelMapusv
extern "C" __declspec(naked) void __stdcall __E__121__()
{
	__asm
	{
		jmp p[121 * 4];
	}
}

// glGetPointerv
extern "C" __declspec(naked) void __stdcall __E__122__()
{
	__asm
	{
		jmp p[122 * 4];
	}
}

// glGetPolygonStipple
extern "C" __declspec(naked) void __stdcall __E__123__()
{
	__asm
	{
		jmp p[123 * 4];
	}
}

// glGetString
extern "C" __declspec(naked) void __stdcall __E__124__()
{
	__asm
	{
		jmp p[124 * 4];
	}
}

// glGetTexEnvfv
extern "C" __declspec(naked) void __stdcall __E__125__()
{
	__asm
	{
		jmp p[125 * 4];
	}
}

// glGetTexEnviv
extern "C" __declspec(naked) void __stdcall __E__126__()
{
	__asm
	{
		jmp p[126 * 4];
	}
}

// glGetTexGendv
extern "C" __declspec(naked) void __stdcall __E__127__()
{
	__asm
	{
		jmp p[127 * 4];
	}
}

// glGetTexGenfv
extern "C" __declspec(naked) void __stdcall __E__128__()
{
	__asm
	{
		jmp p[128 * 4];
	}
}

// glGetTexGeniv
extern "C" __declspec(naked) void __stdcall __E__129__()
{
	__asm
	{
		jmp p[129 * 4];
	}
}

// glGetTexImage
extern "C" __declspec(naked) void __stdcall __E__130__()
{
	__asm
	{
		jmp p[130 * 4];
	}
}

// glGetTexLevelParameterfv
extern "C" __declspec(naked) void __stdcall __E__131__()
{
	__asm
	{
		jmp p[131 * 4];
	}
}

// glGetTexLevelParameteriv
extern "C" __declspec(naked) void __stdcall __E__132__()
{
	__asm
	{
		jmp p[132 * 4];
	}
}

// glGetTexParameterfv
extern "C" __declspec(naked) void __stdcall __E__133__()
{
	__asm
	{
		jmp p[133 * 4];
	}
}

// glGetTexParameteriv
extern "C" __declspec(naked) void __stdcall __E__134__()
{
	__asm
	{
		jmp p[134 * 4];
	}
}

// glHint
extern "C" __declspec(naked) void __stdcall __E__135__()
{
	__asm
	{
		jmp p[135 * 4];
	}
}

// glIndexMask
extern "C" __declspec(naked) void __stdcall __E__136__()
{
	__asm
	{
		jmp p[136 * 4];
	}
}

// glIndexPointer
extern "C" __declspec(naked) void __stdcall __E__137__()
{
	__asm
	{
		jmp p[137 * 4];
	}
}

// glIndexd
extern "C" __declspec(naked) void __stdcall __E__138__()
{
	__asm
	{
		jmp p[138 * 4];
	}
}

// glIndexdv
extern "C" __declspec(naked) void __stdcall __E__139__()
{
	__asm
	{
		jmp p[139 * 4];
	}
}

// glIndexf
extern "C" __declspec(naked) void __stdcall __E__140__()
{
	__asm
	{
		jmp p[140 * 4];
	}
}

// glIndexfv
extern "C" __declspec(naked) void __stdcall __E__141__()
{
	__asm
	{
		jmp p[141 * 4];
	}
}

// glIndexi
extern "C" __declspec(naked) void __stdcall __E__142__()
{
	__asm
	{
		jmp p[142 * 4];
	}
}

// glIndexiv
extern "C" __declspec(naked) void __stdcall __E__143__()
{
	__asm
	{
		jmp p[143 * 4];
	}
}

// glIndexs
extern "C" __declspec(naked) void __stdcall __E__144__()
{
	__asm
	{
		jmp p[144 * 4];
	}
}

// glIndexsv
extern "C" __declspec(naked) void __stdcall __E__145__()
{
	__asm
	{
		jmp p[145 * 4];
	}
}

// glIndexub
extern "C" __declspec(naked) void __stdcall __E__146__()
{
	__asm
	{
		jmp p[146 * 4];
	}
}

// glIndexubv
extern "C" __declspec(naked) void __stdcall __E__147__()
{
	__asm
	{
		jmp p[147 * 4];
	}
}

// glInitNames
extern "C" __declspec(naked) void __stdcall __E__148__()
{
	__asm
	{
		jmp p[148 * 4];
	}
}

// glInterleavedArrays
extern "C" __declspec(naked) void __stdcall __E__149__()
{
	__asm
	{
		jmp p[149 * 4];
	}
}

// glIsEnabled
extern "C" __declspec(naked) void __stdcall __E__150__()
{
	__asm
	{
		jmp p[150 * 4];
	}
}

// glIsList
extern "C" __declspec(naked) void __stdcall __E__151__()
{
	__asm
	{
		jmp p[151 * 4];
	}
}

// glIsTexture
extern "C" __declspec(naked) void __stdcall __E__152__()
{
	__asm
	{
		jmp p[152 * 4];
	}
}

// glLightModelf
extern "C" __declspec(naked) void __stdcall __E__153__()
{
	__asm
	{
		jmp p[153 * 4];
	}
}

// glLightModelfv
extern "C" __declspec(naked) void __stdcall __E__154__()
{
	__asm
	{
		jmp p[154 * 4];
	}
}

// glLightModeli
extern "C" __declspec(naked) void __stdcall __E__155__()
{
	__asm
	{
		jmp p[155 * 4];
	}
}

// glLightModeliv
extern "C" __declspec(naked) void __stdcall __E__156__()
{
	__asm
	{
		jmp p[156 * 4];
	}
}

// glLightf
extern "C" __declspec(naked) void __stdcall __E__157__()
{
	__asm
	{
		jmp p[157 * 4];
	}
}

// glLightfv
extern "C" __declspec(naked) void __stdcall __E__158__()
{
	__asm
	{
		jmp p[158 * 4];
	}
}

// glLighti
extern "C" __declspec(naked) void __stdcall __E__159__()
{
	__asm
	{
		jmp p[159 * 4];
	}
}

// glLightiv
extern "C" __declspec(naked) void __stdcall __E__160__()
{
	__asm
	{
		jmp p[160 * 4];
	}
}

// glLineStipple
extern "C" __declspec(naked) void __stdcall __E__161__()
{
	__asm
	{
		jmp p[161 * 4];
	}
}

// glLineWidth
extern "C" __declspec(naked) void __stdcall __E__162__()
{
	__asm
	{
		jmp p[162 * 4];
	}
}

// glListBase
extern "C" __declspec(naked) void __stdcall __E__163__()
{
	__asm
	{
		jmp p[163 * 4];
	}
}

// glLoadIdentity
extern "C" __declspec(naked) void __stdcall __E__164__()
{
	__asm
	{
		jmp p[164 * 4];
	}
}

// glLoadMatrixd
extern "C" __declspec(naked) void __stdcall __E__165__()
{
	__asm
	{
		jmp p[165 * 4];
	}
}

// glLoadMatrixf
extern "C" __declspec(naked) void __stdcall __E__166__()
{
	__asm
	{
		jmp p[166 * 4];
	}
}

// glLoadName
extern "C" __declspec(naked) void __stdcall __E__167__()
{
	__asm
	{
		jmp p[167 * 4];
	}
}

// glLogicOp
extern "C" __declspec(naked) void __stdcall __E__168__()
{
	__asm
	{
		jmp p[168 * 4];
	}
}

// glMap1d
extern "C" __declspec(naked) void __stdcall __E__169__()
{
	__asm
	{
		jmp p[169 * 4];
	}
}

// glMap1f
extern "C" __declspec(naked) void __stdcall __E__170__()
{
	__asm
	{
		jmp p[170 * 4];
	}
}

// glMap2d
extern "C" __declspec(naked) void __stdcall __E__171__()
{
	__asm
	{
		jmp p[171 * 4];
	}
}

// glMap2f
extern "C" __declspec(naked) void __stdcall __E__172__()
{
	__asm
	{
		jmp p[172 * 4];
	}
}

// glMapGrid1d
extern "C" __declspec(naked) void __stdcall __E__173__()
{
	__asm
	{
		jmp p[173 * 4];
	}
}

// glMapGrid1f
extern "C" __declspec(naked) void __stdcall __E__174__()
{
	__asm
	{
		jmp p[174 * 4];
	}
}

// glMapGrid2d
extern "C" __declspec(naked) void __stdcall __E__175__()
{
	__asm
	{
		jmp p[175 * 4];
	}
}

// glMapGrid2f
extern "C" __declspec(naked) void __stdcall __E__176__()
{
	__asm
	{
		jmp p[176 * 4];
	}
}

// glMaterialf
extern "C" __declspec(naked) void __stdcall __E__177__()
{
	__asm
	{
		jmp p[177 * 4];
	}
}

// glMaterialfv
extern "C" __declspec(naked) void __stdcall __E__178__()
{
	__asm
	{
		jmp p[178 * 4];
	}
}

// glMateriali
extern "C" __declspec(naked) void __stdcall __E__179__()
{
	__asm
	{
		jmp p[179 * 4];
	}
}

// glMaterialiv
extern "C" __declspec(naked) void __stdcall __E__180__()
{
	__asm
	{
		jmp p[180 * 4];
	}
}

// glMatrixMode
extern "C" __declspec(naked) void __stdcall __E__181__()
{
	__asm
	{
		jmp p[181 * 4];
	}
}

// glMultMatrixd
extern "C" __declspec(naked) void __stdcall __E__182__()
{
	__asm
	{
		jmp p[182 * 4];
	}
}

// glMultMatrixf
extern "C" __declspec(naked) void __stdcall __E__183__()
{
	__asm
	{
		jmp p[183 * 4];
	}
}

// glNewList
extern "C" __declspec(naked) void __stdcall __E__184__()
{
	__asm
	{
		jmp p[184 * 4];
	}
}

// glNormal3b
extern "C" __declspec(naked) void __stdcall __E__185__()
{
	__asm
	{
		jmp p[185 * 4];
	}
}

// glNormal3bv
extern "C" __declspec(naked) void __stdcall __E__186__()
{
	__asm
	{
		jmp p[186 * 4];
	}
}

// glNormal3d
extern "C" __declspec(naked) void __stdcall __E__187__()
{
	__asm
	{
		jmp p[187 * 4];
	}
}

// glNormal3dv
extern "C" __declspec(naked) void __stdcall __E__188__()
{
	__asm
	{
		jmp p[188 * 4];
	}
}

// glNormal3f
extern "C" __declspec(naked) void __stdcall __E__189__()
{
	__asm
	{
		jmp p[189 * 4];
	}
}

// glNormal3fv
extern "C" __declspec(naked) void __stdcall __E__190__()
{
	__asm
	{
		jmp p[190 * 4];
	}
}

// glNormal3i
extern "C" __declspec(naked) void __stdcall __E__191__()
{
	__asm
	{
		jmp p[191 * 4];
	}
}

// glNormal3iv
extern "C" __declspec(naked) void __stdcall __E__192__()
{
	__asm
	{
		jmp p[192 * 4];
	}
}

// glNormal3s
extern "C" __declspec(naked) void __stdcall __E__193__()
{
	__asm
	{
		jmp p[193 * 4];
	}
}

// glNormal3sv
extern "C" __declspec(naked) void __stdcall __E__194__()
{
	__asm
	{
		jmp p[194 * 4];
	}
}

// glNormalPointer
extern "C" __declspec(naked) void __stdcall __E__195__()
{
	__asm
	{
		jmp p[195 * 4];
	}
}

// glOrtho
extern "C" __declspec(naked) void __stdcall __E__196__()
{
	__asm
	{
		jmp p[196 * 4];
	}
}

// glPassThrough
extern "C" __declspec(naked) void __stdcall __E__197__()
{
	__asm
	{
		jmp p[197 * 4];
	}
}

// glPixelMapfv
extern "C" __declspec(naked) void __stdcall __E__198__()
{
	__asm
	{
		jmp p[198 * 4];
	}
}

// glPixelMapuiv
extern "C" __declspec(naked) void __stdcall __E__199__()
{
	__asm
	{
		jmp p[199 * 4];
	}
}

// glPixelMapusv
extern "C" __declspec(naked) void __stdcall __E__200__()
{
	__asm
	{
		jmp p[200 * 4];
	}
}

// glPixelStoref
extern "C" __declspec(naked) void __stdcall __E__201__()
{
	__asm
	{
		jmp p[201 * 4];
	}
}

// glPixelStorei
extern "C" __declspec(naked) void __stdcall __E__202__()
{
	__asm
	{
		jmp p[202 * 4];
	}
}

// glPixelTransferf
extern "C" __declspec(naked) void __stdcall __E__203__()
{
	__asm
	{
		jmp p[203 * 4];
	}
}

// glPixelTransferi
extern "C" __declspec(naked) void __stdcall __E__204__()
{
	__asm
	{
		jmp p[204 * 4];
	}
}

// glPixelZoom
extern "C" __declspec(naked) void __stdcall __E__205__()
{
	__asm
	{
		jmp p[205 * 4];
	}
}

// glPointSize
extern "C" __declspec(naked) void __stdcall __E__206__()
{
	__asm
	{
		jmp p[206 * 4];
	}
}

// glPolygonMode
extern "C" __declspec(naked) void __stdcall __E__207__()
{
	__asm
	{
		jmp p[207 * 4];
	}
}

// glPolygonOffset
extern "C" __declspec(naked) void __stdcall __E__208__()
{
	__asm
	{
		jmp p[208 * 4];
	}
}

// glPolygonStipple
extern "C" __declspec(naked) void __stdcall __E__209__()
{
	__asm
	{
		jmp p[209 * 4];
	}
}

// glPopAttrib
extern "C" __declspec(naked) void __stdcall __E__210__()
{
	__asm
	{
		jmp p[210 * 4];
	}
}

// glPopClientAttrib
extern "C" __declspec(naked) void __stdcall __E__211__()
{
	__asm
	{
		jmp p[211 * 4];
	}
}

// glPopMatrix
extern "C" __declspec(naked) void __stdcall __E__212__()
{
	__asm
	{
		jmp p[212 * 4];
	}
}

// glPopName
extern "C" __declspec(naked) void __stdcall __E__213__()
{
	__asm
	{
		jmp p[213 * 4];
	}
}

// glPrioritizeTextures
extern "C" __declspec(naked) void __stdcall __E__214__()
{
	__asm
	{
		jmp p[214 * 4];
	}
}

// glPushAttrib
extern "C" __declspec(naked) void __stdcall __E__215__()
{
	__asm
	{
		jmp p[215 * 4];
	}
}

// glPushClientAttrib
extern "C" __declspec(naked) void __stdcall __E__216__()
{
	__asm
	{
		jmp p[216 * 4];
	}
}

// glPushMatrix
extern "C" __declspec(naked) void __stdcall __E__217__()
{
	__asm
	{
		jmp p[217 * 4];
	}
}

// glPushName
extern "C" __declspec(naked) void __stdcall __E__218__()
{
	__asm
	{
		jmp p[218 * 4];
	}
}

// glRasterPos2d
extern "C" __declspec(naked) void __stdcall __E__219__()
{
	__asm
	{
		jmp p[219 * 4];
	}
}

// glRasterPos2dv
extern "C" __declspec(naked) void __stdcall __E__220__()
{
	__asm
	{
		jmp p[220 * 4];
	}
}

// glRasterPos2f
extern "C" __declspec(naked) void __stdcall __E__221__()
{
	__asm
	{
		jmp p[221 * 4];
	}
}

// glRasterPos2fv
extern "C" __declspec(naked) void __stdcall __E__222__()
{
	__asm
	{
		jmp p[222 * 4];
	}
}

// glRasterPos2i
extern "C" __declspec(naked) void __stdcall __E__223__()
{
	__asm
	{
		jmp p[223 * 4];
	}
}

// glRasterPos2iv
extern "C" __declspec(naked) void __stdcall __E__224__()
{
	__asm
	{
		jmp p[224 * 4];
	}
}

// glRasterPos2s
extern "C" __declspec(naked) void __stdcall __E__225__()
{
	__asm
	{
		jmp p[225 * 4];
	}
}

// glRasterPos2sv
extern "C" __declspec(naked) void __stdcall __E__226__()
{
	__asm
	{
		jmp p[226 * 4];
	}
}

// glRasterPos3d
extern "C" __declspec(naked) void __stdcall __E__227__()
{
	__asm
	{
		jmp p[227 * 4];
	}
}

// glRasterPos3dv
extern "C" __declspec(naked) void __stdcall __E__228__()
{
	__asm
	{
		jmp p[228 * 4];
	}
}

// glRasterPos3f
extern "C" __declspec(naked) void __stdcall __E__229__()
{
	__asm
	{
		jmp p[229 * 4];
	}
}

// glRasterPos3fv
extern "C" __declspec(naked) void __stdcall __E__230__()
{
	__asm
	{
		jmp p[230 * 4];
	}
}

// glRasterPos3i
extern "C" __declspec(naked) void __stdcall __E__231__()
{
	__asm
	{
		jmp p[231 * 4];
	}
}

// glRasterPos3iv
extern "C" __declspec(naked) void __stdcall __E__232__()
{
	__asm
	{
		jmp p[232 * 4];
	}
}

// glRasterPos3s
extern "C" __declspec(naked) void __stdcall __E__233__()
{
	__asm
	{
		jmp p[233 * 4];
	}
}

// glRasterPos3sv
extern "C" __declspec(naked) void __stdcall __E__234__()
{
	__asm
	{
		jmp p[234 * 4];
	}
}

// glRasterPos4d
extern "C" __declspec(naked) void __stdcall __E__235__()
{
	__asm
	{
		jmp p[235 * 4];
	}
}

// glRasterPos4dv
extern "C" __declspec(naked) void __stdcall __E__236__()
{
	__asm
	{
		jmp p[236 * 4];
	}
}

// glRasterPos4f
extern "C" __declspec(naked) void __stdcall __E__237__()
{
	__asm
	{
		jmp p[237 * 4];
	}
}

// glRasterPos4fv
extern "C" __declspec(naked) void __stdcall __E__238__()
{
	__asm
	{
		jmp p[238 * 4];
	}
}

// glRasterPos4i
extern "C" __declspec(naked) void __stdcall __E__239__()
{
	__asm
	{
		jmp p[239 * 4];
	}
}

// glRasterPos4iv
extern "C" __declspec(naked) void __stdcall __E__240__()
{
	__asm
	{
		jmp p[240 * 4];
	}
}

// glRasterPos4s
extern "C" __declspec(naked) void __stdcall __E__241__()
{
	__asm
	{
		jmp p[241 * 4];
	}
}

// glRasterPos4sv
extern "C" __declspec(naked) void __stdcall __E__242__()
{
	__asm
	{
		jmp p[242 * 4];
	}
}

// glReadBuffer
extern "C" __declspec(naked) void __stdcall __E__243__()
{
	__asm
	{
		jmp p[243 * 4];
	}
}

// glReadPixels
extern "C" __declspec(naked) void __stdcall __E__244__()
{
	__asm
	{
		jmp p[244 * 4];
	}
}

// glRectd
extern "C" __declspec(naked) void __stdcall __E__245__()
{
	__asm
	{
		jmp p[245 * 4];
	}
}

// glRectdv
extern "C" __declspec(naked) void __stdcall __E__246__()
{
	__asm
	{
		jmp p[246 * 4];
	}
}

// glRectf
extern "C" __declspec(naked) void __stdcall __E__247__()
{
	__asm
	{
		jmp p[247 * 4];
	}
}

// glRectfv
extern "C" __declspec(naked) void __stdcall __E__248__()
{
	__asm
	{
		jmp p[248 * 4];
	}
}

// glRecti
extern "C" __declspec(naked) void __stdcall __E__249__()
{
	__asm
	{
		jmp p[249 * 4];
	}
}

// glRectiv
extern "C" __declspec(naked) void __stdcall __E__250__()
{
	__asm
	{
		jmp p[250 * 4];
	}
}

// glRects
extern "C" __declspec(naked) void __stdcall __E__251__()
{
	__asm
	{
		jmp p[251 * 4];
	}
}

// glRectsv
extern "C" __declspec(naked) void __stdcall __E__252__()
{
	__asm
	{
		jmp p[252 * 4];
	}
}

// glRenderMode
extern "C" __declspec(naked) void __stdcall __E__253__()
{
	__asm
	{
		jmp p[253 * 4];
	}
}

// glRotated
extern "C" __declspec(naked) void __stdcall __E__254__()
{
	__asm
	{
		jmp p[254 * 4];
	}
}

// glRotatef
extern "C" __declspec(naked) void __stdcall __E__255__()
{
	__asm
	{
		jmp p[255 * 4];
	}
}

// glScaled
extern "C" __declspec(naked) void __stdcall __E__256__()
{
	__asm
	{
		jmp p[256 * 4];
	}
}

// glScalef
extern "C" __declspec(naked) void __stdcall __E__257__()
{
	__asm
	{
		jmp p[257 * 4];
	}
}

// glScissor
extern "C" __declspec(naked) void __stdcall __E__258__()
{
	__asm
	{
		jmp p[258 * 4];
	}
}

// glSelectBuffer
extern "C" __declspec(naked) void __stdcall __E__259__()
{
	__asm
	{
		jmp p[259 * 4];
	}
}

// glShadeModel
extern "C" __declspec(naked) void __stdcall __E__260__()
{
	__asm
	{
		jmp p[260 * 4];
	}
}

// glStencilFunc
extern "C" __declspec(naked) void __stdcall __E__261__()
{
	__asm
	{
		jmp p[261 * 4];
	}
}

// glStencilMask
extern "C" __declspec(naked) void __stdcall __E__262__()
{
	__asm
	{
		jmp p[262 * 4];
	}
}

// glStencilOp
extern "C" __declspec(naked) void __stdcall __E__263__()
{
	__asm
	{
		jmp p[263 * 4];
	}
}

// glTexCoord1d
extern "C" __declspec(naked) void __stdcall __E__264__()
{
	__asm
	{
		jmp p[264 * 4];
	}
}

// glTexCoord1dv
extern "C" __declspec(naked) void __stdcall __E__265__()
{
	__asm
	{
		jmp p[265 * 4];
	}
}

// glTexCoord1f
extern "C" __declspec(naked) void __stdcall __E__266__()
{
	__asm
	{
		jmp p[266 * 4];
	}
}

// glTexCoord1fv
extern "C" __declspec(naked) void __stdcall __E__267__()
{
	__asm
	{
		jmp p[267 * 4];
	}
}

// glTexCoord1i
extern "C" __declspec(naked) void __stdcall __E__268__()
{
	__asm
	{
		jmp p[268 * 4];
	}
}

// glTexCoord1iv
extern "C" __declspec(naked) void __stdcall __E__269__()
{
	__asm
	{
		jmp p[269 * 4];
	}
}

// glTexCoord1s
extern "C" __declspec(naked) void __stdcall __E__270__()
{
	__asm
	{
		jmp p[270 * 4];
	}
}

// glTexCoord1sv
extern "C" __declspec(naked) void __stdcall __E__271__()
{
	__asm
	{
		jmp p[271 * 4];
	}
}

// glTexCoord2d
extern "C" __declspec(naked) void __stdcall __E__272__()
{
	__asm
	{
		jmp p[272 * 4];
	}
}

// glTexCoord2dv
extern "C" __declspec(naked) void __stdcall __E__273__()
{
	__asm
	{
		jmp p[273 * 4];
	}
}

// glTexCoord2f
extern "C" __declspec(naked) void __stdcall __E__274__()
{
	__asm
	{
		jmp p[274 * 4];
	}
}

// glTexCoord2fv
extern "C" __declspec(naked) void __stdcall __E__275__()
{
	__asm
	{
		jmp p[275 * 4];
	}
}

// glTexCoord2i
extern "C" __declspec(naked) void __stdcall __E__276__()
{
	__asm
	{
		jmp p[276 * 4];
	}
}

// glTexCoord2iv
extern "C" __declspec(naked) void __stdcall __E__277__()
{
	__asm
	{
		jmp p[277 * 4];
	}
}

// glTexCoord2s
extern "C" __declspec(naked) void __stdcall __E__278__()
{
	__asm
	{
		jmp p[278 * 4];
	}
}

// glTexCoord2sv
extern "C" __declspec(naked) void __stdcall __E__279__()
{
	__asm
	{
		jmp p[279 * 4];
	}
}

// glTexCoord3d
extern "C" __declspec(naked) void __stdcall __E__280__()
{
	__asm
	{
		jmp p[280 * 4];
	}
}

// glTexCoord3dv
extern "C" __declspec(naked) void __stdcall __E__281__()
{
	__asm
	{
		jmp p[281 * 4];
	}
}

// glTexCoord3f
extern "C" __declspec(naked) void __stdcall __E__282__()
{
	__asm
	{
		jmp p[282 * 4];
	}
}

// glTexCoord3fv
extern "C" __declspec(naked) void __stdcall __E__283__()
{
	__asm
	{
		jmp p[283 * 4];
	}
}

// glTexCoord3i
extern "C" __declspec(naked) void __stdcall __E__284__()
{
	__asm
	{
		jmp p[284 * 4];
	}
}

// glTexCoord3iv
extern "C" __declspec(naked) void __stdcall __E__285__()
{
	__asm
	{
		jmp p[285 * 4];
	}
}

// glTexCoord3s
extern "C" __declspec(naked) void __stdcall __E__286__()
{
	__asm
	{
		jmp p[286 * 4];
	}
}

// glTexCoord3sv
extern "C" __declspec(naked) void __stdcall __E__287__()
{
	__asm
	{
		jmp p[287 * 4];
	}
}

// glTexCoord4d
extern "C" __declspec(naked) void __stdcall __E__288__()
{
	__asm
	{
		jmp p[288 * 4];
	}
}

// glTexCoord4dv
extern "C" __declspec(naked) void __stdcall __E__289__()
{
	__asm
	{
		jmp p[289 * 4];
	}
}

// glTexCoord4f
extern "C" __declspec(naked) void __stdcall __E__290__()
{
	__asm
	{
		jmp p[290 * 4];
	}
}

// glTexCoord4fv
extern "C" __declspec(naked) void __stdcall __E__291__()
{
	__asm
	{
		jmp p[291 * 4];
	}
}

// glTexCoord4i
extern "C" __declspec(naked) void __stdcall __E__292__()
{
	__asm
	{
		jmp p[292 * 4];
	}
}

// glTexCoord4iv
extern "C" __declspec(naked) void __stdcall __E__293__()
{
	__asm
	{
		jmp p[293 * 4];
	}
}

// glTexCoord4s
extern "C" __declspec(naked) void __stdcall __E__294__()
{
	__asm
	{
		jmp p[294 * 4];
	}
}

// glTexCoord4sv
extern "C" __declspec(naked) void __stdcall __E__295__()
{
	__asm
	{
		jmp p[295 * 4];
	}
}

// glTexCoordPointer
extern "C" __declspec(naked) void __stdcall __E__296__()
{
	__asm
	{
		jmp p[296 * 4];
	}
}

// glTexEnvf
extern "C" __declspec(naked) void __stdcall __E__297__()
{
	__asm
	{
		jmp p[297 * 4];
	}
}

// glTexEnvfv
extern "C" __declspec(naked) void __stdcall __E__298__()
{
	__asm
	{
		jmp p[298 * 4];
	}
}

// glTexEnvi
extern "C" __declspec(naked) void __stdcall __E__299__()
{
	__asm
	{
		jmp p[299 * 4];
	}
}

// glTexEnviv
extern "C" __declspec(naked) void __stdcall __E__300__()
{
	__asm
	{
		jmp p[300 * 4];
	}
}

// glTexGend
extern "C" __declspec(naked) void __stdcall __E__301__()
{
	__asm
	{
		jmp p[301 * 4];
	}
}

// glTexGendv
extern "C" __declspec(naked) void __stdcall __E__302__()
{
	__asm
	{
		jmp p[302 * 4];
	}
}

// glTexGenf
extern "C" __declspec(naked) void __stdcall __E__303__()
{
	__asm
	{
		jmp p[303 * 4];
	}
}

// glTexGenfv
extern "C" __declspec(naked) void __stdcall __E__304__()
{
	__asm
	{
		jmp p[304 * 4];
	}
}

// glTexGeni
extern "C" __declspec(naked) void __stdcall __E__305__()
{
	__asm
	{
		jmp p[305 * 4];
	}
}

// glTexGeniv
extern "C" __declspec(naked) void __stdcall __E__306__()
{
	__asm
	{
		jmp p[306 * 4];
	}
}

// glTexImage1D
extern "C" __declspec(naked) void __stdcall __E__307__()
{
	__asm
	{
		jmp p[307 * 4];
	}
}

// glTexImage2D
extern "C" __declspec(naked) void __stdcall __E__308__()
{
	__asm
	{
		jmp p[308 * 4];
	}
}

// glTexParameterf
extern "C" __declspec(naked) void __stdcall __E__309__()
{
	__asm
	{
		jmp p[309 * 4];
	}
}

// glTexParameterfv
extern "C" __declspec(naked) void __stdcall __E__310__()
{
	__asm
	{
		jmp p[310 * 4];
	}
}

// glTexParameteri
extern "C" __declspec(naked) void __stdcall __E__311__()
{
	__asm
	{
		jmp p[311 * 4];
	}
}

// glTexParameteriv
extern "C" __declspec(naked) void __stdcall __E__312__()
{
	__asm
	{
		jmp p[312 * 4];
	}
}

// glTexSubImage1D
extern "C" __declspec(naked) void __stdcall __E__313__()
{
	__asm
	{
		jmp p[313 * 4];
	}
}

// glTexSubImage2D
extern "C" __declspec(naked) void __stdcall __E__314__()
{
	__asm
	{
		jmp p[314 * 4];
	}
}

// glTranslated
extern "C" __declspec(naked) void __stdcall __E__315__()
{
	__asm
	{
		jmp p[315 * 4];
	}
}

// glTranslatef
extern "C" __declspec(naked) void __stdcall __E__316__()
{
	__asm
	{
		jmp p[316 * 4];
	}
}

// glVertex2d
extern "C" __declspec(naked) void __stdcall __E__317__()
{
	__asm
	{
		jmp p[317 * 4];
	}
}

// glVertex2dv
extern "C" __declspec(naked) void __stdcall __E__318__()
{
	__asm
	{
		jmp p[318 * 4];
	}
}

// glVertex2f
extern "C" __declspec(naked) void __stdcall __E__319__()
{
	__asm
	{
		jmp p[319 * 4];
	}
}

// glVertex2fv
extern "C" __declspec(naked) void __stdcall __E__320__()
{
	__asm
	{
		jmp p[320 * 4];
	}
}

// glVertex2i
extern "C" __declspec(naked) void __stdcall __E__321__()
{
	__asm
	{
		jmp p[321 * 4];
	}
}

// glVertex2iv
extern "C" __declspec(naked) void __stdcall __E__322__()
{
	__asm
	{
		jmp p[322 * 4];
	}
}

// glVertex2s
extern "C" __declspec(naked) void __stdcall __E__323__()
{
	__asm
	{
		jmp p[323 * 4];
	}
}

// glVertex2sv
extern "C" __declspec(naked) void __stdcall __E__324__()
{
	__asm
	{
		jmp p[324 * 4];
	}
}

// glVertex3d
extern "C" __declspec(naked) void __stdcall __E__325__()
{
	__asm
	{
		jmp p[325 * 4];
	}
}

// glVertex3dv
extern "C" __declspec(naked) void __stdcall __E__326__()
{
	__asm
	{
		jmp p[326 * 4];
	}
}

// glVertex3f
extern "C" __declspec(naked) void __stdcall __E__327__()
{
	__asm
	{
		jmp p[327 * 4];
	}
}

// glVertex3fv
extern "C" __declspec(naked) void __stdcall __E__328__()
{
	__asm
	{
		jmp p[328 * 4];
	}
}

// glVertex3i
extern "C" __declspec(naked) void __stdcall __E__329__()
{
	__asm
	{
		jmp p[329 * 4];
	}
}

// glVertex3iv
extern "C" __declspec(naked) void __stdcall __E__330__()
{
	__asm
	{
		jmp p[330 * 4];
	}
}

// glVertex3s
extern "C" __declspec(naked) void __stdcall __E__331__()
{
	__asm
	{
		jmp p[331 * 4];
	}
}

// glVertex3sv
extern "C" __declspec(naked) void __stdcall __E__332__()
{
	__asm
	{
		jmp p[332 * 4];
	}
}

// glVertex4d
extern "C" __declspec(naked) void __stdcall __E__333__()
{
	__asm
	{
		jmp p[333 * 4];
	}
}

// glVertex4dv
extern "C" __declspec(naked) void __stdcall __E__334__()
{
	__asm
	{
		jmp p[334 * 4];
	}
}

// glVertex4f
extern "C" __declspec(naked) void __stdcall __E__335__()
{
	__asm
	{
		jmp p[335 * 4];
	}
}

// glVertex4fv
extern "C" __declspec(naked) void __stdcall __E__336__()
{
	__asm
	{
		jmp p[336 * 4];
	}
}

// glVertex4i
extern "C" __declspec(naked) void __stdcall __E__337__()
{
	__asm
	{
		jmp p[337 * 4];
	}
}

// glVertex4iv
extern "C" __declspec(naked) void __stdcall __E__338__()
{
	__asm
	{
		jmp p[338 * 4];
	}
}

// glVertex4s
extern "C" __declspec(naked) void __stdcall __E__339__()
{
	__asm
	{
		jmp p[339 * 4];
	}
}

// glVertex4sv
extern "C" __declspec(naked) void __stdcall __E__340__()
{
	__asm
	{
		jmp p[340 * 4];
	}
}

// glVertexPointer
extern "C" __declspec(naked) void __stdcall __E__341__()
{
	__asm
	{
		jmp p[341 * 4];
	}
}

// glViewport
extern "C" __declspec(naked) void __stdcall __E__342__()
{
	INIT_GL  // needed for passing/still fullscreen mode
		__asm
	{
		jmp p[342 * 4];
	}
}

// wglChoosePixelFormat
extern "C" __declspec(naked) void __stdcall __E__343__()
{
	INIT_GL
		__asm
	{
		jmp p[343 * 4];
	}
}

// wglCopyContext
extern "C" __declspec(naked) void __stdcall __E__344__()
{
	INIT_GL
		__asm
	{
		jmp p[344 * 4];
	}
}

// wglCreateContext
extern "C" __declspec(naked) void __stdcall __E__345__()
{
	INIT_GL
		__asm
	{
		jmp p[345 * 4];
	}
}

// wglCreateLayerContext
extern "C" __declspec(naked) void __stdcall __E__346__()
{
	INIT_GL
		__asm
	{
		jmp p[346 * 4];
	}
}

// wglDeleteContext
extern "C" __declspec(naked) void __stdcall __E__347__()
{
	INIT_GL
		__asm
	{
		jmp p[347 * 4];
	}
}

// wglDescribeLayerPlane
extern "C" __declspec(naked) void __stdcall __E__348__()
{
	INIT_GL
		__asm
	{
		jmp p[348 * 4];
	}
}

// wglDescribePixelFormat
extern "C" __declspec(naked) void __stdcall __E__349__()
{
	INIT_GL
		__asm
	{
		jmp p[349 * 4];
	}
}

// wglGetCurrentContext
extern "C" __declspec(naked) void __stdcall __E__350__()
{
	INIT_GL
		__asm
	{
		jmp p[350 * 4];
	}
}

// wglGetCurrentDC
extern "C" __declspec(naked) void __stdcall __E__351__()
{
	INIT_GL
		__asm
	{
		jmp p[351 * 4];
	}
}

// wglGetDefaultProcAddress
extern "C" __declspec(naked) void __stdcall __E__352__()
{
	INIT_GL
		__asm
	{
		jmp p[352 * 4];
	}
}

// wglGetLayerPaletteEntries
extern "C" __declspec(naked) void __stdcall __E__353__()
{
	INIT_GL
		__asm
	{
		jmp p[353 * 4];
	}
}

// wglGetPixelFormat
extern "C" __declspec(naked) void __stdcall __E__354__()
{
	INIT_GL
		__asm
	{
		jmp p[354 * 4];
	}
}

// wglGetProcAddress
/*extern "C" __declspec(naked) void __stdcall __E__355__()
	{INIT_GL
	__asm
	{
	jmp p[355*4];
	}
	}*/

extern "C" int __stdcall __E__355__(char* name)
{
	typedef int(__stdcall *pS)(char* name);
	pS pps = (pS)p[355];
	int rv = pps(name);
	if ((strcmp(name, "glShaderSource") == 0) || (strcmp(name, "glShaderSourceARB") == 0))
	{
		orig_glShaderSource = (PFNGLSHADERSOURCEPROC)rv;
		return (int)my_glShaderSource;
	}
	else if ((strcmp(name, "glCreateShaderProgramv") == 0))
	{
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)pps("glGetProgramiv");
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)pps("glGetProgramInfoLog");

		orig_glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC)rv;
		return (int)my_glCreateShaderProgramv;
	}
	else if ((strcmp(name, "glCompileShader") == 0) || (strcmp(name, "glCompileShaderARB") == 0))
	{
		glGetShaderiv = (PFNGLGETSHADERIVPROC)pps("glGetShaderiv");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)pps("glGetShaderInfoLog");
		glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)pps("glGetShaderSource");

		orig_glCompileShader = (PFNGLCOMPILESHADERPROC)rv;
		return (int)my_glCompileShader;
	}
	else if ((strcmp(name, "glLinkProgram") == 0) || (strcmp(name, "glLinkProgramARB") == 0))
	{
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)pps("glGetProgramiv");
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)pps("glGetProgramInfoLog");

		orig_glLinkProgram = (PFNGLLINKPROGRAMPROC)rv;
		return (int)my_glLinkProgram;
	}
	return rv;
}


// wglMakeCurrent
extern "C" __declspec(naked) void __stdcall __E__356__()
{
	INIT_GL
		__asm
	{
		jmp p[356 * 4];
	}
}

// wglRealizeLayerPalette
extern "C" __declspec(naked) void __stdcall __E__357__()
{
	__asm
	{
		jmp p[357 * 4];
	}
}

// wglSetLayerPaletteEntries
extern "C" __declspec(naked) void __stdcall __E__358__()
{
	__asm
	{
		jmp p[358 * 4];
	}
}

// wglSetPixelFormat
extern "C" __declspec(naked) void __stdcall __E__359__()
{
	INIT_GL
		__asm
	{
		jmp p[359 * 4];
	}
}

// wglShareLists
extern "C" __declspec(naked) void __stdcall __E__360__()
{
	INIT_GL
		__asm
	{
		jmp p[360 * 4];
	}
}

// wglSwapBuffers
extern "C" __declspec(naked) void __stdcall __E__361__()
{
	INIT_GL
		__asm
	{
		jmp p[361 * 4];
	}
}

// wglSwapLayerBuffers
extern "C" __declspec(naked) void __stdcall __E__362__()
{
	INIT_GL
		__asm
	{
		jmp p[362 * 4];
	}
}

// wglSwapMultipleBuffers
extern "C" __declspec(naked) void __stdcall __E__363__()
{
	INIT_GL
		__asm
	{
		jmp p[363 * 4];
	}
}

// wglUseFontBitmapsA
extern "C" __declspec(naked) void __stdcall __E__364__()
{
	INIT_GL
		__asm
	{
		jmp p[364 * 4];
	}
}

// wglUseFontBitmapsW
extern "C" __declspec(naked) void __stdcall __E__365__()
{
	INIT_GL
		__asm
	{
		jmp p[365 * 4];
	}
}

// wglUseFontOutlinesA
extern "C" __declspec(naked) void __stdcall __E__366__()
{
	INIT_GL
		__asm
	{
		jmp p[366 * 4];
	}
}

// wglUseFontOutlinesW
extern "C" __declspec(naked) void __stdcall __E__367__()
{
	INIT_GL
		__asm
	{
		jmp p[367 * 4];
	}
}

