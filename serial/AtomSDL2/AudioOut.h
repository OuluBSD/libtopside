#ifndef _AtomSDL2_AudioOut_h_
#define _AtomSDL2_AudioOut_h_

#if HAVE_MANUAL_SDL_CLASSES

NAMESPACE_SERIAL_BEGIN


class AsyncMemForwarderBase :
	virtual public AtomBase
{
	Packet		partial_packet;
	byte*		write_mem = 0;
	int			write_size = 0;
	int			write_pos = 0;
	int			partial_pos = 0;
	
	
	void	Consume(int data_begin, Packet p);
	
public:
	
	bool	IsReady(ValDevCls vd) override;
	void	ForwardAsyncMem(byte* mem, int size) override;
	void	LoadPacket(int ch_i, const Packet& p) override;
	void	AltStorePacket(int sink_ch,  int src_ch, Packet& p) override;
	
	
};

class SDL2AudioOutputBase :
	public SDL2BaseT<SDL2AudioOutputBase>,
	public AsyncMemForwarderBase
{
	One<OOSDL2::AudioOutput>	obj;
	//Serial::Proxy				empty_aud;
    RealtimeSourceConfig		aconfig;
	off32_gen					gen;
	
	
public:
	RTTI_DECL1(SDL2AudioOutputBase, AltBaseT)
	COPY_PANIC(SDL2AudioOutputBase)
	ATOM_DEF_VISIT
	
	SDL2AudioOutputBase() : aconfig(gen) {}
	
	bool	AltInitialize(const Script::WorldState& ws) override;
	void	AltUninitialize() override;
	void	AltForward(FwdScope& fwd) override;
	bool	IsConsumedPartialPacket() override {return obj->IsConsumedPartialPacket();}
	
	void	AltIntervalSinkProcess() {}
	
	OOSDL2::Component& GetObj() override {return *obj;}
	OOSDL2::AudioOutput* GetOOSDL2() {return &*obj;}
	
	void SetAudioSyncInterval(double seconds) {aconfig.sync_dt = seconds;}
	
};



NAMESPACE_SERIAL_END

#endif
#endif
