#include "MidiFile.h"


NAMESPACE_MIDI_BEGIN

//////////////////////////////
//
// EventList::EventList -- Constructor.
//

EventList::EventList() {
	Reserve(1000);
}



//////////////////////////////
//
// EventList::EventList(EventList&) -- Copy constructor.
//

EventList::EventList(const EventList& other) {
	list <<= other.list;
}



//////////////////////////////
//
// EventList::EventList(EventList&&) -- Move constructor.
//

EventList::EventList(EventList && other) : list(std::move(other.list)) {
	
}



//////////////////////////////
//
// EventList::~EventList -- Deconstructor.  Deallocate all stored
//   data.
//

EventList::~EventList() {
	Clear();
}



//////////////////////////////
//
// EventList::operator[] --
//

Event&  EventList::operator[](int index) {
	return list[index];
}


const Event&  EventList::operator[](int index) const {
	return list[index];
}



//////////////////////////////
//
// EventList::back -- Return the last element in the list.
//

Event& EventList::Top() {
	return list.Top();
}

// Alias for back:

Event& EventList::Last() {
	return Top();
}



//////////////////////////////
//
// EventList::getEvent -- The same thing as operator[], for
//      internal use when operator[] would look more messy.
//

Event& EventList::GetEvent(int index) {
	return list[index];
}



//////////////////////////////
//
// EventList::clear -- De-allocate any Events present in the list
//    and set the size of the list to 0.
//

void EventList::Clear() {
	list.SetCount(0);
}



//////////////////////////////
//
// EventList::data --
//

/*Event** EventList::GetData() {
	return list.GetData();
}*/



//////////////////////////////
//
// EventList::reserve --  Pre-allocate space in the list for storing
//     elements.
//

void EventList::Reserve(int rsize) {
	if (rsize > (int)list.GetCount()) {
		list.Reserve(rsize);
	}
}


//////////////////////////////
//
// EventList::getSize -- Return the number of Events stored in the list.
//

int EventList::GetCount() const {
	return (int)list.GetCount();
}


//////////////////////////////
//
// EventList::append -- add a Event at the end of the list.  Returns
//     the index of the appended event.
//

int EventList::Append(Event& event) {
	list.Add(event);
	return (int)list.GetCount() - 1;
}


int EventList::Push(Event& event) {
	return Append(event);
}


int EventList::Add(Event& event) {
	return Append(event);
}


//////////////////////////////
//
// EventList::linkNotePairs -- Match note-ones and note-offs together
//   There are two models that can be done if two notes are overlapping
//   on the same pitch: the first note-off affects the last note-on,
//   or the first note-off affects the first note-on.  Currently  the
//   first note-off affects the last note-on, but both methods could
//   be implemented with user selectability.  The current state of the
//   track is assumed to be in time-sorted order.  Returns the number
//   of linked notes (note-on/note-off pairs).
//


int EventList::LinkNotePairs() {

	// Note-on states:
	// dimension 1: MIDI channel (0-15)
	// dimension 2: MIDI key     (0-127)  (but 0 not used for note-ons)
	// dimension 3: List of active note-ons or note-offs.
	Vector<Vector<Vector<Event*> > > noteons;
	noteons.SetCount(16);
	
	for (int i = 0; i < (int)noteons.GetCount(); i++) {
		noteons[i].SetCount(128);
	}
	
	// Controller linking: The following General MIDI controller numbers are
	// also monitored for linking within the track (but not between tracks).
	// hex dec  name                                    range
	// 40  64   Hold pedal (Sustain) on/off             0..63=off  64..127=on
	// 41  65   Portamento on/off                       0..63=off  64..127=on
	// 42  66   Sustenuto Pedal on/off                  0..63=off  64..127=on
	// 43  67   Soft Pedal on/off                       0..63=off  64..127=on
	// 44  68   Legato Pedal on/off                     0..63=off  64..127=on
	// 45  69   Hold Pedal 2 on/off                     0..63=off  64..127=on
	// 50  80   General Purpose Button                  0..63=off  64..127=on
	// 51  81   General Purpose Button                  0..63=off  64..127=on
	// 52  82   General Purpose Button                  0..63=off  64..127=on
	// 53  83   General Purpose Button                  0..63=off  64..127=on
	// 54  84   Undefined on/off                        0..63=off  64..127=on
	// 55  85   Undefined on/off                        0..63=off  64..127=on
	// 56  86   Undefined on/off                        0..63=off  64..127=on
	// 57  87   Undefined on/off                        0..63=off  64..127=on
	// 58  88   Undefined on/off                        0..63=off  64..127=on
	// 59  89   Undefined on/off                        0..63=off  64..127=on
	// 5A  90   Undefined on/off                        0..63=off  64..127=on
	// 7A 122   Local Keyboard On/Off                   0..63=off  64..127=on
	
	// first keep track of whether the controller is an on/off switch:
	Vector<Tuple<int, int> > contmap;
	Tuple<int, int> zero(0, 0);
	
	contmap.SetCount(128, zero);
	
	contmap[64].a = 1;
	contmap[64].b = 0;
	contmap[65].a = 1;
	contmap[65].b = 1;
	contmap[66].a = 1;
	contmap[66].b = 2;
	contmap[67].a = 1;
	contmap[67].b = 3;
	contmap[68].a = 1;
	contmap[68].b = 4;
	contmap[69].a = 1;
	contmap[69].b = 5;
	contmap[80].a = 1;
	contmap[80].b = 6;
	contmap[81].a = 1;
	contmap[81].b = 7;
	contmap[82].a = 1;
	contmap[82].b = 8;
	contmap[83].a = 1;
	contmap[83].b = 9;
	contmap[84].a = 1;
	contmap[84].b = 10;
	contmap[85].a = 1;
	contmap[85].b = 11;
	contmap[86].a = 1;
	contmap[86].b = 12;
	contmap[87].a = 1;
	contmap[87].b = 13;
	contmap[88].a = 1;
	contmap[88].b = 14;
	contmap[89].a = 1;
	contmap[89].b = 15;
	contmap[90].a = 1;
	contmap[90].b = 16;
	contmap[122].a= 1;
	contmap[122].b = 17;
	
	// dimensions:
	// 1: mapped controller (0 to 17)
	// 2: channel (0 to 15)
	Vector<Vector<Event*> > contevents;
	contevents.SetCount(18);
	
	Vector<Vector<int> > oldstates;
	oldstates.SetCount(18);
	
	for (int i = 0; i < 18; i++) {
		contevents[i].SetCount(16, NULL);
		oldstates[i].SetCount(16, -1);
	}
	
	// Now iterate through the EventList keeping track of note and
	// select controller states and linking notes/controllers as needed.
	int channel;
	int key;
	int contnum;
	int contval;
	int conti;
	int contstate;
	int counter = 0;
	Event* mev;
	Event* noteon;
	
	for (int i = 0; i < GetCount(); i++) {
		mev = &GetEvent(i);
		mev->UnlinkEvent();
		
		if (mev->IsNoteOn()) {
			// store the note-on to pair later with a note-off message.
			key = mev->GetKeyNumber();
			channel = mev->GetChannel();
			noteons[channel][key].Add(mev);
		}
		
		else
		if (mev->IsNoteOff()) {
			key = mev->GetKeyNumber();
			channel = mev->GetChannel();
			
			if (noteons[channel][key].GetCount() > 0) {
				noteon = noteons[channel][key].Top();
				noteons[channel][key].Pop();
				noteon->LinkEvent(mev);
				counter++;
			}
		}
		
		else
		if (mev->IsController()) {
			contnum = mev->GetP1();
			
			if (contmap[contnum].a) {
				conti     = contmap[contnum].b;
				channel   = mev->GetChannel();
				contval   = mev->GetP2();
				contstate = contval < 64 ? 0 : 1;
				
				if ((oldstates[conti][channel] == -1) && contstate) {
					// a newly initialized onstate was detected, so store for
					// later linking to an off state.
					contevents[conti][channel] = mev;
					oldstates[conti][channel] = contstate;
				}
				else if (oldstates[conti][channel] == contstate) {
					// the controller state is redundant and will be ignored.
				}
				else if ((oldstates[conti][channel] == 0) && contstate) {
					// controller is currently off, so store on-state for next link
					contevents[conti][channel] = mev;
					oldstates[conti][channel] = contstate;
				}
				else if ((oldstates[conti][channel] == 1) && (contstate == 0)) {
					// controller has just been turned off, so link to
					// stored on-message.
					contevents[conti][channel]->LinkEvent(mev);
					oldstates[conti][channel] = contstate;
					// not necessary, but maybe use for something later:
					contevents[conti][channel] = mev;
				}
			}
		}
	}
	
	return counter;
}



//////////////////////////////
//
// EventList::clearLinks -- remove all note-on/note-off links.
//

void EventList::ClearLinks() {
	for (int i = 0; i < (int)GetCount(); i++) {
		GetEvent(i).UnlinkEvent();
	}
}



//////////////////////////////
//
// EventList::operator=(EventList) -- Assignment.
//

EventList& EventList::operator=(const EventList& other) {
	list <<= other.list;
	return *this;
}


NAMESPACE_MIDI_END
