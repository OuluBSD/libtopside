#include "EonBaseGen.h"

NAMESPACE_EONGEN_BEGIN


World::World() {
	
}

void World::OnError(String msg) {
	LOG("World: error: " << msg);
}

bool World::LoadJSON(String json) {
	Object o = ParseJSON(json);
	//LOG(GetObjectTreeString(o));
	
	if (!o.IsMap())
		return false;
	
	ObjectMap& m = o.GetMap();
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (key == "bases") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadBases(sub.GetMap()))
				return false;
		}
		else if (key == "headers") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadHeaders(sub.GetMap()))
				return false;
		}
		else if (key == "loops") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadLoops(sub.GetMap()))
				return false;
		}
		else if (key == "nodelinks") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadNodeLinks(sub.GetMap()))
				return false;
		}
		else if (key == "chains") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadChains(sub.GetMap()))
				return false;
		}
		else if (key == "topchains") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadTopChains(sub.GetMap()))
				return false;
		}
		else TODO
		
	}
	
	
	return true;
}

bool World::LoadBases(ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (!sub.IsMap()) {
			OnError("Expected map");
			return false;
		}
		
		if (!LoadBase(key, sub.GetMap()))
			return false;
	}
	
	return true;
}

bool World::LoadHeaders(ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (!sub.IsMap()) {
			OnError("Expected map");
			return false;
		}
		
		if (!LoadHeader(key, sub.GetMap()))
			return false;
	}
	
	return true;
}

bool World::LoadLoops(ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (!sub.IsMap()) {
			OnError("Expected map");
			return false;
		}
		
		if (!LoadLoop(key, sub.GetMap()))
			return false;
	}
	
	return true;
}

bool World::LoadNodeLinks(ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (!sub.IsMap()) {
			OnError("Expected map");
			return false;
		}
		
		if (!LoadNodeLink(key, sub.GetMap()))
			return false;
	}
	
	return true;
}

bool World::LoadChains(ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (!sub.IsMap()) {
			OnError("Expected map");
			return false;
		}
		
		if (!LoadChain(key, sub.GetMap()))
			return false;
	}
	
	return true;
}

bool World::LoadTopChains(ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (!sub.IsMap()) {
			OnError("Expected map");
			return false;
		}
		
		if (!LoadTopChain(key, sub.GetMap()))
			return false;
	}
	
	return true;
}

bool World::LoadBase(String key, ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	int i = units.Find(key);
	if (i >= 0) {
		OnError("Unit '" + key + "' already exists");
		return false;
	}
	
	Object* sink = m.TryFind("sink");
	Object* side = m.TryFind("side");
	Object* src  = m.TryFind("src");
	if (!sink || !sink->IsString()) {OnError("Base '" + key + "' is missing sink string");   return false;}
	if (!src  || !src->IsString())  {OnError("Base '" + key + "' is missing source string"); return false;}
	if (!side || !side->IsString()) {OnError("Base '" + key + "' is missing side string");   return false;}
	
	Unit& unit = units.Add(key);
	unit.type = Unit::BASE;
	unit.key = key;
	
	if (!ParseValDev(sink->Get<String>(), unit.sink, unit.sink_count)) return false;
	if (!ParseValDev(src->Get<String>(),  unit.src, unit.src_count)) return false;
	
	
	String side_str = side->Get<String>();
	if (side_str == "src") {
		unit.side_src = true;
		unit.side_dev = unit.src.dev;
	}
	else if (side_str == "sink") {
		unit.side_src = false;
		unit.side_dev = unit.sink.dev;
	}
	else {
		CParser p(side_str);
		if (!p.IsId()) {
			OnError("Expected id in '" + side_str + "'");
			return false;
		}
		String dev_str = p.ReadId();
		unit.side_dev =  DevCls::Get(dev_str);
		if (unit.side_dev == DevCls::INVALID) {
			OnError("Invalid device class in '" + side_str + "'");
			return false;
		}
		
		if (!p.Char('-')) {
			OnError("Expected '-' in '" + side_str + "'");
			return false;
		}
		
		if (!p.IsId()) {
			OnError("Expected id in '" + side_str + "'");
			return false;
		}
		String side_str_part = p.ReadId();
		
		if (side_str_part == "src") {
			unit.side_src = true;
		}
		else if (side_str_part == "sink") {
			unit.side_src = false;
		}
		else {
			OnError("Unexpected side id '" + side_str_part + "'");
			return false;
		}
	}
	
	
	return true;
}

bool World::LoadHeader(String key, ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	int i = units.Find(key);
	if (i >= 0) {
		OnError("Unit '" + key + "' already exists");
		return false;
	}
	
	Object* base = m.TryFind("base");
	if (!base || !base->IsString()) {OnError("Base '" + key + "' is missing base string");   return false;}
	
	Unit& unit = units.Add(key);
	unit.type = Unit::HEADER;
	
	String base_str = base->Get<String>();
	
	i = units.Find(base_str);
	if (i < 0) {
		OnError("Base unit '" + key + "' does not exist");
		return false;
	}
	
	Unit& base_unit = units[i];
	Link& link = links.Add();
	link.type = Link::BASE_UNIT;
	link.from_unit = &unit;
	link.to_unit = &base_unit;
	
	unit.links.Add(&link);
	base_unit.links.Add(&link);
	
	return true;
}

bool World::LoadLoop(String key, ObjectMap& m) {
	
	int i = nodes.Find(key);
	if (i >= 0) {
		OnError("Unit '" + key + "' already exists");
		return false;
	}
	
	Object* m_headers = m.TryFind("headers");
	if (!m_headers || !m_headers->IsArray()) {OnError("Base '" + key + "' is missing headers array"); return false;}
	ObjectArray& headers = m_headers->GetArray();
	
	Vector<Unit*> header_ptrs;
	for(int i = 0; i < headers.GetCount(); i++) {
		Object& a_header = headers[i];
		if (!a_header.IsString()) {
			OnError("Expected string in headers array");
			return false;
		}
		
		String header_key = a_header.Get<String>();
		i = units.Find(header_key);
		if (i < 0) {
			OnError("Header unit '" + header_key + "' does not exist");
			return false;
		}
		
		Unit& header_unit = units[i];
		if (header_unit.type != Unit::HEADER) {
			OnError("Type of the unit '" + header_key + "' is not HEADER");
			return false;
		}
		
		header_ptrs.Add(&header_unit);
	}
	
	Node& node = nodes.Add(key);
	node.type = Node::LOOP;
	
	for (Unit* header : header_ptrs) {
		Link& link = links.Add();
		link.type = Link::LOOP_UNIT;
		link.from_node = &node;
		link.to_unit = header;
		
		node.links.Add(&link);
		header->links.Add(&link);
	}
	
	return true;
}

bool World::LoadNodeLink(String key, ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	Object* from = m.TryFind("from");
	Object* to   = m.TryFind("to");
	if (!from || !from->IsString()) {OnError("Link '" + key + "' is missing from string");   return false;}
	if (!to   || !to->IsString())   {OnError("Link '" + key + "' is missing to string"); return false;}
	
	String from_str = from->Get<String>();
	String to_str = to->Get<String>();
	
	int i = nodes.Find(from_str);
	if (i < 0) {
		OnError("From-node '" + from_str + "' not found");
		return false;
	}
	Node& f = nodes[i];
	
	i = nodes.Find(to_str);
	if (i < 0) {
		OnError("To-node '" + to_str + "' not found");
		return false;
	}
	Node& t = nodes[i];
	
	
	Node& node = nodes.Add(key);
	node.type = Node::VALID_NODE_LINK;
	
	
	Link& link = links.Add();
	link.type = Link::NODE_LINK;
	link.from_node = &f;
	link.to_node = &t;
	
	f.links.Add(&link);
	t.links.Add(&link);
	
	
	return true;
}

bool World::LoadChain(String key, ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	Object* m_loops = m.TryFind("loops");
	Object* m_links = m.TryFind("links");
	if (!m_loops || !m_loops->IsArray()) {OnError("Base '" + key + "' is missing loops array"); return false;}
	if (!m_links || !m_links->IsString()) {OnError("Base '" + key + "' is missing links string"); return false;}
	ObjectArray& loops = m_loops->GetArray();
	String links_str = m_links->Get<String>();
	
	Vector<Node*> loop_ptrs;
	for(int i = 0; i < loops.GetCount(); i++) {
		Object& a_loop = loops[i];
		if (!a_loop.IsString()) {
			OnError("Expected string in loops array");
			return false;
		}
		
		String loop_key = a_loop.Get<String>();
		int j = nodes.Find(loop_key);
		if (j < 0) {
			OnError("Header unit '" + loop_key + "' does not exist");
			return false;
		}
		
		Node& loop_node = nodes[j];
		if (loop_node.type != Node::LOOP) {
			OnError("Type of the node '" + loop_key + "' is not LOOP");
			return false;
		}
		
		loop_ptrs.Add(&loop_node);
	}
	
	Vector<LinkItem> str_links;
	if (!SolveLinks(links_str, str_links))
		return false;
	
	for (LinkItem& li : str_links) {
		if (li.from >= loop_ptrs.GetCount()) {
			OnError("Too large 'from' array position " + IntStr(li.from));
			return false;
		}
		
		if (li.to >= loop_ptrs.GetCount()) {
			OnError("Too large 'to' array position " + IntStr(li.to));
			return false;
		}
	}
	
	
	Node& node = nodes.Add(key);
	node.type = Node::CHAIN;
	
	for (Node* loop : loop_ptrs) {
		Link& link = links.Add();
		link.type = Link::CHAIN_LOOP;
		link.from_node = &node;
		link.to_node = loop;
		
		node.links.Add(&link);
		loop->links.Add(&link);
	}
	
	for (LinkItem& li : str_links) {
		Link& link = links.Add();
		link.type = Link::VALID_NODE_LINK;
		link.from_node = loop_ptrs[li.from];
		link.to_node = loop_ptrs[li.to];
		
		link.from_node->links.Add(&link);
		link.to_node->links.Add(&link);
	}
	
	return true;
}

bool World::LoadTopChain(String key, ObjectMap& m) {
	//DUMP(key) LOG(GetObjectTreeString(m));
	
	Object* m_nodes = m.TryFind("nodes");
	Object* m_links = m.TryFind("links");
	if (!m_nodes || !m_nodes->IsArray()) {OnError("Base '" + key + "' is missing nodes array"); return false;}
	if (!m_links || !m_links->IsString()) {OnError("Base '" + key + "' is missing links string"); return false;}
	ObjectArray& nodes = m_nodes->GetArray();
	String links_str = m_links->Get<String>();
	
	Vector<Node*> loop_ptrs;
	for(int i = 0; i < nodes.GetCount(); i++) {
		Object& a_loop = nodes[i];
		if (!a_loop.IsString()) {
			OnError("Expected string in nodes array");
			return false;
		}
		
		String loop_key = a_loop.Get<String>();
		int j = this->nodes.Find(loop_key);
		if (j < 0) {
			OnError("Header unit '" + loop_key + "' does not exist");
			return false;
		}
		
		Node& loop_node = this->nodes[j];
		if (loop_node.type != Node::LOOP &&
			loop_node.type != Node::CHAIN) {
			OnError("Type of the node '" + loop_key + "' is not LOOP or CHAIN");
			return false;
		}
		
		loop_ptrs.Add(&loop_node);
	}
	
	Vector<LinkItem> str_links;
	if (!SolveLinks(links_str, str_links))
		return false;
	
	for (LinkItem& li : str_links) {
		if (li.from >= loop_ptrs.GetCount()) {
			OnError("Too large 'from' array position " + IntStr(li.from));
			return false;
		}
		
		if (li.to >= loop_ptrs.GetCount()) {
			OnError("Too large 'to' array position " + IntStr(li.to));
			return false;
		}
	}
	
	
	Node& node = this->nodes.Add(key);
	node.type = Node::TOPCHAIN;
	
	for (Node* loop : loop_ptrs) {
		Link& link = links.Add();
		link.type = Link::CHAIN_LOOP;
		link.from_node = &node;
		link.to_node = loop;
		
		node.links.Add(&link);
		loop->links.Add(&link);
	}
	
	for (LinkItem& li : str_links) {
		Link& link = links.Add();
		link.type = Link::VALID_NODE_LINK;
		link.from_node = loop_ptrs[li.from];
		link.to_node = loop_ptrs[li.to];
		
		link.from_node->links.Add(&link);
		link.to_node->links.Add(&link);
	}
	
	return true;
}

#define ERR(msg) OnError(":" + IntStr(p.GetLine()) + ":" + IntStr(p.GetColumn()) + ": " + msg);

bool World::ParseValDev(String s, ValDevCls& vd, byte& count) {
	CParser p(s);
	if (!p.IsId()) {
		ERR("Expected id in '" + s + "'")
		return false;
	}
	String dev_str = p.ReadId();
	
	if (!p.Char('-')) {
		ERR("Expected char '-' in '" + s + "'");
		return false;
	}
	
	if (!p.IsId()) {
		ERR("Expected id in '" + s + "'")
		return false;
	}
	String val_str = p.ReadId();
	
	
	vd.dev = DevCls::Get(dev_str);
	if (vd.dev == DevCls::INVALID) {
		ERR("Invalid device id '" + dev_str + "'");
		return false;
	}
	
	
	vd.val = ValCls::Get(val_str);
	if (vd.val == ValCls::INVALID) {
		ERR("Invalid value id '" + val_str + "'");
		return false;
	}
	
	if (p.Char('-')) {
		if (p.Char('x')) {
			count = 255;
			if (!p.IsEof()) {
				ERR("Unexpected data in '" + val_str + "'");
				return false;
			}
		}
		else {
			if (p.IsInt()) {
				ERR("Expected count integer in '" + val_str + "'");
				return false;
			}
			int i = p.ReadInt();
			if (i >= 256) {
				ERR("Integer maximum is 255 in '" + val_str + "'");
				return false;
			}
			ASSERT(i >= 0);
			count = i;
		}
	}
	else {
		count = 1;
	}
	
	return true;
}

bool World::SolveLinks(String s, Vector<LinkItem>& v) {
	String err;
	enum {BEGINNING, FROM, TO, SIDE, FINISH};
	int mode = BEGINNING;
	int from, to;
	bool side = false;
	for(int i = 0; i < s.GetCount();) {
		int chr = s[i];
		
		if (IsSpace(chr)) {i++; continue;}
		if (mode == BEGINNING)
			mode = FROM;
		
		if (mode == FROM || mode == TO) {
			int integer;
			if (chr == '-') {
				i++;
				String a;
				while (i < s.GetCount()) {
					chr = s[i];
					if (!IsDigit(chr)) break;
					a.Cat(chr);
					i++;
				}
				integer = StrInt(a);
			}
			else if (IsDigit(chr)) {
				integer = chr - '0';
				i++;
			}
			else {
				OnError("Invalid character at " + IntStr(i) + " in '" + s + "'");
				return false;
			}
			if (mode == FROM)
				from = integer;
			else
				to = integer;
			mode++;
		}
		else if (mode == SIDE) {
			if (chr == 's') {
				side = true;
				i++;
			}
			mode++;
		}
		else if (mode == FINISH) {
			LinkItem& it = v.Add();
			it.from = from;
			it.to = to;
			it.side = side;
			side = false;
			mode = BEGINNING;
		}
	}
	if (mode == BEGINNING)
		;
	else if (mode == SIDE || mode == FINISH) {
		LinkItem& it = v.Add();
		it.from = from;
		it.to = to;
		it.side = side;
	}
	else {
		OnError("Unexpected end in '" + s + "'");
		return false;
	}
	
	return true;
}


NAMESPACE_EONGEN_END
