#include "HighLib.h"

NAMESPACE_TOPSIDE_BEGIN


HiAnimProgram::HiAnimProgram() {
	
	
}

void HiAnimProgram::Clear() {
	vm.Clear();
	code.Clear();
	
	
}

void HiAnimProgram::Init(HiValue lambda) {
	ASSERT(lambda.IsLambda());
	vm = new Hi(ctx->global, ctx->op_limit, lambda.GetLambdaRW());
}

void HiAnimProgram::ContinueVm() {
	vm->StopSleep();
}

void HiAnimProgram::Iterate() {
	if (vm) {
		if (vm->CheckSleepFinished()) {
			vm->Run();
			
			if (!vm->IsSleepExit()) {
				//tc.Kill();
				ctx->WhenStopProgram(*this);
			}
		}
	}
}

bool HiAnimProgram::IsRunning() const {
	return vm && vm->IsRunning();
}


NAMESPACE_TOPSIDE_END
