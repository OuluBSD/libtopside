#ifndef _Local_Index_h_
#define _Local_Index_h_

NAMESPACE_TOPSIDE_BEGIN



template <int I, class K=int, class V=double>
struct FixedTopValueSorter {
	static const int size = I;
	
	K key[size];
	V value[size];
	int count = 0;
	
	
	FixedTopValueSorter() {Reset();}
	void Reset() {
		count = 0;
		for(int i = 0; i < size; i++) {
			value[i] = -DBL_MAX;
			key[i] = -1;
		}
	}
	void Add(const K& key, const V& value) {
		if (value <= this->value[size-1])
			return;
		for(int i = 0; i < size; i++) {
			if (value > this->value[i]) {
				for(int j = size-1; j > i; j--) {
					this->value[j] = this->value[j-1];
					this->key[j]   = this->key[j-1];
				}
				this->value[i] = value;
				this->key[i] = key;
				count = min(count+1, size);
				break;
			}
		}
	}
	void Serialize(Stream& s) {
		for(int i = 0; i < size; i++)
			s % value[i] % key[i];
	}
};

template <class K=int, class V=double>
struct TopValueSorter {
	struct Item : Moveable<Item> {
		K key;
		V value;
		void Serialize(Stream& s) {s % key % value;}
	};
	Vector<Item> items;
	int max_count = -1;
	
	TopValueSorter() {Reset();}
	void Reset() {items.SetCount(0);}
	void Reserve(int i) {items.Reserve(i);}
	void SetMaxCount(int i) {max_count = i;}
	void Add(const K& key, const V& value) {
		int size = items.GetCount();
		Item it {key, value};
		if (!size || value <= items[size-1].value) {
			if (max_count < 0 || (max_count >= 0 && size < max_count))
				items.Add(it);
		}
		else {
			int i = 0;
			for (Item& iter : items) {
				if (value > iter.value) {
					items.Insert(i, it);
					if (size+1 > max_count)
						items.SetCount(max_count);
					break;
				}
				i++;
			}
		}
	}
	void Serialize(Stream& s) {s % items;}
};




struct OrderedLinkedItem {
	typedef OrderedLinkedItem Item;
	
	Item* prev = NULL;
	Item* next = NULL;
	dword value = 0;
	dword key = 0;
	
	
};

/*
	OrderedLinkedList
	- can has many duplicate "key" values, but only single "value" value.
	- e.g.
		- "key" is some measured sorter value, where lower is better
		- "value" is unique identifier
		- by popping the begin pointer, you can process the unique identifier with best sorter
		  value
*/
struct OrderedLinkedList {
	typedef OrderedLinkedItem Item;
	
	Array<Item> items;
	Vector<Item*> begins;
	Vector<Item*> unused;
	Item* begin = NULL, *end = NULL;
	dword min = 0, max = 0, step = 0;
	Mutex lock;
	dword total_added = 0;
	dword count = 0;
	
	
	void Clear();
	void Zero();
	void Init(dword min, dword max, dword step);
	Item& Alloc();
	void Free(Item* t);
	int CountDistanceNotZero(Item* a, Item* b);
	bool IsOrdered() const;
	void InsertBetween(Item* it, Item* prev, Item* next);
	void RemoveBetween(Item* it);
	Item* FindWhereNext(dword key, Item* prev);
	Item* FindClosest(dword begin_i, dword key);
	dword GetBeginPos(dword key);
	void Add(dword key, dword value);
	void Remove(dword key, dword value);
	void Remove(Item* it);
	void RemoveUnsafe(Item* it);
	dword GetMinKey() const {return begin ? begin->key : 0;}
	dword GetMaxKey() const {return   end ?   end->key : 0;}
	bool PopBegin(dword& key, dword& value);
};







struct FastSortedIndex {
	Vector<Vector<int>> data;
	Vector<uint64> value_mask;
	int count = 0;
	int first_data_i = INT_MAX;
	
	void Reserve(int count) {
		if (count > data.GetCount()) {
			data.SetCount(count);
			int value_count = count / 64 + 1;
			value_mask.SetCount(value_count, 0);
		}
	}
	
	void Clear() {
		for(int i = 0; i < data.GetCount(); i++)
			data[i].SetCount(0);
		for(int i = 0; i < value_mask.GetCount(); i++)
			value_mask[i] = 0;
		count = 0;
		first_data_i = INT_MAX;
	}
	
	void Add(int key, int value) {
		Vector<int>& key_vec = data[key];
		if (key_vec.IsEmpty()) {
			int mask_i = key / 64;
			int64 bit_i = key % 64;
			uint64& v = value_mask[mask_i];
			uint64 add = 1LL << bit_i;
			v |= add;
		}
		key_vec.Add(value);
		count++;
		if (key < first_data_i)
			first_data_i = key;
	}
	
	struct Iterator {
		Vector<Vector<int>>* data;
		Vector<uint64>* value_mask;
		int i, data_i, data_vec_i;
		int count;
		
		int* Ptr() {return &(*data)[data_i][data_vec_i];}
		int Value() {
			Vector<int>& v = (*data)[data_i];
			ASSERT(data_vec_i >= 0 && data_vec_i < v.GetCount());
			return v[data_vec_i];
		}
		void operator++(int __) {
			if (data_i >= 0 && data_i < data->GetCount() && data_vec_i+1 < (*data)[data_i].GetCount()) {
				data_vec_i++;
				i++;
				return;
			}
			else {
				data_i++;
				data_vec_i = 0;
				while (data_i < data->GetCount()) {
					int mask_i = data_i / 64;
					int64 bit_i = data_i % 64;
					uint64 m = (*value_mask)[mask_i];
					if (m == 0) {
						data_i = (mask_i+1) * 64;
						continue;
					}
					while (bit_i < 64) {
						if (m & (1LL << bit_i)) {
							i++;
							return;
						}
						bit_i++;
						data_i++;
					}
				}
			}
			i = count;
			data_i = data->GetCount();
			data_vec_i = -1;
		}
		void operator--(int __) {
			if (data_i >= 0 && data_i < data->GetCount() && data_vec_i-1 >= 0) {
				data_vec_i--;
				i--;
				return;
			}
			else {
				data_i--;
				data_vec_i = -1;
				while (data_i >= 0) {
					int mask_i = data_i / 64;
					int64 bit_i = data_i % 64;
					uint64& m = (*value_mask)[mask_i];
					if (m == 0) {
						data_i = (mask_i) * 64 - 1;
						continue;
					}
					while (bit_i >= 0) {
						if (m & (1LL << bit_i)) {
							i--;
							data_vec_i = (*data)[data_i].GetCount()-1;
							return;
						}
						bit_i--;
						data_i--;
					}
				}
			}
			i = -1;
			data_i = -1;
			data_vec_i = -1;
		}
		operator bool() const {return i >= 0 && i < count;}
	};
	
	Iterator Begin() {
		Iterator i;
		i.data = &data;
		i.value_mask = &value_mask;
		i.i = -1; i.data_i = -1; i.data_vec_i = -1; i.count = count;
		i++;
		return i;
	}
	
	Iterator Last() {
		Iterator i;
		i.data = &data;
		i.value_mask = &value_mask;
		i.i = count; i.data_i = data.GetCount(); i.data_vec_i = -1; i.count = count;
		i--;
		return i;
	}
};


NAMESPACE_TOPSIDE_END

#endif
