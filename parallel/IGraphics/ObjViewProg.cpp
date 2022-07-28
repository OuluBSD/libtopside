#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
ObjViewProgT<Gfx>::ObjViewProgT() {
	sz = Size(TS::default_width, TS::default_height);
	
	if (0) {
		obj = "cube.obj";
	}
	else {
		obj = "african_head" DIR_SEPS "african_head.obj";
	}
}

template <class Gfx>
void ObjViewProgT<Gfx>::Initialize() {
	Serial::FboAtomT<Gfx>::Latest().AddBinder(this);
}

template <class Gfx>
void ObjViewProgT<Gfx>::Uninitialize() {
	Serial::FboAtomT<Gfx>::Latest().RemoveBinder(this);
	loader.Clear();
}

template <class Gfx>
bool ObjViewProgT<Gfx>::Arg(const String& key, const String& value) {
	
	if (key == "use.pbr") {
		use_pbr = value == "true";
	}
	else if (key == "model") {
		obj = value;
	}
	else if (key == "skybox.diffuse") {
		have_skybox = true;
		skybox_diffuse = value;
	}
	else if (key == "skybox.irradiance") {
		have_skybox = true;
		skybox_irradiance = value;
	}
	else if (key == "width") {
		sz.cx = StrInt(value);
	}
	else if (key == "height") {
		sz.cy = StrInt(value);
	}
	else return false;
	
	return true;
}

template <class Gfx>
bool ObjViewProgT<Gfx>::Render(Draw& fb) {
	using DataState = DataStateT<Gfx>;
	using ModelState = ModelStateT<Gfx>;
	using StateDraw = StateDrawT<Gfx>;
	
	StateDraw* sd = CastPtr<StateDraw>(&fb);
	ASSERT(sd);
	
	if (frame == 0) {
		DataState& state = sd->GetState();
		
		if (state.GetModelCount() == 0) {
			int env_material_model = -1;
			
			if (have_skybox) {
				ModelState& skybox = state.AddModelT();
				ASSERT(skybox.id >= 0);
				float skybox_sz = 1e8;
				Index<String> ext_list; ext_list << "" << ".png" << ".jpg";
				Index<String> dir_list; dir_list << "" << "imgs" << "imgs/skybox";
				ModelBuilder mb;
				Mesh& box_mesh = mb.AddBox(vec3(0), vec3(skybox_sz), true, true);
				Model& box = mb;
				
				if (!box.LoadCubemapFile(box_mesh, TEXTYPE_CUBE_DIFFUSE, skybox_diffuse)) {
					LOG("ObjViewProg::Render: error: could not load skybox diffuse image '" << skybox_diffuse << "'");
					return false;
				}
				if (!box.LoadCubemapFile(box_mesh, TEXTYPE_CUBE_IRRADIANCE, skybox_irradiance)) {
					LOG("ObjViewProg::Render: error: could not load skybox irradiance image '" << skybox_irradiance << "'");
					return false;
				}
				
				loader = mb;
				if (!skybox.LoadModel(loader)) {
					RTLOG("ObjViewProg::Render: error: could not load skybox");
					return false;
				}
				if (!skybox.LoadModelTextures(loader)) {
					RTLOG("ObjViewProg::Render: error: could not load skybox textures");
					return false;
				}
				
				skybox.env_material = skybox.materials.GetKey(0);
				skybox.env_material_model = skybox.id;
				env_material_model = skybox.id;
				
				bool b = skybox.SetProgram("sky");
				ASSERT(b);
			}
			
			ModelState& mdl = state.AddModelT();
			mdl.env_material_model = env_material_model;
			
			String data_dir = ShareDirFile("models");
			String obj_path = AppendFileName(data_dir, obj);
			
			if (!loader.LoadModel(obj_path)) {
				RTLOG("ObjViewProg::Render: error: could not load model file: '" << obj_path << "'");
				return false;
			}
			if (!mdl.LoadModel(loader)) {
				RTLOG("ObjViewProg::Render: error: could not load model state");
				return false;
			}
			if (!mdl.LoadModelTextures(loader)) {
				RTLOG("ObjViewProg::Render: error: could not load model textures: '" << obj_path << "'");
				return false;
			}
			
			bool b = mdl.SetProgram("default");
			ASSERT(b);
		}
	}
	
	
	DrawObj(*sd, true);
	
	iter++;
	frame++;
	if (ts.Seconds() >= phase_time) {
		iter = 0;
		ts.Reset();
		phase = (phase + 1) % phases;
	}
	
	return true;
}

template <class Gfx>
void ObjViewProgT<Gfx>::DrawObj(StateDrawT<Gfx>& fb, bool use_texture) {
	using DataState = DataStateT<Gfx>;
	
	ASSERT(fb.HasTarget());
	DataState& state = fb.GetState();
	
	float ratio = (float)sz.cy / (float)sz.cx;
	float eye_ratio = (float)sz.cy / (float)(sz.cx * 0.5);
	float aspect = (float)sz.cx / (float)sz.cy;
	float f = ts.Seconds() / phase_time;
	float angle = f * (2.0 * M_PI);
	
	if (!state.user_view) {
		float rad = 1.5;
		float x = cos(angle) * rad;
		float z = sin(angle) * rad * SCALAR_FWD_Z;
		float eye_x = cos(angle);
		float eye_y = sin(angle);
		mat4 proj = Perspective(DEG2RAD(90), 1.0, 0.1, 100.0);
		
		vec3 eye {x, 0, z};
		//vec3 center {0.3f * -eye_x, 0.0f, 0.3f * eye_y};
		vec3 center {0, 0, 0};
		vec3 up = VEC_UP;
		mat4 lookat = LookAt(eye, center, up);
		mat4 port = GetViewport(-1 * ratio, -1, 2 * ratio, 2, 1);
		mat4 base = port * proj;
		
		state.camera_pos = eye;
		state.camera_dir = (center - eye).GetNormalized();
		state.view = base * lookat;
		
		if (1) {
			float eye_dist = 0.08;
			state.is_stereo = true;
			mat4 eye_port = GetViewport(-1 * eye_ratio, -1, 2 * eye_ratio, 2, 1);
			mat4 base = eye_port * proj;
			vec3 l_eye(-eye_dist, 0, -1 * SCALAR_FWD_Z);
			vec3 r_eye(+eye_dist, 0, -1 * SCALAR_FWD_Z);
			vec3 l_center { -eye_dist, 0, 0};
			vec3 r_center { +eye_dist, 0, 0};
			mat4 l_lookat = LookAt(l_eye, l_center, up);
			mat4 r_lookat = LookAt(r_eye, r_center, up);
			state.view_stereo[0] = base * l_lookat;
			state.view_stereo[1] = base * r_lookat;
		}
		
		//state.view_stereo[0] = state.view;
		//state.view_stereo[1] = state.view;
		
		//mat4 rot = rotate(Identity<mat4>(), angle, up);
		//mat4 model = Translate(vec3(0.0, 0.0, 0.0));
		//state.view = port * proj * lookat * model * rot;
		
	}
	#if 0
	state.light_dir = vec3 {sin(angle), 0.0, cos(angle)};
	#else
	state.light_dir = AxesDir(M_PI/2, M_PI/4);
	#endif
	
}

template <class Gfx>
ObjViewVertexT<Gfx>::ObjViewVertexT() {
	this->UseUniform(GVar::VAR_VIEW);
}

template <class Gfx>
void ObjViewVertexT<Gfx>::Process(VertexShaderArgsT<Gfx>& a) {
	vec4 pos = a.v.position.Splice().Embed();
	vec4 screen = a.va->view * pos;
	if (screen[3] != 0) {
		screen.Project();
		a.v.position = screen;
		//LOG(a.v.position.ToString());
	}
}

template <class Gfx>
ObjViewFragmentT<Gfx>::ObjViewFragmentT() {
	this->UseUniform(GVar::VAR_DIFFUSE);
	this->UseUniform(GVar::VAR_SPECULAR);
	this->UseUniform(GVar::VAR_CUBE_DIFFUSE);
	this->UseUniform(GVar::VAR_CUBE_IRRADIANCE);
}

template <class Gfx>
void ObjViewFragmentT<Gfx>::Process(FragmentShaderArgsT<Gfx>& args) {
	#if 0
	float w = args.generic->iResolution[0];
	float h = args.generic->iResolution[1];
	float x = args.frag_coord[0] / w;
	float y = args.frag_coord[1] / h;
	args.frag_color_out = vec4(x, y, 0, 1);
	#else
	
	ASSERT(args.fa);
	vec3& n = args.normal;
	vec3& light_dir = args.fa->light_dir;
	float m = Dot(n, light_dir);
	
	vec4& used_clr = args.frag_color_out;
	used_clr[3] = 0;
	
	float intensity = std::max(0.0f, m);
	
	intensity = intensity * 0.5 + 0.5;
	
	auto& diffuse = args.fa->color_buf[TEXTYPE_DIFFUSE];
	if (diffuse) {
		const ByteImage& tex = *diffuse;
		float tex_x = args.tex_coord[0];
		float tex_y = args.tex_coord[1];
		ASSERT(tex_x >= 0.0f && tex_x <= 1.0f);
		ASSERT(tex_y >= 0.0f && tex_y <= 1.0f);
		int tex_xi = tex_x * tex.GetWidth();
		int tex_yi = tex_y * tex.GetHeight();
		tex_xi = std::max(0, std::min(tex.GetWidth() - 1, tex_xi));
		tex_yi = std::max(0, std::min(tex.GetHeight() - 1, tex_yi));
		const byte* b = tex.GetIter(tex_xi, tex_yi);
		ASSERT(intensity <= 1.0f);
		float mul = intensity / 255.0;
		float R = b[0] * mul;
		float G = b[1] * mul;
		float B = b[2] * mul;
		ASSERT(R >= 0.0f && R <= 1.0f);
		ASSERT(G >= 0.0f && G <= 1.0f);
		ASSERT(B >= 0.0f && B <= 1.0f);
		used_clr[0] = R;
		used_clr[1] = G;
		used_clr[2] = B;
	}
	else {
		used_clr[0] = intensity;
		used_clr[1] = intensity;
		used_clr[2] = intensity;
	}
	#endif
}


SDLOGL_EXCPLICIT_INITIALIZE_CLASS(ObjViewProgT)
X11OGL_EXCPLICIT_INITIALIZE_CLASS(ObjViewProgT)
X11SW_EXCPLICIT_INITIALIZE_CLASS(ObjViewProgT)
X11SW_EXCPLICIT_INITIALIZE_CLASS(ObjViewVertexT)
X11SW_EXCPLICIT_INITIALIZE_CLASS(ObjViewFragmentT)


NAMESPACE_PARALLEL_END
