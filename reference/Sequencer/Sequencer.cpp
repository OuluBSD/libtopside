#include "Sequencer.h"

#define IMAGECLASS SequencerImg
#define IMAGEFILE <Sequencer/Images.iml>
#include <Draw/iml_source.h>

NAMESPACE_TOPSIDE_BEGIN

FileSel& SequencerFs()
{
	static FileSel fs;
	return fs;
}

FileSel& MidiFs()
{
	static FileSel fs;
	return fs;
}



Sequencer::Sequencer()
{
	Title("Sequencer");
	Icon(SequencerImg::icon());
	Sizeable().MaximizeBox().MinimizeBox();
	
	AddFrame(menubar);
	AddFrame(TopSeparatorFrame());
	AddFrame(toolbar);
	AddFrame(statusbar);
	Add(editor.SizePos());
	
	
	menubar.Set(THISFN(MainBar));
	WhenClose = THISBACK(Destroy);
	menubar.WhenHelp = toolbar.WhenHelp = statusbar;
	
	editor.ClearModify();
	
	SetBar();
	editor.WhenRefreshBar = THISBACK(SetBar);
	
	OpenMain();
	ActiveFocus(editor);
}

void Sequencer::SerializeApp(Stream& s) {
	int version = 1;
	s / version;
	s % SequencerFs()
	  % MidiFs();
	if (version >= 1)
		s % lrufile();
}

void Sequencer::DragAndDrop(Point, PasteClip& d) {
	if(IsAvailableFiles(d)) {
		Vector<String> fn = GetFiles(d);
		for(int open = 0; open < 2; open++) {
			for(int i = 0; i < fn.GetCount(); i++) {
				String ext = GetFileExt(fn[i]);
				if(FileExists(fn[i]) && (ext == ".rtf" || ext == ".qtf")) {
					if(open)
						OpenFile(fn[i]);
					else {
						if(d.Accept())
							break;
						return;
					}
				}
			}
			if(!d.IsAccepted())
				return;
		}
	}
}

void Sequencer::FrameDragAndDrop(Point p, PasteClip& d) {
	DragAndDrop(p, d);
}

void Sequencer::SetBar() {
	toolbar.Set(THISBACK(MainBar));
}

void Sequencer::MainBar(Bar& bar)
{
	bar.Sub("File", [=](Bar& bar) {
		bar.Add("New Session", CtrlImg::new_doc(), THISBACK(New))
			.Key(K_CTRL_N)
			.Help("Open new session");
		bar.Add("Open..", CtrlImg::open(), THISBACK(Open))
		   .Key(K_CTRL_O)
		   .Help("Open existing session");
		bar.Add("Save", CtrlImg::save(), THISBACK(Save))
			.Key(K_CTRL_S)
			.Help("Save current session");
		bar.Add("Save As", CtrlImg::save_as(), THISBACK(SaveAs))
			.Help("Save current session with a new name");
		
		if(bar.IsMenuBar()) {
			if(lrufile().GetCount())
				lrufile()(bar, THISBACK(OpenFile));
			bar.Separator();
			bar.Add("Exit", THISBACK(Destroy));
		}
	});
	
	bar.Sub("Edit", [=](Bar& bar) {
		editor.SubBar(bar);
	});
	
	
	if (!bar.IsToolBar()) {
		
	}
	else {
		
	}
	
	
	bar.Sub("Help", [=](Bar& bar) {
		bar.Add("Index", SequencerImg::question(), THISBACK(Index));
		bar.Add("About..", SequencerImg::information(), THISBACK(About));
		
		bar.Add("Help topics",SequencerImg::help(), [&] {
			HelpWindow help;
			help.GoTo("topic://Topic/app/main$en-us");
			help.Execute();
		})
			.Key(K_F1)
			.Help("Opens help window");
	});
}

void Sequencer::New() {
	new Sequencer;
}

void Sequencer::Open() {
	FileSel& fs = SequencerFs();
	if(fs.ExecuteOpen())
		OpenFile(fs);
	else
		statusbar.Temporary("Loading aborted.");
}

void Sequencer::Save0()
{
	lrufile().NewEntry(filename);
	if(filename.IsEmpty())
		SaveAs();
	else {
		/*if (SaveFile(filename, editor.GetXml())) {
			statusbar.Temporary("File " + filename + " was saved.");
			ClearModify();
		}
		else*/
			Exclamation("Error saving the file [* " + DeQtf(filename) + "]!");
	}
}

void Sequencer::Save() {
	if(!editor.IsModified()) return;
	Save0();
}

void Sequencer::SaveAs() {
	FileSel& fs = SequencerFs();
	if(fs.ExecuteSaveAs()) {
		filename = fs;
		Title(filename);
		Save0();
	}
}

void Sequencer::Load(const String& name) {
	lrufile().NewEntry(name);
	//editor.SetXml(LoadFile(name));
	PromptOK("TODO");
	filename = name;
	editor.ClearModify();
	Title(filename);
}

void Sequencer::OpenFile(const String& fn) {
	if(filename.IsEmpty() && !editor.IsModified())
		Load(fn);
	else
		(new Sequencer)->Load(fn);
}

void Sequencer::Destroy() {
	if(editor.IsModified()) {
		switch(PromptYesNoCancel("Do you want to save the changes to the document?")) {
		case 1:
			Save();
			break;
		case -1:
			return;
		}
	}
	delete this;
}


void Sequencer::Index() {
	
}

void Sequencer::About() {
	PromptOK("[A5 Sequencer]&Using [*^www://upp.sf.net^ Ultimate`+`+] technology.");
}

NAMESPACE_TOPSIDE_END
