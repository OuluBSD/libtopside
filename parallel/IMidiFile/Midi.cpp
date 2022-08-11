#include "IMidiFile.h"


NAMESPACE_PARALLEL_BEGIN



MidiFileReaderAtom::MidiFileReaderAtom() {
	
}

bool MidiFileReaderAtom::Initialize(const Script::WorldState& ws) {
	close_machine = ws.GetBool(".close_machine", false);
	
	String path = ws.GetString(".filepath");
	if (path.IsEmpty()) {
		LOG("MidiFileReaderAtom::Initialize: error: 'filepath' argument is required, but not given");
		return false;
	}
	
	path = RealizeShareFile(path);
	if (!OpenFilePath(path)) {
		LOG("MidiFileReaderAtom::Initialize: error: " << last_error << ": " << path);
		return false;
	}
	
	//DumpMidiFile();
	
	AddAtomToUpdateList();
	
	return true;
}

void MidiFileReaderAtom::Uninitialize() {
	RemoveAtomFromUpdateList();
	
	Clear();
}

void MidiFileReaderAtom::Clear() {
	last_error.Clear();
	song_dt = -1;
	track_i.SetCount(0);
}

bool MidiFileReaderAtom::OpenFilePath(String path) {
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
	
	// DumpMidiFile();
	
	return true;
}

void MidiFileReaderAtom::DumpMidiFile() {
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

void MidiFileReaderAtom::Update(double dt) {
	if (close_machine && IsEnd())
		GetMachine().SetNotRunning();
	
	// The first update is often laggy, so wait until the second one
	if (song_dt < 0) {
		song_dt = 0;
		return;
	}
	
	song_dt += dt;
	//LOG("midi song dt: " << song_dt);
	
	tmp.midi.Reserve(1000);
	
	for(int i = 0; i < file.GetTrackCount(); i++) {
		CollectTrackEvents(i);
	}
	
}

void MidiFileReaderAtom::CollectTrackEvents(int i) {
	if (i >= track_i.GetCount())
		track_i.SetCount(i+1,0);
	
	int& iter = track_i[i];
	const auto& t = file[i];
	
	while (iter < t.GetCount()) {
		const auto& e = t[iter];
		if (e.seconds <= song_dt) {
			iter++;
			tmp.midi.Add(&e);
		}
		else break;
	}
}

bool MidiFileReaderAtom::IsEnd() const {
	for(int i = 0; i < track_i.GetCount(); i++) {
		const int& iter = track_i[i];
		const auto& t = file[i];
		if (iter < t.GetCount())
			return false;
	}
	return true;
}

bool MidiFileReaderAtom::IsReady(PacketIO& io) {
	return io.full_src_mask == 0 && io.active_sink_mask & 0x1 && tmp.midi.GetCount() > 0;
}

bool MidiFileReaderAtom::Recv(int sink_ch, const Packet& in) {
	return true;
}

bool MidiFileReaderAtom::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	Format fmt = out.GetFormat();
	
	if (fmt.IsMidi()) {
		Vector<byte>& data = out.Data();
		
		int sz = tmp.midi.GetCount() * sizeof(MidiIO::Event);
		data.SetCount(sz);
		
		MidiIO::Event* dst = (MidiIO::Event*)(byte*)data.Begin();
		for(const MidiIO::Event* ev : tmp.midi) {
			//LOG("track " << ev->track << ": " << ev->ToString());
			*dst++ = *ev;
		}
		
		tmp.Reset();
	}
	
	return true;
}
















MidiNullAtom::MidiNullAtom() {
	
}

bool MidiNullAtom::Initialize(const Script::WorldState& ws) {
	verbose = ws.GetBool(".verbose", false);
	
	return true;
}

void MidiNullAtom::Uninitialize() {
	
}

bool MidiNullAtom::IsReady(PacketIO& io) {
	return true;
}

bool MidiNullAtom::Recv(int sink_ch, const Packet& in) {
	
	if (verbose) {
		const Vector<byte>& data = in->Data();
		int count = data.GetCount() / sizeof(MidiIO::Event);
		LOG("MidiNullAtom::Recv: " << count << " midi events");
		
		const MidiIO::Event* ev  = (const MidiIO::Event*)(const byte*)data.Begin();
		const MidiIO::Event* end = ev + count;
		while (ev != end) {
			LOG("track " << ev->track << ": " << ev->ToString());
			ev++;
		}
	}
	
	return true;
}

bool MidiNullAtom::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}



NAMESPACE_PARALLEL_END
