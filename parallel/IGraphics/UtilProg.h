#ifndef _IGraphics_UtilProg_h_
#define _IGraphics_UtilProg_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class PassVertexT : public SoftShaderBaseT<Gfx> {
	
public:
	void Process(VertexShaderArgsT<Gfx>& args) override;
	
};

template <class Gfx>
class PassFragmentT : public SoftShaderBaseT<Gfx> {
	
public:
	void Process(FragmentShaderArgsT<Gfx>& args) override;
	
};

template <class Gfx>
class ColorTestFragmentT : public SoftShaderBaseT<Gfx> {
	
public:
	void Process(FragmentShaderArgsT<Gfx>& args) override;
	
};

template <class Gfx>
class ProxyInput0FragmentT : public SoftShaderBaseT<Gfx> {
	
public:
	void Process(FragmentShaderArgsT<Gfx>& args) override;
	
};


NAMESPACE_PARALLEL_END

#endif
