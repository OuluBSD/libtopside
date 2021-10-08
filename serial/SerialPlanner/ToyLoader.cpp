#include "SerialPlanner.h"


NAMESPACE_SERIAL_BEGIN


ToyLoader::ToyLoader() {
	
}

const ObjectMap* ToyLoader::GetStageMap(int i, Object& o) {
	#define TOY_ASSERT(x) if (!(x)) {return 0;}
	TOY_ASSERT(o.IsMap());
	const ObjectMap& map = o.Get<ObjectMap>();
	TOY_ASSERT(map.Find("stages") >= 0);
	const Object& stages_o = map.Get("stages");
	TOY_ASSERT(stages_o.IsArray());
	const ObjectArray& stages = stages_o.Get<ObjectArray>();
	LOG(GetObjectTreeString(stages_o));
	int stage_count = stages.GetCount();
	TOY_ASSERT(i >= 0 && i < stage_count)
	const Object& stage = stages[i];
	TOY_ASSERT(stage.IsMap());
	const ObjectMap& stage_map = stage.Get<ObjectMap>();
	return &stage_map;
	#undef TOY_ASSERT
}

String ToyLoader::GetStageType(int i, Object& o) {
	#define TOY_ASSERT(x) if (!(x)) {return String();}
	const ObjectMap* stage_map = GetStageMap(i, o);
	TOY_ASSERT(stage_map)
	TOY_ASSERT(stage_map->Find("type") >= 0);
	return stage_map->Get("type").ToString();
	#undef TOY_ASSERT
}

String ToyLoader::GetStagePath(int i, Object& o) {
	String stage_str = "stage" + IntStr(i);
	#define TOY_ASSERT(x) if (!(x)) {return String();}
	TOY_ASSERT(o.IsMap());
	const ObjectMap& map = o.Get<ObjectMap>();
	TOY_ASSERT(map.Find(stage_str + "_path") >= 0);
	return map.Get(stage_str + "_path");;
	#undef TOY_ASSERT
}

bool ToyLoader::Load(Object& o) {
	LOG(GetObjectTreeString(o));
	#define TOY_ASSERT(x) if (!(x)) {LOG("ToyLoader::Load: error: assertion failed (" #x ")"); return false;}
	TOY_ASSERT(o.IsMap());
	const ObjectMap& map = o.Get<ObjectMap>();
	TOY_ASSERT(map.Find("stages") >= 0);
	const Object& stages_o = map.Get("stages");
	TOY_ASSERT(stages_o.IsArray());
	const ObjectArray& stages = stages_o.Get<ObjectArray>();
	LOG(GetObjectTreeString(stages_o));
	int stage_count = stages.GetCount();
	if (stage_count == 1) {
		if (GetStageType(0, o) == "image")
			eon_script = GetSingleBufferVideo(GetStagePath(0, o));
		else
			TODO
	}
	else if (stage_count == 2) {
		if (GetStageType(0, o) == "image" && GetStageType(1, o) == "imagebuffer")
			eon_script = GetDoubleBufferVideo(GetStagePath(0, o), GetStagePath(1, o));
		else
			TODO
	}
	else {
		TODO
		
	}
	
	#if 0
	for(int i = 0; i < stage_count; i++) {
		LOG("Loading stage " << i+1 << "/" << stage_count);
		const Object& stage = stages[i];
		TOY_ASSERT(stage.IsMap());
		const ObjectMap& stage_map = stage.Get<ObjectMap>();
		TOY_ASSERT(stage_map.Find("type") >= 0);
		const Object& type_o = stage_map.Get("type");
		String type_str = type_o.ToString();
		String stage_str = "stage" + IntStr(i);
		TOY_ASSERT(map.Find(stage_str + "_path") >= 0);
		TOY_ASSERT(map.Find(stage_str + "_content") >= 0);
		String stage_path = map.Get(stage_str + "_path");
		String stage_content = map.Get(stage_str + "_path");
		//DUMP(stage_path);
		//DUMP(type_str);
		if (type_str == "image") {
			//LOG(GetObjectTreeString(stage));
			if (stage_count == 1) {
				eon_script = GetSingleBufferVideo(stage_path);
			}
			if (stage_count == 2) {
				eon_script = GetDoubleBufferVideo(stage_path);
			}
			else TODO
		}
		else TODO
	}
	#endif
	#undef TOY_ASSERT
	return true;
}

String ToyLoader::GetResult() {
	return eon_script;
}

static const char* __single_buf_tmpl = R"30N(
machine sdl.app: {
	driver context: {
		sdl.context: true;
	};
	chain program: {
		loop ogl.fbo: {
			ogl.customer: true;
			sdl.fbo.standalone: true {filepath: "${PATH0}";};
		};
	};
};
)30N";

static const char* __double_buf_tmpl = R"30N(
machine sdl.app: {
	driver context: {
		sdl.context: true;
	};
	chain program: {
		loop ogl.fbo: {
			ogl.customer: true;
			ogl.fbo.source.pipe:	true {name: "buf0"; filepath: "${PATH1}";};
			sdl.fbo.pipe: true {name: "buf1"; in0: "buf0"; filepath: "${PATH0}";};
		};
	};
};
)30N";

static const char* __double_side_buf_tmpl = R"30N(
machine sdl.app: {
	driver context: {
		sdl.context: true;
	};
	chain program: {
		loop ogl.fbo.buffer: {
			ogl.customer: true;
			ogl.fbo.source: true {name: "buf0"; filepath: "${PATH1}";};
		};
		loop ogl.fbo.screen: {
			ogl.customer: true;
			sdl.fbo: true {name: "buf1"; in0: "buf0"; filepath: "${PATH0}";};
		};
	};
};

)30N";

String ToyLoader::GetSingleBufferVideo(String glsl_path) {
	ASSERT(!glsl_path.IsEmpty())
	String out = __single_buf_tmpl;
	out.Replace("${PATH0}", glsl_path);
	//DUMP(out);
	return out;
}

String ToyLoader::GetDoubleBufferVideo(String glsl_path0, String glsl_path1) {
	ASSERT(!glsl_path0.IsEmpty())
	ASSERT(!glsl_path1.IsEmpty())
	String out = __double_buf_tmpl;
	out.Replace("${PATH0}", glsl_path0);
	out.Replace("${PATH1}", glsl_path1);
	//DUMP(out);
	return out;
}


NAMESPACE_SERIAL_END