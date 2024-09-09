#ifndef VULA_H_INCLUDED
#define VULA_H_INCLUDED



#define _AMD64_

#include <minwindef.h>
#include <winternl.h>
#include "vlalib.h"



// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░       ░▒▓██████▓▒░  
// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
//  ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
//  ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓████████▓▒░ 
//   ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
//   ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ 
//    ░▒▓██▓▒░   ░▒▓██████▓▒░░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░ 
// 
//
// Contributed by zvqle
                                             
typedef struct _data{
    WCHAR* cmd;
    WCHAR* arg;
} data;

extern LONG NTAPI RtlCompareUnicodeString(PUNICODE_STRING,
    PUNICODE_STRING,
    BOOLEAN
);
extern ULONG NTAPI RtlGetCurrentDirectory_U(
    ULONG,
    _Out_writes_bytes_(BufferLength) PWSTR 
);
extern NTSTATUS NTAPI RtlSetCurrentDirectory_U(
    PUNICODE_STRING
);


#endif