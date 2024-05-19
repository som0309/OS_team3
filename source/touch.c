#include "../header/main.h"
int file_num = 0;

int touch_option(DirectoryTree *dTree, char *cmd) {
    ThreadTree threadTree[MAX_BUFFER];
    pthread_t threadID[MAX_THREAD];
    
    int thread_n = 0;
    int option = 0;
    char *time;
    char *file;
    char *cmd_op;

    // touch 뒤에 입력이 없었을 경우
    if (cmd == NULL) {
        printf("touch: missing file operand\n");
        printf("Try 'touch --help' for more information.\n");
        return -1;
    }

    // 입력된 옵션 종류
    if (cmd[0] == "-") {
        cmd_op = strtok(NULL, " ");
        if (strcmp(cmd_op, "-a" == 0)) {
            option = 1;
        }
        else if (strcmp(cmd_op, "-c" == 0)) {
            option = 2;
        }
        else if (strcmp(cmd_op, "-t" == 0)) {
            option = 3;
        }
        else if (strcmp(cmd_op, "-ac" == 0) || strcmp(cmd_op, "-ca" == 0)) {
            option = 4;
        }
        else if (strcmp(cmd_op, "-ct" == 0) || strcmp(cmd_op, "-tc" == 0)) {
            option = 5;
        }
        else if (strcmp(cmd_op, "-ta" == 0) || strcmp(cmd_op, "-at" == 0)) {
            option = 6;
        }
        else if (strcmp(cmd_op, "-act" == 0) || strcmp(cmd_op, "-atc" == 0) || strcmp(cmd_op, "-cat" == 0) || strcmp(cmd_op, "-cta" == 0) || strcmp(cmd_op, "-tac" == 0) || strcmp(cmd_op, "-tca" == 0)) {
            option = 7;
        }
        else if (strcmp(cmd_op, "--help" == 0)) {
            printf("Usage: touch [OPTION]... [FILE]...\n");
            printf("Update the access and modification times of each FILE to the current time.\n\n");
            printf("A FILE argument that does not exist is created empty, unless -c\n");
            printf("is supplied.\n\n");
            printf("A FILE argument string of - is handled specially and causes touch to\n");
            printf("change the times of the file associated with standard output.\n\n");
            printf("Mandatory arguments to long options are mandatory for short options too.\n");
            printf("  -a                     change only the access time\n");
            printf("  -c, --no-create        do not create any files\n");
            printf("  -t STAMP               use [[CC]YY]MMDDhhmm[.ss] instead of current time\n");
            printf("      --time=WORD        change the specified time:\n");
            printf("                           WORD is access, atime, or use: equivalent to -a\n");
            printf("                           WORD is modify or mtime: equivalent to -m\n");
            printf("      --help     display this help and exit\n\n");
            printf("GNU coreutils online help: <https://www.gnu.org/software/coreutils/>\n");
            printf("Full documentation at: <https://www.gnu.org/software/coreutils/touch>\n");
            printf("or available locally via: info '(coreutils) touch invocation'\n\n");

            return -1;
        }
        else { // 옵션 입력이 틀렸을 경우
            printf("touch: invalid option -- '%s'\n", cmd_op);
            printf("Try 'touch --help' for more information.\n");
            return -1;
        }

        // 변경할 시간이 없거나 시간 형식이 틀렸을 경우
        if(option == 3 || option == 5 || option == 6 || option == 7) {
            time = strtok(NULL, " ");
            if (time == NULL) {
                printf("touch: option requires an argument -- 't'\n");
                printf("Try 'touch --help' for more information.\n");
                return -1;
            }
            else if (is_valid_touch_time(time)) {
                printf("touch: invalid date format '%s'\n", time);
                return -1;
            }
        }
        else { 
            time = NULL;
        }

        // 대상 파일이 없을 경우
        file = strtok(NULL, " ");
        if (file == NULL) {
            printf("touch: missing file operand");
            printf("Try 'touch --help' for more information.\n");
            return -1;
        }
    }
    else { // 옵션이 없는 경우
        // 대상 파일이 없을 경우
        file = strtok(NULL, " ");
        if (file == NULL) {
            printf("touch: missing file operand");
            printf("Try 'touch --help' for more information.\n");
            return -1;
        }
    }

    while(file != NULL) {
        threadTree[thread_n].threadTree = dTree;
        threadTree[thread_n].option = option;
        threadTree[thread_n].content = time;
        threadTree[thread_n].command = file;
        file = strtok(NULL, " ");
        thread_n++;
        file_num++;
    }

    // pthread 생성
    for (int i = 0; i < thread_n; i++) {
        pthread_create(&threadID[i], NULL, touch_thread, (void*)&threadTree[i]);
    }

    // 각 스레드가 종료될 때까지 대기
    for (int i = 0; i < thread_n; i++) {
        pthread_join(threadID[i], NULL);
    }

    file_num = 0;

    return 1;
}

void *touch_thread(void* arg) {
    ThreadTree* threadTree = (ThreadTree*)arg;

    int option = threadTree->option;
    char* t = threadTree->content;
    char* file = threadTree->command;

    int check = checkfile(file);
    if (check == 0) {            // 파일 또는 디렉토리가 없을 경우
        // 파일 생성
        int fd = open(file, O_CREAT | O_EXCL, 0664);
        if (fd == -1) {
            perror("File cannot create");
            return NULL;
        }
        close(fd);

        if (option == 3) { // -t
            // 시간 문자열을 구성하여 시간 구조체로 변환
            time_t file_time = timeSetting(t);
            // 파일의 모든 시간을 현재 시간으로 변경
            utime(file, NULL);
            // 파일의 접근 시간과 수정 시간 변경
            struct utimbuf new_times = {file_time, file_time};
            utime(file, &new_times);
        }

        if (option == 6) { // -ta, -at
            // 시간 문자열을 구성하여 시간 구조체로 변환
            time_t file_time = timeSetting(t);
            // 파일의 수정 시간 받아 옴
            struct stat file_stat;
            stat(file, &file_stat);
            // 파일의 모든 시간을 현재 시간으로 변경
            utime(file, NULL);
            // 파일의 접근 시간과 수정 시간 변경
            struct utimbuf new_times = {file_time, file_stat.st_mtime};
            utime(file, &new_times);
        }
    }
    else if (check != 0 && access(file, W_OK) == 0) { // 파일 또는 디렉토리의 메타데이터 수정이 가능한 경우
        switch (option)
        {
        case 0: // 옵션 x
        case 2: // -c
            // 파일의 모든 시간을 현재 시간으로 변경
            utime(file, NULL);
            break;
        case 1: // -a
        case 4: // -ac, -ca
            // 파일의 수정 시간 받아 옴
            struct stat file_stat;
            stat(file, &file_stat);
            // 현재 시간 가져오기
            time_t current_time= time(NULL);
            struct tm *now = localtime(&current_time);
            // 파일의 모든 시간을 현재 시간으로 변경
            utime(file, NULL);
            // 파일의 접근 시간과 수정 시간 변경
            struct utimbuf new_times = {mktime(now), file_stat.st_mtime};
            utime(file, &new_times);
            break;
        case 3: // -t
        case 5: // -ct, -tc
            // 시간 문자열을 구성하여 시간 구조체로 변환
            time_t file_time = timeSetting(t);
            // 파일의 모든 시간을 현재 시간으로 변경
            utime(file, NULL);
            // 파일의 접근 시간과 수정 시간 변경
            struct utimbuf new_times = {file_time, file_time};
            utime(file, &new_times);
            break;
        case 6: // -ta, -at
        case 7: // -act, -atc, -cat, -cta, -tac, -tca
            // 시간 문자열을 구성하여 시간 구조체로 변환
            time_t file_time = timeSetting(t);
            // 파일의 수정 시간 받아 옴
            struct stat file_stat;
            stat(file, &file_stat);
            // 파일의 모든 시간을 현재 시간으로 변경
            utime(file, NULL);
            // 파일의 접근 시간과 수정 시간 변경
            struct utimbuf new_times = {file_time, file_stat.st_mtime};
            utime(file, &new_times);
            break;
        default:
            printf("Invalid option\n");
            break;
        }
    }
    else { // 파일 또는 디렉토리의 쓰기 권한이 없을 경우
        printf("touch: cannot touch '%s': Permission denied\n", file);
        return NULL;
    }

    pthread_exit(NULL);
}