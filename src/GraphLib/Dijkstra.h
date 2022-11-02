#ifndef _GraphLib_Dijkstra_h_
#define _GraphLib_Dijkstra_h_

#include "BinaryHeapMap.h"

//    Path-finding algorithm Dijkstra
//
//    - worst-case running time is O((|E| + |V|) · log |V| ) thus better than
//     Bellman-Ford for sparse graphs (with less edges), but cannot handle
//     negative edge weights

NAMESPACE_GRAPHLIB_BEGIN

void Dijkstra(Graph& g, Node& source);

NAMESPACE_GRAPHLIB_END

#endif
