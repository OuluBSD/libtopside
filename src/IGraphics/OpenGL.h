#ifndef _IGraphics_OpenGL_h_
#define _IGraphics_OpenGL_h_

#ifdef flagOGL

#ifndef flagSCREEN
	#error <Graphics/OpenGL.h> should only be included, when SCREEN flag is set.
#endif



#if defined flagPOSIX || defined flagCLANG || defined flagGCC
	#ifdef flagWIN32
		// glext fail
	#else
		#include <GL/glext.h>
	#endif
#elif defined flagMSC
	#include <ports/glext/glext.h>
#else
	#include "glext.h"
#endif





NAMESPACE_GRAPHICS_BEGIN
using namespace GVar;

inline void Begin(PrimType type) {glBegin(type);}
inline void Finish() {glFinish();}
inline void ClearColor(Float r, Float g, Float b, Float a) {glClearColor(r,g,b,a);}
inline void ClearDepth(Float z) {glClearDepth(z);}
inline void Enable(SysAttr attr) {glEnable(attr);}
inline void Disable(SysAttr attr) {glDisable(attr);}
inline void Scissor(Int x, Int y, Uint w, Uint h) {glScissor(x, y, w, h);}
inline void MatrixMode(MtxMode mode) {glMatrixMode(mode);}
inline void GetBoolean(ParamEnum p, Gxb* b) {glGetBooleanv(p, b);}
inline void DepthMask(Gxb b) {glDepthMask(b);}
inline void Clear(Gxbf bitfield) {glClear(bitfield);}
inline void CullFace(CullMode mode) {glCullFace(mode);}
inline void PolygonOffset(Gxf factor, Gxf units) {glPolygonOffset(factor, units);}
inline void LoadIdentity() {glLoadIdentity();}
inline void TexEnv(TexTgt target, TexParam param, Gxf* params) {glTexEnvfv(target, param, params);}
inline void TexEnv(TexTgt target, TexEnvValue value) {glTexEnvi(target, TEXPARAM_TEXTURE_ENV_MODE, value);}
inline void ShadeModel(ShadeMode mode) {glShadeModel(mode);}
inline void Flush() {glFlush();}
inline void Color(Byte r, Byte g, Byte b, Byte a) {glColor4ub(r,g,b,a);}
inline void Vertex(Float x, Float y, Float z) {glVertex3f(x,y,z);}
inline void End() {glEnd();}
inline void LineWidth(Float w) {glLineWidth(w);}
inline void PointSize(Float sz) {glPointSize(sz);}
inline void Fog(FogParam param, Gxf value) {glFogf(param, value);}
inline void Fog(FogParam param, Gxi value) {glFogi(param, value);}
inline void Fog(FogParam param, Gxf* value) {glFogfv(param, value);}
inline void BlendFunc(SrcFactor sfactor, DstFactor dfactor) {glBlendFunc(sfactor, dfactor);}
inline void LogicOp(LogicOpType op) {glLogicOp(op);}
inline void DepthFunc(LogicFuncType func) {glDepthFunc(func);}
inline void TexImage2D(Uint level, InFmt internalformat, Uint width, Uint height, Bool border,
	PixFmt format, PixType type, const Void *pixels) {
	glTexImage2D(GL_TEXTURE_2D, level, internalformat, width, height, border, format, type, pixels);
}
inline void PixelStore(PixAlign align, Int value) {glPixelStorei(align, value);}
inline void ReadPixels(Int x, Int y, Uint width, Uint height, PixFmt format, PixType type, void* data) {
	glReadPixels(x, y, width, height, format, type, data);
}
inline void PixelTransfer(PixTrans pname, Float param) {glPixelTransferf(pname, param);}
inline void ActiveTexture(TexArb texture);// winclang error {glActiveTextureARB(texture);}
inline void AlphaFunc(LogicFuncType func, Float value) {glAlphaFunc(func, value);}
inline void GenTextures(Uint n, Uint* textures) {glGenTextures(n, textures);}
inline void BindTexture(TexBind target, Uint texture) {glBindTexture(target, texture);}
inline void TexParameter(TexBind target, ParamName pname, Int param) {glTexParameteri(target, pname, param);}
inline void DeleteTextures(Uint n, const Uint* textures) {glDeleteTextures(n, textures);}
inline void LoadMatrix(const Float* m) {glLoadMatrixf(m);}
inline void Viewport(Int x, Int y, Uint width, Uint height) {glViewport(x, y, width, height);}
inline void DepthRange(Float near, Float far);// winclang error {glDepthRangef(near, far);}

inline void MultiTexCoord(TexArb target, Gxf s, Gxf t, Gxf r, Gxf q);// winclang error {glMultiTexCoord4fARB(target, s, t, r, q);}

NAMESPACE_GRAPHICS_END

#endif
#endif
