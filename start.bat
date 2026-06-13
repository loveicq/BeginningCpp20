@echo off
call "D:\Microsoft\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -arch=amd64
cd /d E:\cpp\Gitee\cpp20
if not exist tmp_build mkdir tmp_build
if not exist tmp_build\std.obj (
    echo Generating std.obj...
    cl /std:c++latest /EHsc /c /Fo:tmp_build\std.obj "%VCToolsInstallDir%\modules\std.ixx"
)
code .