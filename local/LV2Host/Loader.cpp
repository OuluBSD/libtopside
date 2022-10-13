#include "LV2Host.h"

NAMESPACE_TOPSIDE_BEGIN


MidiLV2ContextLoader::MidiLV2ContextLoader() {
	
}

void MidiLV2ContextLoader::Clear() {
	id_counter = 0;
}

void MidiLV2ContextLoader::OnError(TypeCls type, String fn, String msg) {
	last_error = msg;
	WhenError();
}

void MidiLV2ContextLoader::OnError(String fn, String msg) {
	LOG("MidiLV2ContextLoader::" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

bool MidiLV2ContextLoader::Load(String path, Object& o) {
	LOG("MidiLV2ContextLoader::Load: " << path);
	
	String ext = GetFileExt(path);
	if (ext == ".mid")
		return LoadFileMidi(path, o);
	
	return false;
}

bool MidiLV2ContextLoader::LoadFileMidi(String path, Object& dst) {
	const char* fn_name = "LoadFileMidi";
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
	
	TODO
	
	return true;
}











String SerialMidiLV2Loader::LoadFile(String file_path) {
	MidiLV2ContextLoader mid_loader;
	Object o;
	if (!mid_loader.Load(file_path, o)) {
		LOG("SerialMidiLV2Loader::LoadFile: error: toy file loading failed: " << file_path);
		return String();
	}
	
	TODO
}


NAMESPACE_TOPSIDE_END
