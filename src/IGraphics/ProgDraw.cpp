#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN




ProgImage::ProgImage() {
	
}

void ProgImage::Paint(const DrawCommand* begin, const DrawCommand* end, ImageDraw& id) {
	draw.SetTarget(id);
	draw.Process(begin, end);
}

void ProgImage::SkipWindowCommands(bool b) {
	draw.SkipWindowCommands(b);
}


//SDLCPU_EXCPLICIT_INITIALIZE_CLASS(ProgImage)


NAMESPACE_PARALLEL_END

