
#include <system.h>

int timer_ticks = 0;

void timer_handler(struct regs *r)
{
   // Timer callback
}


void timer_wait(int ticks)
{
    unsigned long eticks;

    // Warten, bis timer_ticks gross genug ist
}


void timer_install()
{
    
    irq_install_handler(0, timer_handler);
}
