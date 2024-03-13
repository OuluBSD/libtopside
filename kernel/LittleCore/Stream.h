#ifndef _LittleCore_Stream_h_
#define _LittleCore_Stream_h_


#define K_EOL "\n"

struct KStream {
	
	
	
	KStream& operator << (const KString& s);
	KStream& operator << (char c);
	
};


KStream& KCout();
KStream& KCerr();

#endif
