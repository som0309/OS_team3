//디렉토리 구조를 가져오는 코드
#include "../header/main.h"
DirectoryTree* loadDirectory(){

    DirectoryTree* currentDirTree = (DirectoryTree*)malloc(sizeof(DirectoryTree));
    char tmp[256];

    Directory = fopen("Directory.txt", "r");
    while(fgets(tmp, 256, Directory) != NULL){
        ReadNode(currentDirTree, tmp);
    }
    fclose(Directory);
    currentDirTree->current = currentDirTree->root;
    return currentDirTree;

}