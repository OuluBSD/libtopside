#ifdef flagMAIN
#include "Sequencer.h"

GUI_APP_MAIN {
	using namespace UPP;
	using namespace TS;
	
	GetMidi();
	
	try {
		SetLanguage(LNG_ENGLISH);
		SetDefaultCharset(CHARSET_UTF8);
		
		SequencerFs().Type("Sequencer files", "*.msq")
		         .AllFilesType()
		         .DefaultExt("msq");
		MidiFs().Type("MIDI files", "*.mid")
		       .AllFilesType()
		       .DefaultExt("mid");
		
		LoadFromFile(callback(Sequencer::SerializeApp));
		One<Sequencer> seq;
		seq.Create();
		Ctrl::EventLoop();
		StoreToFile(callback(Sequencer::SerializeApp));
	}
	catch (Exc e) {
		PromptOK(e);
	}
}

#endif
