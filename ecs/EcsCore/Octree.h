#ifndef _EcsCore_Octree_h_
#define _EcsCore_Octree_h_

#if 0

NAMESPACE_OULU_BEGIN




class OctreeSystem : public System<OctreeSystem> {
	
public:
	SYS_CTOR()
	
	void Update(double dt) override;
	
	
	float GetHumanLength() {return 1.0 + 3.0 / 4.0;} // 1.75m goes to grid nicely
	
};




class OctreeComponent : public Component<OctreeComponent> {
	One<Octree> tree;
	
	
	void RealizeTree();
	
public:
	using Component::Component;
	
	OctreeComponent();
	
	void operator=(const OctreeComponent&) {}
	
	void Initialize() override;
	void Uninitialize() override;
	
	
	OctreeComponent& DrawLine(vec3 a, vec3 b, float width);
	
};


NAMESPACE_OULU_END

#endif
#endif
