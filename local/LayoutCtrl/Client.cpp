#include "LayoutCtrl.h"


NAMESPACE_LAYOUT_BEGIN


Client::Client()
{
	Title("Overlay client");
	Sizeable().MaximizeBox().MinimizeBox();
	
	AddFrame(menu);
	
	menu.Set(THISBACK(MainMenu));
	
	Add(browser.SizePos());
}

void Client::MainMenu(Bar& bar) {
	
}


NAMESPACE_LAYOUT_END
