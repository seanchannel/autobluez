
# log, timeout, and screen defaults file
*NOCOLOR
*LOG $EL_log
@$EL_timeout

# add shell aliases for converting BLE output logs from hex to ascii
>>. ./bashrc
>

; ============ $EL_testname: Connect to BLE ============ 
*/[$EL_address][LE]>/
>screen -c screenrc -L -Logfile $EL_SCREENLOG -S $EL_testname gatttool -I --listen -b $EL_address
>connect
-<Error
-<connect error
-<connect: Device or resource busy (16)
<Connection successful
>
>>^A
>^D
>

; ============ $EL_testname: Connect to Power Supply ============ 

? $EL_powerdev == NONE ? %SKIP_POWER_LOG
>>screen -c screenrc -L -Logfile $EL_POWERLOG -S power-${EL_testname} picocom --baud 9600 --echo --omap crcrlf --imap lfcrlf -r $EL_powerdev
<<Terminal ready
>>*IDN?
<<B&K Precision, 9201
>>^A
>^D
>
%SKIP_POWER_LOG

##-------------------------------------------------------------------##

; ============ $EL_testname: "set log $EL_logmark" ============
>cp /dev/null $EL_SCREENLOG
>echo -n "set log $EL_logmark" | xxd -ps
+$cmd=\n(.*)
>screen -r $EL_testname
>char-write-req 0x001b $cmd
<Characteristic value was written successfully
<Notification handle = 0x001b value: 4c 4f 47 47 45 44 3a
>
>>^A
>^D
>

; ============ $EL_testname: Verify e.g. "LOGGED: $EL_logmark" ============
>dehex $EL_SCREENLOG
-<Please try again
-<Unknown
<LOGGED: $EL_logmark

