#ifndef _IGraphics_Base_h_
#define _IGraphics_Base_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class BufferBaseT :
	public Atom
{
	
protected:
	using Buffer = BufferT<Gfx>;
	Buffer buf;
	
	RealtimeSourceConfig* last_cfg = 0;
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(BufferBaseT, Atom);
	
	void Visit(RuntimeVisitor& vis) override {vis % buf; vis.VisitThis<Atom>(this);}
	void Update(double dt) override {buf.Update(dt);}
	RealtimeSourceConfig* GetConfig() override {return last_cfg;}
	
	Buffer& GetBuffer() {return buf;}
	
};


template <class Gfx>
class ShaderBaseT :
	public BufferBaseT<Gfx>
{
	bool is_audio = false;
	
public:
	using ShaderBase = ShaderBaseT<Gfx>;
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(ShaderBase, BufferBase);
	
	ShaderBaseT() {}
	
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool ProcessPacket(PacketValue& in, PacketValue& out) override;
	bool Recv(int sink_ch, const Packet& in) override;
	void Finalize(RealtimeSourceConfig& cfg) override;
	
	/*bool ProcessPacket(PacketValue& in, PacketValue& out) override
	bool ProcessPackets(PacketIO& io) override {
		auto& buf = this->buf;
		int src_ch = 0;
		PacketIO::Sink& prim_sink = io.sink[0];
		PacketIO::Source& src = io.src[src_ch];
		src.from_sink_ch = 0;
		src.p = this->ReplyPacket(src_ch, prim_sink.p);
		
		
		bool succ = true;
		
		
		for(int sink_ch = MAX_VDTUPLE_SIZE-1; sink_ch >= 0; sink_ch--) {
			PacketIO::Sink& sink = io.sink[sink_ch];
			Packet& in = sink.p;
			if (!in) {
				ASSERT(!sink.filled);
				continue;
			}
			sink.may_remove = true;
			
			RTLOG("OglShaderBase::ProcessPackets: " << sink_ch << ", " << src_ch << ": " << in->ToString());
			
			
			Format in_fmt = in->GetFormat();
			if (in_fmt.vd == VD(OGL,FBO)) {
				Size3 sz = in_fmt.fbo.GetSize();
				int channels = in_fmt.fbo.GetChannels();
				
				int base = this->GetSink()->GetSinkCount() > 1 ? 1 : 0;
				if (in->IsData<InternalPacketData>()) {
					succ = buf.LoadOutputLink(sz, sink_ch - base, in->GetData<InternalPacketData>()) && succ;
				}
				else {
					RTLOG("OglShaderBase::ProcessPackets: cannot handle packet: " << in->ToString());
				}
			}
			
			
			if (sink_ch == 0) {
				
				
				//BeginDraw();
				buf.Process(*this->last_cfg);
				//CommitDraw();
				
				ASSERT(in->GetFormat().IsValid());
				
				
			}
		}
		
		InterfaceSourceRef src_iface = this->GetSource();
		int src_count = src_iface->GetSourceCount();
		for (int src_ch = 0; src_ch < src_count; src_ch++) {
			PacketIO::Source& src = io.src[src_ch];
			if (!src.val)
				continue;
			Format src_fmt = src_iface->GetSourceValue(src_ch).GetFormat();
			if (src_fmt.vd == VD(OGL,FBO)) {
				Packet& out = src.p;
				if (!out) {
					src.from_sink_ch = 0;
					out = this->ReplyPacket(src_ch, prim_sink.p);
				}
				PacketValue& val = *out;
				InternalPacketData& data = val.GetData<InternalPacketData>();
				this->GetBuffer().StoreOutputLink(data);
				RTLOG("OglShaderBase::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
			}
		}
		
		return succ;
	}*/
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<BufferBase>(this);}
	
	
};


template <class Gfx>
class TextureBaseT :
	public BufferBaseT<Gfx>
{
	using Filter = GVar::Filter;
	using Wrap = GVar::Wrap;
	
	bool			loading_cubemap = false;
	Filter			filter = GVar::FILTER_LINEAR;
	Wrap			wrap = GVar::WRAP_REPEAT;
	Array<Packet>	cubemap;
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(TextureBaseT, BufferBase);
	
	TextureBaseT() {}
	
	bool Initialize(const Script::WorldState& ws) override {
		
		String f = ws.Get(".filter");
		if (!f.IsEmpty()) {
			if (f == "nearest")
				filter = GVar::FILTER_NEAREST;
			else if (f == "linear")
				filter = GVar::FILTER_LINEAR;
			else if (f == "mipmap")
				filter = GVar::FILTER_MIPMAP;
			else {
				LOG("OglTextureBase::Initialize: error: invalid filter string '" << f << "'");
				return false;
			}
		}
		
		String w = ws.Get(".wrap");
		if (!w.IsEmpty()) {
			if (w == "clamp")
				wrap = GVar::WRAP_CLAMP;
			else if (w == "repeat")
				wrap = GVar::WRAP_REPEAT;
			else {
				LOG("OglTextureBase::Initialize: error: invalid wrap string '" << w << "'");
				return false;
			}
		}
		
		return true;
	}
	
	bool PostInitialize() override {
		
		return true;
	}
	
	void Uninitialize() override {
		
	}
	
	bool IsReady(PacketIO& io) override {
		bool b = io.full_src_mask == 0 && io.active_sink_mask == 0b11;
		RTLOG("OglTextureBase::IsReady: " << (b ? "true" : "false"));
		return b;
	}
	
	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		TODO
	}
	
	/*bool ProcessPackets(PacketIO& io) override {
		auto& buf = this->buf;
		ASSERT(io.src_count == 2 && io.sink_count == 2);
		
		PacketIO::Sink& prim_sink = io.sink[0];
		PacketIO::Source& prim_src = io.src[0];
		PacketIO::Sink& sink = io.sink[1];
		
		ASSERT(prim_sink.p && sink.p);
		prim_sink.may_remove = true;
		sink.may_remove = true;
		prim_src.from_sink_ch = 0;
		prim_src.p = this->ReplyPacket(0, prim_sink.p);
		
		PacketValue& from = *sink.p;
		const Vector<byte> from_data = from.GetData();
		
		Format from_fmt = from.GetFormat();
		ASSERT(from_fmt.IsVideo() || from_fmt.IsVolume());
		Size3 sz;
		int channels;
		if (from_fmt.IsVideo()) {
			sz			= from_fmt.vid.GetSize();
			channels	= from_fmt.vid.GetChannels();
			
			if (from_fmt.vid.IsCubemap()) {
				if (from.seq == 0) {
					loading_cubemap = true;
					cubemap.Clear();
				}
				
				if (loading_cubemap) {
					if (from.seq == cubemap.GetCount())
						cubemap.Add(sink.p);
					
					if (cubemap.GetCount() < 6)
						return true;
				}
			}
		}
		else if (from_fmt.IsVolume()) {
			sz			= from_fmt.vol.GetSize();
			channels	= from_fmt.vol.GetChannels();
		}
		else
			TODO
		
		if (!buf.IsInitialized()) {
			ASSERT(sz.cx > 0 && sz.cy > 0);
			auto& fb = buf.fb;
			fb.is_win_fbo = false;
			fb.size = sz;
			fb.channels = channels;
			fb.sample = GVar::SAMPLE_FLOAT;
			fb.filter = this->filter;
			fb.wrap = this->wrap;
			fb.fps = 0;
			
			if (loading_cubemap) {
				ASSERT(cubemap.GetCount() == 6);
				if (!buf.InitializeCubemap(
						fb.size,
						fb.channels,
						GVar::SAMPLE_U8,
						cubemap[0]->GetData(),
						cubemap[1]->GetData(),
						cubemap[2]->GetData(),
						cubemap[3]->GetData(),
						cubemap[4]->GetData(),
						cubemap[5]->GetData()
					))
					return false;
			}
			else if (sz.cz == 0) {
				if (!buf.InitializeTexture(
					fb.size,
					fb.channels,
					GVar::SAMPLE_U8,
					&*from_data.Begin(),
					from_data.GetCount()))
					return false;
			}
			else {
				if (!buf.InitializeVolume(
					fb.size,
					fb.channels,
					GVar::SAMPLE_U8,
					from_data))
					return false;
			}
		}
		else {
			buf.ReadTexture(
				sz,
				channels,
				GVar::SAMPLE_U8,
				from.GetData());
		}
		
		
		InterfaceSourceRef src_iface = this->GetSource();
		int src_count = src_iface->GetSourceCount();
		for (int src_ch = 1; src_ch < src_count; src_ch++) {
			PacketIO::Source& src = io.src[src_ch];
			if (!src.val)
				continue;
			Format src_fmt = src_iface->GetSourceValue(src_ch).GetFormat();
			if (src_fmt.vd == VD(OGL,FBO)) {
				Packet& out = src.p;
				if (!out) {
					src.from_sink_ch = 1;
					out = this->ReplyPacket(src_ch, prim_sink.p);
				}
				PacketValue& val = *out;
				InternalPacketData& data = val.GetData<InternalPacketData>();
				this->GetBuffer().StoreOutputLink(data);
				RTLOG("OglTextureBase::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
			}
		}
		
		return true;
	}*/
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<BufferBase>(this);}
	
	bool NegotiateSinkFormat(int sink_ch, const Format& new_fmt) override {
		// accept all valid video formats for now
		if (new_fmt.IsValid() && new_fmt.IsVideo()) {
			ISinkRef sink = this->GetSink();
			Value& val = sink->GetValue(sink_ch);
			val.SetFormat(new_fmt);
			return true;
		}
		return false;
	}
	
	
};


template <class Gfx>
class FboReaderBaseT :
	public BufferBaseT<Gfx>
{
public:
	using BufferBase = BufferBaseT<Gfx>;
	using Buffer = BufferT<Gfx>;
	RTTI_DECL1(FboReaderBaseT, BufferBase);
	
	FboReaderBaseT() {}
	
	bool Initialize(const Script::WorldState& ws) override {
		ISourceRef src = this->GetSource();
		Format out_fmt = src->GetSourceValue(src->GetSourceCount()-1).GetFormat();
		if (out_fmt.IsAudio())
			this->SetPrimarySinkQueueSize(DEFAULT_AUDIO_QUEUE_SIZE);
		return true;
	}
	
	bool PostInitialize() override {
		return true;
	}
	
	void Uninitialize() override {
		
	}
	
	bool IsReady(PacketIO& io) override {
		dword iface_sink_mask = this->iface.GetSinkMask();
		bool b = io.active_sink_mask == iface_sink_mask && io.full_src_mask == 0;
		RTLOG("OglFboReaderBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
		return b;
	}
	
	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		TODO
	}
	
	/*bool ProcessPackets(PacketIO& io) override {
		ASSERT(io.nonempty_sinks == 2);
		
		{
			PacketIO::Sink& sink = io.sink[0];
			PacketIO::Source& src = io.src[0];
			sink.may_remove = true;
			src.from_sink_ch = 0;
			src.p = this->ReplyPacket(0, sink.p);
			src.p->AddRouteData(src.from_sink_ch);
		}
		
		{
			PacketIO::Sink& sink = io.sink[1];
			PacketIO::Source& src = io.src[1];
			ASSERT(sink.p && src.val && !src.is_full);
			Packet& in = sink.p;
			sink.may_remove = true;
			src.from_sink_ch = 1;
			src.p = this->ReplyPacket(1, sink.p);
			src.p->AddRouteData(src.from_sink_ch);
			
			Format fmt = src.p->GetFormat();
			
			if (fmt.IsAudio()) {
				int src_queue = src.val->GetMinPackets();
				int sink_queue = sink.val->GetMinPackets();
				ASSERT(src_queue > 1);
				ASSERT(sink_queue > 1);
				
				//DUMP(fmt);
				AudioFormat& afmt = fmt;
				InternalPacketData& v = in->GetData<InternalPacketData>();
				Buffer* src_buf = (Buffer*)v.ptr;
				ASSERT(src_buf);
				
				auto& fb = src_buf->fb;
				int afmt_size = afmt.GetSize();
				ASSERT(fb.size.cx == afmt.sample_rate && fb.size.cy == 1 && fb.channels == afmt_size);
				int len = afmt.sample_rate * fb.channels * sizeof(float);
				ASSERT(len > 0);
				Vector<byte>& out_data = src.p->Data();
				out_data.SetCount(len);
				
				GLuint frame_buf = fb.GetReadFramebuffer();
				ASSERT(frame_buf > 0);
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frame_buf);
				glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
				glReadPixels(0, 0, afmt.sample_rate, 1, GetOglChCode(fb.channels), GL_FLOAT, out_data.Begin());
				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
				
			}
			else TODO
		}
		
		return true;
	}*/
	
	bool NegotiateSinkFormat(int sink_ch, const Format& new_fmt) override {
		
		TODO
		
	}
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<BufferBase>(this);}
	
};




template <class Gfx>
class KeyboardBaseT :
	public BufferBaseT<Gfx>
{
	String			target;
	EnvStateRef		state;
	
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(KeyboardBaseT, BufferBase);
	KeyboardBaseT() {}
	
	bool Initialize(const Script::WorldState& ws) override {
		
		target = ws.Get(".target");
		if (target.IsEmpty()) {
			LOG("EventStateBase::Initialize: error: target state argument is required");
			return false;
		}
		
		Space& space = this->GetParent();
		state = space.FindNearestState(target);
		if (!state) {
			LOG("EventStateBase::Initialize: error: state '" << target << "' not found in parent space: " << space.GetDeepName());
			return false;
		}
		
		FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
		data.SetAll(false);
		
		return true;
	}
	
	bool PostInitialize() override {
		
		return true;
	}
	
	void Uninitialize() override {
		
	}
	
	bool IsReady(PacketIO& io) override {
		if (!state) return false;
		ASSERT(io.src_count == 2);
		if (io.src_count != 2) return false;
		
		dword iface_sink_mask = this->iface.GetSinkMask();
		bool b = io.active_sink_mask == iface_sink_mask && io.full_src_mask == 0;
		RTLOG("OglKeyboardBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
		return b;
	}
	
	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		TODO
	}
	
	/*bool ProcessPackets(PacketIO& io) override {
		RTLOG("OglKeyboardBase::ProcessPackets");
		auto& buf = this->buf;
		
		PacketIO::Sink& prim_sink = io.sink[0];
		PacketIO::Source& src = io.src[0];
		
		ASSERT(prim_sink.p);
		prim_sink.may_remove = true;
		src.from_sink_ch = 0;
		src.p = this->ReplyPacket(0, prim_sink.p);
		
		Packet& from = src.p;
		Size sz(FboKbd::key_tex_w, FboKbd::key_tex_h);
		int channels = 1;
		FboKbd::KeyVec& data = state->Set<FboKbd::KeyVec>(KEYBOARD_PRESSED);
		
		if (!buf.IsInitialized()) {
			ASSERT(sz.cx > 0 && sz.cy > 0);
			auto& fb = buf.fb;
			fb.is_win_fbo = false;
			fb.size = sz;
			fb.channels = channels;
			fb.sample = GVar::SAMPLE_FLOAT;
			fb.fps = 0;
			
			if (!buf.InitializeTexture(
				Size(sz.cx, sz.cy),
				channels,
				GVar::SAMPLE_U8,
				data.Get(),
				data.GetCount() * sizeof(byte)))
				return false;
		}
		else {
			buf.ReadTexture(
				sz,
				channels,
				GVar::SAMPLE_U8,
				data.Get(),
				data.GetCount() * sizeof(byte));
		}
		
		
		InterfaceSourceRef src_iface = this->GetSource();
		int src_count = src_iface->GetSourceCount();
		for (int src_ch = 1; src_ch < src_count; src_ch++) {
			PacketIO::Source& src = io.src[src_ch];
			if (!src.val)
				continue;
			Format src_fmt = src_iface->GetSourceValue(src_ch).GetFormat();
			if (src_fmt.vd == VD(OGL,FBO)) {
				Packet& out = src.p;
				if (!out) {
					src.from_sink_ch = 1;
					out = this->ReplyPacket(src_ch, prim_sink.p);
				}
				PacketValue& val = *out;
				InternalPacketData& data = val.GetData<InternalPacketData>();
				this->GetBuffer().StoreOutputLink(data);
				RTLOG("OglKeyboardBase::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
			}
		}
		
		return true;
	}*/
	
	void Visit(RuntimeVisitor& vis) override {}
	
};


template <class Gfx>
class AudioBaseT :
	public BufferBaseT<Gfx>
{
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(AudioBaseT, BufferBase);
	AudioBaseT() {}
	
	bool Initialize(const Script::WorldState& ws) override {
		return true;
	}
	
	bool PostInitialize() override {
		return true;
	}
	
	void Uninitialize() override {
		
	}
	
	bool IsReady(PacketIO& io) override {
		dword iface_sink_mask = this->iface.GetSinkMask();
		bool b = io.active_sink_mask == iface_sink_mask && io.full_src_mask == 0;
		RTLOG("OglAudioBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink_count << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
		return b;
	}
	
	bool ProcessPacket(PacketValue& in, PacketValue& out) override {
		TODO
	}
	
	/*bool ProcessPackets(PacketIO& io) override {
		RTLOG("OglAudioBase::ProcessPackets");
		ASSERT(io.src_count == 2 && io.sink_count == 2);
		auto& buf = this->buf;
		
		PacketIO::Sink&		prim_sink	= io.sink[0];
		PacketIO::Source&	prim_src	= io.src[0];
		PacketIO::Sink&		sink		= io.sink[1];
		PacketIO::Source&	src			= io.src[1];
		
		ASSERT(prim_sink.p);
		prim_sink.may_remove = true;
		prim_src.from_sink_ch = 0;
		prim_src.p = this->ReplyPacket(0, prim_sink.p);
		
		ASSERT(sink.p);
		sink.may_remove = true;
		src.from_sink_ch = 0;
		src.p = this->ReplyPacket(1, sink.p);
		
		Packet& from = sink.p;
		Format from_fmt = from->GetFormat();
		ASSERT(from_fmt.IsAudio());
		AudioFormat& afmt = from_fmt;
		Size sz(afmt.sample_rate, 1);
		int channels = afmt.GetSize();
		const Vector<byte>& data = from->GetData();
		
		if (!buf.IsInitialized()) {
			ASSERT(sz.cx > 0 && sz.cy > 0);
			auto& fb = buf.fb;
			fb.is_win_fbo = false;
			fb.size = sz;
			fb.channels = channels;
			ASSERT(afmt.IsSampleFloat());
			fb.sample = GVar::SAMPLE_FLOAT;
			fb.fps = 0;
			
			if (!buf.InitializeTexture(
				Size(sz.cx, sz.cy),
				channels,
				GVar::SAMPLE_U8,
				&*data.Begin(),
				data.GetCount() * sizeof(byte)))
				return false;
		}
		else {
			buf.ReadTexture(
				sz,
				channels,
				GVar::SAMPLE_U8,
				&*data.Begin(),
				data.GetCount() * sizeof(byte));
		}
		
		
		InterfaceSourceRef src_iface = this->GetSource();
		int src_count = src_iface->GetSourceCount();
		for (int src_ch = 1; src_ch < src_count; src_ch++) {
			PacketIO::Source& src = io.src[src_ch];
			if (!src.val)
				continue;
			Format src_fmt = src_iface->GetSourceValue(src_ch).GetFormat();
			if (src_fmt.vd == VD(OGL,FBO)) {
				Packet& out = src.p;
				if (!out) {
					src.from_sink_ch = 1;
					out = this->ReplyPacket(src_ch, prim_sink.p);
				}
				PacketValue& val = *out;
				InternalPacketData& data = val.GetData<InternalPacketData>();
				this->GetBuffer().StoreOutputLink(data);
				RTLOG("OglKeyboardBase::ProcessPackets: 0, " << src_ch << ": " << out->ToString());
			}
		}
		
		return true;
	}*/
	
	bool NegotiateSinkFormat(int sink_ch, const Format& new_fmt) override {
		// accept all valid video formats for now
		if (new_fmt.IsValid() && new_fmt.IsAudio()) {
			ISinkRef sink = this->GetSink();
			Value& val = sink->GetValue(sink_ch);
			val.SetFormat(new_fmt);
			return true;
		}
		return false;
	}
	
	void Visit(RuntimeVisitor& vis) override {}
	
};

#define GFXTYPE(x) \
	using x##ShaderBase = ShaderBaseT<x##Gfx>; \
	using x##TextureBase = TextureBaseT<x##Gfx>; \
	using x##FboReaderBase = FboReaderBaseT<x##Gfx>; \
	using x##KeyboardBase = KeyboardBaseT<x##Gfx>; \
	using x##AudioBase = AudioBaseT<x##Gfx>;
GFXTYPE_LIST
#undef GFXTYPE


NAMESPACE_PARALLEL_END

#endif
