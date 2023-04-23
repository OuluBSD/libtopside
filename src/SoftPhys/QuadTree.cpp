#include "Internal.h"


NAMESPACE_SOFTPHYS_BEGIN


int QuadTreeNode::max_depth = 5;
int QuadTreeNode::max_obj_per_node = 15;

bool QuadTreeNode::IsLeaf() {
	return children.GetCount() == 0;
}

int QuadTreeNode::NumObjects() {
	Reset();

	int objectCount = contents.GetCount();
	for (int i = 0, size = contents.GetCount(); i < size; ++i) {
		contents[i]->flag = true;
	}

	LinkedList<QuadTreeNode*> process;
	process.Add(this);

	while (process.GetCount() > 0) {
		QuadTreeNode* processing = process.First();

		if (!processing->IsLeaf()) {
			for (int i = 0, size = processing->children.GetCount(); i < size; ++i) {
				process.Add(&processing->children[i]);
			}
		}
		else {
			for (int i = 0, size = processing->contents.GetCount(); i < size; ++i) {
				if (!processing->contents[i]->flag) {
					objectCount += 1;
					processing->contents[i]->flag = true;
				}
			}
		}
		
		process.RemoveFirst();
	}

	Reset();
	return objectCount;
}

void QuadTreeNode::Insert(QuadTreeData& data) {
	if (!RectangleRectangle(data.bounds, node_bounds)) {
		return; // The object does not fit into this node
	}

	if (IsLeaf() && contents.GetCount() + 1 > max_obj_per_node) {
		Split(); // Try splitting!
	}

	if (IsLeaf()) {
		contents.Add(&data);
	}
	else {
		for (int i = 0, size = children.GetCount(); i < size; ++i) {
			children[i].Insert(data);
		}
	}
}

void QuadTreeNode::Remove(QuadTreeData& data) {
	if (IsLeaf()) {
		int removeIndex = -1;
		for (int i = 0, size = contents.GetCount(); i < size; ++i) {
			if (contents[i]->object == data.object) {
				removeIndex = i;
				break;
			}
		}

		if (removeIndex != -1) {
			contents.Remove(1);
		}
	}
	else {
		for (int i = 0, size = children.GetCount(); i < size; ++i) {
			children[i].Remove(data);
		}
	}

	Shake();
}

void QuadTreeNode::Update(QuadTreeData& data) {
	Remove(data);
	Insert(data);
}

void QuadTreeNode::Shake() {
	// Cant shake a leaf
	if (!IsLeaf()) {
		int numObjects = NumObjects();
		// None of the children contain any objects, collapse
		if (numObjects == 0) {
			children.Clear();
		}
		// Children combined have less objects than maximum for the node, collapse!
		else if (numObjects < max_obj_per_node) {
			// Loop trough down to leaf nodes, non-recursivley
			LinkedList<QuadTreeNode*> process;
			process.Add(this);

			while (process.GetCount() > 0) {
				QuadTreeNode* processing = process.First();

				if (!processing->IsLeaf()) {
					// Not a leaf node, add children to list to process!
					for (int i = 0, size = processing->children.GetCount(); i < size; ++i) {
						process.Add(&processing->children[i]);
					}
				}
				else {
					// Was a leaf node, add all children to our list!
					contents.Append(processing->contents);
				}
				
				process.RemoveFirst();
			}

			children.Clear();
		}
	}
}

void QuadTreeNode::Reset() {
	if (IsLeaf()) {
		for (int i = 0, size = contents.GetCount(); i < size; ++i) {
			contents[i]->flag = false;
		}
	}
	else {
		for (int i = 0, size = children.GetCount(); i < size; ++i) {
			children[i].Reset();
		}
	}
}

void QuadTreeNode::Split() {
	if (cur_depth + 1 >= max_depth) {
		return;
	}

	vec2 min = GetMin(node_bounds);
	vec2 max = GetMax(node_bounds);
	vec2 center = min + ((max - min) * 0.5f);

	FixedRectangle childAreas[] = {
		FixedRectangle(FromMinMax(vec2(min[0], min[1]), vec2(center[0], center[1]))),
		FixedRectangle(FromMinMax(vec2(center[0], min[1]), vec2(max[0], center[1]))),
		FixedRectangle(FromMinMax(vec2(center[0], center[1]), vec2(max[0], max[1]))),
		FixedRectangle(FromMinMax(vec2(min[0], center[1]), vec2(center[0], max[1]))),
	};
	for (int i = 0; i < 4; ++i) {
		children.Add().Set(childAreas[i]);
		children[i].cur_depth = cur_depth + 1;
	}

	for (int i = 0, size = contents.GetCount(); i < size; ++i) {
		children[i].Insert(*contents[i]);
	}

	contents.Clear();
}

Vector<QuadTreeData*> QuadTreeNode::Query(const FixedRectangle& area) {
	Vector<QuadTreeData*> result;
	if (!RectangleRectangle(area, node_bounds)) {
		return result;
	}

	if (IsLeaf()) {
		for (int i = 0, size = contents.GetCount(); i < size; ++i) {
			if (RectangleRectangle(contents[i]->bounds, area)) {
				result.Add(contents[i]);
			}
		}
	}
	else {
		for (int i = 0, size = children.GetCount(); i < size; ++i) {
			Vector<QuadTreeData*> recurse = children[i].Query(area);
			if (recurse.GetCount() > 0) {
				result.Append(recurse);
			}
		}
	}
	return result;
}


NAMESPACE_SOFTPHYS_END
