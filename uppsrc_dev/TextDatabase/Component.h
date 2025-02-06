#ifndef _TextDatabase_Song_h_
#define _TextDatabase_Song_h_


BEGIN_TEXTLIB_NAMESPACE


struct ComponentIdea {
	String title, target_song, reference_song, description;
	
	void Serialize(Stream& s) {
		s % title
		  % target_song
		  % reference_song
		  % description
		  ;
	}
	void Jsonize(JsonIO& json) {
		json
			("title", title)
			("target_song", target_song)
			("reference_song", reference_song)
			("description", description)
			;
	}
};




struct Component :
	DataFile
{
	String						entity;
	String						name;
	String						reference;
	String						scripts_file_title;
	
	Snapshot*					snapshot = 0;
	
	void Store(Snapshot& snap);
	void LoadTitle(Snapshot& snap, String title);
	void ReloadStructure();
	String GetAnyTitle(Entity& a) const;
	
	void Serialize(Stream& s) {TODO}
	void Jsonize(JsonIO& json) {
		json
			("entity", entity)
			("name", name)
			("reference", reference)
			("script_file_title", scripts_file_title)
			;
	}
	
};


END_TEXTLIB_NAMESPACE


#endif
