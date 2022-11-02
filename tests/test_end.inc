
; -+-+-+-> WaterGuru $EL_pod $EL_testname: cleanup

# set log TESTEND
>echo -n "set log TESTEND" | xxd -ps
+$cmd=\n(.*)
>screen -r $EL_testname
>char-write-req 0x001b $cmd
<Characteristic value was written successfully
<Notification handle = 0x001b value: 24 4c 4f 47 3a 20 54 45 53 54 45 4e 44
>
>>^A
>^D
>

# $timers 1
>echo -n '$timers 1' | xxd -ps
+$cmd=\n(.*)
>screen -r $EL_testname
>char-write-req 0x001b $cmd
<Characteristic value was written successfully
<Notification handle = 0x001b value: 24 74 69 6d 65 72 73 20 31
>
>>^A
>^D
>

# $log upload
#@$EL_delay
#>echo -n '$log upload' | xxd -ps
#+$cmd=\n(.*)
#>screen -r $EL_testname
#>char-write-req 0x001b $cmd
#<Characteristic value was written successfully
#<Notification handle = 0x001b value: 24 6c 6f 67 20 75 70 6c 6f 61 64 20 4f 4b
#>
#>>^A
#>^D
#>
#@$EL_timeout

>screen -r $EL_testname -X stuff "char-write-req 0x001b `echo -n set log end | xxd -ps`\015"
>screen -r $EL_testname -X stuff 'disconnect\015'
>screen -r $EL_testname -X stuff 'exit\015'

#? $EL_power == NONE ? %SKIP_POWER_STOP
#>screen -r power-$EL_testname
#>^C
#:2
#>
#
#>picocom --echo --baud 9600 --omap crcrlf --imap lfcrlf -r $EL_power > /dev/null
#>>OUTP 0
#>>SYST:LOC
#>>^A
#>>^X
#%SKIP_POWER_STOP
