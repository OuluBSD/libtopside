#ifndef _DAW_Links_h_
#define _DAW_Links_h_


LINK(DawInstrumentToFx, DawMidiInstrument, DawFxChannel)
LINK(DawInstrumentToMaster, DawMidiInstrument, DawMasterChannel)
LINK(DawMasterToHw, DawMasterChannel, DawHwSink)


#endif
