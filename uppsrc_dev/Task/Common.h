#ifndef _Task_Common_h_
#define _Task_Common_h_


BEGIN_TEXTLIB_NAMESPACE


typedef enum : int {
	AITASK_TRANSLATE,
	AITASK_TRANSLATE_SONG_DATA,
	AITASK_CREATE_IMAGE,
	AITASK_EDIT_IMAGE,
	AITASK_VARIATE_IMAGE,
	AITASK_VISION,
	AITASK_RAW_COMPLETION,
	AITASK_GENERIC_PROMPT,
	
	AITASK_COUNT
} AiTaskType;


END_TEXTLIB_NAMESPACE

NAMESPACE_UPP
using namespace TextLib;
NTL_MOVEABLE(AiTaskType)
END_UPP_NAMESPACE

BEGIN_TEXTLIB_NAMESPACE


struct VisionArgs {
	int fn = 0;
	
	void Jsonize(JsonIO& json) {
		json	("fn", fn)
				;
	}
	String Get() const {return StoreAsJson(*this);}
	void Put(const String& s) {LoadFromJson(*this, s);}
	
};

struct GenericPromptArgs {
	int fn = 0;
	VectorMap<String, Vector<String>> lists;
	String response_title;
	bool is_numbered_lines = false;
	
	void Jsonize(JsonIO& json) {
		json	("fn", fn)
				("lists", lists)
				("t", response_title)
				("nl", is_numbered_lines)
				;
	}
	
	String Get() const {return StoreAsJson(*this);}
	void Put(const String& s) {LoadFromJson(*this, s);}
};


END_TEXTLIB_NAMESPACE


#endif
