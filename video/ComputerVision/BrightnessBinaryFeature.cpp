#include "ComputerVision.h"

NAMESPACE_TOPSIDE_BEGIN


BrightnessBinaryFeature::BrightnessBinaryFeature() {
	img_pyr.SetSize(0, 0, 0, 1);
}
// make features local copy
// to avoid array allocation with each scale
// this is strange but array works faster than Int32 version???
void BrightnessBinaryFeature::prepare_cascade(Cascade& cascade) {
	for (CascadeStageClassifier& cs : cascade.classifiers) {
		ASSERT(cs.features.GetCount() == cs.count);
		cs._features.SetCount(cs.count);
		auto iter = cs._features.Begin();
		for (const CascadeFeature& f : cs.features) {
			CascadeFeature& t = *iter++;
			t.Init2D(f.size);
		}
	}
}

const pyra8& BrightnessBinaryFeature::build_pyramid(const pyra8::Mat& src, int min_width, int min_height, int interval) {
	int sw = src.cols;
	int sh = src.rows;
	int channels = src.channels;
	ASSERT(sw > 0 && sh > 0 && channels > 0);
	int nw = 0, nh = 0;
	bool new_pyr = false;
	pyra8::Mat* src0 = 0;
	pyra8::Mat* src1 = 0;
	int channel = 0; // red
	
	this->interval = interval;
	this->scale = pow_fast(2.0, 1 / (this->interval + 1));
	this->next = (this->interval + 1);
	this->scale_to = (log_fast(min<double>(sw / min_width, sh / min_height)) / log_fast(this->scale));
	
	int pyr_l = (int)((this->scale_to + this->next * 2) * 4);
	ASSERT(pyr_l > 0 && pyr_l < 64);
	if (img_pyr.GetLevels() != pyr_l) {
		img_pyr.SetLevels(pyr_l);
		new_pyr = true;
		img_pyr.data[0] = src; // first is src
	}
	
	for (int i = 1; i <= this->interval; ++i) {
		nw = (int)(sw / pow_fast(this->scale, i));
		nh = (int)(sh / pow_fast(this->scale, i));
		src0 = &img_pyr.data[i<<2];
		if (new_pyr || nw != src0->cols || nh != src0->rows) {
			img_pyr.data[i<<2].SetSize(nw, nh, channels);
			src0 = &img_pyr.data[i<<2];
		}
		resample(src, *src0, nw, nh);
	}
	for (int i = this->next; i < this->scale_to + this->next * 2; ++i) {
		src1 = &img_pyr.data[(i << 2) - (this->next << 2)];
		src0 = &img_pyr.data[i<<2];
		nw = src1->cols >> 1;
		nh = src1->rows >> 1;
		if (new_pyr || nw != src0->cols || nh != src0->rows) {
			img_pyr.data[i<<2].SetSize(nw, nh, channels);
			src0 = &img_pyr.data[i<<2];
		}
		DownsamplePyramid(*src1, *src0);
	}
	for (int i = this->next * 2; i < this->scale_to + this->next * 2; ++i) {
		src1 = &img_pyr.data[(i << 2) - (this->next << 2)];
		nw = src1->cols >> 1;
		nh = src1->rows >> 1;
		src0 = &img_pyr.data[(i<<2)+1];
		if (new_pyr || nw != src0->cols || nh != src0->rows) {
			img_pyr.data[(i<<2)+1].SetSize(nw, nh, channels);
			src0 = &img_pyr.data[(i<<2)+1];
		}
		DownsamplePyramid(*src1, *src0, 1, 0);
		
		src0 = &img_pyr.data[(i<<2)+2];
		if (new_pyr || nw != src0->cols || nh != src0->rows) {
			img_pyr.data[(i<<2)+2].SetSize(nw, nh, channels);
			src0 = &img_pyr.data[(i<<2)+2];
		}
		DownsamplePyramid(*src1, *src0, 0, 1);
		
		src0 = &img_pyr.data[(i<<2)+3];
		if (new_pyr || nw != src0->cols || nh != src0->rows) {
			img_pyr.data[(i<<2)+3].SetSize(nw, nh, channels);
			src0 = &img_pyr.data[(i<<2)+3];
		}
		DownsamplePyramid(*src1, *src0, 1, 1);
	}
	return img_pyr;
}

Vector<BBox> BrightnessBinaryFeature::detect(const pyra8& pyramid, Cascade& cascade) {
	int interval = this->interval;
	double scale = this->scale;
	int next = this->next;
	double scale_upto = this->scale_to;
	double sum = 0.0;
	bool flag = true, shortcut = true;
	double scale_x = 1.0, scale_y = 1.0;
	int dx[] = {0, 1, 0, 1};
	int dy[] = {0, 0, 1, 1};
	Vector<BBox> seq;
	const auto& pyr = pyramid.data;
	int bpp = 1, bpp2 = 2, bpp4 = 4;
	
	const Vector<byte>* u8[3] = {0, 0, 0};
	int u8o[] = {0, 0, 0};
	int step[] = {0, 0, 0};
	int paddings[] = {0, 0, 0};
	
	for (int i = 0; i < scale_upto; i++) {
		int i4 = (i << 2);
		int qw = pyr[i4 + (next << 3)].cols - (cascade.width >> 2);
		int qh = pyr[i4 + (next << 3)].rows - (cascade.height >> 2);
		step[0] = pyr[i4].cols * bpp;
		step[1] = pyr[i4 + (next << 2)].cols * bpp;
		step[2] = pyr[i4 + (next << 3)].cols * bpp;
		paddings[0] = (pyr[i4].cols * bpp4) - (qw * bpp4);
		paddings[1] = (pyr[i4 + (next << 2)].cols * bpp2) - (qw * bpp2);
		paddings[2] = (pyr[i4 + (next << 3)].cols * bpp) - (qw * bpp);
		int sn = cascade.classifiers.GetCount();
		for (int j = 0; j < sn; j++) {
			Vector<CascadeFeature>& orig_feature = cascade.classifiers[j].features;
			Vector<CascadeFeature>& feature = cascade.classifiers[j]._features;
			int f_cnt = cascade.classifiers[j].count;
			for (int k = 0; k < f_cnt; k++) {
				CascadeFeature& feature_k = feature[k];
				CascadeFeature& feature_o = orig_feature[k];
				int q_cnt = feature_o.size;
				for (int q = 0; q < q_cnt; q++) {
					feature_k.px[q] = (feature_o.px[q] * bpp) + feature_o.py[q] * step[feature_o.pz[q]];
					feature_k.pz[q] = feature_o.pz[q];
					feature_k.nx[q] = (feature_o.nx[q] * bpp) + feature_o.ny[q] * step[feature_o.nz[q]];
					feature_k.nz[q] = feature_o.nz[q];
				}
			}
		}
		u8[0] = &pyr[i4].data;
		u8[1] = &pyr[i4 + (next<<2)].data;
		for (int q = 0; q < 4; q++) {
			u8[2] = &pyr[i4 + (next<<3) + q].data;
			u8o[0] = (dx[q] * bpp2) + dy[q] * (pyr[i4].cols * bpp2);
			u8o[1] = (dx[q] * bpp) + dy[q] * (pyr[i4 + (next<<2)].cols * bpp);
			u8o[2] = 0;
			for (int y = 0; y < qh; y++) {
				for (int x = 0; x < qw; x++) {
					sum = 0;
					flag = true;
					sn = cascade.classifiers.GetCount();
					for (int j = 0; j < sn; j++) {
						sum = 0;
						const Vector<double>& alpha = cascade.classifiers[j].alpha;
						const Vector<CascadeFeature>& feature = cascade.classifiers[j]._features;
						int f_cnt = cascade.classifiers[j].count;
						for (int k = 0; k < f_cnt; k++) {
							const CascadeFeature& feature_k = feature[k];
							int pmin = (*u8[feature_k.pz[0]])[u8o[feature_k.pz[0]] + feature_k.px[0]];
							int nmax = (*u8[feature_k.nz[0]])[u8o[feature_k.nz[0]] + feature_k.nx[0]];
							if (pmin <= nmax) {
								sum += alpha[k << 1];
							}
							else {
								shortcut = true;
								int q_cnt = feature_k.size;
								for (int f = 1; f < q_cnt; f++) {
									if (feature_k.pz[f] >= 0) {
										int p = (*u8[feature_k.pz[f]])[u8o[feature_k.pz[f]] + feature_k.px[f]];
										if (p < pmin) {
											if (p <= nmax) {
												shortcut = false;
												break;
											}
											pmin = p;
										}
									}
									if (feature_k.nz[f] >= 0) {
										int n = (*u8[feature_k.nz[f]])[u8o[feature_k.nz[f]] + feature_k.nx[f]];
										if (n > nmax) {
											if (pmin <= n) {
												shortcut = false;
												break;
											}
											nmax = n;
										}
									}
								}
								sum += (shortcut) ? alpha[(k << 1) + 1] : alpha[k << 1];
							}
						}
						if (sum < cascade.classifiers[j].threshold) {
							flag = false;
							break;
						}
					}
					if (flag) {
						BBox& b = seq.Add();
						b.x = (x * 4 + dx[q] * 2) * scale_x;
						b.y = (y * 4 + dy[q] * 2) * scale_y;
						b.width = cascade.width * scale_x;
						b.height = cascade.height * scale_y;
						b.neighbors = 1;
						b.confidence = sum;
						
						++x;
						u8o[0] += bpp4;
						u8o[1] += bpp2;
						u8o[2] += bpp;
					}
					u8o[0] += bpp4;
					u8o[1] += bpp2;
					u8o[2] += bpp;
				}
				u8o[0] += paddings[0];
				u8o[1] += paddings[1];
				u8o[2] += paddings[2];
			}
		}
		scale_x *= scale;
		scale_y *= scale;
	}
	
	return seq;
}


NAMESPACE_TOPSIDE_END
