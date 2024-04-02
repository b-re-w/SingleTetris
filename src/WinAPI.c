/* Coded with C Grammar for MSVC in Windows
   This Source uses UTF-8-BOM encoding & CRLF (Windows) line endings
   Alias : SingleTetris - WinAPI.c & Last Moded : 2019.07.08.
   ��Ʈ���� ������ ����� �ְܼ� ���õ� Windows NT API �Լ��� ����
*/

#include "../include/Tetris.h"
#include "../include/WinAPI.h"

void gotoxy(int x, int y) {
    COORD position = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position); // Windows API ���
}

void changeObjColor(int const color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // Windows API ���
}

void hideConsoleCursor(_Bool const hide_flag) {
    // Ŀ�� ���� - https://kkikkodev.tistory.com/27
    CONSOLE_CURSOR_INFO cursorInfo = {0};
    cursorInfo.dwSize = 1; // Ŀ�� ũ�� ����
    cursorInfo.bVisible = !hide_flag; // Ŀ���� ���̷��� TRUE, �׷��� �������� FALSE
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // Windows API ���
}
