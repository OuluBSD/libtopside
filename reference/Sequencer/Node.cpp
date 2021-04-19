#include "Sequencer.h"


NAMESPACE_OULU_BEGIN


NodeParentCtrl::NodeParentCtrl() {
	
}

SessionEditor& NodeParentCtrl::GetEditor() {
	Ctrl* c = this;
	while (c) {
		c = c->GetParent();
		SessionEditor* se = dynamic_cast<SessionEditor*>(c);
		if (se) return *se;
	}
	throw Exc("Couldn't find editor");
}

TrackListCtrl& NodeParentCtrl::GetTrackList() {
	Ctrl* c = this;
	while (c) {
		c = c->GetParent();
		TrackListCtrl* se = dynamic_cast<TrackListCtrl*>(c);
		if (se) return *se;
	}
	throw Exc("Couldn't find tracklist");
}


NAMESPACE_OULU_END

