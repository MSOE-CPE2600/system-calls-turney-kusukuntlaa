// * Anish Kusukuntla
// * Description: Uses the nice command to reduce the priority by 10 and then 
// * sleep for 1837272638 nanoseconds. Prints goodbye after the sleep time.
// * pmod.c
// * Date: 11/15/2024

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    int command = nice(10); //Uses the nice command for decrementing.
    //I would need to increase the nice command to reduce the priority.
    //Checks for if the nice command succeeds
    if (command == -1) {
        perror("nice command failed");
        return 1;
    }
    printf("The nice value is currently: %d\n", command);

    int pid = getpid(); //Gets the current process ID
    int priority = getpriority(PRIO_PROCESS, pid); //Gets the priority of the ID
    //Checks for if the getting the priority succeeds
    if (priority == -1) {
        perror("Failed to get priority");
        return 1;
    }
    
    printf("The program priority value is now %d\n", priority);
    //Begins nano sleep for 1837272638 nanoseconds which is converted to 1.837272638 seconds
    sleep(1.837272638);
    
    
    printf("Goodbye\n");


    return 0;
}