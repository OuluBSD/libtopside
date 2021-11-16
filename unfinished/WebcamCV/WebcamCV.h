#ifndef _WebcamCV_WebcamCV_h_
#define _WebcamCV_WebcamCV_h_

#include <ComputerVision/ComputerVision.h>
#include <LocalCtrl/LocalCtrl.h>


NAMESPACE_TOPSIDE_BEGIN

struct match_t : Moveable<match_t> {
    int screen_idx;
    int pattern_lev;
    int pattern_idx;
    int distance;
    
    void Set(int screen_idx=0, int pattern_lev=0, int pattern_idx=0, int distance=0);
};




class ImageProcBase {
	
	
protected:
	ByteMat input, output, tmp0, tmp1, tmp2;
	Size sz;
	
	void OutputFromGray(const ByteMat& gray);
	void OutputFromXY(const matrix_t<int>& img_gxgy);
	void render_corners(const Vector<keypoint_t>& corners, ByteMat& img);
public:
	
	void SetInput(Image i);
	Image GetOutput() const;
	
	
	virtual void Process() = 0;
	
};


class GrayscaleBase : public ImageProcBase {
	
public:
	
	void Process() override;
	
};

class BoxBlurBase : public ImageProcBase {
	int radius = 3;
	
public:
	
	void SetRadius(int i) {ASSERT(i >= 1 && i <= 21); radius = i;}
	
	void Process() override;
	
};

class GaussianBlurBase : public ImageProcBase {
	int radius = 3;
	double sigma = 0;
	
public:
	
	void SetRadius(int i) {ASSERT(i >= 1 && i <= 11); radius = i;}
	void SetSigma(double d) {ASSERT(d >= 0 && d <= 10); sigma = d;}
	
	void Process() override;
	
};

class PyramidDownsampleBase : public ImageProcBase {
	Pyramid<byte> img_pyr;
	
public:
	
	void render_mono_image(const Vector<byte>& src, ByteMat& dst, int sw, int sh, int xoff, int dw);
	
	void Process() override;
	
};

class ScharrBase : public ImageProcBase {
	matrix_t<int> img_gxgy; // 2ch
	
public:
	
	void Process() override;
	
};

class SobelBase : public ImageProcBase {
	matrix_t<int> img_gxgy; // 2ch
	
public:
	
	void Process() override;
	
};

class SobelEdgeBase : public ImageProcBase {
	matrix_t<int> img_gxgy; // 2ch
	matrix_t<int> img_mag; // 1ch
	
public:
	
	void Process() override;
	
};

class EqualizeHistBase : public ImageProcBase {
	
public:
	
	void Process() override;
	
};

class CannyEdgeBase : public ImageProcBase {
	int blur_radius = 2;
	int low_threshold = 20;
	int high_threshold = 50;
	
public:
	
	void SetRadius(int i) {blur_radius = i; Chk();}
	void SetLowTreshold(int i) {low_threshold = i; Chk();}
	void SetHighTreshold(int i) {high_threshold = i; Chk();}
	void Chk() {ASSERT(blur_radius >= 0 && blur_radius <= 4); ASSERT(low_threshold >= 1 && low_threshold <= 127); ASSERT(high_threshold >= 1 && high_threshold <= 127);}
	
	void Process() override;
	
};

class WarpAffineBase : public ImageProcBase {
	matrix_t<float> mat_affine; // 1ch
	
public:
	WarpAffineBase();
	
	void Process() override;
	
};

class WarpPerspectiveBase : public ImageProcBase {
	matrix_t<float> transform; // 1ch
	
public:
	WarpPerspectiveBase();
	
	void Process() override;
	
};

class VideoStabilizerBase : public ImageProcBase {
	/*
	var videoWidth=0, videoHeight=0;
    var canvasWidth=0, canvasHeight=0;
    var ctx;
    var stabilizer, frame_grabber, motion_estimator;
    var frameSize = new videostab.size_t(videoWidth, videoHeight);

    var render_gl, tex0, tex1;

    var video = document.getElementById('webcam');
    var canvas = document.getElementById('canvas');
    var canvas_gl = document.getElementById('webgl');
    var stat_div = document.getElementById('log');

    var stat = new profiler();
    
    
	var gui,options,ctx,canvasWidth,canvasHeight;
	var img_u8, img_u8_smooth, screen_corners, num_corners;
	var pattern_corners, pattern_preview;
	var matches, homo3x3, match_mask;
    */
    onepass_stabilizer stabilizer;
    Vector<keypoint_t> corners;
    
    void videOK(int videoWidth, int videoHeight);
    void processGL();
    void tCorners(const Vector<float>& M, int w, int h);
    
public:
	VideoStabilizerBase();
	
	void Init();
    void Process() override;
	
	struct OglRenderer {
		int width, height;
		GLuint gl; // context
		Vector<float> worldMatrxi;
		
		#if 0
		void renderGL(int w, int h, view);
		void render();
		void initShaders();
		uint32 getShader(gl, id);
		uint32 createAndSetupTexture();
		void setRectangle(x, y, width, height);
		void setCorners(tlx, tly, trx, _try, brx, bry, blx, bly);
		void render_images(tex_id0, tex_id1, image0, image1, w, h, p);
		#endif
	};
	
};

class FastCornersBase : public ImageProcBase {
	int threshold = 20;
	
	Vector<keypoint_t> corners;
	Size sz;
	fast_corners c;
	
	
public:
	
	void SetSize(Size sz);
	void SetTreshold(int i) {threshold = i; ASSERT(i >= 5 && i <= 100);}
	
	void Process() override;
	
};

class Yape06Base : public ImageProcBase {
	int lap_thres = 30;
	int eigen_thres = 25;
	
	Vector<keypoint_t> corners;
	yape06 y;
	
public:
	
	void SetSize(Size sz);
	void SetTresholdLaplacian(int i) {lap_thres = i; ASSERT(i >= 1 && i <= 100);}
	void SetTresholdEigen(int i) {eigen_thres = i; ASSERT(i >= 1 && i <= 100);}
	
	void Process() override;
	
};

class YapeBase : public ImageProcBase {
	
	Vector<keypoint_t> corners;
	yape	y;
	
	
public:
	
	void SetSize(Size sz);
	
	void Process() override;
	
};

class OrbBase : public ImageProcBase {
    matrix_t<byte> lev0_img;
    matrix_t<byte> lev_img;
    matrix_t<byte> pattern_preview;
    matrix_t<byte> screen_descriptors;
    matrix_t<byte> match_mask;
    matrix_t<float> homo3x3;
    Vector<keypoint_t> screen_corners;
    
    Vector<Vector<keypoint_t>> pattern_corners;
    Vector<matrix_t<byte>> pattern_descriptors;
    Vector<keypoint_t> lev_corners, lev_descr;
    Vector<keypoint_t> corners, pattern_xy, screen_xy;
    Vector<match_t> matches;
	int num_train_levels = 4;
	Orb o;
	yape06 y;
    homography2d mm_kernel;
    ransac_params_t ransac_param;
    motion_estimator<homography2d> mot;
    
    int blur_size = 5;
    int lap_thres = 30;
    int eigen_thres = 25;
    int match_threshold = 48;
    
public:
	static const int u_max[];
	
    void train_pattern();
	void SetSize(Size sz);
	int detect_keypoints(const ByteMat& img, Vector<keypoint_t>& corners, int max_allowed);
    double ic_angle(const ByteMat& img, int px, int py);
    int find_transform(Vector<match_t>& matches);
    int match_pattern();
    void tCorners(const Vector<float>& M, int w, int h);
    
	void Process() override;
	
};

class OpticalFlowLKBase : public ImageProcBase {
	int win_size = 20;
	int max_iterations = 30;
	int point_count = 0;
	double epsilon = 0.01;
	double min_eigen = 0.001;
	pyra8 curr_img_pyr, prev_img_pyr;
	Vector<byte> point_status;
	Vector<float> curr_xy, prev_xy;
	optical_flow_lk of;
	
public:
	
	void SetSize(Size sz);
	void SetWinSize(int i) {win_size = i; ASSERT(win_size >= 7 && win_size <= 30);}
	void SetMaxIters(int i) {max_iterations = i; ASSERT(max_iterations >= 3 && max_iterations <= 30);}
	void SetEpsilon(double d) {epsilon = d; ASSERT(epsilon >= 0.001 && epsilon <= 0.1);}
	void SetMinEigen(double d) {min_eigen = d; ASSERT(min_eigen >= 0.001 && min_eigen <= 0.01);}
	
	void on_canvas_click();
	void draw_circle(int x, int y);
	void prune_oflow_points();
	Point relMouseCoords();
	
	void Process() override;
	
};

class BbfFaceBase : public ImageProcBase {
	static const int max_work_size = 160;
	
	BrightnessBinaryFeature b;
	pyra8 pyr;
	Vector<BBox> rects, result_seq;
	Cascade cascade;
	
public:
	BbfFaceBase();
	void SetSize(Size sz);
	void draw_faces(Vector<BBox>& rects, double sc, bool max);
	
	void Process() override;
	
};

class HaarFaceBase : public ImageProcBase {
	static const int max_work_size = 160;
	
	int min_scale = 2;
	double scale_factor = 1.15;
	bool use_canny = false;
	double edges_density = 0.13;
	bool is_equalize_histogram = true;
	Vector<int> ii_sum;
	Vector<int> ii_sqsum;
	Vector<int> ii_tilted;
	Vector<int> ii_canny;
	Vector<BBox> rects, result_seq;
	ComplexCascade classifier;
	haar h;
	
public:
	HaarFaceBase();
	void SetSize(Size sz);
	void draw_faces(Vector<BBox>& rects, double sc, bool max);
	
	void Process() override;
	
	
};

class WebcamCV : public TopWindow {
	
	struct Renderer : public Ctrl {
		Image input, output;
		
		void Paint(Draw& d) override;
		
	};
	
	Vector<Image> imgs, new_imgs;
	int img_i = 0;
	Renderer rend;
	
	Splitter hsplit;
	ArrayCtrl list;
	ParentCtrl demo_view;
	TimeCallback tc;
	MenuBar menu;
	int type = -1;
	

	GrayscaleBase grayscale;
	BoxBlurBase boxblur;
	GaussianBlurBase gaussblur;
    PyramidDownsampleBase pyrdown;
	ScharrBase scharr;
	SobelBase sobel;
	SobelEdgeBase sobeledge;
	EqualizeHistBase eqhist;
	CannyEdgeBase canny;
	WarpAffineBase warpaff;
	WarpPerspectiveBase warppers;
	VideoStabilizerBase vidstab;
	FastCornersBase fastcor;
	Yape06Base yape06;
	YapeBase yape;
	OrbBase orb;
	OpticalFlowLKBase optflowlk;
	BbfFaceBase bbf;
	HaarFaceBase haar;
	
	Image NewFrame();
	void Tick(ImageProcBase& proc);
	void TickGrayscale() {;}
	void TickBoxBlur() {;}
	void TickGaussianBlur() {;}
	void TickPyramidDown() {;}
	
	
	void MainBar(Bar& bar);
	
public:
	typedef WebcamCV CLASSNAME;
	WebcamCV();
	~WebcamCV();
	
	enum {
		DEMO_GRAYSCALE,
		DEMO_BOXBLUR,
		DEMO_GAUSSIANBLUR,
		DEMO_PYRDOWN,
		DEMO_SCHARR,
		DEMO_SOBEL,
		DEMO_SOBELEDGE,
		DEMO_EQHIST,
		DEMO_CANNY,
		DEMO_WARPAFF,
		DEMO_WARPPERS,
		DEMO_VIDSTAB,
		DEMO_FASTCOR,
		DEMO_YAPE06,
		DEMO_YAPE,
		DEMO_ORB,
		DEMO_OPTFLOWLK,
		DEMO_BBF,
		DEMO_HAAR,
		
		DEMO_COUNT
	};
	
	void OpenDemo(int i);
	String GetDemoName(int i);
	
	void LoadImageSeries(String dir);
	void OpenFile();
	void OpenVideoCapture(int dev, int cap, int fmt, int res);
	void CloseInput();
	void SelectDemo();
	void Data();
	
	
};


NAMESPACE_TOPSIDE_END

#endif
