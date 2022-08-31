#include "LocalPlan.h"

#ifdef flagMAIN
using namespace TS;

CONSOLE_APP_MAIN {
	InterfaceBuilder ib;
	
	ib.AddAudio();
	ib.AddHal();
	ib.AddScreen();
	ib.AddVolumetric();
	ib.AddCamera();
	ib.AddHolographic();
	ib.AddSynth();
	ib.AddEffect();
	ib.AddMidiHw();
	
	ib.Headers();
	
	ib.Generate(1);
	
}


#endif
