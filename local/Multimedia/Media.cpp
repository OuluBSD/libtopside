#include "Multimedia.h"


NAMESPACE_OULU_BEGIN


int MediaInputStream::GetFormatCount() const {
	return fmts.GetCount();
}

const VideoInputFormat& MediaInputStream::GetFormat(int i) const {
	return fmts[i];
}

bool MediaInputStream::FindClosestFormat(Size cap_sz, double fps, double bw_min, double bw_max, int& ret_fmt, int& ret_res) {
	double tgt_bw = (double)cap_sz.cx * (double)cap_sz.cy * (double)fps;
	double bw_low = bw_min * tgt_bw;
	double bw_high = bw_max * tgt_bw;
	if (bw_low > bw_high)
		return false;
	
	struct Result : Moveable<Result> {
		double diff;
		int fmt, res;
		bool operator()(const Result& a, const Result& b) const {return a.diff < b.diff;}
	};
	Vector<Result> results;
	
	for(int i = 0; i < fmts.GetCount(); i++) {
		const VideoInputFormat& fmt = fmts[i];
		for(int j = 0; j < fmt.GetResolutionCount(); j++) {
			const VideoInputFormatResolution& fmt_res = fmt.GetResolution(j);
			VideoFormat vid_fmt = fmt_res.GetVideoFormat();
			Size fmt_sz = vid_fmt.res;
			double fmt_fps = vid_fmt.fps;
			double fmt_bw = (double)fmt_sz.cx * (double)fmt_sz.cy * fmt_fps;
			if (fmt_bw >= bw_low && fmt_bw <= bw_high) {
				Result& r = results.Add();
				r.diff = fabs(tgt_bw - fmt_bw);
				r.fmt = i;
				r.res = j;
			}
		}
	}
	if (results.GetCount()) {
		Sort(results, Result());
		if (0) {
			for(int i = 0; i < results.GetCount(); i++) {
				const Result& r = results[i];
				LOG(i << ": " << r.diff << ": " << r.fmt << ", " << r.res);
			}
		}
		const Result& res = results[0];
		ret_fmt = res.fmt;
		ret_res = res.res;
		return true;
	}
	return false;
}



void MediaStreamThread::Start(bool separate_thrd) {
	Stop();
	this->separate_thrd = separate_thrd;
	if (separate_thrd) {
		flag.Start();
		Thread::Start(THISBACK(Process));
	}
}

void MediaStreamThread::Stop() {
	flag.Stop();
}

void MediaStreamThread::Process() {
	TODO
	#if 0
	ASSERT(cap);
	if (cap) {
		while (cap && cap->IsDeviceOpen() && flag.IsRunning()) {
			if (cap->IsAnyQueueEmpty()) {
				if (!cap->Step(0.001)) {
					continue;
				}
				
				if (cap->ReadAudio()) {
					// got new audio frame
				}
				else if (cap->ReadVideo()) {
					// got new video frame
				}
				else
					Sleep(1);
			}
			
			if (loop_file && !cap->IsDeviceOpen())
				cap->ReopenDevice();
			
		}
	}
	flag.SetStopped();
	#endif
}

int MediaStreamThread::FillVideoBuffer() {
	if (cap)
		return cap->FillVideoBuffer();
	return false;
}

int MediaStreamThread::FillAudioBuffer() {
	if (cap)
		return cap->FillAudioBuffer();
	return false;
}


void MediaStreamThread::Clear() {
	if (cap) {
		cap->Close();
		cap = 0;
	}
}


#ifdef flagOPENGL
void MediaStreamThread::PaintOpenGL(GLuint active_tex) {
	if (cap)
		cap->GetVideo().PaintOpenGLTexture(active_tex);
}
#endif


NAMESPACE_OULU_END
