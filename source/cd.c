#include "../header/main.h"

int moveCurrent(DirectoryTree* currentDirectoryTree, char* dirPath)
{
    DirectoryNode* tempNode = NULL;
    if(strcmp(dirPath,".") == 0){
    }
    else if(strcmp(dirPath,"..") == 0){
        if(currentDirectoryTree->current != currentDirectoryTree->root){
            currentDirectoryTree->current = currentDirectoryTree->current->parent;
        }
    }
    else{

        tempNode = IsExistDir(currentDirectoryTree, dirPath, 'd');
        if(tempNode != NULL){
            currentDirectoryTree->current = tempNode;
        }
        else
            return -1;
    }
    return 0;
}

int movePath(DirectoryTree* currentDirectoryTree, char* dirPath)
{
    DirectoryNode* tempNode = NULL;
    char tempPath[MAX_DIR];
    char* str = NULL;
    int val = 0;

    strncpy(tempPath, dirPath, MAX_DIR);
    tempNode = currentDirectoryTree->current;
    //if input is root
    if(strcmp(dirPath, "/") == 0){
        currentDirectoryTree->current = currentDirectoryTree->root;
    }
    else{
        //if input is absolute path
        if(strncmp(dirPath, "/",1) == 0){
            if(strtok(dirPath, "/") == NULL){
                return ERROR;
            }
            currentDirectoryTree->current = currentDirectoryTree->root;
        }
        //if input is relative path
        str = strtok(tempPath, "/");
        while(str != NULL){
            val = moveCurrent(currentDirectoryTree, str);
            //if input path doesn't exist
            if(val != 0){
                currentDirectoryTree->current = tempNode;
                return -1;
            }
            str = strtok(NULL, "/");
        }
    }
    return 0;
}

int cd(DirectoryTree* currentDirectoryTree, char* cmd)
{
    DirectoryNode* tempNode = NULL;
    char* str = NULL;
    char tmp[MAX_DIR];
    int val;

    if(cmd == NULL){
        strcpy(tmp, userList->current->dir);
        movePath(currentDirectoryTree, tmp);
    }
    else if(cmd[0] == '-'){
        if(strcmp(cmd, "--help") == 0){
            printf("사용법: cd 디렉터리...\n");
            printf("  Change the shell working directory.\n\n");
            printf("  Options:\n");
            printf("        --help\t 이 도움말을 표시하고 끝냅니다\n");
            return ERROR;
        }
        else{
            str = strtok(cmd, "-");
            if(str == NULL){
                printf("cd: 잘못된 연산자\n");
                printf("Try 'cd --help' for more information.\n");
                return ERROR;
            }
            else{
            printf("cd: 부적절한 옵션 -- '%s'\n", str);
            printf("Try 'cd --help' for more information.\n");

            return ERROR;
            }
        }
    }
    else{
        tempNode = IsExistDir(currentDirectoryTree, cmd, 'd');
        if(tempNode != NULL){
            if(HasPermission(tempNode, 'r') != 0){
                printf("-bash: cd: '%s': 허가거부\n", cmd);
                return ERROR;
            }
        }
        tempNode = IsExistDir(currentDirectoryTree, cmd,  'f');
        if(tempNode != NULL){
            printf("-bash: cd: '%s': 디렉터리가 아닙니다\n", cmd);
            return ERROR;
        }
        val = movePath(currentDirectoryTree, cmd);
        if(val != 0){
            printf("-bash: cd: '%s': no such file or directory\n", cmd);
            return ERROR;
        }
    }
    return 0;
}