#ifndef _CtrlCore_DnD_h_
#define _CtrlCore_DnD_h_

NAMESPACE_UPP_BEGIN


struct ClipData : Moveable<ClipData> {
	Value  data;
	String (*render)(const Value& data);

	String  Render() const                   { return render ? (*render)(data) : ~data; }

	ClipData(const Value& data, String (*render)(const Value& data));
	ClipData(const String& data);
	ClipData();
};


class PasteClip {
	friend struct UDropTarget;
	friend class  Ctrl;
	friend PasteClip sMakeDropClip(bool paste);

	GUIPLATFORM_PASTECLIP_DECLS

	byte         action;
	byte         allowed;
	bool         paste;
	bool         accepted;
	String       fmt;
	String       data;

	void GuiPlatformConstruct();

public:
	bool   IsAvailable(const char *fmt) const;
	String Get(const char *fmt) const;

	bool   Accept();

	bool   Accept(const char *fmt);
	String GetFormat()                  { return fmt; }
	String Get() const                  { return data; }
	operator String() const             { return Get(); }
	String operator ~() const           { return Get(); }

	void   Reject()                     { accepted = false; }

	int    GetAction() const            { return action; }
	int    GetAllowedActions() const    { return allowed; }
	void   SetAction(int x)             { action = x; }

	bool   IsAccepted() const           { return accepted; }

	bool   IsQuery() const              { return !paste; }
	bool   IsPaste() const              { return paste; }

	PasteClip();
};


NAMESPACE_UPP_END

#endif
