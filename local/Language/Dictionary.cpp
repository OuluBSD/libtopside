#include "Language.h"


NAMESPACE_LANGUAGE_BEGIN


Dictionary::Dictionary() {
	code.Add();
}

void Dictionary::BeginSearch() {
	cur_code = 0;
	is_search_fail = false;
}

int Dictionary::SearchNext(int chr) {
	is_search_fail = true;
	if (cur_code < 0) {
		return 0;
	}
	const Vector<ChrCode>& c = code[cur_code];
	int count = 0;
	for(int i = 0; i < c.GetCount(); i++) {
		const ChrCode& cc = c[i];
		if (cc.a == chr) {
			if (!count || cc.b >= 0) {
				is_search_fail = false;
				cur_code = cc.b;
			}
			count++;
		}
	}
	return count;
}

void Dictionary::AppendEndpoints(Vector<int>& endpoints) {
	if (cur_code < 0) return;
	const Vector<ChrCode>& c = code[cur_code];
	for(int i = 0; i < c.GetCount(); i++) {
		const ChrCode& cc = c[i];
		if (cc.a == 0 && cc.b < 0) {
			endpoints.Add(-cc.b-1);
		}
	}
}

int Dictionary::GetEndPoint() const {
	if (cur_code < 0) return - 1;
	const Vector<ChrCode>& c = code[cur_code];
	for(int i = 0; i < c.GetCount(); i++) {
		const ChrCode& cc = c[i];
		if (cc.a == 0 && cc.b < 0)
			return -cc.b-1;
	}
	return -1;
}

void Dictionary::Dump() {
	DUMPCC(code);
}








void DictionaryTest() {
	Dictionary d;
	d.Add("a", 0);
	d.Add("a", 1);
	d.Add("ab", 2);
	d.Add("ab", 3);
	d.Add("cd", 4);
	d.Dump();
	ASSERT(d.Find("a") == 0);
	ASSERT(d.Find("ab") == 2);
	ASSERT(d.Find("cd") == 4);
	
	Vector<int> endpoints;
	d.BeginSearch();
	d.SearchNext('a');
	d.AppendEndpoints(endpoints);
	ASSERT(endpoints.GetCount() == 2 && endpoints[0] == 0 && endpoints[1] == 1);
	
	endpoints.Clear();
	d.Clear();
	
	Vector<int> in;
	in.Add(0);
	d.Add(in, 0);
	d.Add(in, 1);
	in.Add(0);
	d.Add(in, 3);
	d.Add(in, 4);
	d.Dump();
	
}


NAMESPACE_LANGUAGE_END
