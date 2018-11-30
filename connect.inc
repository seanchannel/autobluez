
# log, timeout, and screen defaults file
*LOG $EL_log
@$EL_timeout

# shortcut / alias to convert BLE output logs from hex to ascii
>>dehex()
>>{
>>    cat $1 | egrep -a Notification | cut -f7 -d: | sed 's/^/0a/g' | xxd -r -ps
>>    echo
>}

; ============ $EL_testname: Connect to pod ============ 
*/[$EL_address][LE]>/
>screen -c screenrc -L -Logfile $EL_SCREENLOG -S $EL_testname gatttool -I --listen -b $EL_address
>connect
-<Error
-<connect error
-<connect: Device or resource busy (16)
<Connection successful
>>^A
>^D

