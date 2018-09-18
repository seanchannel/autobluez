# wg-firmware-test
Scripts to automate firmware testing

test-command:

    Send a command over BLE and optionally verify the output This script uses
    a list of pods called "podnames" to lookup pod BLE address. The list is in
    the standard /etc/hosts, /etc/ethers style format. Aliases for pod names 
    can be added for convenience. Commands must be in quotes if they are more 
    than one word. Output will be saved to a temporary file $0.log and displayed
    in hex and ascii.

    Syntax:
        ./test-command <POD> "<COMMAND>" [<OUTPUT>]

    Example:
        ./test-command squid version

        ./test-command bench "pad auto 24"

        ./test-command 88 version

    Note: relies on multiple timeouts. There will be at least one timeout shown
    after getting the BLE hex response. Output will include "Expect Failed: ..."
    only for failures detected and return non-zero, and otherwise only shows
    the terminal session and exits with a 0 status.
