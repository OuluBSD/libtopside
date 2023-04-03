#include "Geometry.h"


NAMESPACE_TOPSIDE_BEGIN





void QuadtreeNode::Clear() {
	for(int i = 0; i < QUAD_BRANCHES; i++) {
		if (branch[i]) {
			QuadtreeNode* n = branch[i];
			branch[i] = 0;
			GetRecyclerPool().Return(n);
		}
	}
	flags = 0;
	level = 0;
}



Quadtree::Quadtree() {
	
}

int Quadtree::LimitLevel(int level) const {
	level = std::min(max_scale_level, std::max(min_scale_level, level));
	return level;
}

void Quadtree::Initialize(int min_scale_level, int max_scale_level) {
	ASSERT(min_scale_level <= 0);
	ASSERT(max_scale_level >= 0);
	this->min_scale_level = std::min(min_scale_level, 0);
	this->max_scale_level = std::max(max_scale_level, 0);
	this->scale_count = this->max_scale_level - this->min_scale_level + 1;
	
	root.Clear();
	root.level = this->max_scale_level;
	
	max_len = 0.5f * FastPow<float>(2.f, (float)this->max_scale_level);
	transform = Identity<mat4>();
	has_transform = false;
	
	levels.SetCount(scale_count);
	for(int i = 0; i < scale_count; i++) {
		Level& level = levels[i];
		level.step = FastPow<float>(2.f, (float)(this->min_scale_level + i));
		level.steps = 1 << (scale_count - 1 - i);
	}
	
}

int Quadtree::GetScaleLevel(float len) const {
	float a = FastLn(len);
	int level = (int)(a / (float)M_LN2 + (a >= 0.0f ? +0.5f : -0.5f));
	level = LimitLevel(level);
	return level;
}

QuadtreeNode* Quadtree::GetAddNode(vec3 pos, int level) {
	if (level < min_scale_level ||
		level > max_scale_level ||
		!Contains(pos))
		return NULL;
	
	uint64 seek = GetSeekBits(pos, level);
	
	QuadtreeNode* n = &root;
	while (n->level != level) {
		byte branch_i = seek & 7ULL;
		seek >>= 3ULL;
		QuadtreeNode*& bn = n->branch[branch_i];
		if (!bn) {
			bn = QuadtreeNode::GetRecyclerPool().New();
			bn->parent = n;
			bn->level = n->level - 1;
		}
		n = bn;
	}
	return n;
}

bool Quadtree::Contains(vec3 pos) {
	if (!has_transform) {
		return	fabsf(pos[0]) < max_len &&
				fabsf(pos[1]) < max_len &&
				fabsf(pos[2]) < max_len;
	}
	else {
		TODO
	}
}

uint64 Quadtree::GetSeekBits(vec3 pos, int level) const {
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
			for(int i = 0; i < 3; i++)
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



NAMESPACE_TOPSIDE_END
