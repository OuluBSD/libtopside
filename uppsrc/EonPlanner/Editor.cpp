#include "EonPlanner.h"

NAMESPACE_TOPSIDE_BEGIN


EonPlanEditor::EonPlanEditor() {
	
	//SetExt(eon_ext);
	SetExt(prj_ext);
	
}

void EonPlanEditor::MainMenu(Bar& b) {
	
	b.Sub("File", [this](Bar& bar) {
		
	});
	
}



NAMESPACE_TOPSIDE_END
