# wg-firmware-test

# NOTE: this README is out of date

These scripts are intended to automate the [firmware regression test suite in TestLodge](https://waterguru.testlodge.com/projects/27528/suites/130300). See below for details about using these scripts.

# How This basically works -- developer mode

Some technical details first, and shortcuts at the end.

Linux is required. The linux bluetooth stack (“bluez”) includes a tool package, “bluez-tools”, which includes the 'hcitool' and 'gatttool' utilities. 'xxd' is used to translate hex<->ascii and is part of the “vim” package. So on Ubuntu I just do “sudo apt install bluez-tools” (xxd is usually there already).

‘sudo hcitool lescan’ is used to scan the local bluetooth environment (it must be run as root or you can modify the binary to allow regular users, e.g. 

	sudo setcap 'cap_net_raw,cap_net_admin+eip' `which hcitool`

Once the BT MAC address has been found in the scan you can use ‘gatttool’ to connect, however all communication will be in hex and gatttool is a full-screen interactive program. To connect:

	gatttool -I --listen -b <address>
	
There are “connect” and “disconnect” commands which are very important. To send and reeieve commands at the point you would need to go outside of the gattool, e.g. in another window, and use the ‘xxd’ utility to translate to and from hex that you want to send or receive from gatttool. See shortcuts below.

Both gatttool and hcitool are very sensitive to unexpected signals / interrupts. So if one of these gets terminated unexpectedly it is possible your BT stack will hang ond the computer will need a reboot. It is important to only interrupt hcitool with ^C and it is also important to explicitly give the “disconnect” command in gatttool before quitting.

This is all very painful for a human but computer can automate this with the use of a few other tools.

## Shortcuts

I have some bash shortcuts I use while developing tests, even if I have to reboot occasionally. You can add the contents of bashrc contents to your ~/.bashrc (then source or start a new shell). Please see also the code and comments in there.

First, I take the output from ‘hcitool lescan’ and save the line for my pod(s) into a file ~/.podnames and the shortcuts below use this. Example of ~/.podnames file:

	C8:DF:84:FC:26:55 WaterGuru:FC2655 labbench
	7C:01:0A:FC:C3:14 WaterGuru:FCC314 1097 backyard
	C8:DF:84:FC:23:F2 WaterGuru:FC23F2 testpod

^ note I added aliases at the end of the line which you can use with the shortcuts (or the “FC2655” part). There are 5 aliases / functions defined for bash in bashrc. *“bleep” and “dx” are what I use to do a command-line session.* 

“dx”
	this will wait for you to copy and paste hex output from gatttool into the terminal. multi-line OK. after pasting content press ^D to terminate input and it will print the input as plain tex.

dehex <file>
	this is the same as the above but for a file of gatttool output, e.g. “dehex log.txt” will display contents in plain text. 

blip <pod> <command>
	this will send one command to the pod address found in ~/.podnames without waiting for any response. Useful for when you do not need to stay connected or read the response. E.g.:
	blip testpod restart

bleep <pod> <command>
	this will send a command and wait for responses until ^C is pressed. Copy the response output lines, type ‘dx’ (above) and paste output, press ^D to translate output.

ble <pod>
	this gives you a gatttool prompt at the pod address, unconnected by default. However sometimes the connection gets stuck so you can try entering “disconnect” here, then ‘exit’ / ^D 

# How this works -- automated

The ".podnames" file is not used for automated testing. Instead we require the pod BLE ID (e,g, "FCC314") and we do a BLE scan to find the MAC address and connect. Only after that do we get the pod ID from the unit.

### Prerequisites

Software requirements:
* ```git``` can be used to clone this repository and keep it up to date. Not needed if deployed from zip file (e.g. FAT).
* ```gatttool``` is a utility from the ```bluez``` linux bluetooth stack for BLE communications.
* ```screen``` version 4.06 or newer is used for the interactive BLE and/or serial sessions.
* ```Expect``` is the automation engine written in Tcl/Tk.
* [```expect-lite```](http://expect-lite.sourceforge.net/expect-lite_install.html) is a compact front-end for ```Expect``` and the main script interpreter.
* ```Jo``` is a command-line json utility used by the scripts for parsing pod JSON records.
* ```Dash``` is a minimal POSIX-compliant shell with no bash features installed as /bin/sh on Ubuntu systems.
* ```picocom``` is used to connect to serial devices like the pod serial console and programmable power supplies.
* ```awscli``` is the [pythpn] aws command line interface for downloading logs and pod the pod record (podrec).
* ```toilet``` prints the colorful "PASS" or "FAIL" banner text at the end of a test script.

Additionally, the system must be configured with a bluetooth hardware device.

Example Ubuntu package installation, with repositories configured:
```
$ sudo apt install git bluez bluez-tools screen expect-lite
```

## What's in here

* ```runtest```  - The main front-end user script for running test scripts
* ```tests/``` - test scripts in sub-folders per section, and common scripts for all tests
* ```logs/``` - a log for each 'podname-script', over-written by next script run (except FAT)
* ```screenrc``` - critical settings for the ```screen``` utility, used to open serial and BLE sessions in the backgroupd
* ```bashrc```- shortcuts for test development and translating hex to ascii

## Getting Started

Any mainstream Linux server should support all prerequisites. Each linux distro has it's own software ecosystem, You should be familiar with your system's software management tools and configuration. In general most systems require the 'extended' or 'community' repositories enabled for that platform to install the needed software. For example, to install expext-lite on ubuntu requires the ["Universe" repository](https://help.ubuntu.com/community/Repositories#Managing_Repositories) be enabled, and on RPM-based systems you might need the ["EPEL" repository](https://fedoraproject.org/wiki/EPEL).

### Installing

Clone this repository onto the system or use the GitHub "clone or download" button for other options. E.g.: 

```
$ git clone https://github.com/WaterGuru/wg-firmware-test.git
$ cd wg-firmware-test
```
To scan the local environment for BLE addresses requires root (superuser) privilege, or modify the binary as above.
```
$ sudo hcitool lescan
```

The scan will continue until Control-c is pressed. The scripts look for the address in the terminal output and then send a ^C automatically.

## Running the tests

```runtest``` is used to run any script in the ```tests/``` directory. As input it requires at least a pod BLE ID along with any critical test parameters. These can be specified in any order on the command line before ```runtest```. What follows after is the list of test script to run. E.g. to run all the [local operation](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#suite_section_140046) test section (with default parameters):

```
$ pod=testpod ./runtest wifi_connect mcu-fw-update ble-fw-update basic_info log_upload mode_check
```
### Test Scripts
The default parameters are in the ```runtest``` script. All of these may be specified on the command line. Examples for each script are below with default values. Parameters may be left out if the test is only using the default. Please see the test case documentation linked below for more info about each.

#### Local Operations

##### [TC27](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2134981) ```wifi_connect```, ```wifi_reset``` 
Clear and setup SSID & password, test wifi. (```wifi_connect``` also runs ```wifi_reset```)
```
$ pod=testpod ssid=WG2 pswd=clearwater ./runtest wifi_connect
```
##### [TC13](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2130489) ```mcu-fw-update``` 
Download and install MCU firmware
```
$ pod=testpod env=prod index=9.1 version=9.1.14 ./runtest mcu-fw-update
```
##### [TC83](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2155346) ```ble-fw-update``` 
Download and install BLE firmware
```
$ pod=testpod env=prod index=9.1 bleversion=9 ./runtest ble-fw-update
```
##### [TC14](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2130492) ```basic_info```
Checks for valid firmware version, battery, time, and date, and pod ID.
```
$ pod=testpod version=9.1.14 bleversion=9 podid=22 ./runtest basic_info
```
##### [TC15](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2130494) ```log_upload``` 
upload the log
```
$ pod=testpod ./runtest log_upload
```
##### [TC105](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#case_2262327) ```sensor_mode```
Check mode setting
```
$ pod=testpod mode=Sense ./runtest sensor_mode
```
##### ```version_check``` 
check version reported against expected (used by other scripts)
```
$ pod=testpod version=9.1.14 ./runtest version_check
```
#### Cloud Operations
##### [TC16](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140047#case_2130495) ```remote_firmware_upgrade```
do a cloud check and download / install a new firmware version
```
$ pod=testpod ./runtest remote_firmware_upgrade
```
##### [TC18](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140047#case_2134970) ```cloud_log_upload```
upload the log once on a cloud check
```
$ pod=testpod ./runtest cloud_log_upload
```
##### [TC30](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140047#case_2134984) ```pool_parameters```
verify pool parameters are set after a cloud check
```
$ pod=testpod ./runtest pool_parameters
```
##### [TC52](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140047#case_2140180) ```basic_reporting```
verify basic info is reported to the cloud
```
$ pod=testpod ./runtest basic_reporting
```
##### [TC77](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140047#case_2147118) ```pool_data_reporting```
verify pool measurement data is reported to the cloud
```
$ pod=testpod ./runtest pool_data_reporting
```
##### ```cloud_check```
do a cloud check (used by other scripts)
```
$ pod=testpod ./runtest cloud_check
```
