#ifndef _PlayEditor_App_h_
#define _PlayEditor_App_h_

NAMESPACE_TOPSIDE_BEGIN


class PlayEditor : public TopWindow {
	
	
	void OnMessage(const ProcMsg& p);
	
public:
	typedef PlayEditor CLASSNAME;
	
	PlayEditor();
	
	bool LoadFile(String path);
	bool Load(String content, String path);
	
};


NAMESPACE_TOPSIDE_END

#endif
