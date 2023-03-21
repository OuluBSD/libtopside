#include "GuboCore.h"

NAMESPACE_TOPSIDE_BEGIN


DrawCommand3& DrawCommand3Cache::CreateCommand() {
	if (unused.IsEmpty()) {
		DrawCommand3& cmd = owned.Add();
		cmd.type = DRAW3_NULL;
		cmd.is_cached = true;
		return cmd;
	}
	DrawCommand3& cmd = *unused.Pop();
	cmd.next = NULL;
	cmd.prev = NULL;
	cmd.type = DRAW3_NULL;
	cmd.is_cached = true;
	return cmd;
}

void DrawCommand3Cache::Return(DrawCommand3* cmd) {
	unused.Add(cmd);
}



String DrawCommand3::ColorString() const {
	String s;
	s << "[";
	s << color.GetR() << ",";
	s << color.GetG() << ",";
	s << color.GetB();
	s << "]";
	return s;
}

String DrawCommand3::GetTypeString() const {
	switch (type) {
		#define DRAWCMD3(x) case DRAW3_##x: return ToLower(String(#x));
		DRAWCMD3_LIST
		#undef DRAWCMD3
		
		default: return "<invalid type>";
	}
}

String DrawCommand3::ToString() const {
	String s;
	switch (type) {
		case DRAW3_NULL:					s << "-"; break;
		//case DRAW3_SET_SIZE:				s << "set-size([" << sz.cx << "," << sz.cy << "])"; break;
		//case DRAW3_IMAGE:				s << "draw-image([" << sz.cx << "," << sz.cy << "], " << img.ToString() << ")"; break;
		//case DRAW3_CTRL_DRAW3_BEGIN:		s << "ctrl-draw-begin()"; break;
		//case DRAW3_CTRL_DRAW3_END:		s << "ctrl-draw-end()"; break;
		//case DRAW3_GET_INFO:				s << "get-info()"; break;
		//case DRAW3_GET_PAGE_SIZE:		s << "get-page-size()"; break;
		case DRAW3_START_PAGE:			s << "start-page()"; break;
		case DRAW3_END_PAGE:				s << "end-page()"; break;
		case DRAW3_BEGIN_OP:				s << "begin-op()"; break;
		case DRAW3_END_OP:				s << "end-op()"; break;
		case DRAW3_OFFSET_OP:			s << "offset-op(" << AsString(pt) << ")"; break;
		case DRAW3_CLIP_OP:				s << "clip-op(" << AsString(r) << ")"; break;
		case DRAW3_CLIPOFF_OP:			s << "clipoff-op(" << AsString(r) << ")"; break;
		case DRAW3_EXCLUDE_CLIP_OP:		s << "exclude-clip-op(" << AsString(r) << ")"; break;
		case DRAW3_INTERSECT_CLIP_OP:	s << "intersect-clip-op(" << AsString(r) << ")"; break;
		//case DRAW3_IS_PAINTING_OP:		s << "is-painting-op()"; break;
		//case DRAW3_GET_PAINT_RECT:		s << "get-paint-rect()"; break;
		case DRAW3_RECT_OP:				s << "rect-op(pt[" << pt.x << ", " << pt.y << "], sz[" << sz.cx << "," << sz.cy << "])"; break;
		case DRAW3_SYSDRAW_IMAGE_OP:		s << "sysdraw-image-op(" << AsString(pt) << ", " << AsString(img.ToString()) << ", " << AsString(r) << ", " << ColorString() << ")"; break;
		case DRAW3_IMAGE_OP:				s << "image-op(" << AsString(pt) << ", " << AsString(sz) << ", " << AsString(img.ToString()) << ", " << AsString(r) << ", " << ColorString() << ")"; break;
		case DRAW3_DATA_OP:				s << "data-op(" << AsString(pt) << ", " << AsString(sz) << ", " << txt << ", " << id << ")"; break;
		case DRAW3_LINE_OP:				s << "line-op(" << AsString(pt) << ", " << AsString(pt2) << ", " << width << ", " << ColorString() << ")"; break;
		case DRAW3_POLY_POLYLINE_OP:		s << "poly-polyline-op(vertices=" << points.GetCount() << ", width=" << width << ")"; break;
		case DRAW3_POLY_POLY_POLYGON_OP:	s << "poly-poly-polygon-op(vertices=" << points.GetCount() << ")"; break;
		case DRAW3_ARC_OP:				s << "arc-op(" << AsString(r) << ", " << AsString(pt) << ", " << AsString(pt2) << ", " << width << ")"; break;
		case DRAW3_ELLIPSE_OP:			s << "ellipse-op(" << AsString(r) << ", width=" << width << ")"; break;
		case DRAW3_TEXT_OP:				s << "text-op([" << pt.x << ", " << pt.y << "], " << txt << ")"; break;
		case DRAW3_DRAWING_OP:			s << "drawing-op(" << AsString(r) << ")"; break;
		case DRAW3_PAINTING_OP:			s << "painting-op(" << AsString(r) << ")"; break;
		//case DRAW3_GET_NATIVE_DPI:		s << "get-native-dpi()"; break;
		case DRAW3_BEGIN_NATIVE:			s << "begin-native()"; break;
		case DRAW3_END_NATIVE:			s << "end-native()"; break;
		//case DRAW3_GET_CLOFF_LEVEL:		s << "get-cloff-leve()"; break;
		case DRAW3_ESCAPE:				s << "escape(" << txt << ")"; break;
		
		#if 0
		case DRAW3_META_SIZE:		s << "meta-size([" << i[0] << "," << i[1] << "])"; break;
		case DRAW3_META_SIZE3:		s << "meta-size3([" << i[0] << "," << i[1] << "," << i[2] << "])"; break;
		case DRAW3_BEGIN:			s << "-"; break;
		case DRAW3_BIND_WINDOW:		s << "bind-window(" << HexStr(hash) << ")"; break;
		case DRAW3_UNBIND_WINDOW:	s << "unbind-window()"; break;
		case DRAW3_LINE:				s << "line([" << i[0] << "," << i[1] << "], [" << i[2] << "," << i[3] << "])"; break;
		case DRAW3_IMAGE_SIZED:		s << "image-sized([" << i[0] << "," << i[1] << "], [" << i[2] << "," << i[3] << "], " << img.ToString() << ")"; break;
		case DRAW3_IMAGEBUFFER:		s << "image-buffer([" << i[0] << "," << i[1] << ", " << i[2] << "," << i[3] << "], " << HexStr(ptr) << ")"; break;
		case DRAW3_TRIANGLES:		s << "triangles(" << (int)clr.r << ", " << (int)clr.g << ", " << (int)clr.b << ", " << (int)clr.a << ")"; break;
		case DRAW3_POLYLINE:			s << "polyline(width=" << i[0] << ", pts-count=" << pts.GetCount() << ")"; break;
		case DRAW3_CLIPOFF:			s << "clipoff(" << i[0] << "," << i[1] << ", " << i[2] << "," << i[3] << ")"; break;
		case DRAW3_OFFSET_POINT:		s << "offset-point(" << i[0] << "," << i[1] << ")"; break;
		case DRAW3_END:				s << "end()"; break;
		case DRAW3_WINDOW_OFFSET:	s << "window-offset(" << i[0] << "," << i[1] << ", " << i[2] << "," << i[3] << ")"; break;
		case DRAW3_WINDOW_END:		s << "window-end()"; break;
		case DRAW3_CUBF:				s << "rect(pt[" << i[0] << "," << i[1] << "," << i[2] << "], sz[" << i[3]-i[0] << "," << i[4]-i[1] << "," << i[5]-i[2] << "])"; break;
		#endif
		default:
			if ((int)type >= 0 && (int)type < (int)DRAW3_CMD_COUNT)
				s << "<TODO>";
			else
				s << "<invalid type>";
			break;
	}
	return s;
}

void DrawCommand3::Check() const {
	const DrawCommand3* it = this;
	int i = 0;
	while (it) {
		if (it && it->next && it->next->prev != it) {
			LOG(GetQueueString());
			Panic("DrawCommand3::Check failed");
		}
		if (it->next == this) {
			Panic("Circular command loop");
		}
		it = it->next;
		i++;
	}
}

	
String DrawCommand3::GetQueueString() const {
	String s;
	const DrawCommand3* it = this;
	int i = 0;
	while (it) {
		s << i++ << ": " << it->ToString() << "\n";
		if (it && it->next && it->next->prev != it) {
			s << "<error: iterator moved to non-reversable item>\n";
			break; // failsafe break
		}
		it = it->next;
		if (it == this)
			break;
	}
	return s;
}


NAMESPACE_TOPSIDE_END
