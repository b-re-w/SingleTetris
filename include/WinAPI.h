#pragma once

#include "../Main.h"

#ifndef WINAPI_H
    #define WINAPI_H

    #define SHOW 0  // hideConsoleCursor 함수의 콘솔 커서 보이기 옵션
    #define HIDE 1  // hideConsoleCursor 함수의 콘솔 커서 숨기기 옵션
#endif

void gotoxy(int x, int y) ; // 콘솔창 커서 좌표 이동 함수
void changeObjColor(int const color);  // 콘솔창 글자 색 변경 함수
void hideConsoleCursor(_Bool const hide_flag);  // 콘솔창 커서 깜박임 제거 함수
