#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../main.h"


int system(const char *command);

// Non exhaustive list of reverse engineering tools

char* env_list[SIZE_ENV] = { "wireshark", "ghidra", "apktool", "gdb", "jad", "adb"};


bool string_test(char *line){
    for (int i=0; i<SIZE_ENV;i+=1){
        if(strcmp(line, env_list[i])==0){
            return true;
        }
    }
    return false;
}

int analysis_test(){

    pid_t child_pid;
    pid_t tpid;
    int child_status;
    child_pid = fork();
    if(child_pid==0){
        system("ps -eo comm > comm.txt");
    }else{
        wait(&child_status);
        printf("%d", child_pid);
        raise(SIGKILL);

        char    *filepath = "comm.txt";
        char    *line = NULL;
        bool infile = false;
        size_t  len = 0;
        ssize_t read;

        FILE *fp = fopen(filepath, "r");

        if (!fp) {
            fprintf(stderr, "Failed to open %s\n", filepath);
            return 1;
        }

        while ((read = getline(&line, &len, fp)) != -1) {
            line[strcspn(line, "\n")] = 0;
            if (string_test(line)) {
                infile = true;
            }
        }
        fclose(fp);

        if (line)
            free(line);
        
        if(infile){
            return FAIL;
        }
        return PASS;
    }
}