#include "AudioCtrl.h"

NAMESPACE_TOPSIDE_BEGIN

INITBLOCK_(MidiFileCtrl) {
	MakeComponentCtrlFactory<MidiFileComponent, MidiFileCtrl>();
}


MidiFileCtrl::MidiFileCtrl() {
	
}

void MidiFileCtrl::Reset() {
	
}

void MidiFileCtrl::Updated() {
	if (IsModified()) {
		LOG("MidiFileCtrl::Updated");
		ClearModify();
	
	}
}

void MidiFileCtrl::SetComponent(ComponentBase& base) {
	MidiFileComponent* new_comp = CastPtr<MidiFileComponent>(&base);
	if (new_comp && new_comp == comp)
		return;
	
	Reset();
	comp = new_comp;
	
	if (!comp) {
		LOG("MidiFileCtrl: error: unexpected component");
		return;
	}
	
	SetModify();
}


NAMESPACE_TOPSIDE_END
