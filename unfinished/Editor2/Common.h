#ifndef _Editor_Common_h_
#define _Editor_Common_h_


template <class T>
class Node : public T {
public:
	
	typedef T ValueType;
	
	typedef Node<T> NodeT;
	typedef const Node<T> ConstNodeT;
	
	typedef typename Array<NodeT>::Iterator Iterator;
	typedef typename Array<NodeT>::ConstIterator ConstIterator;
	
	
private:
	NodeT* parent;
	Array<NodeT> sub;
	
	Vector<NodeT*> links;
	
	NodeT& SetParent(Node& n) {parent = &n; return *this;}
	
public:
	
	void Serialize(Stream& s) {
		T::Serialize(s);
		s % sub;
		if (s.IsLoading()) {
			for(int i = 0; i < sub.GetCount(); i++)
				sub[i].parent = this;
			parent = 0;
		}
	}
	
	hash_t GetHashValue() const {
		CombineHash ch;
		ch << T::GetHashValue() << 1 << GetCount() << 1;
		for(int i = 0; i < sub.GetCount(); i++)
			ch << sub[i].GetHashValue() << (i+2);
		return ch;
	}
	
	Node() : parent(0) {}
	Node(const Node& n) : parent(0)  {
		*this = n;
	}
	Node(const T& n) : parent(0)  {
		T::operator=(n);
	}
	
	NodeT& operator = (const NodeT& n) {
		T::operator=(n);
		sub <<= n.sub;
		for(int i = 0; i < sub.GetCount(); i++)
			sub[i].parent = this;
		return *this;
	}
	
	virtual NodeT* GetNode() {return this;}
	
	int GetDepth() {NodeT* ptr = this; for(int i = 0;; i++) {ptr = ptr->parent; if (!ptr) return i;}}
	NodeT* GetParent() const {return parent;}
	void RefreshParent() {
		for(int i = 0; i < sub.GetCount(); i++)
			sub[i].SetParent(*this).RefreshParent();
	}
	Vector<int> GetPosition() const {
		Vector<int> out;
		const NodeT* ptr = parent;
		const NodeT* chk = this;
		while (ptr) {
			int count = ptr->GetCount();
			int pos = -1;
			for(int i = 0; i < count; i++) {
				const NodeT* iptr = &(*ptr)[i];
				if (iptr == chk) {
					pos = i; break;
				}
			}
			ASSERT(pos >= 0);
			out.Insert(0, pos);
			chk = ptr;
			ptr = ptr->parent;
		}
		return out;
	}
	
	NodeT& Seek(const Vector<int>& pos) {
		NodeT* ptr = this;
		for(int i = 0; i < pos.GetCount(); i++) {
			ptr = &ptr->At(pos[i]);
		}
		return *ptr;
	}
	
	void SetData(const T& value) {T::operator=(value);}
	T& GetData() {return *this;}
	const T& GetData() const {return *this;}
	
	NodeT& operator[] (int i) {return sub[i];}
	ConstNodeT& operator[] (int i) const {return sub[i];}
	NodeT& At(int i) {return sub.At(i);}
	ConstNodeT& At(int i) const {return sub[i];}
	
	int GetCount() const {return sub.GetCount();}
	void Remove(int i) {sub.Remove(i);}
	NodeT& Add() {return sub.Add().SetParent(*this);}
	NodeT& Add(const Node& n) {return sub.Add(n).SetParent(*this);}
	NodeT& Add(const T& n) {return sub.Add(new NodeT(n)).SetParent(*this);}
	NodeT& Insert(int pos) {return sub.Insert(pos).SetParent(*this);}
	NodeT& Insert(int pos, const T& n) {return sub.Insert(pos, new NodeT(n)).SetParent(*this);}
	void SetCount(int n) {sub.SetCount(n);}
	void Clear() {sub.Clear();}
	
	int GetLinkCount() {return links.GetCount() + sub.GetCount();}
	void AddLink(NodeT& n) {
		for(int i = 0; i < links.GetCount(); i++) {
			if ((long)&links[i] == (long)&n)
				return;
		}
		links.Add(&n);}
	NodeT& AtLink(int i) {if (i < links.GetCount()) return *links[i]; else return sub[i-links.GetCount()];}
	
	String AsString(int indent=0) {
		String s;
		for(int i = 0; i < indent; i++)
			s += "-";
		s += ": " + ::AsString(*(T*)this) + "\n";
		for(int i = 0; i < sub.GetCount(); i++) {
			s += sub[i].AsString(indent+1);
		}
		return s;
	}
	
	
	
	
	class IteratorDeep {
		friend class Node<T>;
		Iterator begin;
		Vector<NodeT*> cur;
		Vector<int> pos;
	protected:
		
		IteratorDeep(NodeT* cur) {
			this->cur.Add(cur);
			pos.Add(0);
		}
		
		IteratorDeep(const NodeT* cur) {
			this->cur.Add((NodeT*)cur);
			pos.Add(0);
		}
		
	public:
		IteratorDeep(const IteratorDeep& it) {
			*this = it;
		}
		IteratorDeep& operator = (const IteratorDeep& it) {
			begin = it.begin;
			cur <<= it.cur;
			pos <<= it.pos;
			return *this;
		}
		int GetDepth() {return pos.GetCount();}
		int GetPos() {return pos[pos.GetCount()-1];}
		int64 GetCurrentAddr() {return (int64)cur[cur.GetCount() - 1];}
		
		bool IsEnd() const {return pos.GetCount() == 1 && pos[0] == 1;}
		bool operator == (IteratorDeep& it) {return GetCurrentAddr() == it.GetCurrentAddr();}
		bool operator != (IteratorDeep& it) {return !(*this == it);}
		void operator ++(int i) {
			#define LASTPOS pos[pos.GetCount()-1]
			#define LASTCUR cur[cur.GetCount()-1]
			#define SECLASTCUR cur[cur.GetCount()-2]
			#define ADDPOS pos[pos.GetCount()-1]++
			#define ADDCUR LASTCUR = &SECLASTCUR->At(LASTPOS)
			#define REMLASTPOS pos.Remove(pos.GetCount()-1)
			#define REMLASTCUR cur.Remove(cur.GetCount()-1)
			//String s; for(int i = 0; i < pos.GetCount(); i++) s << " " << pos[i]; LOG("+++ " << s);
			
			if (pos.GetCount() == 1 && pos[0] < 0) {pos[0]++; return;}
			if (pos.GetCount() == 1 && pos[0] == 1) return; // at end
			
			if (LASTCUR->GetCount()) {
				pos.Add(0);
				cur.Add(&LASTCUR->At(0));
			} 
			else if (pos.GetCount() == 1) {
				pos[0] = 1; // at end
			}
			else {
				while (1) {
					if (LASTPOS + 1 < SECLASTCUR->GetCount()) {
						ADDPOS;
						ADDCUR;
						break;
					} else {
						REMLASTPOS;
						REMLASTCUR;
						if (pos.GetCount() <= 1) {
							pos.SetCount(1);
							pos[0] = 1;
							break;
						}
					}
				}
			}
		}
		void IncNotDeep() {
			if (LASTCUR->GetCount()) {
				while (1) {
					if (cur.GetCount() >= 2 && LASTPOS + 1 < SECLASTCUR->GetCount()) {
						ADDPOS;
						ADDCUR;
						break;
					} else {
						REMLASTPOS;
						REMLASTCUR;
						if (pos.GetCount() <= 1) {
							pos.SetCount(1);
							pos[0] = 1;
							break;
						}
					}
				}
			} 
			else operator++(1);
		}
		void DecToParent() {
			pos.Remove(pos.GetCount()-1);
			cur.Remove(cur.GetCount()-1);
		}
		
		operator NodeT*() {
			if (pos.GetCount() && pos[0] == 1) return 0;
			return LASTCUR;
		}
		
		NodeT* operator->() {
			if (pos.GetCount() && pos[0] == 1) return 0;
			return LASTCUR;
		}
		
		NodeT& operator*() {
			//if (pos.GetCount() && pos[0] == 1) throw Error("Iterator at end");
			return *LASTCUR;
		}
		
		const NodeT& operator*() const {return *LASTCUR;}
		
		NodeT* Higher() {
			if (cur.GetCount() <= 1) return 0;
			return cur[cur.GetCount()-2];
		}
	};
	
	
	IteratorDeep 		BeginDeep() { return IteratorDeep(this);}
	const IteratorDeep 	BeginDeep() const { return IteratorDeep(this);}
	Iterator 			Begin() { return sub.Begin(); }
	Iterator 			End() { return sub.End(); }
		
};



typedef Node<Value> NodeValue;

template <class T>
T GenerateTree(int total, int branching_low, int branching_high, Callback1<T*> set_value) {
	T root;
	Vector<T*> next_level;
	
	next_level.Add(&root);
	
	int branching_range = branching_high - branching_low + 1;
	
	int count = 0;
	while (count < total) {
		Vector<T*> this_level;
		this_level <<= next_level;
		next_level.Clear();
		for(int i = 0; i < this_level.GetCount(); i++) {
			T& n = *this_level[i];
			int remaining = total-count;
			if (remaining <= 0) break;
			int sub_node_count = branching_low + Random(branching_range);
			if (sub_node_count > remaining) sub_node_count = remaining;
			n.SetCount(sub_node_count);
			count += sub_node_count;
			for(int j = 0; j < sub_node_count; j++) {
				T* ptr = &n[j];
				next_level.Add(ptr);
				set_value(ptr);
			}
		}
	}
	
	return root;
}

#endif
