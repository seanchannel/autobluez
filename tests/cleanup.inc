
; ============ WaterGuru $EL_pod $EL_testname: Cleanup ============
## >>screen -r $EL_testname -S -X stuff 'exit\015'
>>killall screen
## >rm -f $EL_SCREENLOG $EL_POWERLOG
