#include "Task.h"



BEGIN_TEXTLIB_NAMESPACE


void AiTask::Process_CreateImage() {
	WhenResultImages(recv_images);
}

void AiTask::Process_EditImage() {
	WhenResultImages(recv_images);
}

void AiTask::Process_VariateImage() {
	WhenResultImages(recv_images);
}

void AiTask::Process_Default() {
	WhenResult(tmp_str + output);
}


END_TEXTLIB_NAMESPACE

