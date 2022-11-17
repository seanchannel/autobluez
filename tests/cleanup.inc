
; ~~~~~~~> WaterGuru $EL_pod $EL_testname: cleanup <~~~~~~~

? $EL_serial == NONE ? [
# BLE disconnect, gently
>screen -S $EL_testname -X stuff "char-write-req 0x001b `echo -n set log end | xxd -ps`\015"
>screen -S $EL_testname -X stuff 'disconnect\015'
>screen -S $EL_testname -X stuff 'exit\015'

]:[
# serial disconnect, just quit
>screen -S $EL_testname -X quit

]

? $EL_power != NONE ? [
>screen -S power-${EL_testname} -X quit

#>>OUTP 0
#>>SYST:LOC

] 
