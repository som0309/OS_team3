#include "../header/main.h"

// 현재 경로를 출력해야 하므로 DirectoryTree로 파일 시스템에 접근할 수 있어야 하고
// 현재 파일 경로까지 탐색해야 하므로 root부터 현재 위치까지 Stack에 넣은 후 다시 Pop한다.
// Stack을 사용하는 이유는 현재 경로를 root부터 출력하기 위함이다.