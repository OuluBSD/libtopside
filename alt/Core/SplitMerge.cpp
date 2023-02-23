#include "Core.h"

NAMESPACE_UPP_BEGIN


String Join(const Vector<String>& v, String join_str, bool ignore_empty) {
	String out;
	for (const String& s : v) {
		if (s.IsEmpty() && ignore_empty)
			continue;
		if (!out.IsEmpty())
			out << join_str;
		out << s;
	}
	return out;
}

Vector<String> Split(String to_split, String split_str, bool ignore_empty) {
	Vector<String> v;
	
	if (to_split.IsEmpty() || split_str.IsEmpty())
		return v;
	
	int i = to_split.Find(split_str);
	if (i == -1)
		v.Add(to_split);
	else {
		int j = 0;
		while (i >= 0) {
			String str = to_split.Mid(j, i - j);
			if (str.GetCount() == 0) {
				if (!ignore_empty)
					v.Add(str);
			}
			else {
				v.Add(str);
			}
			i += split_str.GetCount();
			j = i;
			i = to_split.Find(split_str, i);
		}
		i = to_split.GetCount();
		String str = to_split.Mid(j, i - j);
		if (str.GetCount() == 0) {
			if (!ignore_empty)
				v.Add(str);
		}
		else {
			v.Add(str);
		}
	}
	
	return v;
}

Vector<WString> Split(WString to_split, WString split_str, bool ignore_empty) {
	Vector<WString> v;
	
	if (to_split.IsEmpty() || split_str.IsEmpty())
		return v;
	
	int i = to_split.Find(split_str);
	if (i == -1)
		v.Add(to_split);
	else {
		int j = 0;
		while (i >= 0) {
			WString str = to_split.Mid(j, i - j);
			if (str.GetCount() == 0) {
				if (!ignore_empty)
					v.Add(str);
			}
			else {
				v.Add(str);
			}
			i += split_str.GetCount();
			j = i;
			i = to_split.Find(split_str, i);
		}
		i = to_split.GetCount();
		WString str = to_split.Mid(j, i - j);
		if (str.GetCount() == 0) {
			if (!ignore_empty)
				v.Add(str);
		}
		else {
			v.Add(str);
		}
	}
	
	return v;
}


NAMESPACE_UPP_END
