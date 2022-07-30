#include <gsl/gsl_multifit.h>
#include <stdbool.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <Geometry/Geometry.h>
using namespace UPP;

bool polynomialfit(int obs, int degree,
				   double *dx, double *dy, double *store) { /* n, p */
	gsl_multifit_linear_workspace *ws;
	gsl_matrix *cov, *X;
	gsl_vector *y, *c;
	double chisq;
	
	int i, j;
	
	X = gsl_matrix_alloc(obs, degree);
	y = gsl_vector_alloc(obs);
	c = gsl_vector_alloc(degree);
	cov = gsl_matrix_alloc(degree, degree);
	
	for (i = 0; i < obs; i++) {
		for (j = 0; j < degree; j++) {
			gsl_matrix_set(X, i, j, pow(dx[i], j));
		}
		gsl_vector_set(y, i, dy[i]);
	}
	
	ws = gsl_multifit_linear_alloc(obs, degree);
	gsl_multifit_linear(X, y, c, cov, &chisq, ws);
	
	/* store result ... */
	for (i = 0; i < degree; i++) {
		store[i] = gsl_vector_get(c, i);
	}
	
	gsl_multifit_linear_free(ws);
	gsl_matrix_free(X);
	gsl_matrix_free(cov);
	gsl_vector_free(y);
	gsl_vector_free(c);
	return true; /* we do not "analyse" the result (cov matrix mainly)
		  to know if the fit is "good" */
}

int CalcLens() {
	using namespace std;
	
	#if 0
	vector<double> x(11);
	iota(x.begin(), x.end(), 0);
	
	vector<double> y { 1, 6, 17, 34, 57, 86, 121, 162, 209, 262, 321 };
	#elif 0
	// Generic stereo fisheye lens camera from ebay
	double z = 0.40;
	vector<double> x(17), pix(17), angle(17);
	x[0] = 0.08;      pix[0] = 159;
	x[1] = 0.13;      pix[1] = 255;
	x[2] = 0.18;      pix[2] = 329;
	x[3] = 0.23;      pix[3] = 402;
	x[4] = 0.28;      pix[4] = 468;
	x[5] = 0.33;      pix[5] = 524;
	x[6] = 0.38;      pix[6] = 576;
	x[7] = 0.48;      pix[7] = 662;
	x[8] = 0.58;      pix[8] = 720;
	x[9] = 0.68;      pix[9] = 771;
	x[10] = 0.78;     pix[10] = 806;
	x[11] = 0.88;     pix[11] = 834;
	x[12] = 0.98;     pix[12] = 864;
	x[13] = 1.08;     pix[13] = 884;
	x[14] = 1.18;     pix[14] = 902;
	x[15] = 1.28;     pix[15] = 914;
	x[16] = 1.38;     pix[16] = 930;
	for(int i = 0; i < x.size(); i++) {
		angle[i] = atan2(x[i], z);// / M_PI * 180;
	}
	#else
	// WMR lenses
	double z = 0.30;
	vector<double> x(5), pix(5), angle(5);
	x[0] = 0.1;      pix[0] = 84;
	x[1] = 0.2;      pix[1] = 163;
	x[2] = 0.3;      pix[2] = 233;
	x[3] = 0.4;      pix[3] = 290;
	x[4] = 0.5;      pix[4] = 333;
	for(int i = 0; i < x.size(); i++) {
		angle[i] = atan2(x[i], z);// / M_PI * 180;
	}
	#endif

	vector<double> result(4);
	
	double pix_to_angle[4];
	
	for(int i = 0; i < 2; i++) {
		if (i == 0)
			polynomialfit(x.size(), 4, pix.data(), angle.data(), result.data());
		else
			polynomialfit(x.size(), 4, angle.data(), pix.data(), result.data());
		
		double a = result[0];
		double b = result[1];
		double c = result[2];
		double d = result[3];
		
		if (i == 0) {
			for(int j = 0; j < 4; j++)
				pix_to_angle[j] = result[j];
		}
		
		auto abc = [a, b, c, d](double xx) {
	        return a + b * xx + c * xx*xx + d * xx*xx*xx;
	    };
	    
		std::cout << "y = " << a << " + " << b << "x + " << c << "x^2 + " << d << "x^3" << std::endl;
	    std::cout << " Input  Approximation" << std::endl;
	    std::cout << " x    y      y1    angle" << std::endl;
	 
	    auto xit = pix.cbegin();
	    auto xend = pix.cend();
	    auto yit = angle.cbegin();
	    auto yend = angle.cend();
	    while (xit != xend && yit != yend) {
	        double r;
	        if (i == 0) {
	            r = abc(*xit);
				double angle = r / M_PI * 180;
				printf("%2.1f %3.2f  %5.3f %3.1f\n", *xit, *yit, r, angle);
	        }
	        else {
	            double angle = *yit / M_PI * 180;
	            r = abc(*yit);
				printf("%2.1f %3.2f  %5.3f %3.1f\n", *yit, *xit, r, angle);
	        }
	        xit = std::next(xit);
	        yit = std::next(yit);
	    }
		
	}
    
    
    {
        // Fixed real world point in image
	    // Distance of the point 70cm
	    // Eye-distance 12cm
	    Size res(640, 481);
        Point l(480,180); // pixel coordinate of real world fixed point
		Point r(180,180);
		
		Point ct(res.cx / 2, res.cy / 2);
		Point l2 = l - ct;
		Point r2 = r - ct;
		l2.y *= -1;
		r2.y *= -1;
		vec2 lv(l.x, res.cy - l.y);
		vec2 rv(r.x, res.cy - r.y);
		DUMP(l2);
		DUMP(r2);
		
		auto p2a = [pix_to_angle](double xx) {
	        return pix_to_angle[0] + pix_to_angle[1] * xx + pix_to_angle[2] * xx*xx + pix_to_angle[3] * xx*xx*xx;
	    };
	    
	    double l_len = sqrt(l2.x * l2.x + l2.y * l2.y);
	    double r_len = sqrt(r2.x * r2.x + r2.y * r2.y);
	    double l_angle = p2a(l_len);
	    double r_angle = p2a(r_len);
	    DUMP(l_angle);
	    DUMP(r_angle);
	    
	    double l_roll_angle = atan2(l2.x, l2.y);
	    double r_roll_angle = atan2(r2.x, r2.y);
	    DUMP(l_roll_angle / M_PI * 180);
	    DUMP(r_roll_angle / M_PI * 180);
	    
	    LensPoly lp;
	    lp.SetSize(res);
	    lp.SetAnglePixel(result[0], result[1], result[2], result[3]);
	    lp.MakePixelToAngle();
	    axes2 ct_ax = lp.Unproject(vec2(res.cx / 2, res.cy / 2));
	    axes2 l_ax = lp.Unproject(lv);
	    axes2 r_ax = lp.Unproject(rv);
	    //DUMP(ct_ax);
	    //DUMP(ct_ax / M_PI * 180);
	    DUMP(l_ax);
	    DUMP(r_ax);
	    DUMP(l_ax / M_PI * 180);
	    DUMP(r_ax / M_PI * 180);
	    
		// default angle from 0.06 x 0.7
		float angle = atan2(0.06, 0.7);
		DUMP(angle / M_PI * 180);
		
		// sum yaw diff and /2
		float camera_angle_sum = r_ax[0] - l_ax[0];
		float camera_angle = camera_angle_sum - 2 * angle;
		float lens_angle = camera_angle / 2;
	    DUMP(camera_angle_sum / M_PI * 180);
	    DUMP(camera_angle / M_PI * 180);
	    DUMP(lens_angle / M_PI * 180);
	    
	    LOG("Single wmr lens is tilted outwards (to left or right) " << lens_angle / M_PI * 180 << " degrees");
    }
    
	return 0;
}
