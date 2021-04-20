#include "EcsCore.h"


NAMESPACE_OULU_BEGIN


ActionAgent::ActionAgent() : wrap(ap) {
	root_node.SetActionPlanner(ap);
}

void ActionAgent::Initialize() {
	
}

void ActionAgent::Uninitialize() {
	
}

ActionGroup ActionAgent::AddActionGroup(int act_count, int atom_count) {
	ASSERT(act_count >= 0 && atom_count >= 0);
	ActionGroup ag		= ag_data.GetCount();
	ActionGroupData& d	= ag_data.Add();
	d.act_offset		= ap.GetActionCount();
	d.atom_offset		= ap.GetAtomCount();
	d.act_count			= act_count;
	d.atom_count		= atom_count;
	ap					.AddSize(act_count, atom_count);
	return ag;
}

void ActionAgent::SetActionName(ActionGroup ag, ActionId act_i, String name) {
	const ActionGroupData& d = ag_data[ag];
	ASSERT(act_i >= 0 && act_i < d.act_count);
	wrap.SetAction(d.act_offset + act_i, name);
}

void ActionAgent::SetCurrentAtom(ActionGroup ag, AtomId atom_i, bool value) {
	const ActionGroupData& d = ag_data[ag];
	ASSERT(atom_i >= 0 && atom_i < d.atom_count);
	current.Set(d.atom_offset + atom_i, value);
}

void ActionAgent::SetGoalAtom(ActionGroup ag, AtomId atom_i, bool value) {
	const ActionGroupData& d = ag_data[ag];
	ASSERT(atom_i >= 0 && atom_i < d.atom_count);
	goal.Set(d.atom_offset + atom_i, value);
}

void ActionAgent::RefreshActionPlan() {
	plan.Clear();
	goal_node.SetWorldState(goal);
	root_node.SetGoal(goal_node);
	root_node.SetWorldState(current);
	AStar<ActionNode> as;
	plan = as.Search(root_node);
}



NAMESPACE_OULU_END
