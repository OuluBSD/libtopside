#ifndef _GraphLib_TournamentTree_h_
#define _GraphLib_TournamentTree_h_

#include "Layout.h"

NAMESPACE_GRAPHLIB_BEGIN

class TournamentTree : public Layout {
	Vector<Node*> order;
	bool src_graph;
public:
	//    @param {Graph} graph
	//    @param {Array[Node]} order
	TournamentTree(Graph& graph);
	TournamentTree(Graph& graph, const Vector<Node*>& order);
	void RefreshOrders();
	virtual void RefreshLayout();
	virtual void LayoutPrepare();
};

NAMESPACE_GRAPHLIB_END

#endif
