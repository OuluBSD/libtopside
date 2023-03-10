#include "ProtoVM.h"


ElectricNodeBase::ElectricNodeBase() {
	
}

void ElectricNodeBase::Clear() {
	conns.Clear();
	sink_count = 0;
	src_count = 0;
	bi_count = 0;
}

ElectricNodeBase& ElectricNodeBase::operator>>(ElectricNodeBase& b) {
	pcb->Attach(*this, b);
	return b;
}

ElectricNodeBase& ElectricNodeBase::operator[](String code) {
	int a;
	if ((a = code.Find(",")) >= 0) {
		String range_str = code.Mid(a+1);
		code = code.Left(a);
		if (range_str.Left(1) == "-")
			TODO;
		
		int range = StrInt(range_str);
		
		int i = 0;
		for (Connector& c : conns) {
			if (c.name == code) {
				
				// create reference node to pcb
				return pcb->AddReferenceRange(*this, i, range);
			}
			i++;
		}
	}
	else {
		int i = 0;
		for (Connector& c : conns) {
			if (c.name == code) {
				
				// create reference node to pcb
				return pcb->AddReferenceSingle(*this, i);
			}
			i++;
		}
	}
	THROW(Exc("did not find pin " + code + " in " + GetDynamicName()));
}

ElectricNodeBase& ElectricNodeBase::NotRequired(String code) {
	int a;
	if ((a = code.Find(",")) >= 0) {
		String range_str = code.Mid(a+1);
		code = code.Left(a);
		int range = StrInt(range_str);
		
		int i = 0;
		for (Connector& c : conns) {
			if (c.name == code) {
				if (i+range > conns.GetCount())
					THROW(Exc("range exceeds pin count"));
				for(int j = 0; j < range; j++)
					conns[i+j].SetRequired(false);
				return *this;
			}
			i++;
		}
	}
	else {
		int i = 0;
		for (Connector& c : conns) {
			if (c.name == code) {
				c.SetRequired(false);
				return *this;
			}
			i++;
		}
	}
	THROW(Exc("did not find pin " + code + " in " + GetDynamicName()));
}

ElectricNodeBase& ElectricNodeBase::operator[](int i) {
	if (i >= 0 && i < conns.GetCount())
		return pcb->AddReferenceSingle(*this, i);
	
	THROW(Exc("invalid pin index " + IntStr(i)));
}

bool ElectricNodeBase::IsEmpty() const {
	if (type == V_PARTIAL || type == V_PARTIAL_RANGE)
		return false;
	
	return conns.IsEmpty();
}

bool ElectricNodeBase::IsTrivialSourceDefaultRange() const {
	if (type == V_PARTIAL_RANGE) {
		int a = ptr_i;
		int b = ptr_i + ptr_n;
		for(int i = a; i < b; i++)
			if (!ptr->conns[i].is_src)
				return false;
		return ptr_n > 0;
	}
	
	if (type == V_PARTIAL)
		return ptr_conn->is_src;
	
	for (Connector& c : conns)
		if (!c.is_src)
			return false;
		
	return conns.GetCount();
}

bool ElectricNodeBase::IsTrivialSinkDefaultRange() const {
	if (type == V_PARTIAL_RANGE) {
		int a = ptr_i;
		int b = ptr_i + ptr_n;
		for(int i = a; i < b; i++)
			if (!ptr->conns[i].is_sink)
				return false;
		return ptr_n > 0;
	}
	
	if (type == V_PARTIAL)
		return ptr_conn->is_sink;
	
	for (Connector& c : conns)
		if (!c.is_sink)
			return false;
		
	return conns.GetCount();
}

bool ElectricNodeBase::IsTrivialSourceDefault() const {
	if (type == V_PARTIAL_RANGE)
		return false;
	
	if (type == V_PARTIAL)
		return ptr_conn->is_src;
	
	return (bi_count + src_count) == 1;
}

bool ElectricNodeBase::IsTrivialSinkDefault() const {
	if (type == V_PARTIAL_RANGE)
		return false;
	
	if (type == V_PARTIAL)
		return ptr_conn->is_sink;
	
	return (bi_count + sink_count) == 1;
}

int ElectricNodeBase::GetPinWidth() const {
	if (type == V_PARTIAL_RANGE)
		return ptr_n;
	
	if (type == V_PARTIAL)
		return 1;
	
	return conns.GetCount();
}

ElectricNodeBase& ElectricNodeBase::SetName(String s) {
	name = s;
	return *this;
}

ElectricNodeBase::Connector& ElectricNodeBase::Get(int i) {
	if (type == V_PARTIAL_RANGE) {
		ASSERT(i >= 0 && i < ptr_n);
		return ptr->conns[ptr_i + i];
	}
	
	if (type == V_PARTIAL) {
		ASSERT(i == 0);
		return ptr->conns[ptr_i];
	}
	
	return conns[i];
}

ElectricNodeBase::Connector& ElectricNodeBase::GetTrivialSource() {
	ASSERT(IsTrivialSourceDefault());
	if (type == V_PARTIAL) {
		ASSERT(ptr_conn && ptr_conn->is_src);
		return *ptr_conn;
	}
	if (type == V_PARTIAL_RANGE) {
		TODO
	}
	for (Connector& c : conns)
		if (c.is_src)
			return c;
	Panic("internal error");
	NEVER();
}

ElectricNodeBase::Connector& ElectricNodeBase::GetTrivialSink() {
	ASSERT(IsTrivialSinkDefault());
	if (type == V_PARTIAL) {
		ASSERT(ptr_conn && ptr_conn->is_sink);
		return *ptr_conn;
	}
	for (Connector& c : conns)
		if (c.is_sink)
			return c;
	Panic("internal error");
	NEVER();
}

ElectricNodeBase::Connector& ElectricNodeBase::AddBidirectional(String name) {
	Connector& conn = conns.Add();
	conn.id = conns.GetCount()-1;
	conn.base = this;
	conn.name = name;
	conn.is_sink = conn.is_src = true;
	bi_count++;
	return conn;
}

ElectricNodeBase::Connector& ElectricNodeBase::AddSource(String name) {
	Connector& conn = conns.Add();
	conn.id = conns.GetCount()-1;
	conn.base = this;
	conn.name = name;
	conn.is_src = true;
	src_count++;
	return conn;
}

ElectricNodeBase::Connector& ElectricNodeBase::AddSink(String name) {
	Connector& conn = conns.Add();
	conn.id = conns.GetCount()-1;
	conn.base = this;
	conn.name = name;
	conn.is_sink = true;
	sink_count++;
	return conn;
}
















ElectricNode::ElectricNode() {
	AddBidirectional("A").SetMultiConn();
}


