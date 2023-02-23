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





NAMESPACE_UPP_END
