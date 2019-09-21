#!/usr/bin/env expect-lite

# log, timeout, and screen defaults file
#*NOINFO
*LOGAPPEND $EL_log
@$EL_timeout
>rm -f $EL_POWERLOG $EL_BLELOG logs/*sample.log
>. ./bashrc
>

; ~~~~~~~~> Connecting to WaterGuru $EL_ble <~~~~~~~~
*NODVPROMPT
>hcitool lescan
+$address=([0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]) WaterGuru:$EL_ble
>^C
*DVPROMPT

*/[$address][LE]>/
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname gatttool -I --listen -b $address
>connect
<Connection successful
>
>char-write-req 0x001b 67657420706f6469640a
>>^A
>^D
>

>dehex $EL_BLELOG
-<Please try again
-<Unknown
+$podid=([1-9][0-9][0-9][0-9]+)

? $test_in_progress != 1 ? ~tests/cleanup.inc
