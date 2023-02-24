#ifndef _CtrlCoreAlt_TopWindow_h_
#define _CtrlCoreAlt_TopWindow_h_


NAMESPACE_UPP


enum {
	IDEXIT = 9999
};

class TopWindow :
	public Ctrl
{
	#ifdef GUIPLATFORM_TOPWINDOW_DECLS_INCLUDE
	#include GUIPLATFORM_TOPWINDOW_DECLS_INCLUDE
	#endif
	
public:
	RTTI_DECL1(TopWindow, Ctrl)
	typedef TopWindow CLASSNAME;
	TopWindow();
	virtual ~TopWindow() {}
	
	void UpdateFromTransform2D();
	void RunInMachine();
	int Run();
	
	static void ShutdownWindows();
	
	enum { MINIMIZED, MAXIMIZED, OVERLAPPED };
	
private:
	struct Abreak : Pte<Abreak> {
		int         ID;
		TopWindow *dlg;

		void    Accept()      { dlg->AcceptBreak(ID); }
		void    Reject()      { dlg->RejectBreak(ID); }
		void    Break()       { dlg->Break(ID); }
	};

	Array<Abreak> action;
	Ptr<Ctrl>     activefocus;
	String        backup;
	PaintRect     background;
	Size          minsize;
	bool          dokeys;
	bool          fullscreen;

	byte          center:2;
	
	int           exitcode = 0;

	WString     title;
	bool        minimizebox:1;
	bool        maximizebox:1;
	bool        noclosebox:1;
	bool        sizeable:1;
	bool        tool:1;
	bool        frameless:1;
	bool        urgent:1;
	bool        close_rejects:1;
	byte        state;
	Image       icon, largeicon;
	
public:
	void        SyncSizeHints();
	void        SyncTitle();
	void        SyncCaption();
	void       Open(Ctrl *owner);
	void       Open();
	void       OpenMain();
	void       Minimize(bool effect = false);
	void       Maximize(bool effect = false);
	void       Overlap(bool effect = false);
	TopWindow& FullScreen(bool b = true);
	TopWindow& TopMost(bool b = true, bool stay_top = true);
	void        Break(int ID = IDEXIT);
	bool        AcceptBreak(int ID);
	void        RejectBreak(int ID);
	bool       IsTopMost() const;
	void        GuiPlatformConstruct();
	void        GuiPlatformDestruct();
	void       SerializePlacement(Stream& s, bool reminimize = false);
	
	TopWindow& Title(String title);
	TopWindow& Icon(Image img);
	
};


END_UPP_NAMESPACE


#endif
