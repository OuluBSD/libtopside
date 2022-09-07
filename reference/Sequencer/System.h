#ifndef _Sequencer_System_h_
#define _Sequencer_System_h_


NAMESPACE_TOPSIDE_BEGIN


enum {CORE_INSTRUMENT, CORE_EFFECT};
enum {BUSITEM_NULL, BUSITEM_AUDIOSOURCE, BUSITEM_AUDIOMIXER, BUSITEM_INSTRUMENT, BUSITEM_EFFECT};


class BusSend : Moveable<BusSend> {
	
public:
	int bus = -1;
	
};

class BusItem {

public:
	~BusItem() {
		if (core) {
			delete core;
			core = NULL;
		}
	}
	Core* core = NULL;
	int type = BUSITEM_NULL;
	AudioFrames output;
	Vector<BusSend> sends;
	
};

class Bus {
	
public:
	ArrayMap<int, BusItem> items;
	BusSend output;
	
	void NoteOn( double frequency, double amplitude = 1.0);
	void NoteOff( double frequency);
};


class System {
	Sound snd;
	ArrayMap<int, Bus> sources;
	Bus output;
	SpinLock genlock;
	int bus_counter = 1;
	
	
public:
	typedef System CLASSNAME;
	System();
	~System();
	
	void Generator(StreamCallbackArgs& arg);
	int GetSourceCount() const {return sources.GetCount();}
	Bus& AddSource() {return sources.Add(bus_counter++);}
	Bus& GetSource(int i) {return sources[i];}
	void RemoveSource(int i) {sources.Remove(i);}
	void ResizeOutputs(const StreamCallbackArgs& arg);
	void Process(Bus& bus);
	void Process(BusItem& bi, BusItem* prev);
	void Process(BusItem& bi, const BusSend& bs);
	Bus* FindSendOut(const BusSend& bs);
	void SetInput(Bus& bus, const CoreParams& params);
	void SetEffect(Bus& bus, int i, const CoreParams& params);
	void Enter() {genlock.Enter();}
	void Leave() {genlock.Leave();}
	
public:
	typedef Core* (*CoreFactoryPtr)();
	typedef Tuple<String, CoreFactoryPtr, CoreFactoryPtr> CoreSystem;
	
	inline static Vector<int>&				Instruments() {static Vector<int> list; return list;}
	inline static Vector<int>&				Effects() {static Vector<int> list; return list;}
	template <class T> static Core*			CoreSystemFn() { return new T; }
	template <class T> static Core*			CoreSystemSingleFn() { return &Single<T>(); }
	inline static Vector<CoreSystem>&		CoreFactories() {static Vector<CoreSystem> list; return list;}
	
	template <class CoreT> static int		GetId() {
		static bool inited;
		static int id;
		if (!inited) {
			id = CoreFactories().GetCount();
			inited = true;
		}
		return id;
	}
	
	template <class CoreT> static void		Register(String name, int type=CORE_INSTRUMENT) {
		int id = GetId<CoreT>();
		if      (type == CORE_INSTRUMENT)		Instruments().Add(id);
		else if (type == CORE_EFFECT)			Effects().Add(id);
		AddCustomCore(name, &System::CoreSystemFn<CoreT>, &System::CoreSystemSingleFn<CoreT>);
	}
	
	static void AddCustomCore(const String& name, CoreFactoryPtr f, CoreFactoryPtr singlef) {
		CoreFactories().Add(CoreSystem(name, f, singlef));
	}
	
	template <class CoreT> static int		Find() {
		CoreFactoryPtr System_fn = &System::CoreSystemFn<CoreT>;
		const Vector<CoreSystem>& facs = CoreFactories();
		for(int i = 0; i < facs.GetCount(); i++) {
			if (facs[i].b == System_fn)
				return i;
		}
		return -1;
	}
	
	
};


NAMESPACE_TOPSIDE_END

#endif
