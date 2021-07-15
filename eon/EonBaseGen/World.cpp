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
		else if (key == "machines") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadMachines(sub.GetMap()))
				return false;
		}
		else if (key == "systems") {
			if (!sub.IsMap()) {
				OnError("Expected map");
				return false;
			}
			
			if (!LoadSystems(sub.GetMap()))
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

bool World::LoadMachines(ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (!sub.IsMap()) {
			OnError("Expected map");
			return false;
		}
		
		if (!LoadMachine(key, sub.GetMap()))
			return false;
	}
	
	return true;
}

bool World::LoadSystems(ObjectMap& m) {
	//LOG(GetObjectTreeString(m));
	
	for(int i = 0; i < m.GetCount(); i++) {
		Object& sub = m[i];
		String key = m.GetKey(i);
		
		if (!sub.IsMap()) {
			OnError("Expected map");
			return false;
		}
		
		if (!LoadSystem(key, sub.GetMap()))
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
	
	uint16 id = units.GetCount();
	Unit& unit = units.Add(key);
	unit.id = id;
	unit.smallest_link_id = id;
	unit.type = Unit::BASE;
	unit.key = key;
	
	if (!ParseValDev(sink->Get<String>(), unit.sink, unit.sink_count)) return false;
	if (!ParseValDev(src->Get<String>(),  unit.src, unit.src_count)) return false;
	if (!ParseValDevSide(side->Get<String>(), unit)) return false;
	
	
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
	
	uint16 id = units.GetCount();
	Unit& unit = units.Add(key);
	unit.id = id;
	unit.smallest_link_id = id;
	unit.key = key;
	unit.type = Unit::HEADER;
	
	String base_str = base->Get<String>();
	
	i = units.Find(base_str);
	if (i < 0) {
		OnError("Base unit '" + key + "' does not exist");
		return false;
	}
	
	Unit& base_unit = units[i];
	
	unit.CopyType(base_unit);
	
	Link& link = links.Add();
	link.type = Link::BASE_UNIT;
	link.from_unit = &unit;
	link.to_unit = &base_unit;
	
	unit.links.Add(&link);
	base_unit.links.Add(&link);
	
	return true;
}

bool World::LoadLoop(String key, ObjectMap& m) {
	
	if (this->nodes.Find(key) >= 0) {
		OnError("Node '" + key + "' already exists");
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
		int j = units.Find(header_key);
		if (j < 0) {
			OnError("Header unit '" + header_key + "' does not exist");
			return false;
		}
		
		Unit& header_unit = units[j];
		if (header_unit.type != Unit::HEADER) {
			OnError("Type of the unit '" + header_key + "' is not HEADER");
			return false;
		}
		
		header_ptrs.Add(&header_unit);
	}
	
	Node& node = nodes.Add(key);
	node.key = key;
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
	
	if (this->nodes.Find(key) >= 0) {
		OnError("Node '" + key + "' already exists");
		return false;
	}
	
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
	node.key = key;
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
	
	if (this->nodes.Find(key) >= 0) {
		OnError("Node '" + key + "' already exists");
		return false;
	}
	
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
	node.key = key;
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
	
	if (this->nodes.Find(key) >= 0) {
		OnError("Node '" + key + "' already exists");
		return false;
	}
	
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
	node.key = key;
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

bool World::LoadMachine(String key, ObjectMap& m) {
	//DUMP(key) LOG(GetObjectTreeString(m));
	
	Object* m_topchains = m.TryFind("topchains");
	Object* m_links = m.TryFind("links");
	if (!m_topchains || !m_topchains->IsArray()) {OnError("Base '" + key + "' is missing topchains array"); return false;}
	if (!m_links || !m_links->IsString()) {OnError("Base '" + key + "' is missing links string"); return false;}
	ObjectArray& topchains = m_topchains->GetArray();
	String links_str = m_links->Get<String>();
	
	Vector<Node*> loop_ptrs;
	for(int i = 0; i < topchains.GetCount(); i++) {
		Object& a_loop = topchains[i];
		if (!a_loop.IsString()) {
			OnError("Expected string in topchains array");
			return false;
		}
		
		String loop_key = a_loop.Get<String>();
		int j = this->nodes.Find(loop_key);
		if (j < 0) {
			OnError("Header unit '" + loop_key + "' does not exist");
			return false;
		}
		
		Node& loop_node = this->nodes[j];
		if (loop_node.type != Node::TOPCHAIN &&
			loop_node.type != Node::CHAIN) {
			OnError("Type of the node '" + loop_key + "' is not TOPCHAIN or CHAIN");
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
	node.key = key;
	node.type = Node::MACHINE;
	
	for (Node* loop : loop_ptrs) {
		Link& link = links.Add();
		link.type = Link::MACHINE_TOPCHAIN;
		link.from_node = &node;
		link.to_node = loop;
		
		node.links.Add(&link);
		loop->links.Add(&link);
	}
	
	for (LinkItem& li : str_links) {
		Link& link = links.Add();
		link.type = Link::MACHINE_TOPCHAIN;
		link.from_node = loop_ptrs[li.from];
		link.to_node = loop_ptrs[li.to];
		
		link.from_node->links.Add(&link);
		link.to_node->links.Add(&link);
	}
	
	return true;
}

bool World::LoadSystem(String key, ObjectMap& m) {
	//DUMP(key) LOG(GetObjectTreeString(m));
	
	String cmp = "machines";
	Object* m_machines = m.TryFind(cmp);
	Object* m_links = m.TryFind("links");
	if (!m_machines || !m_machines->IsArray()) {OnError("Base '" + key + "' is missing machines array"); return false;}
	if (!m_links || !m_links->IsString()) {OnError("Base '" + key + "' is missing links string"); return false;}
	ObjectArray& machines = m_machines->GetArray();
	String links_str = m_links->Get<String>();
	
	Vector<Node*> loop_ptrs;
	for(int i = 0; i < machines.GetCount(); i++) {
		Object& a_loop = machines[i];
		if (!a_loop.IsString()) {
			OnError("Expected string in machines array");
			return false;
		}
		
		String loop_key = a_loop.Get<String>();
		int j = this->nodes.Find(loop_key);
		if (j < 0) {
			OnError("Header unit '" + loop_key + "' does not exist");
			return false;
		}
		
		Node& loop_node = this->nodes[j];
		if (loop_node.type != Node::MACHINE) {
			OnError("Type of the node '" + loop_key + "' is not MACHINE");
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
	node.key = key;
	node.type = Node::MACHINE;
	
	for (Node* loop : loop_ptrs) {
		Link& link = links.Add();
		link.type = Link::SYSTEM_MACHINE;
		link.from_node = &node;
		link.to_node = loop;
		
		node.links.Add(&link);
		loop->links.Add(&link);
	}
	
	for (LinkItem& li : str_links) {
		Link& link = links.Add();
		link.type = Link::MACHINE_TOPCHAIN;
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

bool World::ParseValDevSide(String s, Unit& u) {
	if (s.IsEmpty()) {
		u.accept_side = false;
		return true;
	}
	
	CParser p(s);
	if (p.Id("src")) {
		u.accept_side = true;
		u.side_src = true;
	}
	else if (p.Id("sink")) {
		u.accept_side = true;
		u.side_src = false;
	}
	else {
		OnError("Unexpected side string '" + s + "'");
		return false;
	}
	
	if (!p.Char('-')) {
		OnError("Expected '-' in side string '" + s + "'");
		return false;
	}
	
	int col = p.GetCharPos();
	return ParseValDev(s.Mid(col), u.side, u.side_count);
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

bool World::TraverseUnits(Unit::Type type) {
	
	for (Unit& unit0 : units.GetValues()) {
		if (unit0.type != type)
			continue;
		
		bool any_connected = false;
		
		for (Unit& unit1 : units.GetValues()) {
			if (&unit0 == &unit1 || unit1.type != type)
				continue;
			
			DevCls match_dev0 = unit1.side_src ? unit0.sink.dev : unit0.src.dev;
			DevCls match_dev1 = unit0.side_src ? unit1.sink.dev : unit1.src.dev;
			
			/*if (unit0.key == "center_accel_order_side" &&
				unit1.key == "accel_order_src") {
				LOG("");
			}*/
			
			bool less = unit0.id < unit1.id;
			bool is_series = unit0.src == unit1.sink && (unit0.src != unit0.sink || less);
			bool is_parallel =
				unit0.accept_side &&
				unit1.accept_side &&
				unit0.side.val == unit1.side.val &&
				match_dev0 == unit1.side.dev &&
				match_dev1 == unit0.side.dev &&
				unit0.side_src != unit1.side_src &&
				less;
			if (is_series || is_parallel) {
				Link& link = links.Add();
				link.from_unit = &unit0;
				link.to_unit = &unit1;
				if (is_series)
					link.type = Link::BASE_SRC_TO_SINK;
				else
					link.type = Link::BASE_SIDE_TO_SIDE;
				
				unit0.links.Add(&link);
				unit1.links.Add(&link);
				
				unit0.smallest_link_id = min(unit0.smallest_link_id, unit1.id);
				unit1.smallest_link_id = min(unit1.smallest_link_id, unit0.id);
				
				any_connected = true;
			}
		}
		
		if (!any_connected) {
			for (Link* l : unit0.links) {
				if (l->type == Link::BASE_SRC_TO_SINK ||
					l->type == Link::BASE_SIDE_TO_SIDE) {
					any_connected = true;
					break;
				}
			}
			
			if (!any_connected) {
				OnError("Unit '" + unit0.key + "' cannot connect any other unit");
				return false;
			}
		}
		
		LOG("Unit '" + unit0.key + "' is ok");
	}
	
	for (Unit& unit0 : units.GetValues()) {
		if (unit0.type != type)
			continue;
		
		if (!IsConnectedToId0(unit0)) {
			LOG("Unit '" + unit0.key + "' is not connected to first unit");
		}
	}
	
	int dbg_i = 0;
	for (Unit& unit0 : units.GetValues()) {
		if (unit0.type != type)
			continue;
		
		LOG(dbg_i++ << ": " << unit0.key);
		int dbg_j = 0;
		for (Link* link : unit0.links) {
			if (link->type == Link::BASE_SRC_TO_SINK) {
				Unit* linked = link->from_unit == &unit0 ? link->to_unit : link->from_unit;
				LOG("\t" << dbg_j++ << ": serial " << linked->key);
			}
			else if (link->type == Link::BASE_SIDE_TO_SIDE) {
				Unit* linked = link->from_unit == &unit0 ? link->to_unit : link->from_unit;
				LOG("\t" << dbg_j++ << ": parallel " << linked->key);
			}
		}
	}
	
	return true;
}

bool World::IsConnectedToId0(Unit& u) {
	Unit::Type type = u.type;
	
	uint16 id = u.id;
	Unit* cur = &u;
	while (cur) {
		Unit* next = 0;
		for (Link* link : cur->links) {
			if (link->type == Link::BASE_SRC_TO_SINK ||
				link->type == Link::BASE_SIDE_TO_SIDE) {
				Unit* linked = link->from_unit == cur ? link->to_unit : link->from_unit;
				ASSERT(linked->type == type);
				if (linked->smallest_link_id < id) {
					next = linked;
					id = linked->smallest_link_id;
				}
			}
		}
		if (!next)
			break;
		cur = next;
	}
	
	uint16 first_id = 0xffff;
	for (Unit& unit0 : units.GetValues()) {
		if (unit0.type != type)
			continue;
		first_id = unit0.id;
		break;
	}
	ASSERT(first_id != 0xffff);
	
	return id == first_id;
}

bool World::TraverseLoops() {
	
	int dbg_i = 0;
	for (Node& node0 : nodes.GetValues()) {
		if (node0.type != Node::LOOP)
			continue;
		
		LOG(dbg_i++ << ": " << node0.key);
		
		int dbg_j = 0;
		for (Link* link : node0.links) {
			if (link->type != Link::LOOP_UNIT)
				continue;
			
			Unit* linked = link->to_unit;
			
			LOG("\t" << dbg_j++ << ": " << linked->key);
			
		}
	}
	
	return true;
}

NAMESPACE_EONGEN_END
