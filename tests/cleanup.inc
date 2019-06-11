
; ============ WaterGuru $EL_pod $EL_testname: Disconnect ============
>>screen -r $EL_testname -S -X stuff 'exit\015'
#>>killall screen
>rm -f $EL_SCANLOG
# >rm -f $EL_SCREENLOG $EL_POWERLOG $EL_SCANLOG
