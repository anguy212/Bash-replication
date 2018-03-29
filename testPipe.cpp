#include<sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h>
#include<unistd.h>
#include<iostream>
#include<string>
#include<errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{

    string firstcmd1 = "ls";

    string frsarg1 = "-l";

    string scmd1 = "wc";

    string secarg1 = "-l";
    
    char* firstcmd = new char[firstcmd1.length() + 1];
    
    char* frsarg = new char[frsarg1.length() + 1];

    char* scmd = new char[scmd1.length() + 1];

    char* secarg = new char[secarg1.length() + 1];
    
    strcpy(firstcmd, firstcmd1.c_str());

    strcpy(frsarg, frsarg1.c_str());

    strcpy(scmd, scmd1.c_str());

    strcpy(secarg, secarg1.c_str());
//
    pid_t pid;
    int fd[2];
    
    pipe(fd);
    pid = fork();
    
    if(pid==0) // parent process
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp(firstcmd, firstcmd, frsarg, (char*) NULL);
        fprintf(stderr, "Failed to execute '%s'\n", firstcmd);
        exit(1);
    }
    else // child process
    {
        pid=fork();
        
        if(pid==0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            execlp(scmd, scmd, secarg,(char*) NULL);
            fprintf(stderr, "Failed to execute '%s'\n", scmd);
            exit(1);
        }
        else
        {
            int status;
            close(fd[0]);
            close(fd[1]);
            waitpid(pid, &status, 0);
        }
    }
}
