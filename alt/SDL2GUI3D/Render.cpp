#include <SerialLib/SerialLib.h>
#include "After.h"

NAMESPACE_UPP
using namespace TS;


#if 0

void SDL2GUI3D::Render(bool do_render) {
	if (data->ents.IsEmpty())
		data->ents = GetMachine().Get<EntityStore>();
	
	Vector<Tuple<Entity*, Transform2D*, CoreWindow*>> wins = data->ents->GetComponentsWithEntity<Transform2D, CoreWindow>();
	Windows* windows = Ctrl::GetWindows();
	
	for(int i = 0; i < wins.GetCount(); i++) {
		Tuple<Entity*, Transform2D*, CoreWindow*>& tuple = wins[i];
		Transform2D& t = *tuple.b.a;
		CoreWindow& cw = *tuple.b.b.a;
		
		if (cw.GetId() < 0)
			windows->AddWindow(cw);
		
		Rect r = cw.GetFrameRect();
		Size t_size = ToSize(t.size);
		Point t_pos = ToPoint(t.position);
		if (r.Width()  != t_size.cx ||
			r.Height() != t_size.cy ||
			r.left     != t_pos.x ||
			r.top      != t_pos.y) {
			r.left = t_pos.x;
			r.top = t_pos.y;
			r.right = r.left + t_size.cx;
			r.bottom = r.top + t_size.cy;
			cw.SetFrameRect0(r);
		}
		
		if (cw.IsPendingLayout()) {
			cw.DeepLayout();
			cw.SetPendingEffectRedraw();
		}
		
		do_render = cw.Redraw(true) || do_render;
	}
	
	Vector<Tuple<Entity*, Transform*, Renderable*>> rends = data->ents->GetComponentsWithEntity<Transform, Renderable>();
	if (rends.GetCount())
		do_render = true;
	
	if (do_render) {
		RenderFrame();
	}
	
	//Panic("");
}

void SDL2GUI3D::RenderFrame() {
	
	/*if (data->cam.IsEmpty()) {
		Vector<Tuple<Entity*, Viewable*>> wins = data->ents->GetComponentsWithEntity<Viewable>();
		
		for(int i = 0; i < wins.GetCount(); i++) {
			Tuple<Entity*, Viewable*>& tuple = wins[i];
			ASSERT(tuple.a->HasWeak());
			data->cam = tuple.a->GetSharedFromThis();
			break;
		}
	}
	
	if (data->cam.IsEmpty()) return;
	
	glEnable(GL_DEPTH_TEST);
	RenderCamera();
	
	RenderWindows();*/
	
}




void SDL2GUI3D::RenderWindows() {
	
	glDisable(GL_DEPTH_TEST);
	
	Transform& t = *data->cam->Get<Transform>();
	Viewable& c = *data->cam->Get<Viewable>();
	
	int width = screen_sz.cx;
	int height = screen_sz.cy;
	mat4 projection = ortho(-width, width, -height, height, -1024.0f, 1024.0f);
    simple_shader.SetMat4("projection", projection);
    
    mat4 view = LookAt(vec3(0.0f, 0.0f, -1.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f, 1.0f, 0.0f));
	simple_shader.SetMat4("view", view);
    
    mat4 ident = identity<mat4>();
    simple_shader.SetMat4("model", ident);
	
	Vector<Tuple<Entity*, Transform2D*, CoreWindow*>> wins = data->ents->GetComponentsWithEntity<Transform2D, CoreWindow>();
	
	for(int i = 0; i < wins.GetCount(); i++) {
		Tuple<Entity*, Transform2D*, CoreWindow*>& tuple = wins[i];
		Transform2D& t = *tuple.b.a;
		CoreWindow& cw = *tuple.b.b.a;
		
		Rect r = cw.GetFrameRect();
		Size t_size = ToSize(t.size);
		Point t_pos = ToPoint(t.position);
		const Framebuffer& fb = cw.GetFramebuffer();
		Size sz = fb.GetSize();
		
		int x0 = width - (t_pos.x) * 2 - (t_size.cx) * 2;
		int y0 = height - (t_pos.y) * 2 - (t_size.cy) * 2;
		int x1 = x0 + t_size.cx * 2;
		int y1 = y0 + t_size.cy * 2;
		
		ModelMesh model;
		Mesh& mesh = model.meshes.Add();
		mesh.vertices.Reserve(4);
		mesh.vertices.Add().Set(x0, y0, 0, 0, 1);
		mesh.vertices.Add().Set(x0, y1, 0, 0, 0);
		mesh.vertices.Add().Set(x1, y1, 0, 1, 0);
		mesh.vertices.Add().Set(x1, y0, 0, 1, 1);
		Texture& tex = model.textures.Add();
		tex.width = sz.cx;
		tex.height = sz.cy;
		tex.tex_id = fb.GetTexture();
		mesh.tex_id[TEXTYPE_DIFFUSE] = 0;
		//mesh.textures.Add().img = GetTextureImage(0);
		mesh.indices.Reserve(6);
		mesh.indices.Add(1);
		mesh.indices.Add(2);
		mesh.indices.Add(0);
		mesh.indices.Add(0);
		mesh.indices.Add(2);
		mesh.indices.Add(3);
		mesh.SetupMesh();
		simple_shader.Paint(model);
	}
	
	
}

#endif














END_UPP_NAMESPACE
