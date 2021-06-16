#include <Local/Local.h>
using namespace UPP;


void OrderedLinkedListTest() {
	struct Payload {
		int i;
		dword key;
	};
	Array<Payload> payload;
	
	OrderedLinkedList l;
	
	dword min = 10, max = 1000, step = 10;
	dword range = max - min;
	
	
	l.Init(min, max, step);
	
	payload.SetCount(100);
	for(int i = 0; i < payload.GetCount(); i++) {
		Payload& pl = payload[i];
		pl.i = i;
		pl.key = min + Random(range + 1);
		
		l.Add(pl.key, i);
	}
	
	LOG("Begins:");
	for(int i = 0; i < l.begins.GetCount(); i++) {
		OrderedLinkedItem* begin = l.begins[i];
		if (begin) {
			LOG(i << ": " << (int)begin->key << " --> " << (int)begin->value);
		}
	}
	LOG("");
	
	
	LOG("All:");
	int i = 0;
	OrderedLinkedItem* it = l.begin;
	while(1) {
		LOG(i++ << ": " << (int)it->key << " --> " << (int)it->value);
		if (it == l.end) break;
		it = it->next;
	}
	LOG("Min key: " << (int)l.GetMinKey() << " Max key: " << (int)l.GetMaxKey());
	LOG("");
	
	int removed = 0;
	for(int i = payload.GetCount() / 2; i < payload.GetCount(); i++) {
		Payload& pl = payload[i];
		l.Remove(pl.key, i);
		removed++;
	}
	ASSERT(l.count == payload.GetCount() - removed);
	
	LOG("After removed");
	i = 0;
	it = l.begin;
	while(1) {
		LOG(i++ << ": " << (int)it->key << " --> " << (int)it->value);
		if (it == l.end) break;
		it = it->next;
	}
	LOG("Min key: " << (int)l.GetMinKey() << " Max key: " << (int)l.GetMaxKey());
	LOG("");
	
}



CONSOLE_APP_MAIN {
	OrderedLinkedListTest();
}

