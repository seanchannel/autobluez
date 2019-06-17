
; -+-+-+-> WaterGuru $EL_pod $EL_testname: cleanup
>screen -r $EL_testname -X stuff "char-write-req 0x001b `echo -n set log end | xxd -ps`\015"
>screen -r $EL_testname -X stuff 'disconnect\015'
>screen -r $EL_testname -X stuff 'exit\015'

? $EL_power == NONE ? %SKIP_POWER_STOP
>screen -r $EL_testname-power
>^C
>
>screen -c $EL_SCREENRC -L -Logfile $EL_POWERLOG -S ${EL_testname}-power tests/stop_power
%SKIP_POWER_STOP

# station log goes here
>echo `date +%C%y%m%d:%H%m%S`, $EL_testname, $EL_mfg, $EL_user, $testitem, $testcond, $testvalue, $result >> $EL_stationlog
