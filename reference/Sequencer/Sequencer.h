#ifndef _Sequencer_Sequencer_h_
#define _Sequencer_Sequencer_h_

#include <CtrlLib/CtrlLib.h>
#include <CodeEditor/CodeEditor.h>
#include <AudioCore/AudioCore.h>
using namespace UPP;

#define IMAGECLASS SequencerImg
#define IMAGEFILE <Sequencer/Images.iml>
#include <Draw/iml_header.h>

#undef DLOG
//#define DLOG(x) LOG(x);
#define DLOG(x);

#include "Core.h"
#include "Midi.h"
#include "System.h"
#include "Parts.h"
#include "Simple.h"
#include "Node.h"
#include "ExprCtrl.h"
#include "Session.h"
#include "TrackEditor.h"
#include "TrackListCtrl.h"
#include "SessionTrackCtrl.h"
#include "SessionEditor.h"

NAMESPACE_TOPSIDE_BEGIN


FileSel& SequencerFs();
FileSel& MidiFs();


class Sequencer : public TopWindow {
	SessionEditor    editor;
	MenuBar          menubar;
	ToolBar          toolbar;
	StatusBar        statusbar;
	String           filename;
	
	
	static LRUList& lrufile() { static LRUList l; return l; }
	
protected:
	
	void New();
	void Open();
	void Save();
	void Save0();
	void SaveAs();
	void SaveAll();
	void Load(const String& filename);
	void OpenFile(const String& fn);
	void Destroy();
	
	void Index();
	void About();
	
	
	void SetBar();
	void MainBar(Bar& bar);
	
	
public:
	typedef Sequencer CLASSNAME;
	Sequencer();
	
	virtual void DragAndDrop(Point, PasteClip& d);
	virtual void FrameDragAndDrop(Point, PasteClip& d);

	static void SerializeApp(Stream& s);
	
};


NAMESPACE_TOPSIDE_END


#endif
