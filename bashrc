
# this file is just for conveniece. it is not used by automated tests

export PATH=.:$PATH
export SCREENRC=~/.screenrc
export SCREENLOG=${EL_SCREENLOG:-screen.log}

# The following all require a "podnames" file in the current directory

# connect to a pod in the gatttool interactive command line
ble()
{
        # connect to interactive BLE
	POD=`fgrep -his $1 podnames | awk '{print $1}'`; shift
	echo -n $* | xxd -ps

        gatttool -I --listen -b $POD
}

# send a comman to a pod without waiting for results
blip()
{
        # send one command to a BLE (no response)
	POD=`fgrep -his $1 podnames | awk '{print $1}'`; shift
	COMMAND=`echo -n $* | xxd -ps`
	
        gatttool -b $POD --char-write-req --handle=0x001b --value=$COMMAND
}

# send a comman to a pod and wait for results until ^C is pressed
bleep()
{
        # send one command to a BLE and wait for response
	POD=`fgrep -his $1 podnames | awk '{print $1}'`; shift
	COMMAND=`echo -n $* | xxd -ps`

        gatttool --listen -b $POD --char-write-req --handle=0x001b --value=$COMMAND
}

dehex()
{
    # convert from hex to ascii
    cat $1 | egrep -a Notification | cut -f7 -d: | sed 's/^/0a/g' | xxd -r -ps
    echo
}

# translate hex input pasted into the command line up until ^D is pressed
alias dx='cut -f2 -d: | sed '\''s/^/0a/g'\'' | xxd -r -ps; echo'