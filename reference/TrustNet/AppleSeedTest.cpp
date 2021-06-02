#include <TrustLib/TrustLib.h>




void AppleSeedTest() {
	using namespace UPP;
	using namespace TS;
	
	enum {A, B, C, D, E, X, Y, COUNT};
	
	UnitTest test;
	
	test("instantiation should work", [](UnitTest& t) {
	    Array<TrustEdge> trust;
	    int source = A;
	    trust.Add().Set(A, B, 0.80);
	    trust.Add().Set(A, C, 0.80);
	    trust.Add().Set(B, D, 0.80);
	    trust.Add().Set(X, Y, 0.80);
	    RankingMap rankings;
	    AppleSeed(COUNT, source, trust, 200, 0.85, 0.01, rankings, TrustNet::TempGraph());
	    
        t.Assert(rankings.Find(B) >= 0, "node b exists in rankings");
        t.Assert(rankings.Find(C) >= 0, "node c exists in rankings");
        t.Assert(rankings.Find(D) >= 0, "node d exists in rankings");
        t.Assert(rankings.Find(A) < 0, "source should not be in rankings");
        t.Assert(rankings.Find(X) < 0, "node x should not be in rankings");
        t.Assert(rankings.Find(Y) < 0, "node y should not be in rankings");
        t.End();
	});
	
	test("simple one hop, same weights", [](UnitTest& t) {
	    Array<TrustEdge> trust;
	    int source = A;
	    trust.Add().Set(A, B, 0.80);
	    trust.Add().Set(B, C, 0.80);
	    trust.Add().Set(B, D, 0.80);
	    RankingMap rankings;
	    AppleSeed(COUNT, source, trust, 200, 0.85, 0.01, rankings, TrustNet::TempGraph());
	    
        int b_rank = rankings.Find(B);
        int c_rank = rankings.Find(C);
        int d_rank = rankings.Find(D);
        t.Assert(b_rank >= 0, "node b exists in rankings");
        t.Assert(c_rank >= 0, "node b exists in rankings");
        t.Assert(d_rank >= 0, "node b exists in rankings");
        t.Assert(b_rank < c_rank, "node b is higher than c");
        t.Assert(b_rank < d_rank, "node b is higher than d");
        t.End();
	});
	
	test("simple one hop, lower weight", [](UnitTest& t) {
	    Array<TrustEdge> trust;
	    int source = A;
	    trust.Add().Set(A, B, 0.80);
	    trust.Add().Set(B, C, 0.80);
	    trust.Add().Set(B, D, 0.40);
	    RankingMap rankings;
	    AppleSeed(COUNT, source, trust, 200, 0.85, 0.01, rankings, TrustNet::TempGraph());
	    
        int b_rank = rankings.Find(B);
        int c_rank = rankings.Find(C);
        int d_rank = rankings.Find(D);
        t.Assert(b_rank >= 0, "node b exists in rankings");
        t.Assert(b_rank < c_rank, "node b has more energy than c");
        t.Assert(b_rank < d_rank, "node b has more energy than d");
        t.Assert(c_rank < d_rank, "node c has more energy than d");
        t.End();
	});
	
	test("two trustees", [](UnitTest& t) {
	    Array<TrustEdge> trust;
	    int source = A;
	    
	    // a trusts b and c
	    trust.Add().Set(A, B, 0.80);
	    trust.Add().Set(A, C, 0.80);
	
	    // b trusts d and e
	    trust.Add().Set(B, D, 0.80);
	    trust.Add().Set(B, E, 0.80);
	
	    // c also trusts d
	    trust.Add().Set(C, D, 0.80);
	    
	    RankingMap rankings;
	    AppleSeed(COUNT, source, trust, 200, 0.85, 0.01, rankings, TrustNet::TempGraph());
	    
        int d_rank = rankings.Find(D);
        int e_rank = rankings.Find(E);
        t.Assert(d_rank < e_rank, "node d has more energy than e");
        t.End();
	});
	
	DUMPC(test.GetPasses());
	DUMPC(test.GetFails());
	ASSERT(test.GetFails().IsEmpty());
}
