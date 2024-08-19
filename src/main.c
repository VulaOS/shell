#include "vlalib.h"









void VlEntry() {
    VlPuts(L"VulaOS Build INDEV (0.0.3)\n\n");
    VlPuts(L"String Parsing Test\n\n");
    
    
    while (1) {
        VlSleep(9);
        WCHAR* first;
        WCHAR* second;
        WCHAR* input = VlGets(L"Type Strings So It Can Be Parsed", 1024);
        VlStrTok(&first, 512,&second, 512, L' ', input);
        VlPuts(first);
        VlPuts(L" --- ");
        VlPuts(second);
        VlPuts(L"\n");
        VlFreeString(input, 1024);
        VlFreeString(first, 512);
        VlFreeString(second, 512);
    }
}


