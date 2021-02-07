// rrenable.cpp
// (c) 2021 MooreaTv <moorea@ymail.com>
// Launches child process with debugger mode

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


int _tmain(int argc, TCHAR* argv[])
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (argc != 2)
    {
        printf("Usage: %ls cmdline\n", argv[0]);
        return 1;
    }

    // Start the child process. 
    if (!CreateProcess(NULL,   // No module name (use command line)
        argv[1],        // Command line
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

