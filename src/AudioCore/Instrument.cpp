#include "AudioCore.h"

NAMESPACE_AUDIO_BEGIN

Instrument::Instrument() {
	last_frame_.SetCount( 1, 2, 0.0f );
}

void Instrument::HandleEvent(const MidiIO::Event& e, int track_i) {
	int channel = e.GetChannel();
	
	//LOG("Instrument::HandleEvent: track " << e.track << ": " << e.GetChannel() << ": " << e.ToString());
	
	if (e.IsController()) {
		if (track_i < 0 || channel == track_i) {
			int num = e.GetP1();
			int value = e.GetP2();
			/*LOG("Configure event: " <<
				e.ToString() << ": " <<
				MidiIO::GetEventCtrlString(num) << " = " << value);*/
			ControlChange(num, value);
		}
	}
	else if (e.IsMeta()) {
		bool send = false;
		int mnum = e.GetP1();
		int strlen = e.GetP2();
		String str;
		for(int i = 3; i < 3 + strlen; i++) {
			int chr = e[i];
			str.Cat(chr);
		}
		switch (mnum) {
			case MidiIO::MIDIMETA_SEQNUM:
				break;
			case MidiIO::MIDIMETA_TEXT:
				//LOG("Midi-string: " << str);
				break;
			case MidiIO::MIDIMETA_COPYRIGHT:
				//LOG("Copyright: " << str);
				break;
			case MidiIO::MIDIMETA_TRACKNAME:
				//LOG("Track name: " << str);
				break;
			case MidiIO::MIDIMETA_INSTRNAME:
				//LOG("Instrument name: " << str);
				break;
			case MidiIO::MIDIMETA_LYRICS:
				break;
			case MidiIO::MIDIMETA_MARKER:
				break;
			case MidiIO::MIDIMETA_CUEPOINT:
				break;
			case MidiIO::MIDIMETA_CHPREFIX:
				break;
			case MidiIO::MIDIMETA_TRACKEND:
				break;
			case MidiIO::MIDIMETA_TEMPO:
				break;
			case MidiIO::MIDIMETA_SMPTE:
				break;
			case MidiIO::MIDIMETA_TIMESIG:
				break;
			case MidiIO::MIDIMETA_KEYSIG:
				break;
			case MidiIO::MIDIMETA_CUSTOM:
				break;
		}
		
	}
	else if (e.IsNoteOff()) {
		NoteOff(0);
	}
	else if (e.IsNoteOn()) {
		float freq = 440.0f * powf(2.0f, (e.GetP1() - 69.0f) / 12.0f);
		float ampl = e.GetP2() / 127.0f;
		NoteOn(freq, ampl);
	}
	else if (e.IsNote()) {
		//LOG("Ignore note: " << e.ToString());
	}
	else if (e.IsAftertouch()) {
		//LOG("Ignore aftertouch: " << e.ToString());
	}
	else if (e.IsTimbre() || e.IsPatchChange()) {
		/*int channel = e.GetChannel();
		int value = e.GetP1();
		if (track_i < 0 || channel == track_i) {
			//LOG("Changing channel patch: channel " << channel << " to " << value << ": " << e.ToString());
			int bank = 0;
			// if channel is the midi-standard drum channel
			if (channel == 9) {
				bank = 128;
			}
			//program_select(bank, value);
		}*/
	}
	else if (e.IsPressure()) {
		//LOG("Ignore pressure: " << e.ToString());
	}
	else if (e.IsPitchbend()) {
		int channel = e.GetChannel();
		//int value = e.GetP1();
		if (track_i < 0 || channel == track_i) {
			//LOG("Setting pitch bend: channel " << channel << " to " << value);
			/*int fs_pbend = (128 + value) * 0x4000 / 256;
			pitch_bend(fs_pbend);*/
		}
	}
	else {
		//LOG("Unexpected configure event: " << e.ToString());
	}
}

NAMESPACE_AUDIO_END
