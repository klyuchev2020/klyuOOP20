@echo off

set PROGRAM="%~1"

echo %PROGRAM%

REM запуск программы без параметров
%PROGRAM% 
if NOT %ERRORLEVEL% == 1 goto err

echo.


REM запуск программы с одним параметром, несуществующий входной файл
%PROGRAM% notexistingfile
if NOT %ERRORLEVEL% == 1 goto err

echo.


rem нет ни начальной, ни конечной точки
%PROGRAM% testNoSymbsInLab.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem есть начальная, но нет конечной точки
%PROGRAM% testNoB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem нет начальной, есть конечная точка
%PROGRAM% testNoA.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem одна начальная, две конечные точки
%PROGRAM% testOneATwoB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem две начальные, одна конечная точка
%PROGRAM% testTwoAOneB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem две начальные, ни одной конечной точки
%PROGRAM% testTwoANoB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem две конечные, ни одной начальной точки
%PROGRAM% testNoATwoB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem некорректные символы в файле лабиринта
%PROGRAM% testWrongSymbs.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem отсутствует путь между начальной и конечной точкой
%PROGRAM% testlabyrinth4NoPath.txt
if NOT %ERRORLEVEL% == 2 goto err

echo.

rem разные случаи построения путей

%PROGRAM% testlabyrinth1.txt
if NOT %ERRORLEVEL% == 0 goto err

echo.

%PROGRAM% testlabyrinth2.txt
if NOT %ERRORLEVEL% == 0 goto err

echo.

%PROGRAM% testlabyrinth3.txt
if NOT %ERRORLEVEL% == 0 goto err

echo.

%PROGRAM% testlabyrinth5.txt
if NOT %ERRORLEVEL% == 0 goto err

echo.

%PROGRAM% testlabyrinth6.txt
if NOT %ERRORLEVEL% == 0 goto err

echo.

%PROGRAM% testThinWalls.txt
if NOT %ERRORLEVEL% == 0 goto err

echo.


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT