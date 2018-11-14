# wg-firmware-test

Scripts to automate firmware testing procedures. 

### What's in here

* ```podnames``` - list of pod BLE addresses followed by one or more aliases like pod ID or a name
* ```runtest```  - front-end script used to run test scripts
* ```tests/``` - directory (folder) containing the test scripts
* ```logs/``` - logs lf test runs and BLE communications
* ```connect.inc``` - common procedures at start of every test script`
* ```cleanup.inc``` - common procedures at end of every test script
* ```screenrc``` - critical settings for the ```screen``` utility
* ```bashrc```- diagnostic functions for test development (not used by any scripts)

## Getting Started

These scripts use standard Linux bluetooth and shell utilities along with a Tcl/Tk automation tool and should run on any Linux system. The following information should help you get started.

### Prerequisites

To prepare a system for these tests you should be familiar with Linux in general and your system's software package management tools.

* the system must be configured with a bluetooth device
* ```gatttool``` must be installed from the BlueZ system package(s)
* ```screen``` version 4.06 or newer is required
* ```Expect``` is the Tcl/Tk automation engine
* [```expect-lite```](http://expect-lite.sourceforge.net/expect-lite_install.html) is the main test driver and can be downloaded from the link or installed with your system's package manager (may require configuring additional repositories for your system.) 

To install expext-lite on ubuntu requires the "Universe" [repository](https://help.ubuntu.com/community/Repositories#Managing_Repositories) be configured. 

```
$ sudo apt install expect-lite
```
### Installing

Clone this repository (or copy) to the Linux system the tests will run on. Use the GitHub "clone or download" button for other choices. E.g.: 

```
$ git clone https://github.com/WaterGuru/wg-firmware-test.git
$ cd wg-firmware-test
```

Edit the file ```podnames``` if you need to add a pod or ID / alias to existing pod using vi or other text editor. To scan for pod address requires root (superuser) privilege:

```
$ sudo hcitool lescan
```

The scan will repeat every few secconds until Control-c is pressed. Look for the pod in the terminal output and copy/paste into ```podnames``` (the output is not sorted), adding any alias names for convenience.

## Running the tests

```runtest``` is used to run any script in the ```scripts/``` directory. As input it requires at least a pod name / ID that is listed in ```podnames``` along with any critical test parameters. These can be specified in any order on the command line before ```runtest```. What follows after ```runtest``` is the name of the test script to run. E.g.:

```
$ pod=220 ssid=Barnacle pswd=clearwater ./runtest wifi_setup
```

There are hard-coded defaults for parameters in the ```runtest``` file source. Parameters are named according to the ble command syntax. All of these may be specified as above on the command line.


### Test Parameters

(Explain what these tests test and why...)

