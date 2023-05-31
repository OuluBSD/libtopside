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
	
	if (c.cls_name == "transform3") {
		TODO
	}
	else if (c.cls_name == "transform2") {
		TODO
	}
	else if (c.cls_name == "viewable") {
		TODO
	}
	else if (c.cls_name == "viewport") {
		TODO
	}
	else if (c.cls_name == "camera.chase") {
		TODO
	}
	else if (c.cls_name == "renderable") {
		TODO
	}
	else if (c.cls_name == "model") {
		TODO
	}
	else if (c.cls_name == "gui.app") {
		TODO
	}
	else if (c.cls_name == "body") {
		TODO
	}
	else if (c.cls_name == "text") {
		TODO
	}
	else if (c.cls_name == "easing") {
		TODO
	}
	else if (c.cls_name == "physics") {
		TODO
	}
	else if (c.cls_name == "tool") {
		TODO
	}
	else if (c.cls_name == "tool.selector") {
		TODO
	}
	else if (c.cls_name == "player.hand") {
		TODO
	}
	else if (c.cls_name == "player.head") {
		TODO
	}
	else if (c.cls_name == "player.body") {
		TODO
	}
	else if (c.cls_name == "paint.stroke") {
		TODO
	}
	else if (c.cls_name == "paint") {
		TODO
	}
	else {
		LOG("Not implemented: " << c.cls_name);
		TODO
	}
	
}

void EngineSerializer::Etherize(Ether& e) {
	EtherizePool(e, pool);
}


NAMESPACE_TOPSIDE_END
