#ifndef _IMedia_Audio_h_
#define _IMedia_Audio_h_

NAMESPACE_PARALLEL_BEGIN


template <class Backend>
class AudioFrameT : public PacketBufferBase {
	
	
public:
	RTTI_DECL1(AudioFrameT, PacketBufferBase)
	virtual ~AudioFrameT() {}
	
	
	Format fmt;
	
	
	const Format&		GetFormat() const {return fmt;}
};


template <class Backend>
class AudioInputFrameT : public AudioFrameT<Backend> {
	
public:
	using Base = AudioFrameT<Backend>;
	RTTI_DECL1(AudioInputFrameT, Base)
	
	
};



















NAMESPACE_PARALLEL_END

#endif
