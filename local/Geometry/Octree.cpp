#include "Geometry.h"


NAMESPACE_OULU_BEGIN


OctreeNodePool::OctreeNodePool() {
	recycle.Reserve(10000);
}

OctreeNode* OctreeNodePool::New() {
	if (recycle.IsEmpty())
		return new OctreeNode();
	
	lock.Enter();
	OctreeNode* n = recycle.Pop();
	lock.Leave();
	
	return n;
}

void OctreeNodePool::Delete(OctreeNode* n) {
	lock.Enter();
	recycle.Add(n);
	lock.Leave();
}









void OctreeNode::Clear() {
	for(int i = 0; i < 8; i++) {
		if (branch[i]) {
			OctreeNode* n = branch[i];
			branch[i] = 0;
			Pool().Delete(n);
		}
	}
	flags = 0;
	level = 0;
}



Octree::Octree() {
	
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
	
	max_len = 0.5f * FastPow<double>(2.0, this->max_scale_level);
	transform = identity<mat4>();
	has_transform = false;
	
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
			bn = OctreeNode::Pool().New();
			bn->down = n;
			bn->level = n->level - 1;
		}
		n = bn;
	}
	return n;
}

bool Octree::Contains(vec3 pos) {
	if (!has_transform) {
		return	fabsf(pos[0]) < max_len &&
				fabsf(pos[1]) < max_len &&
				fabsf(pos[2]) < max_len;
	}
	else {
		TODO
	}
}

uint64 Octree::GetSeekBits(vec3 pos, int level) const {
	if (level >= max_scale_level)
		return 0;
	
	if (!has_transform) {
		vec3 neg_pt {max_len * -1, max_len * -1, max_len * -1};
		ASSERT(levels.GetCount());
		
		int level_i = level - min_scale_level;
		int level_i_max = max_scale_level - min_scale_level;
		int rev_level_i = level_i_max - level_i;
		const Level& level = levels[level_i];
		ivec3 ipos;
		for(int i = 0; i < 3; i++)
			ipos[i] = (int)((pos[i] + max_len) / level.step);
		
		for(int i = 0; i < 3; i++) {ASSERT(ipos[i] >= 0 && ipos[i] < level.steps);}
		
		uint64 seek = 0, j = 0;
		for(int shift = rev_level_i - 1; shift >= 0; shift--) {
			uint32 mask = 1UL << shift;
			for(uint64 i = 0; i < 3; i++)
				if (ipos[i] & mask)
					seek |= 1ULL << (j + i);
			j += 3;
		}
		return seek;
	}
	else {
		TODO
	}
}



NAMESPACE_OULU_END
