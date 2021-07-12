#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


template <class ParserDef, class LoaderParent>
void EonLoaderBase<ParserDef,LoaderParent>::Forward() {
	ASSERT(!IsReady() && !IsFailed());
	
	if (status == EonStatus::IN_BEGINNING || status == EonStatus::RETRY) {
		ForwardLoops();
		
		CheckFlags(true);
		if (status == EonStatus::IN_BEGINNING)
			return;
		
		SolveInternal();
		CheckFlags(false);
	}
	else if (status == EonStatus::INPUT_IS_WAITING) {
		TODO
	}
	else {
		TODO
	}
	
}

template <class ParserDef, class LoaderParent>
void EonLoaderBase<ParserDef,LoaderParent>::CheckStatus(EonStatus s) {
	if (s == EonStatus::OUTPUT_IS_WAITING ||
		s == EonStatus::INPUT_IS_WAITING) {
		any_waiting = true;
	}
	else if (s == EonStatus::IN_BEGINNING || s == EonStatus::RETRY) {
		any_retrying = true;
	}
	
	if (s != EonStatus::READY)
		all_ready = false;

}

template <class ParserDef, class LoaderParent>
void EonLoaderBase<ParserDef,LoaderParent>::CheckFlags(bool allow_internal) {
	ResetFlags();
	LoopStatus();
	
	if (any_retrying) {
		status = EonStatus::IN_BEGINNING;
	}
	else if (any_waiting) {
		if (allow_internal) {
			status = EonStatus::SOLVE_INTERNAL_CONNECTIONS;
		}
	}
	else if (all_ready) {
		status = EonStatus::READY;
	}
}

template <class ParserDef, class LoaderParent>
void EonLoaderBase<ParserDef,LoaderParent>::SolveInternal() {
	if (status == EonStatus::SOLVE_INTERNAL_CONNECTIONS) {
		//LOG(GetTreeString(0));
		EonConnectionSolver conn(GetLoader().GetSideIdCounter());
		if (conn.Solve(this)) {
			SetRetryDeep();
		}
		else {
			if (conn.IsMissingInput()) {
				status = EonStatus::OUTPUT_IS_WAITING;
			}
			else if (conn.IsMissingOutput()) {
				status = EonStatus::INPUT_IS_WAITING;
			}
			else {
				LOG(conn.GetError());
				// check error and not-found
				TODO
			}
		}
	}
}


NAMESPACE_ECS_END
