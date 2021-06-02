#include "Shadertoy.h"

NAMESPACE_TOPSIDE_BEGIN


ShadertoyContextLoader::ShadertoyContextLoader() {
	
}

void ShadertoyContextLoader::OnError(TypeCls type, String fn, String msg) {
	LOG(AccelComponent::GetStringFromType(type) << ":" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

void ShadertoyContextLoader::OnError(String fn, String msg) {
	LOG("ShadertoyContextLoader::" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

bool ShadertoyContextLoader::Load(String path, Object& o, ContextComponentBase* b) {
	LOG("ShadertoyContextLoader::Load: " << path << " to " << HexStr(b));
	
	String ext = GetFileExt(path);
	if (ext == ".toy")
		return LoadFileToy(path, o);
	
	return false;
}

bool ShadertoyContextLoader::LoadFileToy(String path, Object& dst) {
	const char* fn_name = "LoadFileToy";
	Clear();
	
	String file_dir = GetFileDirectory(path);
	
	if (!FileExists(path)) {
		OnError(fn_name, "file doesn't exist");
		return false;
	}
	
	bool fail = false;
	dst = ParseJSON(LoadFile(path));
	
	ASSERT(dst.IsMap());
	ObjectMap& map = dst.GetMap();
	for(int i = 0; i < 100; i++) {
		String stage = "stage" + IntStr(i);
		String stage_file = AppendFileName(file_dir, "stage" + IntStr(i) + ".glsl");
		if (!FileExists(stage_file))
			break;
		String glsl = LoadFile(stage_file);
		if (glsl.IsEmpty()) {
			fail = true;
			last_error = "empty shader for stage " + IntStr(i);
		}
		else {
			map.Add(IntStr(i), glsl);
		}
	}
	
	if (fail) {
		OnError(fn_name, last_error);
		return false;
	}
	
	MakeUniqueIds(dst);
	
	return true;
}

void ShadertoyContextLoader::Clear() {
	TODO
}

void ShadertoyContextLoader::MakeUniqueIds(Object& v) {
	TODO
}



NAMESPACE_TOPSIDE_END
