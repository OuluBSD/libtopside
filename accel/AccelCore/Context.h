#ifndef _AccelCore_Context_h_
#define _AccelCore_Context_h_

NAMESPACE_TOPSIDE_BEGIN



class AccellContextStream {
	
};


class AccelContextComponent :
	public Component<AccelContextComponent>
{
	RTTI_COMP0(AccelContextComponent)
	VIS_COMP_0_0
	void Visit(RuntimeVisitor& vis) override {}
	
private:
	static int id_counter;
	
public:
	
	//LinkedList<RefT_Entity<AccelComponent>> comps;
	Vector<String> common_source;
	Vector<uint32> gl_stages;
	String last_error;
	Object post_load;
	
	// Generic
	AccellContextStream stream;
	bool is_open = false;
	
	
	bool					Render();
	void					Clear();
	bool					RefreshStageQueue();
	void					RefreshPipeline();
	//void					RemoveComponent(RefT_Entity<AccelComponent> s) {comps.RemoveKey(s);}
	void					ProcessStageQueue(TypeCls ctx);
	bool					IsModeStage(ComponentBaseRef comp, TypeCls ctx) const;
	void					RefreshStreamValues(TypeCls ctx);
	//ComponentBaseRef		GetComponentById(int id) const;
	void					FindComponents();
	bool					LoadFileAny(String path, Object& dst);
	bool					LoadFileToy(String path, Object& dst);
	void					Reset();
	void					OnError(TypeCls type, String fn, String msg);
	void					OnError(String fn, String msg);
	void					MakeUniqueIds(Object& v);
	int						MakeUniqueId(VectorMap<int,int>& ids, int orig_id);
	bool					Load(Object v);
	void					UpdateTexBuffers();
	void					UpdateSoundBuffers();
	bool					CheckInputTextures();
	void					Close();
	bool					CreateComponents(AcceleratorHeaderVector& v);
	bool					ConnectComponents();
	
#if HAVE_OPENGL
	void					Ogl_ProcessStage(ComponentBaseRef s, GLuint gl_stage);
	void					Ogl_ClearPipeline();
	void					Ogl_CreatePipeline();
#endif
	
	
	
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

using AccelContextComponentRef		= Ref<AccelContextComponent,		RefParent1<Entity>>;



NAMESPACE_TOPSIDE_END

#endif
