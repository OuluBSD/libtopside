#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


void EngineSerializer::EtherizePool(Ether& e, DbgPool& p) {
	byte magic = 0, chk = 0xaf;
	int dbg_i = 0;
	
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
			dbg_i++;
		}
		
		dbg_i = 0;
		for (DbgEntity& o0 : p.ents) {
			e.GetT(magic);
			ASSERT(magic == chk);
			o0.name = e.GetString();
			
			EtherizeEntity(e, o0);
			
			e.GetT(magic);
			ASSERT(magic == chk);
			dbg_i++;
		}
		
	}
	else {
		TODO
	}
}

void EngineSerializer::EtherizeEntity(Ether& e, DbgEntity& o) {
	byte magic = 0, chk = 0xA0;
	int dbg_i = 0;
	
	if (e.IsLoading()) {
		e.GetT(magic);
		ASSERT(magic == chk);
		
		int c = 0;
		e.GetT(c);
		o.comps.SetCount(c);
		for(DbgComponent& c : o.comps) {
			e.GetT(magic);
			ASSERT(magic == chk);
			
			c.Clear();
			c.cls_name = e.GetString();
			EtherizeComponent(e, c);
			
			e.GetT(magic);
			ASSERT(magic == chk);
			
			dbg_i++;
		}
		
		e.GetT(magic);
		ASSERT(magic == chk);
	}
	else {
		TODO
	}
}

void EngineSerializer::EtherizeComponent(Ether& e, DbgComponent& c) {
	int dbg_i = 0;
	while (!e.IsEof()) {
		dword obj_type = 0;
		e.GetT(obj_type);
		if (!obj_type)
			break;
		
		bool is_ref = obj_type & (1ULL << 31);
		obj_type &= ~(1ULL << 31);
		
		byte key_len = 0;
		e.GetT(key_len);
		char key[256];
		e.Get(key, key_len);
		key[key_len] = 0;
		String key_str(key, key_len);
		
		if (is_ref) {
			DbgComponent::RefLink& link = c.refs.Add();
			link.type = obj_type;
			
			bool has_ref_value = false;
			e.GetT(has_ref_value);
			
			if (has_ref_value) {
				e % link.path;
			}
		}
		else {
			Object& o = c.vars.Add(key_str);
			if (o.CreateType(obj_type)) {
				o.GetObjectA()->Etherize(e);
			}
			else {
				LOG("EngineSerializer::EtherizeComponent: error: could not create type " << IntStr64(obj_type));
				break;
			}
		}
		
		byte chk = 0;
		e.GetT(chk);
		ASSERT(chk == 0xFF);
		
		dbg_i++;
	}
}

void EngineSerializer::Etherize(Ether& e) {
	if (e.IsLoading())
		lock.EnterWrite();
	else
		lock.EnterRead();
	
	EtherizePool(e, pool);
	
	if (e.IsLoading())
		lock.LeaveWrite();
	else
		lock.LeaveRead();
}


NAMESPACE_TOPSIDE_END
