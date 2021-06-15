#include "Sequencer.h"


NAMESPACE_TOPSIDE_BEGIN


Track::Track() {
	title = "Default";
	
	
}

Block& Track::GetBlock(int i) {
	if (i < 0 || i >= blocks.GetCount())
		throw Exc("Block doesn't exist");
	return blocks[i];
}





Session::Session() {
	GetMidi().WhenNote << THISBACK(MidiIn);
	
	Track& t = tracks.Add();
	t.SetInput().Set(sys.Find<SimpleOscillator>());
	t.SetEffect(0).Set(sys.Find<SimpleReverb>());
	Block& b = t.AddBlock();
	for(int i = 0; i < 100; i++) {
		Note& n = b.AddNote();
		n.SetShift(Random(BARSIZE));
		n.SetLength(4);
		n.SetPitch(Random(8*12));
		n.SetVelocity(Random(255));
	}
	
	Data();
}

void Session::Data() {
	
	sys.Enter();
	
	for(int i = sys.GetSourceCount(); i < tracks.GetCount(); i++) {
		Bus& nc = sys.AddSource();
		nc.output.bus = 0;
	}
	
	for(int i = sys.GetSourceCount()-1; i >= tracks.GetCount(); i--) {
		sys.RemoveSource(i);
	}
	
	for(int i = 0; i < tracks.GetCount(); i++) {
		Bus& src = sys.GetSource(i);
		Track& t = tracks[i];
		
		sys.SetInput(src, t.GetInput());
		
		for(int j = 0; j < t.GetFxCount(); j++) {
			sys.SetEffect(
				src,
				t.GetFxKey(j),
				t.GetFx(j));
		}
	}
	
	sys.Leave();
}

Track& Session::GetTrack(int i) {
	if (i < 0 || i >= tracks.GetCount())
		throw Exc("Track doesn't exist");
	return tracks[i];
}

void Session::Do(const Op& op) {
	if (!is_group_op) {
		redo_history.Clear();
		
		undo_history.Add(op);
		
		Redo(op);
		
		WhenAction();
	} else {
		group_op.AddOp(op);
	}
}

void Session::DoBegin() {
	group_op.Clear();
	is_group_op = true;
}

void Session::DoEnd() {
	is_group_op = false;
	Do(group_op);
}

void Session::Undo(const Op& op) {
	
	
	switch (op.GetInt(0)) {
		
		case OP_ADDTRACK:
			tracks.pop_back();
			Data();
			break;
			
		case OP_ADDBLOCK:
			tracks[op.GetInt(1)].PopBlock();
			break;
		
		case OP_MOVEBLOCK:
			tracks[op.GetInt(1)].GetBlock(op.GetInt(2))
				.SetShift(op.GetInt(5))
				.SetSize(op.GetInt(6));
			break;
			
		case OP_MOVEBLOCKTRACK:
			tracks[op.GetInt(1)].PickBlock(tracks[op.GetInt(3)], tracks[op.GetInt(3)].GetBlockCount()-1);
			break;
			
		case OP_REMOVETRACK:
			op.Load(tracks.Insert(op.GetInt(1)));
			break;
			
		case OP_MOVENOTE:
			op.Load(tracks[op.GetInt(1)].GetBlock(op.GetInt(2)).GetNote(op.GetInt(3)));
			break;
		
		case OP_ADDNOTE:
			tracks[op.GetInt(1)].GetBlock(op.GetInt(2)).PopNote();
			break;
		
		case OP_REMNOTE:
			op.Load(tracks[op.GetInt(1)].GetBlock(op.GetInt(2)).InsertNote(op.GetInt(3)));
			break;
	}
	
	for(int i = op.GetOpCount()-1; i >= 0; i--) {
		Undo(op.GetOp(i));
	}
}

void Session::Redo(const Op& op) {
	
	switch (op.GetInt(0)) {
		
		case OP_ADDTRACK:
			tracks.Add()
				.SetInput().Set(op.GetInt(1));
			Data();
			break;
			
		case OP_ADDBLOCK:
			tracks[op.GetInt(1)].AddBlock().SetShift(op.GetInt(2));
			break;
		
		case OP_MOVEBLOCK:
			tracks[op.GetInt(1)].GetBlock(op.GetInt(2))
				.SetShift(op.GetInt(3))
				.SetSize(op.GetInt(4));
			break;
			
		case OP_MOVEBLOCKTRACK:
			tracks[op.GetInt(3)].PickBlock(tracks[op.GetInt(1)], op.GetInt(2));
			break;
		
		case OP_REMOVETRACK:
			tracks.Remove(op.GetInt(1));
			break;
			
		case OP_MOVENOTE:
			tracks[op.GetInt(1)].GetBlock(op.GetInt(2)).GetNote(op.GetInt(3))
				.SetShift(op.GetInt(4))
				.SetLength(op.GetInt(5))
				.SetPitch(op.GetInt(6));
			break;
		
		case OP_ADDNOTE:
			tracks[op.GetInt(1)].GetBlock(op.GetInt(2)).AddNote()
				.SetShift(op.GetInt(3))
				.SetLength(op.GetInt(4))
				.SetPitch(op.GetInt(5));
			break;
		
		case OP_REMNOTE:
			tracks[op.GetInt(1)].GetBlock(op.GetInt(2)).RemoveNote(op.GetInt(3));
			break;
	}
	
	for(int i = 0; i < op.GetOpCount(); i++) {
		Redo(op.GetOp(i));
	}
}

void Session::Undo() {
	if (undo_history.IsEmpty())
		return;
	Undo(undo_history.Top());
	redo_history.Add(undo_history.Pop());
}

void Session::Redo() {
	if (redo_history.IsEmpty())
		return;
	Redo(redo_history.Top());
	undo_history.Add(redo_history.Pop());
}

void Session::Play() {
	
	try {
		Vector<PlayEvent> events;
		GetEvents(events);
		
		play_cursor = 0;
		while (play_cursor < events.GetCount()) {
			const PlayEvent& pe = events[play_cursor];
			if (pe.time >= time_cursor)
				break;
			play_cursor++;
		}
		if (play_cursor >= events.GetCount()) {
			play_cursor = 0;
			time_cursor = 0;
		}
		
		TimeStop ts;
		int prev_elapsed = 0;
		while (playing) {
			
			
			while (play_cursor < events.GetCount()) {
				const PlayEvent& pe = events[play_cursor];
				if (pe.time > time_cursor)
					break;
				
				if (pe.type == NOTE_ON) {
					Bus& bus = sys.GetSource(pe.track);
					bus.NoteOn(pe.freq, pe.ampl);
					close_notes.Add(CloseNote(pe.track, pe.freq));
				}
				else if (pe.type == NOTE_OFF) {
					Bus& bus = sys.GetSource(pe.track);
					bus.NoteOff(pe.freq);
				}
				
				play_cursor++;
			}
			
			if (play_cursor >= events.GetCount())
				playing = false;
			
			int elapsed = ts.Elapsed();
			int elapsed_diff = elapsed - prev_elapsed;
			time_cursor += elapsed_diff;
			
			prev_elapsed = elapsed;
			
			WhenTimeChanges();
			Sleep(1);
		}
	}
	catch (Exc e) {
		LOG(e);
	}
	playing = false;
	stopped = true;
}

void Session::CloseNotes() {
	for(int i = 0; i < close_notes.GetCount(); i++) {
		int track = close_notes[i].a;
		double freq = close_notes[i].b;
		Bus& bus = sys.GetSource(track);
		bus.NoteOff(freq);
	}
}

void Session::MidiIn(int note, int vel) {
	Bus& bus = sys.GetSource(0);
	
	if (vel > 0) {
		double freq = Note::GetFrequencyPitch(note);
		bus.NoteOn(freq, vel / 128.0);
	} else {
		double freq = Note::GetFrequencyPitch(note);
		bus.NoteOff(freq);
	}
}

void Session::GetEvents(Vector<PlayEvent>& events) const {
	events.SetCount(0);
	events.Reserve(1000);
	
	for(int i = 0; i < tracks.GetCount(); i++) {
		const Track& t = tracks[i];
		
		for(int j = 0; j < t.GetBlockCount(); j++) {
			const Block& b = t.GetBlock(j);
			
			for(int k = 0; k < b.GetNoteCount(); k++) {
				const Note& n = b.GetNote(k);
				PlayEvent& note_on = events.Add();
				PlayEvent& note_off = events.Add();
				
				int shift = b.GetShift() + n.GetShift();
				
				note_on.time = GetTimeFromShift(shift);
				note_on.type = NOTE_ON;
				note_on.track = i;
				note_on.freq = n.GetFrequency();
				note_on.ampl = n.GetVelocity() / 255.0;
				
				shift += n.GetLength();
				note_off.time = GetTimeFromShift(shift);
				note_off.type = NOTE_OFF;
				note_off.track = i;
				note_off.freq = n.GetFrequency();
				note_off.ampl = 0.0;
			}
		}
	}
	
	Sort(events, PlayEvent());
}

int Session::GetTimeFromShift(int shift) const {
	return (double)shift / BARSIZE * 4.0 * tempo / 60.0 * 1000;
}




Block::Block() {
	
}










Note::Note() {
	
}



NAMESPACE_TOPSIDE_END
