#!/usr/bin/env expect-lite

# log, timeout, and shell aliase (dehex)
#*NOINFO
*LOGAPPEND $EL_log
@$EL_timeout
>rm -f $EL_POWERLOG $EL_BLELOG logs/*sample.log
>. ./bashrc

? $EL_serial == NONE ? [
;>~~~~~~~~> Connecting to WaterGuru BLE $EL_ble <~~~~~~~~

# BLE scan
*NODVPROMPT
>hcitool lescan
+$address=(.*) WaterGuru:$EL_ble
>^C
*DVPROMPT

# BLE connect
*/[$address][LE]>/
>screen -L -Logfile $EL_BLELOG -S $EL_testname gatttool -I --listen -b $address
>connect
-<Function not implemented
-<Error
<Connection successful
>
>>^A
>^D
*//
>

# get the pod ID
> screen -S $EL_testname -X stuff "char-write-req 0x0001b \015\015"
:1
> screen -S $EL_testname -X stuff "char-write-req 0x0001b `echo -n get podid | xxd -ps`\015"
>dehex $EL_BLELOG
+$EL_pod=podId (.+)

]::[
;~~~~~~~~> Connecting to WaterGuru serial $EL_serial <~~~~~~~~

# serial connect
*NODVPROMPT
>screen -L -Logfile $EL_BLELOG -S $EL_testname screen $EL_serial 115200
>>
>>
>>^A
>^D
*DVPROMPT

# get the pod ID
> screen -S $EL_testname -X stuff "\015\015"
> screen -S $EL_testname -X stuff "get podid\015"
>tail $EL_BLELOG | grep podId
+$EL_pod=podId ([1-9][0-9]+)

]
>export EL_pod

? $EL_power != NONE ? [
;~~~~~~~~> Connecting to WaterGuru power supply <~~~~~~~~
>screen -L -Logfile $EL_POWERLOG -S power-${EL_testname} -d -m tests/log_power
]

;~~~~~~~~> Connected to WaterGuru $EL_pod <~~~~~~~~
