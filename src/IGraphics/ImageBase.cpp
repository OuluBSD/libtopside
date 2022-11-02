#include "IGraphics.h"
#include <SerialMach/SerialMach.h>

#ifdef flagSCREEN

NAMESPACE_PARALLEL_BEGIN



template <class Gfx>
ImageBaseAtomT<Gfx>::ImageBaseAtomT()
{
	
}

template <class Gfx>
bool ImageBaseAtomT<Gfx>::Initialize(const Script::WorldState& ws) {
	LOG(ws.ToString());
	
	String arg_filepath = ws.Get(".filepath");
	if (arg_filepath.IsEmpty()) {
		LOG("ImageBaseAtomT: error: no 'filepath' given");
		return false;
	}
	
	String filepath = RealizeFilepathArgument(arg_filepath);
	RTLOG("ImageBaseAtomT: filepath=\"" << filepath << "\"");
	
	cubemap			= ws.Get(".cubemap") == "true";
	vflip			= ws.Get(".vflip") == "true";
	swap_top_bottom	= ws.Get(".swap_top_bottom") == "true";
	
	//OBJ_CREATE
	
	seq = 0;
	imgs.Clear();
	if (cubemap) {
		String dir = GetFileDirectory(filepath);
		String ext = GetFileExt(filepath);
		String title = GetFileTitle(filepath);
		for(int i = 0; i < 6; i++) {
			String side_path;
			if (i == 0)
				side_path = filepath;
			else
				side_path = AppendFileName(dir, title + "_" + IntStr(i) + ext);
			
			Image img = StreamRaster::LoadFileAny(side_path);
			if (img.IsEmpty()) {
				LOG("ImageBaseAtomT: error: empty image: " << side_path);
				return false;
			}
			
			// shadertoy compatibility
			if (vflip)
				img = MirrorVertical(img);
			
			imgs.Add(img);
		}
		
		if (swap_top_bottom)
			Swap(imgs[2], imgs[3]);
	}
	else {
		Image img = StreamRaster::LoadFileAny(filepath);
		if (img.IsEmpty()) {
			LOG("ImageBaseAtomT: error: empty image: " << filepath);
			return false;
		}
		
		// shadertoy compatibility
		if (vflip)
			img = MirrorVertical(img);
		
		imgs.Add(img);
	}
	
	return true;
}

template <class Gfx>
bool ImageBaseAtomT<Gfx>::PostInitialize() {
	ISourceRef src = GetSource();
	int src_count = src->GetSourceCount();
	for(int i = 0; i < src_count; i++) {
		Value& val = src->GetSourceValue(i);
		Format fmt = val.GetFormat();
		if (fmt.vd == VD(Center, Video)) {
			VideoFormat& vfmt = fmt;
			if (vfmt.GetPackedCount() != 4) {
				vfmt.type = LightSampleFD::RGBA_U8_LE;
				if (!this->GetLink()->NegotiateSourceFormat(i, fmt))
					return false;
			}
		}
	}
	
	return true;
}

template <class Gfx>
void ImageBaseAtomT<Gfx>::Uninitialize() {
	imgs.Clear();
	//obj.Clear();
}

template <class Gfx>
bool ImageBaseAtomT<Gfx>::IsReady(PacketIO& io) {
	bool b = io.full_src_mask == 0 && !imgs.IsEmpty();
	RTLOG("ImageBaseAtomT::IsReady: " << (b ? "true" : "false"));
	return b;
}

template <class Gfx>
bool ImageBaseAtomT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	if (imgs.IsEmpty()) return false;
	
	Format fmt = out.GetFormat();
	if (fmt.IsVideo()) {
		out.seq = seq++;
		Image& img = imgs[0];
		
		fmt.vid.SetSize(img.GetSize());
		if (cubemap)
			fmt.vid.SetCubemap();
		out.SetFormat(fmt);
		
		int pack = fmt.vid.GetPackedCount();
		ASSERT(pack == 4);
		DataFromImage(img, out.Data());
		ASSERT(out.GetData().GetCount());
		
		imgs.Remove(0);
	}
	else if (fmt.IsReceipt())
		; // pass
	else TODO
	
	return true;
}

template <class Gfx>
Size ImageBaseAtomT<Gfx>::GetResolution() const {
	if (imgs.GetCount())
		return imgs[0].GetSize();
	return Size(0,0);
}




GFX_EXCPLICIT_INITIALIZE_CLASS(ImageBaseAtomT)

NAMESPACE_PARALLEL_END

#endif
