
# WaterGuru tester .profile

export SCREENRC=$EL_SCREENRC
export SCREENLOG=${EL_SCREENLOG:-screen.log}

if [ -d ~/virtualenv ]; then
    . ~/virtualenv/bin/activate
fi

# send a comman to a pod without waiting for results
blip()
{
        # send one command to a BLE (no response)
	POD=`fgrep -his $1 podnames | awk '{print $1}'`; shift
	COMMAND=`echo -n $* | xxd -ps`
	
        gatttool -b $POD --char-write-req --handle=0x001b --value=$COMMAND
}

# send a comman to a pod and listen for results until ^C is pressed
bleep()
{
        # send one command to a BLE and wait for response
	POD=`fgrep -his $1 podnames | awk '{print $1}'`; shift
	COMMAND=`echo -n $* | xxd -ps`

        gatttool --listen -b $POD --char-write-req --handle=0x001b --value=$COMMAND
}

# convert a gatt log from hex into ascii
dehex()
{
    # convert from hex to ascii
    cat $1 | egrep -a Notification | cut -f7 -d: | sed 's/^/0a/g' | xxd -r -ps
    echo
}

# translate hex input pasted into the command line up until ^D is pressed
alias dx='cut -f2 -d: | sed '\''s/^/0a/g'\'' | xxd -r -ps; echo'
