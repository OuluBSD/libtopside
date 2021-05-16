#pragma once


NAMESPACE_TOPSIDE_BEGIN


class TrustNet : Moveable<TrustNet> {
	double trust_threshold = 0.5;
	int rootid = 0;
	int node_count = 0;
	RankingMap rankings;
	Graph graph;
	bool is_first_order;
	Array<TrustEdge> trust_assignments;
	Vector<bool> id_distrusted;
	
	
public:
	typedef TrustNet CLASSNAME;
	
	TrustNet() {}
	
	void Clear();
	
	int GetRoot() const {return rootid;}
	
	void Load(double trust_threshold, int node_count, int rootid, const Vector<TrustEdge>& assignments, const Index<int>& distrusted);
	bool IsFirstOrderGraph(int root, const Array<TrustEdge>& assignments);
	const TrustEdgeVec& GetFirstOrderEdges(int rootid, const Array<TrustEdge>& assignments);
	RankingMap GetMostTrusted();
	RankingMap GetRankings() const;
	RankingMap GetAllTrusted() const;
	RankingMap HighOnlyStrategy();
	RankingMap GetMissingRankingsList(const Vector<int>& nodes);
	RankingMap FirstOrderRankings(int rootid, const Array<TrustEdge>& assignments);
	Vector<int> GetFirstOrderNodes(const Graph& g, int rootid);
	
	
	static MatFloat GetBreaks(const RankingMap& rankings, int breaks = -1, int* used_breaks = 0);
	static RankingMap NaiveHighTrustStrategy(const RankingMap& rankings);
	static RankingMap Merge(const RankingMap& obj, const RankingMap& obj_arr);
	static Graph& TempGraph();
};



class TrustHandler {
	VectorMap<int, TrustNet> trust_areas;
	
public:
	
	TrustHandler () {}
	
	int GetArea(double trust_threshold) const {return 10000 * trust_threshold;}
	
	void Load(double trust_threshold, int id_count, int rootid, const Vector<TrustEdge>& assignments, const Index<int>& distrusted) {
		trust_areas.GetAdd(GetArea(trust_threshold)).Load(trust_threshold, id_count, rootid, assignments, distrusted);
	}
	
	RankingMap GetMostTrusted(int area) {return Get(area).GetMostTrusted();}
	RankingMap GetRankings(int area) {return Get(area).GetRankings();}
	RankingMap GetAllTrusted(int area) {return Get(area).GetAllTrusted();}
	
	TrustNet& Get(int area) {
		ASSERT(area >= 0 && area < trust_areas.GetCount());
	    return trust_areas[area];
	}
	
	void Remove(int area) {
	    trust_areas.Remove(area);
	}
	
};

NAMESPACE_TOPSIDE_END
