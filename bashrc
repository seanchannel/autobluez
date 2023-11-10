
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

    gatttool -b $POD --char-write-req --handle=$EL_handle --value=$COMMAND
}

# send a comman to a pod and show notifications until ^C is pressed. 
# same syntax as above, but stays connected until you press Control-c.
bleep()
{
    POD=`fgrep -his $1 ~/.podnames | awk '{print $1}'`; shift
    COMMAND=`echo -n $* | xxd -ps`
    gatttool --listen -b $POD --char-write-req --handle=$EL_handle --value=$COMMAND
}

## AWS stuff

# display the most recent logfile sent from the pod: 's3log <podId>' 
s3log()
{
    # the last file listed is the most recent log file uploaded
    logfile=`aws --profile qa s3 ls [log directory URL]/$1/ \
        | tail --lines=1 \
        | awk '{print $4}'`

    # dump the log file to stdout
    aws --profile qa s3 cp s3://[log directory URL]/$1/$logfile - 
}
