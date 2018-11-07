# wg-firmware-test

Scripts to automate firmware testing procedures. 

### What's in here

* ```podnames``` - list of pod BLE addresses followed by one or more aliases such as pod ID or a name
* ```runtest```  - front-end (test harness) used to run test scripts
* ```tests/``` - directory (folder) containing the test scripts
* ```logs/``` - logs for the script and the BLE communications are saved in this directory
* ```connect.inc``` - common procedures included at start of every test script`
* ```cleanup.inc``` - common procedures included at end of every test script
* ```screenrc``` - a few critical settings for the ```screen``` utility
* ```bashrc```- diagnostic functions for test development (not used by any scripts)

## Getting Started

These scripts use standard Linux bluetooth ```gatttool``` and shell utilitie and should work on any Linux system. The following information should help you get started.

### Prerequisites

[expect-lite](http://expect-lite.sourceforge.net) is the main test driver and must be installed first.

To install expext-lite on ubuntu (as root):
```
$ sudo apt install expect-lite
```
### Installing

* Clone this repository (or copy) to the Linux system the tests will run on. To clone from GitHub via HTTPS:

```
$ git clone https://github.com/WaterGuru/wg-firmware-test.git
```

* Edit the file ```podnames``` if you need to add a pod or ID / alias to existing pod using vi or other text editor. To can scan for the pod address requires root (superuser) privilege:

```
$ sudo hcitool lescan
```

The scan will repeat every few secconds until Control-c is pressed. Look for the pod in the terminal output and copy/paste into ```podnames``` (the output is not sorted).

## Running the tests

First, cd into the ```wg-firmware-test``` directory. The scripts assume this is the working directory:

```
$ cd wg-firmware-test
```

```runtest``` is used to run any script in the ```scripts/``` directory. As input it requires at least a pod name / ID that is listed in ```podnames``` along with any critical test parameters. These can be specified in any order on the command line before ```runtest``` e.g.:

```
$ pod=220 ssid=Barnacle pswd=clearwater ./runtest wifi_setup
```

What follows after ```runtest``` is the test script to run.

### Test Parameters

Explain what these tests test and why

```
Give an example
```

