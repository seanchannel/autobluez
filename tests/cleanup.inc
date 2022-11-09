
; ~~~~~~~> WaterGuru $EL_pod $EL_testname: cleanup <~~~~~~~

? $EL_serial == NONE ? [
# BLE disconnect, gently
>screen -r $EL_testname -X stuff "char-write-req 0x001b `echo -n set log end | xxd -ps`\015"
>screen -r $EL_testname -X stuff 'disconnect\015'
>screen -r $EL_testname -X stuff 'exit\015'

]:[
# serial disconnect
>screen -S $EL_testname -X quit

]

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
#
#] 
