#include <TrustLib/TrustLib.h>

void TrustNetTest() {
	using namespace UPP;
	using namespace TS;
	
	enum {
		OLIVER,
		JACK,
		HARRY,
		JACOB,
		CHARLIE,
		THOMAS,
		GEORGE,
		OSCAR,
		
		EMMA,
		OLIVIA,
		AVA,
		SOPHIA,
		ISABELLA,
		MIA,
		EMILY,
		
		NAME_COUNT
	};
	const char* names[] = {
		"Oliver", "Jack", "Harry", "Jacob", "Charlie", "Thomas", "George", "Oscar",
		"Emma", "Olivia", "Ava", "Sophia", "Isabella", "Mia", "Emily"
	};
	
	// Test 1
	{
		LOG("Test 1");
		Index<int> distrusted;
		Vector<TrustEdge> trusted_list;
		
		distrusted.Add(OLIVIA);
		distrusted.Add(HARRY);
		
		trusted_list.Add().Set(AVA, OLIVER, 0.25);
		trusted_list.Add().Set(AVA, EMMA, 0.8);
		trusted_list.Add().Set(EMMA, JACK, 0.8);
		trusted_list.Add().Set(JACK, EMMA, 0.8);
		trusted_list.Add().Set(EMMA, AVA, 0.8);
		trusted_list.Add().Set(OLIVER, OLIVIA, 0.8);
		trusted_list.Add().Set(OLIVIA, HARRY, 1.0);
		trusted_list.Add().Set(HARRY, OLIVIA, 1.0);
		
		TrustNet trust;
		trust.Load(0.5, NAME_COUNT, AVA, trusted_list, distrusted);
		
		RankingMap res = trust.GetMostTrusted();
		DUMPM(res);
		LOG("The most trusted of " << names[trust.GetRoot()] << " is " << names[res.GetKey(0)]);
		for(int i = 0; i < res.GetCount(); i++) {
			LOG("\t" << names[res.GetKey(i)] << " trust score: " << res[i]);
		}
		LOG("\n\n\n");
	}
	
	// Test 2
	{
		LOG("Test 2");
		Index<int> distrusted;
		Vector<TrustEdge> trusted_list;
		
		distrusted.Add(EMILY);
		distrusted.Add(OLIVER);
		
        trusted_list.Add().Set(EMMA, OLIVIA, 0.75);
        trusted_list.Add().Set(EMMA, JACK, 0.75);
        trusted_list.Add().Set(EMMA, HARRY, 0.25);
        trusted_list.Add().Set(EMMA, JACOB, 0.75);
        trusted_list.Add().Set(EMMA, AVA, 0.75);
        trusted_list.Add().Set(EMMA, CHARLIE, 0.75);
        trusted_list.Add().Set(EMMA, SOPHIA, 0.50);
        trusted_list.Add().Set(EMMA, THOMAS, 0.50);
        trusted_list.Add().Set(EMMA, GEORGE, 0.25);
        trusted_list.Add().Set(EMMA, OSCAR, 0.50);
        trusted_list.Add().Set(JACK, EMMA, 0.75);
        trusted_list.Add().Set(JACK, JACOB, 0.75);
        trusted_list.Add().Set(JACK, OSCAR, 0.75);
        trusted_list.Add().Set(JACK, THOMAS, 0.75);
        trusted_list.Add().Set(JACK, ISABELLA, 0);
        trusted_list.Add().Set(SOPHIA, JACK, 0.75);
        trusted_list.Add().Set(SOPHIA, JACOB, 0.75);
        trusted_list.Add().Set(SOPHIA, OSCAR, 0.75);
        trusted_list.Add().Set(SOPHIA, THOMAS, 0.75);
        trusted_list.Add().Set(SOPHIA, HARRY, 0.75);
        trusted_list.Add().Set(SOPHIA, EMMA, 0.50);
        trusted_list.Add().Set(SOPHIA, MIA, 0.50);
        trusted_list.Add().Set(MIA, JACOB, 0.75);
        trusted_list.Add().Set(MIA, ISABELLA, 0);
        trusted_list.Add().Set(THOMAS, OSCAR, 0.75);
        trusted_list.Add().Set(THOMAS, JACK, 0.75);
        trusted_list.Add().Set(THOMAS, JACOB, 0.75);
        trusted_list.Add().Set(OSCAR, THOMAS, 0.75);
        trusted_list.Add().Set(JACOB, AVA, 0.75);
        trusted_list.Add().Set(JACOB, CHARLIE, 0.75);
        trusted_list.Add().Set(JACOB, EMMA, 0.50);
        trusted_list.Add().Set(JACOB, MIA, 0.25);
        trusted_list.Add().Set(OLIVIA, EMMA, 0.75);
        trusted_list.Add().Set(OLIVIA, JACOB, 0.75);
        trusted_list.Add().Set(OLIVIA, GEORGE, 0.75);
        trusted_list.Add().Set(OLIVIA, AVA, 0.75);
        trusted_list.Add().Set(OLIVIA, CHARLIE, 0.75);
        trusted_list.Add().Set(HARRY, JACOB, 0.75);
        trusted_list.Add().Set(HARRY, OSCAR, 0.75);
        trusted_list.Add().Set(HARRY, CHARLIE, 0.75);
        trusted_list.Add().Set(HARRY, SOPHIA, 0.1);
        trusted_list.Add().Set(CHARLIE, AVA, 0.75);
        trusted_list.Add().Set(CHARLIE, JACOB, 0.50);
        trusted_list.Add().Set(AVA, JACOB, 0.75);
        trusted_list.Add().Set(AVA, CHARLIE, 0.75);
        trusted_list.Add().Set(JACOB, EMILY, 0.25);
        trusted_list.Add().Set(EMILY, OLIVER, 0.25);
		
		TrustNet trust;
		trust.Load(0.5, NAME_COUNT, AVA, trusted_list, distrusted);
		
		RankingMap res = trust.GetMostTrusted();
		DUMPM(res);
		LOG("The most trusted of " << names[trust.GetRoot()] << " is " << names[res.GetKey(0)]);
		for(int i = 0; i < res.GetCount(); i++) {
			LOG("\t" << names[res.GetKey(i)] << " trust score: " << res[i]);
		}
		LOG("\n\n\n");
	}
		
}


