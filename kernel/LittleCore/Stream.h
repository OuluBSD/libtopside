#ifndef _LittleCore_Stream_h_
#define _LittleCore_Stream_h_


#define K_EOL "\n"

struct KStream {
	void (*fn)(const char*, int, void*) = 0;
	void* arg = 0;
	
	
	KStream& operator << (const KString& s);
	KStream& operator << (char c);
	
	void SetCallback(void (*fn)(const char*, int, void*), void* arg=0) {this->fn = fn; this->arg = arg;}
	
	
};


KStream& KCout();
KStream& KCerr();

#define KLOG(x) KCout() << x << "\n";

#endif
