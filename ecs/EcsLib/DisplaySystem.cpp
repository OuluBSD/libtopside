#include "EcsLib.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN

#if defined flagGUI

DefaultRenderApp::DefaultRenderApp() : dis_str(this), dis(this) {
	
}

// Component
void DefaultRenderApp::Initialize() {
	// Load shaders
	simple_shader = Shader::NewDefault();
	//simple_shader->Load(FindLocalFile("shaders" DIR_SEPS "model_loading.vs"), FindLocalFile("shaders" DIR_SEPS "model_loading.fs"));
	
	TODO
	//AddToSystem<DisplaySystem>(AsRef<DisplaySource>());
}

void DefaultRenderApp::Uninitialize() {
	//emoveFromSystem<DisplaySystem>(AsRef<DisplaySource>());
	
}

void DefaultRenderApp::Visit(RuntimeVisitor& vis) {
	TODO // rends ?
	vis & ents;
}

// DisplaySource
DisplayStream& DefaultRenderApp::GetStream(DisCtx) {
	return dis_str;
}

void DefaultRenderApp::BeginStream(DisCtx) {
	TODO
}

void DefaultRenderApp::EndStream(DisCtx) {
	TODO
}


// HumanSource
HumanStream& DefaultRenderApp::GetStream(HumCtx) {
	TODO
}

void DefaultRenderApp::BeginStream(HumCtx) {
	TODO
}

void DefaultRenderApp::EndStream(HumCtx) {
	TODO
}


void DefaultRenderApp::DefDisplay::StorePacket(DisplayPacket& p) {
	TODO
}

bool DefaultRenderApp::DefDisplayStream::Render(SystemDraw& draw) {
	return app.Render(draw);
}

bool DefaultRenderApp::Render(SystemDraw& draw) {
	//double delta_time = config.dt;
	
	bool needs_fast_rerender = false;
	
	if (ents.IsEmpty()) {
		ents = GetMachine().TryGet<EntityStore>();
		if (!ents) return !needs_fast_rerender;
	}
	
	/*glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_MULTISAMPLE);*/
	
	DrawFramebuffer* fb_draw = CastPtr<DrawFramebuffer>(draw.ptr);
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
	
	HumanSinkRef cam_out = cams.begin()().dst->AsRef<HumanSink>();
	
	TODO
	#if 0
	ViewableRef cam = cam_out->GetViewable();
	TransformRef trans = cam_out->GetTransform();
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
	mat4 view = LookAt(trans->position, cam->GetTarget(), vec3(0.0f, 1.0f, 0.0f));
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
		ModelMeshRef m = tuple.a;
		TransformRef t = tuple.b.a;
		RenderableRef r = tuple.b.b.a;
		
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
	#endif
	
	return !needs_fast_rerender;
}


#endif

NAMESPACE_TOPSIDE_END


#endif
