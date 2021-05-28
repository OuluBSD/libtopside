#ifndef _AccelCore_ContextComponent_h_
#define _AccelCore_ContextComponent_h_

NAMESPACE_TOPSIDE_BEGIN





class AccelContextComponent :
	public Component<AccelContextComponent>
{
	RTTI_COMP0(AccelContextComponent)
	VIS_COMP_0_0
	void Visit(RuntimeVisitor& vis) override {}
	
private:
	static int id_counter;
	
public:
	LinkedList<AccelComponentGroup> groups;
	Vector<String> common_source;
	String last_error;
	Object post_load;
	
	// Generic
	AccelStream stream;
	bool is_open = false;
	
	
	bool					Render();
	void					Clear();
	void					AddDefaultGroups();
	bool					RefreshStageQueue();
	void					RefreshPipeline();
	//void					RemoveComponent(AccelComponentRef s) {comps.RemoveKey(s);}
	void					ProcessStageQueue(TypeCls ctx);
	//bool					IsModeStage(AccelComponentRef comp, TypeCls ctx) const;
	void					RefreshStreamValues(TypeCls ctx);
	void					FindComponents();
	bool					LoadFileAny(String path, Object& dst);
	bool					LoadFileToy(String path, Object& dst);
	void					Reset();
	void					OnError(TypeCls type, String fn, String msg);
	void					OnError(String fn, String msg);
	void					MakeUniqueIds(Object& v);
	int						MakeUniqueId(VectorMap<int,int>& ids, int orig_id);
	bool					Load(Object v);
	bool					CheckInputTextures();
	void					Close();
	bool					CreateComponents(AcceleratorHeaderVector& v);
	bool					ConnectComponents();
	
#if HAVE_OPENGL
	void					Ogl_ProcessStage(AccelComponentRef s, GLuint gl_stage);
	void					Ogl_ClearPipeline();
	void					Ogl_CreatePipeline();
#endif
	
	
	template <class T> RefT_Entity<T> AddEntityComponent(AccelComponentGroup& g) {
		RefT_Entity<T> o = GetEntity()->Add<T>();
		o->ctx = g.AsRefT();
		g.Add(o);
		return o;
	}
	
	template <class T> AccelComponentGroup* FindGroupContext() {
		TypeCls cls = AsTypeCls<T>();
		for (AccelComponentGroup& g : groups)
			if (g.HasContext(cls))
				return &g;
		return 0;
	}
	
	template <class Ctx, class T> bool AddEntityAccelComponent(AcceleratorHeader& in) {
		static const char* fn_name = "AccelContextComponent::AddEntityAccelComponent";
		AccelComponentGroup* g = FindGroupContext<Ctx>();
		if (!g) {
			OnError(fn_name, "No group found with given context");
			return false;
		}
		RefT_Entity<T> o = GetEntity()->Add<T>();
		if (!o) {
			OnError(fn_name, "Adding component failed");
			return false;
		}
		o->ctx = g->AsRefT();
		if (!o->LoadAsInput(in)) {
			//OnError(fn_name, "Loading AcceleratorHeader in component failed");
			o->Destroy();
			return false;
		}
		ASSERT(o->ctx);
		o->id = in.GetId();
		in.Set(o->GetVideoStream(), o->GetAudioStream());
		g->Add(o);
		return true;
	}
	
public:
	COPY_PANIC(AccelContextComponent);
	
	AccelContextComponent() {}
	
	void		Initialize() override;
	void		Uninitialize() override;
	
    void		Update(double dt);
	String		GetLastError() const {return last_error;}
	void		PostLoadFileAny(String path);
	void		DumpEntityComponents();
	
	
	
	Callback WhenError;
	
};




NAMESPACE_TOPSIDE_END

#endif
