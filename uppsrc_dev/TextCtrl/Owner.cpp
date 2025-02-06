#include "TextCtrl.h"
#include <TopTool/TopTool.h>


BEGIN_TEXTLIB_NAMESPACE


OwnerInfoCtrl::OwnerInfoCtrl() {
	CtrlLayout(*this);
	
	name <<= THISBACK(OnValueChange);
	
}

void OwnerInfoCtrl::Data() {
	MetaDatabase& mdb = MetaDatabase::Single();
	MetaPtrs& p = MetaPtrs::Single();
	
	Clear();
	
	if (p.owner) {
		Owner& a = *p.owner;
			
		this->name						.SetData(a.name);
	}
	
}

void OwnerInfoCtrl::Clear() {
	this->name						.Clear();
}

void OwnerInfoCtrl::OnValueChange() {
	TextDatabase& db = GetDatabase();
	MetaPtrs& p = MetaPtrs::Single();
	
	if (p.owner) {
		Owner& o = *p.owner;
		o.name						= this->name.GetData();
	}
}


END_TEXTLIB_NAMESPACE

