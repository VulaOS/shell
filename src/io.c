#include "io.h"
#include <winnt.h>







void VlPuts(PCWSTR string){
    UNICODE_STRING ustring;
    RtlInitUnicodeString(&ustring, string);
    NtDisplayString(&ustring);
}