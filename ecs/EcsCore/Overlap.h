#ifndef _EcsCore_Overlap_h_
#define _EcsCore_Overlap_h_


NAMESPACE_OULU_BEGIN


class Overlap;

class OverlapSystem : public System<OverlapSystem> {
	Vector<Overlap*> conns;
	
public:
	using System::System;
	
	void Add(Overlap* conn) {VectorFindAdd(conns, conn);}
	void Remove(Overlap* conn) {VectorRemoveKey(conns, conn);}
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
	
};


class Overlap :
	public Component<Overlap>,
	public OverlapSink
{
	
	
public:
	using Component::Component;
	
	IFACE_GENERIC;
	IFACE_CB(OverlapSink);
	
	Overlap();
	
	void Initialize() override;
	void Uninitialize() override;
	
	void operator=(const Overlap& c) {}
	
	
};


class OverlapDetector :
	public Component<OverlapDetector>,
	public OverlapSource
{
	
	
public:
	using Component::Component;
	
	IFACE_GENERIC;
	IFACE_CB(OverlapSource);
	
	OverlapDetector();
	
	void Initialize() override;
	void Uninitialize() override;
	
	void operator=(const OverlapDetector& c) {}
	
	
};



void CreateOctreeEntityFromString(EntityPoolRef octree_root, String map_str, const ArrayMap<int, EntityRef>& map_char_ents);



PREFAB_BEGIN(DefaultOctreeNode)
	OverlapDetector
PREFAB_END

NAMESPACE_OULU_END


#endif
