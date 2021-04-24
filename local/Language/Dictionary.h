#ifndef _Language_Dictionary_h_
#define _Language_Dictionary_h_

NAMESPACE_LANGUAGE_BEGIN

class Dictionary : Moveable<Dictionary> {
	typedef Tuple<int, int> ChrCode;
	
	Vector<Vector<ChrCode> > code;
	
	// Temporary
	int cur_code = 0, cur_dir = 0;
	bool is_search_fail = false;
	
public:
	Dictionary();
	
	void Clear() {code.Clear(); code.Add();}
	
	template <class T>
	void Add(const T& key, int result_code) {
		ASSERT(result_code >= 0);
		BeginSearch();
		for(int i = 0; i <= key.GetCount(); i++) {
			bool is_last = i == key.GetCount();
			int chr = !is_last ? key[i] : 0;
			//ASSERT(chr > 0 || i == key.GetCount());
			int prev_code = cur_code;
			int found = SearchNext(chr);
			if (found == 0) {
				if (!is_last) {
					int new_c_id = code.GetCount();
					Vector<ChrCode>& new_c = code.Add();
					Vector<ChrCode>& c = code[prev_code];
					ChrCode& cc = c.Add();
					cc.a = chr;
					cc.b = new_c_id;
					cur_code = new_c_id;
				} else {
					Vector<ChrCode>& c = code[prev_code];
					ChrCode& cc = c.Add();
					cc.a = chr;
					cc.b = -result_code-1;
					cur_code = -result_code-1;
				}
			}
			else if (found > 0) {
				if (cur_code >= 0) {
					// just continue
				}
				else {
					if (!is_last) {
						int new_c_id = code.GetCount();
						Vector<ChrCode>& new_c = code.Add();
						Vector<ChrCode>& c = code[prev_code];
						ChrCode& cc = c.Add();
						cc.a = chr;
						cc.b = new_c_id;
						cur_code = new_c_id;
					}
					else {
						if (chr != 0)
							Panic("Corrupted dictionary index db");
						Vector<ChrCode>& c = code[prev_code];
						ChrCode& cc = c.Add();
						cc.a = chr;
						cc.b = -result_code-1;
						cur_code = result_code;
					}
				}
			}
			else Panic("Unexpected result");
		}
	}
	
	void Add(const char* key, int result_code) {
		Add(String(key), result_code);
	}
	
	template <class T>
	int Find(const T& key) {
		BeginSearch();
		for(int i = 0; i <= key.GetCount(); i++) {
			int chr = i < key.GetCount() ? key[i] : 0;
			int found = SearchNext(chr);
			if (!found)
				return -1;
		}
		if (cur_code < 0)
			return -cur_code-1;
		return -1;
	}
	
	int Find(const char* key) {return Find(String(key));}
	int GetCurCode() const {return cur_code;}
	int GetEndPoint() const;
	
	void BeginSearch();
	int SearchNext(int chr);
	bool IsSearchFail() const {return is_search_fail;}
	void Dump();
	void AppendEndpoints(Vector<int>& endpoints);
	
	void Serialize(Stream& s) {s % code;}
	
};



template <class T>
class Dict {
	Dictionary d;
	Vector<T> v;
	
public:
	
	T& Get(int a, int b, int c) {
		d.BeginSearch();
		if (!d.SearchNext(a) || !d.SearchNext(b) || !d.SearchNext(c))
			Panic("Dictionary doesn't contain " + Format("%d %d %d", a, b, c));
		int i;
		if (d.GetCurCode() < 0)
			i = -d.GetCurCode()-1;
		else {
			i = d.GetEndPoint();
			if (i == -1)
				Panic("Dictionary doesn't contain " + Format("%d %d %d", a, b, c));
		}
		return v[i];
	}
	
	int GetCount() const {return v.GetCount();}
	
	T& operator[](int i) {return v[i];}
	
};

template <class K1, class K2, class K3, class V>
class DictMap {
	VectorMap<K1, VectorMap<K2, VectorMap<K3, V> > > data;
	
public:
	
	V& Get(const K1& k1, const K2& k2, const K3& k3) {return data.Get(k1).Get(k2).Get(k3);}
	V& GetAdd(const K1& k1, const K2& k2, const K3& k3) {return data.GetAdd(k1).GetAdd(k2).GetAdd(k3);}
	V GetDefault(const K1& k1, const K2& k2, const K3& k3, V def) {
		int i = data.Find(k1);
		if (i < 0) return def;
		auto& v2 = data[i];
		int j = v2.Find(k2);
		if (j < 0) return def;
		auto& v3 = v2[j];
		int k = v3.Find(k3);
		if (k < 0) return def;
		return v3[k];
	}
};




void DictionaryTest();

NAMESPACE_LANGUAGE_END

#endif
