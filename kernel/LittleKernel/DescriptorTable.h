#ifndef DESCRIPTORTABLE_H
#define DESCRIPTORTABLE_H

#include "Common.h"
#include "Monitor.h"

extern "C" {

extern void dt_flush(uint32);
extern void idt_flush(uint32);




// These extern directives let us access the addresses of our ASM ISR handlers.
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


}

 // This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct DescriptorEntry {
   uint16 limit_low;           // The lower 16 bits of the limit.
   uint16 base_low;            // The lower 16 bits of the base.
   uint8  base_middle;         // The next 8 bits of the base.
   uint8  access;              // Access flags, determine what ring this segment can be used in.
   uint8  granularity;
   uint8  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

struct DescriptorPointer {
   uint16 limit;               // The upper 16 bits of all selector limits.
   uint32 base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));

// A struct describing an interrupt gate.
struct InterruptGate {
   uint16 base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16 sel;                 // Kernel segment selector.
   uint8  always0;             // This must always be zero.
   uint8  flags;               // More flags. See documentation.
   uint16 base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct InterruptsPointer {
   uint16 limit;
   uint32 base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));

// A struct describing a Task State Segment.
struct InterruptEntry
{
    uint32 prev_tss;   // The previous TSS - if we used hardware task switching this would form a linked list.
    uint32 esp0;       // The stack pointer to load when we change to kernel mode.
    uint32 ss0;        // The stack segment to load when we change to kernel mode.
    uint32 esp1;       // Unused...
    uint32 ss1;
    uint32 esp2;
    uint32 ss2;
    uint32 cr3;
    uint32 eip;
    uint32 eflags;
    uint32 eax;
    uint32 ecx;
    uint32 edx;
    uint32 ebx;
    uint32 esp;
    uint32 ebp;
    uint32 esi;
    uint32 edi;
    uint32 es;         // The value to load into ES when we change to kernel mode.
    uint32 cs;         // The value to load into CS when we change to kernel mode.
    uint32 ss;         // The value to load into SS when we change to kernel mode.
    uint32 ds;         // The value to load into DS when we change to kernel mode.
    uint32 fs;         // The value to load into FS when we change to kernel mode.
    uint32 gs;         // The value to load into GS when we change to kernel mode.
    uint32 ldt;        // Unused...
    uint16 trap;
    uint16 iomap_base;

} __attribute__((packed));

typedef struct tss_entry_struct tss_entry_t;

struct DescriptorTable {
	DescriptorPointer		d_ptr;
	DescriptorEntry			entries[5];
	InterruptGate			ig_entries[256];
	InterruptsPointer		id_ptr;
	InterruptEntry			tss_entry;
	
	void Init();
	void SetGate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran);
	void InterruptSetGate(uint8 num, uint32 base, uint16 sel, uint8 flags);
	void Flush();
	void InterruptFlush();
	void SetKernelStack(uint32 stack);
	
	void InitDescriptors();
	void InitInterruptGates();
	
	
};








#endif