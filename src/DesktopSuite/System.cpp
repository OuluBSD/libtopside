#include "DesktopSuite.h"


NAMESPACE_ECS_BEGIN


void DesktopSuiteSystem::Visit(RuntimeVisitor& vis) {
	
}

bool DesktopSuiteSystem::Arg(String key, Object value) {
	
	if (key == "program") {
		String program = value;
		Vector<String> progs = Split(program, ";");
		for (String prog : progs) {
			auto item = DesktopFactory::Find(prog);
			if (!item) {
				LOG("DesktopSuiteSystem::Arg: error: no program '" << prog << "' available");
				return false;
			}
			TopWindow* tw = item->New();
			apps.Add(tw);
		}
	}
	
	return true;
}

bool DesktopSuiteSystem::Initialize() {
	
	
	return true;
}

void DesktopSuiteSystem::Start() {
	
}

void DesktopSuiteSystem::Update(double dt) {
	
}

void DesktopSuiteSystem::Stop() {
	
}

void DesktopSuiteSystem::Uninitialize() {
	
}


NAMESPACE_ECS_END
