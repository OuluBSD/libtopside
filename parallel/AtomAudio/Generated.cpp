#include "AtomAudio.h"

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

String MidiFileReaderPipe::GetAction() {
	return "midi.file.reader.pipe";
}

AtomTypeCls MidiFileReaderPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::MIDI_FILE_READER_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,MIDI),0);
	return t;
}

LinkTypeCls MidiFileReaderPipe::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void MidiFileReaderPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<MidiFileReaderAtom>(this);
}

AtomTypeCls MidiFileReaderPipe::GetType() const {
	return GetAtomType();
}


String MidiFileReader::GetAction() {
	return "midi.file.reader";
}

AtomTypeCls MidiFileReader::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::MIDI_FILE_READER;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,RECEIPT),0);
	t.AddOut(VD(CENTER,MIDI),1);
	return t;
}

LinkTypeCls MidiFileReader::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void MidiFileReader::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<MidiFileReaderAtom>(this);
}

AtomTypeCls MidiFileReader::GetType() const {
	return GetAtomType();
}


String MidiFileReader16::GetAction() {
	return "midi.file.reader16";
}

AtomTypeCls MidiFileReader16::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::MIDI_FILE_READER16;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,RECEIPT),0);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	return t;
}

LinkTypeCls MidiFileReader16::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void MidiFileReader16::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<MidiFileReaderAtom>(this);
}

AtomTypeCls MidiFileReader16::GetType() const {
	return GetAtomType();
}


String MidiNullSink::GetAction() {
	return "midi.null.sink";
}

AtomTypeCls MidiNullSink::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::MIDI_NULL_SINK;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,MIDI),0);
	t.AddOut(VD(CENTER,RECEIPT),0);
	return t;
}

LinkTypeCls MidiNullSink::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void MidiNullSink::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<MidiNullAtom>(this);
}

AtomTypeCls MidiNullSink::GetType() const {
	return GetAtomType();
}


#if (defined flagFLUIDLITE) || (defined flagFLUIDSYNTH)
String FluidsynthPipe::GetAction() {
	return "fluidsynth.pipe";
}

AtomTypeCls FluidsynthPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::FLUIDSYNTH_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddIn(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,AUDIO),0);
	return t;
}

LinkTypeCls FluidsynthPipe::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void FluidsynthPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<FluidsynthInstrument>(this);
}

AtomTypeCls FluidsynthPipe::GetType() const {
	return GetAtomType();
}
#endif


String SoftInstrumentPipe::GetAction() {
	return "softinstru.pipe";
}

AtomTypeCls SoftInstrumentPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::SOFT_INSTRUMENT_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddIn(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,AUDIO),0);
	return t;
}

LinkTypeCls SoftInstrumentPipe::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void SoftInstrumentPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<SoftInstrument>(this);
}

AtomTypeCls SoftInstrumentPipe::GetType() const {
	return GetAtomType();
}


String FmSynthPipe::GetAction() {
	return "fmsynth.pipe";
}

AtomTypeCls FmSynthPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::FM_SYNTH_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddIn(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,AUDIO),0);
	return t;
}

LinkTypeCls FmSynthPipe::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void FmSynthPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<FmSynthInstrument>(this);
}

AtomTypeCls FmSynthPipe::GetType() const {
	return GetAtomType();
}


#if defined flagLV2
String LV2InstrumentPipe::GetAction() {
	return "lv2.instrument.pipe";
}

AtomTypeCls LV2InstrumentPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::LV2_INSTRUMENT_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddIn(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,AUDIO),0);
	return t;
}

LinkTypeCls LV2InstrumentPipe::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void LV2InstrumentPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<LV2Instrument>(this);
}

AtomTypeCls LV2InstrumentPipe::GetType() const {
	return GetAtomType();
}
#endif


String CoreSynthPipe::GetAction() {
	return "coresynth.pipe";
}

AtomTypeCls CoreSynthPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::CORE_SYNTH_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddIn(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,AUDIO),0);
	return t;
}

LinkTypeCls CoreSynthPipe::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void CoreSynthPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<CoreSynthInstrument>(this);
}

AtomTypeCls CoreSynthPipe::GetType() const {
	return GetAtomType();
}


String CoreDrummerPipe::GetAction() {
	return "coredrummer.pipe";
}

AtomTypeCls CoreDrummerPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::CORE_DRUMMER_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddIn(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,RECEIPT),0);
	t.AddOut(VD(CENTER,AUDIO),1);
	t.AddOut(VD(CENTER,AUDIO),1);
	t.AddOut(VD(CENTER,AUDIO),1);
	t.AddOut(VD(CENTER,AUDIO),1);
	return t;
}

LinkTypeCls CoreDrummerPipe::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void CoreDrummerPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<CoreDrummerInstrument>(this);
}

AtomTypeCls CoreDrummerPipe::GetType() const {
	return GetAtomType();
}


String CoreEffectPipe::GetAction() {
	return "corefx.pipe";
}

AtomTypeCls CoreEffectPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::CORE_EFFECT_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,AUDIO),0);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddOut(VD(CENTER,AUDIO),0);
	return t;
}

LinkTypeCls CoreEffectPipe::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void CoreEffectPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<AudioCoreEffect>(this);
}

AtomTypeCls CoreEffectPipe::GetType() const {
	return GetAtomType();
}


String CoreEffectAtom::GetAction() {
	return "corefx.atom";
}

AtomTypeCls CoreEffectAtom::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::CORE_EFFECT_ATOM;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddIn(VD(CENTER,AUDIO),1);
	t.AddOut(VD(CENTER,AUDIO),0);
	return t;
}

LinkTypeCls CoreEffectAtom::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void CoreEffectAtom::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<AudioCoreEffect>(this);
}

AtomTypeCls CoreEffectAtom::GetType() const {
	return GetAtomType();
}


#if defined flagLV2
String LV2EffectPipe::GetAction() {
	return "lv2.effect.pipe";
}

AtomTypeCls LV2EffectPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::LV2_EFFECT_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,AUDIO),0);
	t.AddOut(VD(CENTER,AUDIO),0);
	return t;
}

LinkTypeCls LV2EffectPipe::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void LV2EffectPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<LV2Effect>(this);
}

AtomTypeCls LV2EffectPipe::GetType() const {
	return GetAtomType();
}
#endif


#if (defined flagBUILTIN_PORTMIDI) || (defined flagPORTMIDI)
String PortmidiPipe::GetAction() {
	return "midi.src.portmidi";
}

AtomTypeCls PortmidiPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::PORTMIDI_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,MIDI),0);
	return t;
}

LinkTypeCls PortmidiPipe::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void PortmidiPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<PortmidiSource>(this);
}

AtomTypeCls PortmidiPipe::GetType() const {
	return GetAtomType();
}
#endif


#if (defined flagBUILTIN_PORTMIDI) || (defined flagPORTMIDI)
String PortmidiSend::GetAction() {
	return "midi.src.side.portmidi";
}

AtomTypeCls PortmidiSend::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::PORTMIDI_SEND;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,RECEIPT),0);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	t.AddOut(VD(CENTER,MIDI),1);
	return t;
}

LinkTypeCls PortmidiSend::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void PortmidiSend::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<PortmidiSource>(this);
}

AtomTypeCls PortmidiSend::GetType() const {
	return GetAtomType();
}
#endif


String CoreAudioFileOut::GetAction() {
	return "audio.file.writer";
}

AtomTypeCls CoreAudioFileOut::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::CORE_AUDIO_FILE_OUT;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,AUDIO),0);
	t.AddOut(VD(CENTER,RECEIPT),0);
	return t;
}

LinkTypeCls CoreAudioFileOut::GetLinkType() {
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void CoreAudioFileOut::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<CoreAudioSink>(this);
}

AtomTypeCls CoreAudioFileOut::GetType() const {
	return GetAtomType();
}


}

}

