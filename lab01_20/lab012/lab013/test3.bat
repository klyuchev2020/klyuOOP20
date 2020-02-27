@echo off

set PROGRAM="%~1"

echo %PROGRAM%

REM запуск программы без параметров
%PROGRAM%
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с несуществующим именем файла
%PROGRAM% notexistingfile.txt
IF NOT ERRORLEVEL 1 GOTO err

echo.


rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% testcases\onestring.txt > "%TEMP%\onestringRes.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\onestringRes.txt" testcases\onestringRes.txt
if ERRORLEVEL 1 goto err


rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% testcases\twoelemstrings.txt > "%TEMP%\twoelemstringsRes.txt" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\twoelemstringsRes.txt" testcases\twoelemstringsRes.txt
if ERRORLEVEL 1 goto err


rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% testcases\nonnumberindata.txt > "%TEMP%\nonnumberindataRes.txt" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\nonnumberindataRes.txt" testcases\nonnumberindataRes.txt
if ERRORLEVEL 1 goto err


rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% testcases\zerodet.txt > "%TEMP%\zerodetRes.txt" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\zerodetRes.txt" testcases\zerodetRes.txt
if ERRORLEVEL 1 goto err

rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% testcases\regular.txt > "%TEMP%\regularRes.txt" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\regularRes.txt" testcases\regularRes.txt
if ERRORLEVEL 1 goto err




ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT