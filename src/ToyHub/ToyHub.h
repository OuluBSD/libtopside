#ifndef _ToyHub_ToyHub_h_
#define _ToyHub_ToyHub_h_

#ifdef LIBTOPSIDE
	#error ToyHub requires Skylark currently, which depends on U++ Core.
#endif

#include <Local/Local.h>
using namespace UPP; // sql schema requires

#include "Defs.h"
#include "Database.h"
#include "Storage.h"
#include "Session.h"
#include "Request.h"
#include "Server.h"



#endif
