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
	if (0) {
		s << "layer: " << layer << ", src: " << HexStr(src) << ", sink: " << HexStr(sink);
	}
	else {
		s << "layer: " << layer << ", src: " << src->base->GetClassName() << ":" << src->name << ", sink: " << sink->base->GetClassName() << ":" << sink->name;
	}
	return s;
}

void LinkMap::UpdateLinkLayers() {
	for (Link& l : links)
		l.layer = -1;
	
	for (Link& l : links) {
		Pin* src_pin = CastPtr<Pin>(l.src->base);
		Pin* sink_pin = CastPtr<Pin>(l.sink->base);
		ASSERT(!src_pin || !src_pin->is_ref_volt || !src_pin->is_high);
		ASSERT(!sink_pin || !sink_pin->is_ref_volt || sink_pin->is_high);
		if (src_pin && src_pin->is_ref_volt && !src_pin->is_high) {
			l.layer = 0;
		}
		if (sink_pin && sink_pin->is_ref_volt && sink_pin->is_high) {
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
	init_ops.SetCount(0);
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


NAMESPACE_TOPSIDE_END
