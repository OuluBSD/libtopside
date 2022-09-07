#include "Core.h"

NAMESPACE_UPP_BEGIN


const NullOpt null_opt;













Huge::Huge()
{
	size = 0;
}

byte *Huge::AddChunk()
{
	size += CHUNK;
	return data.Add().data;
}

void Huge::Finish(int last_chunk_size)
{
	size = size - CHUNK + last_chunk_size;
}

void Huge::Get(void *t_, size_t pos, size_t sz) const
{
	ASSERT(pos + sz <= size);
	int blki = int(pos / CHUNK);
	size_t blkpos = pos & (CHUNK - 1);
	byte *t = (byte *)t_;
	
	while(sz > 0) {
		size_t m = min(sz, CHUNK - blkpos);
		memcpy(t, data[blki].data + blkpos, m);
		t += m;
		sz -= m;
		blkpos = 0;
		blki++;
	}
}

String Huge::Get() const
{
	if(size >= INT_MAX)
		Panic("String is too big!");
	String s;
	void* mem = s.GetWritableData(0xFF, size);
	Get(mem, 0, size);
	return s;
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
