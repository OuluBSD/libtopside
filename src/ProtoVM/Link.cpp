#include "ProtoVM.h"



Link::Link() {
	
}

bool Link::operator()(const Link& a, const Link& b) const {
	return a.layer < b.layer;
}

String Link::ToString() const {
	String s;
	s << "layer: " << layer << ", src: " << HexStr(src) << ", sink: " << HexStr(sink);
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
	
	for (ElectricNodeBase::Connector& c : n.conns) {
		
		for (ElectricNodeBase::CLink& l : c.links) {
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