#ifndef _Local_Defs_h_
#define _Local_Defs_h_


#define CHKLOGRET0(x, y) if (!(x)) {LOG(y); return false;}
#define CHKLOGRET1(x, y) if (!(x)) {LOG(y); return true;}


#endif
