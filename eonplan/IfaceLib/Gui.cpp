#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(UserInterface, Ui, U) {
	IfaceLib::Add(this);
	
	COLOR(28, 85, 255)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(Window) {
			
		}
		CLASS(Splitter) {
			
		}
		CLASS(SeparatorCtrl) {
			
		}
		CLASS(ArrayCtrl) {
			
		}
		CLASS(ColumnCtrl) {
			
		}
		CLASS(TreeCtrl) {
			
		}
		CLASS(IconCtrl) {
			
		}
		CLASS(ImageCtrl) {
			
		}
		CLASS(Button) {
			
		}
		CLASS(Label) {
			
		}
		CLASS(StringEdit) {
			
		}
		CLASS(IntEdit) {
			
		}
		CLASS(FloatEdit) {
			
		}
		CLASS(TimeEdit) {
			
		}
		CLASS(DateEdit) {
			
		}
		CLASS(DocEdit) {
			
		}
		CLASS(Bar) {
			
		}
		CLASS(MenuBar) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(Ctrl)
		//UTIL_CLASS()
		
		FUNCTION2R(CreateCtrl,		bool, int type, NativeCtrl&)
		FUNCTION1V(ClearCtrl,		NativeCtrl&)
		
		FUNCTION3R(SetCallback,		bool, NativeCtrl&, int when_enum, Callback cb)
		
	}
	
	
	VENDOR(Imgui) {
		
	}
	
	
}


NAMESPACE_PLAN_END
