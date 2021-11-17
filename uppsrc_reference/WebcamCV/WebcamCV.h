#ifndef _WebcamCV_WebcamCV_h_
#define _WebcamCV_WebcamCV_h_

#include <ComputerVision/ComputerVision.h>
#include <LocalCtrl/LocalCtrl.h>


NAMESPACE_TOPSIDE_BEGIN


class ImageProcBase {
	
	
protected:
	ByteMat input, output, tmp0, tmp1, tmp2, train_img;
	Size sz;
	
	void OutputFromGray(const ByteMat& gray);
	void OutputFromXY(const DMatrix<int>& img_gxgy);
	void RenderCorners(const Vector<Keypoint>& corners, ByteMat& img);
	void RenderCorners(const ByteMat& bg, const ByteMat* mini_img, const Vector<Keypoint>& corners, ByteMat& img);
	
public:
	Vector<ColorLine> lines;
	Vector<Point> points;
	Vector<BBox> rects;
	
	void SetInput(Image i);
	Image GetOutput() const;
	
	
	virtual void InitDefault() {}
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
	DMatrix<int> img_gxgy; // 2ch
	
public:
	
	void Process() override;
	
};

class SobelBase : public ImageProcBase {
	DMatrix<int> img_gxgy; // 2ch
	
public:
	
	void Process() override;
	
};

class SobelEdgeBase : public ImageProcBase {
	DMatrix<int> img_gxgy; // 2ch
	DMatrix<int> img_mag; // 1ch
	
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
	DMatrix<float> mat_affine; // 1ch
	
public:
	WarpAffineBase();
	
	void Process() override;
	
};

class WarpPerspectiveBase : public ImageProcBase {
	DMatrix<float> transform; // 1ch
	
public:
	WarpPerspectiveBase();
	
	void Process() override;
	
};

class VideoStabilizerBase : public ImageProcBase {
    OnepassStabilizer stabilizer;
    Vector<Keypoint> corners;
    
    void TCorners(const Vector<float>& M, int w, int h);
    
public:
	VideoStabilizerBase();
	
	void Init();
    void Process() override;
    void InitDefault() override;
	
};

class FastCornersBase : public ImageProcBase {
	int threshold = 20;
	
	Vector<Keypoint> corners;
	Size sz;
	FastCorners c;
	
	
public:
	
	void SetSize(Size sz);
	void SetTreshold(int i) {threshold = i; ASSERT(i >= 5 && i <= 100);}
	
	void Process() override;
	
};

class Yape06Base : public ImageProcBase {
	int lap_thres = 30;
	int eigen_thres = 25;
	
	Vector<Keypoint> corners;
	Yape06 y;
	
public:
	
	void SetSize(Size sz);
	void SetTresholdLaplacian(int i) {lap_thres = i; ASSERT(i >= 1 && i <= 100);}
	void SetTresholdEigen(int i) {eigen_thres = i; ASSERT(i >= 1 && i <= 100);}
	
	void Process() override;
	
};

class YapeBase : public ImageProcBase {
	
	Vector<Keypoint> corners;
	Yape y;
	
	
public:
	
	void InitDefault() override;
	void Process() override;
	
};

class OrbBase : public ImageProcBase {
    DMatrix<byte> lev0_img;
    DMatrix<byte> lev_img;
    DMatrix<byte> pattern_preview;
    DMatrix<byte> match_mask;
    DMatrix<byte> train_img;
    DMatrix<float> homo3x3;
    Vector<Keypoint> screen_corners;
    
    Vector<BinDescriptor> screen_descriptors;
    Vector<Vector<BinDescriptor>> pattern_descriptors;
    
    Vector<Vector<Keypoint>> pattern_corners;
    Vector<Keypoint> lev_corners, lev_descr;
    Vector<Keypoint> corners, pattern_xy, screen_xy;
    Vector<KeypointMatch> matches;
	int num_train_levels = 4;
	Orb o;
	Yape06 y;
    Homography2D mm_kernel;
    RansacParams ransac_param;
    MotionEstimator<Homography2D> mot;
    
    int blur_size = 5;
    int lap_thres = 30;
    int eigen_thres = 25;
    int KeypointMatchhreshold = 48;
    
    
    void render_matches(const Vector<KeypointMatch>& matches);
    void render_pattern_shape();
    
public:
	static const int u_max[];
	
    void TrainPattern();
	int DetectKeypoints(const ByteMat& img, Vector<Keypoint>& corners, int max_allowed);
    double IcAngle(const ByteMat& img, int px, int py);
    int FindTransform(Vector<KeypointMatch>& matches);
    int MatchPattern();
    void TCorners(const Vector<float>& M, int w, int h);
    
	void InitDefault() override;
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
	OpticalFlowLK of;
	
	void MakeRandomPoints();
public:
	
	void SetWinSize(int i) {win_size = i; ASSERT(win_size >= 7 && win_size <= 30);}
	void SetMaxIters(int i) {max_iterations = i; ASSERT(max_iterations >= 3 && max_iterations <= 30);}
	void SetEpsilon(double d) {epsilon = d; ASSERT(epsilon >= 0.001 && epsilon <= 0.1);}
	void SetMinEigen(double d) {min_eigen = d; ASSERT(min_eigen >= 0.001 && min_eigen <= 0.01);}
	
	void PruneOverflowPoints();
	
	void InitDefault() override;
	void Process() override;
	
};

class BbfFaceBase : public ImageProcBase {
	static const int max_work_size = 160;
	
	BrightnessBinaryFeature b;
	pyra8 pyr;
	Vector<BBox> detected_rects;
	Cascade cascade;
	
public:
	BbfFaceBase();
	
	void InitDefault() override;
	void Process() override;
	
};

class HaarFaceBase : public ImageProcBase {
	static const int max_work_size = 160;
	
	int min_scale = 2;
	double scale_factor = 1.15;
	bool use_canny = false;
	double edges_density = 0.13;
	bool is_EqualizeHistogram = true;
	Vector<int> ii_sum;
	Vector<int> ii_sqsum;
	Vector<int> ii_tilted;
	Vector<int> ii_canny;
	Vector<BBox> detected_rects;
	ComplexCascade classifier;
	Haar h;
	
public:
	HaarFaceBase();
	
	void InitDefault() override;
	void Process() override;
	
	
};

class WebcamCV : public TopWindow {
	
	struct Renderer : public Ctrl {
		Image input, output;
		Vector<ColorLine>* lines = 0;
		Vector<Point>* points = 0;
		Vector<BBox>* rects = 0;
		
		void Paint(Draw& d) override;
		
	};
	
	Vector<Image> imgs, new_imgs;
	int img_i = 0;
	int frame_i = 0;
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
	Yape06Base Yape06;
	YapeBase Yape;
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
	void SelectDemo();
	void Data();
	
	
};


NAMESPACE_TOPSIDE_END

#endif
