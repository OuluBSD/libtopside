#ifndef _Local_VR_h_
#define _Local_VR_h_

NAMESPACE_TOPSIDE_BEGIN

#if 0

struct PerceptionTimestamp {
	double ts = 0;
	
	PerceptionTimestamp() {}
	PerceptionTimestamp(double ts) : ts(ts) {}
	PerceptionTimestamp(const PerceptionTimestamp& t) : ts(t.ts) {}
	
	
};

struct HolographicFramePrediction {
	PerceptionTimestamp ts;
	
	
	PerceptionTimestamp Timestamp() const {
		return ts;
	}
};

struct HolographicFrame {
	HolographicFramePrediction pred;
	
	HolographicFramePrediction CurrentPrediction() const {
		return pred;
	}
	
	
};

class IPredictionUpdateListener {

public:
	enum PredictionUpdateReason {
		HolographicSpaceCreateNextFrame,
		HolographicFrameUpdatePrediction,
	};
	
	virtual void OnPredictionUpdated(
		PredictionUpdateReason reason,
		const HolographicFramePrediction& prediction) const = 0;
};

struct HolographicSpace {
	
	
	bool IsValid() const {return true;}
	
	operator bool() const {return IsValid();}
	
};

#endif

NAMESPACE_TOPSIDE_END

#endif
