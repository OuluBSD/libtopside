#ifndef _Emu_Interrupts_h_
#define _Emu_Interrupts_h_



// A few defines to make life a little easier
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47



EXTERN_C_BEGIN

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the #defines above as the
// first parameter.
typedef void (*isr_t)(struct Registers);
void RegisterInterruptHandler(uint8 n, Callback1<struct Registers> handler);

// This gets called from our ASM interrupt handler stub.
void isr_handler(Registers regs);
void irq_handler(Registers regs);

void EnableInterrupts();
void DisableInterrupts();

EXTERN_C_END


#endif
