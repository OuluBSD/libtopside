#ifndef _AccelCore_Stream_h_
#define _AccelCore_Stream_h_

NAMESPACE_TOPSIDE_BEGIN


class AccelStream {
public:
	
	// Generic
	Time time;
	TimeStop total_time;
	double frame_seconds = 0;
	int time_us = 0;
	
	// Controller
	Point mouse, mouse_toycompat_drag, mouse_toycompat_click;
	
	// Video
	SystemDraw* draw = 0;
	Size video_size;
	Point video_offset;
	TimeStop vframe_time;
	double vtotal_seconds = 0;
	int vframes = 0;
	double fps_limit = 60;
	int depth = 0;
	
	// Audio
	Audio* sys_aud = 0;
	double atotal_seconds = 0;
	double audio_last_sync_sec = 0;
	AudioFormat aud_fmt;
	int aframes = 0;
	int aframes_after_sync = 0;
	int asink_frame = 0;
	bool is_audio_sync = 0;
	
	
	AccelStream() {Clear();}
	void Clear();
	void Reset();
	
};





NAMESPACE_TOPSIDE_END

#endif
