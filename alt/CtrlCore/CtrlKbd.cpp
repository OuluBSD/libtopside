#include "CtrlCore.h"

NAMESPACE_UPP_BEGIN


String GetKeyDesc(dword key)
{
	String desc;
//	key &= 0xFFFF;

	if(key == 0)
		return desc;
	// TODO: Cocoa graphics https://tech.karbassi.com/2009/05/27/command-option-shift-symbols-in-unicode/
#ifdef PLATFORM_COCOA
	if(key & K_KEYUP) desc << t_("key\vUP ");
	if(key & K_CTRL)  desc << t_("key\v⌘");
	if(key & K_ALT)   desc << t_("key\v⌃");
	if(key & K_SHIFT) desc << t_("key\v⇧");
	if(key & K_OPTION) desc << t_("key\v⌥");
	key &= ~(K_CTRL | K_ALT | K_SHIFT | K_KEYUP | K_OPTION);
#else
	if(key & K_KEYUP) desc << t_("key\vUP ");
	if(key & K_CTRL)  desc << t_("key\vCtrl+");
	if(key & K_ALT)   desc << t_("key\vAlt+");
	if(key & K_SHIFT) desc << t_("key\vShift+");
	key &= ~(K_CTRL | K_ALT | K_SHIFT | K_KEYUP);
#endif

#ifdef PLATFORM_COCOA
	key &= ~(K_OPTION);
#endif
	if(key < K_DELTA && key > 32 && key != K_DELETE)
		return desc + ToUtf8((wchar)key);
	if(key >= K_NUMPAD0 && key <= K_NUMPAD9)
		desc << "Num " << (char)(key - K_NUMPAD0 + '0');
	else {
		for(int i = 0; KeyNames__[i].a; i++)
			if(KeyNames__[i].a == key) {
				desc << GetLngString(KeyNames__[i].b);
				return desc;
			}
		desc << Format("%04x", (int)key);
	}
	return desc;
}

void Ctrl::SetFocusWnd()
{
	TODO
	/*GuiLock __;
	// notification, don't set host platform focus here
	LLOG("Ctrl::SetFocusWnd");
	if(focusCtrlWnd != this) {
		LLOG("Ctrl::SetFocusWnd->ActivateWnd");
		ActivateWnd();
	}*/
}


NAMESPACE_UPP_END
