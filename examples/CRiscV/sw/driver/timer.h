#pragma once

#include "criscv.h"
#include "io.h"

#define TIMER_IPI_ADDR (TIMER_BASE + 0x0000)
#define TIMER_CMP_ADDR (TIMER_BASE + 0x4000)
#define TIMER_TIME_ADDR (TIMER_BASE + 0xBFF8)


static u64 timer_clockticks(){
        u64 lo, hi;
        hi = read32(TIMER_TIME_ADDR+4);
        lo = read32(TIMER_TIME_ADDR);
        u64 ret = hi << 32;
        ret = ret | lo;
        return ret;
}
static void timer_usleep(u32 usec){
        u32 one_usec = MAIN_CLOCK_HZ/1000000;
        u32 limit = timer_clockticks() + usec*one_usec;
        while((int)(limit-timer_clockticks()) >= 0);
}

