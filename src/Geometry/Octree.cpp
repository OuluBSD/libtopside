#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN


OctreeObject::OctreeObject() {
	
}

void OctreeObject::SetPosition(const vec3& pos) {
	if (owner->Contains(pos)) {
		vec3 p = owner->GetPosition();
		rel_pos = pos - p;
	}
	else {
		Octree& otree = owner->GetOctree();
		OctreeNode* new_owner = otree.GetAddNode(pos, owner->level);
		//ASSERT(new_owner);
		if (new_owner) {
			owner->Detach(this);
			new_owner->Attach(this);
			owner = new_owner;
		}
	}
}

vec3 OctreeObject::GetPosition() const {
	vec3 p = owner->GetPosition() + rel_pos;
	return p;
}

	
	
	
	
	
	
	
	
	
	
void OctreeNode::Clear() {
	for(int i = 0; i < 8; i++) {
		if (branch[i]) {
			OctreeNode* n = branch[i];
			branch[i] = 0;
			GetRecyclerPool().Return(n);
		}
	}
	flags = 0;
	level = 0;
}

bool OctreeNode::Contains(const vec3& v) const {
	vec3 size = GetSize();
	vec3 p = GetPosition();
	
	bool b = true;
	for(int i = 0; i < 3; i++)
		b = b && (p[i] <= v[i] && v[i] <= p[i] + size[i]);
	
	return b;
}

vec3 OctreeNode::GetSize() const {
	float step = FastPow<float>(2.f, (float)level);
	return vec3(step, step, step);
}

float OctreeNode::GetStep() const {
	float step = FastPow<float>(2.f, (float)level);
	return step;
}

vec3 OctreeNode::GetPosition() const {
	return position;
}

AABB OctreeNode::GetAABB() const {
	vec3 first_corner = GetPosition();
	vec3 full_size = GetSize();
	AABB aabb;
	aabb.size = full_size * 0.5;
	aabb.position = first_corner + aabb.size;
	return aabb;
}

Octree& OctreeNode::GetOctree() const {
	return *otree;
}

void OctreeNode::Attach(OctreeObject* o) {
	objs.Add() = o;
}

void OctreeNode::Detach(OctreeObject* o) {
	for (auto it = objs.Begin(); it; ++it) {
		if (&**it == o) {
			it->Detach();
			objs.Remove(it);
			break;
		}
	}
}


	
	
	
	
	
	
	
	


Octree::Octree() {
	root.otree = this;
}

int Octree::LimitLevel(int level) const {
	level = std::min(max_scale_level, std::max(min_scale_level, level));
	return level;
}

void Octree::Initialize(int min_scale_level, int max_scale_level) {
	ASSERT(min_scale_level <= 0);
	ASSERT(max_scale_level >= 0);
	this->min_scale_level = std::min(min_scale_level, 0);
	this->max_scale_level = std::max(max_scale_level, 0);
	this->scale_count = this->max_scale_level - this->min_scale_level + 1;
	
	root.Clear();
	root.level = this->max_scale_level;
	
	max_len = FastPow<float>(2.0f, (float)this->max_scale_level);
	max_off = max_len / 2;
	root.position = vec3(-max_off, -max_off, -max_off);
	
	levels.SetCount(scale_count);
	for(int i = 0; i < scale_count; i++) {
		Level& level = levels[i];
		level.step = FastPow<float>(2.f, (float)(this->min_scale_level + i));
		level.steps = 1 << (scale_count - 1 - i);
	}
	
}

int Octree::GetScaleLevel(float len) const {
	float a = logf_fast(len);
	int level = (int)(a / (float)M_LN2 + (a >= 0.0f ? +0.5f : -0.5f));
	level = LimitLevel(level);
	return level;
}

OctreeNode* Octree::GetAddNode(vec3 pos, int level) {
	ASSERT_(min_scale_level < 0 || max_scale_level > 0, "Initialize octree first");
	
	if (level < min_scale_level ||
		level > max_scale_level ||
		!Contains(pos))
		return NULL;
	
	uint64 seek = GetSeekBits(pos, level);
	
	OctreeNode* n = &root;
	while (n->level != level) {
		byte branch_i = seek & 7ULL;
		seek >>= 3ULL;
		OctreeNode*& bn = n->branch[branch_i];
		if (!bn) {
			bn = OctreeNode::GetRecyclerPool().New();
			bn->otree = this;
			bn->parent = n;
			bn->level = n->level - 1;
			
			vec3 npos = n->GetPosition();
			float s = bn->GetStep();
			switch (branch_i) {
				case OctreeNode::BR_LBI: bn->position = npos + vec3(0, 0, 0); break;
				case OctreeNode::BR_RBI: bn->position = npos + vec3(s, 0, 0); break;
				case OctreeNode::BR_LTI: bn->position = npos + vec3(0, s, 0); break;
				case OctreeNode::BR_RTI: bn->position = npos + vec3(s, s, 0); break;
				case OctreeNode::BR_LBO: bn->position = npos + vec3(0, 0, s); break;
				case OctreeNode::BR_RBO: bn->position = npos + vec3(s, 0, s); break;
				case OctreeNode::BR_LTO: bn->position = npos + vec3(0, s, s); break;
				case OctreeNode::BR_RTO: bn->position = npos + vec3(s, s, s); break;
				default: break;
			}
			
		}
		ASSERT(bn->Contains(pos));
		n = bn;
	}
	return n;
}

bool Octree::Contains(vec3 pos) {
	return	-max_off <= pos[0] && pos[0] < max_off &&
			-max_off <= pos[1] && pos[1] < max_off &&
			-max_off <= pos[2] && pos[2] < max_off;
}

uint64 Octree::GetSeekBits(vec3 pos, int level) const {
	if (level >= max_scale_level)
		return 0;
	
	//vec3 neg_pt {-max_off, -max_off, -max_off};
	ASSERT(levels.GetCount());
	
	int level_i = level - min_scale_level;
	int level_i_max = max_scale_level - min_scale_level;
	int rev_level_i = level_i_max - level_i;
	const Level& l = levels[level_i];
	ivec3 ipos;
	for(int i = 0; i < 3; i++)
		ipos[i] = (int)(((double)pos[i] + (double)max_off) / (double)l.step);
	
	for(int i = 0; i < 3; i++) {ASSERT(ipos[i] >= 0 && ipos[i] < l.steps);}
	
	uint64 seek = 0, j = 0;
	for(int shift = rev_level_i - 1; shift >= 0; shift--) {
		uint32 mask = 1UL << shift;
		for(int i = 0; i < 3; i++)
			if (ipos[i] & mask)
				seek |= 1ULL << (j + i);
		j += 3;
	}
	return seek;
}

OctreeFrustumIterator Octree::GetFrustumIterator(const Frustum& f) {
	return GetIterator<Frustum>(f);
}

OctreeSphereIterator Octree::GetSphereIterator(const vec3& center, float radius) {
	return GetIterator<Sphere>(Sphere(center, radius));
}

OctreeSphereCollection Octree::GetSphereCollection(const vec3& center, float radius) {
	return OctreeSphereCollection {GetSphereIterator(center, radius)};
}





bool OctreeIterator::Next() {
	if (!level && pos[0] == 9)
		return false;
	
	while (1) {
		ASSERT(level >= 0);
		
		{
			OctreeNode* a = addr[level];
			int& p = pos[level];
			p++;
			
			if (p == 0)
				; // pass
			else if (p == 9) {
				if (!level)
					break;
				level--;
				continue;
			}
			else {
				ASSERT(p >= 1 && p <= 8);
				addr[level+1] = a->At(p-1);
				if (addr[level+1]) {
					pos[level+1] = -1;
					level++;
				}
				continue;
			}
		}
		
		return true;
	}
	
	return false;
}

OctreeIterator::operator bool() const {
	return !(!level && pos[0] == 9);
}

OctreeNode& OctreeIterator::operator*() {
	return *addr[level];
}

OctreeNode* OctreeIterator::operator->() {
	return addr[level];
}



















NAMESPACE_TOPSIDE_END
