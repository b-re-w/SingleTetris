/* Coded with C Grammar for MSVC in Windows
   This Source uses UTF-8-BOM encoding & CRLF (Windows) line endings
   Alias : SingleTetris - Main.c & Last Moded : 2019.07.08.
   Tetris Program Coded by IRACK
   ICON : <a href="https://www.freepik.com/free-photos-vectors/logo">Logo vector created by freepik - www.freepik.com</a>
*/

#include "Main.h"
#include "include/Music.h"
#include "include/Tetris.h"
#include "include/WinAPI.h"


int main(int argc, char const * argv[]) {
    // 0. ���ӿ� ���� ������ ����
    _Bool struct_board[YSIZ][XSIZ] = {{0}};  // ��Ʈ���� ��ü ����(��) ����� �迭
    struct object_info objstat;  // ��ü(�����̴� ��Ʈ���� ����) ���� ����� ����ü
    int ylimit = 3;  // y�� ���Ѽ� ����
    int ttspeed = 60;  // ��Ʈ���� ���� �ڵ� ���� ���ǵ� (���ڰ� ������ ���� ������)
    int key = 0;  // _getch() ���ϰ� ����� ����

    // 2. ���� ȭ�� ǥ��
    musicPlay(BGM);  // ��� ���� ���
    showStart(3);  // 3�� ���� ���

    // 2. ��Ʈ���� �⺻ ������� ����
    contructWall(struct_board);  // �� ����

    // 3. ���� ����
    while (1) {
        // 3-0. �ӽ� ���� ����
        int saved_down_count = 0;  // ī��Ʈ�� ttspeedȸ �����Ǹ� �ڵ����� ��ĭ ����

        // 3-1. �ű� ���� �����ϱ�
        getNewShape(&objstat);  // ���ο� ���� �޾ƿ���

        // 3-2. �ٴڱ��� �������� LOOP
        while (1) {
            // 3-2-0. �ӽ� ���� ����
            _Bool if_crash_occured = 0;  // �浹 �߻����� Ȯ�ο� �÷���

            // 3-2-1. ����� �Է� ó��
            // ���� : https://boongubbang.tistory.com/46
            if (_kbhit()) {  // ����Ű�� �ѹ� �Է½� �ΰ��� ���� ��ȯ
                key = _getch();  // ����Ű(224)���� �����̽�Ű���� �޾ƿ�
                if (key == 224) {  // ����Ű�� ���
                    letObjMove(struct_board, &objstat, _getch());  // ��� ������ ����Ű���� ���� �� ���� �����̱�
                } else if (key == SPACE) {  // �����̽��� ��� -> �ϵ� ���
                    while (!letObjMove(struct_board, &objstat, DOWN));  // �ٴڿ� ���� �� ���� �ݺ�
                    saved_down_count = 0;
                    if_crash_occured = 1;
                }
            }

            // 3-2-2. �ٲ� ��� ���
            printGameBoard(struct_board, &objstat, ylimit);  // ���� ��Ȳ �����ֱ�

            // 3-2-3. ���� ��ĭ ������
            if (saved_down_count == ttspeed) {  // ���� ī��Ʈ�� ������ ���ǵ尡 ���� ��
                if_crash_occured = letObjMove(struct_board, &objstat, DOWN);  // �ڵ����� ��ĭ�� ����, �ٴڿ� ���� Ȯ��
                saved_down_count = 0;  // ī��Ʈ ���� �ʱ�ȭ
            }

            // 3-2-4. �ٴڿ� ��Ҵ��� �˻�
            if (if_crash_occured) {  // 1) ���� ��� - �ϼ��� �� ����
                musicPlay(DROP);  // ȿ���� ���
                buildBoard(struct_board, &objstat, NORESET);  // �ٴ� �浹 �߻��� ��ü�� ������ ����
                checkLineFull(struct_board);  // ���� ä�� Ȯ�� �� ����
                break;  // �ٴڿ� ������ �극��ũ
            } else {  // 2) ���� ���� ��� - �ڵ����� ��ĭ ������ ���� ���� ��ġ ���� ��Ű��
            saved_down_count++;  // ī��Ʈ 1 ����
            }
        }

        // 3-3. ���ӿ��� üũ
        if (checkGameOver(struct_board, ylimit)) {  // ���� �й� Ȯ��
            break;  // ���̸� �극��ũ
        }
    }

    // 4. ��� ǥ�� �� ����� ���� Ȯ��
    showTetrisResult(argv[0]);

    return 0;
}
