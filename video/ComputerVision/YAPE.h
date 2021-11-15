#ifndef _ComputerVision_YAPE_h_
#define _ComputerVision_YAPE_h_


NAMESPACE_TOPSIDE_BEGIN


struct lev_table_t : Moveable<lev_table_t> {
	int width, height, radius;
	Vector<int> dirs;
	int dirs_count = 0;
	Vector<int> scores;
	
	void Set(int w, int h, int r);
	
	
};


class yape {
	Vector<lev_table_t> level_tables;
	int tau = 7;
	
	
public:
	
	static int precompute_directions(int step, Vector<int>& dirs, int R);
	
	int third_check(Vector<int>& Sb, int off, int step);
	bool is_local_maxima(const Vector<int>& p, int off, int v, int step, int neighborhood);
	void perform_one_point(const Vector<byte>& I, int x, Vector<int>& Scores, byte Im, byte Ip, const Vector<int>& dirs, int opposite, int dirs_nb);
	void init(int width, int height, int radius, int pyramid_levels=1);
	int detect(const ByteMat& src, Vector<keypoint_t>& points, int border = 4);
	
};



NAMESPACE_TOPSIDE_END

#endif
