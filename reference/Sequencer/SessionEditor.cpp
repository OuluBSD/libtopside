#include "Sequencer.h"


NAMESPACE_TOPSIDE_BEGIN


SessionEditor::SessionEditor() {
	Add(trackctrl.VSizePos().LeftPos(0,150));
	Add(tracklist.VSizePos().HSizePos(150,0));
	Add(trackeditor.SizePos());
	
	ses.WhenAction << THISBACK(Data);
	ses.WhenTimeChanges << THISBACK(PostTimeChanges);
	
	tracklist.AddTrack();
	tracklist.AddTrack();
	
	PostCallback(THISBACK1(SetMode, TRACKLIST));
}

void SessionEditor::SetMode(int i) {
	mode = i;
	
	trackctrl.Hide();
	tracklist.Hide();
	trackeditor.Hide();
	
	switch (i) {
		case TRACKLIST:
			trackctrl.Show();
			tracklist.Show();
			break;
		case AUDIOEDIT:
			break;
		case MIDIEDIT:
			trackeditor.Show();
			break;
	}
	
	Data();
}

void SessionEditor::Data() {
	switch (mode) {
		case TRACKLIST:
			trackctrl.Data();
			tracklist.Data();
			break;
		case AUDIOEDIT:
			break;
		case MIDIEDIT:
			trackeditor.Data();
			break;
	}
	PostTimeChanges();
	WhenRefreshBar();
}

void SessionEditor::TimeChanges() {
	switch (mode) {
		case TRACKLIST:
			tracklist.TimeChanges();
			break;
		case AUDIOEDIT:
			break;
		case MIDIEDIT:
			trackeditor.TimeChanges();
			break;
	}
}

void SessionEditor::Undo() {
	ses.Undo();
	Data();
	WhenRefreshBar();
}

void SessionEditor::Redo() {
	ses.Redo();
	Data();
	WhenRefreshBar();
}

void SessionEditor::Play() {
	if (ses.IsPlaying())
		ses.Stop();
	else
		ses.Start();
}

void SessionEditor::Stop() {
	ses.Stop();
	ses.Seek(0);
}

void SessionEditor::SubBar(Bar& bar) {
	bar.Add(ses.GetUndoHistory().GetCount(), "Undo",
		SequencerImg::undo, THISBACK(Undo)).Key(K_CTRL_Z);
	bar.Add(ses.GetRedoHistory().GetCount(), "Redo",
		SequencerImg::redo, THISBACK(Redo)).Key(K_CTRL_Y);
	
	bar.Separator();
	
	bar.Add("View tracklist", SequencerImg::viewtracklist, THISBACK1(SetMode, TRACKLIST)).Key(K_F2);
	bar.Add("View audio editor", SequencerImg::viewaudio, THISBACK1(SetMode, AUDIOEDIT)).Key(K_F3);
	bar.Add("View midi editor", SequencerImg::viewmidi, THISBACK1(SetMode, MIDIEDIT)).Key(K_F4);
	
	bar.Separator();
	
	bar.Add("Play", SequencerImg::play, THISBACK(Play)).Key(K_SPACE);
	bar.Add("Stop", SequencerImg::stop, THISBACK(Stop)).Key(K_HOME);
	
	switch (mode) {
		case TRACKLIST:
			tracklist.SubBar(bar);
			break;
		case AUDIOEDIT:
			break;
		case MIDIEDIT:
			trackeditor.SubBar(bar);
			break;
	}
}


NAMESPACE_TOPSIDE_END
