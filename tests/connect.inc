
# log, timeout, and screen defaults file
*NOCOLOR
*LOGAPPEND $EL_log
@$EL_timeout

>rm -f $EL_SCANLOG $EL_POWERLOG $EL_SCREENLOG
>>. ./.bashrc

; ============ WaterGuru $EL_pod $EL_testname: Connect to BLE ============ 

>hcitool lescan >> $EL_SCANLOG
:10
>^C
> sort -u $EL_SCANLOG | fgrep $EL_pod
+$address=\n(([0-9A-Fa-f]{2}:){5}([0-9A-Fa-f]{2})) WaterGuru:$EL_pod
>

*/[$address][LE]>/
>screen -c $EL_SCREENRC -L -Logfile $EL_SCREENLOG -S $EL_testname gatttool -I --listen -b $address
>connect
-<Error
-<connect error
-<connect: Device or resource busy
<Connection successful
>
>>^A
>^D
>

? $EL_power == NONE ? %SKIP_POWER_LOG
; ============ WaterGuru $EL_pod $EL_testname: Connect to Power Supply $EL_power ============ 
>screen -c $EL_SCREENRC -L -Logfile $EL_POWERLOG -S ${EL_testname}_power -d -m tests/log_power
# %SKIP_POWER_LOG

##-------------------------------------------------------------------##

; ============ WaterGuru $EL_pod $EL_testname: log test start ============
#>cp /dev/null $EL_SCREENLOG
>screen -r $EL_testname -S -X stuff "char-write-req 0x001b `echo -n set log start | xxd -ps`\015"

; ============ WaterGuru $EL_pod $EL_testname: Verify e.g. "LOGGED: start" ============
>dehex $EL_SCREENLOG
-<Please try again
-<Unknown
<LOGGED: start

