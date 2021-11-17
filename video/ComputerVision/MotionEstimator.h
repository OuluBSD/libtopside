#ifndef _ComputerVision_MotionEstimator_h_
#define _ComputerVision_MotionEstimator_h_


NAMESPACE_TOPSIDE_BEGIN


inline double Square(double x) {return x*x;}


// does isotropic normalization
template <class T>
void IsoNormalizePoints(const Vector<Keypoint>& from, Vector<Keypoint>& to, Vector<T>& T0, Vector<T>& T1, int count) {
	double cx0 = 0.0, cy0 = 0.0, d0 = 0.0, s0 = 0.0;
	double cx1 = 0.0, cy1 = 0.0, d1 = 0.0, s1 = 0.0;
	double  dx = 0.0,  dy = 0.0;
	
	for (int i = 0; i < count; ++i) {
		cx0 += from[i].x;
		cy0 += from[i].y;
		cx1 += to[i].x;
		cy1 += to[i].y;
	}
	
	cx0 /= count;
	cy0 /= count;
	cx1 /= count;
	cy1 /= count;
	
	for (int i = 0; i < count; ++i) {
		dx = from[i].x - cx0;
		dy = from[i].y - cy0;
		d0 += FastSqrt(dx * dx + dy * dy);
		dx = to[i].x - cx1;
		dy = to[i].y - cy1;
		d1 += FastSqrt(dx * dx + dy * dy);
	}
	
	d0 /= count;
	d1 /= count;
	
	s0 = M_SQRT2 / d0;
	s1 = M_SQRT2 / d1;
	
	T0[0] = T0[4] = (T)s0;
	T0[2] = (T)(-cx0 * s0);
	T0[5] = (T)(-cy0 * s0);
	T0[1] = T0[3] = T0[6] = T0[7] = (T)0.0;
	T0[8] = (T)1.0;
	
	T1[0] = T1[4] = (T)s1;
	T1[2] = (T)(-cx1 * s1);
	T1[5] = (T)(-cy1 * s1);
	T1[1] = T1[3] = T1[6] = T1[7] = (T)0.0;
	T1[8] = (T)1.0;
}


bool HaveCollinearPoints(Vector<Keypoint>& points, int count);


class TransformationKernel {
	
	
public:
	virtual bool Run(const Vector<Keypoint>& from, Vector<Keypoint>& to, FloatMat& model) = 0;
	virtual void Error(const Vector<Keypoint>& from, const Vector<Keypoint>& to, const FloatMat& model, Vector<double>& err) = 0;
	
};

class Affine2D : public TransformationKernel {
	DMatrix<float> T0;
	DMatrix<float> T1;
	DMatrix<float> AtA;
	DMatrix<float> AtB;
	DMatrix<float> a_mt;
	DMatrix<float> b_mt;

public:
	Affine2D();
	bool Run(const Vector<Keypoint>& from, Vector<Keypoint>& to, FloatMat& model) override;
	void Error(const Vector<Keypoint>& from, const Vector<Keypoint>& to, const FloatMat& model, Vector<double>& err);
	bool CheckSubset(const Vector<Keypoint>& from, const Vector<Keypoint>& to, int count);
	
};


class Homography2D : public TransformationKernel {
	DMatrix<float> mLtL;
	DMatrix<float> Evec;
	DMatrix<float> T0;
	DMatrix<float> T1;


public:
	
	Homography2D();
	bool Run(const Vector<Keypoint>& from, Vector<Keypoint>& to, FloatMat& model) override;
	void Error(const Vector<Keypoint>& from, const Vector<Keypoint>& to, const FloatMat& model, Vector<double>& err);
	bool CheckSubset(const Vector<Keypoint>& from, Vector<Keypoint>& to, int count);
	
};


class RansacParams {
	
public:
	int size;
	double thresh, eps, prob;
	
public:
	void Init(int size = 0, double thresh = 0.5, double eps = 0.5, double prob = 0.99) {
		this->size = size;
		this->thresh = thresh;
		this->eps = eps;
		this->prob = prob;
	}
	
	int UpdateIters(double _eps, int max_iters) {
		double num = FastLn(1 - this->prob);
		double denom = FastLn(1 - pow_fast(1 - _eps, this->size));
		return (denom >= 0 || -num >= max_iters*(-denom)) ? max_iters : (int)round(num / denom);
	}
};


template <class Kernel>
class MotionEstimator {
	Vector<int> indices;

public:
	
	bool GetSubset(Kernel& kernel, const Vector<Keypoint>& from, const Vector<Keypoint>& to, int need_cnt, int max_cnt, Vector<Keypoint>& from_sub, Vector<Keypoint>& to_sub) {
		int max_try = 1000;
		indices.Reserve(need_cnt);
		indices.SetCount(0);
		int ssiter = 0;
		bool ok = false;
		int i = 0;
		from_sub.SetCount(0);
		from_sub.Reserve(128);
		to_sub.SetCount(0);
		to_sub.Reserve(128);
		for (; ssiter < max_try; ++ssiter)  {
			for (i = 0; i < need_cnt && ssiter < max_try;) {
				auto& idx = indices.Add();
				idx = 0;
				ok = false;
				int idx_i = 0;
				while (!ok) {
					ok = true;
					idx_i = idx = Random(max_cnt);
					for (int j = 0; j < i; ++j) {
						if (idx_i == indices[j]) {
							ok = false;
							break;
						}
					}
				}
				auto& f = from_sub.Add();
				auto& t = to_sub.Add();
				f = from[idx_i];
				t = to[idx_i];
				if (!kernel.CheckSubset(from_sub, to_sub, i + 1)) {
					ssiter++;
					continue;
				}
				++i;
			}
			break;
		}
		
		return (i == need_cnt && ssiter < max_try);
	}
	
	
	int FindInliers(Kernel& kernel, const FloatMat& model, const Vector<Keypoint>& from, Vector<Keypoint>& to, double thresh, Vector<double>& err, ByteMat& mask) {
		int numinliers = 0;
		double t = thresh * thresh;
		int count = from.GetCount();
		ASSERT(count);
		
		kernel.Error(from, to, model, err);
		
		for (int i = 0; i < count; ++i) {
			bool f = err[i] <= t;
			mask.data[i] = f;
			numinliers += f * 1;
		}
		return numinliers;
	}
	
	bool Ransac(RansacParams& params, Kernel& kernel, const Vector<Keypoint>& from, Vector<Keypoint>& to, FloatMat& model, ByteMat* mask, int max_iters = 1000) {
		int count = from.GetCount();
		if (count < params.size)
			return false;
			
		int model_points = params.size;
		int niters = max_iters;
		bool result = false;
		
		Vector<Keypoint> subset0;
		Vector<Keypoint> subset1;
		bool found = false;
		
		int mc = model.cols;
		int mr = model.rows;
		int dt = 1;
		
		FloatMat M (mc, mr, dt);
		ByteMat curr_mask(count, 1, 1);
		
		int inliers_max = -1;
		int numinliers = 0;
		int nmodels = 0;
		
		Vector<double> err;
		err.SetCount(count << 2);
		
		// special case
		if (count == model_points) {
			if (kernel.Run(from, to, M) == 0) {
				return false;
			}
			
			M.copy_to(model);
			if (mask) {
				while (--count >= 0) {
					mask->data[count] = 1;
				}
			}
			return true;
		}
		
		for (int iter = 0; iter < niters; ++iter) {
			// generate subset
			found = GetSubset(kernel, from, to, model_points, count, subset0, subset1);
			if (!found) {
				if (iter == 0) {
					return false;
				}
				break;
			}
			
			ASSERT(subset0.GetCount() == model_points);
			nmodels = kernel.Run(subset0, subset1, M);
			if (nmodels <= 0)
				continue;
				
			// TODO handle multimodel output
			
			ASSERT(from.GetCount() == count);
			numinliers = FindInliers(kernel, M, from, to, params.thresh, err, curr_mask);
			
			if (numinliers > max(inliers_max, model_points - 1)) {
				M.copy_to(model);
				inliers_max = numinliers;
				if (mask)
					curr_mask.copy_to(*mask);
				niters = params.UpdateIters((count - numinliers) / count, niters);
				result = true;
			}
		}
		
		return result;
	}
	
	bool Lmeds(RansacParams& params, Kernel& kernel, const Vector<Keypoint>& from, Vector<Keypoint>& to, FloatMat& model, ByteMat* mask, int max_iters = 1000) {
		int count = from.GetCount();
		if (count < params.size)
			return false;
			
		int model_points = params.size;
		int niters = max_iters;
		bool result = false;
		
		Vector<Keypoint> subset0;
		Vector<Keypoint> subset1;
		bool found = false;
		
		int mc = model.cols;
		int mr = model.rows;
		int dt = 1;
		
		FloatMat M;
		M.SetSize(mc, mr, dt);
		
		ByteMat curr_mask;
		curr_mask.SetSize(count, 1, 1);
		
		int numinliers = 0;
		int nmodels = 0;
		
		Vector<double> err;
		double min_median = 1000000000.0;
		double sigma = 0.0;
		double median_i = 0.0;
		
		params.eps = 0.45;
		niters = params.UpdateIters(params.eps, niters);
		
		// special case
		if (count == model_points) {
			if (kernel.Run(from, to, M) == 0) {
				return false;
			}
			
			M.copy_to(model);
			if (mask) {
				while (--count >= 0) {
					mask->data[count] = 1;
				}
			}
			return true;
		}
		
		for (int iter = 0; iter < niters; ++iter) {
			// generate subset
			found = GetSubset(kernel, from, to, model_points, count, subset0, subset1);
			if (!found) {
				if (iter == 0) {
					return false;
				}
				break;
			}
			
			ASSERT(subset0.GetCount() == model_points);
			nmodels = kernel.Run(subset0, subset1, M);
			if (nmodels <= 0)
				continue;
				
			// TODO handle multimodel output
			ASSERT(from.GetCount() == count);
			kernel.Error(from, to, M, err);
			ASSERT(err.GetCount() == count);
			median_i = Median(err, 0, count - 1);
			
			if (median_i < min_median) {
				min_median = median_i;
				M.copy_to(model);
				result = true;
			}
		}
		
		if (result) {
			sigma = 2.5 * 1.4826 * (1 + 5.0 / (count - model_points)) * FastSqrt(min_median);
			sigma = max(sigma, 0.001);
			
			numinliers = FindInliers(kernel, model, from, to, sigma, err, curr_mask);
			if (mask)
				*mask = curr_mask;
				
			result = numinliers >= model_points;
		}
		
		return result;
	}
	
};



NAMESPACE_TOPSIDE_END

#endif
