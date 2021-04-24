#include <CoreAlt/Core.h>
#include "bz2lib.h"

NAMESPACE_UPP


String BZ2Compress(String s, int level, bool allow_empty) {
	const int chunk_size = 1 << 16;
	bz_stream STREAM;
	Vector<char> dst;
	level = max(1, min(9, level));
	
	int src_len = s.GetCount();
	int dst_len = 0;
	const char* src_buf = s.Begin();

    // Check parameters
    if (!src_len) {
        if (!allow_empty)
            return String();
        src_buf = NULL;
    }
    
    STREAM.bzalloc = NULL;
    STREAM.bzfree  = NULL;
    STREAM.opaque  = NULL;
    int errcode = BZ2_bzCompressInit(&STREAM, level, 0, 0);
   
    if (errcode == BZ_OK) {
        dst.SetCount(chunk_size);
    
        STREAM.next_in   = (char*)s.Begin();
        STREAM.avail_in  = 0;
        STREAM.next_out  = dst.GetData();
        STREAM.avail_out = chunk_size;

        size_t left = src_len;
        do {
            if (STREAM.avail_in == 0) {
                STREAM.avail_in = left > chunk_size ? chunk_size : (unsigned int)left;
                left -= STREAM.avail_in;
            }
            if (STREAM.avail_out == 0) {
                int count = dst.GetCount();
                dst.SetCount(count + chunk_size);
                STREAM.next_out  = dst.GetData() + count;
                STREAM.avail_out = chunk_size;
            }
            errcode = BZ2_bzCompress(&STREAM, left ? BZ_RUN : BZ_FINISH);
            if (left == 0 && STREAM.avail_out > 0)
                break;
        }
        while (errcode == BZ_RUN_OK);

        BZ2_bzCompressEnd(&STREAM);
        
        int dst_len = STREAM.next_out - (char*)dst.GetData();
        ASSERT(dst_len >= 0);
        dst.SetCount(dst_len);
        
        if (errcode == BZ_RUN_OK || errcode == BZ_STREAM_END) {
            String s;
            s.SetData(dst.Begin(), dst.GetCount());
            return s;
        }
    }
	
	return String();
}

String BZ2Decompress(String s, bool allow_fail) {
	const int chunk_size = 1 << 16;
	bz_stream STREAM;
	Vector<char> dst;
	int src_len = s.GetCount();
    if (!src_len)
        return String();
    
    STREAM.bzalloc = NULL;
    STREAM.bzfree  = NULL;
    STREAM.opaque  = NULL;
    int errcode = BZ2_bzDecompressInit(&STREAM, 0, 0);
   
    if (errcode == BZ_OK) {
        dst.SetCount(chunk_size);
        
        STREAM.next_in   = (char*)s.Begin();
        STREAM.avail_in  = 0;
        STREAM.next_out  = dst.GetData();
        STREAM.avail_out = chunk_size;

        size_t left = src_len;
        do {
            if (STREAM.avail_in == 0) {
                STREAM.avail_in = left > chunk_size ? chunk_size : (unsigned int)left;
                left -= STREAM.avail_in;
            }
            if (STREAM.avail_out == 0) {
                int count = dst.GetCount();
                dst.SetCount(count + chunk_size);
                STREAM.next_out  = dst.GetData() + count;
                STREAM.avail_out = chunk_size;
            }
            errcode = BZ2_bzDecompress(&STREAM);
            if (left == 0 && STREAM.avail_out > 0)
                break;
        }
        while (errcode == BZ_OK);
		
        BZ2_bzDecompressEnd(&STREAM);
        
        int dst_len = STREAM.next_out - (char*)dst.GetData();
        ASSERT(dst_len >= 0);
        dst.SetCount(dst_len);
        
        if (errcode == BZ_OK || errcode == BZ_STREAM_END || allow_fail) {
            String s;
            s.SetData(dst.Begin(), dst.GetCount());
            return s;
        }
    }
	
	return String();
}

END_UPP_NAMESPACE

