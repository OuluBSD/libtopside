#include "SerialPlanner.h"

NAMESPACE_SERIAL_BEGIN


String ScriptIfaceOption::ToString() const {
	String s;
	s << HexStr(state.last) << ", " << (is_src ? "src, " : "sink, ") << total_distance << ", " << pre_node_dist << ", " << post_node_dist;
	return s;
}

String ScriptLinkOption::ToString() const {
	String s;
	AtomTypeCls src_type  = src ->state.last->GetWorldState().GetAtom();
	AtomTypeCls sink_type = sink->state.last->GetWorldState().GetAtom();
	String src_str  = IntStr(src_loop ->id) + "," + IntStr(src ->id) + ": " + GetSubAtomString(src_type .sub) + "[" << src ->state.ch_i << "]";
	String sink_str = IntStr(sink_loop->id) + "," + IntStr(sink->id) + ": " + GetSubAtomString(sink_type.sub) + "[" << sink->state.ch_i << "]";
	s << total_distance << ": " << src_str << " " << HexStr(src->state.last) << " (" << src_total_distance << ") -> " << sink_str << " " << HexStr(sink->state.last) << " (" << sink_total_distance << ")";
	return s;
}

String ScriptLoopOptions::ToString() const {
	String s;
	s << "ScriptIfaceOption(" << id << ", " << (ll ? ll->def.id.ToString() : String("<invalid>")) << ")\n";
	
	for(int i = 0; i < link_opts.GetCount(); i++) {
		s << "\t" << i << ": " << link_opts[i].ToString() << "\n";
	}
	
	return s;
}
	
	
	
	
void ScriptConnectionSolver::InitializeLoops(const Vector<ScriptLoopLoader*>& loops) {
	this->loops.SetCount(0);
	this->links.SetCount(0);
	
	this->loops.SetCount(loops.GetCount());
	for(int i = 0; i < loops.GetCount(); i++) {
		auto& l = this->loops[i];
		l.id = i;
		l.ll = loops[i];
	}
}

bool ScriptConnectionSolver::MakeOptionLinkVector() {
	static const bool print = true;
	
	if (loops.IsEmpty()) {
		SetError("no loops");
		return false;
	}
	
	for (ScriptLoopOptions& l : loops) {
		ASSERT(l.ll);
		ASSERT(l.link_opts.IsEmpty());
		ScriptLoopLoader& ll = *l.ll;
		auto s = ll.GetStatus();
		if (s != WAITING_PARENT_SIDE_LINKS) {
			if (s != READY) {
				RTLOG("ScriptConnectionSolver::MakeOptionLinkVector: warning: skipping from status " << l.ll->def.id.ToString() << " " << HexStr(l.ll));
				continue;
			}
			else
				continue;
		}
		
		Vector<Script::ActionPlanner::State>& sources = ll.planner.GetSideSources();
		Vector<Script::ActionPlanner::State>& sinks = ll.planner.GetSideSinks();
		
		int total_count = sources.GetCount() + sinks.GetCount();
		l.link_opts.Reserve(total_count);
		int dbg_i = -1;
		for (Script::ActionPlanner::State& state : sources) {
			dbg_i++;
			Script::WorldState& ws = state.last->GetWorldState();
			const Script::Statement* stmt = 0;
			Script::WorldState* prev_ws = 0;
			for(int i = 0; i < Script::ActionPlanner::State::MAX_PREV; i++) {
				if (!state.previous[i]) break;
				prev_ws = &state.previous[i]->GetWorldState();
				stmt = ws.FindStatement(prev_ws, ll.def.stmts);
				if (stmt) break;
			}
			if (!stmt)
				stmt = ws.FindStatement(0, ll.def.stmts);
			if (!stmt) {
				if (print) RTLOG("ScriptConnectionSolver::MakeOptionLinkVector: src #" << dbg_i << " prev=" << HexStr(prev_ws) << " no statement");
				continue;
			}
			
			ScriptIfaceOption& link_opt = l.link_opts.Add();
			link_opt.id = l.link_opts.GetCount() - 1;
			link_opt.is_src = true;
			link_opt.stmt = stmt;
			link_opt.state = state;
			link_opt.pre_node_dist = state.last->GetCost();
			link_opt.post_node_dist = state.last->GetEstimate();
			double additional_side_ch_dist = state.ch_i * 0.1;
			link_opt.total_distance = link_opt.pre_node_dist + link_opt.post_node_dist + additional_side_ch_dist;
		}
		
		dbg_i = -1;
		for (Script::ActionPlanner::State& state : sinks) {
			dbg_i++;
			Script::WorldState& ws = state.last->GetWorldState();
			const Script::Statement* stmt = 0;
			Script::WorldState* prev_ws = 0;
			for(int i = 0; i < Script::ActionPlanner::State::MAX_PREV; i++) {
				if (!state.previous[i]) break;
				prev_ws = &state.previous[i]->GetWorldState();
				stmt = ws.FindStatement(prev_ws, ll.def.stmts);
				if (stmt) break;
			}
			if (!stmt)
				stmt = ws.FindStatement(0, ll.def.stmts);
			if (!stmt) {
				if (print) RTLOG("ScriptConnectionSolver::MakeOptionLinkVector: sink #" << dbg_i << " prev=" << HexStr(prev_ws) << " no statement");
				continue;
			}
			
			ScriptIfaceOption& link_opt = l.link_opts.Add();
			link_opt.id = l.link_opts.GetCount() - 1;
			link_opt.is_src = false;
			link_opt.stmt = stmt;
			link_opt.state = state;
			link_opt.pre_node_dist = state.last->GetCost();
			link_opt.post_node_dist = state.last->GetEstimate();
			double additional_side_ch_dist = state.ch_i * 0.1;
			link_opt.total_distance = link_opt.pre_node_dist + link_opt.post_node_dist + additional_side_ch_dist;
		}
		
		if (!(l.link_opts.GetCount() || total_count == 0))  {
			LOG("ScriptConnectionSolver::MakeOptionLinkVector: error: dead end in a loop. Probably one of your atom keys is wrong");
			DUMPI(ll.def.stmts);
			return false;
		}
		ASSERT_(l.link_opts.GetCount() || total_count == 0, "all side links failed in " + l.ll->def.id.ToString());
		
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
				Script::WorldState* b_prev_ws = b_state.previous[0] ? &b_state.previous[0]->GetWorldState() : 0;
				int b_side_id = b_state.ch_i - 1;
				ASSERT(b_side_id >= 0);
				ASSERT(b_ws.IsAddAtom());
				AtomTypeCls b_atom = b_ws.GetAtom();
				auto& b_d = Serial::Factory::AtomDataMap().Get(b_atom);
				const Script::Statement& b_stmt = *b_opt.stmt;
				const Array<Script::Statement>& b_conds = b_opt.is_src ? b_stmt.src_side_conds : b_stmt.sink_side_conds;
				
				for (ScriptIfaceOption& a_opt : a_loop.link_opts) {
					if (a_opt.is_src == b_opt.is_src)
						continue;
					
					Script::ActionPlanner::State& a_state = a_opt.state;
					Script::APlanNode* a = a_state.last;
					Script::WorldState& a_ws = a->GetWorldState();
					Script::WorldState* a_prev_ws = a_state.previous[0] ? &a_state.previous[0]->GetWorldState() : 0;
					int a_side_id = a_state.ch_i - 1;
					ASSERT(a_side_id >= 0);
					ASSERT(a_ws.IsAddAtom());
					AtomTypeCls a_atom = a_ws.GetAtom();
					auto& a_d = Serial::Factory::AtomDataMap().Get(a_atom);
					const Script::Statement& a_stmt = *a_opt.stmt;
					const Array<Script::Statement>& a_conds = a_opt.is_src ? a_stmt.src_side_conds : a_stmt.sink_side_conds;
					
					bool a_user_pass = true, b_user_pass = true;
					
					if (a_side_id < a_conds.GetCount()) {
						a_user_pass = false;
						const Script::Statement& cond_stmt = a_conds[a_side_id];
						if (cond_stmt.value.IsEmpty()) {
							// fail
						}
						else if (!b_loop.ll->PassSideConditionals(cond_stmt)) {
							// fail
						}
						else a_user_pass = true;
					}
					
					if (b_side_id < b_conds.GetCount()) {
						b_user_pass = false;
						const Script::Statement& cond_stmt = b_conds[b_side_id];
						if (cond_stmt.value.IsEmpty()) {
							// fail
						}
						else if (!a_loop.ll->PassSideConditionals(cond_stmt)) {
							// fail
						}
						else b_user_pass = true;
					}
					
					if (a_user_pass && b_user_pass) {
						SideStatus a_accepted, b_accepted;
						if ((a_accepted = a_d.side_fn(a_atom, a_ws, b_atom, b_ws)) != SIDE_NOT_ACCEPTED) {
							if ((b_accepted = b_d.side_fn(a_atom, a_ws, b_atom, b_ws)) != SIDE_NOT_ACCEPTED) {
								
								LOG(HexStr(&a) << " accepted " << HexStr(&b) << ": " << HexStr(a) << " " << a_state.ch_i << " -> " << HexStr(b) << " " << b_state.ch_i);
								
								ScriptLinkOption& link = links.Add();
								link.src_loop = a_opt.is_src ? &a_loop : &b_loop;
								link.sink_loop = a_opt.is_src ? &b_loop : &a_loop;
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
	}
	
	
	if (links.IsEmpty()) {
		String s;
		for (ScriptLoopOptions& loop : loops)
			s << loop.ToString();
		LOG(s);
		SetError("No link was accepted");
		return false;
	}
		
	Sort(links, ScriptLinkOption());
	DUMPC(links);
	
	return true;
}






struct LinkGeneratorNode : RTTIBase {
	RTTI_DECL0(LinkGeneratorNode)
	
	Vector<ScriptLinkOption*> available_links;
	Vector<ScriptLinkOption*> added_links;
	Vector<ScriptLoopOptions*> unfinished_loops;
	double length;
	double length_to_node;
	double estimate_to_goal;
	int last_selection;
	
	String ToString() const {return DblStr(length) + ", " + DblStr(length_to_node) + ", " + DblStr(estimate_to_goal);}
	double GetUtility() const {return length_to_node;}
	double GetEstimate() const {return estimate_to_goal;}
	double GetDistance(Node<LinkGeneratorNode>& n) {return n.length;}
};

NAMESPACE_SERIAL_END


NAMESPACE_TOPSIDE_BEGIN

using LGN = Serial::LinkGeneratorNode;

template <>	inline bool TerminalTest<LGN>(Node<LGN>& n, Node<LGN>** prev) {
	using namespace Serial;
	
	if (n.unfinished_loops.IsEmpty())
		return true;
	
	int goal = 0;
	//if (n.estimate_to_goal <= goal) return true;
	//if (n.GetCount()) return !n.GetCount();
	int sub_node_count = n.available_links.GetCount();
	for(int i = 0; i < sub_node_count; i++) {
		Node<LGN>& sub = n.Add();
		sub.last_selection = i;
		
		
		// update available links
		Serial::ScriptLinkOption* added_opt = n.available_links[i];
		sub.added_links <<= n.added_links;
		sub.added_links << added_opt;
		
		for (ScriptLinkOption* opt : n.available_links) {
			if (opt == added_opt)
				continue;
			
			
			// check for conflicts
			bool conflicts = false;
			
			ScriptIfaceReservation src0;
			src0.loop		= opt->src_loop->ll;
			src0.ch_id		= opt->src->state.ch_i;
			src0.type		= opt->src->state.last->GetWorldState().GetAtom();
			src0.is_src		= true;
			
			ScriptIfaceReservation sink0;
			sink0.loop		= opt->sink_loop->ll;
			sink0.ch_id		= -1 - opt->sink->state.ch_i;
			sink0.type		= opt->sink->state.last->GetWorldState().GetAtom();
			sink0.is_src	= false;
			
			for (ScriptLinkOption* cmp : sub.added_links) {
				ScriptIfaceReservation src1;
				src1.loop		= cmp->src_loop->ll;
				src1.ch_id		= cmp->src->state.ch_i;
				src1.type		= cmp->src->state.last->GetWorldState().GetAtom();
				src1.is_src		= true;
				
				ScriptIfaceReservation sink1;
				sink1.loop		= cmp->sink_loop->ll;
				sink1.ch_id		= -1 - cmp->sink->state.ch_i;
				sink1.type		= cmp->sink->state.last->GetWorldState().GetAtom();
				sink1.is_src	= false;
				
				if (src0.Conflicts(src1) || src0.Conflicts(sink1) ||
					sink0.Conflicts(src1) || sink0.Conflicts(sink1)) {
					conflicts = true;
					break;
				}
			}
			
			
			if (!conflicts) {
				sub.available_links << opt;
				
				// update unfinished loops
				VectorFindAdd(sub.unfinished_loops, opt->src_loop);
				VectorFindAdd(sub.unfinished_loops, opt->sink_loop);
			}
		}
		
		// update finished loops
		int completed_loops = 0;
		for (ScriptLoopOptions* prev_unfinished : n.unfinished_loops)
			if (VectorFind(sub.unfinished_loops, prev_unfinished) < 0)
				completed_loops++;
			
		
		double length = completed_loops * 1000 + added_opt->total_distance;
		
		// Accumulate total route length
		if (sub.GetParent()) {
			sub.length				 = length;
			sub.length_to_node		 = n.length_to_node + length;
			sub.estimate_to_goal	 = n.unfinished_loops.GetCount() * 1000;
		}
	}
	
	return false;
}

NAMESPACE_TOPSIDE_END

NAMESPACE_SERIAL_BEGIN

bool ScriptConnectionSolver::LinkPlanner() {
	result.Clear();
	
	Node<LinkGeneratorNode> n;
	n.length_to_node = 0;
	n.length = 0;
	n.available_links.Reserve(links.GetCount());
	n.last_selection = -1;
	for (ScriptLinkOption& opt : links)
		n.available_links.Add(&opt);
	for (ScriptLoopOptions& loop : loops)
		n.unfinished_loops.Add(&loop);
	n.estimate_to_goal = n.unfinished_loops.GetCount() * 1000;
	
	AStar<LinkGeneratorNode> as;
	as.TrimWorst(0);
	
	Vector<LinkGeneratorNode*> ans = as.Search(n);
	
	
	if (ans.GetCount()) {
		if (1) {
			int i = 0;
			double total_distance = 0;
			for(LinkGeneratorNode* n : ans) {
				LOG(i << ": " << HexStr(n));
				total_distance += n->length;
			}
			DUMP(total_distance);
		}
		
		Vector<ScriptLinkOption*>* prev_available = 0;
		for(LinkGeneratorNode* n : ans) {
			if (n->last_selection < 0) {
				prev_available = &n->available_links;
				continue;
			}
			
			ScriptLinkOption& opt = *(*prev_available)[n->last_selection];
			LOG("solved link: " << opt.ToString());
			
			result.Add(&opt);
			
			prev_available = &n->available_links;
		}
		
		return true;
	}
	else {
		
		TODO
		
		return false;
	}
}

NAMESPACE_SERIAL_END
