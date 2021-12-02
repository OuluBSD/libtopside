#ifndef _Graphics_State_h_
#define _Graphics_State_h_

NAMESPACE_TOPSIDE_BEGIN

namespace ShaderVar {
enum {
	VAR_AUDIOTIME,
	VAR_VIEW,
	VAR_PROJECTION,
	VAR_SCALE,
	VAR_MODEL,
	
	VAR_COMPAT_RESOLUTION,
	VAR_COMPAT_TIME,
	VAR_COMPAT_TIMEDELTA,
	VAR_COMPAT_FRAME,
	VAR_COMPAT_MOUSE,
	VAR_COMPAT_DATE,
	VAR_COMPAT_SAMPLERATE,
	VAR_COMPAT_OFFSET,
	VAR_COMPAT_CHANNEL0,
	VAR_COMPAT_CHANNEL1,
	VAR_COMPAT_CHANNEL2,
	VAR_COMPAT_CHANNEL3,
	VAR_COMPAT_FRAMERATE,
	VAR_COMPAT_CHANNELTIME,
	VAR_COMPAT_CHANNELRESOLUTION0,
	VAR_COMPAT_CHANNELRESOLUTION1,
	VAR_COMPAT_CHANNELRESOLUTION2,
	VAR_COMPAT_CHANNELRESOLUTION3,
	VAR_COMPAT_BLOCKOFFSET,
	
	VAR_COUNT,
};

typedef enum {
	SAMPLE_FLOAT,
	SAMPLE_U8,
	SAMPLE_U16,
	SAMPLE_U32,
	SAMPLE_S32,
} Sample;

// note: relative to GL_VERTEX_SHADER_BIT etc.
typedef enum {
	PROG_NULL = -1,
	
	PROG_VERTEX,
	PROG_FRAGMENT,
	PROG_GEOMETRY,
	PROG_TESS_CONTROL,
	PROG_TESS_EVALUATION,
	
	PROG_COUNT
} Type;

typedef enum {
	FILTER_NEAREST,
	FILTER_LINEAR,
	FILTER_MIPMAP,
	
	DEFAULT_FILTER = FILTER_LINEAR
} Filter;

typedef enum {
	WRAP_CLAMP,
	WRAP_REPEAT,
	
	DEFAULT_WRAP = WRAP_REPEAT
} Wrap;

typedef enum {
	INVALID = -1,
	EMPTY,
	BUFFER,
	KEYBOARD,
	TEXTURE,
	CUBEMAP,
	WEBCAM,
	MUSIC,
	MUSICSTREAM,
	VOLUME,
	VIDEO,
} InputType;

extern const char* names[ShaderVar::VAR_COUNT+1];
extern const bool is_obj_var[ShaderVar::VAR_COUNT+1];

static const int INPUT_COUNT = 4;

}


struct FramebufferState : RTTIBase {
	RTTI_DECL0(FramebufferState)
	
	using Sample = ShaderVar::Sample;
	using Filter = ShaderVar::Filter;
	using Wrap = ShaderVar::Wrap;
	
	virtual ~FramebufferState() {}
	
	// meta
	int		id = -1;
	String	name;
	String	description;
	
	// stage
	bool	is_win_fbo = 0;
	bool	is_read_fb_output = 0;
	bool	is_audio = 0;
	bool	is_cubemap = 0;
	bool	is_time_used = 0;
	Filter	filter;
	Wrap	wrap;
	
	// framebuffer
	int8	channels = 0;
	Size	size;
	int		depth = 0;
	Sample	sample = ShaderVar::SAMPLE_FLOAT;
	Point	offset;
	int8	buf_i = 0;
	bool	is_doublebuf = 0;
	
	// context values
	double	time_total = 0;
	double	frame_time = 0;
	double	block_offset = 0;
	int		frames = 0;
	double	fps = 0;
	double	time_us = 0;
	double	sample_rate = 0;
	Time	time;
	
	
	
	virtual FramebufferObject& NewObject() = 0;
	
	/*void Free() {name.Clear(); description.Clear();}
	void Reset() {memset(this, 0, sizeof(FramebufferState));}
	void Default() {id = -1;}
	void Clear() {Free(); Reset(); Default();}*/
};

struct ShaderState : RTTIBase {
	RTTI_DECL0(ShaderState)
	
	using Type = ShaderVar::Type;
	
	virtual ~ShaderState() {}
	
	// meta
	bool enabled;
	
	// shader stage
	Type	type = ShaderVar::PROG_NULL;
	String	code;
	String	library;
	
	// vertex shader
	mat4	view;
	mat4	projection;
	mat4	scale;
	mat4	offset;
	
	
	
	/*void Free() {code.Clear(); library.Clear();}
	void Reset() {memset(this, 0, sizeof(ShaderState));}
	void Default() {}
	void Clear() {Free(); Reset(); Default();}*/
};

struct FramebufferInputState : RTTIBase {
	RTTI_DECL0(FramebufferInputState)
	
	using InputType = ShaderVar::InputType;
	
	virtual ~FramebufferInputState() {}
	
	int id = -1;
	InputType type;
	
	
	/*void Free() {}
	void Reset() {memset(this, 0, sizeof(FramebufferInputState));}
	void Default() {}
	void Clear() {Free(); Reset(); Default();}*/
};

NAMESPACE_TOPSIDE_END

#endif
