#include "IGraphics.h"

#if 0

NAMESPACE_PARALLEL_BEGIN


ModelProg::ModelProg() {
	
}
	
void ModelProg::Process(FramebufferState& state, const DrawCommand* ptr) {
	typedef void (ModelProg::*FnPtr)(const DrawCommand&);
	static FnPtr ptrs[DRAW_CMD_COUNT];
	static bool has_ptrs;
	if (!has_ptrs) {
		ptrs[DRAW_LINE] = &ModelProg::DrawLine;
		ptrs[DRAW_IMAGE] = &ModelProg::DrawImage;
		ptrs[DRAW_RECT] = &ModelProg::DrawRect;
		ptrs[DRAW_TRIANGLES] = &ModelProg::DrawTriangles;
		ptrs[DRAW_POLYLINE] = &ModelProg::DrawPolyline;
		ptrs[DRAW_OFFSET] = &ModelProg::DrawOffset;
		ptrs[DRAW_END] = &ModelProg::DrawEnd;
		has_ptrs = true;
	}
	
	this->state = &state;
	this->sz = state.size;
	model.Clear();
	const DrawCommand* cmd = ptr;
	while (cmd) {
		if (cmd->type > DRAW_NULL && cmd->type < DRAW_CMD_COUNT)
			(*this.*ptrs[cmd->type])(*cmd);
		
		ASSERT(cmd->next != cmd);
		cmd = cmd->next;
	}
}

void ModelProg::DrawLine(const DrawCommand& cmd) {
	int width = sz.cx;
	int height = sz.cy;
	int pos_x0 = cmd.i[0];
	int pos_y0 = cmd.i[1];
	int pos_x1 = cmd.i[2];
	int pos_y1 = cmd.i[3];
	float x0 = -width * 0.5 + pos_x0;
	float y0 = -height * 0.5 + pos_y0;
	float x1 = -width * 0.5 + pos_x1;
	float y1 = -height * 0.5 + pos_y1;
	
	
	Mesh& mesh = model.meshes.Add();
	mesh.vertices.Reserve(2);
	mesh.vertices.Add().Set(x0, y0, 0, 0, 1);
	mesh.vertices.Add().Set(x1, y1, 0, 1, 0);
	ColorCopy(cmd.clr, mesh.material.ambient);
	//mesh.material.ambient.a = cmd.clr.a;
	mesh.is_colored_only = true;
	mesh.is_lines = true;
	mesh.indices.Reserve(2);
	mesh.indices.Add(0);
	mesh.indices.Add(1);
	mesh.Refresh(state->CreateObject());
}

void ModelProg::DrawImage(const DrawCommand& cmd) {
	int width = sz.cx;
	int height = sz.cy;
	int pos_x = cmd.i[0];
	int pos_y = cmd.i[1];
	int scale_x = cmd.img.GetWidth();
	int scale_y = cmd.img.GetHeight();
	float x0 = -width * 0.5 + pos_x + scale_x;
	float y0 = -height * 0.5 + pos_y + scale_y;
	float x1 = x0 - scale_x;
	float y1 = y0 - scale_y;
	
	Model model;
	Mesh& mesh = model.meshes.Add();
	mesh.vertices.Reserve(4);
	mesh.vertices.Add().Set(x0, y0, 0, 1, 1);
	mesh.vertices.Add().Set(x0, y1, 0, 1, 0);
	mesh.vertices.Add().Set(x1, y1, 0, 0, 0);
	mesh.vertices.Add().Set(x1, y0, 0, 0, 1);
	model.textures.Add().Set(cmd.img);
	//if (GetTextureImageCount()) mesh.textures.Add().img = GetTextureImage(0);
	mesh.is_colored_only = false;
	mesh.indices.Reserve(6);
	mesh.indices.Add(0);
	mesh.indices.Add(1);
	mesh.indices.Add(2);
	mesh.indices.Add(0);
	mesh.indices.Add(2);
	mesh.indices.Add(3);
	mesh.Refresh(state->CreateObject());
}

void ModelProg::DrawRect(const DrawCommand& cmd) {
	int width = sz.cx;
	int height = sz.cy;
	int pos_x = cmd.i[0];
	int pos_y = cmd.i[1];
	int scale_x = cmd.i[2] - pos_x;
	int scale_y = cmd.i[3] - pos_y;
	float x0 = -width * 0.5 + pos_x + scale_x;
	float y0 = -height * 0.5 + pos_y + scale_y;
	float x1 = x0 - scale_x;
	float y1 = y0 - scale_y;
	
	Model model;
	Mesh& mesh = model.meshes.Add();
	mesh.vertices.Reserve(4);
	mesh.vertices.Add().Set(x0, y0, 0, 0, 1);
	mesh.vertices.Add().Set(x0, y1, 0, 0, 0);
	mesh.vertices.Add().Set(x1, y1, 0, 1, 0);
	mesh.vertices.Add().Set(x1, y0, 0, 1, 1);
	//model.textures.Add().tex = tex;
	//if (GetTextureImageCount()) model.textures.Add().img = GetTextureImage(0);
	ColorCopy(cmd.clr, mesh.material.ambient);
	//mesh.material.ambient.a = cmd.clr.a;
	mesh.is_colored_only = true;
	mesh.indices.Reserve(6);
	mesh.indices.Add(0);
	mesh.indices.Add(1);
	mesh.indices.Add(2);
	mesh.indices.Add(0);
	mesh.indices.Add(2);
	mesh.indices.Add(3);
	mesh.Refresh(state->CreateObject());
}

void ModelProg::DrawTriangles(const DrawCommand& cmd) {
	int width = sz.cx;
	int height = sz.cy;
	
	const Trif* tri = cmd.triangles.GetData();
	int count = cmd.triangles.GetCount();
	Model model;
	Mesh& mesh = model.meshes.Add();
	mesh.vertices.Reserve(count * 3);
	mesh.indices.Reserve(count * 3);
	
	
	for(int i = 0; i < count; i++) {
		const Trif& t = *tri++;
		float pos_x = t.a.x;
		float pos_y = t.a.y;
		float x = -width  * 0.5 + pos_x;
		float y = -height * 0.5 + pos_y;
		mesh.indices.Add(mesh.vertices.GetCount());
		mesh.vertices.Add().Set(x, y, 0, 0, 1);
		
		pos_x = t.c.x;
		pos_y = t.c.y;
		x = -width  * 0.5 + pos_x;
		y = -height * 0.5 + pos_y;
		mesh.indices.Add(mesh.vertices.GetCount());
		mesh.vertices.Add().Set(x, y, 0, 1, 1);
		
		pos_x = t.b.x;
		pos_y = t.b.y;
		x = -width  * 0.5 + pos_x;
		y = -height * 0.5 + pos_y;
		mesh.indices.Add(mesh.vertices.GetCount());
		mesh.vertices.Add().Set(x, y, 0, 1, 0);
		
	}
	ColorCopy(cmd.clr, mesh.material.ambient);
	//mesh.material.ambient.a = cmd.clr.a;
	mesh.is_colored_only = true;
	mesh.Refresh(state->CreateObject());
}

void ModelProg::DrawPolyline(const DrawCommand& cmd) {
	int width = sz.cx;
	int height = sz.cy;
	
	Model model;
	Mesh& mesh = model.meshes.Add();
	mesh.vertices.Reserve(2);
	const Point *a = &cmd.pts[0];
	for(int i = 0; i < cmd.pts.GetCount(); i++, a++) {
		float pos_x = a->x;
		float pos_y = a->y;
		float x = -width * 0.5 + pos_x;
		float y = -height * 0.5 + pos_y;
		mesh.vertices.Add().Set(x, y, 0, 0, 1);
		if (i) {
			mesh.indices.Add(i-1);
			mesh.indices.Add(i);
		}
	}
	ColorCopy(cmd.clr, mesh.material.ambient);
	//mesh.material.ambient.a = cmd.clr.a;
	mesh.is_colored_only = true;
	mesh.is_lines = true;
	mesh.Refresh(state->CreateObject());
}

void ModelProg::DrawOffset(const DrawCommand& cmd) {
	mat4& next = offset.Add();
	mat4& prev = offset[offset.GetCount()-2];
	float x = cmd.i[0];
	float y = cmd.i[1];
	next = Translate(prev, vec3(x, y, 0));
	TODO //shader.SetMat4("offset", next);
}

void ModelProg::DrawEnd(const DrawCommand& cmd) {
	offset.Pop();
	TODO //shader.SetMat4("offset", offset.Top());
}



NAMESPACE_PARALLEL_END
#endif
