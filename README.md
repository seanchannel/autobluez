# wg-firmware-test

These scripts are intended to automate the [firmware regression test suite in TestLodge](https://waterguru.testlodge.com/projects/27528/suites/130300). See below for script details.

### What's in here

* ```podnames``` - list of pod BLE addresses followed by one or more aliases like pod ID or a name
* ```runtest```  - main script to run test scripts
* ```tests/``` - directory (folder) of test scripts
* ```logs/``` - logs of test runs and BLE communications
* ```connect.inc``` - common procedures at the start of every test script
* ```cleanup.inc``` - common procedures at the end of every test script
* ```screenrc``` - critical settings for the ```screen``` utility
* ```bashrc```- diagnostic functions for test development (not used by any scripts)

## Getting Started

These scripts use standard Linux bluetooth and shell utilities along with a Tcl/Tk automation tool and should run on any Linux system. The following information should help you get started.

### Prerequisites

Setting up a Linux system is a technical task. To prepare a system for these tests you should be familiar with Linux in general and your system's software package management tools.

* the system must be configured with a bluetooth device
* ```gatttool``` handles BLE communications and can be installed from the BlueZ system package(s)
* ```screen``` version 4.06 or newer is required to run and log interactive BLE / serial programs in the background
* ```Expect``` is the core Tcl/Tk automation engine
* [```expect-lite```](http://expect-lite.sourceforge.net/expect-lite_install.html) is the main test driver and can be downloaded from the link or installed with your system's package manager (may require configuring additional repositories) 

To install expext-lite on ubuntu requires the "Universe" [repository](https://help.ubuntu.com/community/Repositories#Managing_Repositories) be configured. 

```
$ sudo apt install expect-lite screen
```
### Installing

Clone this repository onto the system the tests will run on (use the GitHub "clone or download" button for choices.) E.g.: 

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
These scripts are intended to automate the [firmware regression test suite in TestLodge](https://waterguru.testlodge.com/projects/27528/suites/130300).

```runtest``` is used to run any script in the ```tests/``` directory. As input it requires at least a pod name / ID that is listed in ```podnames``` along with any critical test parameters. These can be specified in any order on the command line before ```runtest```. What follows after ```runtest``` is the list of test script to run. E.g. to run all the tests:

```
$ pod=testpod ./runtest wifi_setup mcu-fw-update ble-fw-update basic_info log_upload mode_test
```

There are hard-coded defaults for parameters in the ```runtest``` file source. Parameters are named according to the ble command syntax. All of these may be specified as above on the command line.


### Test Scripts

These scripts are intended to automate the [firmware regression test suite in TestLodge](https://waterguru.testlodge.com/projects/27528/suites/130300). The exact test case ID's and organization of test cases may vary over time when they are improved and updated as needed.

Here is a list of scripts and what parameters you can specify with defaults shown below. All of these scripts send commands over BLE, verify the command is sent, and verify the pod returns expected notifications. Please see the test case documentation linked below for more info about what the script does.

#### [TC27](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2134981) ```wifi_setup```, ```wifi_reset``` 
Clear and setup SSID & password, test wifi. (```wifi_setup``` also runs ```wifi_reset```)
```
$ pod=testpod ssid=WG2 pswd=clearwater ./runtest wifi_setup
```
#### [TC13](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2130489) ```mcu-fw-update``` 
Download and install MCU firmware
```
$ pod=testpod env=prod index=9.1 version=9.1.14 ./runtest mcu-fw-update
```
#### [TC83](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2155346) ```ble-fw-update``` 
Download and install BLE firmware
```
$ pod=testpod env=prod index=9.1 bleversion=9 ./runtest ble-fw-update
```
#### [TC14](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2130492)  ```basic_info```
Checks for valid firmware version, battery, time, and date, and pod ID.
```
$ pod=testpod version=9.1.14 bleversion=9 podid=22 ./runtest basic_info
```
#### [TC15](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2130494) ```log_upload``` 
upload the log
```
$ pod=testpod ./runtest log_upload
```
#### [TC105](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2262327) ```mode_test```
Check mode setting
```
$ pod=testpod mode=Sense ./runtest mode_test
```
#### ```version_test``` 
check version reported against expected
```
$ pod=testpod version=9.1.14 ./runtest version_test
```

