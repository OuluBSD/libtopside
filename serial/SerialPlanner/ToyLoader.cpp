#include "SerialPlanner.h"


NAMESPACE_SERIAL_BEGIN


ArrayMap<String,String>& ToyShaderHashToName() {
	static ArrayMap<String,String> map;
	if (map.IsEmpty()) {
		map.Add("85a6d68622b36995ccb98a89bbb119edf167c914660e4450d313de049320005c", "grid");
		map.Add("cbcbb5a6cfb55c36f8f021fbb0e3f69ac96339a39fa85cd96f2017a2192821b5", "nyan");
		map.Add("0681c014f6c88c356cf9c0394ffe015acc94ec1474924855f45d22c3e70b5785", "bg1");
		map.Add("793a105653fbdadabdc1325ca08675e1ce48ae5f12e37973829c87bea4be3232", "bg2");
		map.Add("0a40562379b63dfb89227e6d172f39fdce9022cba76623f1054a2c83d6c0ba5d", "noise1");
		map.Add("550a8cce1bf403869fde66dddf6028dd171f1852f4a704a465e1b80d23955663", "bg3");
		map.Add("3083c722c0c738cad0f468383167a0d246f91af2bfa373e9c5c094fb8c8413e0", "noise2");
		map.Add("27012b4eadd0c3ce12498b867058e4f717ce79e10a99568cca461682d84a4b04", "noise3");
		map.Add("488bd40303a2e2b9a71987e48c66ef41f5e937174bf316d3ed0e86410784b919", "bg4");
		map.Add("95b90082f799f48677b4f206d856ad572f1d178c676269eac6347631d4447258", "metal");
		map.Add("0c7bf5fe9462d5bffbd11126e82908e39be3ce56220d900f633d58fb432e56f5", "noise4");
		map.Add("10eb4fe0ac8a7dc348a2cc282ca5df1759ab8bf680117e4047728100969e7b43", "stonewall");
		map.Add("e6e5631ce1237ae4c05b3563eda686400a401df4548d0f9fad40ecac1659c46c", "wall");
		map.Add("8de3a3924cb95bd0e95a443fff0326c869f9d4979cd1d5b6e94e2a01f5be53e9", "uk_street");
		map.Add("585f9546c092f53ded45332b343144396c0b2d70d9965f585ebc172080d8aa58", "yard");
		map.Add("94284d43be78f00eb6b298e6d78656a1b34e2b91b34940d02f1ca8b22310e8a0", "bg5");
		map.Add("ad56fba948dfba9ae698198c109e71f118a54d209c0ea50d77ea546abad89c57", "stone1");
		map.Add("52d2a8f514c4fd2d9866587f4d7b2a5bfa1a11a0e772077d7682deb8b3b517e5", "stone2");
		map.Add("aea6b99da1d53055107966b59ac5444fc8bc7b3ce2d0bbb6a4a3cbae1d97f3aa", "noise5");
		map.Add("bd6464771e47eed832c5eb2cd85cdc0bfc697786b903bfd30f890f9d4fc36657", "brown_grid");
		map.Add("1f7dca9c22f324751f2a5a59c9b181dfe3b5564a04b724c657732d0bf09c99db", "wood1");
		map.Add("92d7758c402f0927011ca8d0a7e40251439fba3a1dac26f5b8b62026323501aa", "stone3");
		map.Add("cd4c518bc6ef165c39d4405b347b51ba40f8d7a065ab0e8d2e4f422cbc1e8a43", "stone4");
		map.Add("8979352a182bde7c3c651ba2b2f4e0615de819585cc37b7175bcefbca15a6683", "stone5");
		map.Add("fb918796edc3d2221218db0811e240e72e340350008338b0c07a52bd353666a6", "wood2");
		map.Add("f735bee5b64ef98879dc618b016ecf7939a5756040c2cde21ccb15e69a6e1cfb", "noise6");
		map.Add("3871e838723dd6b166e490664eead8ec60aedd6b8d95bc8e2fe3f882f0fd90f0", "stone6");
		map.Add("79520a3d3a0f4d3caa440802ef4362e99d54e12b1392973e4ea321840970a88a", "stone7");
		map.Add("08b42b43ae9d3c0605da11d0eac86618ea888e62cdd9518ee8b9097488b31560", "alphabet");
		map.Add("3c33c415862bb7964d256f4749408247da6596f2167dca2c86cc38f83c244aa6", "toymusic");
		map.Add("29de534ed5e4a6a224d2dfffab240f2e19a9d95f5e39de8898e850efdb2a99de", "toymusic");
		map.Add("48e2d9ef22ca6673330b8c38a260c87694d2bbc94c19fec9dfa4a1222c364a99", "toymusic");
		map.Add("894a09f482fb9b2822c093630fc37f0ce6cfec02b652e4e341323e4b6e4a4543", "toymusic");
		map.Add("a6a1cf7a09adfed8c362492c88c30d74fb3d2f4f7ba180ba34b98556660fada1", "toymusic");
		map.Add("d96b229eeb7a08d53adfcf1ff89e54c9ffeebed193d317d1a01cc8125c0f5cca", "toymusic");
		map.Add("ec8a6ea755d34600547a5353f21f0a453f9f55ff95514383b2d80b8d71283eda", "toymusic");
		map.Add("3405e48f74815c7baa49133bdc835142948381fbe003ad2f12f5087715731153", "oldie");
		map.Add("c3a071ecf273428bc72fc72b2dd972671de8da420a2d4f917b75d20e1c24b34c", "img_forces");
		map.Add("35c87bcb8d7af24c54d41122dadb619dd920646a0bd0e477e7bdc6d12876df17", "van_damme");
		map.Add("e81e818ac76a8983d746784b423178ee9f6cdcdf7f8e8d719341a6fe2d2ab303", "britney");
	}
	return map;
}

String RealizeFilepathArgument(String arg_filepath) {
	String filepath = RealizeShareFile(arg_filepath);
	
	if (!FileExists(filepath)) {
		bool found = false;
		String title = GetFileTitle(filepath);
		String other_name = ToyShaderHashToName().Get(title, "");
		String ext = GetFileExt(filepath);
		if (!other_name.IsEmpty()) {
			LOG("RealizeFilepathArgument: found real name from hash: " << other_name);
			String toypath =
				AppendFileName(
					GetFileDirectory(arg_filepath),
					other_name + ext);
			if (!FileExists(toypath)) {
				toypath = RealizeShareFile(toypath);
				LOG("RealizeFilepathArgument: trying to find sharefile: " << toypath);
			}
			if (FileExists(toypath)) {
				filepath = toypath;
				found = true;
				LOG("RealizeFilepathArgument: changed hash to file " << filepath);
			}
			else {
				LOG("RealizeFilepathArgument: internal error: file not found: " << filepath);
			}
		}
		
		if (!found) {
			LOG("RealizeFilepathArgument: error: file does not exist: " << filepath);
			filepath = arg_filepath;
		}
	}
	return filepath;
}




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
		if (GetStageType(0, o) == "image" && GetStageType(1, o) == "imagebuffer" && GetStageType(2, o) == "imagebuffer")
			eon_script = GetTripleBufferVideo(GetStagePath(0, o), GetStagePath(1, o), GetStagePath(2, o));
		else
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

static const char* __triple_buf_tmpl = R"30N(
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

String ToyLoader::GetTripleBufferVideo(String glsl_path0, String glsl_path1, String glsl_path2) {
	ASSERT(!glsl_path0.IsEmpty())
	ASSERT(!glsl_path1.IsEmpty())
	ASSERT(!glsl_path2.IsEmpty())
	String out = __triple_buf_tmpl;
	TODO
	out.Replace("${PATH0}", glsl_path0);
	out.Replace("${PATH1}", glsl_path1);
	out.Replace("${PATH2}", glsl_path2);
	//DUMP(out);
	return out;
}


NAMESPACE_SERIAL_END
