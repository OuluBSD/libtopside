#ifndef _Local_Realtime_h_
#define _Local_Realtime_h_


NAMESPACE_TOPSIDE_BEGIN


class RealtimeStream {
	
public:
	
	virtual ~RealtimeStream() {}
	
	//virtual double GetSeconds() const = 0;
	
	virtual String GetLastError() const {return String();}
	
};


NAMESPACE_TOPSIDE_END


#endif
