
; ~~~~~~~> WaterGuru $EL_pod $EL_testname: cleanup <~~~~~~~

? $EL_power != NONE ? [
>>screen -S power-${EL_testname} -X quit
] 

; ~~~~~~~> WaterGuru $EL_pod $EL_testname: quitting screen <~~~~~~~
>>screen -S $EL_testname -X quit
; ~~~~~~~> WaterGuru $EL_pod $EL_testname: done <~~~~~~~


