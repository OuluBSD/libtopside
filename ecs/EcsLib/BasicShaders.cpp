#include "EcsLib.h"

#if 0

NAMESPACE_OULU_BEGIN









MinimalCameraShader::MinimalCameraShader() {
	
	
}

bool MinimalCameraShader::AddToPipeline(Pipeline& pipe) {
	try {
		pipe.Create<MinimalCameraShader::Shader>("graphics.compute");
		return true;
	}
	catch (Exc e) {
		LOG("error: " << e);
		GetEntity().GetMachine().SetNotRunning();
	}
	return false;
}

MinimalCameraShader::Shader::Shader() {
	perspective[0] = vec4{1,		0,	    0,		0};
	perspective[1] = vec4{0,		1,	    0,		0};
	perspective[2] = vec4{0,		0,	    1,		0};
	perspective[3] = vec4{0,		0, -1./5.,		1};
	
	int w = 600, h = 600;
	vport = GetViewport(0, h, w, -h, 255);
}

void MinimalCameraShader::Shader::NativeShaderProcess(CpuPipelineThreadData& thrd) {
	CpuStage& stage = thrd.data->GetCurrentStage();
	
	float f = (float)iter++ / (float)iter_limit;
	float f2 = 1 - fabs(2 * f - 1);
	float angle = f * (2.0 * M_PI);
	float eye_angle = f /** 0.25*/ * M_2PI;
	float eye_x = cos(eye_angle);
	float eye_y = sin(eye_angle);
	vec3 eye {0.2f * eye_x, 0.3f * eye_y, 1};
	vec3 center {0, 0, 0};
	vec3 up {0, 1, 0};
	
	vec3 light {0.2f * eye_x + (float)(M_PI * 0.5), -0.3f * eye_y, 1};
	light.Normalize();
	
	
	stage.SetLookAt(LookAt(eye, center, up));
	stage.SetPerspective(perspective);
	stage.SetViewport(vport);
	stage.SetLightDirection(light);
	stage.UpdateView();
}















MinimalVertexLoaderShader::MinimalVertexLoaderShader() {
	
}

bool MinimalVertexLoaderShader::AddToPipeline(Pipeline& pipe) {
	try {
		pipe.Create<MinimalVertexLoaderShader::Shader>(GFX_MESH_CULLING);
		return true;
	}
	catch (Exc e) {
		LOG("error: " << e);
		GetEntity().GetMachine().SetNotRunning();
	}
	return false;
}

void MinimalVertexLoaderShader::Shader::NativeShaderProcess(CpuPipelineThreadData& thrd) {
	if (thrd.model_i < 0 || thrd.model_i >= thrd.data->models.GetCount())
		return;
	
	const Model& model = thrd.data->models[thrd.model_i];
	
	if (thrd.mesh_i < 0 || thrd.mesh_i >= model.meshes.GetCount())
		return;
	
	const Mesh& mesh = model.meshes[thrd.mesh_i];
	CpuStage& stage = thrd.data->GetCurrentStage();
	
	
	int tris = mesh.indices.GetCount() / 3;
	if (tris) {
		
		// Add context
		int ctx_id = stage.ctx.GetCount();
		auto& ctx = stage.ctx.Add();
		ctx.model_i = thrd.model_i;
		ctx.mesh_i = thrd.mesh_i;
		ctx.material = mesh.material;
		for(int i = 0; i < TEXTYPE_COUNT; i++)
			ctx.tex_id[i] = mesh.tex_id[i];
		
		// Add vertices
		uint32 vtx_offset =  stage.vert.GetCount();
		stage.vert.Append(mesh.vertices);
		
		// Add triangles
		stage.tri.Reserve(stage.tri.GetCount() + tris);
		uint32 tri_offset = stage.tri.GetCount();
		uint32* it = mesh.indices.Begin();
		uint32* end = it + tris * 3;
		vec2* tex_it = mesh.tex_coords.Begin();
		ASSERT(mesh.tex_coords.GetCount() == mesh.vertices.GetCount());
		
		while (it != end) {
			auto& tri = stage.tri.Add();
			tri.ctx_id = ctx_id;
			for(int i = 0; i < 3; i++) {
				tri.idx[i] = vtx_offset + it[i];
				tri.tex.SetColumn(i, *tex_it++);
			}
			tri.flags = 0;
			
			// TODO move after culling
			if (1) {
				vec3 world_coord[3];
				for(int i = 0; i < 3; i++)
					world_coord[i] = stage.vert[tri.idx[i]].position;
				tri.normal = (world_coord[1] - world_coord[0]) ^ (world_coord[2] - world_coord[0]);
				tri.normal.Normalize();
			}
			
			it += 3;
		}
		stage.tri[tri_offset + tris - 1].SetNextContext();
		
	}
	
}







MinimalVertexShader::MinimalVertexShader() {
	
}

bool MinimalVertexShader::AddToPipeline(Pipeline& pipe) {
	try {
		pipe.Create<MinimalVertexShader::Shader>("graphics.vertex");
		return true;
	}
	catch (Exc e) {
		LOG("error: " << e);
		GetEntity().GetMachine().SetNotRunning();
	}
	return false;
}

void MinimalVertexShader::Shader::NativeShaderProcess(CpuPipelineThreadData& thrd) {
	CpuStage& stage = thrd.data->GetCurrentStage();
	const mat4& view = stage.GetView();
	const Vertex& v = stage.GetVertexSource(thrd);
	vec4 vert4 {v.position[0], v.position[1], v.position[2], 1.0};
	vec4 screen_vert4 = view * vert4;
	auto& dst = stage.GetVertexDestination(thrd);
	dst.pos_project = screen_vert4[3];
	screen_vert4.Project();
	dst.position = screen_vert4.Splice();
}







MinimalDepthShader::MinimalDepthShader() {
	
}

bool MinimalDepthShader::AddToPipeline(Pipeline& pipe) {
	try {
		pipe.Create<MinimalDepthShader::Shader>("graphics.geometry");
		return true;
	}
	catch (Exc e) {
		LOG("error: " << e);
		GetEntity().GetMachine().SetNotRunning();
	}
	return false;
}

void MinimalDepthShader::Shader::NativeShaderProcess(CpuPipelineThreadData& thrd) {
	CpuStage& stage = thrd.data->GetCurrentStage();
	const mat4& view = stage.GetView();
	auto& tri = stage.GetTriangleDestination(thrd);
	DepthBuffer& zbuffer = thrd.data->GetDepthBuffer();
	int w = zbuffer.width;
	int h = zbuffer.height;
	
	
	vec3 vtx[3];
	for(int i = 0; i < 3; i++)
		vtx[i] = stage.GetTriangleVertex(tri, i).position;
	
	vec2 bboxmin(w - 1,  h - 1);
	vec2 bboxmax(0, 0);
	vec2 clamp(w - 1, h - 1);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			bboxmin[j] = std::max<int>(0.0,      std::min<int>(bboxmin[j], vtx[i][j]));
			bboxmax[j] = std::min<int>(clamp[j], std::max<int>(bboxmax[j], vtx[i][j]));
		}
	}
	
	vec2 P;
	for (P[0] = bboxmin[0]; P[0] <= bboxmax[0]; P[0]++) {
		for (P[1] = bboxmin[1]; P[1] <= bboxmax[1]; P[1]++) {
			vec3 bc_screen = GetBarycentric(vtx, P);
			if (bc_screen[0] < 0 || bc_screen[1] < 0 || bc_screen[2] < 0)
				continue;
			
			// calculate z-value
			float z = 0;
			for (int i = 0; i < 3; i++)
				z += vtx[i][2] * bc_screen[i];
			
			int pos = (int)P[0] + (int)P[1] * w;
			if (pos == 0) {
				pos = 0;
			}
			DepthValue& zvalue = zbuffer.data[pos];
			
			thrd.TestSetDepth(zvalue, z);
		}
	}
}







MinimalFragmentShader::MinimalFragmentShader() {
	
}

bool MinimalFragmentShader::AddToPipeline(Pipeline& pipe) {
	try {
		pipe.Create<MinimalFragmentShader::Shader>("graphics.fragment");
		return true;
	}
	catch (Exc e) {
		LOG("error: " << e);
		GetEntity().GetMachine().SetNotRunning();
	}
	return false;
}

void MinimalFragmentShader::Shader::NativeShaderProcess(CpuPipelineThreadData& thrd) {
	CpuStage& stage = thrd.data->GetCurrentStage();
	CpuStage::Triangle& tri = stage.tri[thrd.tri_offset];
	CpuStage::Context& ctx = stage.ctx[thrd.ctx_offset];
	Texture* tex_img = NULL;
	Texture* norm_img = NULL;
	Texture* spec_img = NULL;
	
	if (ctx.model_i >= 0 && ctx.mesh_i >= 0) {
		Model& model = thrd.data->models.Get(ctx.model_i);
		if (ctx.tex_id[TEXTYPE_DIFFUSE] >= 0)
			tex_img = &model.textures[ctx.tex_id[TEXTYPE_DIFFUSE]];
		if (ctx.tex_id[TEXTYPE_NORMALS] >= 0)
			norm_img = &model.textures[ctx.tex_id[TEXTYPE_NORMALS]];
		if (ctx.tex_id[TEXTYPE_SPECULAR] >= 0)
			spec_img = &model.textures[ctx.tex_id[TEXTYPE_SPECULAR]];
	}
	
	vec3 vtx[3];
	mat3 normal;
	mat3 MIT_normal;
	for(int i = 0; i < 3; i++) {
		const auto& v = stage.GetTriangleVertex(tri, i);
		vtx[i] = v.position;
		normal[i] = v.normal;
		MIT_normal.SetColumn(i, (stage.MIT * v.normal.Embed()).Splice());
	}
	vec2 P {thrd.pos[0], thrd.pos[1]};
	
	// For testing output
	if (0) {
		thrd.frag_color.a = 255;
		for(int i = 0; i < 3; i++)
			thrd.frag_color[i] = Random(256);
		return;
	}
	
	vec3 barycentric = GetBarycentric(vtx, P);
	ASSERT(barycentric[0] >= 0 && barycentric[1] >= 0 && barycentric[2] >= 0);
	
	
	vec3 bn = (MIT_normal * barycentric).Normalize();
	vec3 l = vec3(bn * stage.light_dir).Normalize();
	
	//mode = GOURAUD;
	//tex_img = NULL;
	//spec_img = NULL;
	
	float intensity = 0;
	if (mode == DEPTH)
		intensity = thrd.pos[2] / 255.0;
	else if (mode == FLAT)
		intensity = std::max(0.0f, tri.normal * stage.light_dir);
	else if (mode == GOURAUD)
		for(int i = 0; i < 3; i++)
			intensity += barycentric[i] * std::max(0.f, normal[i] * stage.light_dir);
			//intensity += barycentric[i] * std::max(0.f, l[i]);
	else {
		bool normal_in_darboux = true;
		
		if (tex_img || norm_img) {
			int w = tex_img ? tex_img->width : norm_img->width;
			int h = tex_img ? tex_img->height : norm_img->height;
			
			vec2 tex = tri.tex * barycentric;
			ivec2 texi {(int)(tex[0] * w), (int)(tex[1] * h)};
			texi[0] = std::max(0, std::min(w - 1, texi[0]));
			texi[1] = std::max(0, std::min(h - 1, texi[1]));
			
	
			float spec_intensity = 0.2;
			float spec_pow_intensity = 1.0;
			float ambient_intensity = 6. / 255.;
			
			float diff = 1.0;
			float spec = 0.0;
			float div = ambient_intensity + 1.0;
			
			
			if (norm_img && !norm_img->IsEmpty()) {
				const byte* nb = norm_img->GetIter(texi[0], texi[1]);
				vec3 n;
				n.SetData(nb, 2, -1);
				
				if (!normal_in_darboux) {
					n = (stage.MIT * n.Embed()).Splice().Normalize();
					diff = n * l;
					diff = std::min(1.0f, std::max(0.f, diff * 0.5f));
				}
				else {
					mat3 A {vtx[1] - vtx[0], vtx[2] - vtx[0], bn};
					mat3 AI = A.GetInverse();
					vec3 iv {tri.tex[0][1] - tri.tex[0][0], tri.tex[0][2] - tri.tex[0][0], 0};
					vec3 jv {tri.tex[1][1] - tri.tex[1][0], tri.tex[1][2] - tri.tex[1][0], 0};
					vec3 i = (AI * iv).Normalize();
					vec3 j = (AI * jv).Normalize();
					mat3 B;
					B.SetColumn(0, i);
					B.SetColumn(1, j);
					B.SetColumn(2, bn);
					n = (B * n).Normalize();
					diff = std::min(1.f, std::max(0.f, n * l));
				}
				
				if (spec_img && !spec_img->IsEmpty()) {
					const byte* sb = spec_img->GetIter(texi[0], texi[1]);
					vec3 r = (n * (n * l * 2.f) - l).Normalize();
					spec = powf_fast_precise(std::max(r[2], 0.f), *sb * spec_pow_intensity);
					spec *= spec_intensity;
					div += spec_intensity;
				}
			}
			
			
			intensity = (ambient_intensity + diff + spec) / div;
			intensity = std::max(0.0f, std::min<float>(1.0f, intensity));
		}
		else intensity = 1.0;
	}
	
	if (tex_img && !tex_img->IsEmpty()) {
		vec2 tex = tri.tex * barycentric;
		ivec2 texi {(int)(tex[0] * tex_img->width), (int)(tex[1] * tex_img->height)};
		texi[0] = std::max(0, std::min(tex_img->width - 1, texi[0]));
		texi[1] = std::max(0, std::min(tex_img->height - 1, texi[1]));
		
		const byte* b = tex_img->GetIter(texi[0], texi[1]);
		if (tex_img->stride == 4) {
			for(int i = 0; i < 3; i++) thrd.frag_color[i] = b[i] * intensity;
			thrd.frag_color[3] = 0xFF;
		}
		else if (tex_img->stride == 3) {
			for(int i = 0; i < 3; i++) thrd.frag_color[i] = b[i] * intensity;
		}
		else {
			int gray = 0;
			for(int i = 0; i < tex_img->stride; i++) gray += b[i];
			gray /= tex_img->stride;
			for(int i = 0; i < 3; i++) thrd.frag_color[i] = gray;
		}
	}
	else
		for(int i = 0; i < 3; i++)
			thrd.frag_color[i] = 255 * intensity;
	
}


NAMESPACE_OULU_END

#endif
