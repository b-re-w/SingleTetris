#pragma once

#include "../Main.h"

#ifndef MUSIC_H
    #define MUSIC_H

    #if defined(_WIN32) || defined(_CYGWIN_)
        #include <process.h>  // 스레드를 위한 헤더파일
        #include <mmsystem.h>  // to use PlaySound()
    #elif defined(__APPLE__) || defined(__MACH__)

    #endif

    #define BGM 1  // musicPlay 함수의 배경음악 재생 옵션
    #define DROP 2  // musicPlay 함수의 효과음 재생 옵션
#endif

void musicPlay(int const type);  // 배경음악 및 효과음을 재생시켜주는 함수
