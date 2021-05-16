#ifndef _EcsCore_Overlap_h_
#define _EcsCore_Overlap_h_


NAMESPACE_TOPSIDE_BEGIN



class OverlapSystem : public System<OverlapSystem> {
	LinkedList<OverlapRef> conns;
	
	void Visit(RuntimeVisitor& vis) override {
		vis && conns;
	}
public:
	SYS_CTOR(OverlapSystem)
	
	void Add(OverlapRef conn) {conns.FindAdd(conn);}
	void Remove(OverlapRef conn) {conns.RemoveKey(conn);}
	
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
	VIS_COMP_0_1(Overlap)
	
	
	
public:
	using Component::Component;
	
	IFACE_GENERIC;
	IFACE_CB(OverlapSink);
	
	Overlap();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	void operator=(const Overlap& c) {}
	
	
};


class OverlapDetector :
	public Component<OverlapDetector>,
	public OverlapSource
{
	VIS_COMP_1_0(Overlap)
	
	
public:
	using Component::Component;
	
	IFACE_GENERIC;
	IFACE_CB(OverlapSource);
	
	OverlapDetector();
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	void operator=(const OverlapDetector& c) {}
	
	
};



void CreateOctreeEntityFromString(PoolRef octree_root, String map_str, const ArrayMap<int, EntityRef>& map_char_ents);



PREFAB_BEGIN(DefaultOctreeNode)
	OverlapDetector
PREFAB_END

NAMESPACE_TOPSIDE_END


#endif
