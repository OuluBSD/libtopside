#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


ScriptLoopLoader::ScriptLoopLoader(ScriptChainLoader& parent, int id, Script::LoopDefinition& def) :
	Base(parent, id, def)
{
	//planner.SetLoopLoader(this);
}

/*void ScriptLoopLoader::LoopStatus() {
	Panic("internal error");
}*/

void ScriptLoopLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	Panic("internal error");
}

/*void ScriptLoopLoader::CheckStatusDeep() {
	// pass
}*/

/*void ScriptLoopLoader::SetStatus(ScriptStatus status) {
	MACHVER_STATUS(LoopLoader_Status, this)
	Base::SetStatus(status);
};*/

String ScriptLoopLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Loop " << id;
	s.Cat('\n');
	
	int id = 0;
	
	/*for (ScriptLoopSegment& seg : segments) {
		s << seg.GetTreeString(id++, indent+1);
	}*/
	
	/*String extra;
	if (status == ScriptStatus::FAILED)
		extra = err_str;*/
	
	//s << GetScriptStatusLine(indent+1, status, extra);
	
	return s;
}

void ScriptLoopLoader::SetSideSourceConnected(const AtomTypeCls& type, int ch_i, ScriptLoopLoader& sink) {
	ASSERT(type.IsValid());
	ASSERT(ch_i > 0);
	ASSERT(type.iface.src.GetCount() > 1 && ch_i < type.iface.src.GetCount());
	int side_ch_i = ch_i - 1;
	
	#if 0
	if (src_side_conns.IsEmpty()) {
		int side_conn_count = type.iface.src.count - 1 - type.user_src_count;
		src_side_conns.SetCount(side_conn_count, 0);
	}
	if (side_ch_i >= src_side_conns.GetCount()) {
		if (side_ch_i < type.iface.src.count - 1)
			src_side_conns.SetCount(side_ch_i + 1);
		else {
			ASSERT_(0, "invalid side channel");
			return;
		}
	}
	#endif
	
	AtomSideLinks& atom = atom_links.Top();
	
	RTLOG("ScriptLoopLoader::SetSideSourceConnected: loop " << HexStr(this) << " src ch #" << ch_i << " set " << HexStr(&sink));
	ASSERT(side_ch_i >= 0 && side_ch_i < atom.src_side_conns.GetCount());
	SideLink& l = atom.src_side_conns[side_ch_i];
	if (l.link == &sink)
		return; // todo: prevent this call happening
	ASSERT(!l.link);
	if (l.link) {AddError(def.loc, "ScriptLoopLoader::SetSideSourceConnected: internal error: atom already linked"); return;}
	l.link = &sink;
	
	MACHVER_STATUS(LoopLoader_AtomLinked, this);
}

void ScriptLoopLoader::SetSideSinkConnected(const AtomTypeCls& type, int ch_i, ScriptLoopLoader& src) {
	ASSERT(type.IsValid());
	ASSERT(ch_i > 0);
	ASSERT(type.iface.sink.GetCount() > 1 && ch_i < type.iface.sink.GetCount());
	int side_ch_i = ch_i - 1;
	
	#if 0
	if (sink_side_conns.IsEmpty()) {
		int side_conn_count = type.iface.sink.count - 1 - type.user_sink_count;
		sink_side_conns.SetCount(side_conn_count, 0);
	}
	if (side_ch_i >= sink_side_conns.GetCount()) {
		if (side_ch_i < type.iface.sink.count - 1)
			sink_side_conns.SetCount(side_ch_i + 1);
		else {
			ASSERT_(0, "invalid side channel");
			return;
		}
	}
	#endif
	
	AtomSideLinks& atom = atom_links.Top();
	
	RTLOG("ScriptLoopLoader::SetSideSourceConnected: loop " << HexStr(this) << " sink ch #" << ch_i << " set " << HexStr(&src));
	ASSERT(side_ch_i >= 0 && side_ch_i < atom.sink_side_conns.GetCount());
	SideLink& l = atom.sink_side_conns[side_ch_i];
	if (l.link == &src)
		return; // todo: prevent this call happening
	ASSERT(!l.link);
	l.link = &src;
	
	MACHVER_STATUS(LoopLoader_AtomLinked, this);
}

bool ScriptLoopLoader::IsAllSidesConnected() const {
	ASSERT(atom_links.GetCount());
	for (const auto& atom : atom_links) {
		for (const SideLink& l : atom.src_side_conns)
			if (l.is_required && !l.link)
				return false;
		for (const SideLink& l : atom.sink_side_conns)
			if (l.is_required && !l.link)
				return false;
	}
	return true;
}

bool ScriptLoopLoader::IsTopSidesConnected() const {
	ASSERT(atom_links.GetCount());
	const auto& atom = atom_links.Top();
	int dbg_i = 0;
	for (const SideLink& l : atom.src_side_conns) {
		if (l.is_required && !l.link) {
			//ASSERT(!l.is_user_stmt);
			return false;
		}
		dbg_i++;
	}
	dbg_i = 0;
	for (const SideLink& l : atom.sink_side_conns) {
		if (l.is_required && !l.link) {
			//ASSERT(!l.is_user_stmt);
			return false;
		}
		dbg_i++;
	}
	return true;
}

/*String ScriptLoopSegment::GetTreeString(int id, int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Segment " << id;
	s.Cat('\n');
	if (!ep.plan.IsEmpty()) {
		bool started = false;
		for (Script::ActionNode* n : ep.plan) {
			started = started || n == start_node;
			if (!started) continue;
			String state_str = n->GetWorldState().ToString();
			if (state_str.GetCount()) {
				s.Cat('\t', indent+1);
				s << state_str << "\n";
			}
		}
	}
	else {
		s.Cat('\t', indent+1);
		s << "empty\n";
	}
	return s;
}*/

/*void ScriptLoopLoader::SetupSegment(ScriptLoopSegment& s) {
	
	
	// Do the action plan searching
	s.as.SetLimit(10000);
	
}*/

/*void ScriptLoopLoader::Forward() {
	if (IsReady())
		return;
	
	ASSERT(!IsFailed());
	ScriptStatus prev_status = status;
	
	TODO*/
	
	/*if (status == ScriptStatus::IN_BEGINNING) {
		if (!InitSegments())
			return;
		
		SetStatus(WAITING_CHILDREN);
	}
	
	if (status == ScriptStatus::WAITING_CHILDREN) {
		SetStatus(SEARCH_SEGMENT);
	}
	
	if (status == ScriptStatus::SEARCH_SEGMENT) {
		MACHVER_ENTER(ScriptLoopLoaderForwardBeginning)
		
		if (def.stmts.IsEmpty() && def.req.IsEmpty()) {
			String id = def.id.ToString();
			SetError("Loop " + IntStr(GetId()) + " '" + id + "' has no statements");
			MACHVER_LEAVE(ScriptLoopLoaderForwardBeginning)
			return;
		}
		
		SearchNewSegment();
		
		MACHVER_LEAVE(ScriptLoopLoaderForwardBeginning)
	}
	else if (status == ScriptStatus::PRUNE_SEGMENT_GOALS) {
		PruneSegmentGoals();
	}
	else  if (status == ScriptStatus::WAITING_OTHER_LOOPS) {
		int si = planner.GetSideSinks().GetCount();
		int sr = planner.GetSideSources().GetCount();
		ASSERT_(si || sr, "planner side links have been cleared for retry");
		RTLOG("ScriptLoopLoader::Forward: WAITING_OTHER_LOOPS -> WAITING_PARENT_SIDE_LINKS: " << def.id.ToString() << " sinks=" << si << " srcs=" << sr);
		SetStatus(WAITING_PARENT_SIDE_LINKS);
	}
	else  if (status == ScriptStatus::WAITING_PARENT_SIDE_LINKS) {
		// pass
		return;
	}
	else {
		
		TODO
		
	}
	
	ASSERT(prev_status != status);*/
//}

bool ScriptLoopLoader::Load() {
	RTLOG("ScriptLoopLoader::Load: " << def.id.ToString());
	ScriptLoader& loader = GetLoader();
	
	bool has_link = !def.is_driver;
	
	// Target entity for atoms
	Script::Id deep_id = GetDeepId();
	//DUMP(deep_id);
	LoopRef l = loader.ResolveLoop(deep_id);
	if (!l) {
		AddError(def.loc, "Could not resolve entity with deep id: " + deep_id.ToString());
		return false;
	}
	
	const auto& map = Parallel::Factory::AtomDataMap();
	LinkBaseRef first_lb;
	AtomBaseRef first_ab;
	
	for(int i = 0; i < def.atoms.GetCount(); i++) {
		const Script::AtomDefinition& atom_def = def.atoms[i];
		const AtomTypeCls atom = atom_def.iface.type;
		const LinkTypeCls link = atom_def.link;
		
		String loop_action = atom_def.id.ToString();
		
		bool is_first = i == 0;
		bool is_last = i == def.atoms.GetCount();
		LinkBaseRef lb;
		AtomBaseRef ab;
		
		if (is_last) {
			ab = first_ab;
			lb = first_lb;
		}
		else {
			ab = l->GetSpace()->AddTypeCls(atom);
			if (has_link)
				lb = l->AddTypeCls(link);
		}
		
		if (is_first) {
			first_ab = ab;
			first_lb = lb;
			is_first = false;
		}
		
		if (!ab) {
			String atom_name = Parallel::Factory::AtomDataMap().Get(atom).name;
			AddError(def.loc, "Could not create atom '" + atom_name + "' at '" + def.id.ToString() + "'");
			DUMP(atom);
			ASSERT(0);
			return false;
		}
		
		if (!lb && has_link) {
			String atom_name = Parallel::Factory::AtomDataMap().Get(atom).name;
			AddError(def.loc, "Could not create link for atom '" + atom_name + "' at '" + def.id.ToString() + "'");
			DUMP(atom);
			ASSERT(0);
			return false;
		}
		
		ab->SetId(id);
		if (has_link) {
			lb->SetId(id);
		
			ab->link = &*lb;
			lb->atom = &*ab;
		}
		
		auto& c = added_atoms.Add();
		c.a					= ab;
		c.l					= lb;
		c.iface				= atom_def.iface;
		c.iface.type		= atom;
		
		c.a->SetInterface(c.iface);
		
		//c.iface				= n->GetInterface();
		//ASSERT(/*!c.iface.type.IsValid() ||*/ c.iface.IsComplete());
		
		//AtomTypeCls type = ws.GetAtom();
		//ASSERT(!c.iface.type.IsValid() || type == c.iface.type);
		//ASSERT((type.iface.src.count == 1 && type.iface.sink.count == 1) || c.iface.type.IsValid());
		
		
		// Add arguments to ws
		#if 0
		const Script::Statement* stmt = ws.FindStatement(prev_ws0, def.stmts);
		if (!stmt) stmt = ws.FindStatement(prev_ws1, def.stmts);
		if (stmt) {
			RTLOG("ScriptLoopLoader::Load: stmt found: " << stmt->ToString());
			for (const Script::Statement& arg : stmt->args) {
				//LOG("\t" << arg.id.ToString());
				String k = arg.id.ToString();
				String v = arg.value ? arg.value->GetValue() : String();
				ws.Set("." + k, v);
				LOG("ScriptLoopLoader::Load: set argument: " << k << " = " << v);
			}
		}
		else {
			RTLOG("ScriptLoopLoader::Load: stmt not found:       ws: " << ws.ToString());
			if (prev_ws0)
				RTLOG("                                        prev_ws0: " << prev_ws0->ToString());
			if (prev_ws0)
				RTLOG("                                        prev_ws1: " << prev_ws1->ToString());
			DUMPI(def.stmts);
			if (!ws.IsEmpty())
				stmt = ws.FindStatement(prev_ws0, def.stmts, true);
		}
		#endif
		
		Script::WorldState ws;
		
		for(int i = 0; i < atom_def.args.GetCount(); i++) {
			String key = atom_def.args.GetKey(i);
			const Object& obj = atom_def.args[i];
			ws.values.GetAdd("." + key) = obj;
		}
		
		if (!ab->InitializeAtom(ws) || !ab->Initialize(ws)) {
			const auto& a = Parallel::Factory::AtomDataMap().Get(atom);
			AddError(def.loc, "Could not " + String(!ab ? "create" : "initialize") + " atom '" + a.name + "' at '" + def.id.ToString() + "'");
			return false;
		}
		
		if (has_link && !lb->Initialize(ws)) {
			const auto& a = Parallel::Factory::AtomDataMap().Get(atom);
			AddError(def.loc, "Could not " + String(!ab ? "create" : "initialize") + " atom '" + a.name + "' at '" + def.id.ToString() + "'");
			return false;
		}
		
		ab->SetInitialized();
		
	}
	
	if (has_link) {
		UpdateLoopLimits();
	
		for(int i = 0; i < added_atoms.GetCount(); i++) {
			AddedAtom& src_info = added_atoms[i];
			AtomBaseRef src = src_info.a;
			
			int next_i = (i + 1) % added_atoms.GetCount();
			AddedAtom& sink_info = added_atoms[next_i];
			AtomBaseRef sink = sink_info.a;
			
			/*
			ScriptLoopSegment& sink_seg = segments[sink_info.seg_i];
			Script::ActionNode& sink_an = *sink_seg.ep.plan[sink_info.plan_i];
			const Script::WorldState& sink_ws = sink_an.GetWorldState();
			
			ValDevCls common_vd = sink_ws.GetCommonSink();
			ASSERT(common_vd.IsValid());
			*/
			if (!l->MakeLink(src, sink)) {
				/*AtomTypeCls atom = sink_ws.GetAtom();
				String atom_name = Parallel::Factory::AtomDataMap().Get(atom).name;
				String src_sink_name = Parallel::Factory::IfaceLinkDataMap().Get(common_vd).name;
				SetError("Could not link atom '" + atom_name + "' source '" + src_sink_name + "' at '" + def.id.ToString() + "'");*/
				AddError(FileLocation(), "could not link atoms");
				return false;
			}
			
			atoms.Add(src);
		}
	}
	
	
	
	AddedAtom& first = added_atoms[0];
	AddedAtom& last  = added_atoms.Top();
	
	
	// Process sub-loops
	/*for (Script::Statement& stmt : def.stmts) {
		if (!stmt.value || stmt.value->type != Script::Value::VAL_CUSTOMER)
			continue;
		//LoadLoopDefinition(stmt.value->customer);
		SetError("Sub-loops not supported yet");
		return false;
	}*/
	
	
	// Add changes to parent state
	/*const Script::WorldState& ret_ws = last_seg.ep.plan.Top()->GetWorldState();
	if (!scope.current_state.Append(ret_ws, def.ret_list)) {
		SetError("Invalid type in return value");
		return false;
	}*/
	
	//status = READY;
	return true;
}

void ScriptLoopLoader::UpdateLoopLimits() {
	
	// as in AtomBase::LinkSideSink
	
	bool changes = false;
	int c = added_atoms.GetCount();
	int total_max = 1000000;
	int total_min = 0;
	
	for(int i = 0; i < c; i++) {
		AddedAtom& info = added_atoms[i];
		InterfaceSourceRef src = info.a->GetSource();
		int src_c = src->GetSourceCount();
		for(int j = 0; j < src_c; j++) {
			int src_min_packets = src->GetSourceValue(j).GetMinPackets();
			int src_max_packets = src->GetSourceValue(j).GetMaxPackets();
			total_min = max(total_min, src_min_packets);
			total_max = min(total_max, src_max_packets);
		}
		
		InterfaceSinkRef sink = info.a->GetSink();
		int sink_c = sink->GetSinkCount();
		for(int j = 0; j < sink_c; j++) {
			int sink_min_packets = sink->GetValue(j).GetMinPackets();
			int sink_max_packets = sink->GetValue(j).GetMaxPackets();
			total_min = max(total_min, sink_min_packets);
			total_max = min(total_max, sink_max_packets);
		}
	}
	
	if (total_min > total_max) {
		total_max = total_min;
	}
	
	LOG("ScriptLoopLoader::UpdateLoopLimits: set loop limits: min=" << total_min << ", max=" << total_max);
	
	for(int i = 0; i < c; i++) {
		AddedAtom& info = added_atoms[i];
		
		InterfaceSourceRef src = info.a->GetSource();
		InterfaceSinkRef sink = info.a->GetSink();
		
		int sink_c = sink->GetSinkCount();
		for(int k = 0; k < sink_c; k++) {
			Value& v = sink->GetValue(k);
			v.SetMinQueueSize(total_min);
			v.SetMaxQueueSize(total_max);
		}
		
		int src_c = src->GetSourceCount();
		for(int k = 0; k < src_c; k++) {
			Value& v = src->GetSourceValue(k);
			v.SetMinQueueSize(total_min);
			v.SetMaxQueueSize(total_max);
		}
			
		/*
		//DUMP(min_packets);
		//DUMP(sink_min_packets);
		//DUMP(src_min_packets);
		*/
	}
}


bool ScriptLoopLoader::PostInitialize() {
	for(int i = added_atoms.GetCount()-1; i >= 0; i--) {
		AddedAtom& a = added_atoms[i];
		if (!a.a->PostInitialize())
			return false;
		if (a.l && !a.l->PostInitialize())
			return false;
	}
	return true;
}

bool ScriptLoopLoader::Start() {
	for(int i = added_atoms.GetCount()-1; i >= 0; i--) {
		AddedAtom& a = added_atoms[i];
		if (!a.a->Start())
			return false;
		a.a->SetRunning();
		
		if (a.l && !a.l->Start())
			return false;
	}
	return true;
}



NAMESPACE_SERIAL_END


