#ifndef _DAW_Links_h_
#define _DAW_Links_h_

NAMESPACE_PLAN_BEGIN


LINK(DawInstrumentToFx, DawMidiInstrument, DawFxChannel)
LINK(DawInstrumentToMaster, DawMidiInstrument, DawMasterChannel)
LINK(DawMasterToHw, DawMasterChannel, DawHwSink)


NAMESPACE_PLAN_END

#endif
