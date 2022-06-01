#ifndef _IGraphics_ObjViewProg_h_
#define _IGraphics_ObjViewProg_h_


NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class ObjViewVertexT : public SoftShaderBaseT<Gfx> {
	
public:
	void Process(VertexShaderArgsT<Gfx>& args) override;
	
};

template <class Gfx>
class ObjViewFragmentT : public SoftShaderBaseT<Gfx> {
	
public:
	void Process(FragmentShaderArgsT<Gfx>& args) override;
	
};

template <class Gfx>
struct ObjViewProgT :
	public BinderIfaceVideo
{
	RTTI_DECL1(ObjViewProgT, BinderIfaceVideo)
	
	ModelLoader loader;
	String obj, tex;
	TimeStop ts;
	double phase_time = 1.5;
	int iter = 0;
	int frame = 0;
	int phase = 0;
	int phases = 2;
	int width, height;
	bool use_pbr = false;
	
	ObjViewProgT();
	void operator=(const ObjViewProgT& t) {Panic("Can't copy ObjViewProgT");}
	void Visit(RuntimeVisitor& vis) override {vis % loader;}
	void Initialize() override;
	bool Render(Draw& draw) override;
	bool Arg(const String& key, const String& value) override;
	
	void DrawObj(StateDrawT<Gfx>& fb, bool use_texture);
	
};


NAMESPACE_PARALLEL_END


#endif
