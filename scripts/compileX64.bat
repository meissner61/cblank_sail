
title %cd%
echo The Current Directory is: %cd%

::Change this line to match your Visual Studio vcvars.bat directory
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

::Change to your personal LIBRARY DIRECTORIES, REMEMBER NO SPACES AROUND = sign
set SDL2="C:\libs\SDL2-2.28.1"

::INCLUDE DIRECTORIES
set SDL2_INCLUDE="%SDL2%\include"

::LIBRARY DIRECTORIES
set SDL2_lib="%SDL2%\lib\x64"

::SOURCE FILES
set SRC_FILES=  ../src/*.c

::Make bin and intermediate directory if its not there
call mkdir ..\bin\x64\
call mkdir ..\intermediate\

::copy require .DLLs
call copy "%SDL2_lib%\SDL2.dll" "..\bin\x64\"

::compile with the aformentioned flags and directories
call cl %SRC_FILES% /std:c++17 /EHsc /W4 ^
        /Fo../intermediate/ ^
        /I%SDL2_INCLUDE% ^
        /link ^
        /LIBPATH:%SDL2_lib% ^
        user32.lib ^
        SDL2main.lib ^
        SDL2.lib ^
        shell32.lib ^
        /SUBSYSTEM:CONSOLE /out:../bin/x64/main.exe

