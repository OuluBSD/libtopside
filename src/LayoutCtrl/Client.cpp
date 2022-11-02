#include "LayoutCtrl.h"


NAMESPACE_LAYOUT_BEGIN


Client::Client()
{
	Title("libtopside client");
	Sizeable().MaximizeBox().MinimizeBox();
	
	AddFrame(menu);
	
	menu.Set(THISBACK(MainMenu));
	
	Add(browser.SizePos());
}

void Client::MainMenu(Bar& bar) {
	
}


NAMESPACE_LAYOUT_END
