#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


void EngineSerializer::EtherizePool(Ether& e, DbgPool& p) {
	byte magic = 0, chk = 0xaf;
	
	if (e.IsLoading()) {
		e.GetT(magic);
		ASSERT(magic == chk);
		
		//p.Clear();
		
		int pc = 0, ec = 0;
		e.GetT(pc);
		e.GetT(ec);
		p.pools.SetCount(pc);
		p.ents.SetCount(ec);
		
		for (DbgPool& p0 : p.pools) {
			e.GetT(magic);
			ASSERT(magic == chk);
			p0.name = e.GetString();
			
			EtherizePool(e, p0);
			
			e.GetT(magic);
			ASSERT(magic == chk);
		}
		
		for (DbgEntity& o0 : p.ents) {
			e.GetT(magic);
			ASSERT(magic == chk);
			o0.name = e.GetString();
			
			EtherizeEntity(e, o0);
			
			e.GetT(magic);
			ASSERT(magic == chk);
		}
		
	}
	else {
		TODO
	}
}

void EngineSerializer::EtherizeEntity(Ether& e, DbgEntity& o) {
	byte magic = 0, chk = 0xA0;
	
	if (e.IsLoading()) {
		e.GetT(magic);
		ASSERT(magic == chk);
		
		int c = 0;
		e.GetT(c);
		o.comps.SetCount(c);
		for(DbgComponent& c : o.comps) {
			e.GetT(magic);
			ASSERT(magic == chk);
			
			c.cls_name = e.GetString();
			EtherizeComponent(e, c);
			
			e.GetT(magic);
			ASSERT(magic == chk);
		}
	}
	else {
		TODO
	}
}

void EngineSerializer::EtherizeComponent(Ether& e, DbgComponent& c) {
	c.Clear();
	while (!e.IsEof()) {
		byte more = 0;
		e.GetT(more);
		if (more) {
			Object& o = c.vars.Add();
			e % o;
		}
		else break;
	}
}

void EngineSerializer::Etherize(Ether& e) {
	EtherizePool(e, pool);
}


NAMESPACE_TOPSIDE_END
