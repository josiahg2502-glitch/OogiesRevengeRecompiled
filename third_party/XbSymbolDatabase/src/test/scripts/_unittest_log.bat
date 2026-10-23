@ECHO OFF

IF "%~1"=="" (
"%~dp0XbSymbolDatabaseUnitTest.exe" > "%~dp0UnitTest.log"
) ELSE (
"%~dp0XbSymbolDatabaseUnitTest.exe" "%~1" > "%~dp0UnitTest.log"
)
