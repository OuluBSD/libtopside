#include "OuluCtrl.h"

NAMESPACE_UPP
FileSel& GFileSel();
END_UPP_NAMESPACE


NAMESPACE_OULU_BEGIN

void SetFileDialogDirectory(String path) {
	FileSel& fs = GFileSel();
	LoadFromGlobal(fs, "GlobalFileSelector");
	fs.ActiveDir(path);
	StoreToGlobal(fs, "GlobalFileSelector");
}

NAMESPACE_OULU_END
