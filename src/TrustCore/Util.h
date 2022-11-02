#pragma once


NAMESPACE_TOPSIDE_BEGIN

typedef VectorMap<int,double> RankingMap;

int RankToId(double rank, const RankingMap& rankings);
RankingMap EdgesToRankedForm(const TrustEdgeVec& edges);

int AppleSeed(int node_count, int source, const Array<TrustEdge>& trust_edges, double init_energy, double spread_factor, double threshold, RankingMap& rankings, Graph& graph);

NAMESPACE_TOPSIDE_END
