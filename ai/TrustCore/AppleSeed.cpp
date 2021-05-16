#include "TrustCore.h"

NAMESPACE_TOPSIDE_BEGIN



int AppleSeed(int node_count, int source, const Array<TrustEdge>& trust_edges, double init_energy, double init_spread_factor, double threshold, RankingMap& rankings, Graph& graph) {
    LLOG("source " << source);
    LLOG("initial energy " << init_energy);
    LLOG("spreading factor " << init_spread_factor);
    LLOG("activation threshold " << threshold);
    LLOG("assignments");
    LDUMPC(trust_edges);
    
    graph.Init(node_count, trust_edges);
    
    const int PREV = 0;
    const int CURR = 1;
    Vector<double> trust[2];
    Vector<double> incoming[2];
    Index<int> nodes[2];
    
	for(int i = 0; i < 2; i++) {
		trust[i].SetCount(node_count, 0);
		incoming[i].SetCount(node_count, 0);
	}
    
    incoming[PREV][source] = init_energy;
    trust[PREV][source] = 0;
    nodes[PREV].Add(source);
    nodes[CURR] <<= nodes[PREV];
    
    int i = 0;
    for (; i < 1000; i++) {
        LLOG("iteration " << i);
        
        for (auto& v : incoming[CURR]) v = 0;
        
        for (int node : nodes[PREV]) {
            LLOG("current node: " << node);
            
            double spread_factor = (node == source ? 1 : init_spread_factor);
            double trust_reserved = (1 - spread_factor) * incoming[PREV][node];
            double prev_trust = trust[PREV][node];
            double new_trust = prev_trust + trust_reserved;
            
            trust[CURR][node] = new_trust;
            LLOG(Format("previous_trust[%d] = %n", node, prev_trust));
            LLOG(Format("current_trust[%d] = %n", node, new_trust));
            
            const TrustEdgeVec& edges = graph.GetEdgesOutTrimmed(node);
            for (const TrustEdge* e : edges) if (e) {
                int dst = e->dst;
                
                if (nodes[CURR].Find(dst) < 0) {
                    const TrustEdgeVec& edges = graph.GetEdgesOut(dst);
                    const TrustEdge* prev = edges[source];
                    if (!prev || prev->weight != 1.0) {
	                    nodes[CURR].Add(dst);
	                    trust[CURR][dst] = 0;
	                    incoming[CURR][dst] = 0;
	                    
	                    TrustEdge& new_edge = graph.NewTempEdge();
	                    new_edge.src = dst;
	                    new_edge.dst = source;
	                    new_edge.weight = 1.0;
	                    ASSERT(dst != source);
	                    graph.AddEdge(new_edge);
                    }
                }
                const TrustEdgeVec& edges_out = graph.GetEdgesOut(node);
                double weight_total = 0;
                for(const TrustEdge* e2 : edges_out)
                    if (e2)
						weight_total += e2->weight;
                double incoming_trust = incoming[PREV][node];
                double weight_dst = e->weight;
                double weighted_incoming = incoming_trust * (weight_dst / weight_total);
                incoming[CURR][dst] += weighted_incoming * spread_factor;
            }
        }
        if (i > 0) {
            double delta_max = 0;
            for (int y : nodes[CURR]) {
                double curr_max = trust[CURR][y];
                double prev_max = trust[PREV][y];
                double delta = curr_max - prev_max;
                if (delta > delta_max)
					delta_max = delta;
            }
            
            if (delta_max <= threshold) {
                LLOG(Format("convergence took %d iterations", i));
                break;
            }
        }
        
        trust[PREV] <<= trust[CURR];
        incoming[PREV] <<= incoming[CURR];
        nodes[PREV] <<= nodes[CURR];
    }
    
    rankings.Clear();
    for(int node : nodes[CURR]) {
        if (node != source) {
			double value = trust[CURR][node];
			rankings.Add(node, value);
        }
    }
    SortByValue(rankings, StdGreater<double>());
    
    return i;
}


NAMESPACE_TOPSIDE_END
