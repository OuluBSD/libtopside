#ifndef _EonPlanner_Editor_h_
#define _EonPlanner_Editor_h_

NAMESPACE_TOPSIDE_BEGIN


class EonPlanEditor : public EditorBase {
	ProjectEditorExt		prj_ext;
	EonBaseExt				eon_ext;
	
public:
	typedef EonPlanEditor CLASSNAME;
	EonPlanEditor();
	
	
	void MainMenu(Bar& b) override;
	
};



NAMESPACE_TOPSIDE_END

#endif
