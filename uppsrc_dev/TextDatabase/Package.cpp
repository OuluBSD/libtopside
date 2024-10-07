#include "TextDatabase.h"


BEGIN_TEXTLIB_NAMESPACE


String GetNodeName(NodeType n) {
	switch (n) {
		case NODE_INVALID: return "Invalid";
		case NODE_CLASS: return "Class";
		case NODE_FUNCTION: return "Function";
		case NODE_VARIABLE: return "Variable";
		
		case NODE_EXPORTER: return "Exporter";
		case NODE_IMPORTER: return "Importer";
		case NODE_LINKED_PROJECT: return "Linked Project";
		case NODE_BUILD_TARGET: return "Build Target";
		
		case NODE_SYSTEM: return "System";
		case NODE_FEATURES: return "Features";
		case NODE_FILE_LIST: return "File list";
		case NODE_FILE: return "File";
		case NODE_DEBUG: return "Debug";
		case NODE_WIZARD: return "Wizard";
		case NODE_DIRECTORY: return "Directory";
		case NODE_MODULE: return "Module";
		case NODE_PACKAGE: return "Package";
		case NODE_META: return "Meta";
		case NODE_METAWIZARD: return "Meta Wizard";
		
		case NODE_GEN_USER_ENTRY_POINT: return "User entry point";
		case NODE_GEN_FEATURES: return "Features";
		case NODE_GEN_SOFTWARE_ARCHITECTURE: return "Software architecture";
		case NODE_GEN_MAIN_LOOP: return "Main loop";
		case NODE_GEN_ASSETS: return "Assets";
		case NODE_GEN_CUSTOM_EDITOR: return "Custom editor";
		
		default: return "";
	}
}

String GetNodeName(int i) {return GetNodeName((NodeType)i);}


void Package::StoreToFile() {
	RealizeDirectory(GetFileDirectory(json_path));
	StoreAsJsonFileStandard(*this, json_path, true);
}

void Package::LoadFromFile(String json_path) {
	this->json_path = json_path;
	LoadFromJsonFile(*this, json_path);
}


END_TEXTLIB_NAMESPACE
