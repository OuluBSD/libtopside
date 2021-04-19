#ifndef _AudioCtrl_MidiFileCtrl_h_
#define _AudioCtrl_MidiFileCtrl_h_

NAMESPACE_OULU_BEGIN


class MidiFileCtrl : public ComponentCtrl {
	MidiFileComponent* comp = 0;
	
public:
	typedef MidiFileCtrl CLASSNAME;
	MidiFileCtrl();
	
	void Reset();
	void Updated() override;
	void SetComponent(ComponentBase& base) override;
	
	
};


NAMESPACE_OULU_END

#endif
