#include "TextCtrl.h"
#include <TopTool/TopTool.h>


BEGIN_TEXTLIB_NAMESPACE


ProfileInfoCtrl::ProfileInfoCtrl() {
	CtrlLayout(*this);
	
	name <<= THISBACK(OnValueChange);
	
}

void ProfileInfoCtrl::Data() {
	MetaDatabase& mdb = MetaDatabase::Single();
	MetaPtrs& p = MetaPtrs::Single();
	
	Clear();
	
	if (p.profile) {
		Profile& a = *p.profile;
		this->name						.SetData(a.name);
		
	}
	
}

void ProfileInfoCtrl::Clear() {
	this->name						.Clear();
		
}

void ProfileInfoCtrl::OnValueChange() {
	TextDatabase& db = GetDatabase();
	MetaPtrs& p = MetaPtrs::Single();
	
	if (p.profile) {
		Profile& o = *p.profile;
		o.name						= this->name.GetData();
		
	}
}


END_TEXTLIB_NAMESPACE

