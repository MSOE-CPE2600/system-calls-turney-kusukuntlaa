// * Anish Kusukuntla
// * Description: Takes the command line and prints out the process priority and
// * scheduling method.
// * pinfo.c
// * Date: 11/15/2024

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char* argv[])
{
    int pid;
    //Checks if getting the identification succeeds.
    //If it succeeds, identification will proceed in being processed.
    if(argc == -1){
        perror("getting the identification failed");
        exit(1);
    } else if(argc > 1){
        for (int i = 0; argv[1][i] != '\0'; i++) {
            if (!isdigit(argv[1][i])) {
                fprintf(stderr, "Error: '%s'\n", argv[1]);
                return 1;
            }
        }
        pid = atoi(argv[1]);
    } else {
        pid = getpid();
    }
    printf("The process identification is %d\n", pid);
    int command = getpriority(PRIO_PROCESS, pid);
    //Checks if getting the priority succeeds
    if (command == -1) {
        perror("getpriority failed");
        return 1;
    }
    printf("The program scheduling priority is %d\n", command);
    int schedule = sched_getscheduler(pid);
    //Prints out which scheduler the identification is under
    if(schedule == SCHED_OTHER){
        printf("schduler: SCHED_OTHER\n");
    } 
    else if(schedule == SCHED_FIFO){
        printf("scheduler: SCHED_FIFO\n");
    } 
    else if(schedule == SCHED_RR){
        printf("scheduler: SCHED_RR\n");
    } 
    #ifdef SCHED_BATCH
    else if(schedule == SCHED_BATCH) {
        printf("scheduler: SCHED_BATCH\n");
    } 
    #endif
    #ifdef SCHED_IDLE
    else if(schedule == SCHED_IDLE) {
        printf("scheduler: SCHED_IDLE\n");
    }
    #endif
    else {
        printf("scheduler is unknown\n");
    }
    return 0;
}