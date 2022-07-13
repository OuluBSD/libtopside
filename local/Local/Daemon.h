#ifndef _Local_Daemon_h_
#define _Local_Daemon_h_

NAMESPACE_TOPSIDE_BEGIN


class DaemonBase;


class DaemonService {
	
protected:
	friend class DaemonBase;
	DaemonBase* base;
	
public:
	virtual ~DaemonService() {}
	
	virtual bool Init(String name) = 0;
	virtual void Update() = 0;
	virtual void Deinit() = 0;
	virtual void Stop() {}
	
	
	DaemonBase& GetBase() const {return *base;}
	DaemonService* FindService(String name) const;
	
};


class DaemonBase {
	ArrayMap<String, DaemonService> services;
	Index<String> requested_services;
	bool running = false;
	
public:
	DaemonBase();
	virtual ~DaemonBase() {}
	
	void Add(String svc_name) {requested_services.FindAdd(svc_name);}
	
	virtual bool Init();
	virtual void Run();
	virtual void Stop();
	virtual void Deinit();
	void DefaultProcedure();
	
	DaemonService* FindService(String name);
	
	static DaemonBase*& Latest() {static DaemonBase* p; return p;}
	
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
