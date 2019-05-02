
; ============ $EL_testname: Connect to power supply ============ 
>>screen -c screenrc -L -Logfile $EL_POWERLOG -S power-${EL_testname} picocom --baud 9600 --echo --omap crcrlf --imap lfcrlf -r $EL_powerdev
<<Terminal ready
>>*IDN?
<<B&K Precision, 9201
>>^A
>^D
>

##-------------------------------------------------------------------##

