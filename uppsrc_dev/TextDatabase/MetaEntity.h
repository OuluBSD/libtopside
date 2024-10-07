#ifndef _TextDatabase_MetaEntity_h_
#define _TextDatabase_MetaEntity_h_


BEGIN_TEXTLIB_NAMESPACE


struct Owner;

struct Profile
{
	Owner* owner = 0;
	String name;
	
	
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			;
	}
	
};

struct Owner
{
	String name;
	Array<Profile> profiles;
	
	void Store();
	void Load(String name);
	void Jsonize(JsonIO& json) {
		json
			("name", name)
			("profiles", profiles)
			;
		if (json.IsLoading()) {
			for (Profile& p : profiles)
				p.owner = this;
		}
	}
	
	static Owner& DatabaseUpdate();
};




END_TEXTLIB_NAMESPACE


#endif
