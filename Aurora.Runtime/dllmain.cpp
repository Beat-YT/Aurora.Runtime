#include "program.h"
#include <windows.h>

static aurora::Program* spProgram;

// BRUUUUH.
DWORD WINAPI Main(LPVOID lpParam)
{
    spProgram = new aurora::Program;

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason,
    LPVOID lpReserved)
{
    /*if (dwReason == DLL_PROCESS_ATTACH) {
        spProgram = new aurora::Program;
    } else if (dwReason == DLL_PROCESS_DETACH && spProgram) {
        delete spProgram;
    }*/

    // Bruh... We don't even properly dispose!
    if (dwReason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, Main, hModule, 0, 0);
    }

    return TRUE;
}
