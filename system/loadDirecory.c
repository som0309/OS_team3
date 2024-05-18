//디렉토리 구조를 가져오는 코드
#include "../header/main.h"
DirectoryTree* loadDirectory(){

    DirectoryTree* currentDirectoryTree = (DirectoryTree*)malloc(sizeof(DirectoryTree));
    char temp[256];

    Directory = fopen("./Directory.txt", "r");
    while(fgets(temp, 256, Directory) != NULL){
        readNode(currentDirectoryTree, temp);
    }
    fclose(Directory);
    currentDirectoryTree->current = currentDirectoryTree->root;     //로그인 후 첫 시작 위치 
    return currentDirectoryTree;

}