#ifndef _EonBaseGen_World_h_
#define _EonBaseGen_World_h_

NAMESPACE_EONGEN_BEGIN


class World {
	ArrayMap<String, Unit>				units;
	ArrayMap<String, UnitNode>			nodes;
	Array<UnitLink>						unit_links;
	
	void OnError(String msg);
	
	bool ParseValDev(String s, ValDevCls& vd);
	
public:
	typedef World CLASSNAME;
	World();
	
	
	bool LoadJSON(String json);
	bool LoadBases(ObjectMap& m);
	bool LoadHeaders(ObjectMap& m);
	bool LoadBase(String key, ObjectMap& m);
	
};


NAMESPACE_EONGEN_END

#endif
