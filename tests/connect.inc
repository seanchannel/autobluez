#!/usr/bin/env expect-lite

# log, timeout, and screen defaults file
#*NOINFO
*LOGAPPEND $EL_log
@$EL_timeout
>rm -f $EL_POWERLOG $EL_BLELOG logs/*sample.log
>. ./bashrc
>

; ~~~~~~~~> Scanning for WaterGuru $EL_ble <~~~~~~~~
*NODVPROMPT
>hcitool lescan
+$address=([0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]) WaterGuru:$EL_ble
>^C
*DVPROMPT

; ~~~~~~~~> Connecting to WaterGuru $EL_ble <~~~~~~~~
>echo -n "get podid" | xxd -ps
+$cmd=\n(.*)
*/[$address][LE]>/
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname gatttool -I --listen -b $address
>connect
<Connection successful
>char-write-req 0x001b $cmd
<Characteristic value was written successfully
#<Notification handle = 0x001b value: 50 4f 44 20 49 44 20 3d
<Notification handle = 0x001b value: 24 70 6f 64 49 64
>
>>^A
>^D
>

>dehex $EL_BLELOG
-<Please try again
-<Unknown
+$EL_pod=podId ([1-9][0-9]+)
>export EL_pod
