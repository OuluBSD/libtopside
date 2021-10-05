#include "TrustCore.h"


NAMESPACE_TOPSIDE_BEGIN

void Graph::Reset(int node_count) {
	tmp.Clear();
	ASSERT(node_count > 0);
	graph.SetCount(node_count);
	for(auto& n : graph)
		n.Reset(node_count);
}

void Graph::Init(int node_count) {
	Reset(node_count);
}

void Graph::Init(int node_count, const Array<TrustEdge>& edges) {
	Reset(node_count);
	for(const TrustEdge& e : edges)
		AddEdge(e);
}

TrustEdgeVec Graph::GetEdgesOutTrimmed(int node) const {
	TrustEdgeVec o;
	const auto& i = graph[node].out;
	for (auto v : i)
		if (v)
			o.Add(v);
	return o;
}

TrustEdgeVec Graph::GetEdgesInTrimmed(int node) const {
	TrustEdgeVec o;
	const auto& i = graph[node].inc;
	for (auto v : i)
		if (v)
			o.Add(v);
	return o;
}

void Graph::AddEdge(const TrustEdge& e) {
    AddOutgoing(e);
    AddIncoming(e);
}

int Graph::Traverse(int root, int node) const {
    if (root == node)
		return 0;
    
    MAKE_STATIC_LOCAL(Vector<int>, queue);
    MAKE_STATIC_LOCAL(Vector<int>, layer);
    MAKE_STATIC_LOCAL(Index<int>, traversed);
    queue.SetCount(0);
    queue.Add(root);
    
    layer.SetCount(0);
    traversed.Clear();
    int depth = 1;
    int cur_i = 0;
    while (queue.GetCount() - cur_i > 0) {
        int current = queue[cur_i++];
        traversed.Add(current);
        const TrustEdgeVec& out_edges = GetEdgesOut(current);
        for(const TrustEdge* e : out_edges) if (e) {
            int n = e->dst;
            if (n == node)
				return depth;
            if (traversed.Find(n) < 0)
				layer.Add(n);
        }
        if (cur_i == queue.GetCount()) {
            Swap(queue, layer);
            layer.SetCount(0);
            cur_i = 0;
            depth = depth + 1;
        }
    }
    
    return -1;
}

int Graph::GetDepth(int root, int node) const {
    return Traverse(root, node);
}

NAMESPACE_TOPSIDE_END
