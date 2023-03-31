#include "IMidiHw.h"

#if defined flagPORTMIDI || defined flagBUILTIN_PORTMIDI

#include <MidiFile/MidiFile.h>


#if defined flagBUILTIN_PORTMIDI || (defined flagWIN32 && defined flagMSC) || flagFREEBSD
	#include <ports/portmidi/portmidi.h>
	#include <ports/portmidi/pmutil.h>
	#include <ports/portmidi/porttime.h>
#else
	#include <portmidi.h>
	#include <porttime.h>
#endif


#ifndef HAVE_PACKETTIMING
	#error HAVE_PACKETTIMING not defined
#endif

// see Sequencer/Midi.h


NAMESPACE_PARALLEL_BEGIN

struct MidPortmidi::NativeSource {
	PmStream* midi_in;
	TimeStop ts;
	int msg_count;
};

PmTimestamp midithru_time_proc(void *info) {
	ASSERT(info);
	MidPortmidi::NativeSource* dev = (MidPortmidi::NativeSource*)info;
	PmTimestamp ts = dev->ts.Elapsed();
    return ts;
}

bool MidPortmidi::Source_Create(NativeSource*& dev) {
	dev = new NativeSource;
	return true;
}

void MidPortmidi::Source_Destroy(NativeSource*& dev) {
	delete dev;
}

void MidPortmidi::Source_Visit(NativeSource& dev, AtomBase&, RuntimeVisitor& vis) {
	
}

bool MidPortmidi::Source_Initialize(NativeSource& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.msg_count = 0;
	
	// Search for usb device by default
	//bool search_usb = ws.GetBool(".search.usb", true);
	
    Pm_Initialize();

	#if 0
    int id = Pm_GetDefaultOutputDeviceID();
    const PmDeviceInfo *info = Pm_GetDeviceInfo(id);
    if (info == NULL) {
        LOG("MidPortmidi::Source_Initialize: error: Could not open default output device (" << id << ").");
        return false;
    }
    LOG("Opening output device " << info->interf << " " << info->name);
	#endif
	
    int id = Pm_GetDefaultInputDeviceID();
    if (id < 0) {
        LOG("MidPortmidi::Source_Initialize: error: no input devices found");
        return false;
    }
    
    #if 1
    int dev_count = Pm_CountDevices();
    int usb_i = -1;
    for(int i = 0; i < dev_count; i++) {
		const PmDeviceInfo* info = Pm_GetDeviceInfo(i);
		String name = info->name;
		if (name.Left(4) == "USB " /*&& usb_i < 0*/)
			usb_i = i;
		LOG("\t" << i << ": " << info->name << (i == id ? " (default)" : "") << (i == usb_i ? " (selected)" : ""));
    }
    if (usb_i >= 0)
        id = usb_i;
    #endif
    
    const PmDeviceInfo *info = Pm_GetDeviceInfo(id);
    if (info == NULL) {
        LOG("MidPortmidi::Source_Initialize: error: Could not open default input device (" << id << ").");
        return false;
    }
    LOG("Opening input device " << info->interf << " " << info->name);
    
    Pm_OpenInput(&dev.midi_in,
                 id,
                 NULL, // driver info
                 0, // use default input size,
                 &midithru_time_proc,
                 &dev // time info
                 );
    // Note: if you set a filter here, then this will filter what goes
    // to the MIDI THRU port. You may not want to do this.
    
    Pm_SetFilter(dev.midi_in, PM_FILT_ACTIVE | PM_FILT_CLOCK);
    
    return true;
}

bool MidPortmidi::Source_PostInitialize(NativeSource& dev, AtomBase& a) {
    return true;
}

bool MidPortmidi::Source_Start(NativeSource& dev, AtomBase& a) {
	dev.ts.Reset();
    return true;
}

void MidPortmidi::Source_Stop(NativeSource& dev, AtomBase& a) {
	
}

void MidPortmidi::Source_Uninitialize(NativeSource& dev, AtomBase& a) {
	Pm_Close(dev.midi_in);
	dev.midi_in = 0;
	
    Pm_Terminate();
}

bool MidPortmidi::Source_Send(NativeSource& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	Format fmt = out.GetFormat();
	
	if (fmt.IsMidi()) {
		Vector<byte>& data = out.Data();
		data.SetCount(0);
		int count = 0;
		
		static const int BUFSIZE = 1;
		PmError result;
		PmEvent buffer[BUFSIZE];
		
		
		while((result = Pm_Poll(dev.midi_in))) {
			
			if (!result)
				break;
			
			int status;
			int length = Pm_Read(dev.midi_in, buffer, BUFSIZE);
			int track_i = 0;
			
			if (length <= 0)
				continue;
			ASSERT(length < 10000);
			
			int offset = count;
			count += length;
			int sz = count * sizeof(MidiIO::Event);
			data.SetCount(sz);
			
			int count = 0;
			MidiIO::Event* dst = ((MidiIO::Event*)(byte*)data.Begin()) + offset;
			
			
			for(int i = 0; i < length; i++) {
				PmEvent& e = buffer[i];
				
				#if 1
				LOG("Got message " << dev.msg_count << ": time " <<
		            (int)(long) e.timestamp << ", " <<
		            (int)(long) Pm_MessageStatus(e.message) << " " <<
		            (int)(long) Pm_MessageData1(e.message) << " " <<
		            (int)(long) Pm_MessageData2(e.message));
				#endif
				
				int status = Pm_MessageStatus(e.message);
				int p1 = Pm_MessageData1(e.message);
				int p2 = Pm_MessageData2(e.message);
				
				MidiIO::Event& ev = *dst;
				ev.SetCount(3);
				uint8* data = ev.Begin();
				data[0] = status;
				data[1] = p1;
				data[2] = p2;
				
				#if CPU_BIG_ENDIAN
				#error TODO
				#endif
				
				ev.tick = e.timestamp;
				ev.track = track_i;
				ev.seconds = e.timestamp * 0.001;
				ev.seq = dev.msg_count;
				
				dev.msg_count++;
			}
			
		}
		
		#if HAVE_PACKETTIMING
		out.SetBeginTime();
		#endif
		
		#if HAVE_PACKETTIMINGCHECK
		out.SetTimingLimit(0.050);
		#endif
	}
	else if (fmt.IsReceipt()) {
		return true;
	}
	
	
	return true;
}

bool MidPortmidi::Source_IsReady(NativeSource& dev, AtomBase& a, PacketIO& io) {
	PmError result = Pm_Poll(dev.midi_in);
	if (!result)
		return false;
	return (io.active_sink_mask & 0x1) && io.full_src_mask == 0;
}





NAMESPACE_PARALLEL_END
#endif

