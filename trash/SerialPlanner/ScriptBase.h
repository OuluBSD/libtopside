#ifndef _SerialScript_ScriptBase_h_
#define _SerialScript_ScriptBase_h_

NAMESPACE_SERIAL_BEGIN


class ScriptLoader;



struct ScriptError : Moveable<ScriptError> {
	ScriptLoopLoader* ll = 0;
	String msg;
	int status = -1;
	
};



class ScriptLoopSegment {
public:
	AStar<Script::ActionNode>		as;
	Script::Plan					ep;
	Script::APlanNode*				start_node = 0;
	const Script::ActionNode*		stop_node = 0;
	//ScriptLoopLoader*				side_conn = 0;
	
	
	String GetTreeString(int id, int indent);
	
};

typedef enum {
	UNASSIGNED,
	
	IN_BEGINNING,
	WAITING_CHILDREN,
	
	SEARCH_SEGMENT,
	PRUNE_SEGMENT_GOALS,
	WAITING_PARENT_SIDE_LINKS,
	WAITING_OTHER_LOOPS,
	
	MAKE_OPTION_LINK_VECTOR,
	PRUNE_OPTION_LINKS,
	LINK_PLANNER,
	LINKER,
	
	READY,
	FAILED,
} ScriptStatus;

inline const char* GetScriptStatusString(ScriptStatus status) {
	const char* t = "<invalid status>";
	switch (status) {
		case IN_BEGINNING:					t = "In beginning"; break;
		case WAITING_PARENT_SIDE_LINKS:		t = "Waiting parent side links"; break;
		case WAITING_OTHER_LOOPS:				t = "Waiting other loops"; break;
		case WAITING_CHILDREN:				t = "Waiting children"; break;
		case SEARCH_SEGMENT:				t = "Search segment"; break;
		case PRUNE_SEGMENT_GOALS:			t = "Prune segment goals"; break;
		case MAKE_OPTION_LINK_VECTOR:		t = "Make option link vector"; break;
		case PRUNE_OPTION_LINKS:			t = "Prune option links"; break;
		case LINK_PLANNER:					t = "Link planner"; break;
		case LINKER:						t = "Linker"; break;
		case READY:							t = "Ready"; break;
		case FAILED:						t = "Failed"; break;
		case UNASSIGNED:					t = "Unassigned"; break;
		default: break;
	}
	return t;
}

String GetScriptStatusLine(int indent, ScriptStatus status, String extra_str=String());

class ScriptSystemLoader;
class ScriptMachineLoader;
class ScriptChainLoader;
class ScriptTopChainLoader;
class ScriptLoader;


int GetTotalSegmentCount(Vector<ScriptLoopLoader*>& v);


template <class ParserDef, class LoaderParent>
class ScriptLoaderBase : RTTIBase {
	
	
protected:
	void ResetFlags() {any_waiting_parent = false; any_waiting_children = false; any_linking = false; any_routing = false; all_ready = true; any_failed = false;}
	void CheckFlags();
	void CheckStatus(ScriptStatus s);
	
	int							iter = 0;
	
	
public:
	RTTI_DECL0(ScriptLoaderBase)
	virtual ~ScriptLoaderBase() {}
	
	LoaderParent&				parent;
	ParserDef&					def;
	ScriptStatus				status = IN_BEGINNING;
	String						err_str;
	int							id = -1;
	bool						any_waiting_parent = false;
	bool						any_waiting_children = false;
	bool						any_linking = false;
	bool						any_routing = false;
	bool						all_ready = false;
	bool						any_failed = false;
	int							prev_segment_count = 0;
	
	ScriptLoaderBase(LoaderParent& parent, int id, ParserDef& def) : parent(parent), id(id), def(def){}
	void				Forward();
	
	//void				SetStatusRetry() {SetStatus(RETRY);}
	void				SetError(String s) {err_str = s; SetStatus(FAILED); LOG("ScriptLoaderBase::SetError: this=" << HexStr(this) << ": " << s); }
	
	bool				IsFailed() const {return status == FAILED;}
	bool				IsReady() const {return status == READY;}
	bool				IsStatus(ScriptStatus s) const {return status == s;}
	int					GetId() const {return id;}
	ScriptStatus		GetStatus() const {return status;}
	ScriptLoader&		GetLoader() {return parent.GetLoader();}
	String				GetErrorString() const {return err_str;}
	
	virtual Script::Id	GetDeepId() const {Script::Id id = parent.GetDeepId(); id.Append(def.id); return id;}
	virtual void		SetStatus(ScriptStatus s) {status = s;}
	
	virtual void		Visit(RuntimeVisitor& vis) = 0;
	virtual String		GetTreeString(int indent) = 0;
	virtual void		GetLoops(Vector<ScriptLoopLoader*>& v) = 0;
	virtual void		ForwardLoops() = 0;
	virtual void		LoopStatus() = 0;
	virtual void		CheckStatusDeep() = 0;
	virtual void		GetDrivers(Vector<ScriptDriverLoader*>& v) {Panic("not implemented");}
	virtual void		GetStates(Vector<ScriptStateLoader*>& v) {Panic("not implemented");}
	
};



NAMESPACE_SERIAL_END

#endif
