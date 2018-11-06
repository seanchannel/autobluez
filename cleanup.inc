
; ============ $EL_testname: Cleanup ============
>>screen -r $EL_testname -S -X stuff 'exit\015'
>>kill %1
>rm $EL_SCREENLOG-tmp
