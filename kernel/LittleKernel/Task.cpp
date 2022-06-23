#include "Kernel.h"


void InitialiseTasking() {
	// Rather important stuff happening, no interrupts please!
	asm volatile("cli");
	
	
	// Relocate the stack so we know where it is.
	MoveStack((void*)0xE0000000, 0x2000);
	
	// Initialise the first task (kernel task)
	auto& ready_queue = global->ready_queue;
	auto& current_task = global->current_task;
	current_task = ready_queue = (Task*)KMemoryAllocate(sizeof(Task));
	
	current_task->id = global->next_pid++;
	current_task->esp = current_task->ebp = 0;
	current_task->eip = 0;
	current_task->page_directory = global->current_directory;
	current_task->next = 0;
	current_task->kernel_stack = KMemoryAllocateAligned(KERNEL_STACK_SIZE);
	
	// Reenable interrupts.
	asm volatile("sti");
}

void MoveStack(void *new_stack_start, uint32 size) {
	uint32 i;
	// Allocate some space for the new stack.
	for (i = (uint32)new_stack_start;
		 i >= ((uint32)new_stack_start - size);
		 i -= 0x1000) {
		KDUMPH(global->current_directory);
		// General-purpose stack is in user-mode.
		AllocFrame(GetPage(i, 1, global->current_directory), 0 /* User mode */, 1 /* Is writable */);
	}
	
	// Flush the TLB by reading and writing the page directory address again.
	uint32 pd_addr;
	asm volatile("mov %%cr3, %0" : "=r"(pd_addr));
	asm volatile("mov %0, %%cr3" : : "r"(pd_addr));

	// Old ESP and EBP, read from registers.
	uint32 old_stack_pointer;
	asm volatile("mov %%esp, %0" : "=r"(old_stack_pointer));
	uint32 old_base_pointer;
	asm volatile("mov %%ebp, %0" : "=r"(old_base_pointer));

	// Offset to add to old stack addresses to get a new stack address.
	uint32 offset            = (uint32)new_stack_start - global->initial_esp;
	
	// New ESP and EBP.
	uint32 new_stack_pointer = old_stack_pointer + offset;
	uint32 new_base_pointer  = old_base_pointer  + offset;
	
	// Copy the stack.
	memcpy((void*)new_stack_pointer, (void*)old_stack_pointer, global->initial_esp - old_stack_pointer);
	
	// Backtrace through the original stack, copying new values into
	// the new stack.
	for (i = (uint32)new_stack_start; i > (uint32)new_stack_start - size; i -= 4) {
		uint32 tmp = * (uint32*)i;
		// If the value of tmp is inside the range of the old stack, assume it is a base pointer
		// and remap it. This will unfortunately remap ANY value in this range, whether they are
		// base pointers or not.
		if ((old_stack_pointer < tmp) && (tmp < global->initial_esp)) {
			tmp = tmp + offset;
			uint32 *tmp2 = (uint32*)i;
			*tmp2 = tmp;
		}
	}
	
	// Change stacks.
	asm volatile("mov %0, %%esp" : : "r"(new_stack_pointer));
	asm volatile("mov %0, %%ebp" : : "r"(new_base_pointer));
}

void switch_task() {
	auto& current_task = global->current_task;
	auto& ready_queue = global->ready_queue;
	auto& current_directory = global->current_directory;
	
	// If we haven't initialised tasking yet, just return.
	if (!current_task)
		return;
		
	// Read esp, ebp now for saving later on.
	uint32 esp, ebp, eip;
	asm volatile("mov %%esp, %0" : "=r"(esp));
	asm volatile("mov %%ebp, %0" : "=r"(ebp));

	// Read the instruction pointer. We do some cunning logic here:
	// One of two things could have happened when this function exits -
	//   (a) We called the function and it returned the EIP as requested.
	//   (b) We have just switched tasks, and because the saved EIP is essentially
	//       the instruction after read_eip(), it will seem as if read_eip has just
	//       returned.
	// In the second case we need to return immediately. To detect it we put a dummy
	// value in EAX further down at the end of this function. As C returns values in EAX,
	// it will look like the return value is this dummy value! (0x12345).
	eip = read_eip();
	
	// Have we just switched tasks?
	if (eip == 0x12345)
		return;
		
	// No, we didn't switch tasks. Let's save some register values and switch.
	current_task->eip = eip;
	current_task->esp = esp;
	current_task->ebp = ebp;
	
	// Get the next task to run.
	current_task = current_task->next;
	// If we fell off the end of the linked list start again at the beginning.
	if (!current_task)
		current_task = ready_queue;
		
	eip = current_task->eip;
	esp = current_task->esp;
	ebp = current_task->ebp;
	
	// Make sure the memory manager knows we've changed page directory.
	current_directory = current_task->page_directory;
	
	// Change our kernel stack over.
	global->dt.SetKernelStack(current_task->kernel_stack + KERNEL_STACK_SIZE);
	
	// Here we:
	// * Stop interrupts so we don't get interrupted.
	// * Temporarily put the new EIP location in ECX.
	// * Load the stack and base pointers from the new task struct.
	// * Change page directory to the physical address (physicalAddr) of the new directory.
	// * Put a dummy value (0x12345) in EAX so that above we can recognise that we've just
	//   switched task.
	// * Restart interrupts. The STI instruction has a delay - it doesn't take effect until after
	//   the next instruction.
	// * Jump to the location in ECX (remember we put the new EIP in there).
	asm volatile("         \
				 cli;                 \
				 mov %0, %%ecx;       \
				 mov %1, %%esp;       \
				 mov %2, %%ebp;       \
				 mov %3, %%cr3;       \
				 mov $0x12345, %%eax; \
				 sti;                 \
				 jmp *%%ecx           "
			 : : "r"(eip), "r"(esp), "r"(ebp), "r"(current_directory->physical_addr));
}

int Fork() {
	auto& current_task = global->current_task;
	auto& current_directory = global->current_directory;
	auto& next_pid = global->next_pid;
	auto& ready_queue = global->ready_queue;
	
	// We are modifying kernel structures, and so cannot be interrupted.
	asm volatile("cli");
	
	// Take a pointer to this process' task struct for later reference.
	Task *parent_task = (Task*)current_task;
	
	// Clone the address space.
	PageDirectory *directory = CloneDirectory(current_directory);
	
	// Create a new process.
	Task *new_task = (Task*)KMemoryAllocate(sizeof(Task));
	new_task->id = next_pid++;
	new_task->esp = new_task->ebp = 0;
	new_task->eip = 0;
	new_task->page_directory = directory;
	current_task->kernel_stack = KMemoryAllocateAligned(KERNEL_STACK_SIZE);
	new_task->next = 0;
	
	// Add it to the end of the ready queue.
	// Find the end of the ready queue...
	Task *tmp_task = (Task*)ready_queue;
	while (tmp_task->next)
		tmp_task = tmp_task->next;
	// ...And extend it.
	tmp_task->next = new_task;
	
	// This will be the entry point for the new process.
	uint32 eip = read_eip();
	
	// We could be the parent or the child here - check.
	if (current_task == parent_task) {
		// We are the parent, so set up the esp/ebp/eip for our child.
		uint32 esp;
	asm volatile("mov %%esp, %0" : "=r"(esp));
		uint32 ebp;
	asm volatile("mov %%ebp, %0" : "=r"(ebp));
		new_task->esp = esp;
		new_task->ebp = ebp;
		new_task->eip = eip;
		// All finished: Reenable interrupts.
		asm volatile("sti");
		
		// And by convention return the PID of the child.
		return new_task->id;
	}
	else {
		// We are the child - by convention return 0.
		return 0;
	}
	
}

int GetPid() {
	return global->current_task->id;
}

void SwitchToUserMode() {
	// Set up our kernel stack.
	global->dt.SetKernelStack(global->current_task->kernel_stack + KERNEL_STACK_SIZE);
	
	// Set up a stack structure for switching to user mode.
	asm volatile("  \
				 cli; \
				 mov $0x23, %ax; \
				 mov %ax, %ds; \
				 mov %ax, %es; \
				 mov %ax, %fs; \
				 mov %ax, %gs; \
				 \
				 \
				 mov %esp, %eax; \
				 pushl $0x23; \
				 pushl %esp; \
				 pushf; \
				 pushl $0x1B; \
				 push $1f; \
				 iret; \
				 1: \
				 ");
	             
}
