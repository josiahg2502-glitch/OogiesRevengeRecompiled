@ECHO OFF

IF "%~1"=="" (
"%~dp0XbSymbolDatabaseUnitTest.exe" --verbose
) ELSE (
"%~dp0XbSymbolDatabaseUnitTest.exe" "%~1" --verbose
)

PAUSE
