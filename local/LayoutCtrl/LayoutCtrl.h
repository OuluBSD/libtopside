#ifndef _LayoutCtrl_LayoutCtrl_h
#define _LayoutCtrl_LayoutCtrl_h

#include <LocalCtrl/LocalCtrl.h>


#include "Defs.h"
#include "TemplateUtils.h"
#include "Resources.h"
#include "Utils.h"
#include "Types.h"
#include "Object.h"
#include "Media.h"
#include "CssUtils.h"
#include "Table.h"
#include "Box.h"
#include "Css.h"
#include "Element.h"
#include "Document.h"
#include "Html.h"
#include "Editor.h"

NAMESPACE_LAYOUT_BEGIN


class Client : public TopWindow {
	
	static const int suggest_bar_height = 30;
	
	MenuBar menu;
	BrowserCtrl browser;
	
	
	void SetTitleReady(int req_id);
	
public:
	typedef Client CLASSNAME;
	Client();
	
	void MainMenu(Bar& bar);
	
	void SetAddress(String s) {browser.SetAddress(s);}
	
};


NAMESPACE_LAYOUT_END

#endif
