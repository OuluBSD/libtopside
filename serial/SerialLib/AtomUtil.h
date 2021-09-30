#ifndef _SerialLib_AtomUtil_h_
#define _SerialLib_AtomUtil_h_

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
	bool	ForwardAsyncMem(byte* mem, int size) override;
	bool	LoadPacket(int ch_i, const Packet& p) override;
	void	AltStorePacket(int sink_ch,  int src_ch, Packet& p) override;
	virtual bool PassLoadPacket(int ch_i, const Packet& p) {return ch_i == GetSink()->GetSinkCount()-1;}
	
};


NAMESPACE_SERIAL_END

#endif
