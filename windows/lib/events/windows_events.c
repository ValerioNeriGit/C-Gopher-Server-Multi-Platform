//
// Created by Valerio on 24/07/2019.
//

//#include <windows.h>
#include <stdio.h>
#include "windows_events.h"
#include "definitions.h"

BOOL WINAPI consoleHandler(DWORD signal) {

    if (signal == CTRL_C_EVENT) {
        printf("Ctrl-C handled\n");
        int flagOne = 1;
        (*configs).reset_config = &flagOne;
    }
    return TRUE;
}
