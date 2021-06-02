#include <TrustLib/TrustLib.h>



void GraphTest() {
	using namespace UPP;
	using namespace TS;
	
	enum {ALICE, BOB, CAROLE, DANIEL, MARJORY, BEA, PERSON_COUNT};
	
	UnitTest test;
	
	
	test("test passes", [](UnitTest& t) {
	    t.Pass("this test passes");
	});
	
	test("adding edges", [](UnitTest& t) {
	    TrustEdge e1;
	    e1.Set(ALICE, BOB, 0.5);
	    Graph graph;
	    graph.Init(PERSON_COUNT);
	    graph.AddEdge(e1);
	
	    t.Assert(graph.Has(ALICE), "alice exists in graph");
	    t.IsEqual<const TrustEdge*>(graph.GetEdgesOutTrimmed(ALICE)[0], &e1, "alice has 1 out edge");
	    t.IsEqual(graph.GetEdgesInTrimmed(ALICE).GetCount(), 0, "alice has 0 in edges");
	    t.Assert(graph.Has(BOB), "bob exists in graph");
	    t.IsEqual(graph.GetEdgesOutTrimmed(BOB).GetCount(), 0, "bob has 0 out edges");
	    t.IsEqual<const TrustEdge*>(graph.GetEdgesInTrimmed(BOB)[0], &e1, "bob has 1 in edge");
	    t.End();
	});
	
	test("adding edges with depth 3", [](UnitTest& t) {
	    Array<TrustEdge> edges;
	    edges.Add().Set(ALICE, BOB, 0.5);
	    edges.Add().Set(BOB, CAROLE, 0.5);
	    edges.Add().Set(CAROLE, DANIEL, 0.5);
	    
	    Graph graph;
	    graph.Init(PERSON_COUNT, edges);
	
	    t.IsEqual(graph.GetDepth(ALICE, ALICE), 0, "alice has depth 0");
	    t.IsEqual(graph.GetDepth(ALICE, BOB), 1, "bob has depth 1");
	    t.IsEqual(graph.GetDepth(ALICE, CAROLE), 2, "carole has depth 2");
	    t.IsEqual(graph.GetDepth(ALICE, DANIEL), 3, "daniel has depth 3");
	    t.IsEqual(graph.GetDepth(ALICE, MARJORY), -1, "marjory is not in the graph");
	    t.End();
	});
	
	test("adding multiple out edges", [](UnitTest& t) {
	    Array<TrustEdge> edges;
	    edges.Add().Set(ALICE, BOB, 0.5);
	    edges.Add().Set(ALICE, CAROLE, 0.5);
	
	    Graph graph;
	    graph.Init(PERSON_COUNT, edges);
	
	    t.IsEqual(graph.GetEdgesOutTrimmed(ALICE).GetCount(), 2, "alice has 2 out edges");
	    t.IsEqual(graph.GetEdgesOutTrimmed(BOB).GetCount(), 0, "bob has 0 out edges");
	    t.IsEqual(graph.GetEdgesInTrimmed(BOB).GetCount(), 1, "bob has 1 in edge");
	    t.IsEqual(graph.GetEdgesOutTrimmed(CAROLE).GetCount(), 0, "carole has 0 in edge");
	    t.IsEqual(graph.GetEdgesInTrimmed(CAROLE).GetCount(), 1, "carole has 1 in edge");
	    t.End();
	});
	
	
	test("node should have same depth regardless of processing of edges", [](UnitTest& t) {
	    Array<TrustEdge> edges;
	    edges.Add().Set(CAROLE, DANIEL, 0.5);
	    edges.Add().Set(BOB, CAROLE, 0.5);
	    edges.Add().Set(ALICE, BOB, 0.5);
	    edges.Add().Set(ALICE, BEA, 0.5);
	    
	    Graph graph;
	    graph.Init(PERSON_COUNT, edges);
	
	    t.IsEqual(graph.GetDepth(ALICE, ALICE), 0, "alice has depth 0");
	    t.IsEqual(graph.GetDepth(ALICE, BOB), 1, "bob has depth 1");
	    t.IsEqual(graph.GetDepth(ALICE, BEA), 1, "bea has depth 1");
	    t.IsEqual(graph.GetDepth(ALICE, CAROLE), 2, "carole has depth 2");
	    t.IsEqual(graph.GetDepth(ALICE, DANIEL), 3, "daniel has depth 3");
	    t.IsEqual(graph.GetDepth(ALICE, MARJORY), -1, "marjory is not in the graph");
	    t.End();
	});
	
	test("replace edgepair with new weight", [](UnitTest& t) {
	    Array<TrustEdge> edges, updated_edge;
	    edges.Add().Set(ALICE, BOB, 0.5);
	    updated_edge.Add().Set(ALICE, BOB, 1.0);
	    
	    Graph graph;
	    graph.Init(PERSON_COUNT, edges);
	    const auto& eout0 = graph.GetEdgesOutTrimmed(ALICE);
	    t.IsEqual(eout0.GetCount(), 1, "alice only has 1 out edge");
	    t.IsEqual(eout0[0]->weight, 0.5f, "initial out edge has weight 0.5");
	    t.IsEqual(eout0[0]->dst, (int)BOB, "edge is from alice to bob");
	
	    graph.Init(PERSON_COUNT, updated_edge);
	    const auto& eout1 = graph.GetEdgesOutTrimmed(ALICE);
	    t.IsEqual(eout1.GetCount(), 1, "alice only has 1 out edge");
	    t.IsEqual(eout1[0]->weight, 1.0f, "updated out edge has weight 1.0");
	    t.IsEqual(eout1[0]->dst, (int)BOB, "edge is from alice to bob");
	    t.End();
	});
	
	DUMPC(test.GetPasses());
	DUMPC(test.GetFails());
	ASSERT(test.GetFails().IsEmpty());
}