#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN



SDL2ImageBase::SDL2ImageBase()
{
	
}

bool SDL2ImageBase::AltInitialize(const Script::WorldState& ws) {
	
	return true;
}

void SDL2ImageBase::AltUninitialize() {
	img.Clear();
}

bool SDL2ImageBase::LoadFileAny(String path) {
	img.Clear();
	
	TODO
	#if 0
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
			
			#ifdef flagGUI
			img << Image(surf);
			#else
			TODO
			#endif
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
		
		#ifdef flagGUI
		img << Image(surf);
		#else
		TODO
		#endif
		
		sstream.SetSkipDrop();
		return true;
	}
	#endif
}

Size SDL2ImageBase::GetResolution() const {
	if (img.GetCount())
		return img[0].GetSize();
	return Size(0,0);
}

/*StaticStream& SDL2ImageBase::GetStream(StcCtx) {
	return sstream;
}

void SDL2ImageBase::BeginStream(StcCtx) {
	TODO
}

void SDL2ImageBase::EndStream(StcCtx) {
	TODO
}*/

#if 0
void SDL2ImageBase::EmitStatic() {
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



NAMESPACE_SERIAL_END
