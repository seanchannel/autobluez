
; ============ WaterGuru $EL_pod $EL_testname: log test end and cleanup ============
>screen -r $EL_testname -S -X stuff "char-write-req 0x001b `echo -n set log start | xxd -ps`\015"
>screen -r $EL_testname -S -X stuff 'exit\015'
>killall screen
