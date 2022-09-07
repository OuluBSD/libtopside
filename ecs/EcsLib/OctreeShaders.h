#ifndef _EcsLib_Octree_h_
#define _EcsLib_Octree_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN


struct OctreeVertexLoaderShader : public Component<OctreeVertexLoaderShader>, public ShaderSink {
	IFACE_CB(ShaderSink)
	
	struct Shader : public IShader {
		void NativeShaderProcess(CpuPipelineThreadData& thrd) override;
		
		ShaderMode GetMode() override {return SHDRMODE_MESH_VERTEX;}
		String ToString() override {return "OctreeVertexLoaderShader";}
		
	};
	
	
	OctreeVertexLoaderShader();
	void operator=(const OctreeVertexLoaderShader& s) {}
	
	bool AddToPipeline(Pipeline& pipe) override;
	
};



struct OctreeFragmentShader : public Component<OctreeFragmentShader>, public ShaderSink {
	
	IFACE_CB(ShaderSink)
	
	struct Shader : public IShader {
		enum {DEPTH, FLAT, GOURAUD, NORMAL, PHONG};
		int mode = PHONG;
		
		void NativeShaderProcess(CpuPipelineThreadData& thrd) override;
		
		ShaderMode GetMode() override {return SHDRMODE_FRAGMENT;}
		String ToString() override {return "OctreeFragmentShader";}
	};
	
	
	OctreeFragmentShader();
	void operator=(const OctreeFragmentShader& s) {}
	
	bool AddToPipeline(Pipeline& pipe) override;
	
};


NAMESPACE_TOPSIDE_END

#endif
#endif
