#ifndef _EcsDebug_SideExt_h_
#define _EcsDebug_SideExt_h_

NAMESPACE_ECS_BEGIN



class DebugSideInputExt :
	public SideInputExt
{
	
public:
	RTTI_DECL1(DebugSideInputExt, SideInputExt)
	typedef DebugSideInputExt CLASSNAME;
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	
	EXT_MAKE_ACTION_BEGIN
	ASSERT(cls.sub == SubCompCls::SIDE_INPUT);
	ValDevCls side_vd = act.Post().GetSideCls();
	ASSERT(side_vd.IsValid());
	String s = vd.GetActionName() + ".side.in." + side_vd.dev.GetActionName();
	EXT_MAKE_ACTION_UNDEF_TO_TRUE(s)
	if (cls.IsMultiSideConnection()) {
		EXT_MAKE_ACTION_UNDEF_TO_TRUE(s + ".multi");
	}
	else {
		EXT_MAKE_ACTION_UNDEF_TO_FALSE(s + ".multi");
	}
	EXT_MAKE_ACTION_END
	
	static SideStatus MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to);
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_SIDE_IN;}
	
};

class DebugSideOutputExt :
	public SideOutputExt
{
	
public:
	RTTI_DECL1(DebugSideOutputExt, SideOutputExt)
	typedef DebugSideOutputExt CLASSNAME;
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	
	EXT_MAKE_ACTION_BEGIN
	ASSERT(cls.sub == SubCompCls::SIDE_OUTPUT);
	ValDevCls side_vd = act.Post().GetSideCls();
	ASSERT(side_vd.IsValid());
	String s = vd.GetActionName() + ".side.out." + side_vd.dev.GetActionName();
	EXT_MAKE_ACTION_UNDEF_TO_TRUE(s)
	if (cls.IsMultiSideConnection()) {
		EXT_MAKE_ACTION_UNDEF_TO_TRUE(s + ".multi");
	}
	else {
		EXT_MAKE_ACTION_UNDEF_TO_FALSE(s + ".multi");
	}
	EXT_MAKE_ACTION_END
	
	static SideStatus MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to);
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_SIDE_OUT;}
	
};



NAMESPACE_ECS_END

#endif
