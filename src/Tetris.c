/* Coded with C Grammar for MSVC in Windows
   This Source uses UTF-8-BOM encoding & CRLF (Windows) line endings
   Alias : SingleTetris - Tetris.c & Last Moded : 2019.07.08.
   ��Ʈ������ �����ϴ� �Լ����� ����
*/

#include "../include/Tetris.h"
#include "../include/WinAPI.h"

void showStart(int count) {
    system("TITLE 1�ο� ��Ʈ����");  // �ܼ� Ÿ��Ʋ ����
    hideConsoleCursor(HIDE);  // �ܼ� Ŀ�� �����
    system("cls");  // �ܼ� clear
    for (; count > 0; count--) {  // count ��ŭ �ݺ�
        gotoxy(8, 5); printf("%d�� �� ������ �����մϴ�.!!!", count);
        Sleep(1000);  // 1�� ���� ���� ����
    }
    while (_kbhit()) {  // ��� ȭ�� ���� �Էµ� Ű�� ����
        char trash = _getch();
    }
    system("cls");  // �ܼ� clear
}

void contructWall(_Bool (* struct_board)[XSIZ]) {
    for (int i = 0; i < YSIZ-1; i++) {
        struct_board[i][0] = 1;  // ���� �� ����
        struct_board[i][XSIZ-1] = 1;  // ������ �� ����
    }
    for (int j = 0; j < XSIZ; j++) {
        struct_board[YSIZ-1][j] = 1;  // �ٴ� ����
    }
}

void getNewShape(struct object_info * objstat) {
    static _Bool first_time = 1;  // �Լ� ���� ���� ����
    if (first_time) {
        srand((unsigned int)time(NULL));  // ���� ���� �ʱⰪ �Է�
        first_time--;
    }
    while (1) {
        objstat->color = rand()%15;  // ���� : https://m.blog.naver.com/PostView.nhn?blogId=wcwtmt&logNo=10172917569&proxyReferer=https%3A%2F%2Fwww.google.com%2F
        if (objstat->color != 0 && objstat->color != 7 && objstat->color != 8) {
            break;
        }
    }  // ���� ����, 0~15(������� ���ܸ� ���� 14����), ������(0)+���(7)+ȸ��(8)+�������(15) ����
    objstat->shape = rand()%SHAPENUM;  // ���� ���, 0~5
    objstat->dir = rand()%SHAPEDIR;  // ���� ����, 0~3
    objstat->y = 3;  // y��ǥ �ʱ�ȭ
    objstat->x = 0;  // x��ǥ �̵��� �ʱ�ȭ
}

void buildBoard(_Bool (* target_board)[XSIZ], struct object_info * objstat, _Bool const reset) {
    if (reset) { // reset �μ��� 1�϶��� �ʱ�ȭ ����
        memset(target_board, 0x00, sizeof(_Bool)*YSIZ*XSIZ); // �ʱ�ȭ
    }
    for (int i = (objstat->y < YSIZ) ? (objstat->y) : (YSIZ-1), ii = (objstat->y < YSIZ) ? (3) : (YSIZ+2-objstat->y); i < YSIZ && i >= 0 && ii >= 0; i--, ii--) {
        for (int j = 0; j < 4; j++) {
            if (ttshape[objstat->shape][(objstat->dir)%SHAPEDIR][ii][j]) { // ���� ������
                target_board[i][ttshape[objstat->shape][(objstat->dir)%SHAPEDIR][ii][j]+objstat->x] = 1; // �̵��� x ��ǥ �ݿ�
            }
        }
    }
}

_Bool letObjMove(_Bool (* struct_board)[XSIZ], struct object_info * objstat, int const where_to_move) {
    // 0. ���� �� �ʱ�ȭ
    _Bool object_board[YSIZ][XSIZ] = {{0}}; // ��ü ����� �迭
    struct object_info objtmp = {
        objstat->color,
        objstat->shape,
        objstat->dir,
        objstat->y,
        objstat->x
    };  // ��ü ���� ����� �ӽ� ����ü

    // 1. ��ü ���� �ӽ� ����
    switch (where_to_move) {
        case LEFT:
            (objtmp.x)--;  // �ӽ� x ����
            break;
        case RIGHT:
            (objtmp.x)++;  // �ӽ� x ����
            break;
        case UP:
            (objtmp.dir)++;  // �ӽ� ���� ����
            break;
        case DOWN:
            (objtmp.y)++;  // �ӽ� y ����
            break;
    }

    // 2. �浹 �˻� �� ���� ����
    buildBoard(object_board, &objtmp, RESET);  // �浹 �˻縦 ���� ��ü �迭 ����
    if (checkCrash(struct_board, object_board)) {  // �浹 �߻��� ��ȭ ���� ����
        return 1;
    } else {  // �浹 �� �߻��� ��ȭ ����
        objstat->dir = objtmp.dir;
        objstat->y = objtmp.y;
        objstat->x = objtmp.x;
    }
    return 0;
}

_Bool checkCrash(_Bool const (* struct_board)[XSIZ], _Bool const (* object_board)[XSIZ]) {
    for (int i = 0; i < YSIZ; i++) {
        for (int j = 0; j < XSIZ; j++) {
            if (struct_board[i][j] && object_board[i][j]) {  // �ص� �������� ��� 1�� �� ã��
                return 1;
            }
        }
    }
    return 0;
}

void printGameBoard(_Bool const (* struct_board)[XSIZ], struct object_info * objstat, int const ylimit) {
    _Bool object_board[YSIZ][XSIZ] = {{0}};  // ��ü ����� �迭
    int player = 0, you = 0;  // ��Ƽ �÷���ȭ ���� ����

    buildBoard(object_board, objstat, RESET);  // ���� ����� ���� �ϱ� ���� ��ü �迭 ����
    hideConsoleCursor(HIDE);  // �ܼ� Ŀ�� �����

    // ���
    for (int i = 0; i < YSIZ-1; i++) {
        gotoxy(5+34*player, i+2);
        if (i == ylimit) {
            printf("��");  // ���� ���Ѽ� ǥ��
        } else {
            printf("��");  // ���� �� ǥ��
        }
        for (int j = 1; j < XSIZ-1; j++) {
            if (struct_board[i][j] && !object_board[i][j]) {
                printf("��");
            } else if (struct_board[i][j] || object_board[i][j]) {
                changeObjColor(objstat->color); printf("��"); changeObjColor(7);
            } else {
                printf("  ");
            }
        }
        if (i == ylimit) {
            printf("��");  // ������ ���Ѽ� ǥ��
        } else {
            printf("��");  // ������ �� ǥ��
        }
    }
    gotoxy(5+34*player, YSIZ+1);
    for (int i = 0; i < XSIZ; i++) {
        printf("��");
    }
    gotoxy(5+34*player, YSIZ+3); printf("PLAYER %d", player+1);
    if (player == you) {
        printf("(YOU)");
    }
}

void checkLineFull(_Bool (* struct_board)[XSIZ]) {
    int max_line = 0;
    for (int i = YSIZ-2, count = 0; i >= 0; i--) {  // �� �Ʒ��� �����ϰ� �Ʒ��ʺ��� Ȯ��
        for (int j = 1; j < XSIZ-1; j++) {
            if (struct_board[i][j]) {
                if (++count == XSIZ-2) {
                    max_line++;  // ã���� ī��Ʈ ����
                }
            }
        }
        count = 0;
        }
        while (max_line) {
            for (int i = YSIZ-2, count = 0; i >= 0; i--) {  // �� �Ʒ��� �����ϰ� �Ʒ��ʺ��� ����
                for (int j = 1; j < XSIZ-1; j++) {
                    if (struct_board[i][j]) {
                        if (++count == XSIZ-2) {
                            max_line--;
                            for (int ii = i; ii > 0; ii--) {  // ���� �����ϰ� ������
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
        if (struct_board[ylimit][i]) {  // ���Ѽ� �κп� 1�� �ִ��� Ȯ��
            return 1;
        }
    }
    return 0;
}

void showTetrisResult(char const * argv0) {
    // 1.���� ǥ��
    hideConsoleCursor(SHOW);  // �ܼ� Ŀ�� ���̱�
    gotoxy(40, 5); printf("GAME OVER �ФФ�");
    gotoxy(40, 7); printf("������ �����Ϸ��� 0�� �ٽ� �����Ϸ��� 1�� �����ּ���^^");
    // 2.����� Ȯ��
    while (1) {
        char input = _getch();
        static char cmd_buff[50] = {0};
        if (input == '0') {
            break;  // 0 �Է½� ����
        } else if (input == '1') {
            sprintf(cmd_buff, "start \"%s\"", argv0);
            system(cmd_buff);
            break;
        }
    }
}
