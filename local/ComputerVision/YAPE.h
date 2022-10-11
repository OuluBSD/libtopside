#ifndef _ComputerVision_YAPE_h_
#define _ComputerVision_YAPE_h_


NAMESPACE_TOPSIDE_BEGIN


struct YapeTableLevel : Moveable<YapeTableLevel> {
	int width, height, radius;
	Vector<int> dirs;
	int dirs_count = 0;
	Vector<int> scores;
	
	void Set(int w, int h, int r);
	
	
};


class Yape {
	Vector<YapeTableLevel> level_tables;
	int tau = 7;
	
	
public:
	
	static int PrecomputeDirections(int step, Vector<int>& dirs, int R);
	
	int ThirdCheck(Vector<int>& Sb, int off, int step);
	bool IsLocalMaxima(const Vector<int>& p, int off, int v, int step, int neighborhood);
	void PerformOnePoint(const Vector<byte>& I, int x, Vector<int>& Scores, byte Im, byte Ip, const Vector<int>& dirs, int opposite, int dirs_nb);
	void Init(int width, int height, int radius, int pyramid_levels=1);
	int Detect(const ByteMat& src, Vector<Keypoint>& points, int border = 4);
	
};



NAMESPACE_TOPSIDE_END

#endif
