@echo off

set PROGRAM="%~1"

echo %PROGRAM%

REM запуск программы без параметров
%PROGRAM% > "%TEMP%\noparOut.txt"
if NOT ERRORLEVEL 0 goto err
fc.exe "%TEMP%\noparOut.txt" noparRes.txt
if ERRORLEVEL 1 goto err

echo.

REM запуск программы с одним параметром
%PROGRAM% theOnlyParameter > "%TEMP%\onlyparOut.txt"
IF NOT ERRORLEVEL 0 GOTO err
fc.exe "%TEMP%\onlyparOut.txt" onlyparRes.txt
if ERRORLEVEL 1 goto err

echo.

REM запуск программы с двумя параметрами
%PROGRAM% oneParameter twoParameter > "%TEMP%\twoparOut.txt"
IF NOT ERRORLEVEL 0 GOTO err
fc.exe "%TEMP%\twoparOut.txt" twoparRes.txt
if ERRORLEVEL 1 goto err

echo.


REM запуск программы с тремя параметрами, первый не число 
%PROGRAM% ab 13 34ret453 > "%TEMP%\WrongSourceOut.txt"
IF NOT ERRORLEVEL 0 GOTO err
fc.exe "%TEMP%\WrongSourceOut.txt" wrongSrcRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, первый слишком большой 
%PROGRAM% 37 13 34ret453 > "%TEMP%\BigSourceOut.txt"
IF NOT ERRORLEVEL 0 GOTO err
fc.exe "%TEMP%\BigSourceOut.txt" bigSrcRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, второй меньше 2 
%PROGRAM% 23 1a 34ret453 > "%TEMP%\smallDstOut.txt"
IF NOT ERRORLEVEL 0 GOTO err
fc.exe "%TEMP%\smallDstOut.txt" smallDstRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка с 
REM невалидными символами 
%PROGRAM% 13 17 256w3 > "%TEMP%\wrongSmbOut.txt" 
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\wrongSmbOut.txt" wrongSmbRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает слишком большое число 
%PROGRAM% 13 17 100000000000000 > "%TEMP%\tooBigNumberOut.txt"
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\tooBigNumberOut.txt" tooBigNumRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает максимальное целое число 
%PROGRAM% 10 16 2147483647 > "%TEMP%\tooBigNumberOut.txt"
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\tooBigNumberOut.txt" maxIntNumRes.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает минимальное целое число 
%PROGRAM% 10 16 -2147483648 > "%TEMP%\minIntNumOut.txt"
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\minIntNumOut.txt" minIntNumRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает 0 
%PROGRAM% 10 16 0 > "%TEMP%\zeroOut.txt"
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\zeroOut.txt" zerooRes.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число, на 1 больше минимального 
%PROGRAM% 10 16 -2147483647 > "%TEMP%\almostMinNumber.txt"
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\almostMinNumber.txt" almostMinNumRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 2020 
%PROGRAM% 10 3 2020 > "%TEMP%\2020To3Out.txt"
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\2020To3Out.txt" 2020To3_Res.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 2020 
%PROGRAM% 3 10 2202211 > "%TEMP%\2020From3Out.txt"
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\2020From3Out.txt" 2020From3_Res.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 10000 в 25ричной системе и переводит в 23ичную 
%PROGRAM% 25 23 G00 > "%TEMP%\From25To23Out.txt"
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\From25To23Out.txt" from25To23_Res.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 10000 в 25ричной системе и переводит в 23ичную 
%PROGRAM% 23 25 IKI > "%TEMP%\From23To25Out.txt"
IF NOT ERRORLEVEL 0 GOTO err
FC "%TEMP%\From23To25Out.txt" from23To25_Res.txt
IF ERRORLEVEL 1 GOTO err

echo.

%PROGRAM% 2 16 1001001
echo.
%PROGRAM% 16 2 ffff




ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT