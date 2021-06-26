// The premis of this technique is that ptrace can only be called once on a process. If it return -1, then the process is already traced.
#include "ptrace.h"
#include "../main.h"
#include <sys/ptrace.h>
#include <stdio.h>

int ptrace_test(){
    if(ptrace(PTRACE_TRACEME, 0 ,1 ,0) <0){
        return FAIL;
    }else{
        return PASS;
    }
}