#include "AudioCtrl.h"


NAMESPACE_TOPSIDE_BEGIN


AudioWindowCtrl::AudioWindowCtrl() {
	
}

AudioPlotCtrl::AudioPlotCtrl() {
	offset = 0;
	window = -1;
	channel = -1;
}

void AudioPlotCtrl::Paint(Draw& d) {
	Size sz(GetSize());
	
	d.DrawRect(sz, White());
	
	Record& file = *viewctrl->file;
	
	int count = file.GetCount();
	double xstep = (double)sz.cx / (count - 1);
	int step = 1.0 / xstep;
	
	float high = 1.0; //file.GetMax();
	float low = -1.0; //file.GetMin();
	float range = high - low;
	
	int y_center = sz.cy / 2;
	
	Color sym_bg = Color(191, 234, 255);
	
	for(int i = 0; i < count; i += step) {
		int x = (double)i * xstep;
		float value = file.Get(channel, i);
		
		int y = sz.cy - 1 - (value - low) / (range) * sz.cy;
		
		if (y < y_center) {
			d.DrawRect(x, y, 3, (y_center-y)*2, sym_bg);
			d.DrawRect(x, y, 1, y_center-y, Blue());
		} else {
			int h = y-y_center;
			d.DrawRect(x, y_center-h, 3, h*2, sym_bg);
			d.DrawRect(x, y_center, 1, h, Blue());
		}
		
	}
}





AudioHeatmapCtrl::AudioHeatmapCtrl() {
	
}



void AudioHeatmapCtrl::Paint(Draw& d) {
	Size sz(GetSize());
	
	d.DrawRect(sz, White());
	
	if (sz != render.GetSize()) {
		Record& file = *viewctrl->file;
		Vector<FFT1> ffts;
		
		int count = file.GetCount();
		
		double freq_min = 60;
		double freq_max = 8000;
		double freq_range = freq_max - freq_min;
		double freq_min_log10 = log10(freq_min);
		double freq_max_log10 = log10(freq_max);
		double freq_range_log = freq_max_log10 - freq_min_log10;
		double sample_rate = file.GetSampleRate();
		int fft_pos_max = 1.0 / freq_min * sample_rate - 1;
		int fft_pos_min = 1.0 / freq_max * sample_rate;
		int fft_pos_range = fft_pos_max - fft_pos_min;
		int fft_count = fft_pos_max + 1;
		
		int px_width = 2;
		int w_mod = sz.cx % px_width;
		if (w_mod)
			sz.cx += px_width - w_mod;
		
		ImageBuffer buf(sz);
		
		int slices = sz.cx / px_width;
		int slice_sample = count / slices;
		
		ffts.SetCount(slices);
		for(int i = 0; i < slices; i++) {
			int pos = slice_sample * i;
			FFT1& fft = ffts[i];
			file.SetData(fft, channel, pos, fft_count*2);
			fft.ForwardFFT();
		}
		
		double max_mag = -DBL_MAX;
		double min_mag = DBL_MAX;
		
		Vector<double> dest_vec;
		dest_vec.SetCount(sz.cx * sz.cy / px_width);
		RGBA* dest = buf.Begin();
		int k = 0;
		for (int y = 0; y < sz.cy; y++) {
			double freq_log10 = (double)(sz.cy - y) / sz.cy * freq_range_log + freq_min_log10;
			double freq = powf(10, freq_log10);
			int fft_pos = (freq - freq_min) / freq_range * fft_pos_range + fft_pos_min;
			
			int w = sz.cx / px_width;
			for (int x = 0; x < w; x++) {
				FFT1& fft = ffts[x];
				
				double mag = fft.GetMagnitude(fft_pos);
				
				if (!(mag > -DBL_MAX && mag < DBL_MAX)) mag = 0;
				else {
					if (mag > max_mag) max_mag = mag;
					if (mag < min_mag) min_mag = mag;
				}
				
				dest_vec[k] = mag;
				k++;
			}
		}
		
		double mag_range = max_mag - min_mag;
		double min_mag_log10 = min_mag != 0.0 ? log10(min_mag) : 0;
		double max_mag_log10 = log10(max_mag);
		double mag_range_log10 = max_mag_log10 - min_mag_log10;
		
		for(int i = 0; i < dest_vec.GetCount(); i++) {
			double mag = dest_vec[i];
			if (0) {
				mag = (mag - min_mag) / mag_range;
				mag = mag * mag_range_log10 + min_mag_log10;
				mag = powf(10, mag);
				mag = (mag - min_mag) / mag_range;
			} else {
				mag = log10(mag);
				mag = (mag - min_mag_log10) / mag_range_log10;
			}
			
			double gray = mag * 2.0 - 1.0;
			byte r = JetPaletteRed(gray) * 255.0;
			byte g = JetPaletteGreen(gray) * 255.0;
			byte b = JetPaletteBlue(gray) * 255.0;
			for (int j = 0; j < px_width; j++) {
				dest->r = r;
				dest->g = g;
				dest->b = b;
				dest->a = 255;
				dest++;
			}
		}
		
		render = buf;
	}
	
	d.DrawImage(0, 0, render);
}
















AudioViewCtrl::AudioViewCtrl() {
	
	Add(plot_split.SizePos());
	Add(hmap_split.SizePos());
	
	plot_split.Vert();
	hmap_split.Vert();
	
}

void AudioViewCtrl::RefreshData() {
	
	Record& file = *this->file;
	int channels = file.GetChannels();
	
	plot_split.Clear();
	hmap_split.Clear();
	plots.Clear();
	hmaps.Clear();
	
	plots.SetCount(channels);
	hmaps.SetCount(channels);
	for(int i = 0; i < channels; i++) {
		plots[i].viewctrl = this;
		hmaps[i].viewctrl = this;
		plots[i].channel = i;
		hmaps[i].channel = i;
		plot_split << plots[i];
		hmap_split << hmaps[i];
	}
	
	SetView(1);
	
}


void AudioViewCtrl::SetView(int type) {
	
	if (type == 0) {
		plot_split.Show();
		hmap_split.Hide();
	}
	else if (type == 1) {
		plot_split.Hide();
		hmap_split.Show();
	}
	else Panic("Invalid type");
	
}


NAMESPACE_TOPSIDE_END
