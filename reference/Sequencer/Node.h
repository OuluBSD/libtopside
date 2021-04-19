#ifndef _Sequencer_Node_h_
#define _Sequencer_Node_h_

NAMESPACE_OULU_BEGIN

class SessionEditor;
class TrackCtrl;
class TrackListCtrl;

class NodeParentCtrl : public ParentCtrl {
	
	
public:
	NodeParentCtrl();
	
	SessionEditor& GetEditor();
	TrackListCtrl& GetTrackList();
	
};

template <class T>
class LeftDownHook : public T {
	
public:
	virtual void LeftDown(Point p, dword keyflags) {
		WhenLeftDown();
	}
	Callback WhenLeftDown;
};


NAMESPACE_OULU_END

#endif
