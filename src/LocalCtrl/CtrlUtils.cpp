#include "LocalCtrl.h"

NAMESPACE_UPP
#if IS_UPP_CORE
FileSel& GFileSel();
#else
FileSel& GFileSel() {static FileSel s; return s;}
#endif
END_UPP_NAMESPACE


NAMESPACE_TOPSIDE_BEGIN

void SetFileDialogDirectory(String path) {
	FileSel& fs = GFileSel();
	LoadFromGlobal(fs, "GlobalFileSelector");
	fs.ActiveDir(path);
	StoreToGlobal(fs, "GlobalFileSelector");
}

NAMESPACE_TOPSIDE_END
