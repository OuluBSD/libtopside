#include "Internal.h"


NAMESPACE_SERIAL_BEGIN


namespace Script {
bool LoopDefinition::IsPathTrailMatch(const Vector<String>& parts) const {
	if (parts.IsEmpty() || parts.GetCount() > id.parts.GetCount())
		return false;
	for (int i = 0; i < parts.GetCount(); i++) {
		int a = parts.GetCount()-1-i;
		int b = id.parts.GetCount()-1-i;
		const String& as = parts[a];
		const String& bs = id.parts.At(b);
		if (as != bs)
			return false;
	}
	return true;
}
}




ScriptLoopLoader::ScriptLoopLoader(ScriptChainLoader& parent, int id, Script::LoopDefinition& def) :
	Base(parent, id, def)
{
	
}

void ScriptLoopLoader::GetLoops(Vector<ScriptLoopLoader*>& v) {
	Panic("internal error");
}

String ScriptLoopLoader::GetTreeString(int indent) {
	String s;
	s.Cat('\t', indent);
	s << "Loop " << id;
	s.Cat('\n');
	
	return s;
}

void ScriptLoopLoader::SetSideSourceConnected(const AtomTypeCls& type, int ch_i, ScriptLoopLoader& sink) {
	ASSERT(type.IsValid());
	ASSERT(ch_i > 0);
	ASSERT(type.iface.src.GetCount() > 1 && ch_i < type.iface.src.GetCount());
	int side_ch_i = ch_i - 1;
	
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
			return false;
		}
		dbg_i++;
	}
	dbg_i = 0;
	for (const SideLink& l : atom.sink_side_conns) {
		if (l.is_required && !l.link) {
			return false;
		}
		dbg_i++;
	}
	return true;
}

void ScriptLoopLoader::UndoLoad() {
	for(int i = added_atoms.GetCount()-1; i >= 0; i--)
		added_atoms[i].a->Stop();
	for(int i = added_atoms.GetCount()-1; i >= 0; i--)
		added_atoms[i].a->UninitializeDeep();
}

bool ScriptLoopLoader::Load() {
	RTLOG("ScriptLoopLoader::Load: " << def.id.ToString());
	ScriptLoader& loader = GetLoader();
	
	bool has_link = !def.is_driver;
	
	// Target entity for atoms
	Script::Id deep_id = GetDeepId();
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
		
		
		// Add arguments to ws
		
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
		
		LOG("Linking atoms:");
		for(int i = 0; i < added_atoms.GetCount(); i++) {
			LOG(i << ": " << added_atoms[i].iface.type.ToString());
		}
		
		for(int i = 0; i < added_atoms.GetCount(); i++) {
			AddedAtom& src_info = added_atoms[i];
			AtomBaseRef src = src_info.a;
			
			int next_i = (i + 1) % added_atoms.GetCount();
			AddedAtom& sink_info = added_atoms[next_i];
			AtomBaseRef sink = sink_info.a;
			
			if (!l->MakeLink(src, sink)) {
				AddError(FileLocation(), "could not link atoms");
				for(int i = added_atoms.GetCount()-1; i >= 0; i--)
					added_atoms[i].a->Stop();
				for(int i = added_atoms.GetCount()-1; i >= 0; i--)
					added_atoms[i].a->UninitializeDeep();
				return false;
			}
			
			atoms.Add(src);
		}
	}
	
	AddedAtom& first = added_atoms[0];
	AddedAtom& last  = added_atoms.Top();
	
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
		
	}
}


bool ScriptLoopLoader::PostInitialize() {
	int c = added_atoms.GetCount()-1;
	for(int i = c; i >= 0; i--) {
		AddedAtom& a = added_atoms[i];
		if (!a.a->PostInitialize())
			return false;
		if (a.l && !a.l->PostInitialize())
			return false;
	}
	return true;
}

bool ScriptLoopLoader::Start() {
	int c = added_atoms.GetCount()-1;
	for(int i = c; i >= 0; i--) {
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


