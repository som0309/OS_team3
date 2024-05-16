#include "../header/main.h"

void createAndAttachNode(DirectoryTree *currentDirectoryTree, char *str, DirectoryNode *newNode, DirectoryNode *tempNode) {
    if (str) {
        str[strlen(str) - 1] = '\0';
        changePath(currentDirectoryTree, str);
        newNode->parent = currentDirectoryTree->current;
        if (!currentDirectoryTree->current->firstChild) {
            currentDirectoryTree->current->firstChild = newNode;
        } else {
            tempNode = currentDirectoryTree->current->firstChild;
            while (tempNode->nextSibling) {
                tempNode = tempNode->nextSibling;
            }
            tempNode->nextSibling = newNode;
        }
    } else {
        currentDirectoryTree->root = newNode;
        currentDirectoryTree->current = currentDirectoryTree->root;
    }
}

int readNode(DirectoryTree *currentDirectoryTree, char *temp) {
    //Directory.txt 파일에서 현재 저장된 파일 및 디렉토리 정보를 가져와 구조체로 만들어 Tree에 넣는 메소드 
    DirectoryNode *newNode = (DirectoryNode *)malloc(sizeof(DirectoryNode)), *tempNode = NULL;
    char *str;

    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    newNode->parent = NULL;
    //ex) etc d 755 4096 0 0 6 1 1 23 /     이런 정보가 있다고 하면 앞에서부터 하나씩 Node에 속성을 넣는다.
    //폴더 및 파일명 저장 
    str = strtok(temp, " ");
    strncpy(newNode->name, str, MAX_NAME);
    //폴더 및 파일 유형 저장 (-, d, l 등)
    str = strtok(NULL, " ");
    newNode->type = str[0];
    //Node의 Permission 정보 저장 
    str = strtok(NULL, " ");
    newNode->permission.mode = atoi(str);
    modeToPermission(newNode);  //permission 정보를 배열에 저장하는 코드 (755의 권한을 크기 9의 배열에 binary하게 표현)
    //Node 크기 저장
    str = strtok(NULL, " ");
    newNode->SIZE = atoi(str);
    //Node의 user id 저장 
    str = strtok(NULL, " ");
    newNode->id.UID = atoi(str);
    //Node의 group id 저장
    str = strtok(NULL, " ");
    newNode->id.GID = atoi(str);
    //Node의 월 정보 저장 
    str = strtok(NULL, " ");
    newNode->date.month = atoi(str);
    //Node의 일 정보 저장
    str = strtok(NULL, " ");
    newNode->date.day = atoi(str);
    //Node의 시간 정보 저장
    str = strtok(NULL, " ");
    newNode->date.hour = atoi(str);
    //Node의 분 정보 저장
    str = strtok(NULL, " ");
    newNode->date.minute = atoi(str);
    //str은 이제 해당 노드의 위치를 나타냄.
    str = strtok(NULL, " ");
    //DirectoryTree에 Node를 적절한 위치에 추가하기 
    createAndAttachNode(currentDirectoryTree, str, newNode, tempNode);
    return 0;
}
