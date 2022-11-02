#include "LayoutCtrl.h"

NAMESPACE_LAYOUT_BEGIN

Editor::Editor() {
	Add(vsplit.SizePos());
	
	vsplit.Vert();
	vsplit << doc;
	
	doc.SetFont(Monospace());
	
}

void Editor::SetData(const Value& data) {
	
	doc.SetData(data);
	
}



NAMESPACE_LAYOUT_END
