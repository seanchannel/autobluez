# wg-firmware-test
Scripts to automate firmware testing

test-command:

    Send one command over BLE and verify the output. Commands of more
    than one word must be in quotes. Output will be displayed in ascii.

    Syntax:
        ./test-command <POD> "<COMMAND>" [<OUTPUT>]

    Example:
        ./test-command squid version 9.10

podnames

    list of BLE addresses for pods and alias names. Same format as /etc/hosts.

bash_aliases:

    4 command aliases for quickly working with a pod via command line

test scripts:

    These run the test procedures for various test cases.
