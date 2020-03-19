@echo off

set PROGRAM="%~1"

echo %PROGRAM%

REM запуск программы без параметров
%PROGRAM% > "%TEMP%\noparamOut.txt"
if NOT %ERRORLEVEL% == 1 goto err
fc.exe "%TEMP%\noparamOut.txt" noparamRes.txt
if ERRORLEVEL 1 goto err


echo.

REM запуск программы с несуществующим именем файла
%PROGRAM% notexistingfile.txt > "%TEMP%\notexistingOut.txt"
if NOT %ERRORLEVEL% == 1 goto err
fc.exe "%TEMP%\notexistingOut.txt" notexistingRes.txt
if ERRORLEVEL 1 goto err


echo.


rem не хватает строк в файле матрицы
%PROGRAM% testcases\onestring.txt > "%TEMP%\onestringOut.txt"
if NOT %ERRORLEVEL% == 1 goto err
fc.exe "%TEMP%\onestringOut.txt" onestringRes.txt
if ERRORLEVEL 1 goto err


rem не хватает элементов в строке
%PROGRAM% testcases\twoelemstrings.txt > "%TEMP%\twoelemstringsOut.txt" 
if NOT %ERRORLEVEL% == 1 goto err
fc.exe "%TEMP%\twoelemstringsOut.txt" twoelemstringsRes.txt
if ERRORLEVEL 1 goto err


rem в матрице есть нечисловой элемент
%PROGRAM% testcases\nonnumberindata.txt > "%TEMP%\nonnumberindataOut.txt" 
if NOT %ERRORLEVEL% == 1 goto err
fc.exe "%TEMP%\nonnumberindataOut.txt" nonnumberindataRes.txt
if ERRORLEVEL 1 goto err


rem вырожденная матрица
%PROGRAM% testcases\zerodet.txt > "%TEMP%\zerodetOut.txt" 
if NOT %ERRORLEVEL% == 2 goto err
fc.exe "%TEMP%\zerodetOut.txt" zerodetRes.txt
if ERRORLEVEL 1 goto err

rem при запуске с правильными параметрами ожидаетс¤ нулевой код возврата
%PROGRAM% testcases\regular.txt > "%TEMP%\regularOut.txt" 
if NOT %ERRORLEVEL% == 0 goto err
fc.exe "%TEMP%\regularOut.txt" regularRes.txt
if ERRORLEVEL 1 goto err




ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT