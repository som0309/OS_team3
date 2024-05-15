#include "../header/main.h"

// 현재 경로를 출력해야 하므로 DirectoryTree로 파일 시스템에 접근할 수 있어야 하고
// 현재 파일 경로까지 탐색해야 하므로 root부터 현재 위치까지 Stack에 넣은 후 다시 Pop한다.
// Stack을 사용하는 이유는 현재 경로를 root부터 출력하기 위함이다.
void inputStack(DirectoryTree *currentDirectory, DirectoryNode *currentNode, Stack *dirStack){
    // 루트 디렉토리가 아닌 경우
    while (currentNode->parent != currentDirectory->root) {
        Push(dirStack, currentNode->name);
        currentNode = currentNode->parent;
    }
    Push(dirStack, currentNode->name);
}
void popStack(){
    while (!IsEmpty(dirStack)) {
            printf("/%s", Pop(dirStack));
    }
    printf("\n");
}

void printPath(DirectoryTree *currentDirectory, Stack *dirStack) {
    DirectoryNode *currentNode = currentDirectory->current;

    if (currentNode->parent == currentDirectory->root) {
        // 루트 디렉토리인 경우
        printf("/");
    }
    else{
        InputStack(currentDirectory, currentNode, dirStack);
        popStack();
    }
}

int pwd(DirectoryTree *currentDirectory, Stack *dirStack, char *option) {
    int dashCount=0;
    if (currentDirectory == NULL) {
        printf("The current directory information could not be found.\n");
        return ERROR;
    }

    if (!option || !strcmp(option, '-') || !strcmp(option, '--')){
        printPath(currentDirectory, dirStack);
    }
    else if (!strcmp(option, '--')){
        printf("pwd: pwd [-LP]\n");
        printf("  Print the name of the current working directory.\n\n");
        
        printf("  Options:\n");
        printf("    -L\t print the value of $PWD if it names the current working\n");
        printf("  \t directory\n");
        printf("    -P\t print the physical direcrtory, without any symbolic links\n\n");
        
        printf("  By default, 'pwd' behaves as if '-L' were specified.\n\n");
        
        printf("  Exit status:\n");
        printf("  Returns 0 unless an invalid option is given or the current directory\n");
        printf("  cannot be read.\n");
    }
    else{
        printf("-bash: pwd: %.2s: invalid option\n", option);
        printf("pwd: usage: pwd [-LP]\n");
        return ERROR;
    }
    return SUCCESS;
}