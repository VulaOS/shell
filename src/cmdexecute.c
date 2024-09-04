#include "cmdexecute.h"
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
            break;
        default:
            VlPuts(L"Error: Incorrect Index or Switch Overflow (missing break)\n");
            break;
    }
}