#ifndef _TextLib_SolverBase_h_
#define _TextLib_SolverBase_h_

BEGIN_TEXTLIB_NAMESPACE


class SolverBase {
	
protected:
	struct WorkerData : Moveable<WorkerData> {
		int phase = 0, batch = 0, sub_batch = 0;
	};
	Vector<WorkerData> worker_data;
	static int& WorkerId();
	WorkerData& Worker();
	Mutex task_lock, data_lock;
	
	Time time_started, time_stopped;
	int generation = 0, phase = 0, batch = 0, sub_batch = 0, batch_count = 0;
	int generation_count = 1;
	Owner* owner = 0;
	Profile* profile = 0;
	
	bool waiting = false;
	bool running = false, stopped = true;
	bool skip_ready = true;
	bool parallel = false;
	
	void Process();
	void ProcessInParallel();
	void ProcessInOrder();
	void ParallelWorker(int id);
	
	void PostProgress();
	void PostRemaining();
	void SetNotRunning();
	void SetWaiting(bool b);
	void SetGenerations(int i);
	void MovePhase(int p);
	void NextPhase();
	void NextBatch();
	void NextSubBatch();
	
	double GetProgress();
public:
	typedef SolverBase CLASSNAME;
	SolverBase();
	
	TextDatabase& GetDatabase() const;
	
	void SetParallel(bool b=true) {parallel = b;}
	
	void Start() {if (!running) {running = true; stopped = false; Thread::Start(THISBACK(Process));}}
	void Stop() {running = false; while (!stopped) Sleep(1);}
	void SetSkipReady(bool b) {skip_ready = false;}
	static void StopAll();
	
	bool IsRunning() const {return running;}
	
	virtual int GetPhaseCount() const = 0;
	virtual int GetBatchCount(int phase) const {return max(1, batch);}
	virtual int GetSubBatchCount(int phase, int batch) const {return max(1, sub_batch);}
	virtual void DoPhase() = 0;
	virtual void OnBatchError() {NextBatch();}
	
	Callback2<int,int> WhenProgress;
	Callback1<String> WhenRemaining;
	Event<> WhenReady;
	
};


END_TEXTLIB_NAMESPACE

#endif
