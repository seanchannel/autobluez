
; -+-+-+-> WaterGuru $EL_pod $EL_testname: cleanup
>screen -r $EL_testname -X stuff "char-write-req 0x001b `echo -n set log end | xxd -ps`\015"
>screen -r $EL_testname -X stuff 'disconnect\015'
>screen -r $EL_testname -X stuff 'exit\015'

? $EL_power == NONE ? %SKIP_POWER_STOP
>killall screen
>screen -c $EL_SCREENRC -L -Logfile $EL_POWERLOG -S power-${EL_testname} tests/stop_power
>
%SKIP_POWER_STOP

; Thank you and have a nice day!
