#include "Structural.h"


NAMESPACE_TOPSIDE_BEGIN


Graph::Graph() {
	
}

void Graph::DumpKeys() {
	LOG("Graph:");
	for (auto& key : keys) {
		LOG("\t" << key.ToString());
	}
}
void Graph::Clear() {
	ClearError();
	keys.Clear();
	dependers.Clear();
	dependencies.Clear();
}

int Graph::AddKey(Object key) {
	int i = keys.GetCount();
	keys.Add(key);
	dependers.Add();
	dependencies.Add();
	return i;
}

bool Graph::AddEdge(int dependency, int depender) {
	if (dependency < 0 || dependency >= keys.GetCount() ||
		depender   < 0 || depender   >= keys.GetCount()) {
		SetError("Invalid Graph key");
		return false;
	}
	dependers[dependency].Add(depender);
	dependencies[depender].Add(dependency);
	return true;
}

bool Graph::AddEdgeKey(Object dependency, Object depender) {
	int a = keys.Find(dependency);
	if (a < 0) {
		SetError("Dependency key not found"); return false;}
	
	int b = keys.Find(depender);
	if (b < 0) {
		SetError("Depender key not found"); return false;}
	
	if (a < 0 || a >= keys.GetCount() || b   < 0 || b   >= keys.GetCount()) {
		SetError("Invalid Graph key");
		return false;
	}
	dependers[a].Add(b);
	dependencies[b].Add(a);
	return true;
}

// A recursive function used by TopologicalSort
void Graph::TopologicalSortUtil(int v, Vector<bool>& visited, Vector<int>& stack) {
	// Mark the current node as visited.
	visited[v] = true;
	
	// Recur for all the vertices adjacent to this vertex
	for (int key_i : dependers[v])
		if (!visited[key_i])
			TopologicalSortUtil(key_i, visited, stack);
			
	// Push current vertex to stack which stores result
	stack.Add(v);
}

// The function to do Topological Sort. It uses recursive
// TopologicalSortUtil()
void Graph::TopologicalSort() {
	Reset();
		
	// Call the recursive helper function to store Topological
	// Sort starting from all vertices one by one
	sorted.SetCount(0);
	for (int i = 0; i < keys.GetCount(); i++)
		if (visited[i] == false)
			TopologicalSortUtil(i, visited, sorted);
	
}

int Graph::GetSortedKey(int i) const {
	return sorted[i];
}

int Graph::GetEdgesInCount(int key_i) {
	return dependers[key_i].GetCount();
}

int Graph::GetEdgeIn(int key_i, int i) {
	return dependers[key_i][i];
}

int Graph::FindSorted(int key_i) const {
	return VectorFind<int>(sorted, key_i);
}

void Graph::Reset() {
	visited.SetCount(keys.GetCount());
	for(bool& b : visited) b = false;
	sorted.SetCount(0);
	queue.SetCount(0);
	stack.SetCount(0);
}

void Graph::BreadthFirstSearch(int key_i, DfsVisitor& vis) {
	Reset();
	queue.Add(GraphEdge(-1, key_i));
	sorted.Reserve(keys.GetCount());
	
	for(int i = 0; i < queue.GetCount(); i++) {
		const GraphEdge& e = queue[i];
		bool& v = visited[e.b];
		if (v) {
			if (VectorFind(stack, e.b) >= 0)
				vis.BackEdge(e, *this);
			else
				vis.SideEdge(e, *this);
		}
		else {
			v = true;
			sorted.Add(e.b);
			vis.DiscoverEdge(e, *this);
			stack.Add(e.b);
			AddEdgesInToQueue(e.b);
			stack.Remove(stack.GetCount()-1);
		}
	}
}

void Graph::AddEdgesInToQueue(int key_i) {
	Vector<int>& a = dependers[key_i];
	queue.Reserve(queue.GetCount() + a.GetCount());
	for(int depender : a)
		queue.Add(GraphEdge(key_i, depender));
}

void Graph::DepthFirstSearch(DfsVisitor& vis) {
	Reset();
	
	for(int key_i = 0; key_i < keys.GetCount(); key_i++)
		DepthFirstEdge(GraphEdge(-1, key_i), vis);
	
}

void Graph::DepthFirstEdge(const GraphEdge& e_in, DfsVisitor& vis) {
	const Vector<int>& in = dependers[e_in.b];
	for (int depender : in) {
		GraphEdge e(e_in.b, depender);
		bool& v = visited[e.b];
		if (v) {
			if (VectorFind(stack, e.b) >= 0)
				vis.BackEdge(e, *this);
			else
				vis.SideEdge(e, *this);
		}
		else {
			v = true;
			sorted.Add(e.b);
			vis.DiscoverEdge(e, *this);
			stack.Add(e.b);
			DepthFirstEdge(e, vis);
			stack.Remove(stack.GetCount()-1);
		}
	}
}

void Graph::DumpSorted() {
	LOG("Sorted:");
	for(int i = 0; i < sorted.GetCount(); i++) {
		LOG("\t[" << i << "] = \"" << keys[sorted[i]].ToString() << "\"");
	}
}


NAMESPACE_TOPSIDE_END

