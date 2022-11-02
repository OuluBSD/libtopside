#ifndef _SoftPhys_QuadTree_
#define _SoftPhys_QuadTree_


NAMESPACE_SOFTPHYS_BEGIN


struct QuadTreeData {
	void* object;
	Rectangle bounds;
	bool flag;

	inline QuadTreeData(void* o, const Rectangle& b) :
		object(o), bounds(b), flag(false) { }
};

struct QuadTreeNode : Moveable<QuadTreeNode> {
	
protected:
	Vector<QuadTreeNode> children;
	Vector<QuadTreeData*> contents;
	int cur_depth;
	static int max_depth;
	static int max_obj_per_node;
	Rectangle node_bounds;
	
public:
	QuadTreeNode() {}
	inline QuadTreeNode(const Rectangle& bounds) : node_bounds(bounds), cur_depth(0) {}
	
	void Set(const Rectangle& bounds) {node_bounds = bounds; cur_depth = 0;}
	
	bool IsLeaf();
	
	int NumObjects();
	
	void Insert(QuadTreeData& data);
	void Remove(QuadTreeData& data);
	void Update(QuadTreeData& data);
	
	void Shake();
	void Split();
	void Reset();
	Vector<QuadTreeData*> Query(const Rectangle& area);
	
};

typedef QuadTreeNode QuadTree;


NAMESPACE_SOFTPHYS_END

#endif