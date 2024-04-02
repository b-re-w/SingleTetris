/* Coded with C Grammar for MSVC in Windows
   This Source uses UTF-8-BOM encoding & CRLF (Windows) line endings
   Alias : SingleTetris - Tetris.c & Last Moded : 2019.07.08.
   테트리스를 구성하는 함수들을 정의
*/

#include "../include/Tetris.h"
#include "../include/WinAPI.h"

void showStart(int count) {
    system("TITLE 1인용 테트리스");  // 콘솔 타이틀 설정
    hideConsoleCursor(HIDE);  // 콘솔 커서 숨기기
    system("cls");  // 콘솔 clear
    for (; count > 0; count--) {  // count 만큼 반복
        gotoxy(8, 5); printf("%d초 후 게임을 시작합니다.!!!", count);
        Sleep(1000);  // 1초 동안 연산 안함
    }
    while (_kbhit()) {  // 대기 화면 동안 입력된 키를 제거
        char trash = _getch();
    }
    system("cls");  // 콘솔 clear
}

void contructWall(_Bool (* struct_board)[XSIZ]) {
    for (int i = 0; i < YSIZ-1; i++) {
        struct_board[i][0] = 1;  // 왼쪽 벽 생성
        struct_board[i][XSIZ-1] = 1;  // 오른쪽 벽 생성
    }
    for (int j = 0; j < XSIZ; j++) {
        struct_board[YSIZ-1][j] = 1;  // 바닥 생성
    }
}

void getNewShape(struct object_info * objstat) {
    static _Bool first_time = 1;  // 함수 최초 실행 때만
    if (first_time) {
        srand((unsigned int)time(NULL));  // 난수 생성 초기값 입력
        first_time--;
    }
    while (1) {
        objstat->color = rand()%15;  // 참고 : https://m.blog.naver.com/PostView.nhn?blogId=wcwtmt&logNo=10172917569&proxyReferer=https%3A%2F%2Fwww.google.com%2F
        if (objstat->color != 0 && objstat->color != 7 && objstat->color != 8) {
            break;
        }
    }  // 랜덤 색상, 0~15(진한흰색 제외를 위해 14까지), 검정색(0)+흰색(7)+회색(8)+진한흰색(15) 제외
    objstat->shape = rand()%SHAPENUM;  // 랜덤 모양, 0~5
    objstat->dir = rand()%SHAPEDIR;  // 랜덤 방향, 0~3
    objstat->y = 3;  // y좌표 초기화
    objstat->x = 0;  // x좌표 이동값 초기화
}

void buildBoard(_Bool (* target_board)[XSIZ], struct object_info * objstat, _Bool const reset) {
    if (reset) { // reset 인수가 1일때만 초기화 실행
        memset(target_board, 0x00, sizeof(_Bool)*YSIZ*XSIZ); // 초기화
    }
    for (int i = (objstat->y < YSIZ) ? (objstat->y) : (YSIZ-1), ii = (objstat->y < YSIZ) ? (3) : (YSIZ+2-objstat->y); i < YSIZ && i >= 0 && ii >= 0; i--, ii--) {
        for (int j = 0; j < 4; j++) {
            if (ttshape[objstat->shape][(objstat->dir)%SHAPEDIR][ii][j]) { // 값이 있으면
                target_board[i][ttshape[objstat->shape][(objstat->dir)%SHAPEDIR][ii][j]+objstat->x] = 1; // 이동된 x 좌표 반영
            }
        }
    }
}

_Bool letObjMove(_Bool (* struct_board)[XSIZ], struct object_info * objstat, int const where_to_move) {
    // 0. 선언 및 초기화
    _Bool object_board[YSIZ][XSIZ] = {{0}}; // 객체 저장용 배열
    struct object_info objtmp = {
        objstat->color,
        objstat->shape,
        objstat->dir,
        objstat->y,
        objstat->x
    };  // 객체 상태 저장용 임시 구조체

    // 1. 객체 상태 임시 변경
    switch (where_to_move) {
        case LEFT:
            (objtmp.x)--;  // 임시 x 감소
            break;
        case RIGHT:
            (objtmp.x)++;  // 임시 x 증가
            break;
        case UP:
            (objtmp.dir)++;  // 임시 방향 변경
            break;
        case DOWN:
            (objtmp.y)++;  // 임시 y 증가
            break;
    }

    // 2. 충돌 검사 및 실제 적용
    buildBoard(object_board, &objtmp, RESET);  // 충돌 검사를 위한 객체 배열 생성
    if (checkCrash(struct_board, object_board)) {  // 충돌 발생시 변화 적용 안함
        return 1;
    } else {  // 충돌 미 발생시 변화 적용
        objstat->dir = objtmp.dir;
        objstat->y = objtmp.y;
        objstat->x = objtmp.x;
    }
    return 0;
}

_Bool checkCrash(_Bool const (* struct_board)[XSIZ], _Bool const (* object_board)[XSIZ]) {
    for (int i = 0; i < YSIZ; i++) {
        for (int j = 0; j < XSIZ; j++) {
            if (struct_board[i][j] && object_board[i][j]) {  // 앤드 연산으로 모두 1인 값 찾기
                return 1;
            }
        }
    }
    return 0;
}

void printGameBoard(_Bool const (* struct_board)[XSIZ], struct object_info * objstat, int const ylimit) {
    _Bool object_board[YSIZ][XSIZ] = {{0}};  // 객체 저장용 배열
    int player = 0, you = 0;  // 멀티 플레이화 대비용 변수

    buildBoard(object_board, objstat, RESET);  // 게임 출력을 쉽게 하기 위한 객체 배열 생성
    hideConsoleCursor(HIDE);  // 콘솔 커서 숨기기

    // 출력
    for (int i = 0; i < YSIZ-1; i++) {
        gotoxy(5+34*player, i+2);
        if (i == ylimit) {
            printf("▶");  // 왼쪽 상한선 표시
        } else {
            printf("▩");  // 왼쪽 벽 표시
        }
        for (int j = 1; j < XSIZ-1; j++) {
            if (struct_board[i][j] && !object_board[i][j]) {
                printf("■");
            } else if (struct_board[i][j] || object_board[i][j]) {
                changeObjColor(objstat->color); printf("■"); changeObjColor(7);
            } else {
                printf("  ");
            }
        }
        if (i == ylimit) {
            printf("◀");  // 오른쪽 상한선 표시
        } else {
            printf("▩");  // 오른쪽 벽 표시
        }
    }
    gotoxy(5+34*player, YSIZ+1);
    for (int i = 0; i < XSIZ; i++) {
        printf("▩");
    }
    gotoxy(5+34*player, YSIZ+3); printf("PLAYER %d", player+1);
    if (player == you) {
        printf("(YOU)");
    }
}

void checkLineFull(_Bool (* struct_board)[XSIZ]) {
    int max_line = 0;
    for (int i = YSIZ-2, count = 0; i >= 0; i--) {  // 맨 아래줄 제외하고 아래쪽부터 확인
        for (int j = 1; j < XSIZ-1; j++) {
            if (struct_board[i][j]) {
                if (++count == XSIZ-2) {
                    max_line++;  // 찾으면 카운트 증가
                }
            }
        }
        count = 0;
        }
        while (max_line) {
            for (int i = YSIZ-2, count = 0; i >= 0; i--) {  // 맨 아래줄 제외하고 아래쪽부터 제거
                for (int j = 1; j < XSIZ-1; j++) {
                    if (struct_board[i][j]) {
                        if (++count == XSIZ-2) {
                            max_line--;
                            for (int ii = i; ii > 0; ii--) {  // 한줄 제거하고 내리기
                                for (int jj = 1; jj < XSIZ-1; jj++) {
                                    struct_board[ii][jj] = struct_board[ii-1][jj];
                                }
                            }
                        for (int jj = 1; jj < XSIZ-1; jj++) {
                            struct_board[0][jj] = 0;
                        }
                    }
                }
            }
            count = 0;
        }
    }
}

_Bool checkGameOver(_Bool const (* struct_board)[XSIZ], int const ylimit) {
    for (int i = 1; i < XSIZ-1; i++) {
        if (struct_board[ylimit][i]) {  // 상한선 부분에 1이 있는지 확인
            return 1;
        }
    }
    return 0;
}

void showTetrisResult(char const * argv0) {
    // 1.종료 표시
    hideConsoleCursor(SHOW);  // 콘솔 커서 보이기
    gotoxy(40, 5); printf("GAME OVER ㅠㅠㅠ");
    gotoxy(40, 7); printf("게임을 종료하려면 0을 다시 시작하려면 1을 눌러주세요^^");
    // 2.재시작 확인
    while (1) {
        char input = _getch();
        static char cmd_buff[50] = {0};
        if (input == '0') {
            break;  // 0 입력시 종료
        } else if (input == '1') {
            sprintf(cmd_buff, "start \"%s\"", argv0);
            system(cmd_buff);
            break;
        }
    }
}
