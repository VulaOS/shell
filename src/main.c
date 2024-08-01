#include "vlcrt.h"
#include <winternl.h>









void _entry(){
    VlPuts(L"VulaKRNL Build INDEV\n\n");
    VlPuts(L"Type Anything to test the keyboard\n\n");

    while(1){
        VlSleep(9);
        VlGets();
    }
}

