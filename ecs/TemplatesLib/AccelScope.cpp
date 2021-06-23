#include "TemplatesLib.h"

NAMESPACE_ECS_BEGIN


#if 0
void StageComponent::UpdateDevBuffersValT() {
	TODO
	/*auto& stream = GetStreamState();
	
	fb_size.Clear();
	auto& state = stream.template Get<ValSpec>();
	ASSERT(state.fmt.IsValid());
	ClearTex();
	TimeSeriesBase* ts = CastPtr<TimeSeriesBase>(&state.fmt);
	DimBase<1>* base1 = CastPtr<DimBase<1>>(&state.fmt);
	DimBase<2>* base2 = CastPtr<DimBase<2>>(&state.fmt);
	if (ts) {
		if (base1) {
			int sr = max(ts->sample_rate, 1);
			int ch = max(base1->channels, 1);
			fb_size = Size(sr, 1);
#if HAVE_OPENGL
			Ogl_CreateTex(
				fb_size, ch,
				0, has_fbo,
				StageComponentConf::FILTER_LINEAR,
				StageComponentConf::WRAP_CLAMP);
#endif
		}
		else if (base2) {
			fb_size = base2->size;
#if HAVE_OPENGL
			Ogl_CreateTex(
				fb_size, 4,
				1, has_fbo,
				StageComponentConf::FILTER_LINEAR,
				StageComponentConf::WRAP_CLAMP);
#endif
		}
		else {TODO}
	}
	else {TODO}*/
}

#endif



/*void AccelComponentGroupBase::RefreshPipeline() {
#if HAVE_OPENGL
	Ogl_CreatePipeline();
#endif
}*/


bool CreateForwardPacket(AccelComponentGroupBase& gr, InterfaceSinkBase& sink) {
	
	TODO
	#if 0
	using ValSpec				= typename ValDevSpec::Val;
	using DevSpec				= typename ValDevSpec::Dev;
	using ValData				= ScopeValMachT<ValSpec>;
	using ValCore				= ScopeValCoreT<ValSpec>;
	using ValLib				= ScopeValLibT<ValSpec>;
	using Mach					= ScopeValDevMachT<ValDevSpec>;
	using Core					= ScopeValDevCoreT<ValDevSpec>;
	using DevMach				= ScopeDevMachT<DevSpec>;
	using DevLib				= ScopeDevLibT<DevSpec>;
	using SimpleBufferedValue	= typename Mach::SimpleBufferedValue;
	using Packet				= typename ValData::Packet;
	using Value					= typename Mach::Value;
	using Ex					= typename Mach::Ex;
	using ValSink				= typename Core::ValSink;
	using Format				= typename ValData::Format;
	using PacketTracker			= typename ValCore::PacketTracker;
	using InternalPacketData	= typename DevMach::InternalPacketData;
	using StageComponent		= typename DevLib::StageComponent;

	ValSink* val_sink = CastPtr<ValSink>(&sink);
	if (!val_sink)
		return false;

	#define CTX (ValSpec*)0

	Value& val = val_sink->GetValue(CTX);
	SimpleBufferedValue* buf = CastPtr<SimpleBufferedValue>(&val);
	if (buf) {
		//AccelComponentGroup& ag = CastRef<AccelComponentGroup>(gr);

		StageComponent* comp = CastPtr<StageComponent>(val_sink->AsComponentBase());
		if (!comp)
			return false;

		TODO
	/*	Packet p = ValData::CreatePacket();

		p->SetOffset(gr.offset++);

		Format fmt = StageComponent::template GetDefaultFormat<ValSpec>();
		RTLOG("CreateForwardPacketT: sending packet in format: " << fmt.ToString());
		p->SetFormat(fmt);

		InternalPacketData& data = p->template SetData<InternalPacketData>();
		data.pos = 0;
		data.count = ag.GetComponents().GetCount();

		PacketTracker::Track(TrackerInfo("CreateForwardPacketT", __FILE__, __LINE__), *p);
		buf->AddPacket(p);

		NOT HERE
		for (FwdScope scope(comp); scope; scope++)
			scope.Forward();*/

		return true;
	}
	else {
		TODO
	}

	#undef CTX
	#endif
}


#if 0
bool AccelComponentGroupBase::CreateForwardPacket(InterfaceSinkBase& sink) {
	/*#define IFACE(x) if (CreateForwardPacketT<TS::VD<AccelSpec,x##Spec>>(*this, sink)) return true;
	IFACE_LIST
	#undef IFACE
	return false;*/
	TODO
}
#endif








ArrayMap<String,String>& Accel_CommonHashToName() {
	static ArrayMap<String,String> map;
	if (map.IsEmpty()) {
		map.Add("85a6d68622b36995ccb98a89bbb119edf167c914660e4450d313de049320005c", "grid");
		map.Add("cbcbb5a6cfb55c36f8f021fbb0e3f69ac96339a39fa85cd96f2017a2192821b5", "nyan");
		map.Add("0681c014f6c88c356cf9c0394ffe015acc94ec1474924855f45d22c3e70b5785", "bg1");
		map.Add("793a105653fbdadabdc1325ca08675e1ce48ae5f12e37973829c87bea4be3232", "bg2");
		map.Add("0a40562379b63dfb89227e6d172f39fdce9022cba76623f1054a2c83d6c0ba5d", "noise1");
		map.Add("550a8cce1bf403869fde66dddf6028dd171f1852f4a704a465e1b80d23955663", "bg3");
		map.Add("3083c722c0c738cad0f468383167a0d246f91af2bfa373e9c5c094fb8c8413e0", "noise2");
		map.Add("27012b4eadd0c3ce12498b867058e4f717ce79e10a99568cca461682d84a4b04", "noise3");
		map.Add("488bd40303a2e2b9a71987e48c66ef41f5e937174bf316d3ed0e86410784b919", "bg4");
		map.Add("95b90082f799f48677b4f206d856ad572f1d178c676269eac6347631d4447258", "metal");
		map.Add("0c7bf5fe9462d5bffbd11126e82908e39be3ce56220d900f633d58fb432e56f5", "noise4");
		map.Add("10eb4fe0ac8a7dc348a2cc282ca5df1759ab8bf680117e4047728100969e7b43", "stonewall");
		map.Add("e6e5631ce1237ae4c05b3563eda686400a401df4548d0f9fad40ecac1659c46c", "wall");
		map.Add("8de3a3924cb95bd0e95a443fff0326c869f9d4979cd1d5b6e94e2a01f5be53e9", "uk_street");
		map.Add("585f9546c092f53ded45332b343144396c0b2d70d9965f585ebc172080d8aa58", "yard");
		map.Add("94284d43be78f00eb6b298e6d78656a1b34e2b91b34940d02f1ca8b22310e8a0", "bg5");
		map.Add("ad56fba948dfba9ae698198c109e71f118a54d209c0ea50d77ea546abad89c57", "stone1");
		map.Add("52d2a8f514c4fd2d9866587f4d7b2a5bfa1a11a0e772077d7682deb8b3b517e5", "stone2");
		map.Add("aea6b99da1d53055107966b59ac5444fc8bc7b3ce2d0bbb6a4a3cbae1d97f3aa", "noise5");
		map.Add("bd6464771e47eed832c5eb2cd85cdc0bfc697786b903bfd30f890f9d4fc36657", "brown_grid");
		map.Add("1f7dca9c22f324751f2a5a59c9b181dfe3b5564a04b724c657732d0bf09c99db", "wood1");
		map.Add("92d7758c402f0927011ca8d0a7e40251439fba3a1dac26f5b8b62026323501aa", "stone3");
		map.Add("cd4c518bc6ef165c39d4405b347b51ba40f8d7a065ab0e8d2e4f422cbc1e8a43", "stone4");
		map.Add("8979352a182bde7c3c651ba2b2f4e0615de819585cc37b7175bcefbca15a6683", "stone5");
		map.Add("fb918796edc3d2221218db0811e240e72e340350008338b0c07a52bd353666a6", "wood2");
		map.Add("f735bee5b64ef98879dc618b016ecf7939a5756040c2cde21ccb15e69a6e1cfb", "noise6");
		map.Add("3871e838723dd6b166e490664eead8ec60aedd6b8d95bc8e2fe3f882f0fd90f0", "stone6");
		map.Add("79520a3d3a0f4d3caa440802ef4362e99d54e12b1392973e4ea321840970a88a", "stone7");
		map.Add("08b42b43ae9d3c0605da11d0eac86618ea888e62cdd9518ee8b9097488b31560", "alphabet");
		map.Add("3c33c415862bb7964d256f4749408247da6596f2167dca2c86cc38f83c244aa6", "toymusic");
		map.Add("29de534ed5e4a6a224d2dfffab240f2e19a9d95f5e39de8898e850efdb2a99de", "toymusic");
		map.Add("48e2d9ef22ca6673330b8c38a260c87694d2bbc94c19fec9dfa4a1222c364a99", "toymusic");
		map.Add("894a09f482fb9b2822c093630fc37f0ce6cfec02b652e4e341323e4b6e4a4543", "toymusic");
		map.Add("a6a1cf7a09adfed8c362492c88c30d74fb3d2f4f7ba180ba34b98556660fada1", "toymusic");
		map.Add("d96b229eeb7a08d53adfcf1ff89e54c9ffeebed193d317d1a01cc8125c0f5cca", "toymusic");
		map.Add("ec8a6ea755d34600547a5353f21f0a453f9f55ff95514383b2d80b8d71283eda", "toymusic");
		map.Add("3405e48f74815c7baa49133bdc835142948381fbe003ad2f12f5087715731153", "oldie");
		map.Add("c3a071ecf273428bc72fc72b2dd972671de8da420a2d4f917b75d20e1c24b34c", "img_forces");
		map.Add("35c87bcb8d7af24c54d41122dadb619dd920646a0bd0e477e7bdc6d12876df17", "van_damme");
		map.Add("e81e818ac76a8983d746784b423178ee9f6cdcdf7f8e8d719341a6fe2d2ab303", "britney");
	}
	return map;
}


const char* AccelComponentBase::names[VAR_COUNT+1] = {
	#define ACCEL_VAR(v, n) n,
	ACCEL_VAR_LIST
	#undef ACCEL_VAR
	0
};

void AccelComponentBase::ClearTex() {
#if HAVE_OPENGL
	Ogl_ClearTex();
#endif
}

void AccelComponentBase::ClearProg() {
#if HAVE_OPENGL
	Ogl_ClearProg();
#endif
}

int AccelComponentBase::NewWriteBuffer() {
	if (is_doublebuf)
		buf_i = (buf_i + 1) % 2;
	return buf_i;
}

void AccelComponentBase::UseRenderedFramebuffer() {TODO}
bool AccelComponentBase::IsSinkInAccelerator() const {TODO}

TypeCls AccelComponentBase::GetTypeFromString(String type_str) {
	TODO
	#if 0
	#define VALUE(str, i) if (type_str == #str) return AsTypeCls<i>();
	//using Display		= typename ScopeValDevLibT<VD<AccelSpec,DisplaySpec>>::PipeComponent;
	using Video			= typename ScopeValDevLibT<VD<AccelSpec,VideoSpec>>::PipeComponent;
	using Audio			= typename ScopeValDevLibT<VD<AccelSpec,AudioSpec>>::PipeComponent;
	//using ConvPhoto		= typename ScopeConvValDevLibT<PhotoSpec,CenterSpec,AccelSpec>::ConvertComponent;
	using ConvVideo		= typename ScopeConvValDevLibT<VideoSpec,CenterSpec,AccelSpec>::ConvertComponent;
	VALUE(image,		Video);
	VALUE(imagebuf,		Video);
	VALUE(imagebuffer,	Video);
	VALUE(sound,		Audio);
	VALUE(soundbuf,		Audio);
	VALUE(cubemap,		ConvVideo);
	//VALUE(vertex,		Accel_DATA_SINK);
	//VALUE(data,			Accel_DATA_SINK);
	//VALUE(ctrl,			Accel_CTRL_SINK);
	//VALUE(library,		);
	return AsVoidTypeCls();
	#undef VALUE
	#endif
}

void AccelComponentBase::UpdateCompFlags(TypeCls val_spec, int comp_i, int comp_count) {
	has_fbo = false;
	TODO // Was DisplaySpec, now VideoSpec: information is missing
	/*if (val_spec == AsTypeCls<VideoSpec>() && comp_i == comp_count-1)
		has_fbo = true;*/
}

void AccelComponentBase::Clear() {
	DLOG("AccelComponentBase::Clear");

	name.Clear();
	description.Clear();
	for(int i = 0; i < PROG_COUNT; i++)
		code[i].Clear();

	buf_i = 0;
	is_doublebuf = false;
	is_searched_vars = false;

	ClearTex();
	ClearProg();
}

void AccelComponentBase::Close() {
	// pass
}

bool AccelComponentBase::Open() {

#if HAVE_OPENGL
	if (!Ogl_CompilePrograms())
		return false;

	if (!Ogl_LinkStages())
		return false;
#endif

	return true;
}

bool AccelComponentBase::CheckDevice() {
#if HAVE_OPENGL
	if (!Ogl_CheckInputTextures())
		return false;
#endif
	return true;
}

/*void AccelComponentBase::Forward() {
	using DevSpec = AccelSpec;
	using DevMach = ScopeDevMachT<DevSpec>;
	using InternalPacketData = typename DevMach::InternalPacketData;

	AccelComponent& c = CastRef<AccelComponent>(this);

	c.Forward();
}*/

/*
void AccelComponentBase::Process() {
	AccelComponent& c = CastRef<AccelComponent>(this);
#if HAVE_OPENGL
	int pos = c.GetPos();
	ASSERT(pos >= 0);
	uint32 gl_stage = c.group->gl_stages[pos];
	ASSERT(gl_stage > 0);
	c.group->Ogl_ProcessStage(*this, gl_stage);
#endif
}*/











const char* AccelComponentConfBase::type_names[ACCEL_TYPE_COUNT+1] = {
	#define ACCEL_TYPE_ITEM(x,y) y,
	ACCEL_TYPE_LIST
	#undef ACCEL_TYPE_ITEM
	0
};

const char* AccelComponentConfBase::filter_names[ACCEL_FILTER_COUNT+1] = {
	#define ACCEL_FILTER_ITEM(x,y) y,
	ACCEL_FILTER_LIST
	#undef ACCEL_FILTER_ITEM
	0
};

const char* AccelComponentConfBase::wrap_names[ACCEL_WRAP_COUNT+1] = {
	#define ACCEL_WRAP_ITEM(x,y) y,
	ACCEL_WRAP_LIST
	#undef ACCEL_WRAP_ITEM
	0
};

String AccelComponentConfBase::GetStringFromType(Type i) {
	return type_names[(int)i];
}

String AccelComponentConfBase::GetStringFromFilter(Filter i) {
	ASSERT(i >= 0 && i < ACCEL_FILTER_COUNT);
	return filter_names[(int)i];
}

String AccelComponentConfBase::GetStringFromWrap(Wrap i) {
	return wrap_names[(int)i];
}

AccelComponentConfBase::Type AccelComponentConfBase::GetTypeFromString(String s) {
	#define ACCEL_TYPE_ITEM(x,y) if (s == y) return x;
	ACCEL_TYPE_LIST
	#undef ACCEL_TYPE_ITEM
	return TYPE_INVALID;
}

AccelComponentConfBase::Filter AccelComponentConfBase::GetFilterFromString(String s) {
	#define ACCEL_FILTER_ITEM(x,y) if (s == y) return x;
	ACCEL_FILTER_LIST
	#undef ACCEL_FILTER_ITEM
	return FILTER_INVALID;
}

AccelComponentConfBase::Wrap AccelComponentConfBase::GetWrapFromString(String s) {
	#define ACCEL_WRAP_ITEM(x,y) if (s == y) return x;
	ACCEL_WRAP_LIST
	#undef ACCEL_WRAP_ITEM
	return WRAP_INVALID;
}

void AccelComponentConfBase::Set(Type t, String path, Filter filter, Wrap wrap, bool vflip) {
	this->type = t;
	this->filepath = path;
	this->filter = filter;
	this->wrap = wrap;
	this->vflip = vflip;
}

bool AccelComponentConfBase::IsEqualHeader(const AccelComponentConfBase& i) const {
	return	filepath == i.filepath &&
			type == i.type &&
			wrap == i.wrap &&
			filter == i.filter &&
			vflip == i.vflip;
}

void AccelComponentConfBase::Set(const AccelComponentConfBase& i) {
	filepath = i.filepath;
	type = i.type;
	wrap = i.wrap;
	filter = i.filter;
	vflip = i.vflip;
}

void AccelComponentConfBase::CopyIdStream(const AccelComponentConfBase& in) {
	TODO
	//id = in.id;
	//astream = in.astream;
	//vstream = in.vstream;
}

bool AccelComponentConfBase::IsTypeComponentSource(Type i) {
	TODO
	#if 0
	#define PIPECOMP(ValSpec)		ScopeValDevLibT<VD<AccelSpec,ValSpec>>::PipeComponent
	#define CONVCOMP_TO(ValSpec)	ScopeConvValDevLibT<ValSpec,CenterSpec,AccelSpec>::ConvertComponent
	#define CONVCOMP_FROM(ValSpec)	ScopeConvValDevLibT<ValSpec,AccelSpec,CenterSpec>::ConvertComponent
	#define IFACE(x) \
		if (i == AsTypeCls<PIPECOMP(x##Spec)>()) return true; \
		if (i == AsTypeCls<CONVCOMP_TO(x##Spec)>()) return true;
	IFACE_LIST
	#undef IFACE
	#undef PIPECOMP
	#undef CONVCOMP_TO
	#undef CONVCOMP_FROM
	return false;
	#endif
}







bool StageComponent::Load(ObjectMap& st_map, int stage_i, String frag_code) {
	TODO
	#if 0
	const char* fn_name = "AccelComponent::Load";
	Clear();


	Index<String> dirs;
	dirs.Add( ShareDirFile("imgs") );
	dirs.Add( ShareDirFile("sounds") );
	dirs.Add( ShareDirFile("videos") );


	String name = st_map.TryGet("name", "").ToString();
	String description = st_map.TryGet("description", "").ToString();

	Object& inputs = st_map.GetAdd("inputs", ObjectArray());
	if (!inputs.IsArray()) {
		OnError(fn_name, "no inputs");
		return false;
	}
	ObjectArray& in_arr = inputs.GetArray();
	for(int i = 0; i < in_arr.GetCount(); i++) {
		Object& in_el = in_arr.Get(i);
		if (!in_el.IsMap())
			continue;
		ObjectMap& in_map = in_el.GetMap();
		StageComponentConf& in = this->in.Add();
		if (in_map.IsEmpty()) {
			in.SetType(StageComponentConf::TYPE_EMPTY);
			continue;
		}
		String path = in_map.TryGet("filename", "").ToString();

		in.SetId(	(int)in_map.TryGet("id", -1).ToInt()); // TODO fix all of these, not safe now
		in.Set(		StageComponentConf::GetTypeFromString(in_map.TryGet("type", "").ToString()),
					path,
					StageComponentConf::GetFilterFromString(in_map.TryGet("filter", "linear").ToString()),
					StageComponentConf::GetWrapFromString(in_map.TryGet("wrap", "clamp").ToString()),
					ScanBoolString(in_map.TryGet("vflip", "false").ToString()));

		/*if (in.GetType() != StageComponentConf::TYPE_BUFFER) {
			in.SetId(-1);
		}*/

		if (path.GetCount() && GetFileDirectory(path).IsEmpty()) {
			String filename = GetFileName(path);
			String title = GetFileTitle(filename);
			filename = Accel_CommonHashToName().Get(title, title) + GetFileExt(filename);

			bool found = false;
			for (String dir : dirs) {
				String filepath = AppendFileName(dir, filename);
				if (FileExists(filepath)) {
					in.SetPath(filepath);
					found = true;
					break;
				}
			}
			if (!found) {
				OnError(fn_name, "file does not exist: \"" + filename + "\"");
				return false;
			}
		}
	}

	Object& outputs = st_map.GetAdd("outputs", ObjectArray());
	if (!outputs.IsArray()) {
		OnError(fn_name, "no outputs");
		return false;
	}
	ObjectArray& out_arr = outputs.GetArray();
	for(int i = 0; i < out_arr.GetCount(); i++) {
		Object& out_el = out_arr.Get(i);
		if (!out_el.IsMap())
			continue;
		ObjectMap& out_map = out_el.GetMap();

		if (!i) {
			id = (int)out_map.TryGet("id", -1).ToInt();
		}
		else {
			OnError(fn_name, "only 1 output is supported currently");
			return false;
		}
	}

	#if HAVE_OPENGL

	// Load GLSL code
	String& glsl = frag_code;
	if (glsl.IsEmpty()) {
		OnError(fn_name, "shader is empty for stage " + IntStr(id));
		return false;
	}

	// Hotfixes for GLSL code
	#if HAVE_OPENGL
	Ogl_RemoveToken(glsl, "lowp");
	Ogl_RemoveToken(glsl, "mediump");
	Ogl_RemoveToken(glsl, "highp");
	if (glsl.GetCount() && glsl[glsl.GetCount()-1] == 0) // Remove trailing 0
		glsl = glsl.Left(glsl.GetCount()-1);
	#else
	TODO
	#endif

	code[PROG_FRAGMENT] = glsl;

	#else
	Panic("not implemented");
	#endif

	return true;
	#endif
}


#if 0

template <class ValSpec>
void ConvertAccelCenterT(CenterComponent& conv, typename ScopeValMachT<ValSpec>::Packet& p) {
	TODO
}

template <>
void ConvertAccelCenterT<AudioSpec>(CenterComponent& conv, AudioPacket& p) {
	using ValSpec					= AudioSpec;
	using FromDevSpec				= AccelSpec;
	using ValMach					= ScopeValMachT<ValSpec>;
	using Mach						= ScopeValMachT<ValSpec>;
	using Format					= typename ValMach::Format;
	using FromDevMach				= ScopeDevMachT<FromDevSpec>;
	using FromInternalPacketData	= typename FromDevMach::InternalPacketData;

	FromInternalPacketData& in = p->GetData<FromInternalPacketData>();
	AccelComponent* acc_comp = reinterpret_cast<AccelComponent*>(in.dev_comp);
	ASSERT(acc_comp);

	Format fmt = p->GetFormat();
	fmt.SetDevSpec<CenterSpec>();
	p->SetFormat(fmt);

	Vector<byte>& data = p->Data();

	/*Format::SampleType type = fmt.GetType();
	if (type != Format::SampleType::FLT_LE) {
		conv.OnError("ConvertAccelCenterT", "TODO type conversion: f32 -> ...");
		p.Clear();
		return;
	}*/

#if HAVE_OPENGL
	int sample_rate = fmt.GetSampleRate();
	int sz = sample_rate * fmt.channels * sizeof(float);
	data.SetCount(sz);
	ASSERT(acc_comp->color_buf[acc_comp->buf_i] > 0);
	RTLOG("ConvertAccelCenterT: read active opengl color buffer");
	glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glReadPixels(0, 0, sample_rate, 1, GetOglChCode(fmt.channels), GL_FLOAT, data.Begin());

	if (0) {
		float* f = (float*)(void*)data.Begin();
		for(int i = 0; i < sample_rate; i++) {
			String s;
			s << i << ":";
			for(int j = 0; j < fmt.channels; j++) {
				int begin = (1 + j) * 20;
				if (s.GetCount() < begin) s.Cat(' ', begin - s.GetCount());
				s << DblStr(*f);
			}
			LOG(s);
		}
		LOG("");
		TODO
	}
#endif

}

#endif


/*#define IFACE(x) \
template<> template<> \
void ScopeDevLibT<CenterSpec>::StageComponent::ConvertPacket<AccelSpec, x##Spec>(typename ScopeValMachT<x##Spec>::Packet& p) { \
	ConvertAccelCenterT<x##Spec>(*this, p);\
}
IFACE_LIST
#undef IFACE*/





/*void ConvertCenterAccelT(AccelComponent& conv, typename ScopeValMachT<ValSpec>::Packet& p) {
	TODO
}*/

/*#define IFACE(x) \
template<> template<> \
void ScopeDevLibT<AccelSpec>::StageComponent::ConvertPacket<CenterSpec, x##Spec>(typename ScopeValMachT<x##Spec>::Packet& p) { \
	ConvertCenterAccelT<x##Spec>(*this, p);\
}
IFACE_LIST
#undef IFACE*/



#if 0

bool ScopeDevLibT<AccelSpec>::StageContextConnector::Load(Object& json) {
	using DevSpec = AccelSpec;
	using DevComponentBase = AccelComponentBase;

	DLOG("DevStageContextConnector::Load begin");
	const char* fn_name = "Load";
	if (!json.IsMap()) {
		OnError(fn_name, "invalid json");
		return false;
	}

	Index<String> dirs;
	dirs.Add( ShareDirFile("imgs") );
	dirs.Add( ShareDirFile("sounds") );
	dirs.Add( ShareDirFile("videos") );

	ObjectMap& map = json.GetMap();

	String name = map.GetAdd("name", "unnamed").ToString();
	String description = map.GetAdd("description", "").ToString();
	DLOG("DevStageContextConnector::Load: name='" << name << "'");

	Object& stages = map.GetAdd("stages", ObjectArray());
	if (!stages.IsArray()) {
		OnError(fn_name, "no stages in");
		return false;
	}
	ObjectArray& st_arr = stages.GetArray();
	for(int i = 0; i < st_arr.GetCount(); i++) {
		Object& st_el = st_arr.Get(i);
		if (!st_el.IsMap()) {
			OnError(fn_name, "unexpected element in stages");
			return false;
		}

		ObjectMap& st_map = st_el.GetMap();

		String frag_code;
		Object& outputs = st_map.GetAdd("outputs", ObjectArray());
		if (outputs.IsArray()) {
			ObjectArray& out_arr = outputs.GetArray();
			for(int i = 0; i < out_arr.GetCount(); i++) {
				Object& out_el = out_arr.Get(i);
				if (!out_el.IsMap())
					continue;
				ObjectMap& out_map = out_el.GetMap();
				int j = out_map.Find("id");
				if (j >= 0) {
					int id = (int)out_map.GetObject(j).ToInt();
					frag_code = map.GetAdd(IntStr(id)).ToString();
				}
			}
		}

		String type_str = st_map.TryGet("type", "").ToString();

		if (type_str == "imagebuf" && st_arr.GetCount() == 1)
			type_str = "image";

		if (type_str == "library") {
			common_source.Add(frag_code);
		}
		else {
			TypeCls type = DevComponentBase::GetTypeFromString(type_str);
			if (type == AsVoidTypeCls()) {
				OnError(fn_name, "Invalid type string '" + type_str + "'");
				return false;
			}

			if (StageComponent::IsDevPipeComponent(type)) {
				StageComponentGroup* group = 0;

				// Find group
				if (0)
					;
				#define PIPECOMP(ValSpec) typename ScopeValDevLibT<VD<DevSpec,ValSpec>>::PipeComponent
				#define IFACE(x) \
					else if (type == AsTypeCls<PIPECOMP(x##Spec)>()) \
						group = &GetAddGroupContext<x##Spec>(); \
					else if (type == AsTypeCls<typename ScopeConvValDevLibT<x##Spec,DevSpec,CenterSpec>::ConvertComponent>()) \
						group = &GetAddGroupContext<x##Spec>(); \
					else if (type == AsTypeCls<typename ScopeConvValDevLibT<x##Spec,CenterSpec,DevSpec>::ConvertComponent>()) \
						group = &GetAddGroupContext<x##Spec>();
				IFACE_LIST
				#undef IFACE
				if (!group) {
					OnError(fn_name, "No group exists for type '" + type_str + "'");
					return false;
				}


				// Create new comp
				TODO
				#if 0
				RefT_Entity<StageComponent> comp;
				if (0)
					;
				#define IFACE(x) \
					else if (type == AsTypeCls<PIPECOMP(x##Spec)>()) \
						comp = AddEntityComponent<PIPECOMP(x##Spec)>(*group);
					//else if (type == AsTypeCls<Dev##x##ConvertComponent>()) comp = AddEntityComponent<Dev##x##ConvertComponent>(*group); \
					//else if (type == AsTypeCls<x##DevConvertComponent>()) comp = AddEntityComponent<x##DevConvertComponent>(*group);
				IFACE_LIST
				#undef IFACE
				#undef PIPECOMP

				if (!comp)
					return false;

				if (!comp->Load(st_map, i, frag_code)) {
					ComponentBaseRef cb = comp->template AsRef<ComponentBase>();
					EntityRef e = cb->ComponentBase::GetEntity();
					e->Destroy();
					OnError(fn_name, "Loading stage " + IntStr(i) + " failed");
					return false;
				}
				#endif

				//for(StageComponentConf& in : comp->in) {ASSERT(in.GetId() < 0 || in.GetType() == StageComponentConf::TYPE_BUFFER);}
			}
			else {
				// Find existing component
				bool found = false;
				for (auto& group : groups)
					if ((found = group.LoadExisting(type, st_map, i, frag_code)))
						break;
				if (!found) {
					OnError(fn_name, "did not find existing component for persistent type '" + type_str + "'");
					return false;
				}
			}
		}
	}

	// Find unique inputs
	StageComponentConfVector v;
	for (StageComponentGroup& g : groups)
		g.FindUniqueInputs(v);


	if (v.in.GetCount()) {
		// Create components for unique inputs
		if (!CreateComponents(v))
			return false;

		// Connect created components for inputs
		DumpEntityComponents();
		for (auto& group : groups)
			group.ConnectInputs(v);

		// Connect inputs
		if (!ConnectComponentInputs())
			return false;

	}

	// Connect outputs
	if (!ConnectComponentOutputs())
		return false;

	DLOG("DevStageContextConnector::Load end");
	return true;
}


#endif







NAMESPACE_ECS_END
