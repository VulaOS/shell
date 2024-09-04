#include "cmdparser.h"
#include "shell.h"









void VlEntry() {
    VlPuts(L"VulaOS Build INDEV (0.0.4)\n\n");
    VlPuts(L"Shell Test\n");
    VlPuts(L"Type Help for List of Commands\n\n");

    
    data data;
    
    while (1) {
        VlSleep(9);
        
        WCHAR* input = VlGets(L"->", 1024);
        VlStrTok(&data.cmd, 512,&data.arg, 512, L' ', input);
        matcher(&data);
        VlFreeString(input, 1024);
        VlFreeString(data.cmd, 512);
        VlFreeString(data.arg, 512);
    }
}


