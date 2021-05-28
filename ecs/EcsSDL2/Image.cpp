#include "EcsSDL2.h"

NAMESPACE_TOPSIDE_BEGIN



SDL2ImageComponent::SDL2ImageComponent() :
	svalue(this), sstream(this)
{
	
}

void SDL2ImageComponent::Initialize() {
	
}

void SDL2ImageComponent::Uninitialize() {
	img.Clear();
}

bool SDL2ImageComponent::LoadFileAny(String path) {
	img.Clear();
	sstream.SetSkipDrop(false);
	
	if (path.Left(9) == "<cubemap>") {
		path = path.Mid(9);
		
		String dir = GetFileDirectory(path);
		String title = GetFileTitle(path);
		String ext = GetFileExt(path);
		
		for(int i = 0; i < 6; i++) {
			if (i)
				path = AppendFileName(dir, title + "_" + IntStr(i) + ext);
			
			SDL_Surface* surf = IMG_Load(path);
			if (!surf) {
				last_error = IMG_GetError();
				return false;
			}
			
			img << Image(surf);
		}
		sstream.SetSkipDrop();
		return true;
	}
	else {
		SDL_Surface* surf = IMG_Load(path);
		if (!surf) {
			last_error = IMG_GetError();
			return false;
		}
		img << Image(surf);
		sstream.SetSkipDrop();
		return true;
	}
}

Size SDL2ImageComponent::GetResolution() const {
	if (img.GetCount())
		return img[0].GetSize();
	return Size(0,0);
}

StaticStream& SDL2ImageComponent::GetStream(StcCtx) {
	return sstream;
}

void SDL2ImageComponent::BeginStream(StcCtx) {
	TODO
}

void SDL2ImageComponent::EndStream(StcCtx) {
	TODO
}

#if 0
void SDL2ImageComponent::EmitStatic() {
	int id = 0;
	for(Image& img : this->img) {
		int w = img.GetWidth();
		int h = img.GetHeight();
		int d = 1;
		int stride = img.GetStride();
		int pitch = img.GetPitch();
		const byte* img_data = img.Begin();
		
		StaticValueData data;
		data.obj_i = id;
		data.w = w;
		data.h = h;
		data.d = d;
		data.stride = stride;
		data.pitch = pitch;
		data.data = img_data;
		
		for(StaticSinkRef sink : StaticSource::GetConnections())
			sink->RecvStatic(data);
		id++;
	}
}
#endif



NAMESPACE_TOPSIDE_END
