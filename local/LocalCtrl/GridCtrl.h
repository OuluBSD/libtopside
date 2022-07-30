#ifndef _LocalCtrl_GridCtrl_h_
#define _LocalCtrl_GridCtrl_h_

NAMESPACE_TOPSIDE_BEGIN


class GridCtrl : public ParentCtrl {
	int cols = 2, rows = 2;
	
public:
	typedef GridCtrl CLASSNAME;
	GridCtrl();
	
	void SetGridSize(int rows, int cols);
	void Layout() override;
	
};


NAMESPACE_TOPSIDE_END

#endif
