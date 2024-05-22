#include "../header/main.h"

char* catInterface(DirectoryTree* currentDirectoryTree, char* var){
    
        // -n 옵션 및 > 'filename' 옵션을 확인
        int numberFlag = 0; // -n 옵션 여부. 줄번호 출력 여부.
        char *redirectFilename = NULL;      // 만들려는 파일 이름 
        if (var != NULL && !strcmp(var, "-n"))
        {
            numberFlag = 1;
            var = strtok(NULL, " ");
        }
        if (var != NULL && var[0] == '>')
        {
            redirectFilename = var + 2; // '>' 다음 문자열을 파일명으로 설정
            var = strtok(NULL, " ");
        }

        if (var != NULL)
        {
            printf("READ");
            cat(currentDirectoryTree, var, numberFlag, redirectFilename);
        }
        else
        {
            printf("Usage: cat [-n] [filename] [> 'filename']\n");
        }

        return var;
}

void cat(DirectoryTree *currentDirectoryTree, char *filename, int numberFlag, char *redirectFilename)
{
    FILE *file;
    char line[256];
    int lineNumber = 1;
// > 'filename' 옵션이 설정되었을 경우 출력을 지정된 파일로 리다이렉션
    if (redirectFilename != NULL)
    {
        FILE *redirectFile = fopen(redirectFilename, "w");
        if (redirectFile == NULL)
        {
            printf("Error: Cannot open file '%s' for writing\n", redirectFilename);
            fclose(file);
            return;
        }

        rewind(file); // 파일 포인터를 다시 파일의 처음으로 이동
        while (fgets(line, sizeof(line), file))
        {
            fprintf(redirectFile, "%s", line);
        }

        printf("Output redirected to file '%s'\n", redirectFilename);
        fclose(redirectFile);
    }
    else{
    // 파일을 읽기 모드로 열기
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Cannot open file '%s'\n", filename);
        return;
    }

    // -n 옵션이 설정되었을 경우 각 줄에 번호를 붙여서 출력
    if (numberFlag)
    {
        while (fgets(line, sizeof(line), file))
        {
            printf("%d %s", lineNumber, line);
            lineNumber++;
        }
    }
    else
    {
        // -n 옵션이 없으면 파일 내용을 그대로 출력
        while (fgets(line, sizeof(line), file))
        {
            printf("%s", line);
        }
    }

    fclose(file);
    }
}