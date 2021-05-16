#ifndef _Sequencer_SessionEditor_h_
#define _Sequencer_SessionEditor_h_


NAMESPACE_TOPSIDE_BEGIN

	
class SessionEditor : public ParentCtrl {
	SessionTrackCtrl	trackctrl;
	TrackListCtrl		tracklist;
	TrackEditorCtrl		trackeditor;
	
	Session				ses;
	
	
	int mode = -1;
public:
	typedef SessionEditor CLASSNAME;
	SessionEditor();
	
	enum {TRACKLIST, AUDIOEDIT, MIDIEDIT};
	
	void Data();
	void TimeChanges();
	void PostTimeChanges() {PostCallback(THISBACK(TimeChanges));}
	void Undo();
	void Redo();
	void Play();
	void Stop();
	
	Session& GetSession() {return ses;}
	
	void SetMode(int i);
	void SetTrackList() {SetMode(TRACKLIST);}
	void SetAudioEditor() {SetMode(AUDIOEDIT);}
	void SetMidiEditor() {SetMode(MIDIEDIT);}
	void SetMidiEditor(int track, int block) {SetMode(MIDIEDIT); trackeditor.Set(track, block);}
	void SubBar(Bar& bar);
	
	Callback WhenRefreshBar;
	
	
};


NAMESPACE_TOPSIDE_END

#endif
