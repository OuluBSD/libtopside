#include "SerialScript.h"


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
	
	
	this->stages.SetCount(stage_count);
	for(int i = 0; i < stage_count; i++) {
		LOG("Loading stage " << i+1 << "/" << stage_count);
		ToyStage& to = this->stages[i];
		const Object& stage = stages[i];
		TOY_ASSERT(stage.IsMap());
		
		const ObjectMap& stage_map = stage.Get<ObjectMap>();
		TOY_ASSERT(stage_map.Find("type") >= 0);
		const Object& type_o = stage_map.Get("type");
		
		const Object& outputs = stage_map.Get("outputs");
		TOY_ASSERT(outputs.IsArray());
		const ObjectArray& output_arr = outputs.Get<ObjectArray>();
		TOY_ASSERT(!output_arr.IsEmpty());
		
		const Object& inputs = stage_map.Get("inputs");
		TOY_ASSERT(inputs.IsArray());
		const ObjectArray& input_arr = inputs.Get<ObjectArray>();
		
		String type_str = type_o.ToString();
		String stage_str = "stage" + IntStr(i);
		TOY_ASSERT(map.Find(stage_str + "_path") >= 0);
		TOY_ASSERT(map.Find(stage_str + "_content") >= 0);
		String stage_path = map.Get(stage_str + "_path");
		String stage_content = map.Get(stage_str + "_path");
		
		const Object& output = output_arr[0];
		ASSERT(output.IsMap());
		const ObjectMap& output_map = output.Get<ObjectMap>();
		TOY_ASSERT(output_map.Find("id") >= 0);
		String output_id_str = output_map.Get("id").ToString();
		
		to.name = stage_str;
		to.type = type_str;
		to.output_id = output_id_str;
		to.script_path = stage_path;
		to.script = stage_content;
		
		to.inputs.SetCount(input_arr.GetCount());
		for(int j = 0; j < input_arr.GetCount(); j++) {
			ToyInput& to_in = to.inputs[j];
			const Object& in = input_arr[j];
			TOY_ASSERT(in.IsMap());
			const ObjectMap& in_map = in.Get<ObjectMap>();
			
			if (in_map.Find("id") < 0)
				continue;
			
			TOY_ASSERT(in_map.Find("type") >= 0);
			to_in.id		= in_map.Get("id").ToString();
			to_in.type		= in_map.Get("type").ToString();
			if (in_map.Find("filter") >= 0)		to_in.filter	= in_map.Get("filter").ToString();
			if (in_map.Find("wrap") >= 0)		to_in.wrap		= in_map.Get("wrap").ToString();
			if (in_map.Find("vflip") >= 0)		to_in.vflip		= in_map.Get("vflip").ToString();
			if (in_map.Find("filename") >= 0)	to_in.filename	= in_map.Get("filename").ToString();
		}
		
	}
	#undef TOY_ASSERT
	
	if (!FindStageNames())
		return false;
	
	PruneLibraries();
	
	if (!SolveLoopbacks())
		return false;
	
	if (!MakeScript())
		return false;
	
	return true;
}

bool ToyLoader::FindStageNames() {
	
	for (ToyStage& stage : stages)
		stage.user_stages.Clear();
	
	for (ToyStage& stage : stages) {
		stage.stage_name = "ogl." + stage.name + "." + stage.type;
	}
	
	
	for (ToyStage& stage : stages) {
		
		for (ToyInput& input : stage.inputs) {
			
			if (input.type == "buffer" ||
				input.type == "image" ||
				input.type == "sound") {
				
				bool found = false;
				input.stage_name.Clear();
				
				for (ToyStage& s0 : stages) {
					if (input.id == s0.output_id) {
						found = true;
						input.stage_name = s0.stage_name;
						if (&s0 == &stage)
							continue; // skip loopbacks
						
						LOG("stage " << stage.stage_name << " uses stage " << input.stage_name);
						s0.user_stages.Add(stage.stage_name);
						if (s0.user_stages.GetCount() > 4) {
							LOG("ToyLoader::FindStageNames: error: more than 4 users for stage '" << s0.name << "'");
							return false;
						}
					}
				}
				
				if (!found) {
					LOG("ToyLoader::FindStageNames: error: did not find input stage with id '" << input.id << "'");
					return false;
				}
			}
			
		}
		
	}
	
	return true;
}

void ToyLoader::PruneLibraries() {
	libraries.Clear();
	
	Vector<int> rm_list;
	int i = 0;
	for (ToyStage& stage : stages) {
		if (stage.type == "library") {
			if (stage.script_path.GetCount())
				libraries << stage.script_path;
			rm_list << i;
		}
		i++;
	}
	
	stages.Remove(rm_list);
}

bool ToyLoader::SolveLoopbacks() {
	bool succ = true;
	
	for (ToyStage& stage : stages) {
		stage.loopback_stage = -1;
		
		int loopback_count = 0;
		int i = 0;
		for (ToyInput& input : stage.inputs) {
			if (input.stage_name == stage.stage_name) {
				input.Clear();
				loopback_count++;
				stage.loopback_stage = i;
			}
			i++;
		}
		
		if (loopback_count > 1) {
			LOG("ToyLoader::SolveLoopbacks: error: only one loopback is allowed, but stage has " << loopback_count);
			succ = false;
		}
	}
	
	return succ;
}

void ToyInput::Clear() {
	stage_name.Clear();
	id.Clear();
	type.Clear();
	filter.Clear();
	wrap.Clear();
	vflip.Clear();
	filename.Clear();
}



static const char* __eon_script_begin = R"30N(
machine sdl.app:
	
	driver context:
		sdl.context
	
	chain program:
		state event.register
		
)30N";

static const char* __eon_script_end = R"30N(

)30N";

bool ToyLoader::MakeScript() {
	bool has_audio_output = false;
	
	String& s = eon_script;
	s.Clear();
	s << __eon_script_begin;
	
	String library_str = Join(libraries, ";");
	
	s << "		loop center.events:\n"
	  << "			center.customer\n"
	  << "			sdl.event.pipe\n"
	  << "			state.event.pipe:\n"
	  << "				target = \"event.register\"\n"
	  << "		\n";
	
	Index<String> keyboard_input_stages;
	
	for (ToyStage& stage : stages) {
		String l;
		l << "ogl." << stage.name << "." << stage.type;
		
		Vector<int> cubemaps;
		
		for(int i = 0; i < stage.inputs.GetCount(); i++) {
			ToyInput& input = stage.inputs[i];
			
			String a, b;
			
			if (input.id.IsEmpty())
				continue;
			
			if (input.type == "texture") {
				if (input.filename.IsEmpty()) {
					LOG("ToyLoader::MakeScript: error: empty input filename in stage " << stage.name);
					return false;
				}
				a << "center." << stage.name << ".ct" << input.id;
				b << "ogl." << stage.name << ".fbo" << input.id;
				s << "		loop " << a << ":\n";
				s << "			center.customer\n";
				s << "			center.image.loader[][loop == " << b << "]:\n";
				if (input.vflip == "true")
					s << "				vflip = true\n";
				s << "				filepath = \"" << input.filename << "\"\n";
				s << "		\n";
				s << "		loop " << b << ":\n";
				s << "			ogl.customer\n";
				s << "			sdl.ogl.fbo.image[loop == " << a << "][loop == " << l << "]\n";
				s << "		\n";
				input.stage_name = b;
			}
			else if (input.type == "cubemap") {
				a << "center." << stage.name << ".ct" << input.id;
				b << "ogl." << stage.name << ".fbo" << input.id;
				s << "		loop " << a << ":\n";
				s << "			center.customer\n";
				s << "			center.image.loader[][loop == " << b << "]:\n";
				if (input.vflip == "true")
					s << "				vflip = true\n";
				s << "				cubemap = true\n";
				s << "				filepath = \"" << input.filename << "\"\n";
				s << "		\n";
				s << "		loop " << b << ":\n";
				s << "			ogl.customer\n";
				s << "			sdl.ogl.fbo.image[loop == " << a << "][loop == " << l << "]\n";
				s << "		\n";
				input.stage_name = b;
				cubemaps << i;
			}
			else if (input.type == "webcam") {
				a << "center." << stage.name << ".ct" << input.id;
				b << "ogl." << stage.name << ".fbo" << input.id;
				s << "		loop " << a << ":\n";
				s << "			center.customer\n";
				s << "			center.video.webcam[][loop == " << b << "]";
				if (input.vflip == "true")
					s << "				vflip = true\n";
				s << "		\n";
				s << "		loop " << b << ":\n";
				s << "			ogl.customer\n";
				s << "			sdl.ogl.fbo.image[loop == " << a << "][loop == " << l << "]\n";
				input.stage_name = b;
			}
			else if (input.type == "musicstream" ||
					 input.type == "music") {
				if (input.filename.IsEmpty()) {
					if (1) {
						input.filename = "most_geometric_person.mp3";
					}
					else {
						LOG("ToyLoader::MakeScript: error: empty input filename in stage " << stage.name);
						return false;
					}
				}
				a << "center." << stage.name << ".ct" << input.id;
				b << "ogl." << stage.name << ".fbo" << input.id;
				s << "		loop " << a << ":\n";
				s << "			center.customer\n";
				s << "			center.audio.loader[][loop == " << b << "]\n";
				s << "				filepath = \"" << input.filename << "\"\n";
				s << "		\n";
				s << "		loop " << b << ":\n";
				s << "			ogl.customer\n";
				s << "			sdl.ogl.center.fbo.audio[loop == " << a << "][loop == " << l << "]\n";
				s << "		\n";
				input.stage_name = b;
			}
			else if (input.type == "keyboard") {
				keyboard_input_stages.Add(l);
				input.stage_name = "ogl.keyboard.source";
				/*
				b << "ogl." << stage.name << ".fbo" << input.id;
				s << "		loop " << b << ": {\n";
				s << "			ogl.customer: true;\n";
				s << "			sdl.ogl.fbo.keyboard: true [][loop == " << l << "] {target: event.register;};\n";
				s << "		};\n";
				s << "		\n";
				input.stage_name = b;
				*/
			}
			else if (input.type == "volume") {
				a << "center." << stage.name << ".ct" << input.id;
				b << "ogl." << stage.name << ".fbo" << input.id;
				s << "		loop " << a << ":\n";
				s << "			center.customer\n";
				s << "			center.volume.loader[][loop == " << b << "]:\n";
				if (input.vflip == "true")
					s << "				vflip = true\n";
				s << "				filepath = \"" << input.filename << "\"\n";
				s << "		\n";
				s << "		loop " << b << ":\n";
				s << "			ogl.customer\n";
				s << "			sdl.ogl.fbo.volume[loop == " << a << "][loop == " << l << "]\n";
				s << "		\n";
				input.stage_name = b;
			}
			else if (input.type == "video") {
				if (input.filename.IsEmpty()) {
					LOG("ToyLoader::MakeScript: error: empty input filename in stage " << stage.name);
					return false;
				}
				a << "center." << stage.name << ".ct" << input.id;
				b << "ogl." << stage.name << ".fbo" << input.id;
				s << "		loop " << a << ":\n";
				s << "			center.customer\n";
				s << "			center.video.loader[][loop == " << b << "]:\n";
				if (input.vflip == "true")
					s << "				vflip = true\n";
				s << "				filepath = \"" << input.filename << "\"\n";
				s << "		\n";
				s << "		loop " << b << ":\n";
				s << "			ogl.customer\n";
				s << "			sdl.ogl.fbo.image[loop == " << a << "][loop == " << l << "]\n";
				s << "				filter = mipmap\n";
				s << "		\n";
				input.stage_name = b;
			}
			else if (input.type == "buffer") {
				ASSERT(input.stage_name.GetCount());
				// pass
			}
			else if (input.type == "empty") {
				// pass
			}
			else {
				LOG("ToyLoader::MakeScript: error: invalid input type '" << input.type << "'");
				return false;
			}
		}
		
		s << "		loop " << l << ":\n"
		  << "			ogl.customer\n";
		  
		
		bool has_input = false;
		for (const ToyInput& input : stage.inputs)
			if (!input.stage_name.IsEmpty())
				has_input = true;
		
		bool is_screen = stage.type == "image";
		bool is_audio = stage.type == "sound";
		
		if (is_audio)
			stage.user_stages.Add("ogl.fbo.audio.conv"); // audio shader requires separate output, which is added later
		
		bool has_no_sides = stage.inputs.IsEmpty() && stage.user_stages.IsEmpty();
		
		if (has_no_sides) {
			if (is_screen)
				s << "			sdl.fbo.standalone";
			else
				s << "			sdl.ogl.fbo.source.standalone";
		}
		else {
			if (is_screen)
				s << "			sdl.fbo";
			else
				s << "			sdl.ogl.fbo.side";
		}
		
		
		if (!has_no_sides) {
			s << " [";
			for(int i = 0; i < 4; i++) {
				if (i < stage.inputs.GetCount()) {
					ToyInput& input = stage.inputs[i];
					if (!input.stage_name.IsEmpty())
						s << (i > 0 ? " loop == " : "loop == ") << input.stage_name;
				}
				s << ",";
			}
			s << "][";
			for(int i = 0; i < 4; i++) {
				if (i < stage.user_stages.GetCount())
					s << (i > 0 ? " loop == " : "loop == ") << stage.user_stages[i];
				s << ",";
			}
			s << "]";
		}
		s << ":\n";
		
		for (int cubemap : cubemaps)
			s << "				buf" << cubemap << " = \"cubemap\"\n";
		
		if (is_audio) {
			s << "				type = \"audio\"\n";
			s << "				retarded.local.time = \"true\"\n";
		}
		
		if (is_screen) {
			s << "				close_machine =	true\n";
			s << "				sizeable =		true\n";
		}
		
		s << "				env =			event.register\n";
		s << "				shader.frag.path =	\"" << EscapeString(stage.script_path) << "\"\n";
		
		if (stage.loopback_stage >= 0)
			s << "				loopback =			\"" << stage.loopback_stage << "\"\n";
		
		if (library_str.GetCount())
			s << "				library =		\"" << library_str << "\"\n";
		
		
		// Add output for audio
		if (is_audio) {
			if (has_audio_output) {
				LOG("ToyLoader::MakeScript: error: requiring new audio output while one exists already in stage " << stage.name);
					return false;
			}
			
			s << "		loop ogl.fbo.audio.conv:\n";
			s << "			ogl.customer\n";
			s << "			sdl.ogl.fbo.center.audio[loop == " << l << "][loop == center.audio.sink]\n";
			s << "		\n";
			s << "		loop center.audio.sink:\n";
			s << "			center.customer\n";
			s << "			center.audio.side.sink.center.user[loop == ogl.fbo.audio.conv]\n";
			s << "			sdl.audio\n";
			s << "		\n";
			
			has_audio_output = true;
		}
	}
	
	if (keyboard_input_stages.GetCount()) {
		s << "		loop ogl.keyboard.source:\n";
		s << "			ogl.customer\n";
		s << "			sdl.ogl.fbo.keyboard[][";
		for(int i = 0; i < 4; i++) {
			if (i < keyboard_input_stages.GetCount()) {
				if (i) s << " ";
				s << "loop == " << keyboard_input_stages[i] << ",";
			}
			else s << ",";
		}
		s << "]:\n";
		s << "				target = event.register\n";
		s << "		\n";
	}
	
	s << __eon_script_end;
	
	LOG(GetLineNumStr(s));
	
	return true;
}

String ToyLoader::GetResult() {
	return eon_script;
}


NAMESPACE_SERIAL_END

