#ifndef VLCRT_H_INCLUDED
#define VLCRT_H_INCLUDED





#include "vula.h"

#define VLSTRINGSIZE 512 * sizeof(WCHAR)

void VlPuts(PCWSTR string);
void* VlAlloc(size_t size);
BOOL VlFree(void* address, size_t size);
NTSTATUS VlSleep(int milliseconds);
WCHAR* Vlitow(int num, WCHAR* str);
WCHAR* VlStatusToString(NTSTATUS status, WCHAR* str);
WCHAR* VlCharToString(WCHAR character);
WCHAR VlGetKey();
WCHAR* VlGets(WCHAR* prompt, size_t size);
BOOL VlFreeString(WCHAR* string, size_t size);
void VlStrTok(WCHAR** firststring, size_t firststringsize, WCHAR** secondstring, size_t secondstringsize, WCHAR delimiter, WCHAR* sourcestring);


#endif