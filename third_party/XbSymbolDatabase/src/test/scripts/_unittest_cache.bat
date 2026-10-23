@ECHO OFF
SETLOCAL EnableDelayedExpansion

SET "SCRIPT_DIR=%~dp0"

SET fileC=0
SET dirC=0
:: Sort all inputs from user into directory and file lists
:ARGI_LOOP
FOR /F "tokens=1,2 delims=d" %%A IN ("-%~a1") DO (
 IF "%%B" neq "" (
  :: input is a directory
  SET /A dirC+=1
  SET "dirs[!dirC!]=%~s1"
 ) else if "%%A" neq "-" (
  :: input is a file
  SET /A fileC+=1
  SET "xbes[!fileC!]=%~s1"
 ) else (
  ECHO ERROR: "%~1" does not exist
 )
)
SHIFT
:: Continue in loop if user has more inputs
IF NOT "%~1" == "" GOTO ARGI_LOOP

:: Skip if we don't have any directory in the list.
IF %dirC% EQU 0 GOTO SKIP_DIRS_LOOP
SET dirI=1

:DIRS_LOOP
SET "dir=!dirs[%dirI%]!"
:: Look in each sub directory to find filtered files found.
FOR /R "%dir%" %%i IN (*.xbe) DO (
  SET /A fileC+=1
  SET "xbes[!fileC!]=%%~si"
)
SET /A dirI+=1
:: Continue loop until we hit the limit
IF %dirI% LEQ %dirC% GOTO DIRS_LOOP

:SKIP_DIRS_LOOP
:: Remove unused variables
SET "dirs="
SET "dirC="
SET "dirI="

:: Execute Unit Test program to generate cache files.
FOR /L %%i IN (1,1,%fileC%) DO (
 START "XbSymbolDatabaseUnitTest Cache #%%i" "%SCRIPT_DIR%XbSymbolDatabaseUnitTest.exe" "!xbes[%%i]!" -out "%SCRIPT_DIR%cache"
)

ENDLOCAL
