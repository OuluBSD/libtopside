#include "TrustCore.h"


NAMESPACE_TOPSIDE_BEGIN

int RankToId(double rank, const RankingMap& rankings) {
    for (int i = 0; i < rankings.GetCount(); i++) {
        double value = rankings[i];
		if (fabs(value - rank) < 0.005)
			return rankings.GetKey(i);
    }
    return -1;
}

RankingMap EdgesToRankedForm(const TrustEdgeVec& edges) {
    RankingMap rankings;
    for (const TrustEdge* e: edges) {
        ASSERT(rankings.Find(e->dst) < 0);
        rankings.Add(e->dst, e->weight);
    }
    SortByValue(rankings, StdGreater<double>());
    return rankings;
}


NAMESPACE_TOPSIDE_END
