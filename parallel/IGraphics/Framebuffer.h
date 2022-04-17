#ifndef _SoftRend_Framebuffer_h_
#define _SoftRend_Framebuffer_h_

NAMESPACE_PARALLEL_BEGIN


/*class SoftBuffer : Moveable<SoftBuffer> {
	bool inited = false;
	
public:
	Texture tex;
	
public:
	typedef SoftBuffer CLASSNAME;
	
	
	
	void Clear() {inited = false;}
	bool Create() {ASSERT(!inited); inited = true; return true;}
	void operator=(const Nuller&) {Clear();}
	operator bool() const {return inited;}
};*/


template <class Gfx>
class SoftFramebufferT {
	bool inited = false;
	
protected:
	friend class SoftRend;
	using NativeTexture = typename Gfx::NativeTexture;
	
	NativeTexture tex = 0;
	Texture* gtex = 0;
	
	GVar::Wrap wrap[GVar::TEXTYPE_COUNT] {GVar::WRAP_REPEAT, GVar::WRAP_REPEAT};
	GVar::Filter filter[GVar::TEXTYPE_COUNT] {GVar::FILTER_NEAREST, GVar::FILTER_NEAREST, GVar::FILTER_NEAREST};
public:
	typedef SoftFramebufferT CLASSNAME;
	SoftFramebufferT();
	
	void Clear();
	bool Create();
	void ClearData(GVar::BufferType type);
	void ClearDataAll();
	
	void SetParam(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat);
	
	const NativeTexture& GetTex() const {ASSERT(tex); return tex;}
	Texture& GetGeomTex() const {ASSERT(gtex); return *gtex;}
	
	void operator=(NativeTexture& tex);
	void SetTexture(Texture* t) {ASSERT(tex == 0); gtex = t;}
	void operator=(const Nuller&) {Clear();}
	void operator=(const SoftFramebufferT&) = delete;
	operator bool() const {return inited;}
	
	NativeTexture& GetNativeTexture() {return tex;}
	
};


NAMESPACE_PARALLEL_END

#endif
