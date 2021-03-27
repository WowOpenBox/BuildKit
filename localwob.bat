copy ..\WowOpenBox\WowOpenBox.tcl OpenMultiBoxing.vfs\app\WowOpenBox.tkapp
tclkit\tclkit.exe  sdx/sdx.kit wrap OpenMultiBoxing -runtime runtime.exe
del OpenMultiBoxing.exe
rename OpenMultiBoxing OpenMultiBoxing.exe
rem .\OpenMultiBoxing.exe -debug
.\rrenable-debug.exe
