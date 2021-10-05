#ifndef _EonIDE_Editor_h_
#define _EonIDE_Editor_h_

NAMESPACE_TOPSIDE_BEGIN


class EonPlanEditor : public EditorBase {
	ProjectEditorExt		prj_ext;
	EonBaseExt				eon_ext;
	RunningFlag				flag;
	
	
	void CompileProcess();
	
public:
	typedef EonPlanEditor CLASSNAME;
	EonPlanEditor();
	~EonPlanEditor() {Stop();}
	
	
	void MainMenu(Bar& b) override;
	
	void Compile();
	void Stop();
	void PostCompile() {PostCallback(THISBACK(Compile));}
	void OnCompilerMessage(ProcMsg e);
	
};



NAMESPACE_TOPSIDE_END

#endif
