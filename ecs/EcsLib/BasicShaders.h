#ifndef _EcsLib_BasicShaders_h_
#define _EcsLib_BasicShaders_h_

#if 0

NAMESPACE_OULU_BEGIN




struct MinimalCameraShader : public Component<MinimalCameraShader>, public ShaderSink {
	IFACE_CB(ShaderSink)
	
	struct Shader : public IShader {
		mat4 perspective, vport;
		int iter = 0;
		static const int iter_limit = 100;
		
		Shader();
		void NativeShaderProcess(CpuPipelineThreadData& thrd) override;
		ShaderMode GetMode() override {return SHDRMODE_COMPUTE;}
		String ToString() override {return "MinimalCameraShader";}
	};
	
	
	MinimalCameraShader();
	void operator=(const MinimalCameraShader& s) {}
	
	bool AddToPipeline(Pipeline& pipe) override;
	
};

struct MinimalVertexLoaderShader : public Component<MinimalVertexLoaderShader>, public ShaderSink {
	IFACE_CB(ShaderSink)
	
	struct Shader : public IShader {
		void NativeShaderProcess(CpuPipelineThreadData& thrd) override;
		
		ShaderMode GetMode() override {return SHDRMODE_MESH_VERTEX;}
		String ToString() override {return "MinimalVertexLoaderShader";}
		
	};
	
	
	MinimalVertexLoaderShader();
	void operator=(const MinimalVertexLoaderShader& s) {}
	
	bool AddToPipeline(Pipeline& pipe) override;
	
};

struct MinimalVertexShader : public Component<MinimalVertexShader>, public ShaderSink {
	IFACE_CB(ShaderSink)
	
	struct Shader : public IShader {
		void NativeShaderProcess(CpuPipelineThreadData& thrd) override;
		
		ShaderMode GetMode() override {return SHDRMODE_VERTEX;}
		String ToString() override {return "MinimalVertexShader";}
		
	};
	
	
	MinimalVertexShader();
	void operator=(const MinimalVertexShader& s) {}
	
	bool AddToPipeline(Pipeline& pipe) override;
	
	
};


// opengl: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/gl_FragDepth.xhtml
struct MinimalDepthShader : public Component<MinimalDepthShader>, public ShaderSink {
	IFACE_CB(ShaderSink)
	
	struct Shader : public IShader {
		void NativeShaderProcess(CpuPipelineThreadData& thrd) override;
		
		ShaderMode GetMode() override {return SHDRMODE_TRIANGLE;}
		String ToString() override {return "MinimalDepthShader";}
		
	};
	
	
	MinimalDepthShader();
	void operator=(const MinimalDepthShader& s) {}
	
	bool AddToPipeline(Pipeline& pipe) override;
	
};

struct MinimalFragmentShader : public Component<MinimalFragmentShader>, public ShaderSink {
	
	IFACE_CB(ShaderSink)
	
	struct Shader : public IShader {
		enum {DEPTH, FLAT, GOURAUD, NORMAL, PHONG};
		int mode = PHONG;
		
		void NativeShaderProcess(CpuPipelineThreadData& thrd) override;
		
		ShaderMode GetMode() override {return SHDRMODE_FRAGMENT;}
		String ToString() override {return "MinimalFragmentShader";}
	};
	
	
	MinimalFragmentShader();
	void operator=(const MinimalFragmentShader& s) {}
	
	bool AddToPipeline(Pipeline& pipe) override;
	
};











struct BasicPipeline : EntityPrefab<
	PipelineComponent,
		MinimalCameraShader,
		MinimalVertexLoaderShader,
		MinimalDepthShader,
		MinimalVertexShader,
		MinimalFragmentShader,
	PipelineDataComponent,
	Connector>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);
		return components;
    }
};

struct OctreeEditPipeline : EntityPrefab<
	PipelineComponent,
		MinimalCameraShader,
		OctreeVertexLoaderShader,
		MinimalDepthShader,
		MinimalVertexShader,
		OctreeFragmentShader,
	PipelineDataComponent,
	Connector>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);
		return components;
    }
};




struct OctreeGround : EntityPrefab<OctreeComponent>
{
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);
		return components;
    }
};

NAMESPACE_OULU_END

#endif
#endif
