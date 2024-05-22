#include "../header/main.h"

int HasPermission(DirectoryNode* dirNode, char o)
{
    if(userList->current->id.UID == 0)
        return 0;

    if(userList->current->id.UID == dirNode->id.UID){
        if(o == 'r'){
            if(dirNode->permission.permission[0] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'w'){
            if(dirNode->permission.permission[1] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'x'){
            if(dirNode->permission.permission[2] == 0)
                return -1;
            else
                return 0;
        }
    }
    else if(userList->current->id.GID == dirNode->id.GID){
        if(o == 'r'){
            if(dirNode->permission.permission[3] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'w'){
            if(dirNode->permission.permission[4] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'x'){
            if(dirNode->permission.permission[5] == 0)
                return -1;
            else
                return 0;
        }
    }
    else{
        if(o == 'r'){
            if(dirNode->permission.permission[6] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'w'){
            if(dirNode->permission.permission[7] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'x'){
            if(dirNode->permission.permission[8] == 0)
                return -1;
            else
                return 0;
        }
    }
    return -1;
}

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
    else if(strcmp(dirPath,"~") == 0){
        char* homePath = (char *)malloc(strlen(dirPath));
        char* userName = NULL;
        strcpy(userName, currentUser->name);
        if (userName == NULL){
            printf("User Name Error\n");
        }
        else{
        homePath = "/home/"+(*userName);
        movePath(currentDirectoryTree,homePath);

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
    tempPath[MAX_DIR - 1] = '\0'; // 보안을 위해 널 종료 문자를 추가
    tempNode = currentDirectoryTree->current;
    
    //입력 값이 루트로 가는 값일 때
    //if input is root
    if(strcmp(dirPath, "/") == 0){
        currentDirectoryTree->current = currentDirectoryTree->root;
    }
    else{
        //if input is absolute path
        if(dirPath[0] == '/'){
            currentDirectoryTree->current = currentDirectoryTree->root; // Set current to root for absolute path
            // 이 부분을 수정하여 절대 경로를 올바르게 처리
            str = strtok(tempPath + 1, "/"); // +1 to skip the first '/'
        } else {
            // Relative path, start tokenizing from the beginning
            str = strtok(tempPath, "/");
        }
        while(str != NULL){

            val = moveCurrent(currentDirectoryTree, str);
            //if input path doesn't exist
            if(val != 0){
                currentDirectoryTree->current = tempNode; // Restore original current node
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
            printf("cd: cd [dir]\n");
            printf("    Change the shell working directory.\n\n");
            printf("    Change the current directory to DIR. The default DIR is the value of the\n");
            printf("    HOME shell variable.\n\n");
            printf("    The variable CDPATH defines the search path for the directory containing\n");
            printf("    DIR. Alternative directory names in CDPATH are separated by a colon (:).\n");
            printf("    A null directory name is the same as the current directory. If DIR begins\n");
            printf("    with a slash (/), then CDPATH is not used.\n\n");
            printf("    If the directory is not found, and the shell option `cdable_vars' is set,\n");
            printf("    the word is assumed to be a variable name. If that variable has a value,\n");
            printf("    its value is used for DIR.\n\n");
            printf("    Options:\n");
            printf("      --help     display this help and exit\n");
            return ERROR;
        }
        else{
            str = strtok(cmd, "-");
            if(str == NULL){
                printf("cd: Permission\n");
                printf("Try 'cd --help' for more information.\n");
                return ERROR;
            }
             else {
            if (cmd[1] == '\0') {
                printf("cd: Invalid option -- 'none'\n");
            } else if (cmd[1] == '-') {
                if (cmd[2] == '\0') {
                    printf("cd: Invalid option -- '-'\n");
                } else {
                    printf("cd: Invalid option -- '-'\n");
                }
            } else {
                printf("cd: Invalid option -- '%c'\n", cmd[1]);
            }
            printf("Try 'cd --help' for more information.\n");
            return ERROR;
        }
    }
    else{
        tempNode = IsExistDir(currentDirectoryTree, cmd, 'd');
        if(tempNode != NULL){
            if(HasPermission(tempNode, 'r') != 0){
                printf("-bash: cd: '%s': Permission denied.\n", cmd);
                return ERROR;
            }
        }
        tempNode = IsExistDir(currentDirectoryTree, cmd,  'f');
        if(tempNode != NULL){
            printf("-bash: cd: '%s': Not a directory.\n", cmd);
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