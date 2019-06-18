
# log, timeout, and screen defaults file
#*NOCOLOR
*LOGAPPEND $EL_log
@$EL_timeout
*~../cleanup.inc


; -+-+-+-> WaterGuru $EL_pod $EL_testname: Setup
$result=FAIL
$testitem=testSetup
$testcond=0
$testvalue=connect

>rm -f $EL_SCANLOG $EL_POWERLOG $EL_BLELOG
>. ./.bashrc
>

? $EL_power == NONE ? %SKIP_POWER_LOG
>screen -c $EL_SCREENRC -L -Logfile $EL_POWERLOG -S ${EL_testname}-power -d -m tests/log_power
; pod startup
:30
%SKIP_POWER_LOG

; scan for BLE address
>>hcitool lescan >> $EL_SCANLOG
:10
>^C
> sort -u $EL_SCANLOG | fgrep $EL_pod
+$address=\n(([0-9A-Fa-f]{2}:){5}([0-9A-Fa-f]{2})) WaterGuru:$EL_pod
? $address == __NO_STRING_CAPTURED__ ? *FAIL
>

; connect to BLE
*/[$address][LE]>/
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname gatttool -I --listen -b $address
>connect
-<Error
-<connect error
-<connect: Device or resource busy
<Connection successful
>
>>^A
>^D
>

; -+-+-+-> WaterGuru $EL_pod $EL_testname: log test start 

>screen -r $EL_testname -S -X stuff "char-write-req 0x001b `echo -n set log start | xxd -ps`\015"
>dehex $EL_BLELOG
-<Please try again
-<Unknown
<LOGGED: start

