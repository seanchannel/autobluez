#!/usr/bin/env expect-lite

# log, timeout, and screen defaults file
#*NOINFO
*LOGAPPEND $EL_log
@$EL_timeout
>rm -f $EL_POWERLOG $EL_BLELOG logs/*sample.log
>. ./bashrc
>

? $EL_serial == NONE ? [

;>~~~~~~~~> Connecting to WaterGuru BLE $EL_ble <~~~~~~~~
*NODVPROMPT
>hcitool lescan
+$address=([0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]) WaterGuru:$EL_ble
>^C
*DVPROMPT

>echo -n "get podid" | xxd -ps
+$cmd=\n(.*)
*/[$address][LE]>/
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname gatttool -I --listen -b $address
>connect
<Connection successful
>char-write-req 0x001b $cmd
<Characteristic value was written successfully
<Notification handle = 0x001b value: 24 70 6f 64 49 64
>
>>^A
>^D
>

>dehex $EL_BLELOG
+$EL_pod=podId ([1-9][0-9]+)

]::[

;~~~~~~~~> Connecting to WaterGuru serial $EL_serial <~~~~~~~~
*NODVPROMPT
# --initstring "$(echo -ne 'AAATZ\r\n\r\n')" 
>>picocom --quiet --logfile $EL_BLELOG --baud 115200 $EL_serial
>>
>>
>>get podid
+$EL_pod=.*podId ([1-9][0-9]+)
>>^A
>^X
>
*DVPROMPT

]

>export EL_pod
