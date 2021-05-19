#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


#if 0
template <>
bool ContextT<MediaContext>::SimpleStream::FindClosestFormat(const MediaFormat& fmt, int& idx) {
	// Size cap_sz, double fps, double bw_min, double bw_max, int& ret_fmt, int& ret_res
	double tgt_bw = (double)cap_sz.cx * (double)cap_sz.cy * (double)fps;
	double bw_low = bw_min * tgt_bw;
	double bw_high = bw_max * tgt_bw;
	if (bw_low > bw_high)
		return false;
	
	struct Result : Moveable<Result> {
		double diff;
		int fmt, res;
		bool operator()(const Result& a, const Result& b) const {return a.diff < b.diff;}
	};
	Vector<Result> results;
	
	for(int i = 0; i < fmts.GetCount(); i++) {
		const VideoSourceFormat& fmt = fmts[i];
		for(int j = 0; j < fmt.GetResolutionCount(); j++) {
			const VideoSourceFormatResolution& fmt_res = fmt.GetResolution(j);
			VideoFormat vid_fmt = fmt_res.GetFormat();
			Size fmt_sz = vid_fmt.res;
			double fmt_fps = vid_fmt.fps;
			double fmt_bw = (double)fmt_sz.cx * (double)fmt_sz.cy * fmt_fps;
			if (fmt_bw >= bw_low && fmt_bw <= bw_high) {
				Result& r = results.Add();
				r.diff = fabs(tgt_bw - fmt_bw);
				r.fmt = i;
				r.res = j;
			}
		}
	}
	if (results.GetCount()) {
		Sort(results, Result());
		if (0) {
			for(int i = 0; i < results.GetCount(); i++) {
				const Result& r = results[i];
				LOG(i << ": " << r.diff << ": " << r.fmt << ", " << r.res);
			}
		}
		const Result& res = results[0];
		ret_fmt = res.fmt;
		ret_res = res.res;
		return true;
	}
	return false;
}
#endif

NAMESPACE_TOPSIDE_END
