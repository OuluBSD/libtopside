#ifndef _TemplatesLib_ConvDevScope_h_
#define _TemplatesLib_ConvDevScope_h_

#if 0

NAMESPACE_ECS_BEGIN


template <class FromDevSpec, class ToDevSpec>
struct ScopeConvDevLibT {
	using FDevMach = ScopeDevMachT<FromDevSpec>;
	using FDevCore = ScopeDevCoreT<FromDevSpec>;
	using FDevLib = ScopeDevLibT<FromDevSpec>;
	
	using TDevMach = ScopeDevMachT<ToDevSpec>;
	using TDevCore = ScopeDevCoreT<ToDevSpec>;
	using TDevLib = ScopeDevLibT<ToDevSpec>;
	
	
	
	
	
	class SideOutput :
		public SideOutputBase
	{
	public:
		RTTI_DECL_1(SideOutput, SideOutputBase, FromDevSpec::GetName() + ToDevSpec::GetName() + "SideOutput")
		void Visit(RuntimeVisitor& vis) {vis.VisitThis<SideOutputBase>(this);}
		COMP_MAKE_ACTION_BEGIN
			COMP_MAKE_ACTION_UNDEF_TO_TRUE(FromDevSpec::GetNameLower() + "." + ToDevSpec::GetNameLower() + ".side")
		COMP_MAKE_ACTION_END
		
	public:
		SideOutput() {}
		
	};
	
	
	class SideInput :
		public SideInputBase
	{
	public:
		RTTI_DECL_1(SideInput, SideInputBase, FromDevSpec::GetName() + ToDevSpec::GetName() + "SideInput")
		void Visit(RuntimeVisitor& vis) {vis.VisitThis<SideInputBase>(this);}
		COMP_MAKE_ACTION_BEGIN
			COMP_MAKE_ACTION_UNDEF_TO_TRUE(FromDevSpec::GetNameLower() + "." + ToDevSpec::GetNameLower() + ".side")
		COMP_MAKE_ACTION_END
		
	public:
		SideInput() {}
		
	};
	
};


NAMESPACE_ECS_END

#endif
#endif
