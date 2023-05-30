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

ModelRef ModelCache::Attach(Model* mdl) {
	if (!mdl)
		return ModelRef();
	
	if (mdl->path.IsEmpty())
		mdl->path = IntStr64(mdl->GetHashValue());
	
	int i = model_cache.Find(mdl->path);
	if (i >= 0) {
		delete mdl;
		return model_cache[i].GetModel();
	}
	
	ModelLoader& ml = model_cache.Add(mdl->path);
	ml.Attach(mdl);
	return ml.GetModel();
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
