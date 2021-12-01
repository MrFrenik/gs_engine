@echo off
rmdir /Q /S bin
mkdir bin
pushd bin

rem Source Files
set refl_name=Reflection
set src_refl_main=..\source\reflection\main.c
set refl_inc=/I ..\source\

rem Name
set name=App

rem Include directories 
set inc=/I ..\third_party\include\

rem Source files
set src_main=..\source\main.c

rem OS Libraries
set os_libs= opengl32.lib kernel32.lib user32.lib ^
shell32.lib vcruntime.lib msvcrt.lib gdi32.lib Winmm.lib Advapi32.lib 

rem Link options
set l_options=/EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib 

rem Compile Reflection
cl /w /MP -Zi /DEBUG:FULL /Fe%refl_name%.exe %src_refl_main% %inc% %refl_inc% ^
/EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:LIBCMT ^
%os_libs% 

rem Run Reflection
%refl_name%.exe "../source/" "../source/reflection/" "GS"

rem Compile Release
rem cl /MP /FS /Ox /W0 /Fe%name%.exe %src_main% %inc% ^
rem /EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:LIBCMT ^
rem %os_libs%

rem Compile Debug
cl /w /MP -Zi /DEBUG:FULL /Fe%name%.exe %src_main% %inc% ^
/EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:LIBCMT ^
%os_libs%

popd
