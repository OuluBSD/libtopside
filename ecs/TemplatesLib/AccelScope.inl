NAMESPACE_TOPSIDE_BEGIN



template <>
template <class ValSpec>
void
ScopeDevLibT<AccelSpec>::DevComponent
::UpdateDevBuffersValT() {
	auto& stream = GetStreamState();
	
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
				DevComponentConf::FILTER_LINEAR,
				DevComponentConf::WRAP_CLAMP);
#endif
		}
		else if (base2) {
			fb_size = base2->size;
#if HAVE_OPENGL
			Ogl_CreateTex(
				fb_size, 4,
				1, has_fbo,
				DevComponentConf::FILTER_LINEAR,
				DevComponentConf::WRAP_CLAMP);
#endif
		}
		else {TODO}
	}
	else {TODO}
}

template <class ValSpec>
void AccelComponentBase::ForwardPacket(typename ScopeValMachT<ValSpec>::Packet p) {
	using DevSpec = AccelSpec;
	using DevMach = ScopeDevMachT<DevSpec>;
	using Mach = ScopeValMachT<ValSpec>;
	using InternalPacketData = typename DevMach::InternalPacketData;
	using TrackerInfo = typename Mach::TrackerInfo;
	DLOG("AccelComponentBase::ForwardPacket: begin");
	
	InternalPacketData& data = p->template GetData<InternalPacketData>();
	AccelComponent& c = CastRef<AccelComponent>(this);
	
	p->CheckTracking(TrackerInfo(this, __FILE__, __LINE__));
	
#if HAVE_OPENGL
	int pos = c.GetPos();
	ASSERT(pos >= 0);
	uint32 gl_stage = c.group->gl_stages[pos];
	ASSERT(gl_stage > 0);
	c.group->Ogl_ProcessStage(*this, gl_stage);
#endif
	
	if (data.pos >= data.count-1)
		PostProcess();
	
	DLOG("AccelComponentBase::ForwardPacket: end");
}



NAMESPACE_TOPSIDE_END
