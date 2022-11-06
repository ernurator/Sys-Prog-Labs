#include "u-lib.hh"
#ifndef ALLOC_SLOWDOWN
#define ALLOC_SLOWDOWN 100
#endif

extern uint8_t end[];

// These global variables go on the data page.
uint8_t* heap_top;
uint8_t* stack_bottom;

void process_main() {
    pid_t p = sys_getpid();

    // The heap starts on the page right after the 'end' symbol,
    // whose address is the first address not allocated to process code
    // or data.
    heap_top = (uint8_t*) round_up((uintptr_t) end, PAGESIZE);

    // The bottom of the stack is the first address on the current
    // stack page (this process never needs more than one stack page).
    stack_bottom = (uint8_t*) round_down((uintptr_t) rdrsp() - 1, PAGESIZE);

    // Allocate heap pages until (1) hit the stack (out of address space)
    // or (2) allocation fails (out of physical memory).
    uint8_t* current_addr = heap_top;
    while (current_addr != stack_bottom) {
        int res = sys_page_alloc(current_addr);
        if (res < 0) {
            break;
        }
        pid_t* pid_ptr = (pid_t*) current_addr;
        *pid_ptr = p; 
        current_addr = current_addr + PAGESIZE;
    }

    // Do nothing forever
    while (true) {
        sys_yield();
    }
}
