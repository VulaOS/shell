#include "vlcrt.h"









void VlEntry() {
    VlPuts(L"VulaOS Build INDEV (0.0.2)\n\n");
    VlPuts(L"Input Test\n\n");

    while (1) {
        VlSleep(9);
        WCHAR* name = VlGets(L"Whats Your Name?", 1024);
        if (name == NULL) {
            VlPuts(L"Memory allocation failed\n");
            continue;
        }

        // gotta implement vlprintf soon lol
        VlPuts(L"Hi ");
        VlPuts(name);
        VlPuts(L"\n");

        VlFreeString(name, 1024);
    }
}


