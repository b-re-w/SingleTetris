cmake_minimum_required(VERSION 3.27)
project(cmake_single_tetris C)

set(CMAKE_C_STANDARD 11)

add_executable(cmake_single_tetris
        Main.h Main.c
        include/Music.h src/Music.c
        include/Tetris.h src/Tetris.c
        include/WinAPI.h src/WinAPI.c
        lib/system.h
        lib/macos/Windows.h
)

target_link_libraries(cmake_single_tetris PRIVATE
        winmm.lib
        ws2_32.lib
        wininet.lib
        version.lib
        Shlwapi.dll
)
