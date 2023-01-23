#include <Draw/Draw.h>
#include "Draw.h"


NAMESPACE_UPP


DrawCommand& DrawCommandCache::CreateCommand() {
	if (unused.IsEmpty()) {
		DrawCommand& cmd = owned.Add();
		cmd.type = 0;
		cmd.is_cached = true;
		return cmd;
	}
	DrawCommand& cmd = *unused.Pop();
	cmd.next = NULL;
	cmd.prev = NULL;
	cmd.type = 0;
	cmd.is_cached = true;
	return cmd;
}

void DrawCommandCache::Return(DrawCommand* cmd) {
	unused.Add(cmd);
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
		case DRAW_NULL:				s << "-"; break;
		case DRAW_META_SIZE:		s << "meta-size([" << i[0] << "," << i[1] << "])"; break;
		case DRAW_META_SIZE3:		s << "meta-size3([" << i[0] << "," << i[1] << "," << i[2] << "])"; break;
		case DRAW_BEGIN:			s << "-"; break;
		case DRAW_BIND_WINDOW:		s << "bind-window(" << HexStr(hash) << ")"; break;
		case DRAW_UNBIND_WINDOW:	s << "unbind-window()"; break;
		case DRAW_LINE:				s << "line([" << i[0] << "," << i[1] << "], [" << i[2] << "," << i[3] << "])"; break;
		case DRAW_IMAGE:			s << "image([" << i[0] << "," << i[1] << "], " << img.ToString() << ")"; break;
		case DRAW_RECT:				s << "rect(pt[" << i[0] << "," << i[1] << "], sz[" << i[2]-i[0] << "," << i[3]-i[1] << "])"; break;
		case DRAW_TRIANGLES:		s << "triangles(" << (int)clr.r << ", " << (int)clr.g << ", " << (int)clr.b << ", " << (int)clr.a << ")"; break;
		case DRAW_POLYLINE:			s << "polyline(width=" << i[0] << ", pts-count=" << pts.GetCount() << ")"; break;
		case DRAW_OFFSET:			s << "offset(" << i[0] << "," << i[1] << ", " << i[2] << "," << i[3] << ")"; break;
		case DRAW_END:				s << "end()"; break;
		case DRAW_WINDOW_OFFSET:	s << "window-offset(" << i[0] << "," << i[1] << ", " << i[2] << "," << i[3] << ")"; break;
		case DRAW_WINDOW_END:		s << "window-end()"; break;
		case DRAW_CUBF:				s << "rect(pt[" << i[0] << "," << i[1] << "," << i[2] << "], sz[" << i[3]-i[0] << "," << i[4]-i[1] << "," << i[5]-i[2] << "])"; break;
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
