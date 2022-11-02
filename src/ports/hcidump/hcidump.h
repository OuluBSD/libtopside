#ifndef _ports_hcidump_hcidump_h_
#define _ports_hcidump_hcidump_h_

#include <Local/Local.h>
#include "internal.h"
/*extern "C" {
	struct hcidump_process_data;
}*/

NAMESPACE_TOPSIDE_BEGIN

class SimpleBluetoothConnection {
	//struct hcidump_process_data* data = 0;
	struct hcidump_process_data data;
	int device_idx;
	int mode;
	int sock;
	unsigned long flags = 0;
	
	bool is_open = false;
	
public:
	SimpleBluetoothConnection();
	~SimpleBluetoothConnection();
	
	
	bool Open(int device_idx);
	void Close();
	bool IsOpen() const {return is_open;}
	
	bool ReadPacket(Vector<byte>& data);
	
	
};

NAMESPACE_TOPSIDE_END


#endif
