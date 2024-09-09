#include "cmdparser.h"
#include "diskio.h"
#include "shell.h"









void VlEntry() {
    VlPuts(L"VulaOS Build INDEV (0.0.5)\n\n");
    VlPuts(L"Shell Test (2)\n");
    VlPuts(L"Type Help for List of Commands\n\n");

    
    data data;
    set_current_directory(L"X:\\Windows\\System32");
    while (1) {
        VlSleep(9);
        WCHAR* dir = get_current_directory();
        WCHAR* input = VlGets(dir, 1024);
        VlStrTok(&data.cmd, 512,&data.arg, 512, L' ', input);
        matcher(&data);
        VlFreeString(input, 1024);
        VlFreeString(data.cmd, 512);
        VlFreeString(data.arg, 512);
        VlFreeString(dir, 512);
    }
}


