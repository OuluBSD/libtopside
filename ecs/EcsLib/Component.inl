
NAMESPACE_TOPSIDE_BEGIN


template<typename DevSpec, typename ValSpec, typename T, class Sink, class Source, class Ext>
void DevComponent<DevSpec,ValSpec,T,Sink,Source,Ext>::ForwardPackets(double dt) {
	using ValDevSpec			= VD<DevSpec,ValSpec>;
	using ValMach				= ScopeValMachT<ValSpec>;
	using Mach					= ScopeValDevMachT<ValDevSpec>;
	using Core					= ScopeValDevCoreT<ValDevSpec>;
	using V						= ValSpec;
	using Packet				= typename ValMach::Packet;
	using Format				= typename Mach::Format;
	using ValueBase				= typename Mach::ValueBase;
	using StreamBase			= typename Mach::StreamBase;
	using Value					= typename Mach::Value;
	using CtxStream				= typename Mach::Stream;
	using ValExchangePoint		= typename Mach::ValExchangePoint;
	using ValExchangePointRef	= typename Mach::ValExchangePointRef;
	using SimpleBufferedValue	= typename Mach::SimpleBufferedValue;
	using SimpleBufferedStream	= typename Mach::SimpleBufferedStream;
	using ValSink				= typename Core::ValSink;
	using ValSinkRef			= typename Core::ValSinkRef;
	using ValSource				= typename Core::ValSource;
	using ValSourceRef			= typename Core::ValSourceRef;
	using DevCompConf			= typename ScopeDevMachT<DevSpec>::StageComponentConf;
	using StageComponent		= typename ScopeDevLibT<DevSpec>::StageComponent;
	
	ASSERT(is_open);
	
	ValSource& src = CastRef<ValSource>(this);
	if (src.GetConnections().IsEmpty())
		return;
	
	RTLOG("DevComponent<" << DevSpec::GetName() << "," << ValSpec::GetName() << "::ForwardPackets: begin");
	#define CTX	(ValSpec*)0
	
	{
		CtxStream& stream = src.GetStream(CTX);
		int buf_sz = stream.Get().GetQueueSize();
		bool buffer_full = buf_sz >= 2;
		
		#if 0 && DEBUG_RT_PIPE
		RTLOG("update source " << HexStr((size_t)&src) << "<" << src.GetConfigString() << ">");
		#endif
		
		TODO
		/*src.Update(dt, buffer_full);
		if (src.Cfg().render) {
			#if DEBUG_RT_PIPE
			RTLOG("begin source " << HexStr((size_t)&src) << "<" << src.GetConfigString() << ">");
			#endif
			
			src.BeginStream(CTX);
		}*/
	}
	
	int dbg_i = 0;
	for (auto& link : src.GetConnections()) {
		ValExchangePointRef expt = link.expt;
		ASSERT(expt);
		
		TODO
		/*off32 begin_offset = expt->GetOffset();
		#if 1 && DEBUG_RT_PIPE
		const RTTI& expt_rtti = expt->GetRTTI();
		RTLOG("expt " << dbg_i << " update " << HexStr((size_t)&expt_rtti.GetRTTI()) << "<" << expt_rtti.GetDynamicName() << "> offset " << IntStr(begin_offset.value));
		#endif
		
		ValSinkRef sink = expt->Sink();
		//ValSourceRef src = expt->Source();
		ASSERT(expt->Source() == &src);
		
		#if 0 && DEBUG_RT_PIPE
		RTLOG("expt updpate src " << HexStr((size_t)&src) << "<" << src.GetConfigString() << "> offset " << IntStr(begin_offset.value));
		#endif
		
		//expt->SetOffset(begin_offset);
		for (FwdScope scope(*expt); scope; scope++)
			scope.Forward();
		
		off32 end_offset = expt->GetOffset();
		src.SetOffset(begin_offset, end_offset);
		
		#if DEBUG_RT_PIPE
		off32 diff = off32::GetDifference(begin_offset, end_offset);
		if (diff) {
			RTLOG("sink " << HexStr((size_t)&*sink) << "<" << sink->GetConfigString() << "> consumed " << diff.ToString());
		}
		#endif
		++dbg_i;*/
	}
	
	{
		TODO
		/*const auto& cfg = src.Cfg();
		if (cfg.begin_offset != cfg.end_offset) {
			#if DEBUG_RT_PIPE
			RTLOG("end source " << HexStr((size_t)&src) << "<" << src.GetConfigString() << ">");
			#endif
			
			src.EndStream(CTX);
		}*/
	}
	
	#undef CTX
	RTLOG("DevComponent<" << DevSpec::GetName() << "," << ValSpec::GetName() << "::ForwardPackets: end");
}


NAMESPACE_TOPSIDE_END
