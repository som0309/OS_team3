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

void clear_permissions(Permission* change_mod) {
    for (int i = 0; i < 9; ++i) {
        change_mod->permission[i] = 0;
    }
}

void apply_absolute_mode(Permission* change_mod, const char* permissionInfoStr) {
    int mode = atoi(permissionInfoStr);
    change_mod->mode = mode;
    // Initialize all permissions to 0
    for (int i = 0; i < 9; ++i) {
        change_mod->permission[i] = 0;
    }

    for (int i = 9; i >= 0; --i) {
        change_mod->permission[i] = mode % 2;
        mode /= 2;
    }
}

void apply_relative_mode(Permission* change_mod, const char* permissionInfoStr) {
    int len = strlen(permissionInfoStr);
    int op = 0; // 1 for '+', -1 for '-', 0 for '='

    for (int i = 0; i < len; ++i) {
        switch (permissionInfoStr[i]) {
            case '+': op = 1; break;
            case '-': op = -1; break;
            case '=': op = 0; clear_permissions(change_mod); break;
            case 'r':
                for (int j = 0; j < 9; j += 3) change_mod->permission[j] = op >= 0 ? 1 : 0;
                break;
            case 'w':
                for (int j = 1; j < 9; j += 3) change_mod->permission[j] = op >= 0 ? 1 : 0;
                break;
            case 'x':
                for (int j = 2; j < 9; j += 3) change_mod->permission[j] = op >= 0 ? 1 : 0;
                break;
        }
    }
}

int parse_permission_info(char* permissionInfo, Permission* change_mod) {
    if (strchr(permissionInfo, '+') != NULL || strchr(permissionInfo, '-') != NULL || strchr(permissionInfo, '=') != NULL) {
        apply_relative_mode(change_mod, permissionInfo);
        return SUCCESS;
    } else if (permissionInfo[0] - '0' < 8 && permissionInfo[1] - '0' < 8 && permissionInfo[2] - '0' < 8 && strlen(permissionInfo) == 3) {
        apply_absolute_mode(change_mod, permissionInfo);
        return SUCCESS;
    }
    else {
        printf("chmod: Invalid Mode: \'%s\'\n", permissionInfo);
        printf("Try \'chmod --help\' for more information.\n");
        return ERROR;
    }
}

void ch_mod(DirectoryTree* currentDirectoryTree, char* permissionInfo, char* nodeName)
//DirectoryTree, 바꿀 권한값, 
{   
	Permission* change_mod = (Permission*)malloc(sizeof(Permission));
    if (!strcmp(permissionInfo, "--help")){
            printf("Usage: chmod [OPTION]... OCTAL-MODE FILE...\n");
            printf("Change the mode of each FILE to MODE.\n\n");
            printf("  Options:\n");
            printf("  -R, --recursive        change files and directories recursively\n");
            printf("      --help     Display this help and exit\n");
            return;
    }
	if(parse_permission_info(permissionInfo, change_mod)) return;
    
	DirectoryNode* temp = find_directory(currentDirectoryTree, nodeName);
	//IsExistDir로 전달할 때 파일인지 폴더인지 타입을 알려줘야 함.
	if (temp != NULL)
	{	
		temp->permission = *change_mod;
	}

	else
	{
		printf("chmod: No such file or directory\n");
	}
}