#ifndef _GraphLib_Layout_h_
#define _GraphLib_Layout_h_

#include "Graph.h"

// Base class for distributing nodes algorithms

NAMESPACE_GRAPHLIB_BEGIN

class Layout {
	
protected:
	Graph* graph;
	
public:
	Layout(Graph& graph);
	virtual ~Layout();
	virtual void Randomize();
	virtual void RefreshLayout();
	virtual void LayoutPrepare();
	void InitCoords();
	void LayoutCalcBounds();
};

NAMESPACE_GRAPHLIB_END

#endif
