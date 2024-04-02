/* Coded with C Grammar for MSVC in Windows
   This Source uses UTF-8-BOM encoding & CRLF (Windows) line endings
   Alias : SingleTetris - Music.c & Last Moded : 2019.07.08.
   ��Ʈ���� ������� �� ȿ������ ����ϴ� �Լ� ����
   ���� : http://egloos.zum.com/newkong/v/4006039
   ���� : https://cfocus.tistory.com/2
*/

#include "../include/Music.h"

unsigned __stdcall bgm(void * arg) {
    srand((unsigned int)time(NULL));  // ���� ���� �ʱⰪ �Է�
    while (1) {
        int sound[3] = {3, 3, 3};
        for (int i = 0; i < 3; i++) {
            while (1) {  // ���� �ٸ����� ���ö� ���� �ݺ�
                sound[i] = rand()%3;
                if (sound[i] != sound[(i+1)%3] && sound[i] != sound[(i+2)%3]) {
                    break;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            if (sound[i] == 0) {
                PlaySound(TEXT("sound\\1.Flames.wav"), NULL, 0 | 0); // 1�� �� ���
            } else if (sound[i] == 1) {
                PlaySound(TEXT("sound\\2.Pluck_It_Up.wav"), NULL, 0 | 0); // 2�� �� ���
            } else if (sound[i] == 2) {
                PlaySound(TEXT("sound\\3.Wood.wav"), NULL, 0 | 0); // 3�� �� ���
            }
        }
    }
    return 0;
}

unsigned __stdcall drop(void * arg) {
    static int count = 0;
    char cmd_buff[50] = {0};
    sprintf(cmd_buff, "sound/soundplayer >> sound\\tmp\\%d.txt", count++);  // ���α׷� �и�
    system(cmd_buff);
    if (count >= 10) {
        count = 0;
    }
    return 0;
}

void musicPlay(int const type) {
    switch (type) {
        case 1:
            _beginthreadex(NULL, 0, bgm, 0, 0, NULL);
            break;
        case 2:
            _beginthreadex(NULL, 0, drop, 0, 0, NULL);
            break;
    }
}
