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
            currentUser = tempUser;
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

void Start(){
    Date tmpDate;
    getToday(&tmpDate);
    printf("Welcome to OS_01_team3 LINUX OS!!!\n\n");
    printf("System information as of ");
    getWeekday(tmpDate.weekday);
    getMonth(tmpDate.month);
    printf("%d %02d:%02d:%02d UTC %d\n\n", tmpDate.day, tmpDate.hour, tmpDate.minute, tmpDate.second, tmpDate.year);
    printf("You can use the command displayed below.\n");
    printf("\t- ls\n\t- cat\n\t- cd\n\t- mkdir\n\t- touch\n\t- mv\n\t- chmod\n\t- more\n\t- cp\n\t- grep\n\t- pwd\n\n");
    printf("The 'exit' command allows you to exit the program.\n\n");
    printf("Last login: ");
    getWeekday(userList->current->date.weekday);
    getMonth(userList->current->date.month);
    printf("%d %02d:%02d:%02d %d\n", userList->current->date.day, userList->current->date.hour, userList->current->date.minute, userList->current->date.second, userList->current->date.year);

}