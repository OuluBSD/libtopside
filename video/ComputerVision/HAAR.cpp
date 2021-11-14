#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN



const Vector<BBox>& haar::detect_single_scale(const Vector<int>& int_sum, const Vector<int>& int_sqsum, const Vector<int>& int_tilted, const Vector<int>& int_canny_sum, int width, int height, double scale, const ComplexCascade& classifier) {
	rects.SetCount(0);
	
	double win_w = (classifier.size[0] * scale);
	double win_h = (classifier.size[1] * scale);
	double step_x = (0.5 * scale + 1.5);
	double step_y = step_x;
	
	//var i,j,k,x,y,
	double ex = (width - win_w);
	double ey = (height - win_h);
	int w1 = (width + 1);
	double inv_area = 1.0 / (win_w * win_h);
	//var stages, stage, trees, tree, stage_thresh, stage_sum, tree_sum, feature, features;
	//var fi_a, fi_b, fi_c, fi_d, fw, fh;
	
	int ii_b = (int)win_w;
	int ii_c = (int)(win_h * w1);
	int ii_d = (int)(ii_c + win_w);
	double edges_thresh = (win_w * win_h) * 0xff * this->edges_density;
	
	// if too much gradient we also can skip
	//int edges_thresh_high = ((win_w*win_h) * 0xff * 0.3);
	
	
	for (double y = 0; y < ey; y += step_y) {
		double ii_a = y * w1;
		for (double x = 0; x < ex; x += step_x, ii_a += step_x) {
			int a = (int)ii_a;
			int ab = (int)(ii_a+ii_b);
			int ac = (int)(ii_a+ii_c);
			int ad = (int)(ii_a+ii_d);
			
			double mean =       int_sum[a]
							  - int_sum[ab]
							  - int_sum[ac]
							  + int_sum[ad];
			                  
			// canny prune
			if (!int_canny_sum.IsEmpty()) {
				double edge_dens =   (int_canny_sum[a]
									- int_canny_sum[ab]
									- int_canny_sum[ac]
									+ int_canny_sum[ad]);
				if (edge_dens < edges_thresh || mean < 20) {
					x += step_x;
					ii_a += step_x;
					continue;
				}
			}
			
			mean *= inv_area;
			double variance =   (int_sqsum[a]
							   - int_sqsum[ab]
							   - int_sqsum[ac]
							   + int_sqsum[ad]) * inv_area - mean * mean;
			                   
			double std = variance > 0. ? pow_fast(variance, 0.5) : 1;
			
			const auto& stages = classifier.classifiers;
			int sn = stages.GetCount();
			bool found = true;
			double stage_sum = 0;
			for (int i = 0; i < sn; ++i) {
				const ComplexCascadeClassifier& stage = stages[i];
				double stage_thresh = stage.threshold;
				const auto& trees = stage.classifiers;
				int tn = trees.GetCount();
				stage_sum = 0;
				for (int j = 0; j < tn; ++j) {
					const SimpleCascadeClassifier& tree = trees[j];
					double tree_sum = 0;
					const Vector<Vector<int>>& features = tree.features;
					int fn = features.GetCount();
					if (tree.tilted) {
						for (int k = 0; k < fn; ++k) {
							const Vector<int>& feature = features[k];
							int fi_a = (int)(x + feature[0] * scale) + (int)(y + feature[1] * scale) * w1;
							int fw = (int)(feature[2] * scale);
							int fh = (int)(feature[3] * scale);
							int fi_b = fw * w1;
							int fi_c =  fh * w1;
							
							tree_sum +=   (int_tilted[fi_a]
										 - int_tilted[fi_a + fw + fi_b]
										 - int_tilted[fi_a - fh + fi_c]
										 + int_tilted[fi_a + fw - fh + fi_b + fi_c]) * feature[4];
						}
					}
					else {
						for (int k = 0; k < fn; ++k) {
							const Vector<int>& feature = features[k];
							int fi_a = (int)(x + feature[0] * scale) + (int)(y + feature[1] * scale) * w1;
							int fw = (int)(feature[2] * scale);
							int fh = (int)(feature[3] * scale);
							int fi_c = fh * w1;
							
							tree_sum +=   (int_sum[fi_a]
										 - int_sum[fi_a+fw]
										 - int_sum[fi_a+fi_c]
										 + int_sum[fi_a+fi_c+fw]) * feature[4];
						}
					}
					stage_sum += (tree_sum * inv_area < tree.threshold * std) ? tree.left_val : tree.right_val;
				}
				if (stage_sum < stage_thresh) {
					found = false;
					break;
				}
			}
			
			if (found) {
				BBox& b = rects.Add();
				b.x = x;
				b.y = y;
				b.width = win_w;
				b.height = win_h;
				b.neighbors = 1;
				b.confidence = stage_sum;
				x += step_x, ii_a += step_x;
			}
		}
	}
	return rects;
}

const Vector<BBox>& haar::detect_multi_scale(const Vector<int>& int_sum, const Vector<int>& int_sqsum, const Vector<int>& int_tilted, const Vector<int>& int_canny_sum, int width, int height, const ComplexCascade& classifier, double scale_factor, double scale_min) {
	rects.SetCount(0);
	
	int win_w = classifier.size[0];
	int win_h = classifier.size[1];
	
	while (scale_min * win_w < width && scale_min * win_h < height) {
		rects.Append(detect_single_scale(int_sum, int_sqsum, int_tilted, int_canny_sum, width, height, scale_min, classifier));
		scale_min *= scale_factor;
	}
	return rects;
}

NAMESPACE_TOPSIDE_END
