#include "../header/main.h"
int file_num = 0;

int grep_option(DirectoryTree *dTree, char *cmd) {
    ThreadTree threadTree[MAX_BUFFER];
    pthread_t threadID[MAX_THREAD];
    
    int thread_n = 0;
    int option = 0;
    char *string;
    char *file;
    char *cmd_op;

    // grep 뒤에 입력이 없었을 경우
    if (cmd == NULL) {
        printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
        printf("Try 'grep --help' for more information.\n");
        return -1;
    }

    // 입력된 옵션 종류
    if (cmd[0] == "-") {
        cmd_op = strtok(NULL, " ");
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
            printf("General help using GNU software: <https://www.gnu.org/gethelp/>\n\n");

            return -1;
        }
        else { // 옵션 입력이 틀렸을 경우
            printf("grep: invalid option -- '%s'\n", cmd_op);
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
        file = strtok(NULL, " ");
        if (file == NULL) {
            printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
            printf("Try 'grep --help' for more information.\n");
            return -1;
        }
    }

    while(file != NULL) {
        threadTree[thread_n].threadTree = dTree;
        threadTree[thread_n].option = option;
        threadTree[thread_n].content = string;
        threadTree[thread_n].command = file;
        file = strtok(NULL, " ");
        thread_n++;
        file_num++;
    }

    // pthread 생성
    for (int i = 0; i < thread_n; i++) {
        pthread_create(&threadID[i], NULL, grep_thread, (void*)&threadTree[i]);
    }

    // 각 스레드가 종료될 때까지 대기
    for (int i = 0; i < thread_n; i++) {
        pthread_join(threadID[i], NULL);
    }

    file_num = 0;

    return 1;
}

int grep_result(int option, char* string, char* file) {
    char buffer[MAX_BUFFER];
    int num = 0;

    FILE* f = fopen(file, "r");
    while (fgets(buffer, MAX_BUFFER, f)) {
        switch (option) {
            case 0:  // 옵션 x
                if (strstr(buffer, string) != NULL) {
                    if (file_num > 1)
                        printf("%s:", file);
                    printf("%s", buffer);
                }
                break;

            case 1:  // -n
                if (strstr(buffer, string) != NULL) {
                    if (file_num > 1)
                        printf("%s:", file);
                    printf("%d:%s", num, buffer);
                }
                break;

            case 2:  // -v
                if (strstr(buffer, string) == NULL) {
                    if (file_num > 1)
                        printf("%s:", file);
                    printf("%s", buffer);
                }
                break;

            case 3:  // -i
                if (strcasestr(buffer, string) != NULL) {
                    if (file_num > 1)
                        printf("%s:", file);
                    printf("%s", buffer);
                }
                break;

            case 4:  // nv, vn 옵션
                if (strstr(buffer, string) == NULL) {
                    if (file_num > 1)
                        printf("%s:", file);
                    printf("%d:%s", num, buffer);
                }
                break;

            case 5:  // -ni, -in
                if (strcasestr(buffer, string) != NULL) {
                    if (file_num > 1)
                        printf("%s:", file);
                    printf("%d:%s", num, buffer);
                }
                break;

            case 6:  // -vi, -iv
                if (strcasestr(buffer, string) == NULL) {
                    if (file_num > 1)
                        printf("%s:", file);
                    printf("%s", buffer);
                }
                break;

            case 7:  // -nvi, -niv, -vni, -vin, inv, ivn
                if (strcasestr(buffer, string) == NULL) {
                    if (file_num > 1)
                        printf("%s:", file);
                    printf("%d:%s", num, buffer);
                }
                break;

            default:
                printf("Invalid option\n");
                break;
        }
        num++;
    }

    fclose(f);

    return 0;
}

void *grep_thread(void* arg) {
    ThreadTree* threadTree = (ThreadTree*)arg;

    int option = threadTree->option;
    char* string = threadTree->content;
    char* file = threadTree->command;

    int check = checkfile(file);
    if (check == 0) {            //파일 또는 디렉토리가 없을 경우
        printf("grep: %s: No such file or directory\n", file);
        return NULL;
    }
    else if (check == 2) {       //디렉일 경우
        printf("grep: %s: Is a directory\n", file);
        return NULL;
    }
    else if (check == 1 && fileAccessCheck(file)) { //허가권한이 거부될 경우
        printf("grep: %s: Permission denied\n", file);
        return NULL;
    }
    else
        grep_result(option, string, file);

    pthread_exit(NULL);
}