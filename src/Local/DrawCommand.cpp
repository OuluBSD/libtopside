#include <Local/Local.h>


NAMESPACE_UPP


DrawCommand& DrawCommandCache::CreateCommand() {
	if (unused.IsEmpty()) {
		DrawCommand& cmd = owned.Add();
		cmd.type = DRAW_NULL;
		cmd.is_cached = true;
		return cmd;
	}
	DrawCommand& cmd = *unused.Pop();
	cmd.next = NULL;
	cmd.prev = NULL;
	cmd.type = DRAW_NULL;
	cmd.is_cached = true;
	return cmd;
}

void DrawCommandCache::Return(DrawCommand* cmd) {
	unused.Add(cmd);
}



String DrawCommand::ColorString() const {
	String s;
	s << "[";
	s << color.GetR() << ",";
	s << color.GetG() << ",";
	s << color.GetB();
	s << "]";
	return s;
}

String DrawCommand::GetTypeString() const {
	switch (type) {
		#define DRAWCMD(x) case DRAW_##x: return ToLower(String(#x));
		DRAWCMD_LIST
		#undef DRAWCMD
		
		default: return "<invalid type>";
	}
}

String DrawCommand::ToString() const {
	String s;
	switch (type) {
		case DRAW_NULL:					s << "-"; break;
		//case DRAW_SET_SIZE:				s << "set-size([" << sz.cx << "," << sz.cy << "])"; break;
		//case DRAW_IMAGE:				s << "draw-image([" << sz.cx << "," << sz.cy << "], " << img.ToString() << ")"; break;
		//case DRAW_CTRL_DRAW_BEGIN:		s << "ctrl-draw-begin()"; break;
		//case DRAW_CTRL_DRAW_END:		s << "ctrl-draw-end()"; break;
		//case DRAW_GET_INFO:				s << "get-info()"; break;
		//case DRAW_GET_PAGE_SIZE:		s << "get-page-size()"; break;
		case DRAW_START_PAGE:			s << "start-page()"; break;
		case DRAW_END_PAGE:				s << "end-page()"; break;
		case DRAW_BEGIN_OP:				s << "begin-op()"; break;
		case DRAW_END_OP:				s << "end-op()"; break;
		case DRAW_OFFSET_OP:			s << "offset-op(" << AsString(pt) << ")"; break;
		case DRAW_CLIP_OP:				s << "clip-op(" << AsString(r) << ")"; break;
		case DRAW_CLIPOFF_OP:			s << "clipoff-op(" << AsString(r) << ")"; break;
		case DRAW_EXCLUDE_CLIP_OP:		s << "exclude-clip-op(" << AsString(r) << ")"; break;
		case DRAW_INTERSECT_CLIP_OP:	s << "intersect-clip-op(" << AsString(r) << ")"; break;
		//case DRAW_IS_PAINTING_OP:		s << "is-painting-op()"; break;
		//case DRAW_GET_PAINT_RECT:		s << "get-paint-rect()"; break;
		case DRAW_RECT_OP:				s << "rect-op(pt[" << pt.x << ", " << pt.y << "], sz[" << sz.cx << "," << sz.cy << "])"; break;
		case DRAW_SYSDRAW_IMAGE_OP:		s << "sysdraw-image-op(" << AsString(pt) << ", " << AsString(img.ToString()) << ", " << AsString(r) << ", " << ColorString() << ")"; break;
		case DRAW_IMAGE_OP:				s << "image-op(" << AsString(pt) << ", " << AsString(sz) << ", " << AsString(img.ToString()) << ", " << AsString(r) << ", " << ColorString() << ")"; break;
		case DRAW_DATA_OP:				s << "data-op(" << AsString(pt) << ", " << AsString(sz) << ", " << txt << ", " << id << ")"; break;
		case DRAW_LINE_OP:				s << "line-op(" << AsString(pt) << ", " << AsString(pt2) << ", " << width << ", " << ColorString() << ")"; break;
		case DRAW_POLY_POLYLINE_OP:		s << "poly-polyline-op(vertices=" << points.GetCount() << ", width=" << width << ")"; break;
		case DRAW_POLY_POLY_POLYGON_OP:	s << "poly-poly-polygon-op(vertices=" << points.GetCount() << ")"; break;
		case DRAW_ARC_OP:				s << "arc-op(" << AsString(r) << ", " << AsString(pt) << ", " << AsString(pt2) << ", " << width << ")"; break;
		case DRAW_ELLIPSE_OP:			s << "ellipse-op(" << AsString(r) << ", width=" << width << ")"; break;
		case DRAW_TEXT_OP:				s << "text-op([" << pt.x << ", " << pt.y << "], " << txt << ")"; break;
		case DRAW_DRAWING_OP:			s << "drawing-op(" << AsString(r) << ")"; break;
		case DRAW_PAINTING_OP:			s << "painting-op(" << AsString(r) << ")"; break;
		//case DRAW_GET_NATIVE_DPI:		s << "get-native-dpi()"; break;
		case DRAW_BEGIN_NATIVE:			s << "begin-native()"; break;
		case DRAW_END_NATIVE:			s << "end-native()"; break;
		//case DRAW_GET_CLOFF_LEVEL:		s << "get-cloff-leve()"; break;
		case DRAW_ESCAPE:				s << "escape(" << txt << ")"; break;
		
		#if 0
		case DRAW_META_SIZE:		s << "meta-size([" << i[0] << "," << i[1] << "])"; break;
		case DRAW_META_SIZE3:		s << "meta-size3([" << i[0] << "," << i[1] << "," << i[2] << "])"; break;
		case DRAW_BEGIN:			s << "-"; break;
		case DRAW_BIND_WINDOW:		s << "bind-window(" << HexStr(hash) << ")"; break;
		case DRAW_UNBIND_WINDOW:	s << "unbind-window()"; break;
		case DRAW_LINE:				s << "line([" << i[0] << "," << i[1] << "], [" << i[2] << "," << i[3] << "])"; break;
		case DRAW_IMAGE_SIZED:		s << "image-sized([" << i[0] << "," << i[1] << "], [" << i[2] << "," << i[3] << "], " << img.ToString() << ")"; break;
		case DRAW_IMAGEBUFFER:		s << "image-buffer([" << i[0] << "," << i[1] << ", " << i[2] << "," << i[3] << "], " << HexStr(ptr) << ")"; break;
		case DRAW_TRIANGLES:		s << "triangles(" << (int)clr.r << ", " << (int)clr.g << ", " << (int)clr.b << ", " << (int)clr.a << ")"; break;
		case DRAW_POLYLINE:			s << "polyline(width=" << i[0] << ", pts-count=" << pts.GetCount() << ")"; break;
		case DRAW_CLIPOFF:			s << "clipoff(" << i[0] << "," << i[1] << ", " << i[2] << "," << i[3] << ")"; break;
		case DRAW_OFFSET_POINT:		s << "offset-point(" << i[0] << "," << i[1] << ")"; break;
		case DRAW_END:				s << "end()"; break;
		case DRAW_WINDOW_OFFSET:	s << "window-offset(" << i[0] << "," << i[1] << ", " << i[2] << "," << i[3] << ")"; break;
		case DRAW_WINDOW_END:		s << "window-end()"; break;
		case DRAW_CUBF:				s << "rect(pt[" << i[0] << "," << i[1] << "," << i[2] << "], sz[" << i[3]-i[0] << "," << i[4]-i[1] << "," << i[5]-i[2] << "])"; break;
		#endif
		default:
			if ((int)type >= 0 && (int)type < (int)DRAW_CMD_COUNT)
				s << "<TODO>";
			else
				s << "<invalid type>";
			break;
	}
	return s;
}

void DrawCommand::Check() const {
	const DrawCommand* it = this;
	int i = 0;
	while (it) {
		if (it && it->next && it->next->prev != it) {
			LOG(GetQueueString());
			Panic("DrawCommand::Check failed");
		}
		if (it->next == this) {
			Panic("Circular command loop");
		}
		it = it->next;
		i++;
	}
}

	
String DrawCommand::GetQueueString() const {
	String s;
	const DrawCommand* it = this;
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


END_UPP_NAMESPACE
