#include "TrustCore.h"


NAMESPACE_TOPSIDE_BEGIN

void TrustNet::Clear() {
	trust_threshold = 0.5;
	rootid = 0;
	node_count = 0;
	rankings.Clear();
	is_first_order = true;
	trust_assignments.Clear();
	id_distrusted.Clear();
}

void TrustNet::Load(double trust_threshold, int node_count, int rootid, const Vector<TrustEdge>& assignments, const Index<int>& distrusted) {
	Clear();
	this->node_count = node_count;
	this->trust_threshold = trust_threshold;
	this->rootid = rootid;
	
	id_distrusted.SetCount(node_count);
	for (auto& i: id_distrusted)
		i = false;
	for (int id : distrusted)
		id_distrusted[id] = true;
		
	trust_assignments.SetCount(0);
	for (const TrustEdge& e : assignments)
		if (!id_distrusted[e.src] && !id_distrusted[e.dst])
			trust_assignments.Add(e);
			
	is_first_order = IsFirstOrderGraph(rootid, trust_assignments);
	if (is_first_order) {
		LLOG("only first order graph. skip");
		graph.Init(node_count, trust_assignments);
		rankings = FirstOrderRankings(rootid, trust_assignments);
	}
	else {
		AppleSeed(node_count, rootid, trust_assignments, 200, 0.85, 0.01, rankings, graph);
	}
}

RankingMap TrustNet::GetMostTrusted() {
	if (rankings.IsEmpty())
		return RankingMap();
	return HighOnlyStrategy();
}

RankingMap TrustNet::GetRankings() const {
	RankingMap nonzero_rankings;
	if (rankings.GetCount()) {
		const auto& values = rankings.GetValues();
		auto key = rankings.GetKeys().Begin();
		for (double value : values) {
			if (value > 0)
				nonzero_rankings.Add(*key, value);
			key++;
		}
	}
	return nonzero_rankings;
}

RankingMap TrustNet::GetAllTrusted() const {
	RankingMap r = GetRankings();
	if (!r.IsEmpty())
		r.GetAdd(rootid) = 1.0;
	return r;
}

MatFloat TrustNet::GetBreaks(const RankingMap& rankings, int breaks, int* used_breaks) {
	const auto& scores = rankings.GetValues();
	if (breaks < 0 || scores.GetCount() < breaks)
		breaks = scores.GetCount();
	if (used_breaks)
		*used_breaks = breaks;
	return CKMeans(scores, breaks);
}

RankingMap TrustNet::NaiveHighTrustStrategy(const RankingMap& rankings) {
	RankingMap tweaked_rankings;
	tweaked_rankings <<= rankings;
	
	int sentinel_i = tweaked_rankings.GetCount();
	tweaked_rankings.GetAdd(sentinel_i++) = 0;
	LLOG("rankings");
	LDUMPM(rankings);
	
	int breaks = 0;
	MatFloat groups = GetBreaks(tweaked_rankings, 3, &breaks);
	
	{
		auto& g0 = groups[0];
		for (int i = 0; i < g0.GetCount(); i++) {
			if (g0[i] <= 0)
				g0.Remove(i--);
		}
	}
	LLOG("groups");
	LDUMPCC(groups);
	LLOG("breaks: " << breaks);
	
	VecFloat highest_group;
	{
		ASSERT(groups.GetCount() >= 2);
		const auto& g1 = groups.Top();
		const auto& g2 = groups[groups.GetCount()-2];
		highest_group.Append(g1);
		highest_group.Append(g2);
	}
	LLOG("highest group");
	LDUMPC(highest_group);
	
	RankingMap result;
	RankingMap rankings_copy;
	rankings_copy <<= rankings;
	for (auto rank : highest_group) {
		int id = RankToId(rank, rankings_copy);
		rankings_copy.RemoveKey(id);
		result.Add(id, rank);
	}
	LLOG("high trust strategy result:");
	LDUMPM(result);
	SortByValue(result, StdGreater<double>());
	return result;
}

RankingMap TrustNet::Merge(const RankingMap& obj, const RankingMap& obj_arr) {
	RankingMap r;
	r <<= obj;
	auto value = obj_arr.GetValues().Begin();
	for (const auto& key : obj_arr.GetKeys()) {
		if (r.Find(key) < 0)
			r.Add(key, *value);
		value++;
	}
	return r;
}

RankingMap TrustNet::HighOnlyStrategy() {
	LLOG("entering high only strategy");
	TrustEdgeVec high_trust_edges, first_order_edges;
	Vector<int> first_order_nodes;
	const TrustEdgeVec& root_edges = graph.GetEdgesOut(rootid);
	for (const TrustEdge* e : root_edges) if (e) {
		if (e->weight >= trust_threshold)
			high_trust_edges.Add(e);
		
		if (e->weight > 0) {
			ASSERT(e->dst >= 0 && e->dst < node_count);
			first_order_edges.Add(e);
			first_order_nodes.Add(e->dst);
		}
	}
	
	if (high_trust_edges.GetCount() == 0) {
		LLOG("no high trust edges, returning missing rankings");
		return GetMissingRankingsList(first_order_nodes);
	}
	else if (is_first_order) {
		LLOG("first order graph, returning edges to ranked form");
		return EdgesToRankedForm(first_order_edges);
	}
		
	RankingMap result = NaiveHighTrustStrategy(rankings);
	
	Vector<int> missing_first_order_nodes;
	missing_first_order_nodes.Reserve(first_order_nodes.GetCount());
	for (int n : first_order_nodes)
		if (result.Find(n) < 0)
			missing_first_order_nodes.Add(n);
	
	RankingMap ranked_missing_edges = GetMissingRankingsList(missing_first_order_nodes);
	LLOG("fully computed, returning augmented appleseed edges");
	
	return Merge(result, ranked_missing_edges);
}

Graph& TrustNet::TempGraph() {
	MAKE_STATIC_LOCAL(Graph, g);
	return g;
}

bool TrustNet::IsFirstOrderGraph(int root, const Array<TrustEdge>& assignments) {
	Graph& g = TempGraph();
	g.Init(node_count, assignments);
	
	const TrustEdgeVec& out_edges = g.GetEdgesOut(root);
	{
		LLOG("is_first_order: root's outgoing edges");
		int i = 0;
		for (const TrustEdge* e : out_edges) if (e) {
			LLOG("\t" << i++ << ": " << e->ToString());
		}
	}
	
	Vector<int> out_nodes;
	for (const TrustEdge* e : out_edges) {
		if (e && e->weight > 0)
			out_nodes.Add(e->dst);
	}
	
	{
		LLOG("is_first_order: root's filtered outgoing nodes");
		LDUMPC(out_nodes);
	}
	
	for (int node : out_nodes) {
		const TrustEdgeVec& edges = g.GetEdgesOut(node);
		{
			LLOG("is_first_order edges");
			int i = 0;
			for (const TrustEdge* e : edges) if (e) {
				LLOG("\t" << i++ << ": " << e->ToString());
			}
		}
		int positive_non_root_count = 0;
		for (const TrustEdge* e : edges)
			if (e && e->weight > 0 && e->dst != root)
				positive_non_root_count++;
				
		if (edges.GetCount() > 0 && positive_non_root_count > 0)
			return false;
	}
	
	return true;
}

RankingMap TrustNet::GetMissingRankingsList(const Vector<int>& nodes) {
	RankingMap v;
	for (int node : nodes) {
		int j = rankings.Find(node);
		v.Add(node, j >= 0 ? rankings[j] : -1);
	}
	return v;
}

const TrustEdgeVec& TrustNet::GetFirstOrderEdges(int rootid, const Array<TrustEdge>& assignments) {
	Graph& g = TempGraph();
	g.Init(node_count, assignments);
	return g.GetEdgesOut(rootid);
}

Vector<int> TrustNet::GetFirstOrderNodes(const Graph& g, int rootid) {
	const TrustEdgeVec& v = g.GetEdgesOut(rootid);
	Vector<int> out;
	out.Reserve(v.GetCount());
	for (const TrustEdge* e : v)
		if (e)
			out.Add(e->dst);
	return out;
}

RankingMap TrustNet::FirstOrderRankings(int rootid, const Array<TrustEdge>& assignments) {
	const TrustEdgeVec& edges = GetFirstOrderEdges(rootid, assignments);
	return EdgesToRankedForm(edges);
}

NAMESPACE_TOPSIDE_END
