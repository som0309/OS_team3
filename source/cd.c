#include "../header/main.h"

TreeNode* IsExistDir(DirectoryTree* dirTree, char* dirName, char type)
{
    //variables
    TreeNode* returnNode = NULL;

    returnNode = dirTree->current->LeftChild;

    while(returnNode != NULL){
        if(strcmp(returnNode->name, dirName) == 0 && returnNode->type == type)
            break;
        returnNode = returnNode->RightSibling;
    }
    return returnNode;
}

int HasPermission(TreeNode* dirNode, char o)
{
    if(usrList->current->UID == 0)
        return 0;

    if(usrList->current->UID == dirNode->UID){
        if(o == 'r'){
            if(dirNode->permission[0] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'w'){
            if(dirNode->permission[1] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'x'){
            if(dirNode->permission[2] == 0)
                return -1;
            else
                return 0;
        }
    }
    else if(usrList->current->GID == dirNode->GID){
        if(o == 'r'){
            if(dirNode->permission[3] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'w'){
            if(dirNode->permission[4] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'x'){
            if(dirNode->permission[5] == 0)
                return -1;
            else
                return 0;
        }
    }
    else{
        if(o == 'r'){
            if(dirNode->permission[6] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'w'){
            if(dirNode->permission[7] == 0)
                return -1;
            else
                return 0;
        }
        if(o == 'x'){
            if(dirNode->permission[8] == 0)
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

<<<<<<< HEAD
    strncpy(tmpPath, dirPath, MAX_DIR);
    tmpNode = dirTree->current;
    //입력 값이 루트로 가는 값일 때ㅐ
=======
    //if input is root
>>>>>>> 78891d9ce92cb11592bec4993abe4258880f8f0b
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
<<<<<<< HEAD
            val = MoveCurrent(dirTree, str);
            //경로가 존재하지 않을 때
=======
            val = moveCurrent(currentDirectoryTree, str);
            //if input path doesn't exist
>>>>>>> 78891d9ce92cb11592bec4993abe4258880f8f0b
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
            printf("cd: Invalid option -- '%s'\n", str);
            printf("Try 'cd --help' for more information.\n");

            return ERROR;
            }
        }
    }
    else{
        tempNode = IsExistDir(currentDirectoryTree, cmd, 'd');
        if(tempNode != NULL){
            // if(HasPermission(tempNode, 'r') != 0){
                if(0){
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