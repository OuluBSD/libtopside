#include <gsl/gsl_multifit.h>
#include <stdbool.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

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
	#else
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
	#endif

	vector<double> result(4);
	
	for(int i = 0; i < 2; i++) {
		if (i == 0)
			polynomialfit(x.size(), 4, pix.data(), angle.data(), result.data());
		else
			polynomialfit(x.size(), 4, angle.data(), pix.data(), result.data());
		
		double a = result[0];
		double b = result[1];
		double c = result[2];
		double d = result[3];
		
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
    
    
	return 0;
}
