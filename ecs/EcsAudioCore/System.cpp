#include "EcsAudioCore.h"


NAMESPACE_TOPSIDE_BEGIN








MixerContextConnector::MixerContextConnector() {
	
}

void MixerContextConnector::Initialize() {
	
}

void MixerContextConnector::Uninitialize() {
	
}



MixerChannelContextConnector::MixerChannelContextConnector() {
	
}

void MixerChannelContextConnector::Initialize() {
	
}

void MixerChannelContextConnector::Uninitialize() {
	
}



MixerChannelInputComponent::MixerChannelInputComponent() {
	
}

void MixerChannelInputComponent::Initialize() {
	
}

void MixerChannelInputComponent::Uninitialize() {
	
}




MixerChannelOutputComponent::MixerChannelOutputComponent() {
	
}

void MixerChannelOutputComponent::Initialize() {
	
}

void MixerChannelOutputComponent::Uninitialize() {
	
}


AudioStream& MixerChannelOutputComponent::GetStream(AudCtx) {
	TODO
}

void MixerChannelOutputComponent::BeginStream(AudCtx) {
	TODO
}

void MixerChannelOutputComponent::EndStream(AudCtx) {
	TODO
}

AudioFormat MixerChannelOutputComponent::GetFormat(AudCtx) {
	TODO
}

Audio& MixerChannelOutputComponent::GetValue(AudCtx) {
	TODO
}



MixerAudioSourceComponent::MixerAudioSourceComponent() {
	
}

void MixerAudioSourceComponent::Initialize() {
	
}

void MixerAudioSourceComponent::Uninitialize() {
	
}

AudioStream& MixerAudioSourceComponent::GetStream(AudCtx) {
	TODO
}

void MixerAudioSourceComponent::BeginStream(AudCtx) {
	TODO
}

void MixerAudioSourceComponent::EndStream(AudCtx) {
	TODO
}

AudioFormat MixerAudioSourceComponent::GetFormat(AudCtx) {
	TODO
}

Audio& MixerAudioSourceComponent::GetValue(AudCtx) {
	TODO
}




MidiFileComponent::MidiFileComponent() {
	EventSource::SetMultiConnection();
	
}

void MidiFileComponent::Initialize() {
	TODO // DevComponent::Initiralize
}

void MidiFileComponent::Uninitialize() {
	
}

void MidiFileComponent::Clear() {
	last_error.Clear();
	song_dt = -1;
	track_i.SetCount(0);
}

bool MidiFileComponent::OpenFilePath(String path) {
	Clear();
	
	if (!FileExists(path)) {
		last_error = "file does not exist: " + path;
		return false;
	}
	
	if (!file.Open(path)) {
		last_error = file.GetLastError();
		return false;
	}
	
	file.DoTimeAnalysis();
	file.LinkNotePairs();
	
	track_i.SetCount(file.GetTrackCount(), 0);
	
	return true;
}

void MidiFileComponent::DumpMidiFile() {
	int track_count = file.GetTrackCount();
	LOG("TPQ: " << file.GetTicksPerQuarterNote());
	if (track_count > 1) {
		LOG("TRACKS: " << track_count);
	}
	for (int track = 0; track < track_count; track++) {
		if (track_count > 1) {
			LOG("\nTrack " << track);
		}
		LOG("Tick\tSeconds\tDur\tMessage");
		const auto& t = file[track];
		for (int event = 0; event < t.GetCount(); event++) {
			const auto& e = t[event];
			LOG(IntStr(e.tick));
			LOG("\t" << DblStr(e.seconds));
			String s = "\t";
			if (e.IsNoteOn()) {
				s << DblStr(e.GetDurationInSeconds());
			}
			for (int i = 0; i < e.GetCount(); i++)
				s << "\t" << IntStr(e[i]);
			LOG(s);
		}
	}
}

#if 0

void MidiFileComponent::EmitMidi(double dt) {
	
	// The first update is often laggy, so wait until the second one
	if (song_dt < 0) {
		song_dt = 0;
		return;
	}
	
	song_dt += dt;
	
	tmp.midi.Reserve(1000);
	
	for(int i = 0; i < file.GetTrackCount(); i++) {
		CollectTrackEvents(i);
		EmitTrack(i);
	}
	
}

void MidiFileComponent::OnLink(Sink sink, Cookie src_c, Cookie sink_c) {
	TODO
	
}

void MidiFileComponent::CollectTrackEvents(int i) {
	if (i >= track_i.GetCount())
		track_i.SetCount(i+1,0);
	
	int& iter = track_i[i];
	const auto& t = file[i];
	
	tmp.Reset();
	while (iter < t.GetCount()) {
		const auto& e = t[iter];
		if (e.seconds <= song_dt) {
			iter++;
			tmp.midi.Add(&e);
		}
		else break;
	}
}

void MidiFileComponent::EmitTrack(int i) {
	if (tmp.midi.IsEmpty())
		return;
	
	for (Ref<MidiSink> c : MidiSource::GetConnections())
		if (c->AcceptsTrack(i))
			c->RecvMidi(tmp);
	
}

#endif



NAMESPACE_TOPSIDE_END
