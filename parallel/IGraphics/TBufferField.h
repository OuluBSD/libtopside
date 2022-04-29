#ifndef _IGraphics_TBufferField_h_
#define _IGraphics_TBufferField_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class GfxBufferFieldT : RTTIBase {
	
public:
	EnvStateRef env;
	
protected:
	using Buffer = BufferT<Gfx>;
	using NativeFrameBufferRef = typename Gfx::NativeFrameBufferRef;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	
	Buffer buf;
	String frag_shdr;
	String vtx_shdr;
	String frag_path;
	String vtx_path;
	String library_paths;
	bool is_user_shader = false;
	bool is_audio = false;
	NativeFrameBufferRef fb = 0;
	NativeColorBufferRef clr = 0;
	
	void SetShaderFile(String frag_path, String vtx_path, String library_paths) {this->frag_path = frag_path; this->vtx_path = vtx_path; this->library_paths = library_paths;}
	void SetFragmentShader(String s) {frag_shdr = s;}
	void SetVertexShader(String s) {vtx_shdr = s;}
	
public:
	using GfxBufferField = GfxBufferFieldT<Gfx>;
	RTTI_DECL0(GfxBufferFieldT);
	
	void Visit(RuntimeVisitor& vis) {vis % buf;}
	
	bool Initialize(AtomBase& a, const Script::WorldState& ws);
	bool PostInitialize();
	bool ImageInitialize(bool is_win_fbo, Size screen_sz);
	
	Buffer& GetBuffer() {return buf;}
	bool AcceptsOrder() const {return is_user_shader || frag_shdr.GetCount();}
	void Update(double dt) {buf.Update(dt);}
	
	bool IsAudio() const {return is_audio;}
	
};


NAMESPACE_PARALLEL_END

#endif
