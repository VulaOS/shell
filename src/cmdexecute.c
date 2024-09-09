#include "cmdexecute.h"
#include "diskio.h"
#include "vlalib.h"




void execute(data* data, int index){
    switch(index){
        case 0:
            VlPuts(data->arg);
            VlPuts(L"\n");
            break;
        case 1:
            VlPuts(L"ECHO ARG1: PRINTS ARG1\n");
            VlPuts(L"HELP: PRINTS THE HELP SCREEN\n");
            VlPuts(L"CD ARG1: MOVES TO ARG1\n");
            VlPuts(L"CHANGEL ARG1: CHANGES DRIVELETTER TO ARG1\n");

            break;
        case 2:
            set_current_directory(data->arg);
            break;
        case 3:
            // cannot use wchar arrays bc msvc won't compile for some reason, stuck on the heap =(
            WCHAR* buf = VlAlloc(512);
            VlStrCat(buf, data->arg);
            VlStrCat(buf, L":");
            set_current_directory(buf);
            VlFree(buf, 512);
            break;
        case 4:
            create_file(data->arg);
            break;
        case 5:
            read_file(data->arg);
            break;
        default:
            VlPuts(L"Error: Incorrect Index or Switch Overflow (missing break)\n");
            break;
    }
}