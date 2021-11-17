#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN



bool IsBBoxCollision(const BBox& r1, const BBox& r2) {
	auto w1 = r1.width;
	auto w2 = r2.width;
	double distance = (w1 * 0.25 + 0.5);
	
	return r2.x <= r1.x + distance &&
		   r2.x >= r1.x - distance &&
		   r2.y <= r1.y + distance &&
		   r2.y >= r1.y - distance &&
		   w2 <= (w1 * 1.5 + 0.5) &&
		   w1 <= (w2 * 1.5 + 0.5);
}


void GroupRectangles(const Vector<BBox>& rects, Vector<BBox>& result_seq, int min_neighbors) {
	struct Node : Moveable<Node> {
		int			parent;
		BBox		element;
		int			rank;
	};
	
	int c = rects.GetCount();
	Vector<Node> node;
	node.SetCount(c);
	auto r_iter = rects.Begin();
	for (Node& n : node) {
		n.parent = -1;
		n.element = *r_iter;
		n.rank = 0;
		r_iter++;
	}
	
	int i = 0;
	for (Node& n : node) {
		if (n.element.IsEmpty()) {
			i++;
			continue;
		}
		
		int root = i;
		while (node[root].parent != -1)
			root = node[root].parent;
		for (int j = 0; j < c; ++j) {
			if (i != j &&
				!node[j].element.IsEmpty() &&
				IsBBoxCollision(node[i].element, node[j].element)) {
				int root2 = j;
				
				while (node[root2].parent != -1)
					root2 = node[root2].parent;
					
				if (root2 != root) {
					if (node[root].rank > node[root2].rank)
						node[root2].parent = root;
					else {
						node[root].parent = root2;
						if (node[root].rank == node[root2].rank)
							node[root2].rank++;
						root = root2;
					}
					
					// compress path from node2 to the root:
					int temp, node2 = j;
					while (node[node2].parent != -1) {
						temp = node2;
						node2 = node[node2].parent;
						node[temp].parent = root;
					}
					
					// compress path from node to the root:
					node2 = i;
					while (node[node2].parent != -1) {
						temp = node2;
						node2 = node[node2].parent;
						node[temp].parent = root;
					}
				}
			}
		}
		
		i++;
	}
	
	Vector<int> idx_seq;
	idx_seq.SetCount(c);
	int class_idx = 0;
	for (int i = 0; i < c; i++) {
		int j = -1;
		int node1 = i;
		if (!node[node1].element.IsEmpty()) {
			while (node[node1].parent != -1)
				node1 = node[node1].parent;
			if (node[node1].rank >= 0)
				node[node1].rank = ~class_idx++;
			j = ~node[node1].rank;
		}
		idx_seq[i] = j;
	}
	
	Vector<BBox> comps;
	comps.SetCount(class_idx+1);
	for (BBox& b : comps)
		b.Clear();
	
	// count number of neighbors
	for (int i = 0; i < c; ++i) {
		const BBox& r1 = rects[i];
		int idx = idx_seq[i];
		BBox& b = comps[idx];
		
		if (b.neighbors == 0)
			b.confidence = r1.confidence;
			
		++b.neighbors;
		
		b.x += r1.x;
		b.y += r1.y;
		b.width += r1.width;
		b.height += r1.height;
		b.confidence = max(b.confidence, r1.confidence);
	}
	
	Vector<BBox> seq2;
	seq2.Reserve(class_idx);
	// calculate average bounding box
	for (i = 0; i < class_idx; ++i) {
		int n = comps[i].neighbors;
		if (n >= min_neighbors) {
			BBox& b = seq2.Add();
			b.x = (comps[i].x * 2 + n) / (2 * n);
			b.y = (comps[i].y * 2 + n) / (2 * n);
			b.width = (comps[i].width * 2 + n) / (2 * n);
			b.height = (comps[i].height * 2 + n) / (2 * n);
			b.neighbors = comps[i].neighbors;
			b.confidence = comps[i].confidence;
		}
	}
	
	
	int c2 = seq2.GetCount();
	result_seq.SetCount(0);
	result_seq.Reserve(c2);
	// filter out small face rectangles inside large face rectangles
	for (const BBox& r1 : seq2) {
		bool flag = true;
		for (const BBox& r2 : seq2) {
			double distance = (r2.width * 0.25 + 0.5);
			
			if (&r1 != &r2 &&
				r1.x >= r2.x - distance &&
				r1.y >= r2.y - distance &&
				r1.x + r1.width <= r2.x + r2.width + distance &&
				r1.y + r1.height <= r2.y + r2.height + distance &&
				(r2.neighbors > max(3, r1.neighbors) || r1.neighbors < 3)) {
				flag = false;
				break;
			}
		}
		
		if (flag)
			result_seq.Add(r1);
	}
	
}


NAMESPACE_TOPSIDE_END
