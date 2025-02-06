#include "OrgCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


Image GetNodeImage(NodeType n) {
	switch (n) {
		case NODE_INVALID: return OrgLibImgs::invalid;
		case NODE_CLASS: return OrgLibImgs::class_;
		case NODE_FUNCTION: return OrgLibImgs::function;
		case NODE_VARIABLE: return OrgLibImgs::variable;
		
		case NODE_EXPORTER: return OrgLibImgs::exporter();
		case NODE_IMPORTER: return OrgLibImgs::importer();
		case NODE_LINKED_PROJECT: return OrgLibImgs::linkedproject();
		case NODE_BUILD_TARGET: return OrgLibImgs::buildtarget();
		
		case NODE_SYSTEM: return OrgLibImgs::system();
		case NODE_FEATURES: return OrgLibImgs::features();
		case NODE_FILE_LIST: return OrgLibImgs::filelist();
		case NODE_FILE: return OrgLibImgs::file();
		case NODE_DEBUG: return OrgLibImgs::debug();
		case NODE_WIZARD: return OrgLibImgs::wizard();
		case NODE_DIRECTORY: return OrgLibImgs::directory();
		case NODE_MODULE: return OrgLibImgs::module_();
		case NODE_PACKAGE: return OrgLibImgs::package();
		case NODE_META: return OrgLibImgs::meta();
		case NODE_METAWIZARD: return OrgLibImgs::metawizard();
		
		case NODE_GEN_USER_ENTRY_POINT: return OrgLibImgs::entrypoint();
		case NODE_GEN_FEATURES: return OrgLibImgs::features();
		case NODE_GEN_SOFTWARE_ARCHITECTURE: return OrgLibImgs::architecture();
		case NODE_GEN_MAIN_LOOP: return OrgLibImgs::mainloop();
		case NODE_GEN_ASSETS: return OrgLibImgs::assets();
		case NODE_GEN_CUSTOM_EDITOR: return OrgLibImgs::customeditor();
		
		default: return OrgLibImgs::unknown;
	}
}


END_TEXTLIB_NAMESPACE
