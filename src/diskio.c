#include "diskio.h"
#include "shell.h"
#include "vlalib.h"





PWSTR get_current_directory(){
    WCHAR* buffer = VlAlloc(1024);
    RtlGetCurrentDirectory_U(1024, buffer);

    return buffer;
}


void set_current_directory(WCHAR* path){
    if(!path){
        VlPuts(L"Invalid Path\n");
    }
    UNICODE_STRING pathstring;
    RtlInitUnicodeString(&pathstring, path);
    NTSTATUS status = RtlSetCurrentDirectory_U(&pathstring);
    if(!NT_SUCCESS(status)){
       VlPrintStatus(L"RtlSetCurrentDirectory_U", status);
       return;
    }
}

HANDLE open_file_for_reading(WCHAR* filename) {
    WCHAR* buffer = VlAlloc(1024);
    if (filename[1] == ':') {
        VlStrCat(buffer, L"\\??\\");
        VlStrCat(buffer, filename);
        VlStrCat(buffer, L"\0\\");
    }
    else {
        WCHAR* path = get_current_directory(); 
        VlStrCat(buffer, L"\\??\\");
        VlStrCat(buffer, path);
        VlStrCat(buffer,L"\\");
        VlStrCat(buffer, filename);
        VlStrCat(buffer, L"\0\\");
        VlFree(path, 1024);  

    }

    UNICODE_STRING objectName;
    RtlInitUnicodeString(&objectName, buffer);
    OBJECT_ATTRIBUTES obj;
    InitializeObjectAttributes(&obj, &objectName, OBJ_CASE_INSENSITIVE, NULL, NULL);

    HANDLE fHandle;
    IO_STATUS_BLOCK ioStatusBlock;

    NTSTATUS createFileStatus = NtCreateFile(
        &fHandle,
        FILE_READ_DATA | FILE_READ_ATTRIBUTES,
        &obj,
        &ioStatusBlock,
        NULL,
        FILE_ATTRIBUTE_NORMAL,
        FILE_SHARE_READ,
        FILE_OPEN,
        FILE_SEQUENTIAL_ONLY,
        NULL,
        0
    );

    if (!NT_SUCCESS(createFileStatus)) {
        NtClose(fHandle);
        VlPrintStatus(L"NtCreateFile", createFileStatus);
        return NULL;
    }
    VlFree(buffer, 1024);
    return fHandle;
}

void create_file(WCHAR* filename) {
    WCHAR* buffer = VlAlloc(1024);
    if (filename[1] == ':') {
        VlStrCat(buffer, L"\\??\\");
        VlStrCat(buffer, filename);
        VlStrCat(buffer, L"\0\\");

    }
    else {
        WCHAR* path = get_current_directory(); 
        VlStrCat(buffer, L"\\??\\");
        VlStrCat(buffer, path);
        VlStrCat(buffer,L"\\");
        VlStrCat(buffer, filename);
        VlStrCat(buffer, L"\0\\");
        VlFree(path, 1024);  
    }

    UNICODE_STRING objectName;
    RtlInitUnicodeString(&objectName, buffer);
    OBJECT_ATTRIBUTES obj;
    InitializeObjectAttributes(&obj, &objectName, OBJ_CASE_INSENSITIVE, NULL, NULL);

    HANDLE fHandle;
    IO_STATUS_BLOCK ioStatusBlock;

    NTSTATUS createFileStatus = NtCreateFile(
        &fHandle,
        FILE_WRITE_DATA | FILE_READ_DATA | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES,
        &obj,
        &ioStatusBlock,
        NULL,
        FILE_ATTRIBUTE_NORMAL,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        FILE_CREATE,
        FILE_SEQUENTIAL_ONLY,
        NULL,
        0
    );

    if (!NT_SUCCESS(createFileStatus)) {
        NtClose(fHandle);
        VlPrintStatus(L"NtCreateFile", createFileStatus);
    }
    VlFree(buffer, 1024);  

    NtClose(fHandle);
}

void read_file(WCHAR* filename){
    HANDLE fileHandle = open_file_for_reading(filename);
    IO_STATUS_BLOCK ioStatusBlock;
    WCHAR* secondaryBuffer = VlAlloc(1024);
    LARGE_INTEGER byteOffset = { 0 };
    NTSTATUS status = NtReadFile(fileHandle, 
                                NULL, 
                                NULL, 
                                NULL, 
                                &ioStatusBlock , 
                                &secondaryBuffer, 
                                1024, 
                                &byteOffset, 
                                NULL);
    if(!NT_SUCCESS(status)){
        VlPrintStatus(L"NtReadFile", status);
        return;
    }
    VlPuts(secondaryBuffer);
    VlPuts(L"\n");
    NtClose(fileHandle);
}