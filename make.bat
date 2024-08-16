@echo off




cl /c src/*.c
link *.obj ntdll.lib /subsystem:native /entry:_entry /out:vula.exe
del *.obj

echo compilation finished 
echo build at
date /t
time /t
