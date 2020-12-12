#include "program.h"
#include <windows.h>

static aurora::Program* spProgram;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason,
    LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        spProgram = new aurora::Program;
    } else if (dwReason == DLL_PROCESS_DETACH && spProgram) {
        delete spProgram;
    }

    return TRUE;
}
