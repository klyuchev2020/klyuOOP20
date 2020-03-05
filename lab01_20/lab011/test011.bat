@echo off

set PROGRAM="%~1"

echo %PROGRAM%
echo %TEMP%


REM запуск программы без параметров
%PROGRAM%
IF NOT ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с одним параметром
%PROGRAM% theOnlyParameter
IF NOT ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с тремя параметрами 
%PROGRAM% testcases\houseJackShort.txt cat dog > "%TEMP%\output091.txt"
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем несуществующего файла
%PROGRAM% notExistingFile anyString > "%TEMP%\outputNotExists.txt"
IF NOT ERRORLEVEL 1 GOTO err
FC "%TEMP%\outputNotExists.txt" testcases\notExistingFileResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с отсутствующим образцом
%PROGRAM% testcases\houseJackShort.txt hgfedcba > "%TEMP%\outputAbsent.txt"
IF NOT ERRORLEVEL 1 GOTO err
FC "%TEMP%\outputAbsent.txt" testcases\houseShortAbsentResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
%PROGRAM% testcases\houseJackShort.txt dog > "%TEMP%\outputDog.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\outputDog.txt" testcases\houseShortDogResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
%PROGRAM% testcases\houseJackShort.txt rat > "%TEMP%\outputRat.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\outputRat.txt" testcases\houseShortRatResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
%PROGRAM% testcases\houseJackShort.txt at > "%TEMP%\outputAt.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\outputAt.txt" testcases\houseShortAtResult.txt
IF ERRORLEVEL 1 GOTO err

echo.

REM запуск программы с именем существующего файла и с присутствующим образцом
%PROGRAM% testcases\houseJackFull.txt Ja > "%TEMP%\outputJaFull.txt"
IF ERRORLEVEL 1 GOTO err
FC "%TEMP%\outputJaFull.txt" testcases\houseJackFullJaResult.txt
IF ERRORLEVEL 1 GOTO err

echo.


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT 