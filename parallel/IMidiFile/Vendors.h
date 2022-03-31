// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 23:44:55

#ifndef _IMidiFile_Vendors_h_
#define _IMidiFile_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define MIF_CLS_LIST(x) \
	MIF_CLS(MidiFile, x) \



#define MIF_VNDR_LIST \



#define MIF_CLS(x, v) struct v##x;
#define MIF_VNDR(x) MIF_CLS_LIST(x)
MIF_VNDR_LIST
#undef MIF_VNDR
#undef MIF_CLS





NAMESPACE_PARALLEL_END


#endif

