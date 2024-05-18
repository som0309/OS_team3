#include "../header/main.h"
//로그인, 로그아웃, 프롬프트 메세지 등을 출력하는 코드들 
void login(UserList *userList, DirectoryTree *currentDirectoryTree) {
    UserNode *tempUser = NULL;
    char userName[MAX_NAME];
    char temp[MAX_DIR];
    tempUser = userList->head;
    printf("Users: ");
    
    while (tempUser) {
        printf("%s ", tempUser->name);
        tempUser = tempUser->nextNode;
    }

    printf("\n");

    while (1) {
        printf("Login as: ");
        fgets(userName, sizeof(userName), stdin);
        userName[strlen(userName) - 1] = '\0';
        if (!strcmp(userName, "exit")) {
            exit(0);
        }
        tempUser = userExistence(userList, userName);
        if (tempUser) {
            userList->current = tempUser;
            break;
        }
        printf("'%s' User not found\n", userName);
    }
    strcpy(temp, userList->current->dir);
    movePath(currentDirectoryTree, temp);
}

// prompt를 출력하는 함수
void printPrompt(DirectoryTree *currentDirectoryTree, Stack *dirStack) {
    DirectoryNode *tempNode = NULL;
    char temp[MAX_DIR] = "";
    char tempSecond[MAX_DIR] = "";
    char printCursor;

    if (userList->current == userList->head) {
        printCursor = '#'; // root로 로그인 했을 떄
        DEFAULT;
        printf("%s@OS_01_team3", userList->current->name);
        printf(":");
    }
    else {
        printCursor = '$'; // 그 외 user로 로그인 했을 때
        BOLD;GREEN;
        printf("%s@OS_01_team3", userList->current->name);
        DEFAULT;
        printf(":");
    }
    tempNode = currentDirectoryTree->current;

    if(tempNode == currentDirectoryTree->root){
        strcpy(temp, "/");
    } else {
        while (tempNode->parent) {
            Push(dirStack, tempNode->name);
            tempNode = tempNode->parent;
        }
        while (IsEmpty(dirStack) == 0) {
            strcat(temp, "/");
            strcat(temp, Pop(dirStack));
        }
    }
    strncpy(tempSecond, temp, strlen(userList->current->dir));
    if (userList->current == userList->head){
        DEFAULT;
        printf("%s", temp);
    } else if (strcmp(userList->current->dir, tempSecond)) {
	    BOLD;BLUE;
        printf("%s", temp);
    } else {
        tempNode = currentDirectoryTree->current;
        while (tempNode->parent) {
            Push(dirStack, tempNode->name);
            tempNode = tempNode->parent;
        }
        Pop(dirStack);
        Pop(dirStack);
	    BOLD;BLUE;
        printf("~");
        while (IsEmpty(dirStack) == 0) {
            printf("/");
            printf("%s", Pop(dirStack));
        }
    }
    DEFAULT;
    printf("%c ", printCursor);
}