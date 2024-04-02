#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define Third_Run "Small_Glass_Pane_Shatter.wav"

int main(void) {
    PlaySound(TEXT(Third_Run), NULL, SND_FILENAME | 0 | SND_LOOP );
    return 0;
}
