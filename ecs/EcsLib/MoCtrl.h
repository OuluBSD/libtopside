#ifndef _EcsCore_MoCtrl_h_
#define _EcsCore_MoCtrl_h_


NAMESPACE_OULU_BEGIN


struct MotionControllerComponent : Component<MotionControllerComponent> {
	bool IsSource(const ControllerSourceDevice& rhs) const;
	
	bool attachControllerModel = false;
	ControllerSourceHandedness requestedHandedness;
	ControllerSourceDevice source;
	ControllerSourceLocation location;
};


class MotionControllerSystem :
			public System<MotionControllerSystem>,
			public IPredictionUpdateListener,
			public ControllerListenerInterface {
public:
	using System::System;
	
protected:
	void Start() override;
	void Stop() override;
	
	void OnPredictionUpdated(
		PredictionUpdateReason reason,
		const HolographicFramePrediction& prediction) const override;
	    
	void OnSourceDetected(const ControllerEventArgs& args) override;
	void OnSourceUpdated(const ControllerEventArgs& args) override;
	void OnSourceLost(const ControllerEventArgs& args) override;
	
private:
	void RefreshComponentsForSource(const ControllerSourceDevice& source) const;
};


NAMESPACE_OULU_END


#endif
