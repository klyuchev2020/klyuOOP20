@echo off

set PROGRAM="%~1"

echo %PROGRAM%

REM ������ ��������� ��� ����������
%PROGRAM% 
if NOT %ERRORLEVEL% == 1 goto err

echo.

REM ������ ��������� � ����� ����������
%PROGRAM% Hello_World72.txt 
if NOT %ERRORLEVEL% == 1 goto err

echo.

REM ������ ��������� � ����� �����������
%PROGRAM% crypt Hello_World72.txt 
if NOT %ERRORLEVEL% == 1 goto err

echo.

REM ������ ��������� � ����� �����������
%PROGRAM% decrypt Hello_World72.txt Hello_World72encoded
if NOT %ERRORLEVEL% == 1 goto err

echo.

REM ������ ��������� � �������� �����������, ������ ����������
%PROGRAM% cript Hello_World72.txt Hello_World72encoded 36
if NOT %ERRORLEVEL% == 1 goto err

echo.

REM ������ ��������� � �������� �����������, ��������� �� �����
%PROGRAM% crypt Hello_World72.txt Hello_World72encoded hw
if NOT %ERRORLEVEL% == 1 goto err

echo.

REM ������ ��������� � �������� �����������, ��������� -- �����, ������� 255
%PROGRAM% crypt Hello_World72.txt Hello_World72encoded 300
if NOT %ERRORLEVEL% == 1 goto err

echo.

REM ������ ��������� � �������� �����������, ��������� -- �����, ������� 0
%PROGRAM% crypt Hello_World72.txt Hello_World72encoded -1
if NOT %ERRORLEVEL% == 1 goto err

echo.

REM ������ ��������� � �������� �����������, �������������� ������� ����
%PROGRAM% crypt notexistingfile outputfile 20
if NOT %ERRORLEVEL% == 2 goto err

echo.

REM ������ ��������� � �������� �����������, �������������� �������� ����
%PROGRAM% crypt Hello_World0.txt notexistingfile2 20
if NOT %ERRORLEVEL% == 0 goto err

echo.


rem ������ ������������� ����� � ����� �������� �������������
%PROGRAM% crypt Hello_World0.txt Hello_World0encrypt 0
if NOT %ERRORLEVEL% == 0 goto err

echo.

%PROGRAM% decrypt Hello_World0encrypt Hello_World0encdec 0
if NOT %ERRORLEVEL% == 0 goto err

echo.

fc.exe /B Hello_World0.txt Hello_World0encdec
if ERRORLEVEL 1 goto err

echo.

rem ������ ������������� ����� � ����� �������� �������������, ��� ����� (�� ������ ������� �� 256 �����)
%PROGRAM% crypt AllBytes AllBytesEncrypt 0
if NOT %ERRORLEVEL% == 0 goto err

echo.

%PROGRAM% decrypt AllBytesEncrypt AllBytesEncDec 0
if NOT %ERRORLEVEL% == 0 goto err

echo.

fc.exe /B AllBytesEncDec AllBytes
if ERRORLEVEL 1 goto err

echo.
echo "single 1-bits in byte mixing"
echo.

rem ������ ������������� �����, ����� � ������������ ��������� �����, ��������� � ��������� ��������
%PROGRAM% crypt single1bytes single1bytesMixed 0
if NOT %ERRORLEVEL% == 0 goto err
fc.exe /B single1bytesMixed single1bytesMixedRes
if ERRORLEVEL 1 goto err


rem ����� 00000000, 00000001, 00000011, 00000111, 00001111, 00011111, 00111111, 01111111, 11111111, �������� ������������� �����
%PROGRAM% decrypt justanotherbyteset justanotherbytesetRevMixed 0
if NOT %ERRORLEVEL% == 0 goto err
fc.exe /B justanotherbytesetRevMixed justanotherbytesetRevMixedRes
if ERRORLEVEL 1 goto err

rem ������ ������������� ����� � ����� �������� �������������, ���� jpg
%PROGRAM% crypt 44.jpg 44encrypt 100
if NOT %ERRORLEVEL% == 0 goto err

echo.

%PROGRAM% decrypt 44encrypt 44encdec 100
if NOT %ERRORLEVEL% == 0 goto err

echo.

fc.exe /B 44.jpg 44encdec
if ERRORLEVEL 1 goto err

echo.


ECHO Program testing succeeded :-)

EXIT

:err
ECHO Program testing failed :-(
EXIT