#include "AudioHost.h"


NAMESPACE_TOPSIDE_BEGIN


MidiEonContextLoader::MidiEonContextLoader() {
	
}

void MidiEonContextLoader::Clear() {
	id_counter = 0;
}

void MidiEonContextLoader::OnError(TypeCls type, String fn, String msg) {
	last_error = msg;
	WhenError();
}

void MidiEonContextLoader::OnError(String fn, String msg) {
	LOG("MidiEonContextLoader::" << fn << ": error: " << msg);
	last_error = msg;
	WhenError();
}

bool MidiEonContextLoader::Load(String path, Object& o) {
	LOG("MidiEonContextLoader::Load: " << path);
	
	String ext = GetFileExt(path);
	if (ext == ".mid")
		return LoadFileMidi(path, o);
	
	return false;
}

bool MidiEonContextLoader::LoadFileMidi(String path, Object& dst) {
	const char* fn_name = "LoadFileMidi";
	Clear();
	
	if (!FileExists(path)) {
		String share_path = ShareDirFile(path);
		if (FileExists(share_path))
			path = share_path;
	}
	
	if (!FileExists(path)) {
		OnError(fn_name, "file doesn't exist: " + path);
		return false;
	}
	
	
	MidiIO::File f;
	
	if (!f.Open(path)) {
		OnError(fn_name, "file loading failed: " + path);
		return false;
	}
	
	// Find first patch-change for every track
	VectorMap<int,int> patches;
	int track_count = f.GetTrackCount();
	for(int i = 0; i < track_count; i++) {
		int ev_count = f.GetEventCount(i);
		for(int j = 0; j < ev_count; j++) {
			const MidiIO::Event& ev = f.GetEvent(i, j);
			if (ev.IsPatchChange()) {
				int timbre = ev.GetP1();
				LOG("Track " << i << ": " << MidiIO::GetTimbreName(timbre));
				patches.Add(i,timbre);
				break;
			}
		}
	}
	
	const char* begin = R"eon(
machine midi.app:
	chain program:
		loop event:
			center.customer
			midi.file.reader16[][${SIDEOUT}]:
				filepath = "${PATH}"
				close_machine = true
				drum.ch = ${DRUM_CH}
				use.global.time = ${GLOBALTIME}
				
		loop drums:
			center.customer
			coredrummer.pipe[loop == event][${DRUMOUT}]:
				preset = "presets/gscw1.preset"
				ch.oh = 1
				ch.kick = 2
				ch.snare = 3
				ch.toms = 4
)eon";

	const char* ch_tmpl = R"eon(
		loop ch.${CHANNEL}:
			center.customer
			fluidsynth.pipe[loop == event]:
				verbose = false
				patch = ${PATCH}
			corefx.pipe:
				filter = "compressor"
				gain = 10
			center.audio.side.src.center.user[][loop == sidemixer]
)eon";

	const char* drum_ch_tmpl = R"eon(
		loop ch.${CHANNEL}:
			center.customer
			center.audio.side.sink.center.user[loop == drums]
			corefx.pipe:
				filter = "compressor"
			center.audio.side.src.center.user[][loop == mixer${DRUMSIDEOUT}]
)eon";

	const char* end = R"eon(
		loop sidemixer:
			center.customer
			center.audio.mixer16[${SIDECOMPIN}]:
				auto.limit = true
				sync = true
			center.audio.side.src.center.user[][loop == sidecomp, loop == reverb]
		
		loop sidecomp:
			center.customer
			corefx.atom[loop == sidemixer, ${SIDECOMPCHAININ}]:
				filter = "compressor"
				sidechain = true
				treshold = -20
				attack = 20
				release = 100
				ratio = 5
				auto.makeup = false
			center.audio.side.src.center.user[][loop == mixer]
		
		loop reverb:
			center.customer
			center.audio.mixer16[loop == sidemixer${REVERBIN}]:
				auto.limit = true
				sync = true
			corefx.pipe:
				filter = "freeverb"
				mix = 1.0
				roomsize = 0.98
			center.audio.side.src.center.user[][loop == mixer]
		
		loop mixer:
			center.customer
			center.audio.mixer16[${SIDEIN}]:
				auto.limit = true
				sync = true
			corefx.pipe:
				filter = "compressor"
				treshold = -2
				ratio = 10
			${AUDIO_OUT_ATOM}
)eon";

	
	// fast hack to allow audio file out switch
	bool audio_file_out = false;
	const auto& cmdline = CommandLine();
	for (String cmd : cmdline) {
		if (cmd == "-EXPORT_AUDIO_FILE=y")
			audio_file_out = true;
	}
	
	String audio_out_atom = "center.audio.sink.hw";
	bool use_global_time = false;
	
	if (audio_file_out) {
		audio_out_atom = "audio.file.writer";
		use_global_time = true;
	}
	
	String eon;
	
	eon = begin;
	
	String sideout;
	int sideout_count = 0;
	for(int i = 0; i < track_count; i++) {
		int patch = patches.Get(i, -1);
		if (patch >= 0) {
			String ch = ch_tmpl;
			ch.Replace("${CHANNEL}", IntStr(i));
			ch.Replace("${PATCH}", IntStr(patch));
			eon += ch;
			
			if (sideout.GetCount()) sideout << ", ";
			sideout << "loop == ch." << i;
			sideout_count++;
		}
	}
	
	const char* drum_ch[4] {"oh", "kick", "snare", "toms"};
	String drumout;
	String sidecompin = sideout;
	String sidein;
	String sidecompchainin;
	String reverbin;
	
	sidein << "loop == sidecomp, loop == reverb";
	
	for(int i = 0; i < 4; i++) {
		String drumsideout;
		
		sidein  << ", loop == ch." << drum_ch[i];
		if (i)
			drumout << ", ";
		drumout << "loop == ch." << drum_ch[i];
		
		// Others than 'oh'
		if (i != 0) {
			if (!sidecompchainin.IsEmpty()) sidecompchainin << ", ";
			sidecompchainin << "loop == ch." << drum_ch[i];
			drumsideout << ", loop == sidecomp";
		}
		// Others than 'kick' are connected to reverb
		if (i != 1) {
			reverbin << ", loop == ch." << drum_ch[i];
			drumsideout << ", loop == reverb";
		}
		
		String ch = drum_ch_tmpl;
		ch.Replace("${CHANNEL}", drum_ch[i]);
		ch.Replace("${DRUMSIDEOUT}", drumsideout);
		eon += ch;
		
		if (sideout.GetCount()) sideout << ", ";
		sideout << "loop == ch." << i;
		sideout_count++;
	}
	
	sideout << ", loop == drums";
	sideout_count++;
	
	eon += end;
	
	eon.Replace("${PATH}", path);
	eon.Replace("${SIDEOUT}", sideout);
	eon.Replace("${SIDEIN}", sidein);
	eon.Replace("${SIDECOMPIN}", sidecompin);
	eon.Replace("${SIDECOMPCHAININ}", sidecompchainin);
	eon.Replace("${DRUMOUT}", drumout);
	eon.Replace("${DRUM_CH}", IntStr(sideout_count));
	eon.Replace("${REVERBIN}", reverbin);
	eon.Replace("${AUDIO_OUT_ATOM}", audio_out_atom);
	eon.Replace("${GLOBALTIME}", use_global_time ? "true" : "false");
	
	
	//LOG(eon);
	
	result = eon;
	
	return true;
}











String SerialMidiEonLoader::LoadFile(String file_path) {
	MidiEonContextLoader mid_loader;
	Object o;
	if (!mid_loader.Load(file_path, o)) {
		LOG("SerialMidiEonLoader::LoadFile: error: toy file loading failed: " << file_path);
		return String();
	}
	
	return mid_loader.GetResult();
}


NAMESPACE_TOPSIDE_END
