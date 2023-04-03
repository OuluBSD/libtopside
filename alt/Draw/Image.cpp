#include "Draw.h"


NAMESPACE_UPP_BEGIN



Value::Value(const Image& m) {
	Push(IMAGE_V, m);
}



Atomic Image::serial_counter;



Image::Image(const Nuller&) {
	
}

Image::Image() {
	
}

Image::Image(const Image& img) {
	*this = img;
}

Image::Image(Image&& img) {
	data = img.data;
	data_type = img.data_type;
	aux_data = img.aux_data;
	serial_id = img.serial_id;
	Chk();
	img.data = NULL;
	img.data_type = NO_DATA;
	img.aux_data = 0;
}

Image::Image(ImageDataRef* data) {
	this->data = data;
	data_type = IMAGE_DATA_REF;
	data->Inc();
}

Image::Image(RawSysImage* raw) {
	if (raw) {
		data = new ImageDataRef(raw);
		data_type = IMAGE_DATA_REF;
		serial_id = ++serial_counter;
	}
}

Image::Image(Image (*fn)()) {
	if (fn)
		*this = fn();
}

Image::Image(const Image& (*fn)()) {
	if (fn)
		*this = fn();
}

Image::~Image() {
	Clear();
}

bool Image::IsImageDataRef() const {
	return data_type == IMAGE_DATA_REF;
}

const byte* Image::GetIter(int x, int y) const {
	if (IsImageDataRef()) {
		ImageDataRef* data = GetData();
		const byte* d = data->img.GetData();
		int pitch = data->img.GetPitch();
		int stride = data->img.GetStride();
		return d + y * pitch + x * stride;
	}
	return 0;
}

String Image::ToString() const {
	String s;
	s << GetSize().ToString() << ", data=" << HexStr(data);
	return s;
}

void Image::Chk() {
	
}

void Image::Clear() {
	if (IsImageDataRef())
		GetData()->Dec();
	data = NULL;
	data_type = NO_DATA;
	aux_data = 0;
	serial_id = 0;
}

void Image::operator=(const Image& img) {
	Clear();
	data = img.data;
	data_type = img.data_type;
	aux_data = img.aux_data;
	serial_id = img.serial_id;
	Chk();
	if (IsImageDataRef())
		GetData()->Inc();
}

void Image::Set(void* data, DataType dt, int64 aux_data) {
	Clear();
	this->data = data;
	this->data_type = dt;
	this->aux_data = aux_data;
	this->serial_id = ++serial_counter;
}

void Image::SetHotSpot(Point pt) {
	if (IsImageDataRef())
		GetData()->hotspot = pt;
}

void Image::SetAuxData(int64 d) {
	aux_data = d;
}

bool Image::IsEmpty() const {
	return data_type == NO_DATA;
}

Point Image::GetHotSpot() const {
	if (IsImageDataRef())
		return GetData()->hotspot;
	return Point(0, 0);
}

void Image::CenterHotSpot() {
	if (IsImageDataRef())
		GetData()->hotspot = Point(GetWidth() / 2, GetHeight() / 2);
}

Image::ImageDataRef* Image::GetData() const {
	ASSERT(data_type == IMAGE_DATA_REF);
	if (data_type == IMAGE_DATA_REF)
		return (ImageDataRef*)data;
	return 0;
}

int Image::GetLength() const {
	if (data_type == IMAGE_DATA_REF) {
		auto* p = GetData();
		int w = p->img.GetWidth();
		int pitch = p->img.GetPitch();
		return w * pitch;
	}
	return 0;
}

int Image::GetWidth() const {
	if (data_type == IMAGE_DATA_REF)
		return GetData()->img.GetWidth();
	return 0;
}

int Image::GetHeight() const {
	if (data_type == IMAGE_DATA_REF)
		return GetData()->img.GetHeight();
	return 0;
}

Size Image::GetSize() const {
	if (data_type == IMAGE_DATA_REF) {
		auto* p = GetData();
		return Size(p->img.GetWidth(), p->img.GetHeight());
	}
	return Size(0, 0);
}

Size Image::GetResolution() const {
	if (data_type == IMAGE_DATA_REF) {
		auto* p = GetData();
		return Size(p->img.GetWidth(), p->img.GetHeight());
	}
	return Size(0, 0);
}

int Image::GetStride() const {
	if (data_type == IMAGE_DATA_REF) {
		auto* p = GetData();
		return p->img.GetStride();
	}
	return 0;
}

int Image::GetPitch() const {
	if (data_type == IMAGE_DATA_REF) {
		auto* p = GetData();
		return p->img.GetPitch();
	}
	return 0;
}

const byte* Image::Begin() const {
	return GetIter(0, 0);
}

const byte* Image::End() const {
	Size sz = GetSize();
	return GetIter(0, sz.cy);
}

Image::operator bool() const {
	return data_type != NO_DATA;
}

bool Image::IsNullInstance() const {
	return data_type == NO_DATA;
}

int32 Image::GetSerialId() const {
	return serial_id;
}

int64 Image::GetAuxData() const {
	return aux_data;
}

bool Image::IsSame(const Image& i) const {
	if (IsImageDataRef() && i.IsImageDataRef()) {
		ImageDataRef* data0 = GetData();
		ImageDataRef* data1 = i.GetData();
		if (data0 == data1)
			return true;
	}
	hash_t h0 = GetHashValue();
	hash_t h1 = i.GetHashValue();
	return h0 == h1;
}

hash_t Image::GetHashValue() const {
	const byte* it = Begin();
	const byte* end = End();
	if (it && end) {
		CombineHash c;
		while (it != end) {
			c.Put(*it++);
		}
		return c;
	}
	return 0;
}






void ImageBuffer::Create(Size sz) {
	ASSERT(sz.cx > 0 && sz.cy > 0);
	this->sz = sz;
	int area = sz.GetArea();
	buf.SetCount(area);
}

void ImageBuffer::Clear() {
	buf.SetCount(0);
}






Image RescaleFilter(const Image& img, int cx, int cy, int filter) {
	TODO
}

Image RescaleFilter(const Image& img, Size sz, Rect r, int filter) {
	TODO
}

Image CachedRescale(const Image& img, Size sz) {
	TODO
}



NAMESPACE_UPP_END

