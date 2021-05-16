//$ class TopWindow {

private:
	Topside::CoreWindow* cw = NULL;
	int id;
	
public:
	void Init(Topside::CoreWindow* cw, int id);
	
	Topside::CoreWindow* GetWindow() const {return cw;}
	
	
//$ };
