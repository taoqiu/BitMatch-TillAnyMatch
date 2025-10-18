@echo off
ConBitMatch.exe
if %errorlevel% equ 0 (
    echo 运行成功
) else (
    echo 运行失败，错误代码：%errorlevel%
)
cmd