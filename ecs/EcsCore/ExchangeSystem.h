#ifndef _EcsCore_ExchangeSystem_h_
#define _EcsCore_ExchangeSystem_h_


NAMESPACE_OULU_BEGIN





class AudioExchangePoint : public ExchangePoint {
	ConnectorBase* conn = 0;
	off32 offset;
	bool use_consumer = false;
	bool dbg_offset_is_set = false;
	
public:
	typedef AudioExchangePoint CLASSNAME;
	AudioExchangePoint();
	~AudioExchangePoint() {Deinit();}
	
	void Init(ConnectorBase* conn);
	void Deinit();
	void Update(double dt) override;
	void SetOffset(off32 o) {offset = o; dbg_offset_is_set = true;}
	void UseConsumer(bool b=true) {use_consumer = b;}
	void Destroy() {conn = 0;}
	
	off32 GetOffset() const {return offset;}
	
};




class VideoExchangePoint : public ExchangePoint {
	ConnectorBase* conn = 0;
	bool any_sink_consumed = false;
	
	
public:
	typedef VideoExchangePoint CLASSNAME;
	VideoExchangePoint();
	~VideoExchangePoint() {Deinit();}
	
	void Init(ConnectorBase* conn);
	void Deinit();
	void Update(double dt) override;
	
	bool AnySinkConsumed() const {return any_sink_consumed;}
	
};



NAMESPACE_OULU_END


#endif
