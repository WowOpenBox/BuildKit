// OpenMultiBoxing_RR.cpp : Enable Round Robin by "debugging" the main exe
// so it can send focus commands.
// (ie it launches child process with debugger mode)
// (c) 2021 MooreaTv <moorea@ymail.com>
// GPLv3 License
// Can't be used in commercial products. NO WARRANTY.

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void EnterDebugLoop(const LPDEBUG_EVENT DebugEv)
{
    printf("start EnterDebugLoop\n");
    for (;;)
    {
        if (!WaitForDebugEvent(DebugEv, INFINITE)) {
            printf("WaitForDebugEvent failed (%d).\n", GetLastError());
            return;
        }
        if (DebugEv->dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) {
            printf("Child process exited.");
            return;
        }
        if (!ContinueDebugEvent(DebugEv->dwProcessId,
            DebugEv->dwThreadId,
            DBG_CONTINUE)) {
            printf("ContinueDebugEvent failed (%d).\n", GetLastError());
            return;
        }
    }
}

#define MAX_CMD 256

//int _tmain(int argc, TCHAR* argv[])
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const char* cmd1 = "OpenMultiBoxing-vX.Y.Z.exe -rr"; // vX.Y.Z changed at CI time (note: doesn't work for .10. etc)
    wchar_t* cmd = (wchar_t*)calloc(MAX_CMD, sizeof(wchar_t));
    if (!cmd) {
        printf("Unable to allocate %d array of wide char!\n", MAX_CMD);
        return -1;
    }
    size_t i = 0;
    for (; i < strlen(cmd1); i++) {
        cmd[i] = cmd1[i];
    }
    cmd[i++] = ' ';
    for (size_t j= 0; j <= wcslen(pCmdLine); j++) {
        cmd[i + j] = pCmdLine[j];
    }
    //printf("Running: %ls\n", cmd);

    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process. 
    if (!CreateProcessW(NULL,   // No module name (use command line)
        cmd,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,
        DEBUG_ONLY_THIS_PROCESS,
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 2;
    }
    printf("Started %ld\n", pi.dwProcessId);
    DEBUG_EVENT DebugEv;
    ZeroMemory(&DebugEv, sizeof(DebugEv));
    DebugEv.dwProcessId = pi.dwProcessId;
    DebugEv.dwThreadId = pi.dwThreadId;
    EnterDebugLoop(&DebugEv);
    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
