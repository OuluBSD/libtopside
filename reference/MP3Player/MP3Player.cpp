#include "MP3Player.h"

NAMESPACE_TOPSIDE_BEGIN



#if HAVE_FFMPEG
void MP3Player::OnError() {
	GetEntity()->GetMachine().SetNotRunning();
}

void MP3Player::OnStop() {
	GetEntity()->GetMachine().SetNotRunning();
}

void MP3Player::Initialize() {
	/*EntityRef e = GetEntity();
	file_in = e->Find<FfmpegComponent>();
	audio   = e->Find<AudioSinkComponent>();
	if (!file_in || !audio)
		Panic("Invalid MP3 player");
	
	file_in->WhenStopped = THISBACK(OnStop);
	
	if (!file_in->LoadFileAny(file_path)) {
		LOG("opening media file failed: " << file_in->GetLastError());
		GetMachine().SetNotRunning();
		return;
	}*/
	
    //e->FindConnector<ConnectAllCenterInterfaces>()->LinkAll();
}

void MP3Player::Uninitialize() {
	/*file_in.Clear();
	audio.Clear();
	GetEntity()->Destroy();*/
}

void MP3Player::Forward(FwdScope& fwd) {
	TODO
}

void MP3Player::StorePacket(Packet& p) {
	TODO
}

#endif




NAMESPACE_TOPSIDE_END
