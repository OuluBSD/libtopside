
#if 0

class SImageDraw2 : public SImageDraw1 {
public:
	ImageBuffer& GetBuffer() {return this->ib;}
	const ImageBuffer& GetBuffer() const {return this->ib;}
};

class PubSystemDraw : public SImageDraw2 {
	SImageDraw2 alpha;
	bool has_alpha;
	
public:
	PubSystemDraw();
	PubSystemDraw(Size sz);
	PubSystemDraw(int cx, int cy);
	
	void Resize(Size sz);
	
	operator Image() const;
	
	Size GetSize() const;
	
};

#endif
