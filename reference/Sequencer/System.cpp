#include "Sequencer.h"


NAMESPACE_TOPSIDE_BEGIN



void Bus::NoteOn(double frequency, double amplitude) {
	if (items.IsEmpty())
		return;
		
	BusItem& first = items[0];
	
	if (first.core == NULL)
		return;
		
	first.core->NoteOn(frequency, amplitude);
}

void Bus::NoteOff(double frequency) {
	if (items.IsEmpty())
		return;
		
	BusItem& first = items[0];
	
	if (first.core == NULL)
		return;
		
	first.core->NoteOff(frequency);
}











System::System() {
	snd <<= THISBACK(Generator);
	snd.OpenDefault();
	snd.SetFlags(SND_NOCLIP);
	snd.Start();
	
	BusItem& bi = output.items.Add(-1);
	bi.type = BUSITEM_AUDIOMIXER;
}

System::~System() {
	snd.Close();
}

void System::Generator(StreamCallbackArgs& arg) {
	ResizeOutputs(arg);
	
	genlock.Enter();
	
	for (int i = 0; i < sources.GetCount(); i++) {
		Bus& src = sources[i];
		Process(src);
	}
	
	Process(output);
	
	genlock.Leave();
	
	if (output.items.IsEmpty())
		return;
		
	const AudioFrames& from = output.items.Top().output;
	
	for (int i = 0; i < arg.fpb * CH_COUNT; i++) {
		((float*)arg.output)[i] = from.output[i];
	}
}

void System::ResizeOutputs(const StreamCallbackArgs& arg) {
	for (int i = 0; i < sources.GetCount(); i++) {
		Bus& src = sources[i];
		
		for (int j = 0; j < src.items.GetCount(); j++) {
			BusItem& bi = src.items[j];
			bi.output.SetCount(arg.fpb, CH_COUNT);
		}
	}
	
	for (int j = 0; j < output.items.GetCount(); j++) {
		BusItem& bi = output.items[j];
		bi.output.SetCount(arg.fpb, CH_COUNT);
		bi.output.Zero();
	}
}

void System::Process(Bus& bus) {
	for (int j = 0; j < bus.items.GetCount(); j++) {
		BusItem* prev = j == 0 ? NULL : &bus.items[j-1];
		BusItem& bi = bus.items[j];
		
		Process(bi, prev);
		
		for (int k = 0; k < bi.sends.GetCount(); k++) {
			Process(bi, bi.sends[k]);
		}
	}
	
	if (!bus.items.IsEmpty())
		Process(bus.items.Top(), bus.output);
}

void System::Process(BusItem& bi, BusItem* prev) {

	if (bi.type == BUSITEM_AUDIOSOURCE) {
	
	}
	else
	if (bi.type == BUSITEM_AUDIOMIXER) {
	
	}
	else
	if (bi.type == BUSITEM_INSTRUMENT) {
		bi.core->Tick(bi.output);
	}
	
	else
	if (bi.type == BUSITEM_EFFECT) {
		bi.core->Tick(prev->output, bi.output);
	}
}

void System::Process(BusItem& bi, const BusSend& bs) {
	Bus* b = FindSendOut(bs);
	
	if (!b)
		return;
		
	if (b->items.IsEmpty())
		return;
		
	BusItem& out = b->items[0];
	
	for (int i = 0; i < bi.output.GetCount(); i++) {
		out.output[i] += bi.output[i];
	}
}

Bus* System::FindSendOut(const BusSend& bs) {
	if (bs.bus == 0)
		return &output;
		
	int i;
	
	i = sources.Find(bs.bus);
	
	if (i != -1)
		return &sources[i];
		
	return NULL;
}

void System::SetInput(Bus& bus, const CoreParams& params) {
	BusItem& bi = bus.items.GetAdd(-1);
	SortByKey(bus.items, StdLess<int>());
	
	if (bi.core == NULL || bi.core->factory != params.factory) {
		if (bi.core)
			delete bi.core;
			
		bi.core = CoreFactories()[params.factory].b();
		
		ASSERT(bi.core);
		
		bi.core->factory = params.factory;
	}
	
	bi.type = BUSITEM_INSTRUMENT;
	bi.core->Configure(params);
}

void System::SetEffect(Bus& bus, int i, const CoreParams& params) {
	BusItem& bi = bus.items.GetAdd(i);
	SortByKey(bus.items, StdLess<int>());
	
	if (bi.core == NULL || bi.core->factory != params.factory) {
		if (bi.core)
			delete bi.core;
			
		bi.core = CoreFactories()[params.factory].b();
		
		ASSERT(bi.core);
		
		bi.core->factory = params.factory;
	}
	
	bi.type = BUSITEM_EFFECT;
	bi.core->Configure(params);
}


NAMESPACE_TOPSIDE_END
