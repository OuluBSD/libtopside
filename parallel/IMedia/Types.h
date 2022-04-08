#ifndef _IMedia_Types_h_
#define _IMedia_Types_h_


NAMESPACE_PARALLEL_BEGIN


#define MEDIA_CLS_LIST(m) \
	MEDIA_CLS(MediaAtomBase, m) \
	\
	MEDIA_CLS(AudioFrameQueue, m) \
	MEDIA_CLS(VideoFrameQueue, m) \
	MEDIA_CLS(FileChannel, m) \
	MEDIA_CLS(FileInput, m) \
	\
	MEDIA_CLS(AudioFrame, m) \
	MEDIA_CLS(AudioInputFrame, m) \
	\
	MEDIA_CLS(VideoCodecFormat, m) \
	MEDIA_CLS(VideoSourceFormatResolution, m) \
	MEDIA_CLS(VideoSourceFormat, m) \
	MEDIA_CLS(VideoInputFrame, m) \
	MEDIA_CLS(VideoOutputFrame, m) \
	MEDIA_CLS(VideoLoaderBase, m) \
	\
	MEDIA_CLS(MediaStreamThread, m) \
	


#define MEDIA_RENDSYS_LIST \
	MEDIA_RSYS(Ffmpeg) \


#define MEDIA_RSYS(x) MEDIA_CLS_LIST(x)
	#define MEDIA_CLS(x, g) struct g##x;
		MEDIA_RENDSYS_LIST
	#undef MEDIA_CLS
	#define MEDIA_CLS(x, g) template <class Backend> struct x##T;
		MEDIA_RENDSYS_LIST
	#undef MEDIA_CLS
#undef MEDIA_RSYS


#ifdef flagFFMPEG
	#define FFMPEG_MEDIATYPE \
		MEDIATYPE(FfmpegMedia)
	#define FFMPEG_EXCPLICIT_INITIALIZE_CLASS(x) \
		template struct x <FfmpegMedia>;
#else
	#define FFMPEG_MEDIATYPE
	#define FFMPEG_EXCPLICIT_INITIALIZE_CLASS(x)
#endif

#define MEDIATYPE_LIST \
	 \
	FFMPEG_MEDIATYPE \


#define MEDIA_EXCPLICIT_INITIALIZE_CLASS(x) \
	 \
	FFMPEG_EXCPLICIT_INITIALIZE_CLASS(x) \




template <class Backend>
struct FfmpegT {
	#define MEDIA_RSYS(x) MEDIA_CLS_LIST(x)
	#define MEDIA_CLS(x, g) using x = x##T<Backend>;
		MEDIA_RENDSYS_LIST
	#undef MEDIA_CLS
	#undef MEDIA_RSYS
	
	using AudioInputFrameRef	= Ref<AudioInputFrame, RefParent1<PacketBufferParent>>;
	using VideoInputFrameRef	= Ref<VideoInputFrame, RefParent1<PacketBufferParent>>;
	using AudioFrameQueueRef	= Ref<AudioFrameQueue, RefParent1<PacketBufferParent>>;
	using VideoFrameQueueRef	= Ref<VideoFrameQueue, RefParent1<PacketBufferParent>>;
	
	
	struct Thread {
		
	};
	
	static Thread& Local();
	
	
	
};

struct FfmpegMedia : FfmpegT<FfmpegMedia> {};


NAMESPACE_PARALLEL_END

#endif
