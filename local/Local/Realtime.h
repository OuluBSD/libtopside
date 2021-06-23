#ifndef _Local_Realtime_h_
#define _Local_Realtime_h_


NAMESPACE_TOPSIDE_BEGIN


class RealtimeStream :
	RTTIBase,
	public RefScopeEnabler<RealtimeStream, Ecs::ComponentBase>
{
	
public:
	RTTI_DECL_R0(RealtimeStream)
	virtual ~RealtimeStream() {}
	
	virtual void Clear() = 0;
	
	virtual String GetLastError() const {return String();}
	
};


NAMESPACE_TOPSIDE_END


#endif
