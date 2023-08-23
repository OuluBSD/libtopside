#include "Emu.h"

EXTERN_C_BEGIN

int multiboot_main(struct multiboot *mboot_ptr);

EXTERN_C_END



#ifdef flagGUI

GUI_APP_MAIN {
	
	int ret = multiboot_main(0);
	
}

#else

CONSOLE_APP_MAIN {
	
	int ret = multiboot_main(0);
	
}

#endif
