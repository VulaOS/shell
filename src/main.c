#include "vlcrt.h"









void _entry(){
    VlPuts(L"VulaOS Build INDEV\n\n");
    VlPuts(L"Type Anything to test the keyboard\n\n");

    while(1){
        VlSleep(9);
        WCHAR* name = VlGets(L"Whats Your Name?");
        // I really need to implement printf
        VlPuts(L"Hi ");
        VlPuts(name);
        VlPuts(L"\n");
        
        VlFree(name, VLSTRINGSIZE);
    }
}

