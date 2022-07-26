#ifndef _IGraphics_TBufferField_h_
#define _IGraphics_TBufferField_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class GfxBufferFieldT : RTTIBase {
	
protected:
	using Buffer = BufferT<Gfx>;
	using DataState = DataStateT<Gfx>;
	using NativeFrameBufferRef = typename Gfx::NativeFrameBufferRef;
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	
	Buffer buf;
	DataState data;
	NativeFrameBufferRef fb = 0;
	NativeColorBufferRef clr = 0;
	
public:
	using GfxBufferField = GfxBufferFieldT<Gfx>;
	RTTI_DECL0(GfxBufferFieldT);
	
	void Visit(RuntimeVisitor& vis) {vis % buf;}
	
	bool Initialize(AtomBase& a, const Script::WorldState& ws);
	bool PostInitialize();
	bool ImageInitialize(bool is_win_fbo, Size screen_sz);
	
	Buffer& GetBuffer() {return buf;}
	bool AcceptsOrder() const {return buf.AcceptsOrders();}
	//bool AcceptsOrder() const {return is_user_shader || shdr_frag_name.GetCount();}
	void Update(double dt) {buf.Update(dt);}
	
	bool IsAudio() const {return buf.IsAudio();}
	
};


NAMESPACE_PARALLEL_END

#endif
