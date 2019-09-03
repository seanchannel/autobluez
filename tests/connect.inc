
# log, timeout, and screen defaults file
#*NOINFO
*LOGAPPEND $EL_log
@$EL_timeout


>rm -f $EL_POWERLOG $EL_BLELOG logs/*sample.log
>. ./bashrc
>

#? $EL_power == NONE ? %SKIP_POWER_LOG
#>>screen -c $EL_SCREENRC -L -Logfile $EL_POWERLOG -S power-${EL_testname} -d -m tests/log_power
#; waiting 30 sec. for pod startup...
#:30
#%SKIP_POWER_LOG

; scanning for BLE address...
*NODVPROMPT
>hcitool lescan
+$address=([0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]) WaterGuru:$EL_pod
>^C
*DVPROMPT

; connecting to BLE...
*/[$address][LE]>/
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname gatttool -I --listen -b $address
>connect
<Connection successful
>
>>^A
>^D
>
