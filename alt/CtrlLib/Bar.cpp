#include "CtrlLib.h"


NAMESPACE_UPP




BarCtrl::BarCtrl() {
	
}

void BarCtrl::Set(Callback1<Bar&> menu) {
	TODO
}





ToolButton::ToolButton() {
	
}

void ToolButton::Paint(Draw& w) {
	TODO
}

void ToolButton::MouseEnter(Point, dword) {
	TODO
}

void ToolButton::MouseLeave() {
	TODO
}

Size ToolButton::GetMinSize() const {
	TODO
}

void ToolButton::LeftDown(Point, dword) {
	TODO
}

void ToolButton::LeftRepeat(Point, dword) {
	TODO
}

void ToolButton::LeftUp(Point, dword) {
	TODO
}

bool ToolButton::HotKey(dword key) {
	TODO
}

String ToolButton::GetDesc() const {
	TODO
}

int ToolButton::OverPaint() const {
	TODO
}


Bar::Item& ToolButton::Text(const char *text) {
	TODO
}

Bar::Item& ToolButton::Key(dword key) {
	TODO
}

Bar::Item& ToolButton::Repeat(bool repeat) {
	TODO
}

Bar::Item& ToolButton::Image(const UPP::Image& img) {
	TODO
}

Bar::Item& ToolButton::Enable(bool _enable) {
	TODO
}

Bar::Item& ToolButton::Tip(const char *tip) {
	TODO
}

Bar::Item& ToolButton::Help(const char *help) {
	TODO
}

Bar::Item& ToolButton::Topic(const char *help) {
	TODO
}

Bar::Item& ToolButton::Description(const char *desc) {
	TODO
}

Bar::Item& ToolButton::Radio(bool check) {
	TODO
}

Bar::Item& ToolButton::Check(bool check) {
	TODO
}

void ToolButton::FinalSync() {
	TODO
}





ToolBar::ToolBar() {
	
}

bool ToolBar::HotKey(dword key) {
	TODO
}

void ToolBar::Paint(Draw& w) {
	TODO
}

Bar::Item& ToolBar::AddItem(Callback  cb) {
	TODO
}

Bar::Item& ToolBar::AddSubMenu(Callback1<Bar&> proc) {
	TODO
}









MenuBar::MenuBar() {
	
}

void MenuBar::FrameLayout(Rect& r) {
	TODO
}

void MenuBar::FrameAddSize(Size& sz) {
	TODO
}

void MenuBar::Execute(Callback1<Bar&> cb) {
	TODO
}


END_UPP_NAMESPACE
