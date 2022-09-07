#ifndef _MIDIEVENTLIST_H_INCLUDED
#define _MIDIEVENTLIST_H_INCLUDED


NAMESPACE_MIDI_BEGIN

class EventList {

public:
	EventList();
	
	~EventList();
	
	EventList(const EventList& other);
	EventList(EventList && other);
	
	Event&  operator[](int index);
	const Event&  operator[](int index) const;
	Event&  Top();
	Event&  Last();
	Event&  GetEvent(int index);
	void        Clear();
	void        Reserve(int rsize);
	int         GetCount() const;
	int         LinkNotePairs();
	int         LinkEventPairs() {return LinkNotePairs();}
	int			Link() {return LinkNotePairs();}
	void        ClearLinks();
	//Event** GetData();
	
	int         Push(Event& event);
	int         Add(Event& event);
	int         Append(Event& event);
	
	// careful when using these, intended for internal use in File class:
	Event&  Add() {return list.Add();}
	
	EventList& operator=(const EventList& other);
	
protected:
	friend class File;
	
	Array<Event>     list;
	
};

NAMESPACE_MIDI_END

#endif
