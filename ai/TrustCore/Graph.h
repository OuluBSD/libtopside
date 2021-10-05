#ifndef _TrustCore_Graph_h_
#define _TrustCore_Graph_h_

NAMESPACE_TOPSIDE_BEGIN



struct TrustEdge : Moveable<TrustEdge> {
	float weight;
	int src, dst;
	
	
	void Set(int src, int dst, float weight) {
		this->src = src;
		this->dst = dst;
		this->weight = weight;
	}
	String ToString() const {
		return Format("weight: %3n, src: %d, dst: %d", weight, src, dst);
	}
};


typedef Vector<const TrustEdge*> TrustEdgeVec;


struct GraphNode : Moveable<GraphNode> {
	TrustEdgeVec inc, out;
	
	
	void Reset(int c) {
		inc.SetCount(c);
		out.SetCount(c);
		for (auto& v : inc) v = 0;
		for (auto& v : out) v = 0;
	}
	void Clear() {inc.SetCount(0); out.SetCount(0);}
};



class Graph {
	typedef GraphNode Node;
	
	Vector<Node> graph;
	Array<TrustEdge> tmp;
	
public:
	typedef Graph CLASSNAME;
	
	
	Graph() {}
	
	void Clear() {graph.Clear(); tmp.Clear();}
	void Reset(int node_count);
	void Init(int node_count);
	void Init(int node_count, const Array<TrustEdge>& edges);
	
	TrustEdge& NewTempEdge() {return tmp.Add();}
	const Array<TrustEdge>& GetTmpEdges() const {return tmp;}
	
	const TrustEdgeVec& GetEdgesOut(int node) const {return graph[node].out;}
	const TrustEdgeVec& GetEdgesIn(int node) const {return graph[node].inc;}
	TrustEdgeVec GetEdgesOutTrimmed(int node) const;
	TrustEdgeVec GetEdgesInTrimmed(int node) const;
	const Vector<Node>& GetNodes() const {return graph;}
	bool Has(int node) const {return node >= 0 && node < graph.GetCount();}
	
	void AddOutgoing(const TrustEdge& e) {graph[e.src].out[e.dst] = &e;}
	void AddIncoming(const TrustEdge& e) {graph[e.dst].inc[e.src] = &e;}
	
	void AddEdge(const TrustEdge& e);
	int Traverse(int root, int node) const;
	int GetDepth(int root, int node) const;
	
	
};


NAMESPACE_TOPSIDE_END

#endif
