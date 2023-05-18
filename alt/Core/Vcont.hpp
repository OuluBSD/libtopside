#pragma once

NAMESPACE_UPP_BEGIN


template <class T>
void StreamContainerRaw(Stream& s, T& cont)
{ // optimised version for fundamental types, for Vector
	int n = cont.GetCount();
	s / n;
	if(n < 0) {
		s.LoadError();
		return;
	}
	if(s.IsLoading()) {
		cont.Clear();
		cont.Reserve(min(n, int(256*1024 / sizeof(T)))); // protect against invalid streams...
		
		while(n > 0) {
			int count = min(n, 65536);
			int q = cont.GetCount();
			cont.SetCount(q + count);
			s.SerializeRaw(cont.begin() + q, count);
			n -= count;
		}
	}
	else
		s.SerializeRaw(cont.begin(), n);
}

template <class T>
void StreamContainer(Stream& s, T& cont)
{
	int n = cont.GetCount();
	s / n;
	if(n < 0) {
		s.LoadError();
		return;
	}
	if(s.IsLoading())
	{
		cont.Clear();
		cont.Reserve(min(n, int(256*1024 / sizeof(T)))); // protect against invalid streams...
		while(n--)
			s % cont.Add();
	}
	else
	{
		for(auto ptr = cont.begin(); n--; ++ptr)
			s % *ptr;
	}
}

template <>
inline void StreamContainer(Stream& s, Vector<byte>& cont)
{
	StreamContainerRaw(s, cont);
}

template <>
inline void StreamContainer(Stream& s, Vector<word>& cont)
{
	StreamContainerRaw(s, cont);
}

template <>
inline void StreamContainer(Stream& s, Vector<int16>& cont)
{
	StreamContainerRaw(s, cont);
}

template <>
inline void StreamContainer(Stream& s, Vector<dword>& cont)
{
	StreamContainerRaw(s, cont);
}

template <>
inline void StreamContainer(Stream& s, Vector<int>& cont)
{
	StreamContainerRaw(s, cont);
}

template <>
inline void StreamContainer(Stream& s, Vector<uint64>& cont)
{
	StreamContainerRaw(s, cont);
}

template <>
inline void StreamContainer(Stream& s, Vector<float>& cont)
{
	StreamContainerRaw(s, cont);
}

template <>
inline void StreamContainer(Stream& s, Vector<double>& cont)
{
	StreamContainerRaw(s, cont);
}


NAMESPACE_UPP_END
