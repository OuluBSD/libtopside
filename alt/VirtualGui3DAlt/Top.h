//$ class TopWindow {

private:
	Oulu::CoreWindow* cw = NULL;
	int id;
	
public:
	void Init(Oulu::CoreWindow* cw, int id);
	
	Oulu::CoreWindow* GetWindow() const {return cw;}
	
	
//$ };
