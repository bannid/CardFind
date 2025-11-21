@echo off
set StartTime=%time%
mkdir build
pushd build
rem Files
rem LibsPath
rem Libs
rem Includes


set FilesWin32Engine= ..\winmain.cpp
set Includes= ..\include
set LibsPath=/LIBPATH:"..\lib\"

set LibsWin32= kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib xaudio2.lib ole32.lib oleaut32.lib opengl32.lib glfw3.lib

set LibsFbxImporter= assimp.lib

cl /DDEBUG  /FeCardFind.exe /MD -FC -Zi %FilesWin32Engine% /I %Includes% /link %LibsPath% %LibsWin32%  /NODEFAULTLIB:MSVCRTD -subsystem:windows

cl /DDEBUG /LD ..\game\game.cpp /I %Includes% -Zi /link -PDB:game_%random%.pdb

echo ----------------------- TIMINGS -----------------------
echo BuildStarted: %StartTime%
echo BuildEnded  : %time%

echo -------------------------------------------------------

popd