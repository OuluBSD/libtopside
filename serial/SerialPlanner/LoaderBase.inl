#include "SerialPlanner.h"

NAMESPACE_SERIAL_BEGIN


template <class ParserDef, class LoaderParent>
void ScriptLoaderBase<ParserDef,LoaderParent>::Forward() {
	ASSERT(!IsReady() && !IsFailed());
	
	if (status == ScriptStatus::IN_BEGINNING || status == ScriptStatus::RETRY) {
		ForwardLoops();
		
		CheckFlags(true);
		if (status == ScriptStatus::IN_BEGINNING)
			return;
		
		SolveInternal();
		CheckFlags(false);
	}
	else if (status == ScriptStatus::INPUT_IS_WAITING ||
			 status == ScriptStatus::OUTPUT_IS_WAITING) {
		SetError("no compatible side-source was found for side-sink");
	}
	else {
		TODO
	}
	
}

template <class ParserDef, class LoaderParent>
void ScriptLoaderBase<ParserDef,LoaderParent>::CheckStatus(ScriptStatus s) {
	if (s == ScriptStatus::OUTPUT_IS_WAITING ||
		s == ScriptStatus::INPUT_IS_WAITING) {
		any_waiting = true;
	}
	else if (s == ScriptStatus::IN_BEGINNING || s == ScriptStatus::RETRY) {
		any_retrying = true;
	}
	else if (s == ScriptStatus::FAILED) {
		any_failed = true;
	}
	
	if (s != ScriptStatus::READY)
		all_ready = false;

}

template <class ParserDef, class LoaderParent>
void ScriptLoaderBase<ParserDef,LoaderParent>::CheckFlags(bool allow_internal) {
	ResetFlags();
	LoopStatus();
	
	if (any_failed) {
		status = ScriptStatus::FAILED;
	}
	else if (any_retrying) {
		status = ScriptStatus::IN_BEGINNING;
	}
	else if (any_waiting) {
		if (allow_internal) {
			status = ScriptStatus::SOLVE_INTERNAL_CONNECTIONS;
		}
	}
	else if (all_ready) {
		status = ScriptStatus::READY;
	}
}

template <class ParserDef, class LoaderParent>
void ScriptLoaderBase<ParserDef,LoaderParent>::SolveInternal() {
	if (status == ScriptStatus::SOLVE_INTERNAL_CONNECTIONS) {
		//LOG(GetTreeString(0));
		ScriptConnectionSolver conn(GetLoader().GetSideIdCounter());
		if (conn.Solve(this)) {
			SetRetryDeep();
		}
		else {
			if (conn.IsMissingInput()) {
				status = ScriptStatus::OUTPUT_IS_WAITING;
			}
			else if (conn.IsMissingOutput()) {
				status = ScriptStatus::INPUT_IS_WAITING;
			}
			else {
				LOG(conn.GetError());
				// check error and not-found
				TODO
			}
		}
	}
}


NAMESPACE_SERIAL_END
