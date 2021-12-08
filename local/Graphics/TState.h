#ifndef _Graphics_TState_h_
#define _Graphics_TState_h_

NAMESPACE_TOPSIDE_BEGIN

template <class Gfx> struct DataStateT;

template <class Gfx>
struct DataObjectT : GfxDataObject {
	using Base = DataObjectT<Gfx>;
	RTTI_DECL1(DataObjectT, GfxDataObject)
	
	using DataState = typename Gfx::DataState;
	using NatTex = typename Gfx::NativeTexture;
	using NatVertexArray = typename Gfx::NativeVertexArray;
	using NatVertexBuffer = typename Gfx::NativeVertexBuffer;
	using NatElementBuffer = typename Gfx::NativeElementBuffer;
	using DataStateBase = DataStateT<Gfx>;
	
	DataStateBase* state = 0;
	VectorMap<int,NatTex> tex;
	uint32 element_count = 0;
	NatVertexArray vao;
	NatVertexBuffer vbo;
	NatElementBuffer ebo;
	
    mat4 view;
    mat4 proj;
    mat4 scale;
    mat4 model;
    bool is_global_view = false;
    int id = -1;
	
	
	DataObjectT() {
		vao = Null;
		vbo = Null;
		ebo = Null;
	}
	
	void SetState(DataStateBase* state) {this->state = state;}
	void Refresh(Mesh& m) override {TODO}
    virtual ShaderVar::GfxType GetGfxType() const override {return Gfx::type;}
	
};

template <class Gfx>
struct DataStateT : GfxDataState {
	RTTI_DECL1(DataStateT, GfxDataState)
	using Base = DataStateT<Gfx>;
	using NatColorBuf = typename Gfx::NativeColorBuffer;
	using NatDepthBuf = typename Gfx::NativeDepthBuffer;
	using NatFrameBuf = typename Gfx::NativeFrameBuffer;
	using NatProgram  = typename Gfx::NativeProgram;
	using NatPipeline = typename Gfx::NativePipeline;
	using NatShader = typename Gfx::NativeShader;
	using ShaderState = typename Gfx::ShaderState;
	using InputState = typename Gfx::InputState;
	using DataObject = typename Gfx::DataObject;
	using Framebuffer = typename Gfx::FramebufferState;
	
	
	Array<DataObject> objects;
	
	
	DataStateT() {
		
	}
	
	GfxDataObject& CreateObject() override {
		DataObject* p = new DataObject();
		p->SetState(this);
		objects.Add(p);
		p->id = objects.GetCount() - 1;
		RendVer1(OnRealizeObject, p->id);
		return *p;
	}

};

template <class Gfx>
struct StateDrawT : GfxStateDraw {
	RTTI_DECL1(StateDrawT, GfxStateDraw)
	using Base = StateDrawT<Gfx>;
	
	
	
};



NAMESPACE_TOPSIDE_END

#endif
