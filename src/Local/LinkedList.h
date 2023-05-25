#ifndef _Local_LinkedList_h_
#define _Local_LinkedList_h_

NAMESPACE_TOPSIDE_BEGIN





template <class T>
void MemSwap(T& a, T& b) {
	uint8 tmp[sizeof(T)];
	MemoryCopy((void*)tmp, (void*)&a, sizeof(T));
	MemoryCopy((void*)&a, (void*)&b, sizeof(T));
	MemoryCopy((void*)&b, (void*)tmp, sizeof(T));
}


template <class T>
void EndianSwapT(T& o) {
	static const int bytes = sizeof(T);
	static const int bytes_2 = bytes / 2;
	if (bytes_2 > 0) {
		byte* a = (byte*)&o;
		byte* b = a + bytes - 1;
		for(int i = 0; i < bytes_2; i++) {
			byte c = *a;
			*a++ = *b;
			*b-- = c;
		}
	}
}


template <class T>
class LinkedList {
	
	struct Item {
		Item* prev = 0;
		Item* next = 0;
		T value;
		
		Item() {}
		Item(const Item& i) : prev(i.prev), next(i.next), value(i.value) {}
	};
	
	typedef RecyclerPool<Item> Rec;
	static inline Rec& GetRecyclerPool() {MAKE_STATIC(Rec, r); return r;}
	
	Item* first = 0;
	Item* last = 0;
	int count = 0;
	
public:
	typedef LinkedList CLASSNAME;
	using ElPtr = Item*;
	
	class Iterator {
		Item* it = 0;
		
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& i) {this->it = i.it; i.it = 0;}
		Iterator(const Iterator& i) : it(i.it) {}
		void	Clear() {it = 0;}
		Item*	GetItem() const {return it;}
		bool	IsEmpty() const {return it == 0;}
		T*   operator->() {ASSERT(it); return &it->value;}
		T&   operator*() const {ASSERT(it); return it->value;}
		void operator=(const Iterator& i) {Clear(); it = i.it;}
		bool operator==(const Iterator& i) const {return i.it == it;}
		bool operator!=(const Iterator& i) const {return i.it != it;}
		void operator++() {if (it) it = it->next;}
		void operator--() {if (it) it = it->prev;}
		T&   operator()() const {ASSERT(it); return it->value;}
		T&   Get() const {ASSERT(it); return it->value;}
		operator T*() const {return &it->value;}
		operator bool() const {return it;}
		ElPtr GetElPtr() const {return it;}
	};
	
	struct RefGet {
		Item* p = 0;
		RefGet(ElPtr it) : p(it) {}
		T& operator()() {return p->value;}
	};
	
	
	LinkedList() {}
	LinkedList(const LinkedList& l) = delete;
	LinkedList(LinkedList&& l) {Swap(first,l.first); Swap(last,l.last); Swap(count,l.count);}
	~LinkedList() {Clear();}
	
	
	T& At(int i) {
		int j = 0;
		for(Iterator it = begin(); it; ++it, ++j)
			if (j == i)
				return *it;
		ASSERT(0);
		THROW(Exc("Position not found in LinkedList: " + IntStr(i)));
	}
	
	const T& At(int i) const {
		int j = 0;
		for(Iterator it = begin(); it; ++it, ++j)
			if (j == i)
				return *it;
		ASSERT(0);
		THROW(Exc("Position not found in LinkedList: " + IntStr(i)));
	}
	
	T& First() {return first->value;}
	const T& First() const {return first->value;}
	T PopFirst() {if (!first) return Null; T o = First(); RemoveFirst(); return o;}
	
	T& Top() {return last->value;}
	const T& Top() const {return last->value;}
	
	Item* AddItem() {
		Item* it = GetRecyclerPool().New();
		if (!first) {
			last = first = it;
			first->prev = 0;
			first->next = 0;
		}
		else {
			last->next = it;
			it->prev = last;
			last = it;
		}
		++count;
		return it;
	}
	Item* AddFirstItem() {
		Item* it = GetRecyclerPool().New();
		if (!first) {
			last = first = it;
			first->prev = 0;
			first->next = 0;
		}
		else {
			first->prev = it;
			it->next = first;
			first = it;
		}
		++count;
		return it;
	}
	T& Add() {return AddItem()->value;}
	T& Add(const T& o) {T& r = AddItem()->value; r = o; return r;}
	T& AddFirst() {return AddFirstItem()->value;}
	T& AddFirst(const T& o) {T& r = AddFirstItem()->value; r = o; return r;}
	int GetCount() const {return count;}
	bool IsEmpty() const {return count == 0;}
	bool IsFilled() const {return count != 0;}
	operator bool() const {return count > 0;}
	
	void SetCount(int i) {
		if (i < 0) return;
		int diff = i - GetCount();
		if (!diff) return;
		if (diff > 0) {
			for(int i = 0; i < diff; i++)
				Add();
		}
		else {
			diff = -diff;
			RemoveLast(diff);
		}
	}
	void RemoveFirst(int count=1) {
		if (!count) return;
		ASSERT(count > 0 && count <= this->count);
		count = std::min(count, this->count);
		if (count == this->count)
			Clear();
		else {
			Item* it = first;
			for(int i = 0; i < count; i++)
				it = it->next;
			Item* last_rm = it->prev;
			it->prev = 0;
			this->count -= count;
			first = it;
			it = last_rm;
			while (it) {
				last_rm = it->prev;
				GetRecyclerPool().Return(it);
				it = last_rm;
			}
		}
	}
	void RemoveLast(int count=1) {
		if (!count) return;
		ASSERT(count > 0 && count <= this->count);
		count = std::min(count, this->count);
		if (count == this->count)
			Clear();
		else {
			Item* it = last;
			for(int i = 0; i < count; i++)
				it = it->prev;
			Item* first_rm = it->next;
			it->next = 0;
			this->count -= count;
			last = it;
			it = first_rm;
			while (it) {
				first_rm = it->next;
				GetRecyclerPool().Return(it);
				it = first_rm;
			}
		}
	}
	Iterator Remove(const Iterator& iter) {
		Item* item = iter.GetItem();
		Item* in_place = 0;
		if (item->prev) {
			if (item->next) {
				in_place = item->next;
				item->prev->next = item->next;
				item->next->prev = item->prev;
			}
			else {
				ASSERT(item == last);
				item->prev->next = 0;
				last = item->prev;
			}
		}
		else {
			ASSERT(item == first);
			if (item->next) {
				in_place = item->next;
				item->next->prev = 0;
				first = item->next;
			}
			else {
				ASSERT(item == last);
				first = 0;
				last = 0;
			}
		}
		--count;
		GetRecyclerPool().Return(item);
		return in_place;
	}
	void Reverse() {
		if (IsEmpty())
			return;
		Item* iter = first;
		MemSwap(first, last);
		while (iter) {
			Item* next = iter->next;
			MemSwap(iter->prev, iter->next);
			iter = next;
		}
		ASSERT(first->prev == 0 && last->next == 0);
	}
	void Clear() {
		if (!first) return;
		auto& rec = GetRecyclerPool();
		Item* iter = last;
		while (iter) {
			Item* prev = iter->prev;
			--count;
			if (prev)
				prev->next = 0;
			rec.Return(iter);
			iter = prev;
		}
		first = 0;
		last = 0;
		ASSERT(count == 0);
	}
	Iterator FindIter(const T& k) const {
		Iterator iter = first;
		while (iter) {
			if (*iter == k)
				return iter;
			++iter;
		}
		return Iterator();
	}
	T*       Find(const T& k)       {Iterator iter = FindIter(k); return iter ? (T*)iter : 0;}
	const T* Find(const T& k) const {Iterator iter = FindIter(k); return iter ? (T*)iter : 0;}
	T& FindAdd(const T& k) {
		Iterator iter = FindIter(k);
		return iter ? iter() : Add(k);
	}
	void RemoveKey(const T& k) {
		for(Iterator it = begin(); it;) {
			if (it.Get() == k)
				it = Remove(it);
			else
				++it;
		}
	}
	
	void Append(const LinkedList& l) {
		for (Iterator it = l.begin(); it; ++it)
			Add(it());
	}
	void PickAppend(LinkedList& l) {
		if (!l.first) return;
		if (!first) {
			first = l.first;
			last = l.last;
			count = l.count;
		}
		else {
			last->next = l.first;
			l.first->prev = last;
			last = l.last;
			count += l.count;
		}
		l.first = 0;
		l.last = 0;
		l.count = 0;
	}
	
	void operator=(LinkedList&& l) {Swap(first,l.first); Swap(last,l.last); Swap(count,l.count);}
	void operator<<=(const LinkedList& l) {Clear(); Append(l);}
	
	
	
	Iterator Begin() const		{return Iterator(first);}
	Iterator begin() const		{return Iterator(first);}
	Iterator End() const		{return Iterator();}
	Iterator end() const		{return Iterator();}
	Iterator rbegin() const		{return last ? Iterator(last) : Iterator();}
	Iterator rend() const		{return Iterator();}
	
	Iterator pbegin() const		{return Iterator(first);}
	Iterator pend() const		{return Iterator();}
	Iterator rpbegin() const	{return last ? Iterator(last) : Iterator();}
	Iterator rpend() const		{return Iterator();}
	
};



template <class K, class V>
class LinkedMap {
	LinkedList<K> keys;
	LinkedList<V> values;
	
public:
	typedef typename LinkedList<K>::Iterator KeyIter;
	typedef typename LinkedList<V>::Iterator ValueIter;
	struct Iterator {
		KeyIter key;
		ValueIter value;
		Iterator() {}
		Iterator(KeyIter&& k, ValueIter&& v) : key(std::move(k)), value(std::move(v)) {}
		Iterator(const KeyIter& k, const ValueIter& v) : key(k), value(v) {}
		void operator=(const Iterator& i) {key = i.key; value = i.value;}
		void operator++() {++key; ++value;}
		void operator--() {--key; --value;}
		bool operator==(const Iterator& i) const {return key == i.key;}
		bool operator!=(const Iterator& i) const {return key != i.key;}
		V*   operator->() {return &value();}
		V&   operator*() {return *value;}
		V&   operator()() {return *value;}
		operator bool() const {return key;}
		V& Get() {return value.Get();}
	};
	
	LinkedMap() {}
	~LinkedMap() {Clear();}
	void Clear() {keys.Clear(); values.Clear();}
	
	V& Add(const K& k) {keys.AddItem()->value = k; return values.Add();}
	V& Add(const K& k, const V& v) {V& o = Add(k); o = v; return o;}
	V& GetAdd(const K& k) {
		Iterator it = Find(k);
		if (it)
			return *it;
		return Add(k);
	}
	int GetCount() const {return keys.GetCount();}
	bool IsEmpty() const {return keys.IsEmpty();}
	Iterator Remove(const Iterator& iter) {
		Iterator it;
		it.key		= keys.Remove(iter.key);
		it.value	= values.Remove(iter.value);
		return it;
	}
	
	Iterator Find(const K& key) {
		KeyIter k = keys.begin();
		ValueIter v = values.begin();
		for (;k; ++k, ++v)
			if (*k == key)
				return Iterator(k, v);
		return Iterator();
	}
	void RemoveKey(const K& key) {
		Iterator it = Find(key);
		if (it)
			Remove(it);
	}
	LinkedList<V>& GetValues() {return values;}
	

	Iterator begin()	{return Iterator(keys.begin(), values.begin());}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return Iterator(keys.rbegin(), values.rbegin());}
	Iterator rend()		{return Iterator();}
	
};


NAMESPACE_TOPSIDE_END

#endif
