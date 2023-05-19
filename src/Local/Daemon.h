#ifndef _Local_Daemon_h_
#define _Local_Daemon_h_

NAMESPACE_TOPSIDE_BEGIN


class DaemonBase;


class DaemonService : RTTIBase {
	
protected:
	friend class DaemonBase;
	DaemonBase* base;
	
public:
	RTTI_DECL0(DaemonService)
	virtual ~DaemonService() {}
	
	virtual bool Init(String name) = 0;
	virtual void Update() = 0;
	virtual void Deinit() = 0;
	virtual void Stop() {}
	
	
	DaemonBase& GetBase() const {return *base;}
	DaemonService* FindService(String name) const;
	
};


class DaemonBase : RTTIBase {
	ArrayMap<String, DaemonService> services;
	Index<String> requested_services;
	RunningFlag flag;
	bool inited = false;
	int timeout = 0;
	
public:
	typedef DaemonBase CLASSNAME;
	RTTI_DECL0(DaemonBase)
	DaemonBase();
	virtual ~DaemonBase();
	
	DaemonBase& SetTimeout(int sec) {timeout = sec; return *this;}
	void Add(String svc_name);
	
	virtual bool Init();
	virtual void Run();
	virtual void Stop();
	virtual void Deinit();
	void Update();
	void DefaultProcedure();
	void SetNotRunning();
	
	void RunInThread() {Thread::Start(THISBACK(Run));}
	
	DaemonService* FindService(String name);
	template <class T> T* FindServiceT() {
		for (DaemonService& svc : services.GetValues()) {
			T* o = CastPtr<T>(&svc);
			if (o)
				return o;
		}
		return 0;
	}
	
	static DaemonBase*& Latest() {static DaemonBase* p; return p;}
	static DaemonBase& Single();
	
public:
	typedef DaemonService* (*NewFn)();
	static ArrayMap<String, NewFn>& NewFnArray() {static ArrayMap<String, NewFn> a; return a;}
	template <class T> static DaemonService* Create() {return new T();}
	template <class T> static void Register(String name) {NewFnArray().GetAdd(name) = &Create<T>;}
	
};



#ifdef flagGLIB2
struct Glib2Daemon : DaemonBase {
	GMainLoop *loop = NULL;
	GList *device_list = NULL;
	static int num_devices;
	
	
	
	RTTI_DECL1(Glib2Daemon, DaemonBase)
	Glib2Daemon() {}
	~Glib2Daemon() {}
	
	
	bool Init() override;
	void Run() override;
	void Stop() override;
	void Deinit() override;
	
};

#endif



NAMESPACE_TOPSIDE_END

#endif
