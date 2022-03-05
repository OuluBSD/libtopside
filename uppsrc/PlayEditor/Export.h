#ifndef _PlayEditor_Export_h_
#define _PlayEditor_Export_h_

NAMESPACE_TOPSIDE_BEGIN


class VideoExporter {
	
	static const int fps = 25;
	static const int block_frames = 10 * fps;
	
	struct Task : Moveable<Task> {
		int block;
		int frame;
		int total_frame;
		double time;
		double total_time;
		int in_process_thrd = -1;
		bool ready = 0;
		
	};
	
	Size frame_sz;
	
	PlayScript& script;
	Array<PlayRenderer> rends;
	RunningFlag flag;
	int thrd_count = 1;
	Vector<Task> tasks;
	Task* task_iter;
	Mutex lock;
	int ready_count = 0;
	bool last_block_only = false;
	
	int total_time = 0;
	int total_frames = 0;
	
	
	Task* GetTask(int thrd_i);
	void ProcessTask(int thrd_i, Task& task);
	void Process(int thrd_i);
	void ExportSrt();
	
	String GetExportDirectory();
	String GetBlockDirectory(int block);
	String GetFramePath(int block, int frame);
	
public:
	typedef VideoExporter CLASSNAME;
	VideoExporter(PlayScript& script);
	~VideoExporter();
	
	void SetTotalTime(int ms);
	void SetLastBlockOnly(bool b) {last_block_only = b;}
	void SetFrameSize(Size sz) {frame_sz = sz;}
	void Start();
	void Stop();
	bool IsRunning() const {return flag.IsRunning();}
	int GetActual() const {return ready_count;}
	int GetTotal() const {return tasks.GetCount();}
	
	Callback WhenEnd;
	
	static String GetSrtTimeString(int time);
	
};


NAMESPACE_TOPSIDE_END

#endif
