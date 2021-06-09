#include "EcsLib.h"

NAMESPACE_TOPSIDE_BEGIN


bool EonLoader::Initialize() {
	
	return true;
}

void EonLoader::Start() {
	
}

void EonLoader::Update(double dt) {
	
}

void EonLoader::Stop() {
	
}

void EonLoader::Uninitialize() {
	
}

bool EonLoader::LoadFile(String path) {
	if (!FileExists(path)) {
		LOG("Could not find EON file");
		return false;
	}
	String eon = TS::LoadFile(path);
	return Load(eon, path);
}

bool EonLoader::Load(String content, String filepath) {
	DLOG("EonLoader::Load: Loading \"" << filepath << "\":\n" << content);
	
	TODO
	
}


NAMESPACE_TOPSIDE_END
