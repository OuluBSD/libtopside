#ifndef _EcsDebug_ConvExt_h_
#define _EcsDebug_ConvExt_h_

NAMESPACE_ECS_BEGIN



class DebugConverterExt :
	public ConverterExt
{
	
public:
	RTTI_DECL1(DebugConverterExt, ConverterExt)
	typedef DebugConverterExt CLASSNAME;
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void LoadPacket(const Packet& p) override;
	void StorePacket(Packet& p) override;
	
	COMP_MAKE_ACTION_BEGIN
		ASSERT(cls.sub == SubCompCls::CONVERTER);
		String s = cls.sink.GetActionName() + ".convert." + cls.src.val.GetActionName() + ".dbg";
		//DUMP(s)
		COMP_MAKE_ACTION_UNDEF_TO_TRUE(s)
	COMP_MAKE_ACTION_END
	
	static SideStatus MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to);
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_DBG_CONVERTER;}
	
};



NAMESPACE_ECS_END

#endif
