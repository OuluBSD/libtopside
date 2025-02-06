#ifndef _LittleKernel_Task_h_
#define _LittleKernel_Task_h_


#define KERNEL_STACK_SIZE 2048       // Use a 2kb kernel stack.

extern "C" {
	uint32 read_eip();
}

// This structure defines a 'task' - a process.
struct Task
{
    int id;                // Process ID.
    uint32 esp, ebp;       // Stack and base pointers.
    uint32 eip;            // Instruction pointer.
    PageDirectory *page_directory; // Page directory.
    uint32 kernel_stack;   // Kernel stack location.
    Task *next;            // The next task in a linked list.
};

// Initialises the tasking system.
void InitialiseTasking();

// Called by the timer hook, this changes the running process.
void TaskSwitch();

// Forks the current process, spawning a new one with a different
// memory space.
int Fork();

// Causes the current process' stack to be forcibly moved to a new location.
void MoveStack(void *new_stack_start, uint32 size);

// Returns the pid of the current process.
int GetPid();

void SwitchToUserMode();


#endif
