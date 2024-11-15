// * Anish Kusukuntla, etc

// * info.c
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <string.h>
int main(int argc, char* argv[])
{
    
    time_t ts; //Declares a time variable
    time(&ts); //Gets the time in nanaseconds of the day
    struct tm *localTime = localtime(&ts); //stores the ts for retrieving local time

    
    if(localTime != NULL) {
        printf("Current time is %d : %d : %d\n", localTime -> tm_hour, localTime -> tm_min, 
        localTime -> tm_sec); 
        //localTime can print out the hour of the day, 
        // minute of the hour, or seconds of the minute.
    }

    struct utsname s_info; //declares a variable for the struct utsname
    
    
    // This if statement would recieve the name for the network, system, release,
    // version, and machine. It would print each of them as long as all of them exist. 
     
    if(uname(&s_info) == 0) {
        if (s_info.nodename && strlen(s_info.nodename) > 0) {
            printf("System network name: %s\n", s_info.nodename);
        } 
        if(s_info.sysname && strlen(s_info.sysname) > 0) {
            printf("Operating system name: %s\n", s_info.sysname);
        } 
        if(s_info.release && strlen(s_info.release) > 0) {
            printf("Release system name: %s\n", s_info.release);
        } if(s_info.version && strlen(s_info.version) > 0) {
            printf("Version system name: %s\n", s_info.version);
        } if(s_info.machine && strlen(s_info.machine) > 0) {
            printf("Machine system name: %s\n", s_info.machine);
        }
    }
    //Gets the number of CPUs
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    if(nprocs > 0) {
        printf("CPUs: %ld\n", nprocs);
    }
    // Gets the total and free memory from the file /proc/meminfo
    FILE *f = fopen("/proc/meminfo", "r");
    if (f == NULL){
        
        perror("File is not able to open\n");
        return 1;
    }

    char line[256];
    long memory1 = -1;
    long memory2 = -1;
    
    // In the while loop, the file would count how many total bytes there are in the physical memory
    // and free memory.
     
    while (fgets(line, sizeof(line), f)){
        if (sscanf(line, "MemTotal: %ld kB", &memory1) == 1) {
            memory1 *= 1024;
            
        } else if (sscanf(line, "MemFree: %ld kB", &memory2) == 1) {
            memory2 *= 1024;
            
        }
        if(memory1 != -1 && memory2 != -1){
            break;
        }
    }
    
    fclose(f);
    //Would then print the memory of both physical and free
    if(memory1 != -1){
        printf("Physical Memory (in bytes): %ld\n", memory1);
    }
    if(memory2 != -1){
        printf("Free Memory (in bytes): %ld\n", memory2);
    }
    return 0;
}