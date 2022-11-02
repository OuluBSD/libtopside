#ifndef _GraphLib_Spring_h_
#define _GraphLib_Spring_h_

#include "Layout.h"

//    TODO take ratio into account
//    TODO use integers for speed
NAMESPACE_GRAPHLIB_BEGIN

class Spring : public Layout {
	Vector<double> randoms;
	Vector<double> node_to_node_weights;
	int tmp_node_count;
	int random_cursor;
	double maxRepulsiveForceDistance;
	double maxVertexMovement;
	double c;
	double weighted_force_mul;
	int iterations;
	int k;
	bool use_weighted_force;
	
	double GetRandom();
	
public:
	Spring(Graph& graph);
	virtual void Randomize();
	virtual void RefreshLayout();
	virtual void LayoutPrepare();
	void LayoutIteration();
	void LayoutRepulsive(Node& node1, Node& node2);
	void LayoutRepulsive(Node& node, Edge& edge);
	void LayoutAttractive(Edge& edge);
	
	void SetWeightedForce(bool b) {use_weighted_force = b;}
	bool IsWeightedForce() const {return use_weighted_force;}
	
};

NAMESPACE_GRAPHLIB_END

#endif
