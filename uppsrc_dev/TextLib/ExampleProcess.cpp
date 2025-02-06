#include "TextLib.h"


BEGIN_TEXTLIB_NAMESPACE


ExampleProcess::ExampleProcess() {
	
}

int ExampleProcess::GetPhaseCount() const {
	return PHASE_COUNT;
}

int ExampleProcess::GetBatchCount(int phase) const {
	switch (phase) {
		case PHASE_GENERATE:			return 1;
		default: return 1;
	}
}

int ExampleProcess::GetSubBatchCount(int phase, int batch) const {
	switch (phase) {
		default: return 1;
	}
}

void ExampleProcess::DoPhase() {
	switch (phase) {
		case PHASE_GENERATE:			Generate(); return;
		case PHASE_GENERATE_DETAILS:	GenerateDetails(); return;
		default: return;
	}
}

ExampleProcess& ExampleProcess::Get(Profile& p) {
	static ArrayMap<String, ExampleProcess> arr;
	
	String key = "PROFILE(" + p.name + ")";
	ExampleProcess& ts = arr.GetAdd(key);
	ts.profile = &p;
	ts.owner = p.owner;
	return ts;
}

void ExampleProcess::Generate() {
	if (batch == 0 && sub_batch == 0) {
		tasks.Clear();
		for(int i = 0; i < 10; i++) {
			Task& t = tasks.Add();
			t.category = i;
		}
	}
	
	if (batch >= tasks.GetCount()) {
		NextPhase();
		return;
	}
	
	Task& t = tasks[batch];
	
	
	/*SetWaiting(1);
	TaskMgr& m = TaskMgr::Single();
	m.GetBiographyGenerator(args, [this](String result) {
		
		NextBatch();
		SetWaiting(0);
	});*/
}

void ExampleProcess::GenerateDetails() {
	NextPhase();
}

END_TEXTLIB_NAMESPACE

