@echo off

ECHO ======================================================
ECHO The Old Metin2 Project - Automated client build script
ECHO Only use on a clean project directory.
ECHO ======================================================

rem SET M2_MSVC_DIR=C:\Program Files\Microsoft Visual Studio\2022\Community\
rem SET M2_7ZIP_PATH=C:\Program Files\7-Zip\7z.exe

rem Check the environment variables
VERIFY OTHER 2>nul
SETLOCAL ENABLEEXTENSIONS
IF ERRORLEVEL 1 ECHO Unable to enable extensions
IF NOT DEFINED M2_MSVC_DIR (
	ECHO M2_MSVC_DIR is NOT defined! Please define M2_MSVC_DIR with the path of your local MSVC install.
	EXIT /B -1
)
IF NOT DEFINED M2_7ZIP_PATH (
	ECHO M2_7ZIP_PATH is NOT defined! Please define M2_7ZIP_PATH with the path of your local 7-Zip "7z.exe" executable.
	EXIT /B -1
)
ENDLOCAL

rem Cause variables to be expanded at execution time (in order for !errorlevel! to work)
SETLOCAL EnableDelayedExpansion

rem Initialize the MSVC environment
CALL "%M2_MSVC_DIR%\VC\Auxiliary\Build\vcvars32.bat"

rem Build
msbuild Metin2Client.sln /p:Configuration=Distribute /p:Platform="Win32"
if !errorlevel! neq 0 exit /b !errorlevel!

rem Start assembling the client package
RMDIR /S /Q dist
MKDIR dist\
COPY /Y build\bin\Distribute\UserInterface.exe dist\metin2.exe
COPY /Y build\bin\Distribute\Config.exe dist\config.exe

rem Copy over the data from the bin directory
xcopy bin\ dist\ /Y /Q
DEL /S dist\.gitignore
xcopy bin\BGM\ dist\BGM\ /E /Y /Q
xcopy bin\lib\ dist\lib\ /E /Y /Q
MKDIR dist\mark\
xcopy bin\miles\ dist\miles\ /E /Y /Q
MKDIR dist\pack\
COPY /Y bin\pack\Index dist\pack\
COPY /Y bin\pack\*.rdch dist\pack\
MKDIR dist\screenshot\
xcopy bin\upload\ dist\upload\ /E /Y /Q

rem Build and copy the archives
DEL /F /Q "bin\pack\*.zip"

FOR /d %%i IN ("bin\pack\*") DO (
	echo Packing %%i
	"%M2_7ZIP_PATH%" a "%%i.zip" ".\%%i\*"
	if !errorlevel! neq 0 exit /b !errorlevel!
) 
MOVE /Y bin\pack\*.zip dist\pack\
