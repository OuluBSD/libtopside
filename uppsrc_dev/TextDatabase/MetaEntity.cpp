#include "TextDatabase.h"


BEGIN_TEXTLIB_NAMESPACE


#if 0
void Owner::CopyOld() {
	MetaDatabase& mdb = MetaDatabase::Single();
	
	int c = mdb.meta_entities.GetCount();
	
	mdb.owners.SetCount(c);
	for(int i = 0; i < mdb.owners.GetCount(); i++) {
		Owner& o = mdb.owners[i];
		const MetaEntity& e = mdb.meta_entities[i];
		
		o.name = e.name;
		o.year_of_birth = e.year_of_birth;
		o.year_of_hobbyist_begin = e.year_of_hobbyist_begin;
		o.year_of_career_begin = e.year_of_career_begin;
		o.is_guitarist = e.is_guitarist;
		o.electronic_tools = e.electronic_tools;
		
		o.profiles.SetCount(max(o.profiles.GetCount(), 1));
		Profile& p = o.profiles[0];
		p.name = e.name;
		p.begin = Date(o.year_of_hobbyist_begin,1,1);
		p.biography = e.biography;
		p.preferred_genres = e.preferred_genres;
		p.languages = e.languages;
	}
	
}
#endif


Owner& Owner::DatabaseUpdate() {
	static Owner e;
	return e;
}

void Owner::Store() {
	String dir = AppendFileName(MetaDatabase::GetDirectory(), "share");
	String path = AppendFileName(dir, name + ".json");
	RealizeDirectory(dir);
	StoreAsJsonFileStandard(*this, path);
}

void Owner::Load(String name) {
	String dir = AppendFileName(MetaDatabase::GetDirectory(), "share");
	String path = AppendFileName(dir, name + ".json");
	RealizeDirectory(dir);
	LoadFromJsonFileStandard(*this, path);
}


END_TEXTLIB_NAMESPACE

