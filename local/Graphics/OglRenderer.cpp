#include "Graphics.h"

#ifdef flagSCREEN

NAMESPACE_TOPSIDE_BEGIN


void OglRendererBase::ClearBuffers() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void OglRendererBase::SetSmoothShading(bool b) {
	glShadeModel(b ? GL_SMOOTH : GL_FLAT);
}

void OglRendererBase::SetDepthTest(bool b) {
	if (b) glEnable(GL_DEPTH_TEST);
	else   glDisable(GL_DEPTH_TEST);
}

void OglRendererBase::SetDepthOrderLess(bool b) {
	if (b) glDepthFunc( GL_LEQUAL );
	else   glDepthFunc( GL_GEQUAL );
}

void OglRendererBase::SetClearValue(RGBA clr, byte depth) {
	// Set the background black
	glClearColor( clr.r/255.0f, clr.g/255.0f, clr.b/255.0f, clr.a/255.0f );
	
	// Depth buffer setup
	glClearDepth( depth/255.0f );
	
}

void OglRendererBase::SetFastPerspectiveCorrection(bool b) {
	if (b)
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
	else
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void OglRendererBase::SetTriangleBacksideCulling(bool b) {
	if (b) {
		glEnable( GL_CULL_FACE );
		glCullFace( GL_BACK );
	}
	else
		glDisable( GL_CULL_FACE );
}

void OglRendererBase::SetTriangleFrontsideCCW(bool b) {
	glFrontFace( b ? GL_CCW : GL_CW );
}

void OglRendererBase::SetViewport(Size sz) {
	ASSERT(sz.cx > 0 && sz.cy > 0);
	glViewport(0, 0, sz.cx, sz.cy);
}

void OglRendererBase::LeaveFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*void OglRendererBase::ActivateNextFrame() {
	// pass
}*/


NAMESPACE_TOPSIDE_END

#endif
