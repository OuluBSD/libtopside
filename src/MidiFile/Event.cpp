#include "MidiFile.h"


NAMESPACE_MIDI_BEGIN

//////////////////////////////
//
// Event::Event -- Constructor classes
//

Event::Event() : Message() {
	ClearVariables();
}


Event::Event(int command) : Message(command)  {
	ClearVariables();
}


Event::Event(int command, int p1) : Message(command, p1) {
	ClearVariables();
}


Event::Event(int command, int p1, int p2)
		: Message(command, p1, p2) {
	ClearVariables();
}


Event::Event(int time, int track, Vector<uint8>& message)
		: Message(message) {
	tick      = time;
	track     = track;
	eventlink = NULL;
}


Event::Event(const Event& mfevent) {
	tick    = mfevent.tick;
	track   = mfevent.track;
	seconds = mfevent.seconds;
	seq     = mfevent.seq;
	eventlink = NULL;
	this->SetCount(mfevent.GetCount());
	
	for (int i = 0; i < MsgVec::GetCount(); i++) {
		(*this)[i] = mfevent[i];
	}
}



//////////////////////////////
//
// Event::~Event -- File Event destructor
//

Event::~Event() {
	tick  = -1;
	track = -1;
	this->SetCount(0);
	eventlink = NULL;
}


//////////////////////////////
//
// Event::ClearVariables --  Clear everything except Message data.
//

void Event::ClearVariables() {
	tick      = 0;
	track     = 0;
	seconds   = 0.0;
	seq       = 0;
	eventlink = NULL;
}


//////////////////////////////
//
// Event::operator= -- Copy the contents of another Event.
//

Event& Event::operator=(const Event & mfevent) {
	if (this == &mfevent) {
		return *this;
	}
	
	tick    = mfevent.tick;
	
	track   = mfevent.track;
	seconds = mfevent.seconds;
	seq     = mfevent.seq;
	eventlink = NULL;
	this->SetCount(mfevent.GetCount());
	
	for (int i = 0; i < MsgVec::GetCount(); i++) {
		(*this)[i] = mfevent[i];
	}
	
	return *this;
}


Event& Event::operator=(const Message & message) {
	if (this == &message) {
		return *this;
	}
	
	ClearVariables();
	
	this->SetCount(message.GetCount());
	
	for (int i = 0; i < MsgVec::GetCount(); i++) {
		(*this)[i] = message[i];
	}
	
	return *this;
}


Event& Event::operator=(const Vector<uint8>& bytes) {
	ClearVariables();
	this->SetCount(bytes.GetCount());
	
	for (int i = 0; i < MsgVec::GetCount(); i++) {
		(*this)[i] = bytes[i];
	}
	
	return *this;
}


Event& Event::operator=(const Vector<char>& bytes) {
	ClearVariables();
	SetMessage(bytes);
	return *this;
}


Event& Event::operator=(const Vector<int>& bytes) {
	ClearVariables();
	SetMessage(bytes);
	return *this;
}



//////////////////////////////
//
// Event::UnlinkEvent -- Disassociate this event with another.
//   Also tell the other event to disassociate from this event.
//

void Event::UnlinkEvent() {
	if (eventlink == NULL) {
		return;
	}
	
	Event* mev = eventlink;
	
	eventlink = NULL;
	mev->UnlinkEvent();
}



//////////////////////////////
//
// Event::LinkEvent -- Make a link between two messages.
//   Unlinking
//

void Event::LinkEvent(Event* mev) {
	if (mev->eventlink != NULL) {
		// unlink other event if it is linked to something else;
		mev->UnlinkEvent();
	}
	
	// if this is already linked to something else, then unlink:
	
	if (eventlink != NULL) {
		eventlink->UnlinkEvent();
	}
	
	UnlinkEvent();
	
	mev->eventlink = this;
	eventlink = mev;
}


void Event::LinkEvent(Event& mev) {
	LinkEvent(&mev);
}



//////////////////////////////
//
// Event::GetLinkedEvent -- Returns a linked event.  Usually
//   this is the note-off message for a note-on message and vice-versa.
//   Returns null if there are no links.
//

Event* Event::GetLinkedEvent() {return eventlink;}
const Event* Event::GetLinkedEvent() const {return eventlink;}



//////////////////////////////
//
// Event::IsLinked -- Returns true if there is an event which is not
//   NULL.  This function is similar to GetLinkedEvent().
//

int Event::IsLinked() {
	return eventlink == NULL ? 0 : 1;
}



//////////////////////////////
//
// Event::GetTickDuration --  For linked events (note-ons and note-offs),
//    return the absolute tick time difference between the two events.
//    The tick values are presumed to be in absolute tick mode rather than
//    delta tick mode.  Returns 0 if not linked.
//

int Event::GetTickDuration() {
	Event* mev = GetLinkedEvent();
	
	if (mev == NULL) {
		return 0;
	}
	
	int tick2 = mev->tick;
	
	if (tick2 > tick) {
		return tick2 - tick;
	}
	
	else {
		return tick - tick2;
	}
}



//////////////////////////////
//
// Event::GetDurationInSeconds -- For linked events (note-ons and
//     note-offs), return the duration of the note in seconds.  The
//     seconds analysis must be done first; otherwise the duration will be
//     reported as zero.
//

double Event::GetDurationInSeconds() const {
	const Event* mev = GetLinkedEvent();
	
	if (mev == NULL) {
		return 0;
	}
	
	double seconds2 = mev->seconds;
	
	if (seconds2 > seconds) {
		return seconds2 - seconds;
	}
	
	else {
		return seconds - seconds2;
	}
}




String Event::ToString() const {
	String s;
	s << tick << "\t" << DblStr(seconds) << "\t";
	if (IsNoteOn())
		s << DblStr(GetDurationInSeconds());
	for (int i = 0; i < GetCount(); i++)
		s << "\t" << IntStr((*this)[i]);
	return s;
}

NAMESPACE_MIDI_END
