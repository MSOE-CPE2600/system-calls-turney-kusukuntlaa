// * Anish Kusukuntla
// * Lab 9 - System Calls
// * Description: Takes the command line and displays the file's (if valid)
// * information such as what file it is under, permissions, owner identification,
// * and when it was last modified.
// * finfo.c
// * Date: 11/15/2024

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

int main(int argc, char* argv[])
{
    //Checks to see if the user is putting a file name
    if(argc != 2){
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    struct stat s;
    //Checks to make sure the filename is valid
    if(stat(argv[1], &s) == -1) {
        perror("Error: Trouble with information");
        return 1;
    }
    //Prints what file it is under
    printf("File: ");
    if(S_ISREG(s.st_mode)) {
        printf("Regular file\n");
    } else if(S_ISDIR(s.st_mode)) {
        printf("Directory\n");
    } else if(S_ISLNK(s.st_mode)) {
        printf("Symbolic link\n");
    } else if(S_ISBLK(s.st_mode)) {
        printf("Block device\n");
    } else if(S_ISCHR(s.st_mode)) {
        printf("Character device\n");
    } else if(S_ISFIFO(s.st_mode)) {
        printf("FIFO\n");
    } else if(S_ISSOCK(s.st_mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown\n");
    }
    
    printf("Permissions: ");
    //Prints out the permission set for the file
    //Found that this is another way to use an if statement for using the ?
    printf((S_ISDIR(s.st_mode)) ? "d" : "-");
    printf((s.st_mode & S_IRUSR) ? "r" : "-");
    printf((s.st_mode & S_IWUSR) ? "w" : "-");
    printf((s.st_mode & S_IXUSR) ? "x" : "-");
    printf((s.st_mode & S_IRGRP) ? "r" : "-");
    printf((s.st_mode & S_IWGRP) ? "w" : "-");
    printf((s.st_mode & S_IXGRP) ? "x" : "-");
    printf((s.st_mode & S_IROTH) ? "r" : "-");
    printf((s.st_mode & S_IWOTH) ? "w" : "-");
    printf((s.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    //Prints out the owner identification, size, and the time it was last modified
    printf("Owner Identification: %d\n", s.st_uid);
    printf("Size: %ld bytes\n", s.st_size);
    char timer[80];
    struct tm *info = localtime(&s.st_mtime);
    strftime(timer, sizeof(timer), "%m-%d-%Y", info);
    printf("Last modified: %s\n", timer);
    printf("%d : %d : %d\n", info -> tm_hour, info -> tm_min, info -> tm_sec);
    return 0;
}