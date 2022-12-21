
## WaterGuru firmware test shell support
#
# link this file to ~/.bash_aliases, etc


# BLE hex to ASCII copy/paste in the terminal, ^D when done
alias dx='cut -f2 -d: | sed '\''s/^/0a/g'\'' | xxd -r -ps; echo'

# BLE hex to ASCII a file, e.g. 'dehex myfile.log' 
dehex()
{
    cat $1 | egrep -a Notification | cut -f7 -d: | sed 's/^/0a/g' | xxd -r -ps
    echo
}

## the following require ~/.podnames (see example file)

# send a command to a pod without waiting for notificatsions
# e.g. 'blip <mypod> restart' or 'blip <mypod> pad test 2'
blip()
{
    POD=`fgrep -his $1 ~/.podnames | awk '{print $1}'`; shift
    COMMAND=`echo -n $* | xxd -ps`

    gatttool -b $POD --char-write-req --handle=0x0010 --value=$COMMAND
}

# send a comman to a pod and show notifications until ^C is pressed. 
# same syntax as above, but stays connected until you press Control-c.
bleep()
{
    POD=`fgrep -his $1 ~/.podnames | awk '{print $1}'`; shift
    COMMAND=`echo -n $* | xxd -ps`
    gatttool --listen -b $POD --char-write-req --handle=0x0010 --value=$COMMAND
}

## AWS stuff

# display the most recent logfile sent from the pod: 's3log <podId>' 
s3log()
{
    # the last file listed is the most recent log file uploaded
    logfile=`aws --profile qa s3 ls qa-log.waterguru.com/pod/$1/ \
        | tail --lines=1 \
        | awk '{print $4}'`

    # dump the log file and search for the given keyword
    aws --profile qa s3 cp s3://qa-log.waterguru.com/pod/$1/$logfile - 
}

# get a podRec() and save to file, e.g. 'podRec <podId>'
podrec()
{
    payload="'`jo podId=$1 crudOp=READ returnRec=true`'"
    outfile=${2:-$1-podRec.json}

    eval aws --profile qa --region us-west-2 lambda invoke --function-name qa-managePod --invocation-type RequestResponse \
        --payload ${payload} $outfile
}
