#ifndef _Structural_Graph_h_
#define _Structural_Graph_h_


NAMESPACE_TOPSIDE_BEGIN


class Graph;


struct GraphEdge : Moveable<GraphEdge> {
	int a, b;
	
	GraphEdge() = default;
	GraphEdge(const GraphEdge&) = default;
	GraphEdge(int a, int b) : a(a), b(b) {}
	
};

class DfsVisitor {
	
public:
	
	virtual void BackEdge(const GraphEdge& e, Graph& g) {}
	virtual void SideEdge(const GraphEdge& e, Graph& g) {}
	virtual void DiscoverEdge(const GraphEdge& e, Graph& g) {}
	
};


struct CycleDetector : public DfsVisitor {
	CycleDetector(bool& has_cycle) : has_cycle(has_cycle) {}
			
	void BackEdge(const GraphEdge& e, Graph& g) override {
		has_cycle = true;
	}
	
protected:
	bool& has_cycle;
};


class Graph : public ErrorReporter {
	Vector<Vector<int> > dependers, dependencies;
	Index<Object> keys;
	
	Vector<GraphEdge> queue;
	Vector<int> sorted, stack;
	Vector<bool> visited;
	
	void TopologicalSortUtil(int v, Vector<bool>& visited, Vector<int>& Stack);
	
	void AddEdgesInToQueue(int key_i);
	void Reset();
	void DepthFirstEdge(const GraphEdge& e, DfsVisitor& vis);
	
public:
	Graph();
	
	void DumpKeys();
	void Clear();
	void TopologicalSort();
	void BreadthFirstSearch(int key_i, DfsVisitor& vis);
	void DepthFirstSearch(DfsVisitor& vis);
	
	int  AddKey(Object key);
	bool AddEdge(int dependency, int depender);
	bool AddEdgeKey(Object dependency, Object depender);
	
	int GetKeyCount() const {return keys.GetCount();}
	Object GetKey(int i) const {return keys[i];}
	int GetSortedKey(int i) const;
	int GetSortedCount() const {return sorted.GetCount();}
	int GetEdgesInCount(int key_i);
	int GetEdgeIn(int key_i, int i);
	int FindSorted(int key_i) const;
	
	void DumpSorted();
};

NAMESPACE_TOPSIDE_END

#endif
