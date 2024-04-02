#pragma once

#include "../Main.h"

#ifndef WINAPI_H
    #define WINAPI_H

    #define SHOW 0  // hideConsoleCursor �Լ��� �ܼ� Ŀ�� ���̱� �ɼ�
    #define HIDE 1  // hideConsoleCursor �Լ��� �ܼ� Ŀ�� ����� �ɼ�
#endif

void gotoxy(int x, int y) ; // �ܼ�â Ŀ�� ��ǥ �̵� �Լ�
void changeObjColor(int const color);  // �ܼ�â ���� �� ���� �Լ�
void hideConsoleCursor(_Bool const hide_flag);  // �ܼ�â Ŀ�� ������ ���� �Լ�
