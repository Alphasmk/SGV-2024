@ECHO OFF
cd /d C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build
call vcvarsall.bat x86
cd /d E:\unic\courseKPO\Project1\SGVASM
ml.exe /c /coff /Zi asm.asm
link.exe /OPT:NOREF /DEBUG /SUBSYSTEM:CONSOLE asm.obj user32.lib /OUT:SGVASM.exe
cls
call SGVASM.exe
pause
exit