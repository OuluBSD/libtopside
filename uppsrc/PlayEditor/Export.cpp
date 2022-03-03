#include "PlayEditor.h"
#include <plugin/jpg/jpg.h>

NAMESPACE_TOPSIDE_BEGIN


VideoExporter::VideoExporter(PlayScript& script) : script(script) {
	thrd_count = max(1, CPU_Cores() - 1);
	frame_sz = Size(1280,720);
	
}

void VideoExporter::SetTotalTime(int ms) {
	total_time = ms;
	total_frames = (ms * 25) / 1000;
	LOG("VideoExporter::SetTotalTime: " << total_time / 1000 << " seconds, " << total_frames << " frames");
}

void VideoExporter::Start() {
	ASSERT(total_time > 0);
	if (total_time <= 0) return;
	
	Stop();
	
	tasks.Clear();
	tasks.SetCount(total_frames);
	{
		ready_count = 0;
		
		double total_time_end = this->total_time * 0.001;
		double time_step = 1.0 / (double)fps;
		double total_time = 0.0;
		
		int total_frame = 0;
		int block_i = 0;
		int block_frame_begin = 0;
		double block_time_begin = 0;
		bool block_exists = DirectoryExists(GetBlockDirectory(0));
		
		for (Task& t : tasks) {
			t.total_frame = total_frame;
			t.total_time = total_time;
			t.frame = total_frame - block_frame_begin;
			t.time = total_time - block_time_begin;
			t.block = block_i;
			t.in_process_thrd = -1;
			t.ready = false;
			
			if (block_exists && FileExists(GetFramePath(t.block, t.frame))) {
				t.ready = true;
				ready_count++;
			}
			
			total_time += time_step;
			total_frame++;
			if (total_frame % block_frames == 0) {
				block_i++;
				block_frame_begin += block_frames;
				block_time_begin = total_time;
				block_exists = DirectoryExists(GetBlockDirectory(block_i));
			}
		}
	}
	task_iter = tasks.Begin();
	
	rends.Clear();
	for(int i = 0; i < thrd_count; i++)
		rends.Add(new PlayRenderer(script));
	for (PlayRenderer& rend : rends)
		rend.SetFrameSize(frame_sz);
	
	flag.Start(thrd_count);
	for(int i = 0; i < thrd_count; i++) {
		Thread::Start(THISBACK1(Process, i));
	}
}

String VideoExporter::GetBlockDirectory(int block) {
	return AppendFileName(GetFileDirectory(script.filepath), Format("block%04d", block));
}

String VideoExporter::GetFramePath(int block, int frame) {
	return AppendFileName(GetBlockDirectory(block), Format("%05d.jpg", frame));
}

void VideoExporter::Stop() {
	if (!flag.IsRunning()) return;
	flag.SetNotRunning();
	//hangs app: flag.Stop();
}

void VideoExporter::Process(int thrd_i) {
	LOG("VideoExporter::Process: " << thrd_i << " started");
	
	while (flag.IsRunning()) {
		Task* t = GetTask(thrd_i);
		if (!t)
			break;
		ProcessTask(thrd_i, *t);
	}
	
	bool last = flag.DecreaseRunning() == 0;
	LOG("VideoExporter::Process: " << thrd_i << " stopped");
	
	if (last)
		WhenEnd();
}

VideoExporter::Task* VideoExporter::GetTask(int thrd_i) {
	Task* ret = 0;
	lock.Enter();
	
	while (task_iter != tasks.End()) {
		if (!task_iter->ready && task_iter->in_process_thrd < 0) {
			task_iter->in_process_thrd = thrd_i;
			ret = task_iter;
		}
		task_iter++;
		if (ret)
			break;
	}
	
	lock.Leave();
	return ret;
}

void VideoExporter::ProcessTask(int thrd_i, Task& task) {
	LOG("VideoExporter::ProcessTask: " << thrd_i << " started task " << task.total_frame);
	
	String block_dir = GetBlockDirectory(task.block);
	RealizeDirectory(block_dir);
	
	String path = GetFramePath(task.block, task.frame);
	PlayRenderer& rend = rends[thrd_i];
	
	PlayRendererConfig cfg;
	cfg.render_bg = true;
	cfg.render_blur = true;
	cfg.render_notes = true;
	cfg.render_text_bending = true;
	
	rend.Seek(task.total_time * 1000);
	Image img = rend.Render(cfg);
	
	JPGEncoder enc;
	enc.Quality(100);
	enc.SaveFile(path, img);
	
	lock.Enter();
	ready_count++;
	lock.Leave();
	LOG("VideoExporter::ProcessTask: " << thrd_i << " stopped task " << task.total_frame);
}



NAMESPACE_TOPSIDE_END
