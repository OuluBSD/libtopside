#include "AudioCtrl.h"

NAMESPACE_OULU_BEGIN

INITBLOCK {
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
	MidiFileComponent* new_comp = dynamic_cast<MidiFileComponent*>(&base);
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


NAMESPACE_OULU_END
