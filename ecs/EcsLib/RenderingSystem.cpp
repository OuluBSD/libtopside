#include "EcsLib.h"


#if 0

NAMESPACE_TOPSIDE_BEGIN


#if 0


RenderingSystem::RenderingSystem(Machine& m) : RefScopeParent<RefParent1<Machine>>(m) {
	invalid = 0;
	vscreen_sz = Size(800,600);
}

bool RenderingSystem::Initialize() {
	
	return true;
}

void RenderingSystem::Start() {
	ents = GetMachine().Get<EntityStore>();
}

void RenderingSystem::Update(double dt) {

	for (DisplaySourceRef src : srcs) {
		DisplayStream& stream = src->GetStream(DisCtx);
		int buf_sz = stream.GetDisplay().GetQueueSize();
		bool buffer_full = buf_sz >= 2;
		
		src->Update(dt, buffer_full);
		if (src->Cfg().render) {
			#if DEBUG_DISPLAY_PIPE
			DISPLAYLOG("begin source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->BeginStream(DisCtx);
		}
	}
	
	for (DisplayExchangePointRef expt : expts) {
		DisplaySourceRef src = expt->Source();
		off32 begin_offset = expt->GetOffset();
		
		expt->SetOffset(begin_offset);
		expt->Update(dt);
		
		off32 end_offset = expt->GetOffset();
		src->SetOffset(begin_offset, end_offset);
		
		#if DEBUG_DISPLAY_PIPE
		off32 diff = off32::GetDifference(begin_offset, end_offset);
		if (diff) {
			auto sink = expt->Sink();
			DISPLAYLOG("sink " << HexStr((size_t)&*sink) << "<" << sink->GetConfigString() << "> consumed " << diff.ToString());
		}
		#endif
	}
	
	for (DisplaySourceRef src :srcs) {
		const auto& cfg = src->Cfg();
		if (cfg.begin_offset != cfg.end_offset) {
			#if DEBUG_DISPLAY_PIPE
			DISPLAYLOG("end source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->EndStream(DisCtx);
		}
	}
}

void RenderingSystem::Stop() {
	
}

void RenderingSystem::Uninitialize() {
	
	//Close();
	
}

void RenderingSystem::Add(DisplaySourceRef src) {
	srcs.FindAdd(src);
	
	Ref<RegistrySystem> reg = GetMachine().TryGet<RegistrySystem>();
	if (reg)
		src->SetTitle(reg->GetAppName());
}

void RenderingSystem::Remove(DisplaySourceRef src) {
	srcs.RemoveKey(src);
}

void RenderingSystem::Add(DisplaySinkRef r) {
	sinks.FindAdd(src);
}

void RenderingSystem::Add(DisplayExchangePointRef r) {
	expts.FindAdd(src);
}

void RenderingSystem::Remove(DisplaySinkRef r) {
	sinks.RemoveKey(src);
}

void RenderingSystem::Remove(DisplayExchangePointRef r) {
	expts.RemoveKey(src);
}







#if defined flagGUI

DefaultRenderApp::DefaultRenderApp() {
	
}

void DefaultRenderApp::Initialize() {
	// Load shaders
	simple_shader = Shader::NewDefault();
	//simple_shader->Load(FindLocalFile("shaders" DIR_SEPS "model_loading.vs"), FindLocalFile("shaders" DIR_SEPS "model_loading.fs"));
	
	AddToSystem<DisplaySystem>(AsRef<DisplaySource>());
}

void DefaultRenderApp::Uninitialize() {
	RemoveFromSystem<DisplaySystem>(AsRef<DisplaySource>());
	
}

DisplayStream& DefaultRenderApp::GetStream(DisCtx) {
	TODO
}

void DefaultRenderApp::BeginStream(DisCtx) {
	TODO
}

void DefaultRenderApp::EndStream(DisCtx) {
	TODO
}

#if 0
bool DefaultRenderApp::Render(const DisplaySinkConfig& config, SystemDraw& draw) {
	double delta_time = config.dt;
	
	bool needs_fast_rerender = false;
	
	if (ents.IsEmpty()) {
		ents = GetMachine().TryGet<EntityStore>();
		if (!ents) return !needs_fast_rerender;
	}
	
	/*glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_MULTISAMPLE);*/
	
	FramebufferDraw* fb_draw = dynamic_cast<FramebufferDraw*>(draw.ptr);
	if (!fb_draw)
		return !needs_fast_rerender;
	/*Framebuffer* fb = fb_draw->GetFramebuffer();
	if (!fb)
		return;*/
	/*Camera* cam = fb_draw->GetCamera();
	if (!cam)
		return;*/
	const auto& cams = HumanSource::GetConnections();
	
	if (cams.IsEmpty())
		return !needs_fast_rerender;
	
	CameraSinkRef cam_out = cams.begin()()->AsRef<CameraSink>();
	Camerable* cam = cam_out.GetCamerable();
	Transform* trans = cam_out.GetTransform();
	if (!cam || !trans)
		return !needs_fast_rerender;
	
	Size sz = draw.GetPageSize();
	
	//Vector<Tuple<Entity*, Transform*, Renderable*>> rends = ents->GetComponentsWithEntity<Transform, Renderable>();
	rends.SetCount(0);
	/*const auto& models = ModelSource::GetSinks();
	for(ModelSink* out : models) {
		out->GetModels(rends);
	}*/
	
	Shader& shader = *simple_shader;
	shader.Use();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);
    
    mat4 projection = perspective(GetRadians(100.0f), (float)sz.cx / (float)sz.cy, 0.1f, 100.0f);
    shader.SetMat4("projection", projection);
    
    // camera/view transformation
	mat4 view = LookAt(trans->position, cam->target, vec3(0.0f, 1.0f, 0.0f));
    shader.SetMat4("view", view);
    
    
    // render the loaded model
    /*mat4 model = mat4(1.0f);
    model = translate(model, vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
    model = scale(model, vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
    float a = delta_time * 0.1 * 360 / (2 * M_PI);
    model = rotate(model, a, vec3(0.25, 1.0, 0));
    shader.SetMat4("model", model);*/
    //RenderFrame();
	
    
	for(RendModel& tuple : rends) {
		Model* m = tuple.a;
		Transform* t = tuple.b.a;
		Renderable* r = tuple.b.b.a;
		
		if (t && m) {
			mat4 mat = t->GetMatrix();
			shader.SetMat4("model", mat);
			shader.SetStackMat4(mat);
			shader.Paint(*m);
		}
		else if (r && r->cb) {
			r->cb.Execute(shader);
		}
		else {
			LOG("error: invalid RendModel output");
			/*mat4 mat = t.GetMatrix();
			shader.SetMat4("model", mat);
			shader.SetStackMat4(mat);
			
			if (r.model.IsEmpty()) {
				if (r.model_name.GetCount()) {
					LOG("Load model " << r.model_name);
					r.model.Create();
					if (r.model_name == "UnitCube") {
						r.model->LoadModel(FindLocalFile("models" DIR_SEPS "cube.obj"));
					}
					else if (r.model_name == "Gun") {
						r.model->LoadModel(FindLocalFile("models" DIR_SEPS "Gun.glb"));
					}
					else if (r.model_name == "Baseball") {
						r.model->LoadModel(FindLocalFile("models" DIR_SEPS "Baseball.glb"));
					}
					else if (r.model_name == "PaintBrush") {
						r.model->LoadModel(FindLocalFile("models" DIR_SEPS "PaintBrush.glb"));
					}
					else {
						LOG("Unhandled model name " + r.model_name);
						r.model->LoadModel(FindLocalFile("models" DIR_SEPS "cube.obj"));
					}
				}
				else {
					r.model.Create();
					r.model->LoadModel(FindLocalFile("models" DIR_SEPS "cube.obj"));
				}
			}
			
			shader.Paint(*r.GetModel());*/
		}
	}
	
	//glDisable(GL_TEXTURE_2D);
	
	return !needs_fast_rerender;
}
#endif

#endif
#endif

NAMESPACE_TOPSIDE_END


#endif
