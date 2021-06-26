#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int result = PASS;

/*     puts("Testing breakpoint");
    int res = breakpoint_test();
    if(res){
        puts("PASS");
    }else{
        puts("FAIL");
        result = FAIL;
    } */

    puts("Testing ptrace");
    int res = ptrace_test();
    if(res){
        puts("PASS");
    }else{
        puts("FAIL");
        result = FAIL;
    }

    puts("Testing analysis");
    res = analysis_test();
    if(res){
        puts("PASS");
    }else{
        puts("FAIL");
        result = FAIL;
    }


    puts("Testing Virtual Machines");
    res = vm_test();
    if(res){
        puts("PASS");
    }else{
        puts("FAIL");
        result = FAIL;
    }
}