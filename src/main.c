#include "vula.h"



void _entry(){
    UNICODE_STRING string;
    RtlInitUnicodeString(&string, L"Vula Build INDEV");



    NtDisplayString(&string);

    while(1){continue;}

}