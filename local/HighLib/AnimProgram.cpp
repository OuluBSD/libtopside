#include "HighLib.h"

NAMESPACE_TOPSIDE_BEGIN


HiAnimProgram::HiAnimProgram() {
	Clear();
	user_group = -1;
}

void HiAnimProgram::Clear() {
	vm.Clear();
	code.Clear();
	user = HiValue();
	user_flags = 0;
	user_type = 0;
	//not this: user_group = -1;
	
}

void HiAnimProgram::Init(HiValue lambda) {
	ASSERT(lambda.IsLambda());
	vm = new Hi(ctx->global, ctx->op_limit, lambda.GetLambdaRW());
}

void HiAnimProgram::Continue() {
	vm->StopSleep();
}

void HiAnimProgram::Stop() {
	if (vm) {
		vm->Stop();
		WhenStop(*this);
	}
}

bool HiAnimProgram::Process() {
	Iterate();
	return vm ? vm->IsRunning() : false;
}

void HiAnimProgram::Iterate() {
	if (is_native) {
		if (is_native_running && !native_fn()) {
			is_native_running = false;
			Stop();
		}
	}
	else {
		if (vm) {
			if (vm->CheckSleepFinished()) {
				vm->Run();
				
				if (!vm->IsSleepExit()) {
					Stop();
				}
			}
		}
	}
}

bool HiAnimProgram::IsRunning() const {
	return vm && vm->IsRunning();
}

HiAnimProgram& HiAnimProgram::Set(Gate0 cb, HiValue a0, HiValue a1) {
	Clear();
	this->a0 = a0;
	this->a1 = a1;
	is_native = true;
	is_native_running = true;
	native_fn = cb;
	return *this;
}

HiAnimProgram& HiAnimProgram::Set(HiValue *self, HiValue fn, HiValue a0, HiValue a1) {
	HiGlobal& g = ctx->global;
	
	Clear();
	is_native = false;
	
	// Find & check lambda before setting fields
	HiValue lambda;
	String fn_name;
	if (fn.IsLambda()) {
		lambda = fn;
		fn_name = "<lambda>";
	}
	else {
		fn_name = fn.ToString();
		fn_name.Replace("\"", "");
		if (self && self->IsMap())
			lambda = self->MapGet(fn_name);
		if (!lambda.IsLambda()) {
			lambda = g.Get(fn_name, HiValue());
			if (!lambda.IsLambda()) {
				LOG("Key '" << fn_name << "' is not lambda");
				return *this;
			}
		}
	}
	
	Vector<HiValue> arg;
	if (!a0.IsVoid()) arg << a0;
	if (!a0.IsVoid() && !a1.IsVoid()) arg << a1;
	
	const HiLambda& l = lambda.GetLambda();
	if (arg.GetCount() != l.arg.GetCount()) {
		String argnames;
		for(int i = 0; i < l.arg.GetCount(); i++)
			argnames << (i ? ", " : "") << l.arg[i];
		LOG(Format("invalid number of arguments (%d passed, expected: %s)", arg.GetCount(), argnames));
		return *this;
	}
	
	// Set fields
	this->a0 = a0;
	this->a1 = a1;
	this->fn_name = fn_name;
	
	// Initialize esc runner
	ASSERT(vm.IsEmpty());
	vm = new Hi(g, l.code, ctx->op_limit, l.filename, l.line);
	auto& e = *vm;
	if (self)
		e.Self() = *self;
	for(int i = 0; i < l.arg.GetCount(); i++)
		e.Var().GetPut(l.arg[i]) = arg[i];
	
	//e.no_return = e.no_break = e.no_continue = true;
	//e.loop = 0;
	//e.skipexp = 0;
	
	ASSERT(vm->IsRunning());
	ASSERT(IsRunning());
	LOG("Script::Set: started " << fn_name);
	
	return *this;
}


NAMESPACE_TOPSIDE_END
