#include "SerialPlanner.h"

NAMESPACE_SERIAL_BEGIN


String ScriptIfaceOption::ToString() const {
	String s;
	s << (is_src ? "src, " : "sink, ") << HexStr(state.last) << ", " << total_distance << ", " << pre_node_dist << ", " << post_node_dist;
	return s;
}

String ScriptLinkOption::ToString() const {
	String s;
	s << total_distance << ": " << HexStr(src->state.last) << " (" << src_total_distance << ") -> " << HexStr(sink->state.last) << " (" << sink_total_distance << ")";
	return s;
}
	
	
	
	
void ScriptConnectionSolver::InitializeLoops(const Vector<ScriptLoopLoader*>& loops) {
	this->loops.SetCount(0);
	this->links.SetCount(0);
	
	this->loops.SetCount(loops.GetCount());
	for(int i = 0; i < loops.GetCount(); i++)
		this->loops[i].ll = loops[i];
}

bool ScriptConnectionSolver::MakeOptionLinkVector() {
	if (loops.IsEmpty()) {
		SetError("no loops");
		return false;
	}
	
	for (ScriptLoopOptions& l : loops) {
		ASSERT(l.ll);
		ASSERT(l.link_opts.IsEmpty());
		ScriptLoopLoader& ll = *l.ll;
		
		Vector<Script::ActionPlanner::State>& sources = ll.planner.GetSideSources();
		Vector<Script::ActionPlanner::State>& sinks = ll.planner.GetSideSinks();
		
		int total_count = sources.GetCount() + sinks.GetCount();
		l.link_opts.Reserve(total_count);
		
		for (Script::ActionPlanner::State& state : sources) {
			ScriptIfaceOption& link_opt = l.link_opts.Add();
			link_opt.is_src = true;
			link_opt.state = state;
			link_opt.pre_node_dist = state.last->GetCost();
			link_opt.post_node_dist = state.last->GetEstimate();
			link_opt.total_distance = link_opt.pre_node_dist + link_opt.post_node_dist;
		}
		
		for (Script::ActionPlanner::State& state : sinks) {
			ScriptIfaceOption& link_opt = l.link_opts.Add();
			link_opt.is_src = false;
			link_opt.state = state;
			link_opt.pre_node_dist = state.last->GetCost();
			link_opt.post_node_dist = state.last->GetEstimate();
			link_opt.total_distance = link_opt.pre_node_dist + link_opt.post_node_dist;
		}
		
		
		Sort(l.link_opts, ScriptIfaceOption());
		DUMPC(l.link_opts);
	}
	
	return true;
}

bool ScriptConnectionSolver::FindAcceptedLinks() {
	ASSERT(links.IsEmpty());
	links.Reserve(128);
	
	for (ScriptLoopOptions& b_loop : loops) {
			
		for (ScriptLoopOptions& a_loop : loops) {
			if (&a_loop == &b_loop)
				break;
			
			for (ScriptIfaceOption& b_opt : b_loop.link_opts) {
				Script::ActionPlanner::State& b_state = b_opt.state;
				Script::APlanNode* b = b_state.last;
				Script::WorldState& b_ws = b->GetWorldState();
				Script::WorldState* b_prev_ws = b_state.second_last ? &b_state.second_last->GetWorldState() : 0;
				int b_side_id = b_state.ch_i - 1;
				ASSERT(b_ws.IsAddAtom());
				AtomTypeCls b_atom = b_ws.GetAtom();
				auto& b_d = Serial::Factory::AtomDataMap().Get(b_atom);
				
				for (ScriptIfaceOption& a_opt : a_loop.link_opts) {
					if (a_opt.is_src == b_opt.is_src)
						continue;
					
					Script::ActionPlanner::State& a_state = a_opt.state;
					Script::APlanNode* a = a_state.last;
					Script::WorldState& a_ws = a->GetWorldState();
					Script::WorldState* a_prev_ws = a_state.second_last ? &a_state.second_last->GetWorldState() : 0;
					int a_side_id = a_state.ch_i - 1;
					ASSERT(a_ws.IsAddAtom());
					AtomTypeCls a_atom = a_ws.GetAtom();
					auto& a_d = Serial::Factory::AtomDataMap().Get(a_atom);
					
					SideStatus a_accepted, b_accepted;
					if ((a_accepted = a_d.side_fn(a_atom, a_ws, b_atom, b_ws)) != SIDE_NOT_ACCEPTED) {
						if ((b_accepted = b_d.side_fn(a_atom, a_ws, b_atom, b_ws)) != SIDE_NOT_ACCEPTED) {
							
							LOG(HexStr(&a) << " accepted " << HexStr(&b) << ": " << HexStr(a) << " " << a_state.ch_i << " -> " << HexStr(b) << " " << b_state.ch_i);
							
							ScriptLinkOption& link = links.Add();
							link.src  = a_opt.is_src ? &a_opt : &b_opt;
							link.sink = a_opt.is_src ? &b_opt : &a_opt;
							link.src_total_distance = link.src->total_distance;
							link.sink_total_distance = link.sink->total_distance;
							link.total_distance = link.src_total_distance + link.sink_total_distance;
						}
					}
				}
			}
		}
	}
	
		
	Sort(links, ScriptLinkOption());
	DUMPC(links);
	
	return true;
}


NAMESPACE_SERIAL_END
