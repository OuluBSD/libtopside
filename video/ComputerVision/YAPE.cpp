#include "ComputerVision.h"


NAMESPACE_TOPSIDE_BEGIN


void lev_table_t::Set(int w, int h, int r) {
	width = w;
	height = h;
	radius = r;
	dirs.SetCount(1024);
	dirs_count = yape::precompute_directions(w, this->dirs, r);
	ASSERT(dirs_count > 0);
	scores.SetCount(w*h, 0);
}



int yape::precompute_directions(int step, Vector<int>& dirs, int R) {
	int i = 0;
	double x, y;
	
	x = R;
	for (y = 0; y < x; y++, i++) {
		x = (FastSqrt((R * R - y * y)) + 0.5);
		dirs[i] = (int)(x + step * y);
	}
	for (x-- ; x < y && x >= 0; x--, i++) {
		y = (FastSqrt((R * R - x * x)) + 0.5);
		dirs[i] = (int)(x + step * y);
	}
	for (; -x < y; x--, i++) {
		y = (FastSqrt((R * R - x * x)) + 0.5);
		dirs[i] = (int)(x + step * y);
	}
	for (y-- ; y >= 0; y--, i++) {
		x = (-FastSqrt((R * R - y * y)) - 0.5);
		dirs[i] = (int)(x + step * y);
	}
	for (; y > x; y--, i++) {
		x = (-FastSqrt((R * R - y * y)) - 0.5);
		dirs[i] = (int)(x + step * y);
	}
	for (x++ ; x <= 0; x++, i++) {
		y = (-FastSqrt((R * R - x * x)) - 0.5);
		dirs[i] = (int)(x + step * y);
	}
	for (; x < -y; x++, i++) {
		y = (-FastSqrt((R * R - x * x)) - 0.5);
		dirs[i] = (int)(x + step * y);
	}
	for (y++ ; y < 0; y++, i++) {
		x = (FastSqrt((R * R - y * y)) + 0.5);
		dirs[i] = (int)(x + step * y);
	}
	
	dirs[i] = dirs[0];
	dirs[i + 1] = dirs[1];
	return i;
}

int yape::third_check(Vector<int>& Sb, int off, int step) {
	int n = 0;
	if (Sb[off+1]   != 0)
		n++;
	if (Sb[off-1]   != 0)
		n++;
	if (Sb[off+step]   != 0)
		n++;
	if (Sb[off+step+1] != 0)
		n++;
	if (Sb[off+step-1] != 0)
		n++;
	if (Sb[off-step]   != 0)
		n++;
	if (Sb[off-step+1] != 0)
		n++;
	if (Sb[off-step-1] != 0)
		n++;
		
	return n;
}

bool yape::is_local_maxima(const Vector<int>& p, int off, int v, int step, int neighborhood) {

	if (v > 0) {
		off -= step * neighborhood;
		for (int y = -neighborhood; y <= neighborhood; ++y) {
			for (int x = -neighborhood; x <= neighborhood; ++x) {
				if (p[off+x] > v)
					return false;
			}
			off += step;
		}
	}
	else {
		off -= step * neighborhood;
		for (int y = -neighborhood; y <= neighborhood; ++y) {
			for (int x = -neighborhood; x <= neighborhood; ++x) {
				if (p[off+x] < v)
					return false;
			}
			off += step;
		}
	}
	return true;
}

void yape::perform_one_point(const Vector<byte>& I, int x, Vector<int>& Scores, byte Im, byte Ip, const Vector<int>& dirs, int opposite, int dirs_nb) {
	ASSERT(opposite > 0);
	int score = 0;
	int a = 0;
	int b = (opposite - 1);
	byte A = 0, B0 = 0, B1 = 0, B2 = 0;
	int state = 0;
	
	// WE KNOW THAT NOT(A ~ I0 & B1 ~ I0):
	A = I[x+dirs[a]];
	if ((A <= Ip)) {
		if ((A >= Im)) { // A ~ I0
			int i = x+dirs[b];
			B0 = I[i];
			if ((B0 <= Ip)) {
				if ((B0 >= Im)) {
					Scores[x] = 0;
					return;
				}
				else {
					b++;
					B1 = I[x+dirs[b]];
					if ((B1 > Ip)) {
						b++;
						B2 = I[x+dirs[b]];
						if ((B2 > Ip))
							state = 3;
						else if ((B2 < Im))
							state = 6;
						else {
							Scores[x] = 0;    // A ~ I0, B2 ~ I0
							return;
						}
					}
					else { /* if ((B1 < Im))*/
						b++;
						B2 = I[x+dirs[b]];
						if ((B2 > Ip))
							state = 7;
						else if ((B2 < Im))
							state = 2;
						else {
							Scores[x] = 0;    // A ~ I0, B2 ~ I0
							return;
						}
					}
					//else { Scores[x] = 0; return; } // A ~ I0, B1 ~ I0
				}
			}
			else { // B0 < I0
				b++;
				B1 = I[x+dirs[b]];
				if ((B1 > Ip)) {
					b++;
					B2 = I[x+dirs[b]];
					if ((B2 > Ip))
						state = 3;
					else if ((B2 < Im))
						state = 6;
					else {
						Scores[x] = 0;    // A ~ I0, B2 ~ I0
						return;
					}
				}
				else if ((B1 < Im)) {
					b++;
					B2 = I[x+dirs[b]];
					if ((B2 > Ip))
						state = 7;
					else if ((B2 < Im))
						state = 2;
					else {
						Scores[x] = 0;    // A ~ I0, B2 ~ I0
						return;
					}
				}
				else {
					Scores[x] = 0;    // A ~ I0, B1 ~ I0
					return;
				}
			}
		}
		else { // A > I0
			B0 = I[x+dirs[b]];
			if ((B0 > Ip)) {
				Scores[x] = 0;
				return;
			}
			b++;
			B1 = I[x+dirs[b]];
			if ((B1 > Ip)) {
				Scores[x] = 0;
				return;
			}
			b++;
			B2 = I[x+dirs[b]];
			if ((B2 > Ip)) {
				Scores[x] = 0;
				return;
			}
			state = 1;
		}
	}
	else { // A < I0
		B0 = I[x+dirs[b]];
		if ((B0 < Im)) {
			Scores[x] = 0;
			return;
		}
		b++;
		B1 = I[x+dirs[b]];
		if ((B1 < Im)) {
			Scores[x] = 0;
			return;
		}
		b++;
		B2 = I[x+dirs[b]];
		if ((B2 < Im)) {
			Scores[x] = 0;
			return;
		}
		state = 0;
	}
	
	for (a = 1; a <= opposite; a++) {
		A = I[x+dirs[a]];
		
		switch (state) {
		case 0:
			if ((A > Ip)) {
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 < Im)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 0;
					break;
				};
			}
			if ((A < Im)) {
				if ((B1 > Ip)) {
					Scores[x] = 0;
					return;
				}
				if ((B2 > Ip)) {
					Scores[x] = 0;
					return;
				}
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 > Ip)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 8;
					break;
				};
			}
			// A ~ I0
			if ((B1 <= Ip)) {
				Scores[x] = 0;
				return;
			}
			if ((B2 <= Ip)) {
				Scores[x] = 0;
				return;
			}
			B1 = B2;
			b++;
			B2 = I[x+dirs[b]];
			if ((B2 > Ip)) {
				score -= A + B1;
				state = 3;
				break;
			};
			if ((B2 < Im)) {
				score -= A + B1;
				state = 6;
				break;
			};
			{
				Scores[x] = 0;
				return;
			}
			
		case 1:
			if ((A < Im)) {
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 > Ip)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 1;
					break;
				};
			}
			if ((A > Ip)) {
				if ((B1 < Im)) {
					Scores[x] = 0;
					return;
				}
				if ((B2 < Im)) {
					Scores[x] = 0;
					return;
				}
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 < Im)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 9;
					break;
				};
			}
			// A ~ I0
			if ((B1 >= Im)) {
				Scores[x] = 0;
				return;
			}
			if ((B2 >= Im)) {
				Scores[x] = 0;
				return;
			}
			B1 = B2;
			b++;
			B2 = I[x+dirs[b]];
			if ((B2 < Im)) {
				score -= A + B1;
				state = 2;
				break;
			};
			if ((B2 > Ip)) {
				score -= A + B1;
				state = 7;
				break;
			};
			{
				Scores[x] = 0;
				return;
			}
			
		case 2:
			if ((A > Ip)) {
				Scores[x] = 0;
				return;
			}
			B1 = B2;
			b++;
			B2 = I[x+dirs[b]];
			if ((A < Im)) {
				if ((B2 > Ip)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 4;
					break;
				};
			}
			// A ~ I0
			if ((B2 > Ip)) {
				score -= A + B1;
				state = 7;
				break;
			};
			if ((B2 < Im)) {
				score -= A + B1;
				state = 2;
				break;
			};
			{
				Scores[x] = 0;    // A ~ I0, B2 ~ I0
				return;
			}
			
		case 3:
			if ((A < Im)) {
				Scores[x] = 0;
				return;
			}
			B1 = B2;
			b++;
			B2 = I[x+dirs[b]];
			if ((A > Ip)) {
				if ((B2 < Im)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 5;
					break;
				};
			}
			// A ~ I0
			if ((B2 > Ip)) {
				score -= A + B1;
				state = 3;
				break;
			};
			if ((B2 < Im)) {
				score -= A + B1;
				state = 6;
				break;
			};
			{
				Scores[x] = 0;
				return;
			}
			
		case 4:
			if ((A > Ip)) {
				Scores[x] = 0;
				return;
			}
			if ((A < Im)) {
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 > Ip)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 1;
					break;
				};
			}
			if ((B2 >= Im)) {
				Scores[x] = 0;
				return;
			}
			B1 = B2;
			b++;
			B2 = I[x+dirs[b]];
			if ((B2 < Im)) {
				score -= A + B1;
				state = 2;
				break;
			};
			if ((B2 > Ip)) {
				score -= A + B1;
				state = 7;
				break;
			};
			{
				Scores[x] = 0;
				return;
			}
			
		case 5:
			if ((A < Im)) {
				Scores[x] = 0;
				return;
			}
			if ((A > Ip)) {
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 < Im)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 0;
					break;
				};
			}
			// A ~ I0
			if ((B2 <= Ip)) {
				Scores[x] = 0;
				return;
			}
			B1 = B2;
			b++;
			B2 = I[x+dirs[b]];
			if ((B2 > Ip)) {
				score -= A + B1;
				state = 3;
				break;
			};
			if ((B2 < Im)) {
				score -= A + B1;
				state = 6;
				break;
			};
			{
				Scores[x] = 0;
				return;
			}
			
		case 7:
			if ((A > Ip)) {
				Scores[x] = 0;
				return;
			}
			if ((A < Im)) {
				Scores[x] = 0;
				return;
			}
			B1 = B2;
			b++;
			B2 = I[x+dirs[b]];
			// A ~ I0
			if ((B2 > Ip)) {
				score -= A + B1;
				state = 3;
				break;
			};
			if ((B2 < Im)) {
				score -= A + B1;
				state = 6;
				break;
			};
			{
				Scores[x] = 0;    // A ~ I0, B2 ~ I0
				return;
			}
			
		case 6:
			if ((A > Ip)) {
				Scores[x] = 0;
				return;
			}
			if ((A < Im)) {
				Scores[x] = 0;
				return;
			}
			B1 = B2;
			b++;
			B2 = I[x+dirs[b]];
			// A ~ I0
			if ((B2 < Im)) {
				score -= A + B1;
				state = 2;
				break;
			};
			if ((B2 > Ip)) {
				score -= A + B1;
				state = 7;
				break;
			};
			{
				Scores[x] = 0;    // A ~ I0, B2 ~ I0
				return;
			}
			
		case 8:
			if ((A > Ip)) {
				if ((B2 < Im)) {
					Scores[x] = 0;
					return;
				}
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 < Im)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 9;
					break;
				};
			}
			if ((A < Im)) {
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 > Ip)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 1;
					break;
				};
			}
			{
				Scores[x] = 0;
				return;
			}
			
		case 9:
			if ((A < Im)) {
				if ((B2 > Ip)) {
					Scores[x] = 0;
					return;
				}
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 > Ip)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 8;
					break;
				};
			}
			if ((A > Ip)) {
				B1 = B2;
				b++;
				B2 = I[x+dirs[b]];
				if ((B2 < Im)) {
					Scores[x] = 0;
					return;
				}
				{
					score -= A + B1;
					state = 0;
					break;
				};
			}
			{
				Scores[x] = 0;
				return;
			}
			
		default:
			//"PB default";
			break;
		} // switch(state)
	} // for(a...)
	
	Scores[x] = (score + dirs_nb * I[x]);
}




	
void yape::init(int width, int height, int radius, int pyramid_levels) {
	radius = min(radius, 7);
	radius = max(radius, 3);
	level_tables.SetCount(pyramid_levels);
	int i = 0;
	for (lev_table_t& l : level_tables) {
		l.Set(width >> i, height >> i, radius);
		ASSERT(l.dirs_count > 0);
		i++;
	}
}

int yape::detect(const ByteMat& src, Vector<keypoint_t>& points, int border) {
	lev_table_t& t = this->level_tables[0];
	int R = t.radius;
	int Rm1 = (R - 1);
	auto& dirs = t.dirs;
	int dirs_count = t.dirs_count;
	ASSERT(dirs_count > 0);
	int opposite = dirs_count >> 1;
	const auto& img = src.data;
	int w = src.cols;
	int h = src.rows;
	int hw = w >> 1;
	Vector<int>& scores = t.scores;
	//int x = 0, y = 0, row = 0, rowx = 0, ip = 0, im = 0, abs_score = 0, score = 0;
	int tau = this->tau;
	int number_of_points = 0;
	
	int sx = max(R + 1, border);
	int sy = max(R + 1, border);
	int ex = min(w - R - 2, w - border);
	int ey = min(h - R - 2, h - border);
	
	int row = (sy * w + sx);
	for (int y = sy; y < ey; ++y, row += w) {
		for (int x = sx, rowx = row; x < ex; ++x, ++rowx) {
			auto ip = min(255, img[rowx] + tau);
			auto im = max(0, img[rowx] - tau);
			
			if (im < img[rowx+R] && img[rowx+R] < ip && im < img[rowx-R] && img[rowx-R] < ip) {
				scores[rowx] = 0;
			}
			else {
				perform_one_point(img, rowx, scores, im, ip, dirs, opposite, dirs_count);
			}
		}
	}
	
	// local maxima
	row = (sy * w + sx);
	for (int y = sy; y < ey; ++y, row += w) {
		for (int x = sx, rowx = row; x < ex; ++x, ++rowx) {
			auto& score = scores[rowx];
			auto abs_score = abs(score);
			if (abs_score < 5) {
				// if this pixel is 0, the next one will not be good enough. Skip it.
				++x, ++rowx;
			}
			else if (third_check(scores, rowx, w) >= 3 && is_local_maxima(scores, rowx, score, hw, R)) {
				keypoint_t& pt = points[number_of_points];
				pt.x = x;
				pt.y = y;
				pt.score = abs_score;
				++number_of_points;
				
				x += Rm1;
				rowx += Rm1;
			}
		}
	}
	
	return number_of_points;
}


NAMESPACE_TOPSIDE_END
