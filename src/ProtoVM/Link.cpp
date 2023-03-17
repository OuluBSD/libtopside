#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


Link::Link() {
	
}

bool Link::operator()(const Link& a, const Link& b) const {
	//if (a.layer != b.layer) return a.layer < b.layer;
	if (a.sink->base != b.sink->base) return a.sink->base < b.sink->base;
	if (a.sink->id != b.sink->id) return a.sink->id < b.sink->id;
	if (a.src->base != b.src->base) return a.src->base < b.src->base;
	if (a.src->id != b.src->id) return a.src->id < b.src->id;
	return &a < &b;
}

String Link::ToString() const {
	String s;
	s << "src: " << src->base->GetName() << ":" << src->base->GetClassName() << ":" << src->name
	<< ", sink: " << sink->base->GetName() << ":" << sink->base->GetClassName() << ":" << sink->name;
	return s;
}

String ProcessOp::ToString() const {
	String s;
	s << "prio: " << priority << ", type: ";
	switch (type) {
		//case READ: s << "READ"; break;
		case WRITE: s << (successor ? "BIDIR" : "WRITE"); break;
		case TICK: s << "TICK"; break;
		default: s << "INVALID"; break;
	}
	
	if (src && sink) {
		s << ", src: " << src->base->GetName() << ":" << src->base->GetClassName() << ":" << src->name
		  << ", sink: " << sink->base->GetName() << ":" << sink->base->GetClassName() << ":" << sink->name;
	}
	else if (dest)
		s << ", base: " << dest->GetClassName() << ", name: " << dest->GetName();
	
	s << ", ";
	if (mem_bytes)
		s << mem_bytes << " bytes, ";
	s << mem_bits << " bits";
	
	return s;
}

bool ProcessOp::operator()(const ProcessOp& a, const ProcessOp& b) const {
	int a_prio = a.priority < 0 ? INT_MAX / 2 : a.priority;
	int b_prio = b.priority < 0 ? INT_MAX / 2 : b.priority;
	if (a_prio != b_prio)
		return a_prio < b_prio;
	if ((bool)a.successor != (bool)b.successor)
		return a.successor != 0;
	if (a.type != b.type)
		return a.type > b.type;
	if (a.link && b.link)
		return a.link->operator()(*a.link, *b.link);
	return a.link != 0;
}
/*bool UnitOps::HasOps(ProcessType type) const {
	for (ProcessOp* op : ops) {
		if (op->type == type)
			return true;
	}
	return false;
}*/

#if 1
void LinkMap::UpdateLinkLayers() {
	rt_ops.SetCount(0);
	rt_ops.Reserve(links.GetCount() * 2);
	units.Clear();
	
	Vector<ElcBase*> unit_ptrs;
	
	for (Link& link : links) {
		VectorFindAdd(unit_ptrs, link.sink->base);
		VectorFindAdd(unit_ptrs, link.src->base);
	}
	
	for (ElcBase* ptr : unit_ptrs) {
		UnitOps& unit = units.Add((size_t)ptr);
		unit.unit = ptr;
	}
	
	DUMPC(links);
	for (Link& link : links) {
		UnitOps& src_unit = units.Get((size_t)link.src->base);
		UnitOps& sink_unit = units.Get((size_t)link.sink->base);
		
		// Write op
		ProcessOp& write_op = rt_ops.Add();
		ASSERT(link.src->is_src);
		{
			ProcessOp& op = write_op;
			op.priority = -1;
			op.type = ProcessType::WRITE;
			op.mem_bytes = 0;
			op.mem_bits = 1;
			op.link = &link;
			op.processor = link.src->base;
			op.dest = link.sink->base;
			op.id = link.src->id;
			op.dest_id = link.sink->id;
			op.src = link.src;
			op.sink = link.sink;
			
			ASSERT(sink_unit.unit->GetFixedPriority() != 0);
			sink_unit.read_ops.Add(&op);
			src_unit.write_ops.Add(&op);
		}
		
		// Bidirectional write op
		if (link.src->is_sink && link.sink->is_src) {
			ProcessOp& op = rt_ops.Add();
			op.priority = -1;
			op.type = ProcessType::WRITE;
			op.mem_bytes = 0;
			op.mem_bits = 1;
			op.link = &link;
			op.processor = link.sink->base;
			op.dest = link.src->base;
			op.id = link.sink->id;
			op.dest_id = link.src->id;
			op.successor = &write_op;
			op.sink = link.src;
			op.src = link.sink;
			
			ASSERT(src_unit.unit->GetFixedPriority() != 0);
			src_unit.read_ops.Add(&op);
			sink_unit.write_ops.Add(&op);
		}
		
		// Unsupported: read?
		if (!link.src->is_src) {
			TODO // is this fail?
		}
	}
	
	for (UnitOps& unit : units.GetValues()) {
		
		// Tick op
		{
			ProcessOp& op = rt_ops.Add();
			
			// write-only chips can be processed first
			op.priority = unit.unit->GetFixedPriority();
			op.type = ProcessType::TICK;
			op.mem_bytes = 0;
			op.mem_bits = 0;
			op.link = 0;
			op.processor = 0;
			op.dest = unit.unit;
			op.id = 0;
			op.dest_id = 0;
			unit.tick_op = &op;
			
			// Units without read can be prioritized first (also related ops)
			if (!unit.HasReadOps()) {
				op.priority = 0;
			}
			
			// Write initial priority (default is unset, which is -1)
			for (ProcessOp* write_op : unit.write_ops)
				write_op->priority = op.priority;
		}
	}
	
	Sort(rt_ops, ProcessOp());
	
}

bool LinkMap::UpdateProcess() {
	/*
	- sort by chip
		- chips with all inputs ready earlier
		- chips with READ pins before chips with RW pins
	- Tick between READ and WRITE !!!
	- check if ProcessOp can be finalized based on ProcessOp::successor value
		- probably leave at least 1 between values because of this (prefer. 10)
	*/
	
	bool very_verbose = false;
	bool verbose = true;
	int priority_step = 10;
	int priority = priority_step;
	
	// Optimized processed op checking
	Vector<ProcessOp*> todo_ops;
	for (ProcessOp& op : rt_ops)
		todo_ops.Add(&op);
	Vector<int> rm_list;
	
	while (1) {
		priority += priority_step;
		
		bool changed_priority = false;
		for (ProcessOp& op : rt_ops) {
			if (op.IsBiDir() && !op.HasPriority()) {
				op.priority = priority;
				changed_priority = true;
			}
		}
		
		if (changed_priority)
			continue;
		
		if (very_verbose) {
			Sort(rt_ops, ProcessOp());
			DUMPC(rt_ops);
		}
			
		int ticked_count = 0;
		for (UnitOps& unit : units.GetValues()) {
			
			// Check if tick can be made
			if (!unit.tick_op->HasPriority()) {
				
				// Check if all pins have been written
				bool read_ready = true;
				for (ProcessOp* op : unit.read_ops) {
					if (!op->HasPriority()) {
						read_ready = false;
						break;
					}
				}
				
				if (read_ready) {
					unit.tick_op->priority = priority + 1;
					ticked_count++;
					
					for (ProcessOp* write_op : unit.write_ops) {
						if (!write_op->HasPriority())
							write_op->priority = priority + 2;
					}
				}
			}
		}
		
		if (!ticked_count) {
			LOG("LinkMap::UpdateProcess: error: couldn't tick any unit");
			return false;
		}
		
		
		// Remove ready
		rm_list.SetCount(0);
		int i = 0;
		for (ProcessOp* todo_op : todo_ops)
			if (todo_op->HasPriority())
				rm_list.Add(i++);
			else i++;
		todo_ops.Remove(rm_list);
		
		
		// Break when all ready
		if (todo_ops.IsEmpty())
			break;
	}
	
	
	// Hotfix: set bidir-read op before tick... (not sure what to do, as they are too early now)
	for (UnitOps& unit : units.GetValues()) {
		if (!unit.tick_op->priority)
			continue;
		for (ProcessOp* op : unit.read_ops) {
			if (op->IsBiDir())
				op->priority = unit.tick_op->priority - 1;
		}
	}
	
	
	// Sort ops (required for merge)
	Sort(rt_ops, ProcessOp());
	
	
	// Merge bit ops to byte ops
	rm_list.SetCount(0);
	for(int i = 0; i < rt_ops.GetCount(); i++) {
		ProcessOp& op = rt_ops[i];
		if (op.type != WRITE)
			continue;
		ElcConn* src = op.src;
		ElcConn* sink = op.sink;
		
		// Hack: find byte ranges for speedup
		bool found_byte_range = false;
		if ((src->name == "0" || src->name == "A0" || src->name == "D0") &&
			(sink->name == "0" || sink->name == "A0" || sink->name == "D0")) {
			String src_prefix = src->name.Left(src->name.GetCount()-1);
			String sink_prefix = sink->name.Left(sink->name.GetCount()-1);
			int match_count = 1;
			for(int j = i+1, k = 1; j < rt_ops.GetCount(); j++, k++) {
				ProcessOp& op0 = rt_ops[j];
				if (op0.type != WRITE)
					continue;
				
				String chk_src = src_prefix + IntStr(k);
				String chk_sink = sink_prefix + IntStr(k);
				
				if (op0.src->name != chk_src || op0.sink->name != chk_sink)
					break;
				
				match_count++;
			}
			
			// Check if match count aligns byte size
			if (match_count >= 2) {
				found_byte_range = true;
				int bytes = match_count / 8;
				int bitmod = match_count % 8;
				//if (verbose) {LOG("byte op: " << bytes << " bytes" << (bitmod ? " + " + IntStr(bitmod) + " bits" : String()) << ": " << ToString());}
				
				op.mem_bytes = bytes;
				op.mem_bits = bitmod;
				
				for(int j = 1; j < match_count; j++)
					rm_list.Add(i+j);
				i += match_count - 1; // skip bits, which were included in bytes
			}
		}
	}
	rt_ops.Remove(rm_list);
	
	if (verbose) {
		Sort(rt_ops, ProcessOp());
		DUMPC(rt_ops);
	}
	
	return true;
}

#else
void LinkMap::UpdateLinkLayers() {
	for (Link& l : links)
		l.layer = -1;
	
	for (Link& l : links) {
		Pin* src_pin = CastPtr<Pin>(l.src->base);
		Pin* sink_pin = CastPtr<Pin>(l.sink->base);
		ASSERT(!src_pin || !src_pin->is_high);
		ASSERT(!sink_pin || sink_pin->is_high);
		if (src_pin && !src_pin->is_high) {
			l.layer = 0;
		}
		if (sink_pin && sink_pin->is_high) {
			l.layer = INT_MAX;
		}
	}
	
	Sort(links, Link());
	DUMPC(links);
	
	while (1) {
		bool have_orphans = false;
		bool changes = false;
		
		for (Link& l : links) {
			if (l.layer >= 0)
				continue;
			
			int sink_min_layer, sink_max_layer;
			int src_min_layer, src_max_layer;
			
			Pin* src_pin = CastPtr<Pin>(l.src->base);
			Pin* sink_pin = CastPtr<Pin>(l.sink->base);
			GetLayerRange(*l.src->base, src_min_layer, src_max_layer);
			GetLayerRange(*l.sink->base, sink_min_layer, sink_max_layer);
			
			if (sink_min_layer < 0 &&
				sink_max_layer < 0 &&
				src_min_layer < 0 &&
				src_max_layer < 0) {
				have_orphans = true;
			}
			
			else if (src_min_layer < sink_min_layer || sink_min_layer < 0) {
				l.layer = src_min_layer + 1;
				changes = true;
			}
		}
		
		if (!changes)
			break;
	}
	
	
	Sort(links, Link());
	DUMPC(links);
}

void LinkMap::GetLayerRange(const ElectricNodeBase& n, int& min, int& max) {
	min = INT_MAX;
	max = INT_MIN;
	
	for (const ElectricNodeBase::Connector& c : n.conns) {
		
		for (const ElectricNodeBase::CLink& l : c.links) {
			Link& link = *l.link;
			if (link.layer < 0)
				continue;
			
			if (link.layer < min) min = link.layer;
			if (link.layer > max) max = link.layer;
		}
		
	}
	
	if (min == INT_MAX) {
		min = -1;
		max = -1;
	}
}

void LinkMap::UpdateProcess() {
	rt_ops.SetCount(0);
	
	Vector<ElcBase*> units;
	
	for (Link& link : links) {
		VectorFindAdd(units, link.sink->base);
		VectorFindAdd(units, link.src->base);
	}
	
	bool verbose = true;
	
	if (verbose) {
		LOG("Units:");
		for (ElcBase* u : units) {
			LOG("\t" << u->GetClassName());
		}
	}
	
	// Reserve memory
	#if 0
	int mem_count = 0;
	for (ElcBase* u : units) {
		int mem_sz = u->GetMemorySize();
		if (mem_sz > 0) {
			if (verbose) {LOG("Reserving memory for " << u->GetClassName() << " " << u->GetName() << ": " << mem_sz << " bytes");}
			ProcessOp& op = init_ops.Add();
			op.type = ProcessOp::REALIZE_MEMORY;
			op.mem_bytes = mem_sz;
			op.mem_id = mem_count++;
		}
	}
	#endif
	
	for(int i = 0; i < links.GetCount(); i++) {
		Link& link = links[i];
		
		// Hack: find byte ranges for speedup
		bool found_byte_range = false;
		if ((link.src->name == "0" || link.src->name == "A0" || link.src->name == "D0") &&
			(link.sink->name == "0" || link.sink->name == "A0" || link.sink->name == "D0")) {
			String src_prefix = link.src->name.Left(link.src->name.GetCount()-1);
			String sink_prefix = link.sink->name.Left(link.sink->name.GetCount()-1);
			int match_count = 1;
			for(int j = i+1, k = 1; j < links.GetCount(); j++, k++) {
				Link& link0 = links[j];
				String chk_src = src_prefix + IntStr(k);
				String chk_sink = sink_prefix + IntStr(k);
				
				if (link0.src->name != chk_src || link0.sink->name != chk_sink)
					break;
				
				match_count++;
			}
			
			// Check if match count aligns byte size
			if (match_count >= 2) {
				found_byte_range = true;
				int bytes = match_count / 8;
				int bitmod = match_count % 8;
				if (verbose) {LOG("byte op: " << bytes << " bytes" << (bitmod ? " + " + IntStr(bitmod) + " bits" : String()) << ": " << link.ToString());}
				
				ProcessOp& op = rt_ops.Add();
				if (link.src->is_sink && link.src->is_src)
					op.type = ProcessType::RW;
				else if (link.src->is_src)
					op.type = ProcessType::WRITE;
				else
					TODO; // fail?
				op.mem_bytes = bytes;
				op.mem_bits = bitmod;
				op.link = &link;
				op.processor = link.src->base;
				op.dest = link.sink->base;
				op.id = link.src->id;
				op.dest_id = link.sink->id;
				i += match_count - 1; // skip bits, which were included in bytes
			}
		}
		if (!found_byte_range) {
			if (verbose) {LOG("bit op: " << link.ToString());}
			
			// Add op
			ProcessOp& op = rt_ops.Add();
			if (link.src->is_sink && link.src->is_src)
				op.type = ProcessType::RW;
			else if (link.src->is_src)
				op.type = ProcessType::WRITE;
			else
				TODO; // fail?
			op.mem_bytes = 0;
			op.mem_bits = 1;
			op.link = &link;
			op.processor = link.src->base;
			op.dest = link.sink->base;
			op.id = link.src->id;
			op.dest_id = link.sink->id;
		}
	}
	
}
#endif


NAMESPACE_TOPSIDE_END
