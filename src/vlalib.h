#ifndef VLALIB_H_INCLUDED
#define VLALIB_H_INCLUDED


#define _AMD64_
#include <minwindef.h>
#include <winternl.h>


typedef enum _EVENT_TYPE
{
    NotificationEvent,
    SynchronizationEvent
} EVENT_TYPE;


typedef struct _KEYBOARD_INPUT_DATA {
    USHORT UnitId;
    USHORT MakeCode;
    USHORT Flags;
    USHORT Reserved;
    ULONG  ExtraInformation;
} KEYBOARD_INPUT_DATA, *PKEYBOARD_INPUT_DATA;

extern NTSTATUS NTAPI NtDisplayString(PUNICODE_STRING String);
extern NTSTATUS NTAPI NtAllocateVirtualMemory(HANDLE, PVOID, ULONG_PTR, PSIZE_T, ULONG, ULONG);
extern NTSTATUS NTAPI NtFreeVirtualMemory(HANDLE, PVOID, PSIZE_T, ULONG);
extern NTSTATUS NTAPI NtDelayExecution(BOOL, PLARGE_INTEGER);
extern NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
extern NTSTATUS NTAPI NtCreateEvent(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, EVENT_TYPE, BOOL);
extern NTSTATUS NTAPI NtReadFile(HANDLE, HANDLE, PIO_APC_ROUTINE, PVOID, PIO_STATUS_BLOCK, PVOID, ULONG, PLARGE_INTEGER, PULONG);
extern NTSTATUS NTAPI NtCreateFile(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PIO_STATUS_BLOCK, PLARGE_INTEGER, ULONG, ULONG, ULONG, ULONG, PVOID, ULONG);
extern NTSTATUS NTAPI NtClose(HANDLE);
extern NTSTATUS NTAPI NtWaitForSingleObject(HANDLE, BOOLEAN, PLARGE_INTEGER);

#define SE_CREATE_TOKEN_PRIVILEGE       (2L)
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE (3L)
#define SE_LOCK_MEMORY_PRIVILEGE        (4L)
#define SE_INCREASE_QUOTA_PRIVILEGE     (5L)
#define SE_UNSOLICITED_INPUT_PRIVILEGE  (6L)
#define SE_MACHINE_ACCOUNT_PRIVILEGE    (7L)
#define SE_TCB_PRIVILEGE                (8L)
#define SE_SECURITY_PRIVILEGE           (9L)
#define SE_TAKE_OWNERSHIP_PRIVILEGE     (10L)
#define SE_LOAD_DRIVER_PRIVILEGE        (10L)
#define SE_SYSTEM_PROFILE_PRIVILEGE     (11L)
#define SE_SYSTEMTIME_PRIVILEGE         (12L)
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE (13L)
#define SE_INC_BASE_PRIORITY_PRIVILEGE  (14L)
#define SE_CREATE_PAGEFILE_PRIVILEGE    (15L)
#define SE_CREATE_PERMANENT_PRIVILEGE   (16L)
#define SE_BACKUP_PRIVILEGE             (17L)
#define SE_RESTORE_PRIVILEGE            (18L)
#define SE_SHUTDOWN_PRIVILEGE           (19L)
#define SE_DEBUG_PRIVILEGE              (20L)
#define SE_AUDIT_PRIVILEGE              (21L)
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE (22L)
#define SE_CHANGE_NOTIFY_PRIVILEGE      (23L)
#define SE_REMOTE_SHUTDOWN_PRIVILEGE    (24L)
#define KEY_MAKE 0x00 
#define KEY_BREAK 0x01 
#define KEY_E0 0x02 
#define KEY_E1 0x04 
#define RTL_CONSTANT_STRING(s) { sizeof(s) - sizeof((s)[0]), sizeof(s), s }
#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)
#define EVENT_QUERY_STATE 0x0001

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