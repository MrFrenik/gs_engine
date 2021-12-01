@echo off
rmdir /Q /S bin
mkdir bin
pushd bin

rem Variables
set name=gs_editor
set core_dir=../../gs_core/

rem Source Files
set refl_name=Reflection
set src_refl_main=%core_dir%\source\reflection\main.c
set refl_inc=/I %core_dir%\source\ 

rem Include directories 
set inc=/I %core_dir%\third_party\include\ 
set core_inc=/I %core_dir%\source 

set libdbg=%core_dir%\third_party\libs\win\dbg
set librel=%core_dir%\third_party\libs\win\rel

set core_libs_dbg=%libdbg%\cimgui.lib
set core_libs_rel=%libdbg%\cimgui.lib

rem Source files
set src_main=..\source\gs_editor_main.c

rem OS Libraries
set os_libs= opengl32.lib kernel32.lib user32.lib ^
shell32.lib vcruntime.lib msvcrt.lib gdi32.lib Winmm.lib Advapi32.lib 

rem Link options
set l_options=/EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib 

rem Compile Reflection
cl /w /MP -Zi /DEBUG:FULL /Fe%refl_name%.exe %src_refl_main% %inc% %refl_inc% ^
/EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:LIBCMT ^
%os_libs% 

rem Run Reflection for GS files
%refl_name%.exe "%core_dir%/source/" "%core_dir%/source/reflection/" "gs"

rem Run Reflection for gs_editor files 
%refl_name%.exe "../source/" "../source/reflection/" "gs_editor"

rem Compile Release
rem cl /MP /FS /Ox /W0 /Fe%name%.exe %src_main% %inc% %core_inc% ^
rem /EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:LIBCMT ^
rem %os_libs%

rem Compile Debug
cl /w /MP -Zi /DEBUG:FULL /Fe%name%.exe %src_main% %inc% %core_inc% ^
/EHsc /link /SUBSYSTEM:CONSOLE /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:libcmt.lib ^
/NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrtd.lib %core_libs_dbg% %os_libs%

popd

