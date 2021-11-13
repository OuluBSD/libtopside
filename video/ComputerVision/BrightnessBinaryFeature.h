#ifndef _ComputerVision_BrightnessBinaryFeature_h_
#define _ComputerVision_BrightnessBinaryFeature_h_

NAMESPACE_TOPSIDE_BEGIN


class BrightnessBinaryFeature {
	pyra8 img_pyr;
	int interval = 4;
	double scale = 1.1486;
	int next = 5;
	double scale_to = 1;
	
	
public:

	BrightnessBinaryFeature() {
		img_pyr.SetSize(0, 0, 0, 1);
	}
	
	bool _group_func(const Rect& r1, const Rect& r2) {
		int w1 = r1.Width();
		int w2 = r2.Width();
		double distance = (w1 * 0.25 + 0.5);
		
		return r2.left <= r1.left + distance &&
			   r2.left >= r1.left - distance &&
			   r2.top <= r1.top + distance &&
			   r2.top >= r1.top - distance &&
			   w2 <= (w1 * 1.5 + 0.5) &&
			   w1 <= (w2 * 1.5 + 0.5);
	}
	
	// make features local copy
	// to avoid array allocation with each scale
	// this is strange but array works faster than Int32 version???
	void prepare_cascade(Cascade& cascade) {
		for (CascadeStageClassifier& cs : cascade.stage_classifiers) {
			ASSERT(cs.features.GetCount() == cs.count);
			cs._features.SetCount(cs.count);
			auto iter = cs._features.Begin();
			for (const CascadeFeature& f : cs.features) {
				CascadeFeature& t = *iter++;
				t.Init2D(f.size);
			}
		}
	}
	
	const pyra8& build_pyramid(const pyra8::DTen& src, int min_width, int min_height, int interval = 4) {
		int sw = src.cols;
		int sh = src.rows;
		int channels = src.channels;
		ASSERT(sw > 0 && sh > 0 && channels > 0);
		int nw = 0, nh = 0;
		bool new_pyr = false;
		pyra8::DTen* src0 = 0;
		pyra8::DTen* src1 = 0;
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
			pyra8::Downsample(*src1, *src0);
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
			pyra8::Downsample(*src1, *src0, 1, 0);
			
			src0 = &img_pyr.data[(i<<2)+2];
			if (new_pyr || nw != src0->cols || nh != src0->rows) {
				img_pyr.data[(i<<2)+2].SetSize(nw, nh, channels);
				src0 = &img_pyr.data[(i<<2)+2];
			}
			pyra8::Downsample(*src1, *src0, 0, 1);
			
			src0 = &img_pyr.data[(i<<2)+3];
			if (new_pyr || nw != src0->cols || nh != src0->rows) {
				img_pyr.data[(i<<2)+3].SetSize(nw, nh, channels);
				src0 = &img_pyr.data[(i<<2)+3];
			}
			pyra8::Downsample(*src1, *src0, 1, 1);
		}
		return img_pyr;
	}
	
	Vector<BBox> detect(const pyra8& pyramid, Cascade& cascade) {
		int interval = this->interval;
		double scale = this->scale;
		int next = this->next;
		int scale_upto = this->scale_to;
		double sum = 0.0, alpha;
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
			int sn = cascade.stage_classifiers.GetCount();
			for (int j = 0; j < sn; j++) {
				Vector<CascadeFeature>& orig_feature = cascade.stage_classifiers[j].features;
				Vector<CascadeFeature>& feature = cascade.stage_classifiers[j]._features;
				int f_cnt = cascade.stage_classifiers[j].count;
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
				u8[2] = pyr[i4 + (next<<3) + q].data;
				u8o[0] = (dx[q] * bpp2) + dy[q] * (pyr[i4].cols * bpp2);
				u8o[1] = (dx[q] * bpp) + dy[q] * (pyr[i4 + (next<<2)].cols * bpp);
				u8o[2] = 0;
				for (int y = 0; y < qh; y++) {
					for (int x = 0; x < qw; x++) {
						sum = 0;
						flag = true;
						sn = cascade.stage_classifiers.GetCount();
						for (int j = 0; j < sn; j++) {
							sum = 0;
							alpha = cascade.stage_classifiers[j].alpha;
							feature = cascade.stage_classifiers[j]._feature;
							int f_cnt = cascade.stage_classifiers[j].count;
							for (int k = 0; k < f_cnt; k++) {
								feature_k = feature[k];
								int pmin = u8[feature_k.pz[0]][u8o[feature_k.pz[0]] + feature_k.px[0]];
								int nmax = u8[feature_k.nz[0]][u8o[feature_k.nz[0]] + feature_k.nx[0]];
								if (pmin <= nmax) {
									sum += alpha[k << 1];
								}
								else {
									shortcut = true;
									int q_cnt = feature_k.size;
									for (int f = 1; f < q_cnt; f++) {
										if (feature_k.pz[f] >= 0) {
											int p = u8[feature_k.pz[f]][u8o[feature_k.pz[f]] + feature_k.px[f]];
											if (p < pmin) {
												if (p <= nmax) {
													shortcut = false;
													break;
												}
												pmin = p;
											}
										}
										if (feature_k.nz[f] >= 0) {
											int n = u8[feature_k.nz[f]][u8o[feature_k.nz[f]] + feature_k.nx[f]];
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
							if (sum < cascade.stage_classifiers[j].threshold) {
								flag = false;
								break;
							}
						}
						if (flag) {
						seq.push( {"x" : (x * 4 + dx[q] * 2) * scale_x,
								   "y" : (y * 4 + dy[q] * 2) * scale_y,
								   "width" : cascade.width * scale_x,
								   "height" : cascade.height * scale_y,
								   "neighbor" : 1,
								   "confidence" : sum
									  });
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
	
	// OpenCV method to group detected rectangles
	void group_rectangles(const Vector<Rect>& rects, int min_neighbors = 1) {
		int n = rects.GetCount;
		Vector<Node> node;
		node.SetCount(n);
		for (int i = 0; i < n; ++i) {
			node[i].Set(-1, rects[i], 0);
			/*node[i] = {"parent" : -1,
			           "element" : rects[i],
			           "rank" : 0};*/
		}
		for (int i = 0; i < n; ++i) {
			if (!node[i].element)
				continue;
			int root = i;
			while (node[root].parent != -1)
				root = node[root].parent;
			for (int j = 0; j < n; ++j) {
				if (i != j && node[j].element && _group_func(node[i].element, node[j].element)) {
					int root2 = j;
					
					while (node[root2].parent != -1)
						root2 = node[root2].parent;
						
					if (root2 != root) {
						if (node[root].rank > node[root2].rank)
							node[root2].parent = root;
						else {
							node[root].parent = root2;
							if (node[root].rank == node[root2].rank)
								node[root2].rank++;
							root = root2;
						}
						
						// compress path from node2 to the root:
						int temp, node2 = j;
						while (node[node2].parent != -1) {
							temp = node2;
							node2 = node[node2].parent;
							node[temp].parent = root;
						}
						
						// compress path from node to the root:
						node2 = i;
						while (node[node2].parent != -1) {
							temp = node2;
							node2 = node[node2].parent;
							node[temp].parent = root;
						}
					}
				}
			}
		}
		Vector<int> idx_seq;
		int class_idx = 0;
		for (int i = 0; i < n; i++) {
			int j = -1;
			int node1 = i;
			if (node[node1].element) {
				while (node[node1].parent != -1)
					node1 = node[node1].parent;
				if (node[node1].rank >= 0)
					node[node1].rank = ~class_idx++;
				j = ~node[node1].rank;
			}
			idx_seq[i] = j;
		}
		
		Vector<BBox> comps;
		for (int i = 0; i < class_idx + 1; ++i) {
		comps[i] = {"neighbors" :
						0,
					"x" :
						0,
					"y" :
						0,
					"width" :
						0,
					"height" :
						0,
					"confidence" :
						0
					   };
		}
		
		// count number of neighbors
		for (int i = 0; i < n; ++i) {
			const Rect& r1 = rects[i];
			int idx = idx_seq[i];
			
			if (comps[idx].neighbors == 0)
				comps[idx].confidence = r1.confidence;
				
			++comps[idx].neighbors;
			
			comps[idx].x += r1.x;
			comps[idx].y += r1.y;
			comps[idx].width += r1.width;
			comps[idx].height += r1.height;
			comps[idx].confidence = max(comps[idx].confidence, r1.confidence);
		}
		
		Vector<BBox> seq2;
		// calculate average bounding box
		for (i = 0; i < class_idx; ++i) {
			n = comps[i].neighbors;
			if (n >= min_neighbors)
			seq2.push( {"x" : (comps[i].x * 2 + n) / (2 * n),
						"y" : (comps[i].y * 2 + n) / (2 * n),
						"width" : (comps[i].width * 2 + n) / (2 * n),
						"height" : (comps[i].height * 2 + n) / (2 * n),
						"neighbors" : comps[i].neighbors,
						"confidence" : comps[i].confidence
						   });
		}
		
		Vector<BBox> result_seq;
		n = seq2.GetCount();
		// filter out small face rectangles inside large face rectangles
		for (int i = 0; i < n; ++i) {
			const BBox& r1 = seq2[i];
			bool flag = true;
			for (int j = 0; j < n; ++j) {
				const BBox& r2 = seq2[j];
				double distance = (r2.width * 0.25 + 0.5);
				
				if (i != j &&
					r1.x >= r2.x - distance &&
					r1.y >= r2.y - distance &&
					r1.x + r1.width <= r2.x + r2.width + distance &&
					r1.y + r1.height <= r2.y + r2.height + distance &&
					(r2.neighbors > max(3, r1.neighbors) || r1.neighbors < 3)) {
					flag = false;
					break;
				}
			}
			
			if (flag)
				result_seq.push(r1);
		}
		return result_seq;
	}
	
};


NAMESPACE_TOPSIDE_END

#endif
