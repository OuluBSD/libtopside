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
		SetError("linking side connections failed");
		SetStatus(FAILED);
	}
	#if 0
	else if (status == MAKE_OPTION_LINK_VECTOR ||
			 status == PRUNE_OPTION_LINKS ||
			 status == LINK_PLANNER) {
		SolveInternal();
		CheckFlags();
	}
	else if (status == WAITING_PARENT) {
		CheckFlags();
	}
	else if (status == ScriptStatus::SOURCE_IS_WAITING ||
			 status == ScriptStatus::SINK_IS_WAITING) {
		SetError("no compatible side-source was found for side-sink");
	}
	#endif
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
		s == ScriptStatus::WAITING_CHILDREN
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

#if 0
template <class ParserDef, class LoaderParent>
void ScriptLoaderBase<ParserDef,LoaderParent>::SolveInternal() {
	if (status == MAKE_OPTION_LINK_VECTOR ||
		status == PRUNE_OPTION_LINKS ||
		status == LINK_PLANNER
	) {
		//LOG(GetTreeString(0));
		ScriptConnectionSolver conn(GetLoader().GetSideIdCounter());
		if (conn.Solve(this)) {
			CheckStatusDeep();
		}
		else {
			TODO
			#if 0
			if (conn.IsWaitingSource()) {
				SetStatus(ScriptStatus::SOURCE_IS_WAITING);
			}
			else if (conn.IsWaitingSink()) {
				SetStatus(ScriptStatus::SINK_IS_WAITING);
			}
			else {
				LOG(conn.GetError());
				// check error and not-found
				TODO
			}
			#endif
		}
	}
	else if (status == READY) {
		// pass
	}
	else {
		TODO
	}
}
#endif

NAMESPACE_SERIAL_END
