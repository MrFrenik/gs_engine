@echo off
rmdir /Q /S bin
mkdir bin
pushd bin

rem Source Files
set core_dir=..\gs_core
set proj_gen_name=ProjGen
set src_proj_gen_main=%core_dir%\source\proj_gen\main.c

rem Include directories 
set inc=/I %core_dir%\third_party\include\

rem OS Libraries
set os_libs= opengl32.lib kernel32.lib user32.lib ^
shell32.lib vcruntime.lib msvcrt.lib gdi32.lib Winmm.lib Advapi32.lib 

rem Link options
set l_options=/EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib 

rem Compile Project Generator
cl /w /MP -Zi /DEBUG:FULL /Fe%proj_gen_name%.exe %src_proj_gen_main% %inc% %refl_inc% ^
/EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:LIBCMT ^
%os_libs% 

rem Run Project Generator
%proj_gen_name%.exe %1 %2

rem Compile Release
rem cl /MP /FS /Ox /W0 /Fe%name%.exe %src_main% %inc% ^
rem /EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:LIBCMT ^
rem %os_libs%

rem Compile Debug
rem cl /w /MP -Zi /DEBUG:FULL /Fe%name%.exe %src_main% %inc% ^
rem /EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:LIBCMT ^
rem %os_libs%

popd

rmdir /Q /S bin
