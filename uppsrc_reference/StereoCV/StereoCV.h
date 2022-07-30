#ifndef _StereoCV_StereoCV_h_
#define _StereoCV_StereoCV_h_

#include <ComputerVision/ComputerVision.h>
#include <LocalCtrl/LocalCtrl.h>
#include <plugin/jpg/jpg.h>


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



class PointcloudBase : public ImageProcBase {
	
public:
	PointcloudBase();
	
	void InitDefault() override;
	void Process() override;
	
	
};


class StereoCV : public TopWindow {
	
	struct Renderer : public Ctrl {
		Image input, output;
		Vector<ColorLine>* lines = 0;
		Vector<Point>* points = 0;
		Vector<BBox>* rects = 0;
		
		void Paint(Draw& d) override;
		
	};
	
	int img_i = 0;
	int frame_i = 0;
	Renderer rend;
	
	Splitter hsplit;
	ArrayCtrl list;
	ParentCtrl demo_view;
	TimeCallback tc;
	MenuBar menu;
	int type = -1;
	
	RunningFlag flag;
	SerialServiceClient client;
	Vector<byte> tmp_data;
	Image latest_bright, latest_dark;
	Mutex lock;
	
	PointcloudBase pointcloud;
	String export_path;
	
	Image NewFrame();
	void Tick(ImageProcBase& proc);
	void TickGrayscale() {;}
	void TickBoxBlur() {;}
	void TickGaussianBlur() {;}
	void TickPyramidDown() {;}
	
	
	void MainBar(Bar& bar);
	
	void FrameDownloader();
	void GetFrame(TcpSocket& sock);
	
public:
	typedef StereoCV CLASSNAME;
	StereoCV();
	~StereoCV();
	
	enum {
		DEMO_POINTCLOUD,
		
		DEMO_COUNT
	};
	
	void OpenDemo(int i);
	String GetDemoName(int i);
	
	void Export(String path);
	void SelectDemo();
	void Data();
	
	bool ConnectDebugVideo();
	
	
};


NAMESPACE_TOPSIDE_END

#endif
