#include "../header/main.h"
UserList *loadUserList() {
    UserList *userList = (UserList *)malloc(sizeof(UserList));
    char tmp[MAX_NAME];

    User = fopen("system/User.txt", "r");
    while (fgets(tmp, MAX_NAME, User)) {
        readUser(userList, tmp);
    }
    fclose(User);
    userList->current = NULL;
    return userList;
}
UserNode *userExistence(UserList *userList, char *name){
    for (UserNode *current = userList->head; current; current = current->nextNode) {
        if (!strcmp(current->name, name)) {
            return current;
        }
    }
    return NULL;
}

int readUser(UserList *userList, char *tmp) {
    UserNode *userNode = (UserNode *)malloc(sizeof(UserNode));
    char *str;

    userNode->nextNode = NULL;
    str = strtok(tmp, " ");
    strncpy(userNode->name, str, MAX_NAME);
    str = strtok(NULL, " ");
    userNode->id.UID = atoi(str);
    str = strtok(NULL, " ");
    userNode->id.GID = atoi(str);
    str = strtok(NULL, " ");
    userNode->date.year = atoi(str);
    str = strtok(NULL, " ");
    userNode->date.month = atoi(str);
    str = strtok(NULL, " ");
    userNode->date.weekday = atoi(str);
    str = strtok(NULL, " ");
    userNode->date.day = atoi(str);
    str = strtok(NULL, " ");
    userNode->date.hour = atoi(str);
    str = strtok(NULL, " ");
    userNode->date.minute = atoi(str);
    str = strtok(NULL, " ");
    userNode->date.second = atoi(str);
    str = strtok(NULL, " ");
    str[strlen(str)-1] = '\0';
    strncpy(userNode->dir, str, MAX_DIR);

    if (!strcmp(userNode->name, "root")) {
        userList->head = userNode;
        userList->tail = userNode;
    } else {
        userList->tail->nextNode = userNode;
        userList->tail = userNode;
    }
    return SUCCESS;
}
void userWrite(UserList* userList, UserNode* userNode)
{
    time(&ltime);
    today = localtime(&ltime);

    userList->current->date.year = today->tm_year + 1900;
    userList->current->date.month = today->tm_mon + 1;
    userList->current->date.weekday = today->tm_wday;
    userList->current->date.day = today->tm_mday;
    userList->current->date.hour = today->tm_hour;
    userList->current->date.minute = today->tm_min;
    userList->current->date.second = today->tm_sec;

    fprintf(User, "%s %d %d %d %d %d %d %d %d %d %s\n", userNode->name, userNode->id.UID, userNode->id.GID, userNode->date.year, userNode->date.month, userNode->date.weekday, userNode->date.day, userNode->date.hour, userNode->date.minute, userNode->date.second, userNode->dir);

    if (userNode->nextNode != NULL) {
        userWrite(userList, userNode->nextNode);
    }

}
void SaveUserList(UserList *userList){
    userWrite(userList, userList->head);
    fclose(Directory);
}