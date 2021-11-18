//$ class TopWindow {

private:
	TS::Ecs::CoreWindow* cw = NULL;
	int id;
	
public:
	void Init(TS::Ecs::CoreWindow* cw, int id);
	
	TS::Ecs::CoreWindow* GetWindow() const {return cw;}
	
	
//$ };
