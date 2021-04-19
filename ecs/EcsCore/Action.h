#ifndef _EcsCore_Action_h_
#define _EcsCore_Action_h_


NAMESPACE_OULU_BEGIN


class ActionAgent :
	public Component<ActionAgent>,
	public ActionSource
{
	Vector<String> labels;
	ActionPlanner ap;
	ActionPlannerWrapper wrap;
	
public:
	using Component::Component;
	
	IFACE_GENERIC;
	IFACE_CB(ActionSource);
	
	ActionAgent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	void operator=(const ActionAgent& c) {}
	
	void SetSize(int act_count, int atom_count) {ap.SetSize(act_count, atom_count);}
	void SetAction(int act_i, String label) {wrap.SetAction(act_i, label);}
	
};


NAMESPACE_OULU_END


#endif
