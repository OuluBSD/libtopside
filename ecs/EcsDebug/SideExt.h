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
	void StorePacket(Packet& p) override;
	
	COMP_MAKE_ACTION_BEGIN
		ASSERT(cls.sub == SubCompCls::SIDE_INPUT);
		ValDevCls side_vd = act.Post().GetSideCls();
		ASSERT(side_vd.IsValid());
		COMP_MAKE_ACTION_FALSE_TO_TRUE(cls.side.vd.GetActionName() + ".side.in." + side_vd.dev.GetActionName())
	COMP_MAKE_ACTION_END
	
	static bool MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to);
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_SIDE_OUT;}
	
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
	void StorePacket(Packet& p) override;
	
	COMP_MAKE_ACTION_BEGIN
		ASSERT(cls.sub == SubCompCls::SIDE_OUTPUT);
		ValDevCls side_vd = act.Post().GetSideCls();
		ASSERT(side_vd.IsValid());
		COMP_MAKE_ACTION_FALSE_TO_TRUE(cls.side.vd.GetActionName() + ".side.out." + side_vd.dev.GetActionName())
	COMP_MAKE_ACTION_END
	
	static bool MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to);
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_SIDE_OUT;}
	
};



NAMESPACE_ECS_END

#endif
