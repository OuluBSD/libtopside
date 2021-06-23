#include "TemplatesMach.h"


NAMESPACE_ECS_BEGIN

String Format::ToString() const {TODO}
TypeCls Format::GetDevSpec() const {TODO}
int Format::GetSampleSize() const {TODO}
int Format::GetArea() const {TODO}
int Format::GetFrameSize() const {TODO}
double Format::GetFrameSeconds() const {TODO}
int Format::GetMinBufSamples() const {TODO}
bool Format::IsValid() const {TODO}
bool Format::IsSame(const Format& f) const {TODO}
bool Format::IsCopyCompatible(const Format& f) const {TODO}
bool Format::operator ==(const Format& f) {TODO}
bool Format::operator !=(const Format& f) {TODO}
void Format::SetDefault(ValDevCls t) {TODO}
void Format::Clear() {TODO}



String PacketValue::ToString() const {
	String s;
	s.Cat('{');
	s << "size: " << data.GetCount();
	s << ", id: " << IntStr64(id);
	s<< ", format: {" << fmt.ToString() << "}";
	
	s.Cat('}');
	return s;
}







void ValStreamState::Clear() {
	fmt.Clear();
	sink_frame = 0;
	is_sync = 0;
	
	frame_time.Reset();
	total_seconds = 0;
	frame_seconds = 0;
	last_sync_sec = 0;
	frames = 0;
	frames_after_sync = 0;
}

void ValStreamState::Reset() {
	frame_time.Reset();
	total_seconds = 0;
	frame_seconds = 0;
	last_sync_sec = 0;
	frames = 0;
	frames_after_sync = 0;
}

void ValStreamState::Step() {
	frames++;
	frame_time.Reset();
}



#if HAVE_OPENGL

bool PacketValue::PaintOpenGLTexture(int texture) {
	TODO
}

#endif


NAMESPACE_ECS_END
