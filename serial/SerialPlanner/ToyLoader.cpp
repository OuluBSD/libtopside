#include "SerialPlanner.h"


NAMESPACE_SERIAL_BEGIN


ToyLoader::ToyLoader() {
	
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
			if (stage_count == 1) {
				LOG(GetObjectTreeString(stage));
				eon_script = GetSingleBufferVideo(stage_path);
			}
			else TODO
		}
		else TODO
	}
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
		loop accel.video: {
			accel.customer: true;
			sdl.video.standalone: true {filepath: "${PATH0}";};
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


NAMESPACE_SERIAL_END
