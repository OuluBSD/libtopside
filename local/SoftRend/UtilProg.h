#ifndef _IGraphics_UtilProg_h_
#define _IGraphics_UtilProg_h_

NAMESPACE_TOPSIDE_BEGIN



class PassVertex : public SoftShaderBase {
	
public:
	PassVertex();
	void Process(VertexShaderArgs& args) override;
	
};


class PassFragment : public SoftShaderBase {
	
public:
	void Process(FragmentShaderArgs& args) override;
	
};


class ColorTestFragment : public SoftShaderBase {
	
public:
	void Process(FragmentShaderArgs& args) override;
	
};


class ProxyInput0Fragment : public SoftShaderBase {
	
public:
	ProxyInput0Fragment();
	void Process(FragmentShaderArgs& args) override;
	
};


class StereoShader : public SoftShaderBase {
	
public:
	StereoShader();
	void Process(VertexShaderArgs& args) override;
	void Process(FragmentShaderArgs& args) override;
	
};


class ObjViewVertex : public SoftShaderBase {
	
public:
	ObjViewVertex();
	void Process(VertexShaderArgs& args) override;
	
};


class ObjViewFragment : public SoftShaderBase {
	
public:
	ObjViewFragment();
	void Process(FragmentShaderArgs& args) override;
	
};


NAMESPACE_TOPSIDE_END

#endif
