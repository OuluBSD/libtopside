#ifndef _ToolCore_FileClasses_h_
#define _ToolCore_FileClasses_h_


BEGIN_TEXTLIB_NAMESPACE


class IntVectorFile {
	Vector<int> idx;
	String path;
public:
	IntVectorFile() {}
	IntVectorFile(const String& p) {Load(p);}
	IntVectorFile(const String& dir, const String& title) {Load(dir, title);}
	~IntVectorFile() {Store();}
	
	void Load(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".txt"));}
	void Load(const String& path);
	void Store();
	void Add(int s) {idx.Add(s);}
	int operator[](int i) const {return idx[i];}
	int GetCount() const {return idx.GetCount();}
	const Vector<int>& GetValues() const {return idx;}
	void Clear() {idx.Clear();}
	
};

class IntIndexFile {
	Index<int> idx;
	String path;
public:
	IntIndexFile() {}
	IntIndexFile(const String& p) {Load(p);}
	IntIndexFile(const String& dir, const String& title) {Load(dir, title);}
	~IntIndexFile() {Store();}
	
	void Load(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".txt"));}
	void Load(const String& path);
	void Store();
	int FindAdd(int s) {
		int i = idx.Find(s);
		if (i >= 0) return i;
		i = idx.GetCount();
		idx.Add(s);
		return i;
	}
	int Find(int s) const {return idx.Find(s);}
	int operator[](int i) const {return idx[i];}
	int GetCount() const {return idx.GetCount();}
	const Vector<int>& GetKeys() const {return idx.GetKeys();}
	void Clear() {idx.Clear();}
	
};

class IndexFile {
	Index<String> idx;
	String path;
public:
	IndexFile() {}
	IndexFile(const String& p) {Load(p);}
	IndexFile(const String& dir, const String& title) {Load(dir, title);}
	~IndexFile() {Store();}
	
	void Load(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".txt"));}
	void Load(const String& path);
	void Store();
	int FindAdd(const String& s) {
		int i = idx.Find(s);
		if (i >= 0) return i;
		i = idx.GetCount();
		idx.Add(s);
		return i;
	}
	int Find(const String& s) const {return idx.Find(s);}
	const String& operator[](int i) const {return idx[i];}
	int GetCount() const {return idx.GetCount();}
	const Vector<String>& GetKeys() const {return idx.GetKeys();}
	
};


template <class K>
struct MapKeys {
	template <class K0=K> String KeyString(const K0& s);
	template <class K0=K> K0 StringKey(const String& s);
	template <class K0=K> String StoreToString(K0& o) {return o.StoreToString();}
	template <class K0=K> void LoadFromString(K0& o, const String& s) {return o.LoadFromString(s);}
	
	template <> String StoreToString(int& i) {return "\"" + IntStr(i) + "\"";}
	template <> String StoreToString(String& s) {return "\"" + s + "\"";}
	template <> void LoadFromString(String& o, const String& s) {
		int a = FindNonEscaped(s, "\"");
		int b = FindNonEscaped(s, "\"", a+1);
		if (a >= 0 && b >= 0) {
			a++;
			o = s.Mid(a,b-a);
		}
	}
	template <> void LoadFromString(int& i, const String& s) {
		int a = FindNonEscaped(s, "\"");
		int b = FindNonEscaped(s, "\"", a+1);
		if (a >= 0 && b >= 0) {
			a++;
			i = StrInt(s.Mid(a,b-a));
		}
	}
	
	template<> String KeyString<String>(const String& s) {
		String key = s;
		key.Replace("\\", "\\\\");
		key.Replace("\"", "\\\"");
		key.Replace("\n", "\\n");
		return key;
	}
	template<> String KeyString<WString>(const WString& s) {
		String key = s.ToString();
		key.Replace("\"", "\\\"");
		key.Replace("\n", "\\n");
		return key;
	}
	template<> String KeyString<hash_t>(const hash_t& k) {
		return HashHex(k);
	}
	template<> String KeyString<int>(const int& k) {
		return IntStr(k);
	}
	template<> String KeyString<ActionHeader>(const ActionHeader& s) {
		String a = s.action;
		String b = s.arg;
		a.Replace("(", "\\(");
		a.Replace(")", "\\)");
		b.Replace("(", "\\(");
		b.Replace(")", "\\)");
		String key = a + "(" + b + ")";
		key.Replace("\"", "\\\"");
		key.Replace("\n", "\\n");
		return key;
	}
	template<> String KeyString<AttrHeader>(const AttrHeader& s) {
		String a = s.group;
		String b = s.value;
		a.Replace("(", "\\(");
		a.Replace(")", "\\)");
		b.Replace("(", "\\(");
		b.Replace(")", "\\)");
		String key = a + "(" + b + ")";
		key.Replace("\"", "\\\"");
		key.Replace("\n", "\\n");
		return key;
	}
	
	template<> String StringKey<String>(const String& s) {
		String key = s;
		key.Replace("\\\\", "\\");
		key.Replace("\\\"", "\"");
		key.Replace("\\n", "\n");
		return key;
	}
	template<> WString StringKey<WString>(const String& s) {
		String key = s;
		key.Replace("\\\"", "\"");
		key.Replace("\\n", "\n");
		return key.ToWString();
	}
	template<> hash_t StringKey<hash_t>(const String& s) {
		return HexHash(s);
	}
	template<> int StringKey<int>(const String& s) {
		return StrInt(s);
	}
	template<> ActionHeader StringKey<ActionHeader>(const String& s_) {
		String s = s_;
		s.Replace("\\\"", "\"");
		s.Replace("\\n", "\n");
		ActionHeader ah;
		int a = FindNonEscaped(s, "(");
		if (a >= 0) {
			ah.action = s.Left(a);
			a++;
			int b = FindNonEscaped(s, ")", a);
			if (b < 0) b = s.GetCount();
			ah.arg = s.Mid(a,b-a);
		}
		ah.action.Replace("\\(", "(");
		ah.action.Replace("\\)", ")");
		ah.arg.Replace("\\(", "(");
		ah.arg.Replace("\\)", ")");
		return ah;
	}
	template<> AttrHeader StringKey<AttrHeader>(const String& s_) {
		String s = s_;
		s.Replace("\\\"", "\"");
		s.Replace("\\n", "\n");
		AttrHeader ah;
		int a = FindNonEscaped(s, "(");
		if (a >= 0) {
			ah.group = s.Left(a);
			a++;
			int b = FindNonEscaped(s, ")", a);
			if (b < 0) b = s.GetCount();
			ah.value = s.Mid(a,b-a);
		}
		ah.group.Replace("\\(", "(");
		ah.group.Replace("\\)", ")");
		ah.value.Replace("\\(", "(");
		ah.value.Replace("\\)", ")");
		return ah;
	}
};

template <class T>
class VectorFile {
	Vector<T> map;
	String path;
	
public:
	VectorFile() {}
	VectorFile(const String& p) {Load(p);}
	VectorFile(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".txt"));}
	~VectorFile() {Store();}

	const T& operator[](int i) const {return map[i];}
	T& operator[](int i) {return map[i];}
	int GetCount() const {return map.GetCount();}
	const Vector<T>& GetValues() const {return map;}
	Vector<T>& GetValues() {return map;}
	T& Add() {return map.Add();}
	T& Add(const T& s) {return map.Add(s);}
	
	void Load(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".txt"));}
	void Load(const String& path) {
		map.Clear();
		this->path = path;
		String content = LoadFile(path);
		content.Replace("\r","");
		if (content.IsEmpty())
			return;
		Vector<String> lines = Split(content, "\n", false);
		for (String& l : lines) {
			auto& v = map.Add();
			v.LoadFromString(l);
		}
		ASSERT(map.GetCount() == lines.GetCount());
	}
	
	void Store() {
		String content;
		for(int i = 0; i < map.GetCount(); i++) {
			if (i) content << "\n";
			content << map[i].StoreToString();
		}
		String old_content = LoadFile(path);
		if (old_content.GetHashValue() != content.GetHashValue()) {
			FileOut fout(path);
			fout << content;
			fout.Close();
		}
	}
	
	void Clear() {map.Clear();}
	
};

template <class K, class T>
class SerializedFile {
	VectorMap<K, T> map;
	String path;
	hash_t orig_hash = 0;
	
public:
	SerializedFile() {}
	SerializedFile(const String& p) {Load(p);}
	SerializedFile(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".bin"));}
	~SerializedFile() {Store();}
	
	int FindAdd(const K& s) {return map.FindAdd(s);}
	int Find(const K& s) const {return map.Find(s);}
	const T& operator[](int i) const {return map[i];}
	T& operator[](int i) {return map[i];}
	int GetCount() const {return map.GetCount();}
	const Vector<K>& GetKeys() const {return map.GetKeys();}
	const Vector<T>& GetValues() const {return map.GetValues();}
	Vector<T>& GetValues() {return map.GetValues();}
	T& GetAdd(const K& s) {return map.GetAdd(s);}
	T& GetAdd(const K& s, int& i) {
		i = map.Find(s);
		if (i >= 0) return map[i];
		i = map.GetCount();
		return map.Add(s);
	}
	const K& GetKey(int i) const {return map.GetKey(i);}
	
	void Load(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".bin"));}
	void Load(const String& path) {
		map.Clear();
		this->path = path;
		String s = LoadFile(path);
		orig_hash = s.GetHashValue();
		LoadFromString(map, s);
	}
	void Store() {
		String s = StoreAsString(map);
		if (s.GetHashValue() != orig_hash) {
			FileOut fout(path);
			fout << s;
		}
	}
	void Clear() {map.Clear();}
	
};

template <class K, class T>
class MapFile {
	VectorMap<K, T> map;
	String path;
	
public:
	MapFile() {}
	MapFile(const String& p) {Load(p);}
	MapFile(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".txt"));}
	~MapFile() {Store();}
	
	int FindAdd(const K& s) {return map.FindAdd(s);}
	int Find(const K& s) const {return map.Find(s);}
	const T& operator[](int i) const {return map[i];}
	T& operator[](int i) {return map[i];}
	int GetCount() const {return map.GetCount();}
	const Vector<K>& GetKeys() const {return map.GetKeys();}
	const Vector<T>& GetValues() const {return map.GetValues();}
	Vector<T>& GetValues() {return map.GetValues();}
	T& GetAdd(const K& s) {return map.GetAdd(s);}
	T& GetAdd(const K& s, int& i) {
		i = map.Find(s);
		if (i >= 0) return map[i];
		i = map.GetCount();
		return map.Add(s);
	}
	const K& GetKey(int i) const {return map.GetKey(i);}
	
	void Load(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".txt"));}
	void Load(const String& path) {
		map.Clear();
		this->path = path;
		String content = LoadFile(path);
		content.Replace("\r","");
		if (content.IsEmpty())
			return;
		if (content.Right(1) == "\n") content = content.Left(content.GetCount()-1);
		Vector<String> lines = Split(content, "\n", false);
		MapKeys<K> k;
		MapKeys<T> v;
		int line_i = -1;
		for (String& l : lines) {
			line_i++;
			int a = FindNonEscaped(l, "\"");
			if (a < 0)
				continue;
			a++;
			int b = FindNonEscaped(l, "\"", a);
			if (b < 0)
				continue;
			K key = k.StringKey(l.Mid(a,b-a));
			String value = TrimBoth(l.Mid(b+1));
			v.LoadFromString(map.Add(key), value);
		}
		ASSERT(map.GetCount() == lines.GetCount());
	}
	void Store() {
		String content;
		MapKeys<K> k;
		MapKeys<T> v;
		for(int i = 0; i < map.GetCount(); i++) {
			if (i) content.Cat('\n');
			String key = k.KeyString(map.GetKey(i));
			content << "\"" << key << "\"";
			String s = v.StoreToString(map[i]);
			if (!s.IsEmpty())
				content << " " << s;
		}
		String old_content = LoadFile(path);
		if (old_content.GetHashValue() != content.GetHashValue()) {
			FileOut fout(path);
			fout << content;
			fout.Close();
		}
	}
	void LoadSerialized(const String& path) {
		LoadFromFile(map, path);
	}
	void StoreSerialized() {
		StoreToFile(map, path);
	}
	
	void Clear() {map.Clear();}
	
};

template <class K0, class K1, class T>
class MapMapFile {
	VectorMap<K0, VectorMap<K1,T>> map;
	String path;
	
public:
	MapMapFile() {}
	MapMapFile(const String& p) {Load(p);}
	MapMapFile(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".txt"));}
	~MapMapFile() {Store();}

	int FindAdd(const K0& s) {return map.FindAdd(s);}
	int Find(const K0& s) const {return map.Find(s);}
	int FindAdd(int i, const K1& s) {return map[i].FindAdd(s);}
	int Find(int i, const K1& s) const {return map[i].Find(s);}
	const VectorMap<K1,T>& operator[](int i) const {return map[i];}
	const T& At(int i, int j) const {return map[i][j];}
	int GetCount() const {return map.GetCount();}
	int GetCount(int i) const {return map[i].GetCount();}
	const K0& GetKey(int i) const {return map.GetKey(i);}
	const K1& GetKey(int i, int j) const {return map[i].GetKey(j);}
	const Vector<K0>& GetKeys() const {return map.GetKeys();}
	const Vector<K1>& GetKeys(int i) const {return map[i].GetKeys();}
	const Vector<T>& GetValues(int i) const {return map[i].GetValues();}
	VectorMap<K1,T>& GetAdd1(const K0& s) {return map.GetAdd(s);}
	VectorMap<K1,T>& GetAdd1(const K0& s, int& i) {
		i = map.Find(s);
		if (i >= 0) return map[i];
		i = map.GetCount();
		return map.Add(s);
	}
	T& GetAdd2(int i, const K1& s) {return map[i].GetAdd(s);}
	T& GetAdd2(int i, const K1& s, int& j) {
		auto& m = map[i];
		j = m.Find(s);
		if (j >= 0) return m[j];
		j = m.GetCount();
		return m.Add(s);
	}
	T& GetAdd3(const K0& s0, const K1& s1) {
		return map.GetAdd(s0).GetAdd(s1);
	}
	
	void Load(const String& dir, const String& title) {Load(AppendFileName(dir, title + ".txt"));}
	void Load(const String& path) {
		map.Clear();
		this->path = path;
		String content = LoadFile(path);
		content.Replace("\r","");
		if (content.Right(1) == "\n") content = content.Left(content.GetCount()-1);
		Vector<String> lines = Split(content, "\n", false);
		VectorMap<K1,T>* m = 0;
		MapKeys<K0> k0;
		MapKeys<K1> k1;
		for (String& l : lines) {
			l = TrimBoth(l);
			if (l.IsEmpty()) {
				m = 0;
				continue;
			}
			int a = FindNonEscaped(l, "\"");
			if (a < 0) continue;
			a++;
			int b = FindNonEscaped(l, "\"", a);
			if (b < 0) continue;
			if (m == 0) {
				K0 key = k0.StringKey(l.Mid(a,b-a));
				m = &map.Add(key);
			}
			else {
				K1 key = k1.StringKey(l.Mid(a,b-a));
				String value = TrimBoth(l.Mid(b+1));
				m->Add(key).LoadFromString(value);
			}
		}
	}
	
	void Store() {
		String content;
		MapKeys<K0> k0;
		MapKeys<K1> k1;
		for(int i = 0; i < map.GetCount(); i++) {
			if (i) content.Cat('\n');
			String key = k0.KeyString(map.GetKey(i));
			content << "\"" << key << "\"\n";
			auto& m = map[i];
			for(int j = 0; j < m.GetCount(); j++) {
				String key = k1.KeyString(m.GetKey(j));
				content << "\"" << key << "\"";
				String s = m[j].StoreToString();
				if (!s.IsEmpty())
					content << " " << s;
				content << "\n";
			}
		}
		String old_content = LoadFile(path);
		if (old_content.GetHashValue() != content.GetHashValue()) {
			FileOut fout(path);
			fout << content;
			fout.Close();
		}
	}
	
};


struct StringDumper {
	String s;
	template <class T> void Do(const T& o) {if (!s.IsEmpty()) s.Cat(' '); s << AsString(o);}
	template <> void Do<String>(const String& o) {
		if (!s.IsEmpty()) s.Cat(' ');
		String t = o;
		t.Replace("\"", "\\\"");
		s << "\"" << t << "\"";
	}
	template <> void Do<WString>(const WString& o) {
		if (!s.IsEmpty()) s.Cat(' ');
		String t = o.ToString();
		t.Replace("\"", "\\\"");
		s << "\"" << t << "\"";
	}
	template <> void Do<Color>(const Color& c) {
		if (!s.IsEmpty()) s.Cat(' ');
		s << c.GetR() << " " << c.GetG() << " " << c.GetB();
	}
	template <> void Do<ActionHeader>(const ActionHeader& c) {
		Do(c.action);
		Do(c.arg);
	}
	template <> void Do<Vector<String>>(const Vector<String>& v) {
		int c = v.GetCount();
		(*this) % c;
		for(int j = 0; j < c; j++)
			(*this) % v[j];
	}
	template <> void Do<VectorMap<String,Vector<String>>>(const VectorMap<String,Vector<String>>& lines) {
		int c = lines.GetCount();
		(*this) % c;
		for(int i = 0; i < lines.GetCount(); i++) {
			const String& key = lines.GetKey(i);
			(*this) % key;
			const auto& v = lines[i];
			c = v.GetCount();
			(*this) % c;
			for(int j = 0; j < c; j++)
				(*this) % v[j];
		}
	}
	operator String() const {return s;}
	template <class T> StringDumper& operator%(const T& o) {Do(o); return *this;}
};


struct StringParser {
	const String& s;
	int a = 0;
	bool err = false;
	StringParser(const String& s) : s(s) {}
	void DoSpaces() {while (a < s.GetCount() && IsSpace(s[a])) {a++;}}
	template <class T> void Do(T& o);
	template <> void Do<String>(String& o) {
		DoSpaces();
		if (a >= s.GetCount() || s[a] != '\"') {err = true; return;}
		a++;
		int b = FindNonEscaped(s, "\"", a);
		if (b < 0) {err = true; return;}
		o = s.Mid(a,b-a);
		o.Replace("\\\"", "\"");
		a = b+1;
	}
	template <> void Do<WString>(WString& o) {
		DoSpaces();
		if (a >= s.GetCount() || s[a] != '\"') {err = true; return;}
		a++;
		int b = FindNonEscaped(s, "\"", a);
		if (b < 0) {err = true; return;}
		String t = s.Mid(a,b-a);
		t.Replace("\\\"", "\"");
		o = t.ToWString();
		a = b+1;
	}
	template <> void Do<int>(int& o) {
		DoSpaces();
		int b = a;
		while (b < s.GetCount() && !IsSpace(s[b])) {b++;}
		o = StrInt(s.Mid(a,b-a));
		a = b;
	}
	template <> void Do<bool>(bool& o) {
		DoSpaces();
		int b = a;
		while (b < s.GetCount() && !IsSpace(s[b])) {b++;}
		o = StrInt(s.Mid(a,b-a));
		a = b;
	}
	template <> void Do<Color>(Color& o) {
		DoSpaces();
		int r = 0, g = 0, b = 0;
		Do(r);
		Do(g);
		Do(b);
		o = Color(r,g,b);
	}
	template <> void Do<ActionHeader>(ActionHeader& o) {
		Do(o.action);
		Do(o.arg);
	}
	template <> void Do<Vector<String>>(Vector<String>& v) {
		int c = 0;
		(*this) % c;
		for(int j = 0; j < c; j++)
			(*this) % v.Add();
	}
	template <> void Do<VectorMap<String,Vector<String>>>(VectorMap<String,Vector<String>>& lines) {
		lines.Clear();
		int c = 0;
		(*this) % c;
		for(int i = 0; i < c; i++) {
			String key;
			(*this) % key;
			auto& v = lines.Add(key);
			(*this) % c;
			for(int j = 0; j < c; j++)
				(*this) % v.Add();
		}
	}
	template <class T> StringParser& operator%(T& o) {Do(o); return *this;}
	void Chk() {ASSERT(!err);}
};


END_TEXTLIB_NAMESPACE


#endif
