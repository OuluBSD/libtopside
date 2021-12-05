#include "Graphics.h"

#ifdef flagSCREEN


NAMESPACE_TOPSIDE_BEGIN


OglFramebuffer::OglFramebuffer() : sz(0,0) {
	
}

bool OglFramebuffer::Create(int w, int h, int channels) {
	sz = Size(0,0);
	this->channels = 0;
	
	if (channels != 3) {
		LOG("OglFramebuffer::Create: error: only channels==3 is supported (tried " << channels << ")");
		return false;
	}
	
	if (sz.cx == w && sz.cy == h) {
		return true;
	}
	this->channels = channels;
	sz.cx = w;
	sz.cy = h;
	
	Clear();
	
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	glGenFramebuffersEXT(1, &fb_name);
	glBindFramebuffer(GL_FRAMEBUFFER, fb_name);
	
	
	// The texture we're going to render to
	glGenTextures(1, &fb_texture);
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, fb_texture);
	
	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	
	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	
	// The depth buffer
	/*GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);*/
	
	
	// Set "fb_texture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fb_texture, 0);
	
	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
	
	return true;
}

void OglFramebuffer::Bind() {
	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, fb_name);
}

void OglFramebuffer::Clear() {
	if (fb_name) {
		
	}
	if (fb_texture) {
		
	}
}


NAMESPACE_TOPSIDE_END

#endif
