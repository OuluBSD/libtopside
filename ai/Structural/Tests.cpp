#include "Structural.h"


NAMESPACE_TOPSIDE_BEGIN

#ifdef flagSTDEXC

void StructuralTests() {
	Graph g;
	int dax_h			= g.AddKey("dax.h");
	int yow_h			= g.AddKey("yow.h");
	int boz_h			= g.AddKey("boz.h");
	int zow_h			= g.AddKey("zow.h");
	int foo_cpp			= g.AddKey("foo.cpp");
	int foo_o			= g.AddKey("foo.o");
	int bar_cpp			= g.AddKey("bar.cpp");
	int bar_o			= g.AddKey("bar.o");
	int libfoobar_a		= g.AddKey("libfoobar.a");
	int zig_cpp			= g.AddKey("zig.cpp");
	int zig_o			= g.AddKey("zig.o");
	int zag_cpp			= g.AddKey("zag.cpp");
	int zag_o			= g.AddKey("zag.o");
	int libzigzag_a		= g.AddKey("libzigzag.a");
	int killerapp		= g.AddKey("killerapp");
	
	g.AddEdge(dax_h, foo_cpp);
	g.AddEdge(dax_h, bar_cpp);
	g.AddEdge(dax_h, yow_h);
	g.AddEdge(yow_h, bar_cpp);
	g.AddEdge(yow_h, zag_cpp);
	g.AddEdge(boz_h, bar_cpp);
	g.AddEdge(boz_h, zig_cpp);
	g.AddEdge(boz_h, zag_cpp);
	g.AddEdge(zow_h, foo_cpp);
	g.AddEdge(foo_cpp, foo_o);
	g.AddEdge(foo_o, libfoobar_a);
	g.AddEdge(bar_cpp, bar_o);
	g.AddEdge(bar_o, libfoobar_a);
	g.AddEdge(libfoobar_a, libzigzag_a);
	g.AddEdge(zig_cpp, zig_o);
	g.AddEdge(zig_o, libzigzag_a);
	g.AddEdge(zag_cpp, zag_o);
	g.AddEdge(zag_o, libzigzag_a);
	g.AddEdge(libzigzag_a, killerapp);
	
	{
		g.TopologicalSort();
		
		LOG("make ordering:");
		for(int i = 0; i < g.GetKeyCount(); i++) {
			LOG("\t" << i << ": " << g.GetKey(i).ToString());
		}
		LOG("");
		
		// Parallel compilation ordering
		int N = g.GetKeyCount();
		VectorMap<int,int> time;
		for(int i = 0; i < N; i++) {
			int key_i = g.GetSortedKey(i);
			int in_count = g.GetEdgesInCount(key_i);
			int max_dist = -1;
			if (in_count > 0) {
				max_dist = 0;
				for(int j = 0; j < in_count; j++) {
					int from_key_i = g.GetEdgeIn(key_i, j);
					int dist = time.Get(from_key_i, 0);
					max_dist = max(max_dist, dist);
				}
			}
			time.Add(key_i, max_dist + 1);
		}
		SortByValue(time, StdLess<int>());
		
		LOG("parallel make ordering, vertices with same group number can be made in parallel");
		for(int i = 0; i < time.GetCount(); i++) {
			int key_i = time.GetKey(i);
			String key = g.GetKey(key_i);
			LOG("\ttime_slot[\"" << key << "\"] = " << time[i]);
		}
		LOG("");
	}
	
	// if I change yow.h what files need to be re-made?
	{
		struct PrintVisitor : public DfsVisitor {
			void DiscoverEdge(const GraphEdge& e, Graph& g) override {
				LOG(g.GetKey(e.b).ToString());
			}
		};
		LOG("A change to yow.h will cause what to be re-made?");
		PrintVisitor vis;
		g.BreadthFirstSearch(yow_h, vis);
		//g.DumpSorted();
		LOG("");
	}
		

	// are there any cycles in the graph?
	{
		bool has_cycle = false;
		CycleDetector vis(has_cycle);
		g.DepthFirstSearch(vis);
		LOG("The graph has a cycle? " << (has_cycle ? "yes" : "no"));
		//g.DumpSorted();
		LOG("");
	}
	
	// add a dependency going from bar.cpp to dax.h
	{
		LOG("adding edge bar_cpp -> dax_h");
		g.AddEdge(bar_cpp, dax_h);
		LOG("");
	}
	
	// are there any cycles in the graph?
	{
		bool has_cycle = false;
		CycleDetector vis(has_cycle);
		g.DepthFirstSearch(vis);
		LOG("The graph has a cycle now? " << (has_cycle ? "yes" : "no"));
		LOG("");
	}
	
	LOG("Finished");
}

#endif

NAMESPACE_TOPSIDE_END
