#include "../header/main.h"

void executeCommand(DirectoryTree *currentDirectoryTree, char *command)
{
    char *var;
    char *var1;
    char *var2;
    int value;

    if (!strcmp(command, "") || command[0] == ' ')
        return;

    var = strtok(command, " ");

    if (!strcmp(var, "mkdir"))
    {
        var = strtok(NULL, " ");
        // mkdir 코드 구현
    }
    else if (!strcmp(var, "touch"))
    {
        var = strtok(NULL, " ");
        // touch 코드 구현
    }
    else if (!strcmp(var, "mv"))
    {
        var = strtok(NULL, " ");
        var1 = strtok(NULL, " ");
        // mv 코드 구현
    }
    else if (!strcmp(var, "cp"))
    {
        var = strtok(NULL, " ");
        var1 = strtok(NULL, " ");
        // cp 코드 구현
    }
    else if (!strcmp(var, "cd"))
    {
        var = strtok(NULL, " ");
        // cd 코드 구현
    }
    else if (!strcmp(var, "pwd"))
    {
        var = strtok(NULL, " ");
        pwd(currentDirectoryTree, dirStack, var);
    }
    else if (!strcmp(var, "ls"))
    {
        var = strtok(NULL, " ");
        // ls 코드 구현
    }
    else if (!strcmp(var, "cat"))
    {
        var = strtok(NULL, " ");

        // -n 옵션 및 > 'filename' 옵션을 확인
        int numberFlag = 0; // -n 옵션 여부. 줄번호 출력 여부.
        char *redirectFilename = NULL;
        if (var != NULL && !strcmp(var, "-n"))
        {
            numberFlag = 1;
            var = strtok(NULL, " ");
        }
        if (var != NULL && var[0] == '>')
        {
            redirectFilename = var + 1; // '>' 다음 문자열을 파일명으로 설정
            var = strtok(NULL, " ");
        }

        if (var != NULL)
        {
            cat(currentDirectoryTree, var, numberFlag, redirectFilename);
        }
        else
        {
            printf("Usage: cat [-n] [filename] [> 'filename']\n");
        }
    }
    else if (!strcmp(var, "chmod"))
    {
        var = strtok(NULL, " ");
        // chmod 코드 구현
    }
    else if (!strcmp(var, "grep"))
    {
        var = strtok(NULL, " ");
        // grep 코드 구현
    }
    else if (!strcmp(command, "exit"))
    {
        printf("logout\n");
        exit(0);
    }
    else
        printf("Command '%s' not found\n", command);
    return;
}
