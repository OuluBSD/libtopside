#ifndef _EcsLib_PathTracer_h_
#define _EcsLib_PathTracer_h_

#if 0

NAMESPACE_OULU_BEGIN


/*struct RaymarchFragmentShader : public Component<RaymarchFragmentShader>, public ShaderSink {
	
	IFACE_CB(ShaderSink)
	
	struct Shader : public IShader {
		enum {DEPTH, FLAT, GOURAUD, NORMAL, PHONG};
		int mode = PHONG;
		
		void NativeShaderProcess(CpuPipelineThreadData& thrd) override;
		
		ShaderMode GetMode() override {return SHDRMODE_FRAGMENT;}
		String ToString() override {return "RaymarchFragmentShader";}
	};
	
	
	RaymarchFragmentShader();
	void operator=(const RaymarchFragmentShader& s) {}
	
	bool AddToPipeline(Pipeline& pipe) override;
	
};*/


NAMESPACE_OULU_END

#endif
#endif
