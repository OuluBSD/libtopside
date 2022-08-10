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
	return LINKTYPE(PIPE, PROCESS);
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
	return LINKTYPE(PIPE, PROCESS);
}

void FluidsynthPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<FluidsynthInstrument>(this);
}

AtomTypeCls FluidsynthPipe::GetType() const
{
	return GetAtomType();
}

}

}
