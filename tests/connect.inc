#!/usr/bin/env expect-lite

# log, timeout, and screen defaults file
#*NOINFO
*LOGAPPEND $EL_log
@$EL_timeout
#>rm -f $EL_POWERLOG $EL_BLELOG logs/*sample.log
>. ./bashrc

? $EL_serial == NONE ? [

;>~~~~~~~~> Connecting to WaterGuru BLE $EL_ble <~~~~~~~~
# scan BLE for the unit
*NODVPROMPT
>hcitool lescan
+$address=([0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]:[0-9A-Fa-f][0-9A-Fa-f]) WaterGuru:$EL_ble
>^C
*DVPROMPT

#connect the screen session to BLE
*/[$address][LE]>/
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname gatttool -I --listen -b $address
>connect
<Connection successful
>
>>^A
>^D
*//
>

#get the pod ID
> screen -r $EL_testname -X stuff "char-write-req 0x0001b 'echo -n "get podid" | xxd -ps'\015"
>dehex $EL_BLELOG
+$EL_pod=podId ([1-9][0-9]+)

]::[

;~~~~~~~~> Connecting to WaterGuru serial $EL_serial <~~~~~~~~
#connect the screen session to serial
*NODVPROMPT
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname screen $EL_serial 115200
>>
>>
>>^A
>^D
*DVPROMPT

#get the pod ID
> screen -r $EL_testname -X stuff "get podid\015"
>tail $EL_BLELOG
+$EL_pod=podId ([1-9][0-9]+)

]

>export EL_pod
