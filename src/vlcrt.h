#ifndef VLCRT_H_INCLUDED
#define VLCRT_H_INCLUDED





#include "vula.h"



void VlPuts(PCWSTR string);
void* VlAlloc(size_t size);
BOOL VlFree(void* address, size_t size);
NTSTATUS VlSleep(int milliseconds);
WCHAR* Vlitow(int num, WCHAR* str);
WCHAR* VlStatusToString(NTSTATUS status, WCHAR* str);
WCHAR* VlCharToString(WCHAR character);
void VlGets();
NTSTATUS VlCreateKeyboardEvent(PHANDLE kEvent);



#endif