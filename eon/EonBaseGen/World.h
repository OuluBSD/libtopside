#ifndef _EonBaseGen_World_h_
#define _EonBaseGen_World_h_

NAMESPACE_EONGEN_BEGIN


class World {
	struct LinkItem : Moveable<LinkItem> {
		int from;
		int to;
		bool side;
	};
	
	ArrayMap<String, Unit>			units;
	ArrayMap<String, Node>			nodes;
	Array<Link>						links;
	
	void OnError(String msg);
	
	bool ParseValDev(String s, ValDevCls& vd, byte& count);
	bool ParseValDevSide(String s, Unit& u);
	bool SolveLinks(String s, Vector<LinkItem>& v);
	bool IsConnectedToId0(Unit& u);
	
public:
	typedef World CLASSNAME;
	World();
	
	
	bool LoadJSON(String json);
	bool LoadBases(ObjectMap& m);
	bool LoadHeaders(ObjectMap& m);
	bool LoadLoops(ObjectMap& m);
	bool LoadNodeLinks(ObjectMap& m);
	bool LoadChains(ObjectMap& m);
	bool LoadTopChains(ObjectMap& m);
	bool LoadMachines(ObjectMap& m);
	bool LoadSystems(ObjectMap& m);
	bool LoadBase(String key, ObjectMap& m);
	bool LoadHeader(String key, ObjectMap& m);
	bool LoadLoop(String key, ObjectMap& m);
	bool LoadNodeLink(String key, ObjectMap& m);
	bool LoadChain(String key, ObjectMap& m);
	bool LoadTopChain(String key, ObjectMap& m);
	bool LoadMachine(String key, ObjectMap& m);
	bool LoadSystem(String key, ObjectMap& m);
	
	bool TraverseUnits(Unit::Type type);
	bool TraverseLoops();
	
};


NAMESPACE_EONGEN_END

#endif
