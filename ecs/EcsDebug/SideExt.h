#ifndef _EcsDebug_SideExt_h_
#define _EcsDebug_SideExt_h_

NAMESPACE_ECS_BEGIN



class DebugAudioSideInputExt :
	public SideInputExt
{
	
public:
	RTTI_DECL1(DebugAudioSideInputExt, SideInputExt)
	typedef DebugAudioSideInputExt CLASSNAME;
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	
	COMP_MAKE_ACTION_BEGIN
		ASSERT(cls.sub == SubCompCls::SIDE_INPUT);
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.side.in.center")
	COMP_MAKE_ACTION_END
	
	static bool MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to);
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_SIDE_OUT;}
	
};

class DebugAudioSideOutputExt :
	public SideOutputExt
{
	
public:
	RTTI_DECL1(DebugAudioSideOutputExt, SideOutputExt)
	typedef DebugAudioSideOutputExt CLASSNAME;
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	
	COMP_MAKE_ACTION_BEGIN
		ASSERT(cls.sub == SubCompCls::SIDE_OUTPUT);
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.side.out.center")
	COMP_MAKE_ACTION_END
	
	static bool MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to);
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_SIDE_OUT;}
	
};



NAMESPACE_ECS_END

#endif
