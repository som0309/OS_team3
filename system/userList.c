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