#ifndef CMAKE_SINGLE_TETRIS_SYSTEM_H
    #define CMAKE_SINGLE_TETRIS_SYSTEM_H

    #if defined(_WIN32) || defined(_CYGWIN_)
        #include <Windows.h>  // to use system(), exit(), rand(), srand(), Sleep(), _getch()
        #include <conio.h>  // to use _kbhit()
    #elif defined(__APPLE__) || defined(__MACH__)
        #include "./macos/Windows.h"
    #endif
#endif //CMAKE_SINGLE_TETRIS_SYSTEM_H
