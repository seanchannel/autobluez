
# log, timeout, and screen defaults file
*NOCOLOR
*LOG $EL_log
@$EL_timeout

# add shell aliases for converting BLE output logs from hex to ascii
>>. ./bash_aliases
>

; ============ $EL_testname: Connect to pod ============ 
*/[$EL_address][LE]>/
>screen -c screenrc -L -Logfile $EL_SCREENLOG -S $EL_testname gatttool -I --listen -b $EL_address
>connect
-<Error
-<connect error
-<connect: Device or resource busy (16)
<Connection successful
>
>>^A
>^D
>

