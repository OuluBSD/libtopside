#include "TextLib.h"


BEGIN_TEXTLIB_NAMESPACE


SolverBase::SolverBase() {
	
}

void SolverBase::Process() {
	if (parallel)
		ProcessInParallel();
	else
		ProcessInOrder();
}

void SolverBase::ProcessInParallel() {
	generation = 0;
	phase = 0;
	batch = 0;
	sub_batch = -1;
	
	TimeStop update_ts, progress_ts;
	time_started = GetSysTime();
	
	int workers = max(1,CPU_Cores()-1);
	this->worker_data.Clear();
	this->worker_data.SetCount(workers);
	for(int i = 0; i < workers; i++)
		Thread::Start(THISBACK1(ParallelWorker, i));
	
	while (running && !Thread::IsShutdownThreads()) {
		if (waiting) {
			Sleep(10);
			continue;
		}
		
		if (update_ts.Seconds() >= 0.1) {
			PostProgress();
			update_ts.Reset();
		}
		
		if (progress_ts.Seconds() >= 10) {
			PostRemaining();
			progress_ts.Reset();
		}
		
		Sleep(1);
	}
	
	running = false;
	stopped = true;
}

void SolverBase::PostRemaining() {
	double progress = GetProgress();
	if (progress > 0.0) {
		Time now = GetSysTime();
		double seconds = now.Get() - time_started.Get();
		double per_second = progress / seconds;
		double remaining = 1 - progress;
		double remaining_seconds = remaining / per_second;
		double mins = remaining_seconds / 60.0;
		double hours = mins / 60.0;
		double secs = fmod(remaining_seconds, 60.0);
		mins = fmod(mins, 60.0);
		String s = Format("Remaining: %d hours, %d mins, %d seconds", (int)hours, (int)mins, (int)secs);
		//LOG(s);
		WhenRemaining(s);
	}
}

void SolverBase::SetNotRunning() {running = false;}
void SolverBase::SetWaiting(bool b) {waiting = b;}
void SolverBase::SetGenerations(int i) {generation_count = i;}
void SolverBase::MovePhase(int p) {phase = p; batch = 0; sub_batch = 0;}

void SolverBase::NextPhase() {
	if (parallel) return;
	phase++;
	batch = 0;
	sub_batch = 0;
}

void SolverBase::NextBatch() {
	if (parallel) return;
	batch++;
	sub_batch = 0;
}

void SolverBase::NextSubBatch() {
	if (parallel) return;
	sub_batch++;
}

int& SolverBase::WorkerId() {
	thread_local static int i;
	return i;
}

SolverBase::WorkerData& SolverBase::Worker() {
	int id = WorkerId();
	return worker_data[id];
}
	
void SolverBase::ParallelWorker(int id) {
	WorkerId() = id;
	WorkerData& w = Worker();
	int phase_count = GetPhaseCount();
	while (running && !Thread::IsShutdownThreads()) {
		
		task_lock.Enter();
		{
			sub_batch++;
			if (sub_batch >= GetSubBatchCount(phase, batch)) {
				sub_batch = 0;
				batch++;
				if (batch >= GetBatchCount(phase)) {
					phase++;
					if (phase >= GetPhaseCount()) {
						running = false;
					}
				}
			}
		}
		w.phase = phase;
		w.batch = batch;
		w.sub_batch = sub_batch;
		task_lock.Leave();
		if (!running) {
			time_stopped = GetSysTime();
			WhenReady();
			break;
		}
		
		
		if (phase >= 0 && phase < phase_count) {
			DoPhase();
		}
		#if 0
		else if (id == 0) {
			generation++;
			phase = 0;
			batch = 0;
			sub_batch = 0;
			
			if (generation >= generation_count) {
				time_stopped = GetSysTime();
				WhenReady();
				break;
			}
		}
		#endif
	}
}

void SolverBase::ProcessInOrder() {
	generation = 0;
	phase = 0;
	batch = 0;
	sub_batch = 0;
	
	TimeStop update_ts, progress_ts;
	
	while (running && !Thread::IsShutdownThreads()) {
		if (waiting) {
			Sleep(10);
			continue;
		}
		
		int phase_count = GetPhaseCount();
		
		if (generation == 0 && phase == 0 && batch == 0 && sub_batch == 0) {
			time_started = GetSysTime();
		}
		
		if (phase >= 0 && phase < phase_count) {
			DoPhase();
		}
		else {
			generation++;
			phase = 0;
			batch = 0;
			sub_batch = 0;
			
			if (generation >= generation_count) {
				time_stopped = GetSysTime();
				WhenReady();
				break;
			}
		}
		
		if (update_ts.Seconds() >= 0.1) {
			PostProgress();
			update_ts.Reset();
		}
		
		if (progress_ts.Seconds() >= 10) {
			PostRemaining();
			progress_ts.Reset();
		}
		
		Sleep(1);
	}
	
	running = false;
	stopped = true;
}

void SolverBase::StopAll() {
	LOG("SolverBase::StopAll: TODO");
}

TextDatabase& SolverBase::GetDatabase() const {
	return MetaDatabase::Single().db;
}

double SolverBase::GetProgress() {
	static const int LEVELS = 3;
	int a[LEVELS], t[LEVELS];
	a[0] = phase;
	a[1] = batch;
	a[2] = sub_batch;
	t[0] = GetPhaseCount();
	t[1] = GetBatchCount(a[0]);
	t[2] = GetSubBatchCount(a[0], a[1]);
	int actual = ((a[0]) * t[1] + a[1]) * t[2] + a[2];
	int total = t[0] * t[1] * t[2];
	if (!total)
		return 0;
	ASSERT(actual >= 0);
	ASSERT(total > 0);
	//ASSERT(actual <= total);
	actual = min(actual, total);
	double f = (double)actual / (double)total;
	return f;
}

void SolverBase::PostProgress() {
	int total = 10000;
	int actual = (int)(total * GetProgress());
	WhenProgress(actual, total);
}


END_TEXTLIB_NAMESPACE