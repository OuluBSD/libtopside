NAMESPACE_TOPSIDE_BEGIN



template <>
template <class ValSpec>
void
ScopeDevLibT<AccelSpec>::DevComponent
::UpdateTexBuffersValT() {
	auto* stream = Stream();
	if (stream) {
		fb_size.Clear();
		auto& state = stream->template Get<ValSpec>();
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
					ComponentConf::FILTER_LINEAR,
					ComponentConf::WRAP_CLAMP);
	#endif
			}
			else if (base2) {
				fb_size = base2->size;
	#if HAVE_OPENGL
				Ogl_CreateTex(
					fb_size, 4,
					1, has_fbo,
					ComponentConf::FILTER_LINEAR,
					ComponentConf::WRAP_CLAMP);
	#endif
			}
			else {TODO}
		}
		else {TODO}
	}
	else {ASSERT_(false, "no stream");}
}


NAMESPACE_TOPSIDE_END
