#include "Draw.h"


NAMESPACE_UPP


DrawCommand& DrawCommandCache::Get() {
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


END_UPP_NAMESPACE
