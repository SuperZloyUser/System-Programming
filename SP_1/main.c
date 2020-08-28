#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int spawn(char* program, char** argList)
{
    pid_t childPid;
    childPid = fork();
    if (0 != childPid)
        return childPid;
    else
    {
        execvp(program, argList);
        abort();
    }
}

int main(int argc, char** argv)
{
    int childStatus;

    spawn("SP_1_sub/SP_1_sub", NULL);

    wait(&childStatus);
    if(WIFEXITED(childStatus))
        return childStatus;
    else
        return 0;

}
