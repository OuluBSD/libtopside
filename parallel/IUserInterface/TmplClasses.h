// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 11:11:55

#ifndef _IUserInterface_TmplClasses_h_
#define _IUserInterface_TmplClasses_h_

NAMESPACE_PARALLEL_BEGIN

template <class Ui> struct UserInterfaceWindowT;
template <class Ui> struct UserInterfaceSplitterT;
template <class Ui> struct UserInterfaceSeparatorCtrlT;
template <class Ui> struct UserInterfaceArrayCtrlT;
template <class Ui> struct UserInterfaceColumnCtrlT;
template <class Ui> struct UserInterfaceTreeCtrlT;
template <class Ui> struct UserInterfaceIconCtrlT;
template <class Ui> struct UserInterfaceImageCtrlT;
template <class Ui> struct UserInterfaceButtonT;
template <class Ui> struct UserInterfaceLabelT;
template <class Ui> struct UserInterfaceStringEditT;
template <class Ui> struct UserInterfaceIntEditT;
template <class Ui> struct UserInterfaceFloatEditT;
template <class Ui> struct UserInterfaceTimeEditT;
template <class Ui> struct UserInterfaceDateEditT;
template <class Ui> struct UserInterfaceDocEditT;
template <class Ui> struct UserInterfaceBarT;
template <class Ui> struct UserInterfaceMenuBarT;


template <class Ui>
struct UserInterfaceWindowT : UiWindow {
	using CLASSNAME = UserInterfaceWindowT<Ui>;
	RTTI_DECL1(CLASSNAME, UiWindow)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiWindow>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceSplitterT : UiSplitter {
	using CLASSNAME = UserInterfaceSplitterT<Ui>;
	RTTI_DECL1(CLASSNAME, UiSplitter)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiSplitter>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceSeparatorCtrlT : UiSeparatorCtrl {
	using CLASSNAME = UserInterfaceSeparatorCtrlT<Ui>;
	RTTI_DECL1(CLASSNAME, UiSeparatorCtrl)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiSeparatorCtrl>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceArrayCtrlT : UiArrayCtrl {
	using CLASSNAME = UserInterfaceArrayCtrlT<Ui>;
	RTTI_DECL1(CLASSNAME, UiArrayCtrl)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiArrayCtrl>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceColumnCtrlT : UiColumnCtrl {
	using CLASSNAME = UserInterfaceColumnCtrlT<Ui>;
	RTTI_DECL1(CLASSNAME, UiColumnCtrl)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiColumnCtrl>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceTreeCtrlT : UiTreeCtrl {
	using CLASSNAME = UserInterfaceTreeCtrlT<Ui>;
	RTTI_DECL1(CLASSNAME, UiTreeCtrl)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiTreeCtrl>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceIconCtrlT : UiIconCtrl {
	using CLASSNAME = UserInterfaceIconCtrlT<Ui>;
	RTTI_DECL1(CLASSNAME, UiIconCtrl)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiIconCtrl>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceImageCtrlT : UiImageCtrl {
	using CLASSNAME = UserInterfaceImageCtrlT<Ui>;
	RTTI_DECL1(CLASSNAME, UiImageCtrl)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiImageCtrl>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceButtonT : UiButton {
	using CLASSNAME = UserInterfaceButtonT<Ui>;
	RTTI_DECL1(CLASSNAME, UiButton)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiButton>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceLabelT : UiLabel {
	using CLASSNAME = UserInterfaceLabelT<Ui>;
	RTTI_DECL1(CLASSNAME, UiLabel)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiLabel>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceStringEditT : UiStringEdit {
	using CLASSNAME = UserInterfaceStringEditT<Ui>;
	RTTI_DECL1(CLASSNAME, UiStringEdit)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiStringEdit>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceIntEditT : UiIntEdit {
	using CLASSNAME = UserInterfaceIntEditT<Ui>;
	RTTI_DECL1(CLASSNAME, UiIntEdit)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiIntEdit>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceFloatEditT : UiFloatEdit {
	using CLASSNAME = UserInterfaceFloatEditT<Ui>;
	RTTI_DECL1(CLASSNAME, UiFloatEdit)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiFloatEdit>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceTimeEditT : UiTimeEdit {
	using CLASSNAME = UserInterfaceTimeEditT<Ui>;
	RTTI_DECL1(CLASSNAME, UiTimeEdit)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiTimeEdit>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceDateEditT : UiDateEdit {
	using CLASSNAME = UserInterfaceDateEditT<Ui>;
	RTTI_DECL1(CLASSNAME, UiDateEdit)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiDateEdit>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceDocEditT : UiDocEdit {
	using CLASSNAME = UserInterfaceDocEditT<Ui>;
	RTTI_DECL1(CLASSNAME, UiDocEdit)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiDocEdit>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceBarT : UiBar {
	using CLASSNAME = UserInterfaceBarT<Ui>;
	RTTI_DECL1(CLASSNAME, UiBar)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiBar>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceMenuBarT : UiMenuBar {
	using CLASSNAME = UserInterfaceMenuBarT<Ui>;
	RTTI_DECL1(CLASSNAME, UiMenuBar)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<UiMenuBar>(this);}
	
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	bool PostInitialize() override {
		return true;
	}

	bool Start() override {
	}

	void Stop() override {
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

#if 0
using ImguiWindow = UserInterfaceWindowT<UiImgui>;
using ImguiSplitter = UserInterfaceSplitterT<UiImgui>;
using ImguiSeparatorCtrl = UserInterfaceSeparatorCtrlT<UiImgui>;
using ImguiArrayCtrl = UserInterfaceArrayCtrlT<UiImgui>;
using ImguiColumnCtrl = UserInterfaceColumnCtrlT<UiImgui>;
using ImguiTreeCtrl = UserInterfaceTreeCtrlT<UiImgui>;
using ImguiIconCtrl = UserInterfaceIconCtrlT<UiImgui>;
using ImguiImageCtrl = UserInterfaceImageCtrlT<UiImgui>;
using ImguiButton = UserInterfaceButtonT<UiImgui>;
using ImguiLabel = UserInterfaceLabelT<UiImgui>;
using ImguiStringEdit = UserInterfaceStringEditT<UiImgui>;
using ImguiIntEdit = UserInterfaceIntEditT<UiImgui>;
using ImguiFloatEdit = UserInterfaceFloatEditT<UiImgui>;
using ImguiTimeEdit = UserInterfaceTimeEditT<UiImgui>;
using ImguiDateEdit = UserInterfaceDateEditT<UiImgui>;
using ImguiDocEdit = UserInterfaceDocEditT<UiImgui>;
using ImguiBar = UserInterfaceBarT<UiImgui>;
using ImguiMenuBar = UserInterfaceMenuBarT<UiImgui>;
#endif


NAMESPACE_PARALLEL_END



#endif

