// Assuming no privilege
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../main.h"

int system(const char *command);

int module_test(){
    pid_t child_pid;
    pid_t tpid;
    int child_status;
    char    *filepath = "module.txt";
    bool empty = true;

    child_pid = fork();
    if(child_pid==0){
        system("/sbin/lsmod | grep 'vmw \\| vboxguest \\| vmxnet' > module.txt");
    }else{
        wait(&child_status);
        raise(SIGKILL);

        FILE *fp = fopen(filepath, "r");

        if (NULL != fp) {
            fseek (fp, 0, SEEK_END);
            int size = ftell(fp);

            if (0 == size) {
            }else{
                return FAIL;
            }
        }   
        return PASS;   
    }    
}

int pci_test(){
    pid_t child_pid;
    pid_t tpid;
    int child_status;
    char    *filepath = "pci.txt";
    bool empty = true;

    child_pid = fork();
    if(child_pid==0){
        system("lspci | grep 'VMware \\| VirtualBox' > pci.txt");
    }else{
        wait(&child_status);
        raise(SIGKILL);

        FILE *fp = fopen(filepath, "r");

        if (NULL != fp) {
            fseek (fp, 0, SEEK_END);
            int size = ftell(fp);

            if (0 == size) {
            }else{
                return FAIL;
            }
        }   
        return PASS;   
    }    
}

int scsi_test(){
    pid_t child_pid;
    pid_t tpid;
    int child_status;
    char    *filepath = "scsi.txt";
    bool empty = true;

    child_pid = fork();
    if(child_pid==0){
        system("cat /proc/scsi/scsi | grep 'VMware \\| VirtualBox' > scsi.txt");
    }else{
        wait(&child_status);
        raise(SIGKILL);

        FILE *fp = fopen(filepath, "r");

        if (NULL != fp) {
            fseek (fp, 0, SEEK_END);
            int size = ftell(fp);

            if (0 == size) {
            }else{
                return FAIL;
            }
        }   
        return PASS;   
    }    
}

int vm_test(){
    int res = module_test()||pci_test()||scsi_test();
    return !res;
}