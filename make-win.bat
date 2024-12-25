@echo off

REM Create bin directory if it doesn't exist
if not exist bin mkdir bin

cd bin

REM Remove win directory if it exists
if exist win rmdir /s /q win

REM Create win directory
mkdir win
cd win

@echo on
cmake -G "Visual Studio 17 2022" ../..
@echo off

cd ../..
