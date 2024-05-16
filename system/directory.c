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
    DirectoryNode *newNode = (DirectoryNode *)malloc(sizeof(DirectoryNode)), *tempNode = NULL;
    char *str;

    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    newNode->parent = NULL;

    str = strtok(temp, " ");
    strncpy(newNode->name, str, MAX_NAME);
    str = strtok(NULL, " ");
    newNode->type = str[0];
    str = strtok(NULL, " ");
    newNode->permission.mode = atoi(str);
    modeToPermission(newNode);
    str = strtok(NULL, " ");
    newNode->SIZE = atoi(str);
    str = strtok(NULL, " ");
    newNode->id.UID = atoi(str);
    str = strtok(NULL, " ");
    newNode->id.GID = atoi(str);
    str = strtok(NULL, " ");
    newNode->date.month = atoi(str);
    str = strtok(NULL, " ");
    newNode->date.day = atoi(str);
    str = strtok(NULL, " ");
    newNode->date.hour = atoi(str);
    str = strtok(NULL, " ");
    newNode->date.minute = atoi(str);
    str = strtok(NULL, " ");

    createAndAttachNode(currentDirectoryTree, str, newNode, tempNode);
    return 0;
}
