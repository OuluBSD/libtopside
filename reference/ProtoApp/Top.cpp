#include "ProtoApp.h"


NAMESPACE_TOPSIDE_BEGIN


ProtoApp::ProtoApp() {
	Title("ProtoApp");
	MaximizeBox().MinimizeBox();
	
	Add(tabs.SizePos());
	
	tabs.Add(vm.SizePos(), "VM");
	
}



NAMESPACE_TOPSIDE_END
