/*
 *          Copyright 2020, Vitali Baumtrok.
 * Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE or copy at
 *        http://www.boost.org/LICENSE_1_0.txt)
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <gl/GL.h>

#define ERR_NONE 0
#define ERR_REGCLS 1
#define ERR_CRWIN_FC 2
#define ERR_DC_FC 3
#define ERR_CPF_FC 4
#define ERR_SPF_FC 5
#define ERR_RC_FC 6
#define ERR_CRWIN_AWR 7
#define ERR_CRWIN 8
#define ERR_DC 9
#define ERR_PADRCPFARB 10
#define ERR_PADRCCAARB 11
#define ERR_CPFARB 12
#define ERR_SPF 13
#define ERR_CCAARB 14
#define ERR_CSV 15
#define ERR_CSF 16
#define ERR_LP 17
#define ERR_VP 18

/* copied from wglext.h */
typedef BOOL(WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL(WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);
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
#define WGL_SWAP_EXCHANGE_ARB             0x2028
#define WGL_SWAP_METHOD_ARB               0x2007
#define WGL_SWAP_COPY_ARB                 0x2029

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
PFNWGLSWAPINTERVALEXTPROC                       wglSwapIntervalEXT = nullptr;

struct {
	const char *vertex, *fragment;
	GLuint vertexId, fragmentId;
} shader = { "#version 130\n\nin vec3 positionIn;\nin vec4 colorIn;\nout vec4 fragementColor;\n\nuniform mat4 projection = mat4(1.0);\nuniform mat4 model = mat4(1.0);\n\nvoid main() {\n\tgl_Position = projection * model * vec4(positionIn, 1.0f);\n\tfragementColor = colorIn;\n}",
             "#version 130\n\nin vec4 fragementColor;\nout vec4 color;\n\nvoid main() {\n\tcolor = fragementColor;\n}",
             0, 0 };

struct {
	GLuint id, vbo, vao;
} program = { 0, 0, 0 };

struct {
	int code;
	LPCWSTR message;
} err = { ERR_NONE, nullptr };

struct {
	HWND hndl;
	HDC deviceContext;
	HGLRC renderContext;
} fakeWindow = { nullptr, nullptr, nullptr };

struct {
	LPCWSTR className;
	LPCSTR classNameChar;
	LPCWSTR title;
	HWND hndl;
	HDC deviceContext;
	HGLRC renderContext;
	int prevX, prevY, width, height, prevWidth, prevHeight, resX, resY;
	bool fullscreen, visible;
} window = { L"OpenGL", "OpenGL", L"OpenGL Example", nullptr, nullptr, nullptr, 0, 0, 0, 0, 0, 0, 640, 480, false, false };

static PROC
getProc(LPCSTR procName, int errCode, LPCWSTR errMessage)
{
	PROC proc = nullptr;
	if (err.code == ERR_NONE)
	{
		proc = wglGetProcAddress(procName);
		if (!proc)
		{
			err.code = errCode;
			err.message = errMessage;
		}
	}
	return proc;
}

static void
checkShader(GLuint shaderId)
{
	if (err.code == ERR_NONE)
	{
		GLint result;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
		if (result == FALSE)
		{
			GLsizei length;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
			if (length > 0)
			{
				GLchar *infoLog = new GLchar[length];
				WCHAR *msg = new WCHAR[length];
				glGetShaderInfoLog(shaderId, length, &length, infoLog);
				MultiByteToWideChar(CP_ACP, 0, infoLog, -1, (LPWSTR)msg, length + 1);
				err.message = msg;
				delete[] infoLog;
			}
			else if (shader.vertexId == shaderId)
				err.message = L"glCompileShader failed: Can not compile vertex shader.";
			else
				err.message = L"glCompileShader failed: Can not compile fragmet shader.";
			if (shader.vertexId == shaderId)
				err.code = ERR_CSV;
			else
				err.code = ERR_CSV;
		}
	}
}

static void
checkProgram(GLuint shaderId, GLenum param)
{
	if (err.code == ERR_NONE)
	{
		GLint result;
		glGetProgramiv(shaderId, param, &result);
		if (result == FALSE)
		{
			GLsizei length;
			glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &length);
			if (length > 0)
			{
				GLchar *infoLog = new GLchar[length];
				WCHAR *msg = new WCHAR[length];
				glGetProgramInfoLog(shaderId, length, &length, infoLog);
				MultiByteToWideChar(CP_ACP, 0, infoLog, -1, (LPWSTR)msg, length + 1);
				err.message = msg;
				delete[] infoLog;
			}
			else if (param == GL_LINK_STATUS)
				err.message = L"glLinkProgram failed: Can not link program.";
			else
				err.message = L"glValidateProgram() failed: Can not execute shader program.";
			if (param == GL_LINK_STATUS)
				err.code = ERR_LP;
			else
				err.code = ERR_VP;
		}
	}
}

static void
centerWindow()
{
	if (err.code == ERR_NONE)
	{
		RECT rect;
		MONITORINFO mi = { sizeof(mi) };

		GetMonitorInfo(MonitorFromWindow(window.hndl, MONITOR_DEFAULTTONEAREST), &mi);
		int x = (mi.rcMonitor.right - mi.rcMonitor.left - window.width) / 2;
		int y = (mi.rcMonitor.bottom - mi.rcMonitor.top - window.height) / 2;

		SetWindowPos(window.hndl, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
}

static void
setFullscreen(bool fullscreen)
{
	DWORD style = GetWindowLong(window.hndl, GWL_STYLE);
	if (fullscreen)
	{
		RECT rect;
		MONITORINFO mi = { sizeof(mi) };
		GetWindowRect(window.hndl, &rect);
		window.prevX = rect.left;
		window.prevY = rect.top;
		window.prevWidth = rect.right - rect.left;
		window.prevHeight = rect.bottom - rect.top;

		GetMonitorInfo(MonitorFromWindow(window.hndl, MONITOR_DEFAULTTOPRIMARY), &mi);
		SetWindowLong(window.hndl, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(window.hndl, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
			mi.rcMonitor.right - mi.rcMonitor.left,
			mi.rcMonitor.bottom - mi.rcMonitor.top,
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}
	else
	{
		MONITORINFO mi = { sizeof(mi) };
		UINT flags = SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW;
		GetMonitorInfo(MonitorFromWindow(window.hndl, MONITOR_DEFAULTTOPRIMARY), &mi);
		SetWindowLong(window.hndl, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
		SetWindowPos(window.hndl, HWND_NOTOPMOST, window.prevX, window.prevY, window.prevWidth, window.prevHeight, flags);
	}
}

static void
draw()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glFlush();
	SwapBuffers(window.deviceContext);
}

static LRESULT CALLBACK
wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_SIZE:
		glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		draw();
		break;
	case WM_KEYDOWN:
		/* ESC */
		if (wParam == 27)
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		/* F11 */
		else if (wParam == 122)
			setFullscreen(window.fullscreen = !window.fullscreen);
		break;
	case WM_CLOSE:
		window.visible = false;
		wglMakeCurrent(window.deviceContext, NULL);
		wglDeleteContext(window.renderContext);
		ReleaseDC(hWnd, window.deviceContext);
		DestroyWindow(hWnd);
		/* stop event queue thread */
		PostQuitMessage(0);
		break;
	default:
		result = DefWindowProc(hWnd, message, wParam, lParam);
	}
	return result;
}

static void
registerClass(HINSTANCE instance)
{
	WNDCLASSEXW wcex;
	memset(&wcex, 0, sizeof(wcex));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = (WNDPROC)wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = window.className;
	wcex.hIconSm = NULL;

	if (!RegisterClassExW(&wcex))
	{
		err.code = ERR_REGCLS;
		err.message = L"RegisterClassExW() failed: Can not register window class.";
	}
}

static void
createFakeWindow(HINSTANCE instance)
{
	if (err.code == ERR_NONE)
	{
		fakeWindow.hndl = CreateWindowW(window.className, L"Fake Window", WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, nullptr, nullptr, instance, nullptr);
		if (!fakeWindow.hndl)
		{
			err.code = ERR_CRWIN_FC;
			err.message = L"CreateWindowW() failed: Can not create fake window.";
		}
	}
}

static void
createFakeContext()
{
	if (err.code == ERR_NONE)
	{
		fakeWindow.deviceContext = GetDC(fakeWindow.hndl);
		if (fakeWindow.deviceContext)
		{
			int pixelFormat;
			PIXELFORMATDESCRIPTOR pixelFormatDesc;
			memset(&pixelFormatDesc, 0, sizeof(PIXELFORMATDESCRIPTOR));
			pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pixelFormatDesc.nVersion = 1;
			pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
			pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
			pixelFormatDesc.cColorBits = 32;
			pixelFormatDesc.cAlphaBits = 8;
			pixelFormatDesc.cDepthBits = 24;
			pixelFormat = ChoosePixelFormat(fakeWindow.deviceContext, &pixelFormatDesc);
			if (pixelFormat)
			{
				if (SetPixelFormat(fakeWindow.deviceContext, pixelFormat, &pixelFormatDesc))
				{
					fakeWindow.renderContext = wglCreateContext(fakeWindow.deviceContext);
					if (!fakeWindow.renderContext)
					{
						err.code = ERR_RC_FC;
						err.message = L"wglCreateContext() failed: Can not create fake render context.";
					}
				}
				else
				{
					err.code = ERR_SPF_FC;
					err.message = L"SetPixelFormat() failed: Can not create fake render context.";
				}
			}
			else
			{
				err.code = ERR_CPF_FC;
				err.message = L"ChoosePixelFormat() failed: Can not create fake render context.";
			}
		}
		else
		{
			err.code = ERR_DC_FC;
			err.message = L"GetDC() failed: Can not create fake device context.";
		}
	}
}

static void
destroyFakeWindow()
{
	if (err.code == ERR_NONE)
	{
		wglMakeCurrent(fakeWindow.deviceContext, NULL);
		wglDeleteContext(fakeWindow.renderContext);
		ReleaseDC(fakeWindow.hndl, fakeWindow.deviceContext);
		DestroyWindow(fakeWindow.hndl);
	}
	else
	{
		if (err.code > ERR_DC_FC)
			ReleaseDC(fakeWindow.hndl, fakeWindow.deviceContext);
		if (err.code > ERR_CRWIN_FC)
			DestroyWindow(fakeWindow.hndl);
	}
	fakeWindow.renderContext = nullptr;
	fakeWindow.deviceContext = nullptr;
	fakeWindow.hndl = nullptr;
}

static void
createWindow(HINSTANCE instance)
{
	if (err.code == ERR_NONE)
	{
		window.fullscreen = false;

		RECT rect = { 0, 0, window.resX, window.resY };
		DWORD style = WS_OVERLAPPEDWINDOW;
		if (AdjustWindowRect(&rect, style, false))
		{
			/* compute window size including border */
			window.width = rect.right - rect.left;
			window.height = rect.bottom - rect.top;

			window.hndl = CreateWindowW(window.className, window.title, style, 0, 0, window.width, window.height, nullptr, nullptr, instance, nullptr);
			if (!window.hndl)
			{
				err.code = ERR_CRWIN;
				err.message = L"CreateWindowW() failed: Can not create window.";
			}
		}
		else
		{
			err.code = ERR_CRWIN_AWR;
			err.message = L"AdjustWindowRect() failed: Can not create window.";
		}
	}
}

static void
createContext()
{
	if (err.code == ERR_NONE)
	{
		window.deviceContext = GetDC(window.hndl);
		if (window.deviceContext)
		{
			PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

			wglMakeCurrent(fakeWindow.deviceContext, fakeWindow.renderContext);

			wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(getProc("wglChoosePixelFormatARB", ERR_PADRCPFARB, L"wglGetProcAddress() failed: Can not find wglChoosePixelFormatARB."));
			wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(getProc("wglCreateContextAttribsARB", ERR_PADRCCAARB, L"wglGetProcAddress() failed: Can not find wglCreateContextAttribsARB."));
			wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(getProc("wglSwapIntervalEXT", ERR_NONE, L""));

			if (err.code == ERR_NONE)
			{
				int pixelFormat;
				BOOL status;
				UINT numFormats;
				const int pixelAttribs[] = {
					WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
					WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
					WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
					/* WGL_SWAP_EXCHANGE_ARB causes problems with window menu in fullscreen */
					WGL_SWAP_METHOD_ARB, WGL_SWAP_COPY_ARB,
					WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
					WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
					WGL_COLOR_BITS_ARB, 32,
					WGL_ALPHA_BITS_ARB, 8,
					WGL_DEPTH_BITS_ARB, 24,
					0
				};
				int  contextAttributes[] = {
					WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
					WGL_CONTEXT_MINOR_VERSION_ARB, 0,
					WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
					0
				};
				status = wglChoosePixelFormatARB(window.deviceContext, pixelAttribs, nullptr, 1, &pixelFormat, &numFormats);
				if (status && numFormats)
				{
					PIXELFORMATDESCRIPTOR pfd;
					memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
					DescribePixelFormat(window.deviceContext, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

					if (SetPixelFormat(window.deviceContext, pixelFormat, &pfd))
					{
						window.renderContext = wglCreateContextAttribsARB(window.deviceContext, 0, contextAttributes);
						if (!window.renderContext)
						{
							err.code = ERR_CCAARB;
							err.message = L"wglCreateContextAttribsARB() failed: Can not create context.";
						}
					}
					else
					{
						err.code = ERR_SPF;
						err.message = L"SetPixelFormat() failed: Can not create context.";
					}
				}
				else
				{
					err.code = ERR_CPFARB;
					err.message = L"wglChoosePixelFormatARB() failed: Can not create context.";
				}
			}
		}
		else
		{
			err.code = ERR_DC;
			err.message = L"GetDC() failed: Can not create context.";
		}
	}
}

static void
initOpenGLFunctions()
{
	if (err.code == ERR_NONE)
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
}

static void
initShader()
{
	if (err.code == ERR_NONE)
	{
		shader.vertexId = glCreateShader(GL_VERTEX_SHADER);
		shader.fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(shader.vertexId, 1, &shader.vertex, NULL);
		glShaderSource(shader.fragmentId, 1, &shader.fragment, NULL);

		glCompileShader(shader.vertexId);
		glCompileShader(shader.fragmentId);

		checkShader(shader.vertexId);
		checkShader(shader.fragmentId);
	}
}

static void
initProgram()
{
	if (err.code == ERR_NONE)
	{
		program.id = glCreateProgram();
		glAttachShader(program.id, shader.vertexId);
		glAttachShader(program.id, shader.fragmentId);
		glLinkProgram(program.id);
		checkProgram(program.id, GL_LINK_STATUS);

		if (err.code == ERR_NONE)
		{
			glValidateProgram(program.id);
			checkProgram(program.id, GL_VALIDATE_STATUS);
		}
	}
}

static void
initVertexObjects()
{
	if (err.code == ERR_NONE)
	{
		GLint positionLocation = glGetAttribLocation(program.id, "positionIn");
		GLint colorLocation = glGetAttribLocation(program.id, "colorIn");

		glGenBuffers(1, &program.vbo);
		glGenVertexArrays(1, &program.vao);

		// x, y, z, r, g, b (triangle)
		float vertices[] = {
			0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0,
			1.0, -1.0, 0.0, 0.0, 1.0, 0.0, 1.0,
			-1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 1.0,
		};
		glBindVertexArray(program.vao);
		glEnableVertexAttribArray(positionLocation);
		glEnableVertexAttribArray(colorLocation);

		glBindBuffer(GL_ARRAY_BUFFER, program.vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(0));
		glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

		glUseProgram(program.id);
	}
}

int APIENTRY
wWinMain(_In_     HINSTANCE hInstance,
         _In_opt_ HINSTANCE hPrevInstance,
         _In_     LPWSTR    lpCmdLine,
         _In_     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	registerClass(hInstance);
	createFakeWindow(hInstance);
	createFakeContext();
	createWindow(hInstance);
	createContext();
	destroyFakeWindow();
	wglMakeCurrent(window.deviceContext, window.renderContext);
	initOpenGLFunctions();
	initShader();
	initProgram();
	initVertexObjects();

	if (err.code == ERR_NONE)
	{
		/* enable vsync */
		if (wglSwapIntervalEXT)
			wglSwapIntervalEXT(1);
		centerWindow();
		ShowWindow(window.hndl, nCmdShow);
		UpdateWindow(window.hndl);
		window.visible = true;

		MSG msg;
		while (window.visible)
		{
			while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			draw();
		}
	}
	else
	{
		wchar_t *title = new wchar_t[10];
		swprintf_s(title, 10, L"Error %d", err.code);
		MessageBox(NULL, err.message, title, MB_OK);
		delete[] title;
	}

	return err.code;
}