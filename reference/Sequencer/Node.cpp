#include "Sequencer.h"


NAMESPACE_TOPSIDE_BEGIN


NodeParentCtrl::NodeParentCtrl() {
	
}

SessionEditor& NodeParentCtrl::GetEditor() {
	Ctrl* c = this;
	while (c) {
		c = c->GetParent();
		SessionEditor* se = CastPtr<SessionEditor>(c);
		if (se) return *se;
	}
	throw Exc("Couldn't find editor");
}

TrackListCtrl& NodeParentCtrl::GetTrackList() {
	Ctrl* c = this;
	while (c) {
		c = c->GetParent();
		TrackListCtrl* se = CastPtr<TrackListCtrl>(c);
		if (se) return *se;
	}
	throw Exc("Couldn't find tracklist");
}


NAMESPACE_TOPSIDE_END

