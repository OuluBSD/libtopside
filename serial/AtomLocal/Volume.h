#ifndef _AtomLocal_Volume_h_
#define _AtomLocal_Volume_h_

NAMESPACE_SERIAL_BEGIN


class VolumeLoaderBase:
	public virtual AtomBase
{
	Vector<byte>	values;
	String			filepath;
	Size			sz;
	int				depth;
	int				stride;
	bool			vflip = false;
	
public:
	VolumeLoaderBase();
	
	bool LoadFile();
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool ProcessPackets(PacketIO& io) override;
	bool IsReady(PacketIO& io) override;
	
	void Visit(RuntimeVisitor& vis) override {}
	
	
};

NAMESPACE_SERIAL_END

#endif
