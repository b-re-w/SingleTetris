/* Coded with C Grammar for MSVC in Windows
   This Source uses UTF-8-BOM encoding & CRLF (Windows) line endings
   Alias : SingleTetris - WinAPI.c & Last Moded : 2019.07.08.
   테트리스 게임을 출력할 콘솔과 관련된 Windows NT API 함수를 정의
*/

#include "../include/Tetris.h"
#include "../include/WinAPI.h"

void gotoxy(int x, int y) {
    COORD position = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position); // Windows API 사용
}

void changeObjColor(int const color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // Windows API 사용
}

void hideConsoleCursor(_Bool const hide_flag) {
    // 커서 제거 - https://kkikkodev.tistory.com/27
    CONSOLE_CURSOR_INFO cursorInfo = {0};
    cursorInfo.dwSize = 1; // 커서 크기 설정
    cursorInfo.bVisible = !hide_flag; // 커서를 보이려면 TRUE, 그렇지 않으려면 FALSE
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // Windows API 사용
}
