#include "IMedia.h"

NAMESPACE_PARALLEL_BEGIN






template <class Backend>
VideoLoaderBaseT<Backend>::VideoLoaderBaseT() {
	
}

template <class Backend>
bool VideoLoaderBaseT<Backend>::Initialize(const Script::WorldState& ws) {
	//LOG(ws.ToString());
	
	String arg_filepath = ws.Get(".filepath");
	if (arg_filepath.IsEmpty()) {
		LOG("VolumeLoaderBase: error: no 'filepath' given");
		return false;
	}
	
	filepath = RealizeFilepathArgument(arg_filepath);
	RTLOG("VideoLoaderBase: filepath=\"" << filepath << "\"");
	
	if (ws.Get(".vflip") == "true")
		vflip = true;
	
	return LoadFile();
}

template <class Backend>
bool VideoLoaderBaseT<Backend>::LoadFile() {
	if (!FileExists(filepath)) {
		LOG("VideoLoaderBase::LoadFile: error: file does not exist: '" << filepath << "'");
		return false;
	}
	
	TODO // maybe use FfmpegAtomBase?
	
	return true;
}

template <class Backend>
void VideoLoaderBaseT<Backend>::Uninitialize() {
	
}


template <class Backend>
bool VideoLoaderBaseT<Backend>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	
	TODO
}











MEDIA_EXCPLICIT_INITIALIZE_CLASS(VideoCodecFormatT)
MEDIA_EXCPLICIT_INITIALIZE_CLASS(VideoSourceFormatResolutionT)
MEDIA_EXCPLICIT_INITIALIZE_CLASS(VideoSourceFormatT)
MEDIA_EXCPLICIT_INITIALIZE_CLASS(VideoInputFrameT)
MEDIA_EXCPLICIT_INITIALIZE_CLASS(VideoOutputFrameT)
MEDIA_EXCPLICIT_INITIALIZE_CLASS(VideoLoaderBaseT)


NAMESPACE_PARALLEL_END
