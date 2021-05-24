#include "GL.h"

#ifdef flagGUI

NAMESPACE_TOPSIDE_BEGIN


void OpenGLRenderer::PreFrame() {
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	
	
	// Enable smooth shading
	glShadeModel( GL_SMOOTH );
	
	// Set the background black
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	// Depth buffer setup
	glClearDepth( 1.0f );
	
	// Enables Depth Testing
	glEnable( GL_DEPTH_TEST );
	
	// The Type Of Depth Test To Do
	glDepthFunc( GL_LEQUAL );
	
	// Really Nice Perspective Calculations
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	
	
	// Culling.
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );
	glEnable( GL_CULL_FACE );
	
	
	ASSERT(screen_sz.cx > 0 && screen_sz.cy > 0);
	glViewport(0, 0, screen_sz.cx, screen_sz.cy);
	
}

void OpenGLRenderer::PostFrame() {
	//if (win)
	//	SDL_GL_SwapWindow(win);
}



NAMESPACE_TOPSIDE_END

#endif
