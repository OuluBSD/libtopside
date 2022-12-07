#ifndef _VirtualGui3D_Direct_h_
#define _VirtualGui3D_Direct_h_

#if 0

NAMESPACE_ECS_BEGIN


class DirectWindow :
	public Component<DirectWindow>
{
	//static uint32 prev_ticks;
	
	
public:
	COPY_PANIC(DirectWindow)
	COMP_DEF_VISIT
	
	
	DirectWindow();
	
	void Initialize() override;
	void Uninitialize() override;
	
	
	Callback WhenClose;
	
};


NAMESPACE_ECS_END


#endif
#endif
