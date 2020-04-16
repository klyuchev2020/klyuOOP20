@echo off

set PROGRAM="%~1"

echo %PROGRAM%

REM ������ ��������� ��� ����������
%PROGRAM% 
if NOT %ERRORLEVEL% == 1 goto err

echo.


REM ������ ��������� � ����� ����������, �������������� ������� ����
%PROGRAM% notexistingfile
if NOT %ERRORLEVEL% == 1 goto err

echo.


rem ��� �� ���������, �� �������� �����
%PROGRAM% testNoSymbsInLab.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem ���� ���������, �� ��� �������� �����
%PROGRAM% testNoB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem ��� ���������, ���� �������� �����
%PROGRAM% testNoA.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem ���� ���������, ��� �������� �����
%PROGRAM% testOneATwoB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem ��� ���������, ���� �������� �����
%PROGRAM% testTwoAOneB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem ��� ���������, �� ����� �������� �����
%PROGRAM% testTwoANoB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem ��� ��������, �� ����� ��������� �����
%PROGRAM% testNoATwoB.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem ������������ ������� � ����� ���������
%PROGRAM% testWrongSymbs.txt
if NOT %ERRORLEVEL% == 1 goto err

echo.

rem ����������� ���� ����� ��������� � �������� ������
%PROGRAM% testlabyrinth4NoPath.txt
if NOT %ERRORLEVEL% == 2 goto err

echo.

rem ������ ������ ���������� �����

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