
# log, timeout, and screen defaults file
*NOCOLOR
*LOG $EL_log
@$EL_timeout

# add shell aliases for converting BLE output logs from hex to ascii
>>. ./bashrc
>

; ============ WaterGuru $EL_pod $EL_testname: Connect to BLE ============ 

>hcitool lescan >> $EL_SCANLOG
:5
>^C
> sort -u $EL_SCANLOG | fgrep $EL_pod
+$address=\n(([0-9A-Fa-f]{2}:){5}([0-9A-Fa-f]{2})) WaterGuru:$EL_pod
>

*/[$address][LE]>/
>screen -c screenrc -L -Logfile $EL_SCREENLOG -S $EL_testname gatttool -I --listen -b $address
>connect
-<Error
-<connect error
-<connect: Device or resource busy (16)
<Connection successful
>
>>^A
>^D
>

# ? $EL_power == NONE ? %SKIP_POWER_LOG
# ; ============ WaterGuru $EL_pod $EL_testname: Connect to Power Supply $EL_power ============ 
# >>screen -c screenrc -L -Logfile $EL_POWERLOG -S power-${EL_testname} picocom --baud 9600 --echo --omap crcrlf --imap lfcrlf -r $EL_power
# <<Terminal ready
# >>*IDN?
# <<B&K Precision, 9201
# # loop here measuring current used
# #
# # >>MEAS:VOLT?
# #
# >>^A
# >^D
# >
# %SKIP_POWER_LOG

##-------------------------------------------------------------------##

; ============ WaterGuru $EL_pod $EL_testname: log test start ============
>cp /dev/null $EL_SCREENLOG
>screen -r $EL_testname -S -X stuff "char-write-req 0x001b `echo -n set log start | xxd -ps`\015"

#>echo -n "set log \"$EL_testname\"" | xxd -ps
#+$cmd=\n(.*)
#>screen -r $EL_testname
#>char-write-req 0x001b $cmd
#<Characteristic value was written successfully
#<Notification handle = 0x001b value: 4c 4f 47 47 45 44 3a
#>
#>>^A
#>^D
#>

; ============ WaterGuru $EL_pod $EL_testname: Verify e.g. "LOGGED: start" ============
>dehex $EL_SCREENLOG
-<Please try again
-<Unknown
<LOGGED: start

