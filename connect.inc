
# log, timeout, and screen defaults file
*LOG $EL_log
@$EL_timeout

; ============ $EL_testname: Connect to pod ============ 
*/[$EL_address][LE]>/
>screen -c screenrc -L -Logfile $EL_SCREENLOG gatttool -I --listen -b $EL_address
>connect
-<Error
-<connect error
-<connect: Device or resource busy (16)
<Connection successful
>>^A
>^D

>tail -s 0 -f $EL_SCREENLOG >> $EL_SCREENLOG-tmp &

# get the screen id
>screen -list | grep pts | sort | head -1
+$myscreen=([0-9]+\.pts.[0-9]+.[a-z\- 0-9]+)

# get shortcut to convert BLE output from hex to ascii
>>. bashrc
