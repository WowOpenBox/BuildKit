copy ..\WowOpenBox\WowOpenBox.tcl OpenMultiBoxing.vfs\app\WowOpenBox.tkapp
powershell -NoProfile -ExecutionPolicy Bypass -File build.ps1 -Out OpenMultiBoxing.exe
rem .\OpenMultiBoxing.exe -debug
.\rrenable-debug.exe
