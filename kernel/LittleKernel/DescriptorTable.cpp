#include "Kernel.h"




void DescriptorTable::Init() {
	d_ptr.limit = (sizeof(DescriptorEntry) * 5) - 1;
	d_ptr.base  = (uint32)&entries;
	
	SetGate(0, 0, 0, 0, 0);                // Null segment
	SetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	SetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	SetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	SetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	Flush();
	
	InitDescriptors();
	InitInterruptGates();
}

void DescriptorTable::SetGate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran) {
	entries[num].base_low    = (base & 0xFFFF);
	entries[num].base_middle = (base >> 16) & 0xFF;
	entries[num].base_high   = (base >> 24) & 0xFF;
	
	entries[num].limit_low   = (limit & 0xFFFF);
	entries[num].granularity = (limit >> 16) & 0x0F;
	
	entries[num].granularity |= gran & 0xF0;
	entries[num].access      = access;
}

void DescriptorTable::Flush() {
	dt_flush((uint32)&d_ptr);
}

void DescriptorTable::InitDescriptors() {
	id_ptr.limit = sizeof(InterruptGate) * 256 -1;
	id_ptr.base  = (uint32)&ig_entries;
	
	//memset(&ig_entries, 0, sizeof(InterruptGate)*256);
	
	 // Remap the irq table.
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
    
    
	InterruptSetGate( 0, (uint32)isr0 , 0x08, 0x8E);
	InterruptSetGate( 1, (uint32)isr1 , 0x08, 0x8E);
	InterruptSetGate( 2, (uint32)isr2 , 0x08, 0x8E);
	InterruptSetGate( 3, (uint32)isr3 , 0x08, 0x8E);
	InterruptSetGate( 4, (uint32)isr4 , 0x08, 0x8E);
	InterruptSetGate( 5, (uint32)isr5 , 0x08, 0x8E);
	InterruptSetGate( 6, (uint32)isr6 , 0x08, 0x8E);
	InterruptSetGate( 7, (uint32)isr7 , 0x08, 0x8E);
	InterruptSetGate( 8, (uint32)isr8 , 0x08, 0x8E);
	InterruptSetGate( 9, (uint32)isr9 , 0x08, 0x8E);
	InterruptSetGate(10, (uint32)isr10, 0x08, 0x8E);
	InterruptSetGate(11, (uint32)isr11, 0x08, 0x8E);
	InterruptSetGate(12, (uint32)isr12, 0x08, 0x8E);
	InterruptSetGate(13, (uint32)isr13, 0x08, 0x8E);
	InterruptSetGate(14, (uint32)isr14, 0x08, 0x8E);
	InterruptSetGate(15, (uint32)isr15, 0x08, 0x8E);
	InterruptSetGate(16, (uint32)isr16, 0x08, 0x8E);
	InterruptSetGate(17, (uint32)isr17, 0x08, 0x8E);
	InterruptSetGate(18, (uint32)isr18, 0x08, 0x8E);
	InterruptSetGate(19, (uint32)isr19, 0x08, 0x8E);
	InterruptSetGate(20, (uint32)isr20, 0x08, 0x8E);
	InterruptSetGate(21, (uint32)isr21, 0x08, 0x8E);
	InterruptSetGate(22, (uint32)isr22, 0x08, 0x8E);
	InterruptSetGate(23, (uint32)isr23, 0x08, 0x8E);
	InterruptSetGate(24, (uint32)isr24, 0x08, 0x8E);
	InterruptSetGate(25, (uint32)isr25, 0x08, 0x8E);
	InterruptSetGate(26, (uint32)isr26, 0x08, 0x8E);
	InterruptSetGate(27, (uint32)isr27, 0x08, 0x8E);
	InterruptSetGate(28, (uint32)isr28, 0x08, 0x8E);
	InterruptSetGate(29, (uint32)isr29, 0x08, 0x8E);
	InterruptSetGate(30, (uint32)isr30, 0x08, 0x8E);
	InterruptSetGate(31, (uint32)isr31, 0x08, 0x8E);
	
    InterruptSetGate(32, (uint32)irq0, 0x08, 0x8E);
    InterruptSetGate(33, (uint32)irq1, 0x08, 0x8E);
    InterruptSetGate(34, (uint32)irq2, 0x08, 0x8E);
    InterruptSetGate(35, (uint32)irq3, 0x08, 0x8E);
    InterruptSetGate(36, (uint32)irq4, 0x08, 0x8E);
    InterruptSetGate(37, (uint32)irq5, 0x08, 0x8E);
    InterruptSetGate(38, (uint32)irq6, 0x08, 0x8E);
    InterruptSetGate(39, (uint32)irq7, 0x08, 0x8E);
    InterruptSetGate(40, (uint32)irq8, 0x08, 0x8E);
    InterruptSetGate(41, (uint32)irq9, 0x08, 0x8E);
    InterruptSetGate(42, (uint32)irq10, 0x08, 0x8E);
    InterruptSetGate(43, (uint32)irq11, 0x08, 0x8E);
    InterruptSetGate(44, (uint32)irq12, 0x08, 0x8E);
    InterruptSetGate(45, (uint32)irq13, 0x08, 0x8E);
    InterruptSetGate(46, (uint32)irq14, 0x08, 0x8E);
    InterruptSetGate(47, (uint32)irq15, 0x08, 0x8E);
    
	InterruptFlush();
}

void DescriptorTable::InitInterruptGates() {
	
}

void DescriptorTable::InterruptSetGate(uint8 num, uint32 base, uint16 sel, uint8 flags) {
	ig_entries[num].base_lo = base & 0xFFFF;
	ig_entries[num].base_hi = (base >> 16) & 0xFFFF;
	
	ig_entries[num].sel     = sel;
	ig_entries[num].always0 = 0;
	// We must uncomment the OR below when we get to using user-mode.
	// It sets the interrupt gate's privilege level to 3.
	ig_entries[num].flags   = flags /* | 0x60 */;
}

void DescriptorTable::InterruptFlush() {
	idt_flush((uint32)&id_ptr);
}


void DescriptorTable::SetKernelStack(uint32 stack) {
    tss_entry.esp0 = stack;
}






