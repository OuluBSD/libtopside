#include "Shadertoy.h"

NAMESPACE_TOPSIDE_BEGIN


ShadertoyContextLoader::ShadertoyContextLoader() {
	
}

void ShadertoyContextLoader::Clear() {
	id_counter = 0;
}

void ShadertoyContextLoader::OnError(TypeCls type, String fn, String msg) {
	last_error = msg;
	WhenError();
}

void ShadertoyContextLoader::OnError(String fn, String msg) {
	LOG("ShadertoyContextLoader::" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

bool ShadertoyContextLoader::Load(String path, Object& o) {
	LOG("ShadertoyContextLoader::Load: " << path);
	
	String ext = GetFileExt(path);
	if (ext == ".toy")
		return LoadFileToy(path, o);
	
	return false;
}

bool ShadertoyContextLoader::LoadFileToy(String path, Object& dst) {
	const char* fn_name = "LoadFileToy";
	Clear();
	
	if (!FileExists(path)) {
		String share_path = ShareDirFile(path);
		if (FileExists(share_path))
			path = share_path;
	}
	
	if (!FileExists(path)) {
		OnError(fn_name, "file doesn't exist: " + path);
		return false;
	}
	
	String file_dir = GetFileDirectory(path);
	bool fail = false;
	dst = ParseJSON(LoadFile(path));
	
	ASSERT(dst.IsMap());
	ObjectMap& map = dst.GetMap();
	for(int i = 0; i < 100; i++) {
		String stage = "stage" + IntStr(i);
		String stage_file = AppendFileName(file_dir, stage + ".glsl");
		if (!FileExists(stage_file))
			break;
		String glsl = LoadFile(stage_file);
		if (glsl.IsEmpty()) {
			fail = true;
			last_error = "empty shader for stage " + IntStr(i);
		}
		else {
			map.Add(stage + "_path", stage_file);
			map.Add(stage + "_content", glsl);
		}
	}
	
	if (fail) {
		OnError(fn_name, last_error);
		return false;
	}
	
	MakeUniqueIds(dst);
	
	return true;
}

void ShadertoyContextLoader::MakeUniqueIds(Object& v) {
	if (!v.IsMap())
		return;
	//DLOG(GetObjectTreeString(v));
	ObjectMap& map = v.GetMap();
	Object& stages = map.GetAdd("stages", ObjectArray());
	if (!stages.IsArray())
		return;
	VectorMap<int,int> ids;
	ObjectArray& st_arr = stages.GetArray();
	VectorMap<int, Object> stage_ids;
	for(int i = 0; i < st_arr.GetCount(); i++) {
		int stage_id = -1;
		Object& st_el = st_arr.Get(i);
		if (st_el.IsMap()) {
			ObjectMap& st_map = st_el.GetMap();
			Object& inputs = st_map.GetAdd("inputs", ObjectArray());
			if (inputs.IsArray()) {
				ObjectArray& in_arr = inputs.GetArray();
				for(int i = 0; i < in_arr.GetCount(); i++) {
					Object& in_el = in_arr.Get(i);
					if (!in_el.IsMap())
						continue;
					ObjectMap& in_map = in_el.GetMap();
					int j = in_map.Find("id");
					if (j >= 0)
						in_map.SetAt(j, MakeUniqueId(ids, (int)in_map.GetObject(j).ToInt()));
				}
			}
			
			Object& outputs = st_map.GetAdd("outputs", ObjectArray());
			if (outputs.IsArray()) {
				ObjectArray& out_arr = outputs.GetArray();
				for(int i = 0; i < out_arr.GetCount(); i++) {
					Object& out_el = out_arr.Get(i);
					if (!out_el.IsMap())
						continue;
					ObjectMap& out_map = out_el.GetMap();
					int j = out_map.Find("id");
					if (j >= 0) {
						int id = MakeUniqueId(ids, (int)out_map.GetObject(j).ToInt());
						if (!i)
							stage_id = id;
						out_map.SetAt(j, id);
					}
				}
				if (out_arr.IsEmpty()) {
					ObjectMap map;
					stage_id = MakeUniqueId(ids, 10000 + i);
					map.Add("id", stage_id);
					out_arr.Add(map);
				}
			}
		}
		
		if (stage_id < 0)
			stage_id = MakeUniqueId(ids, 10000 + i);
		stage_ids.Add(stage_id);
	}
	
	if (0) {
		for(int i = 0; i < stage_ids.GetCount(); i++) {
			int st_pos = map.Find("stage" + IntStr(i) + "_content");
			ASSERT(st_pos >= 0);
			if (st_pos >= 0) {
				stage_ids[i] = map.GetObject(st_pos);
				map.Remove(st_pos);
			}
		}
	}
	
	if (0) {
		DLOG("ShadertoyContextLoader::MakeUniqueIds: result");
		DLOG(GetObjectTreeString(v));
		for(int i = 0; i < stage_ids.GetCount(); i++) {
			DLOG("\t" << stage_ids.GetKey(i) << ": <source>");
		}
	}
	
	if (0) {
		for(int i = 0; i < stage_ids.GetCount(); i++) {
			int id = stage_ids.GetKey(i);
			map.Add(IntStr(id), stage_ids[i]);
		}
	}
}

int ShadertoyContextLoader::MakeUniqueId(VectorMap<int,int>& ids, int orig_id) {
	if (orig_id < 0)
		return -1;
	int i = ids.Find(orig_id);
	if (i >= 0)
		return ids[i];
	int id = ++id_counter;
	ids.Add(orig_id, id);
	return id;
}













String SerialShadertoyLoader::LoadFile(String file_path) {
	TODO
	#if 0
	ShadertoyContextLoader toy_loader;
	Object o;
	if (!toy_loader.Load(file_path, o)) {
		LOG("SerialShadertoyLoader::LoadFile: error: toy file loading failed: " << file_path);
		return String();
	}
	
	Serial::ToyLoader ser_loader;
	if (!ser_loader.Load(o)) {
		LOG("SerialShadertoyLoader::LoadFile: error: toy object loading failed");
		return String();
	}
	
	String eon_script = ser_loader.GetResult();
	
	return eon_script;
	#endif
}


NAMESPACE_TOPSIDE_END
