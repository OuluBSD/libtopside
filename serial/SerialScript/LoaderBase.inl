#include "SerialPlanner.h"

NAMESPACE_SERIAL_BEGIN


template <class ParserDef, class LoaderParent>
void ScriptLoaderBase<ParserDef,LoaderParent>::Forward() {
	if (IsReady())
		return;
	
	ASSERT(!IsFailed());
	if (status == IN_BEGINNING)
		status = WAITING_CHILDREN;
	
	auto prev_status = status;
	
	if (status == WAITING_CHILDREN) {
		ForwardLoops();
		CheckFlags();
	}
	else if (status == MAKE_OPTION_LINK_VECTOR) {
		Vector<ScriptLoopLoader*> loops;
		GetLoops(loops);
		int segment_count = GetTotalSegmentCount(loops);
		if (segment_count == prev_segment_count) {
			SetError("linking side connections failed");
			SetStatus(FAILED);
		}
		else {
			prev_segment_count = segment_count;
			for (ScriptLoopLoader* l : loops)
				if (l->GetStatus() == WAITING_PARENT_SIDE_LINKS)
					l->SetStatus(WAITING_OTHER_LOOPS);
			CheckStatusDeep();
			SetStatus(WAITING_CHILDREN);
		}
	}
	else {
		TODO
	}
	
	ASSERT(prev_status != status || status == WAITING_CHILDREN);
}

template <class ParserDef, class LoaderParent>
void ScriptLoaderBase<ParserDef,LoaderParent>::CheckStatus(ScriptStatus s) {
	
	if (s == ScriptStatus::IN_BEGINNING) {
		TODO
	}
	else if (
		s == ScriptStatus::WAITING_CHILDREN ||
		s == ScriptStatus::WAITING_OTHER_LOOPS
	) {
		any_waiting_children = true;
	}
	else if (
		s == ScriptStatus::SEARCH_SEGMENT ||
		s == ScriptStatus::PRUNE_SEGMENT_GOALS
	) {
		any_routing = true;
	}
	else if (
		s == ScriptStatus::WAITING_PARENT_SIDE_LINKS
	) {
		any_waiting_parent = true;
	}
	else if (
		s == ScriptStatus::MAKE_OPTION_LINK_VECTOR ||
		s == ScriptStatus::PRUNE_OPTION_LINKS ||
		s == ScriptStatus::LINK_PLANNER ||
		s == ScriptStatus::LINKER
	) {
		any_linking = true;
	}
	else if (
		s == ScriptStatus::FAILED
	) {
		any_failed = true;
	}
	else if (
		s == ScriptStatus::READY
	) {
		// pass
	}
	else {
		TODO
	}
	
	if (s != ScriptStatus::READY)
		all_ready = false;
	
}

template <class ParserDef, class LoaderParent>
void ScriptLoaderBase<ParserDef,LoaderParent>::CheckFlags() {
	ResetFlags();
	LoopStatus();
	
	if (any_failed) {
		SetStatus(ScriptStatus::FAILED);
	}
	else if (any_routing || any_waiting_children || any_linking) {
		SetStatus(ScriptStatus::WAITING_CHILDREN);
	}
	else if (all_ready) {
		SetStatus(ScriptStatus::READY);
	}
	else if (any_waiting_parent) {
		SetStatus(ScriptStatus::MAKE_OPTION_LINK_VECTOR);
	}
	else {
		TODO
	}
	
}


NAMESPACE_SERIAL_END
