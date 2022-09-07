#include "EcsCore.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN


void OctreeSystem::Update(double dt) {
	
	
	
}







OctreeComponent::OctreeComponent() {
	
}

void OctreeComponent::RealizeTree() {
	if (tree.IsEmpty()) {
		tree.Create();
		tree->Initialize(-6, +6);
	}
}

void OctreeComponent::Initialize() {
	
}

void OctreeComponent::Uninitialize() {
	
}

OctreeComponent& OctreeComponent::DrawLine(vec3 a, vec3 b, float width) {
	RealizeTree();
	
	if (width > 0.0f) {
		vec3 ab = b - a;
		float len = ab.GetLength();
		float step = width * 0.5;
		vec3 p = a;
		vec3 vstep = ab * (step / len);
		int level = tree->GetScaleLevel(width);
		for (float f = 0; f <= len; f += step) {
			OctreeNode* n = tree->GetAddNode(p, level);
			if (n)
				n->SetDebugDraw(true);
			p += vstep;
		}
	}
	
	return *this;
}


NAMESPACE_TOPSIDE_END

#endif
