#!/bin/sh

pod=`fgrep -his $1 podnames | awk '{print $1}'`; shift
sleep=${sleep:-10}

./test-command $pod "ssid reset" "ssid chars = 0"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep

./test-command $pod "ssid save" "ssid saved"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep

./test-command $pod "ssid set $ssid" "ssid chars = $ssid_len"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep

./test-command $pod "ssid save" "ssid saved"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep

./test-command $pod "ssid show" "$ssid"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep


./test-command $pod "pswd reset" "pswd chars = 0"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep

./test-command $pod "pswd save" "pswd saved"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep

./test-command $pod "pswd set $pswd" "pswd chars = $pswd_len"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep

./test-command $pod "pswd save" "pswd saved"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep

./test-command $pod "pswd show" "$pswd"
if [ $? -ne 0 ]; then echo FAIL; exit; fi
sleep $sleep

./test-command $pod "wifi test" "WI-FI OK"
if [ $? -ne 0 ]; then echo FAIL; exit; fi

XXXXXXXXXXXXX
./test-command $pod "get volt" "Vbat"
if [ $? -ne 0 ]; then exit $?; fi
sleep 2

./test-command $pod "get time" "UTC time"
if [ $? -ne 0 ]; then exit $?; fi
sleep 2

./test-command $pod "get date" "UTC date"
if [ $? -ne 0 ]; then exit $?; fi
sleep 2

