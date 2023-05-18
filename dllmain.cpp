#include "Logger.h"


DWORD WINAPI T1(HMODULE hModuke)
{
    Logger log;
    log.Init_Logger();
    log.Print_log("Test!");
    log.set_log_level(Logger::LOG_ERROR);
    //....


    while(true)
    {
        Sleep(200);

        if (GetAsyncKeyState(VK_NUMPAD1) &1)
        {
            log.Shutdown_Logger();
            FreeLibraryAndExitThread(hModuke, 0);

        }

    }



    return 0;
}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
)
{

    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        const auto Thread1 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(T1), hModule, 0, nullptr);

        if (Thread1)
            CloseHandle(Thread1);

    }




    return TRUE;
}

