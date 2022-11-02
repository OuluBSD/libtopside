#ifndef _IGraphics_GlobalApi_h_
#define _IGraphics_GlobalApi_h_

NAMESPACE_PARALLEL_BEGIN


inline void Begin(PrimType type) {}
inline void Finish() {}
inline void ClearColor(Float r, Float g, Float b, Float a) {}
inline void ClearDepth(Float z) {}
inline void Enable(SysAttr attr) {}
inline void Disable(SysAttr attr) {}
inline void Scissor(Int x, Int y, Uint w, Uint h) {}
inline void MatrixMode(MtxMode mode) {}
inline void GetBoolean(ParamEnum p, Gxb* b) {}
inline void DepthMask(Gxb b) {}
inline void Clear(Gxbf bitfield) {}
inline void CullFace(CullMode mode) {}
inline void PolygonOffset(Gxf factor, Gxf units) {}
inline void LoadIdentity() {}
inline void TexEnv(TexTgt target, TexParam param, Gxf* params) {}
inline void TexEnv(TexTgt target, TexEnvValue value) {}
inline void ShadeModel(ShadeMode mode) {}
inline void Flush() {}
inline void Color(Gxby r, Gxby g, Gxby b, Gxby a) {}
inline void Vertex(Float x, Float y, Float z) {}
inline void End() {}
inline void LineWidth(Float w) {}
inline void PointSize(Float w) {}
inline void Fog(FogParam param, Gxf value) {}
inline void Fog(FogParam param, Gxi value) {}
inline void Fog(FogParam param, Gxf* value) {}
inline void BlendFunc(SrcFactor sfactor, DstFactor dfactor) {}
inline void LogicOp(LogicOpType op) {}
inline void DepthFunc(LogicFuncType func) {}
inline void TexImage2D(Uint level, InFmt internalformat, Uint width, Uint height, Bool border,
	PixFmt format, PixType type, const Void *pixels) {}
inline void PixelStore(PixAlign align, Int value) {}
inline void ReadPixels(Int x, Int y, Uint width, Uint height, PixFmt format, PixType type,
	void* data) {}
inline void PixelTransfer(PixTrans pname, Float param) {}
inline void ActiveTexture(TexArb texture) {}
inline void AlphaFunc(LogicFuncType func, Float value) {}
inline void GenTextures(Uint n, Uint* textures) {}
inline void BindTexture(TexBind target, Uint texture) {}
inline void TexParameter(TexBind target, ParamName pname, Int param) {}
inline void DeleteTextures(Uint n, const Uint* textures) {}
inline void LoadMatrix(const Float* m) {}
inline void Viewport(Int x, Int y, Uint width, Uint height) {}
inline void DepthRange(Float near, Float far) {}

inline void MultiTexCoord(TexArb target, Gxf s, Gxf t, Gxf r, Gxf q) {}

NAMESPACE_PARALLEL_END

#endif
