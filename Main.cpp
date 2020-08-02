/*
 *          Copyright 2020, Vitali Baumtrok.
 * Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE or copy at
 *        http://www.boost.org/LICENSE_1_0.txt)
 */

#include "stdafx.h"
#include <gl/GL.h>

 /* copied from wglext.h */
typedef BOOL(WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
#define WGL_SAMPLE_BUFFERS_ARB            0x2041
#define WGL_SAMPLES_ARB                   0x2042
#define WGL_DRAW_TO_WINDOW_ARB            0x2001
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_DOUBLE_BUFFER_ARB             0x2011
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_TYPE_RGBA_ARB                 0x202B
#define WGL_ACCELERATION_ARB              0x2003
#define WGL_FULL_ACCELERATION_ARB         0x2027
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_ALPHA_BITS_ARB                0x201B
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001

/* copied from glcorearb.h */
#define APIENTRYP APIENTRY *
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_ARRAY_BUFFER                   0x8892
#define GL_STATIC_DRAW                    0x88E4
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
typedef GLuint(APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef GLuint(APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLint(APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, GLvoid **pointer);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);

/* copied from gl_core.h */
PFNGLCREATESHADERPROC                           glCreateShader;
PFNGLSHADERSOURCEPROC                           glShaderSource;
PFNGLCOMPILESHADERPROC                          glCompileShader;
PFNGLGETSHADERIVPROC                            glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC                       glGetShaderInfoLog;
PFNGLCREATEPROGRAMPROC                          glCreateProgram;
PFNGLATTACHSHADERPROC                           glAttachShader;
PFNGLLINKPROGRAMPROC                            glLinkProgram;
PFNGLVALIDATEPROGRAMPROC                        glValidateProgram;
PFNGLGETPROGRAMIVPROC                           glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC                      glGetProgramInfoLog;
PFNGLGENBUFFERSPROC                             glGenBuffers;
PFNGLGENVERTEXARRAYSPROC                        glGenVertexArrays;
PFNGLGETATTRIBLOCATIONPROC                      glGetAttribLocation;
PFNGLBINDVERTEXARRAYPROC                        glBindVertexArray;
PFNGLENABLEVERTEXATTRIBARRAYPROC                glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC                    glVertexAttribPointer;
PFNGLBINDBUFFERPROC                             glBindBuffer;
PFNGLBUFFERDATAPROC                             glBufferData;
PFNGLGETVERTEXATTRIBPOINTERVPROC                glGetVertexAttribPointerv;
PFNGLUSEPROGRAMPROC                             glUseProgram;
PFNGLDELETEVERTEXARRAYSPROC                     glDeleteVertexArrays;
PFNGLDELETEBUFFERSPROC                          glDeleteBuffers;
PFNGLDELETEPROGRAMPROC                          glDeleteProgram;
PFNGLDELETESHADERPROC                           glDeleteShader;

const char *const vertex_shader = "#version 130\n\nin vec3 positionIn;\nin vec4 colorIn;\nout vec4 fragementColor;\n\nuniform mat4 projection = mat4(1.0);\nuniform mat4 model = mat4(1.0);\n\nvoid main() {\n\tgl_Position = projection * model * vec4(positionIn, 1.0f);\n\tfragementColor = colorIn;\n}";
const char *const fragment_shader = "#version 130\n\nin vec4 fragementColor;\nout vec4 color;\n\nvoid main() {\n\tcolor = fragementColor;\n}";

GLuint fragmentShaderID;
GLuint vertexShaderID;
GLuint programID;
GLuint vbo;
GLuint vao;

HDC     hDC;				/* device context */
HGLRC   hRC;				/* render context (opengl context) */
HWND    hWnd;				/* window */

LPCWSTR szWindowClass = L"OpenGL";
LPCWSTR szTitle = L"Example";

void DrawGraphics()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	SwapBuffers(hDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		DrawGraphics();
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 27: /* ESC key */
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteProgram(programID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	/* Initialize bits to 0. */
	memset(&wcex, 0, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc; // event handler
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	DWORD  dwStyle;
	int    x = 0;
	int    y = 0;
	int    width = 256;
	int    height = 256;

	dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	hWnd = CreateWindowW(szWindowClass, szTitle, dwStyle, x, y, width, height, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CreateRenderContext(HINSTANCE hInstance)
{
	/* ------------------------------------------- */
	/*             create fake context             */
	/* ------------------------------------------- */

	HWND                  hFakeWnd;
	HDC                   hFakeDC;
	PIXELFORMATDESCRIPTOR fakePFD;
	int                   fakePixelFormat;
	HGLRC                 hFakeRC;

	PFNWGLCHOOSEPIXELFORMATARBPROC    wglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

	hFakeWnd = CreateWindowW(szWindowClass, L"Fake Window", WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, 1, 1, nullptr, nullptr, hInstance, nullptr);
	if (!hFakeWnd)
	{
		MessageBox(NULL, L"CreateWindow() failed: Can not create a fake window.", L"Error", MB_OK);
		return FALSE;
	}
	hFakeDC = GetDC(hFakeWnd);

	/* Initialize bits to 0. */
	memset(&fakePFD, 0, sizeof(PIXELFORMATDESCRIPTOR));
	fakePFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	fakePFD.nVersion = 1;
	fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	fakePFD.iPixelType = PFD_TYPE_RGBA;
	fakePFD.cColorBits = 32;
	fakePFD.cAlphaBits = 8;
	fakePFD.cDepthBits = 24;
	fakePixelFormat = ChoosePixelFormat(hFakeDC, &fakePFD);
	if (!fakePixelFormat)
	{
		MessageBox(NULL, L"ChoosePixelFormat() failed: Can not find a suitable fake pixel format.", L"Error", MB_OK);
		return FALSE;
	}
	if (!SetPixelFormat(hFakeDC, fakePixelFormat, &fakePFD))
	{
		MessageBox(NULL, L"SetPixelFormat() failed: Can not set fake pixel format.", L"Error", MB_OK);
		return FALSE;
	}
	hFakeRC = wglCreateContext(hFakeDC);
	wglMakeCurrent(hFakeDC, hFakeRC);

	wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
	if (!wglChoosePixelFormatARB)
	{
		MessageBox(NULL, L"wglGetProcAddress() failed: Can not find wglChoosePixelFormatARB.", L"Error", MB_OK);
		return FALSE;
	}
	wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
	if (!wglCreateContextAttribsARB)
	{
		MessageBox(NULL, L"wglGetProcAddress() failed: Can not find wglCreateContextAttribsARB.", L"Error", MB_OK);
		return FALSE;
	}

	/* ------------------------------------------- */
	/*             create true context             */
	/* ------------------------------------------- */

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	int                   pixelFormat;
	BOOL                  status;
	UINT                  numFormats;
	const int pixelAttribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, 4,
		0
	};
	int  contextAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 0,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	hDC = GetDC(hWnd);
	status = wglChoosePixelFormatARB(hDC, pixelAttribs, NULL, 1, &pixelFormat, &numFormats);

	if (status == FALSE || numFormats == 0)
	{
		MessageBox(NULL, L"wglChoosePixelFormatARB() failed: Can not find a suitable pixel format.", L"Error", MB_OK);
		return FALSE;
	}
	/* Initialize bits to 0. */
	memset(&pixelFormatDescriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDescriptor);

	if (SetPixelFormat(hDC, pixelFormat, &pixelFormatDescriptor) == FALSE)
	{
		MessageBox(NULL, L"SetPixelFormat() failed: Can not set format specified.", L"Error", MB_OK);
		return FALSE;
	}
	hRC = wglCreateContextAttribsARB(hDC, 0, contextAttributes);

	/* ------------------------------------------- */
	/*            clean up fake context            */
	/* ------------------------------------------- */

	wglMakeCurrent(hFakeDC, NULL);
	wglDeleteContext(hFakeRC);
	ReleaseDC(hFakeWnd, hFakeDC);
	DestroyWindow(hFakeWnd);

	return (hRC != NULL);
}

void InitGLFunctions()
{
	glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"));
	glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(wglGetProcAddress("glShaderSource"));
	glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(wglGetProcAddress("glCompileShader"));
	glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(wglGetProcAddress("glGetShaderiv"));
	glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(wglGetProcAddress("glGetShaderInfoLog"));
	glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(wglGetProcAddress("glCreateProgram"));
	glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(wglGetProcAddress("glAttachShader"));
	glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(wglGetProcAddress("glLinkProgram"));
	glValidateProgram = reinterpret_cast<PFNGLVALIDATEPROGRAMPROC>(wglGetProcAddress("glValidateProgram"));
	glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(wglGetProcAddress("glGetProgramiv"));
	glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(wglGetProcAddress("glGenBuffers"));
	glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(wglGetProcAddress("glGenVertexArrays"));
	glGetAttribLocation = reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>(wglGetProcAddress("glGetAttribLocation"));
	glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));
	glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(wglGetProcAddress("glEnableVertexAttribArray"));
	glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(wglGetProcAddress("glVertexAttribPointer"));
	glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(wglGetProcAddress("glBindBuffer"));
	glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(wglGetProcAddress("glBufferData"));
	glGetVertexAttribPointerv = reinterpret_cast<PFNGLGETVERTEXATTRIBPOINTERVPROC>(wglGetProcAddress("glGetVertexAttribPointerv"));
	glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(wglGetProcAddress("glUseProgram"));
	glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(wglGetProcAddress("glDeleteVertexArrays"));
	glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(wglGetProcAddress("glDeleteBuffers"));
	glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(wglGetProcAddress("glDeleteProgram"));
	glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(wglGetProcAddress("glDeleteShader"));
}

void checkShader(GLuint shaderID)
{
	GLint result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == FALSE)
	{
		GLsizei length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			GLchar *infoLog = new GLchar[length];
			WCHAR *msg = new WCHAR[length];
			glGetShaderInfoLog(shaderID, length, &length, infoLog);
			MultiByteToWideChar(CP_ACP, 0, infoLog, -1, (LPWSTR)msg, length + 1);
			MessageBox(NULL, msg, L"Error", MB_OK);
			delete infoLog;
			delete msg;
		}
		else
			MessageBox(NULL, L"glCompileShader() failed", L"Error", MB_OK);
		/* TODO: program stop */
	}
}

void checkProgram(GLuint shaderID, GLenum pname)
{
	GLint result;
	glGetProgramiv(shaderID, pname, &result);
	if (result == FALSE)
	{
		GLsizei length;
		glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			GLchar *infoLog = new GLchar[length];
			WCHAR *msg = new WCHAR[length];
			glGetProgramInfoLog(shaderID, length, &length, infoLog);
			MultiByteToWideChar(CP_ACP, 0, infoLog, -1, (LPWSTR)msg, length + 1);
			MessageBox(NULL, msg, L"Error", MB_OK);
			delete infoLog;
			delete msg;
		}
		else
			MessageBox(NULL, L"glLinkProgram() or glValidateProgram() failed", L"Error", MB_OK);
		/* TODO: program stop */
	}
}

void InitShaders()
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShaderID, 1, &vertex_shader, NULL);
	glShaderSource(fragmentShaderID, 1, &fragment_shader, NULL);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	checkShader(vertexShaderID);
	checkShader(fragmentShaderID);

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	checkProgram(programID, GL_LINK_STATUS);
	glValidateProgram(programID);
	checkProgram(programID, GL_VALIDATE_STATUS);

	GLint positionLocation = glGetAttribLocation(programID, "positionIn");
	GLint colorLocation = glGetAttribLocation(programID, "colorIn");

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// x, y, z, r, g, b (triangle)
	float vertices[] = {
		0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0,
		1.0, -1.0, 0.0, 0.0, 1.0, 0.0, 1.0,
		-1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 1.0,
	};
	glBindVertexArray(vao);
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(0));
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	glUseProgram(programID);
}

int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!MyRegisterClass(hInstance))
	{
		MessageBox(NULL, L"RegisterClass() failed: Cannot create a window.", L"Error", MB_OK);
		return FALSE;
	}
	if (!InitInstance(hInstance, nCmdShow))
	{
		MessageBox(NULL, L"CreateWindow() failed: Can not create a window.", L"Error", MB_OK);
		return FALSE;
	}
	if (!CreateRenderContext(hInstance))
	{
		MessageBox(NULL, L"wglCreateContext() failed: Can not create an OpenGL context.", L"Error", MB_OK);
		return FALSE;
	}
	wglMakeCurrent(hDC, hRC);
	InitGLFunctions();
	InitShaders();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	/* main loop */
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
