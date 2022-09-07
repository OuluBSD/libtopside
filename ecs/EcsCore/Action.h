#ifndef _EcsCore_Action_h_
#define _EcsCore_Action_h_


NAMESPACE_TOPSIDE_BEGIN

#if 0

class ActionAgent :
	public Component<ActionAgent>,
	public ActionSource
{
	struct ActionGroupData : Moveable<ActionGroupData> {
		int act_offset, atom_offset;
		int act_count, atom_count;
	};
	
	Vector<ActionGroupData> ag_data;
	Vector<String> labels;
	ActionPlanner ap;
	ActionPlannerWrapper wrap;
	WorldState current, goal;
	APlanNode goal_node, root_node;
	Vector<ActionNode*> plan;
	
public:
	using Component::Component;
	
	IFACE_GENERIC;
	IFACE_CB(ActionSource);
	
	ActionAgent();
	
	void Initialize() override;
	void Uninitialize() override;
	
	WorldState& GetStateCurrent() {return current;}
	WorldState& GetStateGoal() {return goal;}
	
	void Init(int act_count, int atom_count) {ap.SetSize(act_count, atom_count);}
	void SetAction(int act_i, String label) {wrap.SetAction(act_i, label);}
	
	void operator=(const ActionAgent& c) {}
	
	
	ActionGroup AddActionGroup(ActionSink& sink, int act_count, int atom_count) override;
	void SetActionName(ActionGroup ag, ActionId act_i, String name) override;
	void SetCurrentAtom(ActionGroup ag, AtomId atom_i, bool value) override;
	void SetGoalAtom(ActionGroup ag, AtomId atom_i, bool value) override;
	void RefreshActionPlan() override;
	
};

#endif

NAMESPACE_TOPSIDE_END


#endif
