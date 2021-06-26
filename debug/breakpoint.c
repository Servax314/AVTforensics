#include "breakpoint.h"
#include "../main.h"
#include <stdio.h>

void foo()
{
        puts("Hello");
}

int breakpoint_test()
{
        if ((*(volatile unsigned *)((unsigned)foo + 3) & 0xff) == 0xcc) {
                puts("BREAKPOINT");
                return FAIL;
        }
        foo();
        return PASS;
}