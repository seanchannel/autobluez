# wg-firmware-test
Scripts to automate firmware testing

test-command:

    Send a command over BLE and optionally verify the output This script uses
    a list of pods called "podnames" in the current directory to lookup BLE 
    address. Commands of more than one word must be in quotes. Output will be 
    displayed in hex and ascii.

    Syntax:
        ./test-command <POD> "<COMMAND>" [<OUTPUT>]

    Example:
        ./test-command squid version 9.10

    Will always pass with no output argument. Uses some patient timeouts 
    deliberately. Exit code of scripts indicates pass or fail (e.g. echo $?)
    but 'fail' will always be shown for non-matches.

podnames

basic_info.sh
basic_info-test

    These run the "basic info" test suite for date, time, and battery. The
    ".sh" version uses separate connections for each command, which has 
    sometimes resulted in a hung BLE. The "-test" version uses a continuous
    BLE session for all commands.

wifi_setup.sh
wifi_setup-test

    As above but for setting the wifi SSID & password. Both take a pod name.
    The ".sh" version takes variables on the command line. The "-test" version
    takes a pod, SSID, and password (less than 10 chars) as arguments.
