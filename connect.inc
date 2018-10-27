
# set logs from environment variables (via runtest)
*LOG $EL_log
@$EL_timeout
>export SCREENRC=$EL_SCREENRC
>export SCREENLOG=$EL_SCREENLOG

; ============ Connect to pod ============ 
*/[$EL_address][LE]>/
>screen gatttool -I --listen -b $EL_address
-<Usage
>>^A
>H
<logfile
>connect
-<Error
-<connect error
-<connect: Device or resource busy (16)
<Connection successful
>>^A
>^D

# get the screen id
>screen -list | grep pts | sort | head -1
+$myscreen=([0-9]+\.pts.[0-9]+.[a-z\- 0-9]+)

# get shortcut to convert BLE output from hex to ascii
>>. bashrc
