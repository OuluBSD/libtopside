#include "GraphLib.h"

NAMESPACE_GRAPHLIB_BEGIN

Spring::Spring(Graph& graph) : Layout(graph) {
	iterations = 500;
	maxRepulsiveForceDistance = 6;
	k = 2;
	c = 0.01;
	maxVertexMovement = 0.5;
	
	weighted_force_mul = 1.0;
	use_weighted_force = true;
}

double Spring::GetRandom() {
	if (random_cursor == randoms.GetCount()) {
		random_cursor++;
		return randoms.Add(Randomf());
	} else {
		return randoms[random_cursor++];
	}
}

void Spring::Randomize() {
	randoms.Clear();
}

void Spring::RefreshLayout() {
	LayoutPrepare();

	for (int i = 0; i < iterations; i++)
		LayoutIteration();

	LayoutCalcBounds();
}

void Spring::LayoutPrepare() {
	int c = graph->nodes.GetCount();
	tmp_node_count = c;
	node_to_node_weights.SetCount(0);
	node_to_node_weights.SetCount(c*c, 1.0);
	for(int i = 0; i < c; i++) {
		Node& node = graph->nodes[i];
		node.tmp_id = i;
		node.layout_pos_x = 0;
		node.layout_pos_y = 0;
		node.layout_force_x = 0;
		node.layout_force_y = 0;
	}
	for(Edge& e : graph->edges) {
		int a = e.source->tmp_id;
		int b = e.target->tmp_id;
		int p0 = a * c + b;
		int p1 = b * c + a;
		node_to_node_weights[p0] = e.weight;
		node_to_node_weights[p1] = e.weight;
	}
	random_cursor = 0;
}

void Spring::LayoutIteration() {
	
	// Forces on nodes due to node-node repulsions
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node1 = graph->nodes[i];
		
		for(int j = 0; j < i; j++) {
			Node& node2 = graph->nodes[j];
			LayoutRepulsive(node1, node2);
		}
	}
	
	// Forces on colliding edges
	for(int i = 0; i < graph->edges.GetCount(); i++) {
		Edge& a = graph->edges[i];
		for(int j = 0; j < i; j++) {
			Edge& b = graph->edges[j];
			if (a.IsColliding(b)) {
				LayoutRepulsive(*a.target, b);
				LayoutRepulsive(*a.source, b);
				LayoutRepulsive(*b.target, a);
				LayoutRepulsive(*b.source, a);
			}
		}
		
		for (Node& node : graph->nodes.GetValues()) {
			if (a.IsColliding(node)) {
				//LayoutRepulsive(*a.target, node);
				//LayoutRepulsive(*a.source, node);
				LayoutRepulsive(node, a);
			}
		}
	}
	
	// Forces on nodes due to edge attractions
	for(int i = 0; i < graph->edges.GetCount(); i++) {
		Edge& edge = graph->edges[i];
		LayoutAttractive(edge);
	}
	
	// Move by the given force
	for(int i = 0; i < graph->nodes.GetCount(); i++) {
		Node& node = graph->nodes[i];
		
		double xmove = c * node.layout_force_x;
		double ymove = c * node.layout_force_y;
		double max   = maxVertexMovement;

		if (xmove > max)  xmove = +max;
		if (xmove < -max) xmove = -max;
		if (ymove > max)  ymove = +max;
		if (ymove < -max) ymove = -max;

		node.layout_pos_x += xmove;
		node.layout_pos_y += ymove;
		node.layout_force_x = 0;
		node.layout_force_y = 0;
	}
}

void Spring::LayoutRepulsive(Node& node1, Node& node2) {
	double dx = node2.layout_pos_x - node1.layout_pos_x;
	double dy = node2.layout_pos_y - node1.layout_pos_y;
	double d2 = dx * dx + dy * dy;

	if (d2 < 0.01) {
		dx = 0.1 * GetRandom() + 0.1;
		dy = 0.1 * GetRandom() + 0.1;
		d2 = dx * dx + dy * dy;
	}

	double d = sqrt(d2);

	if (d < maxRepulsiveForceDistance) {
		double repulsiveForce = k * k / d;
		if (use_weighted_force) {
			int p = node1.tmp_id * tmp_node_count + node2.tmp_id;
			double weight = node_to_node_weights[p];
			double mul = 1.0 + (weight-1.0) * weighted_force_mul;
			repulsiveForce *= mul;
		}
		node2.layout_force_x += repulsiveForce * dx / d;
		node2.layout_force_y += repulsiveForce * dy / d;
		node1.layout_force_x -= repulsiveForce * dx / d;
		node1.layout_force_y -= repulsiveForce * dy / d;
	}
}

void Spring::LayoutRepulsive(Node& node, Edge& edge) {
	double edge_ct_x = (edge.source->layout_pos_x + edge.target->layout_pos_x) * 0.5;
	double edge_ct_y = (edge.source->layout_pos_y + edge.target->layout_pos_y) * 0.5;
	double dx = edge_ct_x - node.layout_pos_x;
	double dy = edge_ct_y - node.layout_pos_y;
	double d2 = dx * dx + dy * dy;

	if (d2 < 0.01) {
		dx = 0.1 * GetRandom() + 0.1;
		dy = 0.1 * GetRandom() + 0.1;
		d2 = dx * dx + dy * dy;
	}

	double d = sqrt(d2);

	if (d < maxRepulsiveForceDistance) {
		double repulsiveForce = k * k / d;
		/*if (use_weighted_force) {
			int p = node1.tmp_id * tmp_node_count + node2.tmp_id;
			double weight = node_to_node_weights[p];
			double mul = 1.0 + (weight-1.0) * weighted_force_mul;
			repulsiveForce *= mul;
		}*/
		repulsiveForce *= 0.3;
		node.layout_force_x -= repulsiveForce * dx / d;
		node.layout_force_y -= repulsiveForce * dy / d;
	}
}

void Spring::LayoutAttractive(Edge& edge) {
	Node& node1 = *edge.source;
	Node& node2 = *edge.target;
	double dx = node2.layout_pos_x - node1.layout_pos_x;
	double dy = node2.layout_pos_y - node1.layout_pos_y;
	double d2 = dx * dx + dy * dy;

	if (d2 < 0.01) {
		dx = 0.1 * GetRandom() + 0.1;
		dy = 0.1 * GetRandom() + 0.1;
		d2 = dx * dx + dy * dy;
	}

	double d = sqrt(d2);

	if (d > maxRepulsiveForceDistance) {
		d = maxRepulsiveForceDistance;
		d2 = d * d;
	}

	double attractiveForce = (d2 - k * k) / k;

	if (use_weighted_force) {
		double mul = 1.0 + (edge.weight-1.0) * weighted_force_mul;
		attractiveForce /= mul;
	}
	
	if (!edge.attraction)
		edge.attraction = 1;

	attractiveForce *= log((double)edge.attraction) * 0.5 + 1;
	node2.layout_force_x -= attractiveForce * dx / d;
	node2.layout_force_y -= attractiveForce * dy / d;
	node1.layout_force_x += attractiveForce * dx / d;
	node1.layout_force_y += attractiveForce * dy / d;
}

NAMESPACE_GRAPHLIB_END
