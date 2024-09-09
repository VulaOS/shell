#ifndef DISKIO_H_INCLUDED
#define DISKIO_H_INCLUDED

#include "shell.h"



PWSTR get_current_directory();
void set_current_directory(WCHAR* path);
void create_file(WCHAR* filename);
void read_file(WCHAR* filename);

#endif