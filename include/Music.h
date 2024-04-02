#pragma once

#include "../Main.h"

#ifndef MUSIC_H
    #define MUSIC_H

    #if defined(_WIN32) || defined(_CYGWIN_)
        #include <process.h>  // �����带 ���� �������
        #include <mmsystem.h>  // to use PlaySound()
    #elif defined(__APPLE__) || defined(__MACH__)

    #endif

    #define BGM 1  // musicPlay �Լ��� ������� ��� �ɼ�
    #define DROP 2  // musicPlay �Լ��� ȿ���� ��� �ɼ�
#endif

void musicPlay(int const type);  // ������� �� ȿ������ ��������ִ� �Լ�
