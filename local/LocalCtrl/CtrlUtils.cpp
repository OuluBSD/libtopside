#include "LocalCtrl.h"

NAMESPACE_UPP
FileSel& GFileSel();
END_UPP_NAMESPACE


NAMESPACE_TOPSIDE_BEGIN

void SetFileDialogDirectory(String path) {
	FileSel& fs = GFileSel();
	LoadFromGlobal(fs, "GlobalFileSelector");
	fs.ActiveDir(path);
	StoreToGlobal(fs, "GlobalFileSelector");
}

NAMESPACE_TOPSIDE_END
