#ifndef _SoftPhys_QuadTree_
#define _SoftPhys_QuadTree_


NAMESPACE_SOFTPHYS_BEGIN


struct QuadTreeData {
	void* object;
	FixedRectangle bounds;
	bool flag;

	inline QuadTreeData(void* o, const FixedRectangle& b) :
		object(o), bounds(b), flag(false) { }
};

struct QuadTreeNode : Moveable<QuadTreeNode> {
	
protected:
	Vector<QuadTreeNode> children;
	Vector<QuadTreeData*> contents;
	int cur_depth;
	static int max_depth;
	static int max_obj_per_node;
	FixedRectangle node_bounds;
	
public:
	QuadTreeNode() {}
	inline QuadTreeNode(const FixedRectangle& bounds) : node_bounds(bounds), cur_depth(0) {}
	
	void Set(const FixedRectangle& bounds) {node_bounds = bounds; cur_depth = 0;}
	
	bool IsLeaf();
	
	int NumObjects();
	
	void Insert(QuadTreeData& data);
	void Remove(QuadTreeData& data);
	void Update(QuadTreeData& data);
	
	void Shake();
	void Split();
	void Reset();
	Vector<QuadTreeData*> Query(const FixedRectangle& area);
	
};

typedef QuadTreeNode QuadTree;


NAMESPACE_SOFTPHYS_END

#endif