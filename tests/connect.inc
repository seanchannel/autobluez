#!/usr/bin/env expect-lite

# log, timeout, and screen defaults file
*NOINFO
*LOGAPPEND $EL_log
@$EL_timeout
>rm -f $EL_POWERLOG $EL_BLELOG logs/*sample.log
>. ./bashrc

? $EL_serial == NONE ? [
;>~~~~~~~~> Connecting to WaterGuru BLE $EL_ble <~~~~~~~~
# BLE scan & connect

*NODVPROMPT
>hcitool lescan
+$address=(.*) WaterGuru:$EL_ble
:1
>^C
*DVPROMPT
*/[$address][LE]>/
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname gatttool -I --listen -b $address
>connect
<Connection successful
>
>>^A
>^D
*//
>

# get the pod ID
> screen -r $EL_testname -X stuff "char-write-req 0x0001b \015\015"
> screen -r $EL_testname -X stuff "char-write-req 0x0001b `echo -n get podid | xxd -ps`\015"
>dehex $EL_BLELOG
+$EL_pod=podId (.+)
;pod ID $EL_pod

]::[

;~~~~~~~~> Connecting to WaterGuru serial $EL_serial <~~~~~~~~
# serial connect
*NODVPROMPT
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname screen $EL_serial 115200
>>v
>>
>>^A
>^D
*DVPROMPT

# get the pod ID
> screen -r $EL_testname -X stuff "\015"
> screen -r $EL_testname -X stuff "get podid\015"
*NODVPROMPT
>tail -f $EL_BLELOG
+$EL_pod=podId ([1-9][0-9]+)
*DVPRROMPT
>^C

]

>export EL_pod
