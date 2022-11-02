#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN



void OrderedLinkedList::Clear() {
	items.SetCount(0);
	begins.SetCount(0);
	unused.SetCount(0);
	begin = NULL;
	end = NULL;
	min = 0, max = 0, step = 0;
	total_added = 0;
	count = 0;
}

void OrderedLinkedList::Zero() {
	lock.Enter();
	
	for(auto& i : begins) i = NULL;
	unused.SetCount(items.GetCount());
	Item** it = unused.Begin();
	for(Item& i : items)
		*it++ = &i;
	begin = NULL;
	end = NULL;
	total_added = 0;
	count = 0;
	
	lock.Leave();
}

void OrderedLinkedList::Init(dword min, dword max, dword step) {
	Clear();
	if (max <= min || !step)
		Panic(Format("Invalid OrderedLinkedList usage: min=%d, max=%d, step=%d", (int)min, (int)max, (int)step));
	this->min = min;
	this->max = max;
	this->step = step;
	dword count = (max - min) / step + 1;
	if (!count || count > 10000000)
		Panic(Format("Invalid OrderedLinkedList usage: count=%d", (int)count));
	begins.SetCount(count, NULL);
}

OrderedLinkedItem& OrderedLinkedList::Alloc() {
	if (unused.GetCount())
		return *unused.Pop();
	else
		return items.Add();
}

void OrderedLinkedList::Free(Item* t) {
	unused.Add(t);
}

int OrderedLinkedList::CountDistanceNotZero(Item* a, Item* b) {
	bool do_next = true;;
	if (b->key < a->key)
		do_next = false;
	for(int i = 0; i < 2; i++) {
		if (i) do_next = !do_next;
		Item* it = a;
		int dist = 0;
		while (true) {
			if (dist > 0 && it == b)
				return dist;
			if (do_next) {
				if (it->next)
					it = it->next;
				else
					break;
			}
			else {
				if (it->prev)
					it = it->prev;
				else
					break;
			}
			dist++;
		}
	}
	return -1;
}

bool OrderedLinkedList::IsOrdered() const {
	Item* it = begin;
	dword key = min;
	while (it != end) {
		if (it->key < key)
			return false;
		key = it->key;
		it = it->next;
	}
	return true;
}

void OrderedLinkedList::InsertBetween(Item* it, Item* prev, Item* next) {
	it->prev = prev;
	it->next = next;
	//
	if (!prev) {
		begin = it;
		if (next) {
			ASSERT(next->prev != it);
			next->prev = it;
		}
		else
			end = it;
	}
	else if (!next) {
		end = it;
		if (prev) {
			ASSERT(prev->next != it);
			prev->next = it;
		}
		else
			begin = it;
	}
	else {
		ASSERT(prev->next != it);
		ASSERT(next->prev != it);
		prev->next = it;
		next->prev = it;
	}
	//ASSERT(IsOrdered());
}

void OrderedLinkedList::RemoveBetween(Item* it) {
	//ASSERT(IsOrdered());
	if (it->prev && it->next) {
		it->next->prev = it->prev;
		it->prev->next = it->next;
	}
	else if (it->prev) {
		end = it->prev;
		it->prev->next = NULL;
	}
	else if (it->next) {
		begin = it->next;
		it->next->prev = NULL;
	}
	else {
		begin = NULL;
		end = NULL;
	}
	it->prev = NULL;
	it->next = NULL;
	//ASSERT(CountDistanceNotZero(it, it) < 0);
}

OrderedLinkedItem* OrderedLinkedList::FindWhereNext(dword key, Item* prev) {
	while (prev->next) {
		if (prev->next->key > key)
			break;
		prev = prev->next;
	}
	return prev;
}

OrderedLinkedItem* OrderedLinkedList::FindClosest(dword begin_i, dword key) {
	int dec = begin_i - 1;
	int inc = begin_i + 1;
	while (true) {
		bool part_succ = false;
		if (dec >= 0) {
			Item* it = begins[dec];
			if (it) {
				while (it->next && it->next->key < key)
					it = it->next;
				return it;
			}
			dec--;
			part_succ = true;
		}
		if (inc < begins.GetCount()) {
			Item* it = begins[inc];
			if (it)
				return it;
			inc++;
			part_succ = true;
		}
		if (!part_succ) break;
	}
	return NULL;
}

dword OrderedLinkedList::GetBeginPos(dword key) {
	if (key < min || key >= max + step)
		Panic(Format("Invalid key %d (not between %d and %d)", (int)key, (int)min, (int)max));
	dword begin_i = (key - min) / step;
	return begin_i;
}

void OrderedLinkedList::Add(dword key, dword value) {
	lock.Enter();
	Item& it = Alloc();
	it.key = key;
	it.value = value;
	dword begin_i = GetBeginPos(key);
	Item*& key_begin = begins[begin_i];
	if (key_begin) {
		if (key < key_begin->key) {
			InsertBetween(&it, key_begin->prev, key_begin);
			key_begin = &it;
		}
		else {
			Item* prev = FindWhereNext(key, key_begin);
			ASSERT(prev->key <= key);
			InsertBetween(&it, prev, prev->next);
		}
	}
	else {
		key_begin = &it;
		Item* closest = FindClosest(begin_i, key);
		if (!closest)
			InsertBetween(&it, NULL, NULL);
		else {
			if (closest->key <= key)
				InsertBetween(&it, closest, closest->next);
			else
				InsertBetween(&it, closest->prev, closest);
		}
	}
	total_added++;
	count++;
	
	lock.Leave();
}

void OrderedLinkedList::Remove(dword key, dword value) {
	if (key < min || key >= max + step)
		Panic(Format("Invalid key %d (not between %d and %d)", (int)key, (int)min, (int)max));
	
	lock.Enter();
	dword begin_i = GetBeginPos(key);
	Item* it = NULL;
	Item*& key_begin = begins[begin_i];
	ASSERT(key_begin);
	if (key_begin->value == value) {
		it = key_begin;
		if (key_begin->next) {
			dword next_begin_i = GetBeginPos(key_begin->next->key);
			if (begin_i == next_begin_i)
				key_begin = key_begin->next;
			else
				key_begin = NULL;
		}
		else key_begin = NULL;
	}
	else {
		Item* find = key_begin->next;
		while (find && find->value != value && find->next)
			find = find->next;
		ASSERT(find && find->value == value);
		it = find;
	}
	ASSERT(it && it->value == value);
	if (it && it->value == value) {
		RemoveBetween(it);
		Free(it);
		count--;
	}
	
	lock.Leave();
}

void OrderedLinkedList::Remove(Item* it) {
	if (!it)
		return;
	lock.Enter();
	RemoveUnsafe(it);
	lock.Leave();
}

void OrderedLinkedList::RemoveUnsafe(Item* it) {
	dword begin_i = GetBeginPos(it->key);
	Item*& key_begin = begins[begin_i];
	ASSERT(key_begin);
	if (key_begin == it) {
		if (key_begin->next) {
			dword next_begin_i = GetBeginPos(key_begin->next->key);
			if (begin_i == next_begin_i)
				key_begin = key_begin->next;
			else
				key_begin = NULL;
		}
		else key_begin = NULL;
	}
	RemoveBetween(it);
	count--;
	Free(it);
}

bool OrderedLinkedList::PopBegin(dword& key, dword& value) {
	bool succ = false;
	lock.Enter();
	if (begin) {
		Item* it = begin;
		key   = it->key;
		value = it->value;
		RemoveUnsafe(it);
		succ = true;
	}
	lock.Leave();
	return succ;
}



NAMESPACE_TOPSIDE_END
