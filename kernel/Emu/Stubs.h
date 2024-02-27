#ifndef _Emu_Stubs_h_
#define _Emu_Stubs_h_


#define TODO Panic("TODO");


EXTERN_C_BEGIN



struct multiboot {
	size_t flags = 0;
	size_t mem_lower = 0;
	size_t mem_upper = 0;
	size_t boot_device = 0;
	size_t cmdline = 0;
	size_t mods_count = 0;
	size_t mods_addr = 0;
	size_t num = 0;
	size_t size = 0;
	size_t addr = 0;
	size_t shndx = 0;
	size_t mmap_length = 0;
	size_t mmap_addr = 0;
	size_t drives_length = 0;
	size_t drives_addr = 0;
	size_t config_table = 0;
	size_t boot_loader_name = 0;
	size_t apm_table = 0;
	size_t vbe_control_info = 0;
	size_t vbe_mode_info = 0;
	size_t vbe_mode = 0;
	size_t vbe_interface_seg = 0;
	size_t vbe_interface_off = 0;
	size_t vbe_interface_len = 0;
	
	
	Callback OnMonitorCreate;
	
};





EXTERN_C_END


#endif
