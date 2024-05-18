#include "../header/main.h"

DirectoryNode* find_directory(DirectoryTree* currentDirectoryTree, char* name)
{
	DirectoryNode* temp = currentDirectoryTree->current->firstChild;	// current node에 저장되어 있는 디렉토리

	while (temp != NULL)
	{
		if (strcmp(temp->name, name) == 0)		// 같은 이름의 디렉토리가 존재하는 경우
		{
			break;
		}
		temp = temp->nextSibling;
	}
	return temp;
}

void clear_permissions(Permission* p) {
    for (int i = 0; i < 9; ++i) {
        p->permission[i] = 0;
    }
}

void apply_absolute_mode(Permission* p, const char* modeStr) {
    int mode = atoi(modeStr);
    p->mode = mode;

    for (int i = 8; i >= 0; --i) {
        p->permission[i] = mode % 2;
        mode /= 2;
    }
}

void apply_relative_mode(Permission* p, const char* modeStr) {
    int len = strlen(modeStr);
    int op = 0; // 1 for '+', -1 for '-', 0 for '='

    for (int i = 0; i < len; ++i) {
        switch (modeStr[i]) {
            case '+': op = 1; break;
            case '-': op = -1; break;
            case '=': op = 0; clear_permissions(p); break;
            case 'r':
                for (int j = 0; j < 9; j += 3) p->permission[j] = op >= 0 ? 1 : 0;
                break;
            case 'w':
                for (int j = 1; j < 9; j += 3) p->permission[j] = op >= 0 ? 1 : 0;
                break;
            case 'x':
                for (int j = 2; j < 9; j += 3) p->permission[j] = op >= 0 ? 1 : 0;
                break;
        }
    }
}

void parse_permission_info(char* permissionInfo, Permission* change_mod) {
    if (strchr(permissionInfo, '+') != NULL || strchr(permissionInfo, '-') != NULL || strchr(permissionInfo, '=') != NULL) {
        apply_relative_mode(change_mod, permissionInfo);
    } else {
        apply_absolute_mode(change_mod, permissionInfo);
    }
}

void ch_mod(DirectoryTree* currentDirectoryTree, char* permissionInfo, char* nodeName)
//DirectoryTree, 바꿀 권한값, 
{
	Permission* change_mod;
	parse_permission_info(permissionInfo, change_mod);
	DirectoryNode* temp = find_directory(currentDirectoryTree, nodeName);
	//IsExistDir로 전달할 때 파일인지 폴더인지 타입을 알려줘야 함.

	if (temp != NULL)
	{	
		printf("%s",change_mod);	//test code
		temp->permission = *change_mod;
	}

	else
	{
		printf("chmod: No such file or directory\n");
	}
}