#include "header/main.h"

int grep_n = 0; // 필요성 확인!!!

int grep_option(DirectoryTree *dTree, char *cmd) {
    int thread_n = 0;
    ThreadTree threadTree[MAX_NAME]; // 여기도!!!
    pthread_t threadArr[MAX_NAME]; // 여기도!!!

    char *command = cmd;
    char *string;
    char *file;
    char f[MAX_NAME]; // 물어보기!!!
    int option = 0;

    // grep 뒤에 입력이 없었을 경우
    if (cmd == NULL) {
        printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
        printf("Try 'grep --help' for more information.\n");
        return -1;
    }

    // 입력된 옵션 종류
    if (cmd[0] == "-") {
        char *cmd_op = strtok(NULL, " ");
        if (strcmp(cmd_op, "-n" == 0)) {
            option = 1;
        }
        else if (strcmp(cmd_op, "-v" == 0)) {
            option = 2;
        }
        else if (strcmp(cmd_op, "-i" == 0)) {
            option = 3;
        }
        else if (strcmp(cmd_op, "-nv" == 0) || strcmp(cmd_op, "-vn" == 0)) {
            option = 4;
        }
        else if (strcmp(cmd_op, "-vi" == 0) || strcmp(cmd_op, "-iv" == 0)) {
            option = 5;
        }
        else if (strcmp(cmd_op, "-in" == 0) || strcmp(cmd_op, "-ni" == 0)) {
            option = 6;
        }
        else if (strcmp(cmd_op, "-nvi" == 0) || strcmp(cmd_op, "-niv" == 0) || strcmp(cmd_op, "-vni" == 0) || strcmp(cmd_op, "-vin" == 0) || strcmp(cmd_op, "-inv" == 0) || strcmp(cmd_op, "-ivn" == 0)) {
            option = 7;
        }
        else if (strcmp(cmd_op, "--help" == 0)) {
            printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
            printf("Search for PATTERNS in each FILE.\n");
            printf("Example: grep -i 'hello world' menu.h main.c\n\n");
            printf("Pattern selection and interpretation:\n");
            printf("  -i, --ignore-case         ignore case distinctions in patterns and data\n");
            printf("      --no-ignore-case do not ignore case distinctions (default)\n\n");
            printf("Miscellaneous:\n");
            printf("  -v, --invert-match        select non-matching lines\n\n");
            printf("Output control:\n");
            printf("  -n, --line-number         print line number with output lines\n");
            printf("      --line-buffered\t flush output on every line\n\n");
            printf("Report bugs to: bug-grep@gnu.org\n");
            printf("GNU grep home page: <https://www.gnu.org/software/grep/>\n");
            printf("General help using GNU software: <https://www.gnu.org/gethelp/>\n");

            return -1;
        }
        else { // 옵션 입력이 틀렸을 경우
            printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
            printf("Try 'grep --help' for more information.\n");
            return -1;
        }

        // 찾을 문자열이 없을 경우
        string = strtok(NULL, " ");
        if (string == NULL) {
            printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
            printf("Try 'grep --help' for more information.\n");
            return -1;
        }

        // 대상 파일이 없을 경우
        strncpy(f, cmd, MAX_NAME); // 요기도!!! 필요성 확인 
        file = strtok(NULL, " ");
        if (file == NULL) {
            printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
            printf("Try 'grep --help' for more information.\n");
            return -1;
        }
    }
    else { // 옵션이 없는 경우
        // 찾을 문자열이 없을 경우
        string = strtok(NULL, " ");
        if (string == NULL) {
            printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
            printf("Try 'grep --help' for more information.\n");
            return -1;
        }

        // 대상 파일이 없을 경우
        strncpy(f, cmd, MAX_NAME); // 요기도!!! 필요성 확인
        file = strtok(NULL, " ");
        if (file == NULL) {
            printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
            printf("Try 'grep --help' for more information.\n");
            return -1;
        }
    }

    while(file != NULL) {
        threadTree[thread_n].threadTree = dTree; // 여기 살펴보기!!!
        threadTree[thread_n].option = option;
        threadTree[thread_n].content = string;
        threadTree[thread_n].cmd = file;
        file = strtok(NULL, " ");
        thread_n++;
        grep_n++; // 여기도 확인!!!
    }

    for (int i = 0; i < thread_n; i++) {       //pthread생성 후 cat_thread로 처리, 마지막으로 join
        pthread_create(&threadArr[i], NULL, grep_thread, (void*)&threadTree[i]); // 다시 확인...
        pthread_join(threadArr[i], NULL);
    }

    grep_n = 0;
    return 1;
}

int grep_result(DirectoryTree* dTree,  int option, char* string, char* file) {
    FILE* f;
    char buffer[MAX_NAME]; // 체크!!!
    int count = 1;

    f = fopen(file, "r");
    while (feof(f) == 0) {
        fgets(buffer, sizeof(buffer), f);
        if (feof(f) != 0) {
            break;
        }   //옵션에 따라 프린트
        else if (option == 0)    //옵션 x
        {
            if (strstr(buffer, string) != NULL)
            {
                if (grep_n > 1)
                    printf("%s:", file);
                printf("%s", buffer);
            }
        
        else if (option == 1)    // -n
        {
            if (strstr(buffer, string) != NULL)
            {
                if (grep_n > 1)
                    printf("%s:", file);
                printf("%d:%s", count, buffer);
            }
        }
        else if (option == 2)    // -v
        {
            if (strstr(buffer, string) == NULL)
            {
                if (grep_n > 1)
                    printf("%s:", file);
                printf("%s", buffer);
            }
        }
        else if (option == 3)    // -i 
        {
            if (strcasestr(buffer, string) != NULL)
            {
                if (grep_n > 1)
                    printf("%s:", file);
                printf("%s", buffer);
            }
        }
        else if (option == 4)    //nv, vn 옵션
        {
            if (strstr(buffer, string) == NULL)
            {
                if (grep_n > 1)
                    printf("%s:", file);
                printf("%d:%s", count, buffer);
            }
        }
        else if (option == 5)    // -ni, -in
        {
            if (strcasestr(buffer, string) != NULL)
            {
                if (grep_n > 1)
                    printf("%s:", file);
                printf("%d:%s", count, buffer);
            }
        }
        else if (option == 6)    // -vi, -iv
        {
            if (strcasestr(buffer, string) == NULL)
            {
                if (grep_n > 1)
                    printf("%s:", file);
                printf("%s", buffer);
            }
        }
        else if (option == 7) {      // -nvi, -niv, -vni, -vin, inv, ivn
            if (strcasestr(buffer, string) == NULL)
            {
                if (grep_n > 1)
                    printf("%s:", file);
                printf("%d:%s", count, buffer);
            }
        }
        count++;
    }
    fclose(f);
    return 0;
}

void *grep_thread(void* arg) {
    ThreadTree* threadTree = (ThreadTree*)arg;
    DirectoryTree* dTree = threadTree->threadTree;
    DirectoryNode* currentNode = dTree->current;
    int option = threadTree->option;
    char* string = threadTree->content;
    char* file = threadTree->command;

    DirectoryNode* check1 = NULL;
    DirectoryNode* check2 = NULL;

    char tmp[MAX_DIR];

    int check_exist;
    char *dir;

    if (strstr(file, "/") == NULL) {     // 해당 디렉에 포함되는 파일 또는 디렉
        check1 = IsExistDir(dTree, file, 'f'); // 여기는 직접 짜야 될 듯...
        check2 = IsExistDir(dTree, file, 'd'); // 여기는 직접 짜야 될 듯...
        if (check1 == NULL && check2 == NULL) {      //파일 또는 디렉토리가 없을 경우
            printf("grep: %s: No such file or directory.\n", file);
            return NULL;
        }
        else if (check1 == NULL && check2 != NULL) {     //디렉일 경우
            printf("grep: %s: Is a directory\n", file);
            return NULL;
        }
        else if (check1 != NULL && HasPermission(check1, 'r') != 0) { //허가권한이 거부될 경우 => 여기도 짜야 될 것 같아요...
            printf("grep: Can not open file %s: Permission denied\n", check1->name);
            return NULL;
        }
        else
            grep_print(dTree, option, string, file);
    }
    else { //다른 디렉토리의 파일이나 디렉토리일 경우
        check_exist = MovePath(dTree, file); // 요것도 확인...
        if (check_exist) {
            printf("grep: %s: No such file or directory.\n", file);
            return NULL;
        }
        dir = strtok(file, "/");
        while (dir != NULL) {
            strncpy(tmp, dir, MAX_NAME);
            dir = strtok(NULL, "/");
        }
        check1 = IsExistDir(dirTree, tmp, 'f');
        check2 = IsExistDir(dirTree, tmp3, 'd');
        if (check1 == NULL && check2 == NULL) {      //파일 또는 디렉토리가 존재하지 않을 경우
            printf("grep: %s: No such file or directory.\n", tmp);
            dTree->current = currentNode;
            return NULL;
        }
        else if (check1 == NULL && check2 != NULL) {     //디렉토리일 경우
            printf("grep: %s: Is a directory\n", tmp);
            dTree->current = currentNode;
            return NULL;
        }
        else if (check1 != NULL && HasPermission(check1, 'r') != 0) {       //허가권한이 거부될 경우
            printf("grep: Can not open file %s: Permission denied\n", check1->name);
            dTree->current = currentNode;
            return NULL;
        }
        else
            grep_print(dTree, option, string, file);
        dTree->current = currentNode;
    }
    pthread_exit(NULL);
}