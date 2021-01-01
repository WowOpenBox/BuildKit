copy ..\WowOpenBox\WowOpenBox.tkapp OpenMultiBoxing.vfs\app\
tclkit\tclkit.exe  sdx/sdx.kit wrap OpenMultiBoxing -runtime runtime.exe
del OpenMultiBoxing.exe
rename OpenMultiBoxing OpenMultiBoxing.exe
start .\OpenMultiBoxing.exe -debug
