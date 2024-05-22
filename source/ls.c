#include "../header/main.h"

void chmod_print(int chmodinfo)
{
    int temp;
    int div = 100;
    int divideinfo;

    for (int i = 0; i < 3; i++) // 권한 정보 3개의 정보로 나눠짐 -> 소유자, 그룹, 다른 사용자 권한
    {
        // 한 자리수씩 나눠서 문자로 변경
        divideinfo = chmodinfo / div;
        chmodinfo = chmodinfo - divideinfo * div;
        div = div / 10;

        if (divideinfo == 0)
        {
            printf("---");
        }
        else if (divideinfo == 1)
        {
            printf("--x");
        }
        else if (divideinfo == 2)
        {
            printf("-w-");
        }
        else if (divideinfo == 3)
        {
            printf("-wx");
        }
        else if (divideinfo == 4)
        {
            printf("r--");
        }
        else if (divideinfo == 5)
        {
            printf("r-x");
        }
        else if (divideinfo == 6)
        {
            printf("rw-");
        }
        else if (divideinfo == 7)
        {
            printf("rwx");
        }
    }
    printf("\t");
}

int treePreOrder(DirectoryNode* directoryNode, int nodeNum)
{
	if (directoryNode != NULL)
	{
		nodeNum++;
		if (directoryNode->nextSibling == NULL)
		{
			nodeNum = treePreOrder(directoryNode->firstChild, nodeNum);
			nodeNum = treePreOrder(directoryNode->nextSibling, nodeNum);
		}
		else
		{
			DirectoryNode* temp = directoryNode->nextSibling;
			while (temp != NULL)
			{
				nodeNum++;
				temp = temp->nextSibling;
			}
			nodeNum = treePreOrder(directoryNode->firstChild, nodeNum);
			nodeNum = treePreOrder(directoryNode->nextSibling, nodeNum);
		}
	}
	return nodeNum;
}

int directoryLinkPrint(DirectoryNode* directoryNode)
{
	int nodeNum = 0;
	nodeNum = treePreOrder(directoryNode, 0);

	if (directoryNode->nextSibling != NULL)
	{
		DirectoryNode* temp = directoryNode->nextSibling;
		while (temp != NULL)
		{
			nodeNum--;
			if(temp->firstChild!=NULL)
			{
				DirectoryNode* newtemp = temp->nextSibling;
				while(newtemp!=NULL)
				{
					nodeNum--;
					newtemp=newtemp->firstChild;
				}
			}
			temp = temp->nextSibling;
		}
	}
	printf("%d\t", nodeNum);
}

void ls(DirectoryTree* currentDirectoryTree, char* option)  // option = 0 -> ls, option = 1 -> ls -l, option = 2 -> ls -a, option = 3 -> ls -al
{
	DirectoryNode* currentNode = currentDirectoryTree->current;
	DirectoryNode* temp;
	DirectoryNode* directory_list[MAX_DIR];		// 현재 디렉토리에 존재하는 파일이나 디렉토리를 담는 list
	int directory_num = 0;

	if (currentNode->firstChild == NULL)	// 디렉토리 안에 파일이나 다른 디렉토리가 존재하지 않으면 아무 것도 print 하지 않음
	{
		//do nothing
	}
	else  // 디렉토리 내의 정보 저장
	{
		temp = currentNode->firstChild->nextSibling;
		if (temp == NULL)
		{
			directory_list[directory_num++] = currentNode->firstChild;
		}
		else
		{
			directory_list[directory_num++] = currentNode->firstChild;

			while (temp != NULL)
			{	
				directory_list[directory_num++] = temp;
				temp = temp->nextSibling;
			}
		}
	}
	// 저장 이후에 print 옵션
	if (option == NULL)
	{
		int num = 0;
		while (num < directory_num)
		{
			if (directory_list[num]->viewType == 's'){	// 볼 수 있는 파일이면 print
				printf("%s ", directory_list[num]->name);
			}
			num++;
		}
		printf("\n");
	}
	else if (!strcmp(option, "-l"))		// ls -l => 파일이나 디렉토리의 세부 정보 표시
	{
		int num = 0;
		while (num < directory_num)
		{
			// 권한 정보 print
			if (directory_list[num]->viewType == 's' && directory_list[num]->type == 'd')
			{
				printf("d");	// 디렉토리이므로 d
				chmod_print(directory_list[num]->permission.mode);	// 권한 정보
				directoryLinkPrint(directory_list[num]);	// 링크 수
				printf("4096\t");	// 디렉토리 크기 . 디렉토리 크기 항상 4096bytes (4KB)
				// 생성 날짜 정보 print
				int month = directory_list[num]->date.month + 1;
				int day = directory_list[num]->date.day;
				int hour = directory_list[num]->date.hour;
				int minute = directory_list[num]->date.minute;
				int second = directory_list[num]->date.second;
				printf("month: %d\tday: %d\t%02d:%02d:%02d\t", month, day, hour, minute, second);
				printf("%s\n", directory_list[num]->name);		// 디렉토리 이름
			}
			else if (directory_list[num]->viewType == 's' && directory_list[num]->type == '-')
			{
				printf("-");		// file이므로 -
				chmod_print(directory_list[num]->permission.mode);
				printf("1\t");  // 파일 안에 있는 정보 수 -> 파일의 링크 수
				printf("%d\t", sizeof(directory_list[num]->SIZE));		// 파일 크기
				// 생성 날짜 정보 print
				int month = directory_list[num]->date.month + 1;
				int day = directory_list[num]->date.day;
				int hour = directory_list[num]->date.hour;
				int minute = directory_list[num]->date.minute;
				int second = directory_list[num]->date.second;
				printf("month: %d\tday: %d\t%02d:%02d:%02d\t", month, day, hour, minute, second);
				printf("%s\n", directory_list[num]->name);
			}
			num++;
		}
		printf("\n");
	}
	else if (!strcmp(option, "-a"))		// ls -a => 숨김 속성을 가진 파일까지 모두 표시
	{
		int num = 0;
		while (num < directory_num)
		{
			printf("%s ", directory_list[num]->name);
			num++;
		}
		printf("\n");
	}
	else if (!strcmp(option, "-al") || !strcmp(option, "-la"))		// option == 3 => ls -al => 숨김 속성을 가진 파일의 세부 정보까지 모두 표시
	{
		int num = 0;
		while (num < directory_num)
		{
      if (directory_list[num]->type == 'd')
      {
        printf("d");	// 디렉토리이므로 d
				chmod_print(directory_list[num]->permission.mode);	// 권한 정보
				directoryLinkPrint(directory_list[num]);	// 링크 수
				printf("4096\t");	// 디렉토리 크기 -> 디렉토리 크기 항상 4096bytes (4KB)
				// 생성 날짜 정보 print
				int month = directory_list[num]->date.month + 1;
				int day = directory_list[num]->date.day;
				int hour = directory_list[num]->date.hour;
				int minute = directory_list[num]->date.minute;
				int second = directory_list[num]->date.second;
				printf("month: %d\tday: %d\t%02d:%02d:%02d\t", month, day, hour, minute, second);
				printf("%s\n", directory_list[num]->name);		// 디렉토리 이름
      }
      else if (directory_list[num]->type == '-')
      {
        printf("-");		// file이므로 -
        chmod_print(directory_list[num]->permission.mode);
        printf("1\t");  // 파일 안에 있는 정보 수 -> 파일의 링크 수
        printf("%d\t", sizeof(directory_list[num]->SIZE));		// 파일 크기
        // 생성 날짜 정보 print
        int month = directory_list[num]->date.month + 1;
				int day = directory_list[num]->date.day;
				int hour = directory_list[num]->date.hour;
				int minute = directory_list[num]->date.minute;
				int second = directory_list[num]->date.second;
				printf("month: %d\tday: %d\t%02d:%02d:%02d\t", month, day, hour, minute, second);
        printf("%s\n", directory_list[num]->name);
      }
			num++;
		}
		printf("\n");
	}
	else{
		printf("%s\n", option);
		printf("Invalid option. Please check the options and try again\n");	
	}
}