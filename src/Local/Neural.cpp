#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


void Neural::AddInput(int w, int h, int d) {
	Layer& l = layers.Add();
	l.type = L_INPUT;
	l.w = w;
	l.h = h;
	l.d = d;
}

void Neural::AddFullyConnected(int neuron_count, double l1_decay_mul, double l2_decay_mul, double bias) {
	Layer& l = layers.Add();
	l.type = L_FC;
	l.neuron_count = neuron_count;
	l.bias = bias;
	l.l1_decay_mul = l1_decay_mul;
	l.l2_decay_mul = l2_decay_mul;
}

void Neural::AddActivationTanh() {
	Layer& l = layers.Add();
	l.type = L_ACT_TANH;
}

void Neural::AddRegression(int count) {
	Layer& l = layers.Add();
	l.type = L_REGR;
	l.count = count;
}

void Neural::AddInputProxy(int start, int len) {
	Layer& l = layers.Add();
	l.type = L_INPROXY;
	l.start = start;
	l.len = len;
}

void Neural::AddMultiplexerActivationTanh(const Vector<int>& src_layers, int src_output_size) {
	Layer& l = layers.Add();
	l.type = L_MUPLEX_ACT_TANH;
	l.ivec <<= src_layers;
	l.neuron_count = src_output_size;
}

void Neural::Init(int batch_size, double l1_decay, double l2_decay) {
	iter_count = 0;
	this->batch_size = batch_size;
	this->l1_decay = l1_decay;
	this->l2_decay = l2_decay;
	last_loss = 0.0;
	l1_decay_loss = 0.0;
	l2_decay_loss = 0.0;
	eps = 1e-6;
	ro = 0.95;
	
	for(int i = 0; i < layers.GetCount(); i++) {
		Layer& cur = layers[i];
		
		if (cur.type == L_INPUT) {
			input_total = cur.w * cur.h * cur.d;
			cur.out.Init(cur.w, cur.h, cur.d, 0.0);
		}
		else if (cur.type == L_FC) {
			int in_w, in_h, in_d;
			GetVolumeDim(i-1, in_w, in_h, in_d);
			cur.in_count = in_w * in_h * in_d;
			ASSERT(cur.in_count > 0);
			
			cur.filters.SetCount(cur.neuron_count);
			for(int j = 0; j < cur.filters.GetCount(); j++) {
				cur.filters[j].Init(1, 1, cur.in_count);
			}
			cur.bias_filter.Init(1, 1, cur.neuron_count, cur.bias);
			
			int w, h, d;
			GetVolumeDim(i, w, h, d);
			cur.out.Init(w, h, d, 0.0);
		}
		else if (cur.type == L_ACT_TANH) {
			int in_w, in_h, in_d;
			GetVolumeDim(i-1, in_w, in_h, in_d);
			cur.in_count = in_w * in_h * in_d;
			ASSERT(cur.in_count > 0);
			
			int w, h, d;
			GetVolumeDim(i, w, h, d);
			cur.out.Init(w, h, d, 0.0);
		}
		else if (cur.type == L_REGR) {
			int in_w, in_h, in_d;
			GetVolumeDim(i-1, in_w, in_h, in_d);
			cur.in_count = in_w * in_h * in_d;
			ASSERT(cur.in_count > 0);
		}
		else if (cur.type == L_INPROXY) {
			int w, h, d;
			GetVolumeDim(i, w, h, d);
			cur.out.Init(w, h, d, 0.0);
		}
		else if (cur.type == L_MUPLEX_ACT_TANH) {
			int w, h, d;
			GetVolumeDim(i, w, h, d);
			cur.out.Init(w, h, d, 0.0);
		}
	}
}

void Neural::GetVolumeDim(int i, int& w, int& h, int& d) {
	ASSERT(i >= 0 && i < layers.GetCount());
	Layer& cur = layers[i];
	
	if (cur.type == L_INPUT) {
		w = cur.w;
		h = cur.h;
		d = cur.d;
	}
	else if (cur.type == L_FC) {
		w = 1;
		h = 1;
		d = cur.neuron_count;
	}
	else if (cur.type == L_ACT_TANH) {
		GetVolumeDim(i-1, w, h, d);
	}
	else if (cur.type == L_REGR) {
		GetVolumeDim(i-1, w, h, d);
		d = w * h * d;
		h = 1;
		w = 1;
	}
	else if (cur.type == L_INPROXY) {
		d = cur.len;
		h = 1;
		w = 1;
	}
	else if (cur.type == L_MUPLEX_ACT_TANH) {
		w = 1;
		h = 1;
		d = cur.neuron_count * cur.ivec.GetCount();
	}
	else {
		Panic("Not implemented");
	}
	
}

Volume& Neural::Forward(Volume& d) {
	
	Volume* prev = NULL;
	for(int l = 0; l < layers.GetCount(); l++) {
		Layer& cur = layers[l];
		
		if (cur.type == L_INPUT) {
			ASSERT(l == 0);
			prev = &d;
			continue;
		}
		else if (cur.type == L_FC) {
			ASSERT(cur.in_count > 0 && cur.neuron_count > 0);
			for(int i = 0; i < cur.neuron_count; i++) {
				Volume& filter = cur.filters[i];
				double tmp = 0.0;
				ASSERT(prev->d.GetCount() == cur.in_count && filter.d.GetCount() == cur.in_count);
				for(int j = 0; j < cur.in_count; j++)
					tmp += prev->d[j] * filter.d[j];
				cur.out.d[i] = tmp + cur.bias_filter.d[i];
			}
		}
		else if (cur.type == L_ACT_TANH) {
			ASSERT(cur.in_count > 0);
			for(int i = 0; i < cur.in_count; i++) {
				cur.out.d[i] = tanh(prev->d[i]);
			}
		}
		else if (cur.type == L_REGR) {
			ASSERT(l == layers.GetCount()-1);
			CopyHeapless(prev->d, cur.out.d);
			cur.out.PostInit();
			return cur.out;
		}
		else if (cur.type == L_INPROXY) {
			const Layer& in = layers[0];
			ASSERT(in.type == L_INPUT);
			ASSERT(cur.len > 0);
			for (int i = 0, j = cur.start; i < cur.len; i++, j++)
				cur.out.d[i] = d.d[j];
		}
		else if (cur.type == L_MUPLEX_ACT_TANH) {
			ASSERT(cur.ivec.GetCount());
			ASSERT(cur.neuron_count);
			for(int k = 0; k < cur.ivec.GetCount(); k++) {
				const Layer& in = layers[cur.ivec[k]];
				int start = k * cur.neuron_count;
				for (int i = 0, j = start; i < cur.neuron_count; i++, j++)
					cur.out.d[j] = tanh(in.out.d[i]);
			}
		}
		else Panic("Unexpected type");
		
		prev = &cur.out;
	}
	
	THROW(Exc("No last layer found in Neural::Forward"));
}

double Neural::Backward(const Volume& output) {
	double loss = 0.0;
	
	for(int l = layers.GetCount()-1; l >= 0; l--) {
		Layer& cur = layers[l];
		
		if (cur.type == L_INPUT) {
			
		}
		else if (cur.type == L_FC) {
			Layer& prev = layers[l-1];
			prev.out.ZeroGradients();
			for(int i = 0; i < cur.neuron_count; i++) {
				Volume& filter = cur.filters[i];
				double tmp = cur.out.g[i];
				for(int j = 0; j < cur.in_count; j++) {
					prev.out.g[j] += filter.d[j] * tmp;
					filter.g[j] += prev.out.d[j] * tmp;
				}
				cur.bias_filter.g[i] += tmp;
			}
		}
		else if (cur.type == L_ACT_TANH) {
			Layer& prev = layers[l-1];
			for(int i = 0; i < cur.in_count; i++) {
				double d = cur.out.d[i];
				prev.out.g[i] = (1.0 - d * d) * cur.out.g[i];
			}
		}
		else if (cur.type == L_REGR) {
			ASSERT(cur.in_count > 0);
			ASSERT(l == layers.GetCount()-1);
			Layer& prev = layers[l-1];
			for(int i = 0; i < cur.in_count; i++) {
				prev.out.g[i] = prev.out.d[i] - output.d[i];
			}
		}
		else if (cur.type == L_INPROXY) {
			
		}
		else if (cur.type == L_MUPLEX_ACT_TANH) {
			for(int k = 0; k < cur.ivec.GetCount(); k++) {
				Layer& in = layers[cur.ivec[k]];
				int start = k * cur.neuron_count;
				for (int i = 0, j = start; i < cur.neuron_count; i++, j++) {
					double d = cur.out.d[j];
					double g = cur.out.g[j];
					in.out.g[i] = (1.0 - d * d) * g;
				}
			}
		}
		else Panic("Unexpected layer type");
		
		
		if (l == layers.GetCount()-1) {
			ASSERT(cur.in_count > 0);
			Layer& prev = layers[l-1];
			for(int i = 0; i < cur.in_count; i++) {
				double dy = prev.out.g[i];
				loss += 0.5 * dy * dy;
			}
		}
	}
	
	Adadelta();
	
	return loss;
}

void Neural::Adadelta() {
	
	if (pg.IsEmpty()) {
		int pg_vol_len_total = 0;
		for(int i = 0; i < layers.GetCount(); i++) {
			Layer& l = layers[i];
			if (l.type == L_FC) {
				Vector<ParametersAndGradients>& lpg = this->pg.Add();
				
				int in_w, in_h, in_d;
				GetVolumeDim(i-1, in_w, in_h, in_d);
				int in_count = in_w * in_h * in_d;
				
				ParametersAndGradients& pg = lpg.Add();
				pg.l = i;
				pg.f = -1;
				pg.w = 1;
				pg.h = 1;
				pg.d = l.neuron_count;
				pg.len = pg.w * pg.h * pg.d;
				
				pg_vol_len_total += pg.len;
				
				ASSERT(l.filters.GetCount() == l.neuron_count);
				for(int j = 0; j < l.neuron_count; j++) {
					ParametersAndGradients& pg = lpg.Add();
					pg.l = i;
					pg.f = j;
					pg.w = 1;
					pg.h = 1;
					pg.d = in_count;
					pg.len = pg.w * pg.h * pg.d;
					
					pg_vol_len_total += pg.len;
				}
				
			}
		}
		
		gsum.SetCount(pg_vol_len_total, 0);
		xsum.SetCount(pg_vol_len_total, 0);
	}
	
	int gsum_i = 0;
	
	for(int i = 0; i < this->pg.GetCount(); i++) {
		Vector<ParametersAndGradients>& lpg = this->pg[i];
		ParametersAndGradients& pg = lpg[0];
		Layer& l = layers[pg.l];
		
		// Filters
		for(int j = 1; j < lpg.GetCount(); j++) {
			ParametersAndGradients& pg = lpg[j];
			Volume& vol = l.filters[j-1];
			double d0 = l1_decay * l.l1_decay_mul;
			double d1 = l2_decay * l.l2_decay_mul;
			
			ASSERT(vol.d.GetCount () == pg.len);
			for (int k = 0; k < pg.len; k++) {
				l1_decay_loss += d0 * fabs(vol.d[k]);
				l2_decay_loss += d1 * vol.d[k] * vol.d[k] * 0.5;
				double d2 = d0 * (vol.d[k] > 0.0 ? +1.0 : -1.0);
				double d3 = d1 * vol.d[k];
				double d4 = (d2 + d3 + vol.g[k]) / batch_size;
				double& g = gsum[gsum_i];
				double& x = xsum[gsum_i];
				g = ro * g + (1 - ro) * d4 * d4;
				double d5 = -1.0 * sqrt((x + eps) / (g + eps)) * d4;
				x = ro * x + (1 - ro) * d5 * d5;
				vol.d[k] += d5;
				vol.g[k] = 0;
				gsum_i++;
			}
		}
		
		// Is bias
		{
			Volume& vol = l.bias_filter;
			
			double d0 = l1_decay * l.l1_decay_mul;
			double d1 = l2_decay * l.l2_decay_mul;
			
			for (int j = 0; j < pg.len; j++) {
				l1_decay_loss += d0 * fabs(vol.d[j]);
				l2_decay_loss += d1 * vol.d[j] * vol.d[j] * 0.5;
				double d2 = d0 * (vol.d[j] > 0.0 ? +1.0 : -1.0);
				double d3 = d1 * vol.d[j];
				double d4 = (d2 + d3 + vol.g[j]) / batch_size;
				double& g = gsum[gsum_i];
				double& x = xsum[gsum_i];
				g = ro * g + (1 - ro) * d4 * d4;
				double d5 = -1.0 * sqrt((x + eps) / (g + eps)) * d4;
				x = ro * x + (1 - ro) * d5 * d5;
				vol.d[j] += d5;
				vol.g[j] = 0;
				
				gsum_i++;
			}
		}
	}
	
	ASSERT(gsum_i == gsum.GetCount());
}


NAMESPACE_TOPSIDE_END
