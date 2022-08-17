#include "AtomAudio.h"

namespace TS {

namespace Parallel {

AtomTypeCls MidiFileReaderPipe::GetAtomType()
{
	return ATOM11(MIDI_FILE_READER_PIPE, PIPE, CENTER, MIDI, CENTER, ORDER, CENTER, MIDI);
}

LinkTypeCls MidiFileReaderPipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void MidiFileReaderPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<MidiFileReaderAtom>(this);
}

AtomTypeCls MidiFileReaderPipe::GetType() const
{
	return GetAtomType();
}

AtomTypeCls MidiFileReader::GetAtomType()
{
	return ATOM11_U01(MIDI_FILE_READER, PIPE, CENTER, MIDI, CENTER, ORDER, CENTER, RECEIPT, CENTER, MIDI);
}

LinkTypeCls MidiFileReader::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void MidiFileReader::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<MidiFileReaderAtom>(this);
}

AtomTypeCls MidiFileReader::GetType() const
{
	return GetAtomType();
}

AtomTypeCls MidiNullSink::GetAtomType()
{
	return ATOM11(MIDI_NULL_SINK, PIPE, CENTER, MIDI, CENTER, MIDI, CENTER, RECEIPT);
}

LinkTypeCls MidiNullSink::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void MidiNullSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<MidiNullAtom>(this);
}

AtomTypeCls MidiNullSink::GetType() const
{
	return GetAtomType();
}

AtomTypeCls FluidsynthPipe::GetAtomType()
{
	return ATOM11_U10(FLUIDSYNTH_PIPE, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, MIDI, CENTER, AUDIO);
}

LinkTypeCls FluidsynthPipe::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void FluidsynthPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<FluidsynthInstrument>(this);
}

AtomTypeCls FluidsynthPipe::GetType() const
{
	return GetAtomType();
}

AtomTypeCls SoftInstrumentPipe::GetAtomType()
{
	return ATOM11_U10(SOFT_INSTRUMENT_PIPE, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, MIDI, CENTER, AUDIO);
}

LinkTypeCls SoftInstrumentPipe::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void SoftInstrumentPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SoftInstrument>(this);
}

AtomTypeCls SoftInstrumentPipe::GetType() const
{
	return GetAtomType();
}

AtomTypeCls FmSynthPipe::GetAtomType()
{
	return ATOM11_U10(FM_SYNTH_PIPE, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, MIDI, CENTER, AUDIO);
}

LinkTypeCls FmSynthPipe::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void FmSynthPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<FmSynthInstrument>(this);
}

AtomTypeCls FmSynthPipe::GetType() const
{
	return GetAtomType();
}

AtomTypeCls CoreSynthPipe::GetAtomType()
{
	return ATOM11_U10(CORE_SYNTH_PIPE, PIPE, CENTER, AUDIO, CENTER, ORDER, CENTER, MIDI, CENTER, AUDIO);
}

LinkTypeCls CoreSynthPipe::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void CoreSynthPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CoreSynthInstrument>(this);
}

AtomTypeCls CoreSynthPipe::GetType() const
{
	return GetAtomType();
}

AtomTypeCls CoreEffectPipe::GetAtomType()
{
	return ATOM11(CORE_EFFECT_PIPE, PIPE, CENTER, AUDIO, CENTER, AUDIO, CENTER, AUDIO);
}

LinkTypeCls CoreEffectPipe::GetLinkType()
{
	return LINKTYPE(PIPE_OPTSIDE, PROCESS);
}

void CoreEffectPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<AudioCoreEffect>(this);
}

AtomTypeCls CoreEffectPipe::GetType() const
{
	return GetAtomType();
}

}

}

