#include "GL.h"

#if 0


/*
Info:
	- pipelines
		- opengl	https://www.khronos.org/opengl/wiki/Rendering_Pipeline_Overview
		- turing	https://developer.nvidia.com/blog/introduction-turing-mesh-shaders/
		- dx11		https://docs.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-graphics-pipeline
		- dx12		https://docs.microsoft.com/en-us/windows/win32/direct3d12/pipelines-and-shaders-with-directx-12
		- vulkan	https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Introduction
	
Parts:
	
	->ProcessDynamics
	->ProcessShaders
	->AssemblePrimitives
	
	
	ProcessDynamics (Compute Shaders)
		Scenery
			Generation
		Physics
			WindTurbulence
			Objects
			Skeletons
		AI
			EntityLogic
		Sound
			ReverbIR
			SoundInstruments
			SoundEffects
			
	Graphics Pipeline
		(Mesh Shaders)
			SkeletonCulling
			SkeletonBoundingBox
			BoundingBox / Octree LOD
			BoundingBoxCulling
			SkeletonTransform
		(Task shader stage)
			(Tessellation Stage #1)
				PreTessellation (hidden triangle tessellation)
			(Vertex Shaders)
				Model, Perspective, Viewport, etc.
			(Rasterizer Stage #1)
				Depth + triangle orientation culling
		(Mesh shader stage #2)
			(Tessellation Stage #2)
				PostTessellation
			(Vertex Shaders)
			(Rasterizer Stage #2)
				Post Depth + ... culling for tesselated triangles
			(Rasterizer Stage #3)
				Transculent sorting
		(Geometry Shader)
		(Fragment Shaders)
		(Pixel Shaders)
		
Still missing:
	Volumetric stuff
	Lightning

*/


NAMESPACE_TOPSIDE_BEGIN

const char* def_arch = R"V0G0N(
{
	dynamics: {
		scenery: [],
		physics: [],
		ai: [],
		sound: {
			midi_src: [],
			audio_src: [],
			instrument_src: [],
			bus: {
				effects: [],
				output: [],
			}
		}
	},
	graphics: {
		compute: [],
		mesh: {
			skeleton_culling: [],
			skeleton_lod: [],
			skeleton_bbox: [],
			octree_culling: [],
			octree_lod: [],
			octree_bbox: [],
			culling: [],
			skeleton_transform: [],
		},
		vertex: [],
		depth_test: [],
		coarse: {
			tessellation_pre: [],
			rasterizer_pre: [],
		},
		fine: {
			tessellation_post: [],
			rasterizer_opaque: [],
			rasterizer_transculent: [],
		},
		geometry: [],
		fragment: [],
		pixel: [],
	}
}
)V0G0N";

Pipeline::Pipeline() {
	
	ParseStructureJson(def_arch);
	
}

void Pipeline::ParseStructureJson(String json) {
	Value v = ParseJSON(json);
	//LOG(GetValueTreeString(v, "pipeline structure"));
	
	SetStructure(v);
}

void Pipeline::SetStructure(Value v) {
	root.SetStructure(v);
}

void Pipeline::Process() {
	
	
	if (Begin()) {
		ProcessShaders();
	}
	
}

PipelineNode* Pipeline::FindNode(String path) {
	Vector<String> parts = Topside::Split(path, ".", false);
	PipelineNode* n = &root;
	for(const String& part : parts) {
		int i = n->branch.Find(part);
		if (i < 0) return NULL;
		n = &n->branch[i];
	}
	return n;
}






MeshView& ObjectView::CreateMesh() {
	return pline->CreateMesh(*this);
}



CpuPipeline::CpuPipeline() {
	
}

bool CpuPipeline::SetData(Shared<PipelineData> d) {
	pdata = d.As<CpuPipelineData>();
	return pdata;
}

ObjectView& CpuPipeline::CreateObject() {
	TODO
}

MeshView& CpuPipeline::CreateMesh(ObjectView& o) {
	TODO
}

bool CpuPipeline::Begin() {
	
	if (!pdata)
		return false;
	
	thrd.Clear();
	thrd.data = &*pdata;
	thrd.data->ResetThreads(1);
	thrd.data->Begin();
	thrd.thrd_i = 0;
	
	return true;
}

void CpuPipeline::ProcessShaders() {
	
	if (shaders_changed) {
		UpdateShaders();
		shaders_changed = false;
	}
	
	
	
	ProcessShaders(compute);
	ProcessShaders(coarse);
	//ProcessShaders(fine);
	ProcessShaders(geom);
	ProcessShaders(frag);
	
}

void CpuPipeline::ProcessShaders(Vector<IShader*>& v) {
	
	for(IShader* s: v) {
		thrd.ClearTemp();
		
		thrd.data->BeginStage();
		int stage_count = thrd.data->stages.GetCount();
		
		ShaderMode mode = s->GetMode();
		
		if (mode == SHDRMODE_COMPUTE) {
			s->NativeShaderProcess(thrd);
		}
		else if (mode == SHDRMODE_MESH_VERTEX) {
			int model_i = 0;
			for(Model& model: thrd.data->models.GetValues()) {
				int mesh_i = 0;
				for(Mesh& mesh: model.meshes) {
					thrd.model_i = model_i;
					thrd.mesh_i = mesh_i;
					
					s->NativeShaderProcess(thrd);
					
					mesh_i++;
				}
				model_i++;
			}
		}
		else if (mode == SHDRMODE_VERTEX) {
			//ASSERT_(stage_count >= 2, "You need at least one mesh vertex shader");
			//if (stage_count < 2) return;
			//int stage_i = stage_count-2;
			int stage_i = 0;
			auto& prev = thrd.data->stages[stage_i];
			uint32 vtx_count = prev.vert.GetCount();
			for(uint32 vtx_i = 0; vtx_i < vtx_count; vtx_i++) {
				thrd.vtx_offset = vtx_i;
				
				s->NativeShaderProcess(thrd);
			}
		}
		else if (mode == SHDRMODE_TRIANGLE) {
			int stage_i = 0;
			auto& cur = thrd.data->stages[stage_i];
			uint32 tri_count = cur.tri.GetCount();
			for(uint32 tri_i = 0; tri_i < tri_count; tri_i++) {
				thrd.tri_offset = tri_i;
				const auto& tri = cur.tri[tri_i];
				
				s->NativeShaderProcess(thrd);
			}
		}
		else if (mode == SHDRMODE_FRAGMENT) {
			int stage_i = 0;
			auto& cur = thrd.data->stages[stage_i];
			ASSERT(this->fb);
			
			thrd.fb = this->fb;
			thrd.fb->Enter();
			thrd.fb->Zero();
			
			const DepthBuffer& depth_buf = thrd.data->GetDepthBuffer();
			if (thrd.fb) {
				int w = thrd.fb->GetWidth();
				int h = thrd.fb->GetHeight();
				ASSERT(w == depth_buf.width && h == depth_buf.height);
				w = std::min(w, (int)depth_buf.width);
				h = std::min(h, (int)depth_buf.height);
				for(int y = 0; y < h; y++) {
					for(int x = 0; x < w; x++) {
						int pos = y * depth_buf.width + x;
						const DepthValue& dv = depth_buf.data[pos];
						if (dv.triangle_i >= 0) {
							thrd.tri_offset = dv.triangle_i;
							thrd.pos = vec3{(float)x, (float)y, (float)dv.depth};
							
							s->NativeShaderProcess(thrd);
							
							thrd.fb->DrawPixel(x, y, thrd.frag_color);
						}
					}
				}
			}
			
			thrd.fb->Leave();
		}
		else Panic("Invalid shadermode");
	}
}

void CpuPipeline::UpdateShaders() {
	{
		Vector<String> paths;
		paths.Add("graphics.compute");
		paths.Add("graphics.mesh.culling");
		UpdateShaderVector(paths, compute);
	}{
		Vector<String> paths;
		paths.Add("graphics.coarse.tessellation_pre");
		paths.Add("graphics.vertex");
		paths.Add("graphics.coarse.rasterizer_pre");
		UpdateShaderVector(paths, coarse);
	}{
		Vector<String> paths;
		paths.Add("graphics.fine.tessellation_post");
		paths.Add("graphics.vertex");
		paths.Add("graphics.fine.rasterizer_opaque");
		paths.Add("graphics.fine.rasterizer_transculent");
		UpdateShaderVector(paths, fine);
	}{
		Vector<String> paths;
		paths.Add("graphics.geometry");
		UpdateShaderVector(paths, geom);
	}{
		Vector<String> paths;
		paths.Add("graphics.fragment");
		paths.Add("graphics.pixel");
		UpdateShaderVector(paths, frag);
	}
}

void CpuPipeline::UpdateShaderVector(const Vector<String>& paths, Vector<IShader*>& out) {
	out.Clear();
	
	for(const String& p : paths) {
		PipelineNode* n	= FindNode(p);
		if (n)
			for(IShader& s : n->shaders)
				out.Add(&s);
		else {
			LOG("error: couldn't find shader path " << p);
		}
	}
	
	if (0) {
		for(int i = 0; i < out.GetCount(); i++) {
			LOG(i << ": " << out[i]->ToString());
		}
	}
}






void PipelineNode::SetStructure(Value v) {
	Clear();
	if (IsValueMap(v)) {
		ValueMap map = v;
		for(int i = 0; i < map.GetCount(); i++)
			Add(map.GetKey(i)).SetStructure(map.GetPos(i));
	}
}

void PipelineNode::Clear() {
	branch.Clear();
	shaders.Clear();
}

PipelineNode& PipelineNode::Add(String key) {
	auto& n = branch.Add(key);
	n.down = this;
	return n;
}





void CpuStage::UpdateView() {
	M = persp * lookat;
	MIT = M.GetInverseTransposed();
	M_light_dir = (M * light_dir.Embed()).Splice().Normalize();
	MIT_light_dir = (MIT * light_dir.Embed()).Splice().Normalize();
	view = vport * persp * lookat;
}

void CpuStage::operator=(const CpuStage& src) {
	tri <<= src.tri;
	vert <<= src.vert;
	ctx <<= src.ctx;
	
	vport = src.vport;
	lookat = src.lookat;
	persp = src.persp;
	view = src.view;
	light_dir = src.light_dir;
	
}

void CpuStage::Reset() {
	tri.SetCount(0);
	vert.SetCount(0);
	ctx.SetCount(0);
	
	vport.Clear();
	lookat.Clear();
	persp.Clear();
	view.Clear();
	light_dir = vec3{0, 0, -1};
	
	if (tri.GetAlloc() == 0){
		int verts = 10000;
		tri.Reserve(verts / 3);
		vert.Reserve(verts);
		ctx.Reserve(verts / 100);
	}
}

void CpuPipelineData::Begin() {
	if (depth_buf.IsEmpty())
		depth_buf.Create(Size(800,600)); // TODO connect output(s)
	else
		depth_buf.Reset();
	
	stages.Clear();
}

void CpuPipelineData::BeginStage() {
	if (stages.IsEmpty()) {
		CpuStage& stage = stages.Add();
		stage.Reset();
	}
}

int CpuPipelineData::PutModel(One<Model>& model, bool can_pick) {
	if (model.IsEmpty()) {
		LOG("error: CpuPipelineData::PutModel: empty model");
		return -1;
	}
	int id = model_counter++;
	if (can_pick)
		models.Add(id, model.Detach());
	else
		models.Add(id, new Model(*model));
	return id;
}







void CpuPipelineThreadData::TestSetDepth(DepthValue& buf_value, float depth) {
	if (buf_value.depth < depth) {
		buf_value.depth = depth;
		buf_value.triangle_i = tri_offset;
		//ASSERT(tri_offset < data->stages[0].tri.GetCount());
	}
}

NAMESPACE_TOPSIDE_END

#endif
