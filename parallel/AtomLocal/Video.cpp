#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN






VideoLoaderBase::VideoLoaderBase() {
	
}

bool VideoLoaderBase::Initialize(const Script::WorldState& ws) {
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

bool VideoLoaderBase::LoadFile() {
	if (!FileExists(filepath)) {
		LOG("VideoLoaderBase::LoadFile: error: file does not exist: '" << filepath << "'");
		return false;
	}
	
	TODO // maybe use FfmpegAtomBase?
	
	return true;
}

void VideoLoaderBase::Uninitialize() {
	
}

void VideoLoaderBase::Forward(FwdScope& fwd) {
	
	TODO
}

bool VideoLoaderBase::ProcessPackets(PacketIO& io) {
	
	TODO
}













NAMESPACE_SERIAL_END
