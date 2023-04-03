#ifdef flagWIN32
#include "maindef.h"
#include <gl/GL.h>
#include <stdio.h>
#pragma comment(lib, "opengl32.lib")

class FalseContext
{
private:
	HDC hdc;
	HGLRC rc;
	HWND hwnd;
public:
	FalseContext() : hdc(NULL), rc(NULL), hwnd(NULL)
	{
	}
	~FalseContext()
	{
		freecontext();
	}

	void setContext()
	{
		if(wglGetCurrentContext() == NULL)
		{
			initcontext();
			wglMakeCurrent(hdc, rc);
		}
	}

	void removeContext()
	{
		if(wglGetCurrentContext() == rc)
		{
			wglMakeCurrent(NULL,NULL);
		}
	}

private:
	void initcontext()
	{
		if((hdc == NULL) || (rc==NULL))
		{
			createcontext();
		}
	}
	void freecontext()
	{
		if(rc)
		{
			removeContext();
			wglDeleteContext(rc);
			rc = NULL;
		}

		if(hdc)
		{
			ReleaseDC(hwnd, hdc);
			hdc= NULL;
		}

		hwnd = NULL;
	}

	void createcontext()
	{
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL ,    
			PFD_TYPE_RGBA,            
			32,                      
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                       
			8,                        
			0,                       
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};
		int PixelFormatIndex;
		hdc = GetDC(hwnd);


		PixelFormatIndex = ChoosePixelFormat(hdc, &pfd);
		if(PixelFormatIndex == 0)
		{
			PixelFormatIndex = 1;
			if(DescribePixelFormat(hdc,
				PixelFormatIndex, sizeof(PIXELFORMATDESCRIPTOR), 
				&pfd)==0)
			{
				return ;
			}
		}

		if(SetPixelFormat(hdc, PixelFormatIndex,
			&pfd) == FALSE)
		{
			return ;
		}

		DescribePixelFormat(hdc, PixelFormatIndex, 
			sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		rc = wglCreateContext(hdc);
	}

};


void loadproc(char* name, char** funcptr)
{
	/* module opengl32.dll must be loaded */
	HMODULE hOpenGL;
	FalseContext frc;
	if(!funcptr)
		return;
	if(*funcptr)
		return;

	/* try finding the procedure via wglGetProcAddress */
	frc.setContext();
	*funcptr = (char*) wglGetProcAddress(name);
	frc.removeContext();

	if(*funcptr)
	{
		if(IsDebuggerPresent())
		{
			char* buffer = (char*) calloc(128, sizeof(char));
			if(buffer)
			{
				sprintf_s(buffer,128*sizeof(char), "OPENGL: loaded using wglGetProcAddress(\"%s\") = %X\n",
					name, (size_t) funcptr);
				OutputDebugStringA(buffer);
				free(buffer);
			}
		}
		return;
	}

	/* try loading statically from opengl32.dll */
	hOpenGL = LoadLibraryA("opengl32");
	if(!hOpenGL) hOpenGL = LoadLibraryA("opengl32.dll");
	if(!hOpenGL) 
	{
		*funcptr = (char*) 0;
		return;
	}

	*funcptr = (char*) GetProcAddress(hOpenGL, name);
	if(*funcptr)
	{
		if(IsDebuggerPresent())
		{
			char* buffer = (char*) calloc(128, sizeof(char));
			if(buffer)
			{
				sprintf_s(buffer,128*sizeof(char), "OPENGL: loaded using GetProcAddress(OPENGL32.DLL,\"%s\") = %X\n",
					name, (size_t) funcptr);
				OutputDebugStringA(buffer);
				free(buffer);
			}
		}
		return;
	}

	if(IsDebuggerPresent())
	{
		char* buffer = (char*) calloc(128, sizeof(char));
		if(buffer)
		{
			sprintf_s(buffer,128*sizeof(char), "OPENGL: Procedure \"%s\" not found.\n",
				name);
			OutputDebugStringA(buffer);
			free(buffer);
		}
	}

}

extern "C" GLAPI void* APIENTRY glExtGetProcAddress(const char* name)
{
	char* addr = (char*) 0;
	loadproc((char*) name, &addr);
	return (void*) addr;
}

#endif
