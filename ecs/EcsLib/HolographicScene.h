#ifndef _EcsLib_HolographicScene_h_
#define _EcsLib_HolographicScene_h_

NAMESPACE_OULU_BEGIN


class HolographicScene : public System<HolographicScene> {

public:
	typedef HolographicScene CLASSNAME;
	using System::System;
	
	HolographicScene(Machine& core, HolographicSpace holographicSpace);
	
	HolographicFrame GetCurrentFrame() const;
	HolographicSpace GetHolographicSpace() const;
	
	//SpatialCoordinateSystem& WorldCoordinateSystem() const;
	PerceptionTimestamp CurrentTimestamp() const;
	
	void UpdateCurrentPrediction();
	
	void AddPredictionUpdateListener(Shared<IPredictionUpdateListener> listener);
	void RemovePredictionUpdateListener(Shared<IPredictionUpdateListener> listener);
	
protected:
	bool Initialize() override;
	void Start() override;
	void Update(float) override;
	void Uninitialize() override;
	
	void OnCurrentStageChanged();
	
	void OnPredictionChanged(IPredictionUpdateListener::PredictionUpdateReason reason);
	
private:
	mutable RWMutex mtx;
	
	HolographicSpace holospace;
	HolographicFrame cur_frame;
	TimeStop timer;
	
	ListenerCollection<IPredictionUpdateListener> prediction_update_listeners;
};


NAMESPACE_OULU_END

#endif
