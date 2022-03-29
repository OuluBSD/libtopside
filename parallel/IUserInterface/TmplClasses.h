// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

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
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceSplitterT : UiSplitter {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceSeparatorCtrlT : UiSeparatorCtrl {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceArrayCtrlT : UiArrayCtrl {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceColumnCtrlT : UiColumnCtrl {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceTreeCtrlT : UiTreeCtrl {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceIconCtrlT : UiIconCtrl {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceImageCtrlT : UiImageCtrl {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceButtonT : UiButton {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceLabelT : UiLabel {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceStringEditT : UiStringEdit {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceIntEditT : UiIntEdit {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceFloatEditT : UiFloatEdit {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceTimeEditT : UiTimeEdit {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceDateEditT : UiDateEdit {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceDocEditT : UiDocEdit {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceBarT : UiBar {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

template <class Ui>
struct UserInterfaceMenuBarT : UiMenuBar {
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}

	void Uninitialize() override {
	}

	bool ProcessPacket(PacketValue& v) override {
		return true;
	}

	
};

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


NAMESPACE_PARALLEL_END



#endif

