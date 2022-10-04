#!/usr/bin/env expect-lite

# log, timeout, and screen defaults file
#*NOINFO
*LOGAPPEND $EL_log
@$EL_timeout
>rm -f $EL_POWERLOG $EL_BLELOG logs/*sample.log
>. ./bashrc
>

; ~~~~~~~~> Connecting to WaterGuru serial $EL_serial <~~~~~~~~
*//
>screen -c $EL_SCREENRC -L -Logfile $EL_BLELOG -S $EL_testname picocom --baud 115200 --imap lfcrlf $EL_serial
<Terminal ready
>get podid
+$podid=\n(.*)
>
>>^A
>^D
>

+$EL_pod=podId ([1-9][0-9]+)
>export EL_pod
