
# log, timeout, and screen defaults file
#*NOINFO
*LOGAPPEND $EL_log
@$EL_timeout
*~../cleanup.inc


; -+-+-+-> WaterGuru $EL_pod $EL_testname: Setup

>rm -f $EL_SCANLOG $EL_POWERLOG $EL_BLELOG logs/*sample.log
>. ./.bashrc
>

? $EL_power == NONE ? %SKIP_POWER_LOG
>>screen -c $EL_SCREENRC -L -Logfile $EL_POWERLOG -S power-${EL_testname} -d -m tests/log_power
; waiting 30 sec. for pod startup...
:30
%SKIP_POWER_LOG

; searching 10 sec. for BLE address...
>>hcitool lescan >> $EL_SCANLOG
:10
>^C
> sort -u $EL_SCANLOG | fgrep $EL_pod
+$address=\n(([0-9A-Fa-f]{2}:){5}([0-9A-Fa-f]{2})) WaterGuru:$EL_pod
? $address == __NO_STRING_CAPTURED__ ? *FAIL

; connecting to BLE...
*/[$address][LE]>/
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname gatttool -I --listen -b $address
>connect
<Connection successful
>
>>^A
>^D
>

; -+-+-+-> WaterGuru $EL_pod $EL_testname: log test start 

>screen -r $EL_testname -S -X stuff "char-write-req 0x001b `echo -n set log start | xxd -ps`\015"
:2
>dehex $EL_BLELOG
<LOGGED: start

