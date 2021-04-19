#include "EcsCore.h"

#if 0

NAMESPACE_OULU_BEGIN


void Frustum2::Initialize() {
	
	
	
}











void QuadtreeSystem::Update(float dt) {
	
	
	
}







QuadtreeComponent::QuadtreeComponent() {
	
}

void QuadtreeComponent::RealizeTree() {
	if (tree.IsEmpty()) {
		tree.Create();
		tree->Initialize(-6, +6);
	}
}

void QuadtreeComponent::Initialize() {
	
}

void QuadtreeComponent::Uninitialize() {
	
}

QuadtreeComponent& QuadtreeComponent::DrawLine(vec3 a, vec3 b, float width) {
	RealizeTree();
	
	if (width > 0.0f) {
		vec3 ab = b - a;
		float len = ab.GetLength();
		float step = width * 0.5f;
		vec3 p = a;
		vec3 vstep = ab * (step / len);
		int level = tree->GetScaleLevel(width);
		for (float f = 0; f <= len; f += step) {
			QuadtreeNode* n = tree->GetAddNode(p, level);
			if (n)
				n->SetDebugDraw(true);
			p += vstep;
		}
	}
	
	return *this;
}


NAMESPACE_OULU_END

#endif
