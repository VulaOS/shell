# Vula - A Shell for the Native Subsystem of Windows NT Based Systems

# HOW TO COMPILE THE SHELL:

- Open x64 Native Tools Command Prompt for Microsoft Windows
- Clone this repository
- Move to the directory which its cloned at
- run make.bat

# HOW TO RUN:
- Download The VulaKRNL ISO from the Releases
- Either Burn to USB or CD
- Boot Into the USB or CD

  
# HOW TO RUN THE SHELL FOR YOUR OWN WINDOWS INSTALLATION:
- go to HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\ and edit the BootExecute Value to where vula.exe is at
- restart your system

# HOW TO EXIT:
- either go to the recovery enviroment or WinPE
- delete the vula.exe executable or change the registry that was changed earlier
- restart
