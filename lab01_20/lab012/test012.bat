@echo off

set PROGRAM="%~1"

echo %PROGRAM%

REM запуск программы без параметров
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с одним параметром
%PROGRAM% theOnlyParameter
IF NOT ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с двумя параметрами
%PROGRAM% oneParameter twoParameter
IF NOT ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, первый не число 
%PROGRAM% ab 13 34ret453 > WrongSourceOut.txt
IF NOT ERRORLEVEL 2 GOTO err
FC /B WrongSourceOut.txt WrongSourceRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, первый слишком большой 
%PROGRAM% 37 13 34ret453 > BigSourceOut.txt
IF NOT ERRORLEVEL 2 GOTO err
FC /B BigSourceOut.txt BigSourceRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, второй меньше 2 
%PROGRAM% 23 1a 34ret453 > SmallDestOut.txt
IF NOT ERRORLEVEL 2 GOTO err
FC /B SmallDestOut.txt SmallDestRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка с 
REM невалидными символами 
%PROGRAM% 13 17 256w3 > WrongSymbOut.txt
IF NOT ERRORLEVEL 3 GOTO err
FC /B WrongSymbOut.txt WrongSymbRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает слишком большое число 
%PROGRAM% 13 17 100000000000000 > TooBigNumberOut.txt
IF NOT ERRORLEVEL 3 GOTO err
FC /B TooBigNumberOut.txt TooBigNumberRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает максимальное целое число 
%PROGRAM% 10 16 2147483647 > MaxIntNumberOut.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B MaxIntNumberOut.txt MaxIntNumberRes.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает минимальное целое число 
%PROGRAM% 10 16 -2147483648 > MinIntNumberOut.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B MinIntNumberOut.txt MinIntNumberRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает 0 
%PROGRAM% 10 16 0 > ZeroOut.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B ZeroOut.txt ZeroRes.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число, на 1 больше минимального 
%PROGRAM% 10 16 -2147483647 > AlmostMinNumberOut.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B AlmostMinNumberOut.txt AlmostMinNumberRes.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 2020 
%PROGRAM% 10 3 2020 > 2020To3Out.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B 2020To3Out.txt 2020To3Res.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 2020 
%PROGRAM% 3 10 2202211 > 2020From3Out.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B 2020From3Out.txt 2020From3Res.txt
IF ERRORLEVEL 1 GOTO err

echo.


REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 10000 в 25ричной системе и переводит в 23ичную 
%PROGRAM% 25 23 G00 > From25To23Out.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B From25To23Out.txt From25To23Res.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами, источник и приемник валидные, строка 
REM изображает число 10000 в 25ричной системе и переводит в 23ичную 
%PROGRAM% 23 25 IKI > From23To25Out.txt
IF NOT ERRORLEVEL 0 GOTO err
FC /B From23To25Out.txt From23To25Res.txt
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