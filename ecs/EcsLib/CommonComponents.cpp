#include "EcsLib.h"

NAMESPACE_TOPSIDE_BEGIN


/*void Transform::MoveTo(const OverlapSink& conn) {
	TODO
}*/

void CopyTransformPos(EntityRef from, EntityRef to) {
	if (!from.IsEmpty() && !to.IsEmpty()) {
		Ref<Transform> f = from->Find<Transform>();
		Ref<Transform> t = to->Find<Transform>();
		if (f && t)
			*t = *f;
	}
}



void StaticVolumeComponent::Initialize() {
	sz = Size(0,0);
	depth = 0;
	stride = 0;
}

void StaticVolumeComponent::Uninitialize() {
	
}

bool StaticVolumeComponent::LoadFileAny(String path) {
	const char* fn_name = "LoadFileAny";
	
	errstr.Clear();
	
	String s = LoadFile(path);
	if (s.IsEmpty()) {
		errstr = "couldn't load file " + path;
		return false;
	}
	
	MemReadStream data(s.Begin(), s.GetCount());
	int magic, w, h, d, channels, sz;
	data.Get(&magic, 4); // "BIN "
	if (magic == 0x004e4942) {
		data.Get(&w, 4);
		data.Get(&h, 4);
		data.Get(&d, 4);
		data.Get(&channels, 4);
		sz = w * h * d * channels;
		values.SetCount(sz);
		data.Get(values.Begin(), sz);
	}
	else {
		int len = 0;
		for(int i = 1; i <= 4; i++) {
			int per_ch = s.GetCount() / i;
			int root = (int)pow(per_ch, 1.0/3.0);
			int test_sz = root * root * root * i;
			if (test_sz == s.GetCount()) {
				channels = i;
				len = root;
				break;
			}
		}
		if (channels <= 0 || len <= 0) {
			errstr = "couldn't find volume data dimensions";
			return false;
		}
		w = h = d = len;
		sz = w * h * d * channels;
		values.SetCount(sz);
		MemoryCopy(values.Begin(), s.Begin(), sz);
	}
	
	this->sz.cx = w;
	this->sz.cy = h;
	this->depth = d;
	this->stride = channels;
	
	EmitStatic();
	
	return true;
}

Size StaticVolumeComponent::GetResolution() const {
	return sz;
}

int  StaticVolumeComponent::GetDepth() const {
	return depth;
}

void StaticVolumeComponent::EmitStatic() {
	StaticSinkData data;
	data.obj_i = 0;
	data.w = sz.cx;
	data.h = sz.cy;
	data.d = depth;
	data.stride = this->stride;
	data.pitch = data.w;
	data.data = values.Begin();
	for(Ref<StaticSink> c : StaticSource::GetConnections())
		c->RecvStatic(data);
}


NAMESPACE_TOPSIDE_END
