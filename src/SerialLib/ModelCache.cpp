#include "SerialLib.h"


NAMESPACE_TOPSIDE_BEGIN
using namespace Serial;



ModelRef ModelCache::GetAddModelFile(String path) {
	int i = model_cache.Find(path);
	if (i >= 0)
		return model_cache[i].GetModel();
	ModelLoader& l = model_cache.Add(path);
	l.LoadModel(path);
	return l.GetModel();
}



bool ModelCache::Initialize() {
	return true;
}

void ModelCache::Start() {
	
}

void ModelCache::Update(double dt) {
	time += dt;
	
}

void ModelCache::Stop() {
	
}

void ModelCache::Uninitialize() {
	
}


NAMESPACE_TOPSIDE_END
