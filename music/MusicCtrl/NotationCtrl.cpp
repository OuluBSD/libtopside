#include "MusicCtrl.h"


NAMESPACE_TOPSIDE_BEGIN


void update_lomse_window(void* obj, lomse::SpEventInfo pEvent)
{
    NotationCtrl* c = (NotationCtrl*)obj;
	c->PostUpdate();
}

NotationCtrl::NotationCtrl() {
	m_format = lomse::k_pix_format_rgba32;
    lomse.init_library(m_format, 96);
	
	String fonts_dir = ShareDirFile("fonts" DIR_SEPS);
	if (DirectoryExists(fonts_dir))
		lomse.set_default_fonts_path(fonts_dir.ToStd());
	
}
	
void NotationCtrl::OpenDocumentLenmus(String content) {
	presenter.Clear();
	presenter = lomse.new_document(
		lomse::k_view_vertical_book,
		content.Begin(),
		lomse::Document::k_format_ldp);
	
	
    //get the pointer to the interactor and register for receiving desired events
    if (lomse::SpInteractor interactor = presenter->get_interactor(0).lock()) {
        interactor->add_event_handler(lomse::k_update_window_event, this, update_lomse_window);
    }
    
}

void NotationCtrl::Paint(Draw& d) {
	Size sz = GetSize();
	if (presenter.IsEmpty()) {
		d.DrawRect(sz, White());
		return;
	}

    if (lomse::SpInteractor interactor = presenter->get_interactor(0).lock()) {
        ImageBuffer ib(sz);
        interactor->set_rendering_buffer((unsigned char*)ib.Begin(), sz.cx, sz.cy);
        interactor->redraw_bitmap();
        d.DrawImage(0,0, ib);
    }
}

void NotationCtrl::PostUpdate() {
	PostCallback(callback(this, &Ctrl::Update));
}


NAMESPACE_TOPSIDE_END

#if defined flagFREEBSD && defined flagCLANG
extern "C" {
FILE* fopen64(const char * path, const char * mode) {return fopen(path, mode);}
int fseek64(FILE *stream, long offset, int whence) {return fseek(stream, offset, whence);}
int fseeko64(FILE *stream, off_t offset, int whence) {return fseeko(stream, offset, whence);}
off_t ftello64(FILE *stream) {return ftello(stream);}
}
#endif
