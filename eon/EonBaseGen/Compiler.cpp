#include "EonBaseGen.h"

NAMESPACE_EONGEN_BEGIN


Compiler::Compiler() {
	
}

bool Compiler::Compile(UppProject& p, const UppAssembly& as, UppAssemblyData& asd) {
	Index<String> uses;
	p.GetRecursiveUses(uses, asd);
	
	//DUMPC(uses);
	ASSERT(uses.Find(p.GetName()) >= 0);
	
	Vector<String> match_keys;
	match_keys << "bases";
	match_keys << "headers";
	match_keys << "loops";
	match_keys << "nodelinks";
	match_keys << "chains";
	match_keys << "topchains";
	match_keys << "machines";
	match_keys << "systems";
	
	for (String match_key : match_keys) {
		WhenOutput("Matching key '" + match_key + "'");
		
		for(int i = uses.GetCount()-1; i >= 0; i--) {
			String use = uses[i];
			UppProject& p = asd.GetProject(use);
			
			for(int j = 0; j < p.GetFileCount(); j++) {
				String path = p.GetFilePath(j);
				String content = LoadFile(path);
				if (content.IsEmpty()) {
					WhenOutput("Empty file: " + path);
					continue;
				}
				
				String ext = GetFileExt(path);
				if (ext == ".json") {
					WhenOutput("\t" + path);
					try {
						if (!world.LoadJSON(path, content, match_key)) {
							WhenMessage(world.GetError());
							continue;
						}
					}
					catch (Exc e) {
						ProcMsg p;
						p.file = path;
						p.line = 0;
						p.col = 0;
						p.severity = PROCMSG_ERROR;
						p.msg = e;
						WhenMessage(p);
						continue;
					}
				}
			}
		}
	}
	WhenOutput("Files loaded successfully");
	
	
	WhenOutput("Traversing base units");
	if (!world.TraverseUnits(Unit::BASE)) {
		WhenMessage(world.GetError());
		return false;
	}
	
	WhenOutput("Traversing header units");
	if (!world.TraverseUnits(Unit::HEADER)) {
		WhenMessage(world.GetError());
		return false;
	}
	
	WhenOutput("Traversing loops");
	if (!world.TraverseLoops()) {
		WhenMessage(world.GetError());
		return false;
	}
	
	
	WhenOutput("Compiling finished successfully");
	return true;
}

NAMESPACE_EONGEN_END
