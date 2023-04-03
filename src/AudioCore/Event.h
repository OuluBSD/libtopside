#ifndef _MIDIEVENT_H_INCLUDED
#define _MIDIEVENT_H_INCLUDED


NAMESPACE_MIDI_BEGIN

class Event : public Message {

public:
	Event();
	Event(int command);
	Event(int command, int param1);
	Event(int command, int param1, int param2);
	Event(int time, int track, Vector<uint8>& message);
	Event(const Message& message);
	Event(const Event& mfevent);
	
	~Event();
	
	Event& operator= (const Event& mfevent);
	Event& operator= (const Message& message);
	Event& operator= (const Vector<uint8>& bytes);
	Event& operator= (const Vector<char>& bytes);
	Event& operator= (const Vector<int>& bytes);
	void       ClearVariables();
	
	// functions related to event linking (note-ons to note-offs).
	void       UnlinkEvent();
	void       UnlinkEvents();
	void       LinkEvent(Event* mev);
	void       LinkEvents(Event* mev);
	void       LinkEvent(Event& mev);
	void       LinkEvents(Event& mev);
	int        IsLinked();
	const Event*	GetLinkedEvent() const;
	Event*			GetLinkedEvent();
	int        GetTickDuration();
	float     GetDurationInSeconds() const;
	
	String     ToString() const;
	
	int       tick;
	int       track;
	float    seconds;
	int       seq;
	
private:
	Event* eventlink;      // used to match note-ons and note-offs
	
};

NAMESPACE_MIDI_END

#endif
