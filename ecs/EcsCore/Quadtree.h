#ifndef _EcsCore_Quadtree_h_
#define _EcsCore_Quadtree_h_

#if 0

NAMESPACE_OULU_BEGIN



class Frustum2 : public Component<Frustum2> {
	Frustum2Rect f;
	
public:
	using Component::Component;
	
	void operator=(const Frustum2&) {}
	
	void Initialize() override;
	
};


class QuadtreeSystem : public System<QuadtreeSystem> {
	
public:
	using System::System;
	
	void Update(double dt) override;
	
	
	float GetHumanLength() {return 1.0 + 3.0 / 4.0;} // 1.75m goes to grid nicely
	
};




class QuadtreeComponent : public Component<QuadtreeComponent> {
	One<Quadtree> tree;
	
	
	void RealizeTree();
	
public:
	using Component::Component;
	
	QuadtreeComponent();
	
	void operator=(const QuadtreeComponent&) {}
	
	void Initialize() override;
	void Uninitialize() override;
	
	
	QuadtreeComponent& DrawLine(vec3 a, vec3 b, float width);
	
};


NAMESPACE_OULU_END


#endif
#endif
