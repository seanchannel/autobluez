# WaterGuru tester .profile

# always use "-s 0" with 'tail' for no-delay
alias tail='tail -s 0'

# translate hex input pasted into the command line up until ^D is pressed
alias dx='cut -f2 -d: | sed '\''s/^/0a/g'\'' | xxd -r -ps; echo'

# send a comman to a pod without waiting for notificatsions
# e.g. 'blip <mypod> restart' or 'blip <mypod> pad test 2'
blip()
{
	POD=`fgrep -his $1 podnames | awk '{print $1}'`; shift
	COMMAND=`echo -n $* | xxd -ps`
	
        gatttool -b $POD --char-write-req --handle=0x001b --value=$COMMAND
}

# send a comman to a pod and show notifications until ^C is pressed. 
# same syntax as above, but stays connected until you press Control-c.
bleep()
{
	POD=`fgrep -his $1 podnames | awk '{print $1}'`; shift
	COMMAND=`echo -n $* | xxd -ps`
        gatttool --listen -b $POD --char-write-req --handle=0x001b --value=$COMMAND
}

# connect to pod BLE in gatttool. leaves you at the gatttool prompt until exit / ^D
ble()
{
	POD=`fgrep -his $1 podnames | awk '{print $1}'`; shift
        gatttool -I --listen -b $POD 
}

# convert a gatt log from hex into ascii
dehex()
{
    cat $1 | egrep -a Notification | cut -f7 -d: | sed 's/^/0a/g' | xxd -r -ps
    echo
}

