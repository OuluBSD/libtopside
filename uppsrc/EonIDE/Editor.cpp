#include "EonIDE.h"

NAMESPACE_TOPSIDE_BEGIN


EonPlanEditor::EonPlanEditor() {
	Image icon = StreamRaster::LoadFileAny(ShareDirFile("imgs/icons/jigsaw.png"));
	Icon(icon);
	Title("Eon Plan Editor");
	
	
	//SetExt(eon_ext);
	SetExt(prj_ext);
	
}

void EonPlanEditor::MainMenu(Bar& b) {
	
	b.Sub("File", [this](Bar& bar) {
		
	});
	
}

void EonPlanEditor::Compile() {
	if (flag.IsRunning())
		return;
	
	ShowBottom(1);
	
	flag.Start(1);
	Thread::Start(THISBACK(CompileProcess));
}

void EonPlanEditor::Stop() {
	flag.Stop();
	ShowBottom(0);
}

void EonPlanEditor::CompileProcess() {
	UppProject& p = GetProject();
	UppAssemblyData& ad = GetAssemblyData();
	const UppAssembly& a = GetAssembly();
	
	
	WriteConsoleLine("Compiling project \'" + p.GetName() + "\'");
	
	LOG("EonPlanEditor::CompileProcess: TODO");
	
	#if 0
	Ecs::Eon::Gen::Compiler comp;
	comp.WhenOutput = THISBACK(WriteConsoleLine);
	comp.WhenMessage = THISBACK(OnCompilerMessage);
	
	if (!comp.Compile(p, a, ad)) {
		flag.DecreaseRunning();
		return;
	}
	#endif
	
	
	flag.DecreaseRunning();
}

void EonPlanEditor::OnCompilerMessage(ProcMsg e) {
	WriteConsoleLine("\t\t" + e.ToString());
	OnMessage(e);
	if (e.severity == PROCMSG_ERROR) {
		GuiLock __;
		ShowBottom(2);
	}
}


NAMESPACE_TOPSIDE_END
