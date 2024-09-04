#include "cmdparser.h"
#include "shell.h"
#include "vlalib.h"
#include "cmdexecute.h"

WCHAR* cmds[] = {L"echo", L"help"};

static inline LONG compare_string(WCHAR* cmd, WCHAR* cmds){
    UNICODE_STRING cmdstring;
    RtlInitUnicodeString(&cmdstring, cmd);
    UNICODE_STRING cmdsstring;
    RtlInitUnicodeString(&cmdsstring, cmds);
    return RtlCompareUnicodeString(&cmdstring, &cmdsstring, TRUE);
}


void matcher(data* data){
    int cmdsize = sizeof(cmds)/sizeof(cmds[0]);

    for(int i = 0; i < cmdsize; i++){
        if(compare_string(data->cmd, cmds[i]) == 0){
            execute(data, i);
            return;
        }
    }
    VlPuts(L"Not Found\n");
}