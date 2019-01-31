# wg-firmware-test

These scripts are intended to automate the [firmware regression test suite in TestLodge](https://waterguru.testlodge.com/projects/27528/suites/130300). See below for details about using these scripts.

### What's in here

* ```runtest```  - The main front-end user script for running test scripts
* ```podnames``` - A list of BLE addresses for the test units with pod ID and other human-readable aliases
* ```tests/``` - test scripts in sub-folders per section, and common scripts for all tests
* ```logs/``` - a log for each 'podname-script', over-written by next script run
* ```screenrc``` - critical settings for the ```screen``` utility
* ```bashrc```- shortcuts for test development and translating hex to ascii

## Getting Started

Any mainstream Linux server should support all prerequisites. Each linux distro has it's own software ecosystem, You should be familiar with your system's software management tools and configuration. In general most systems require the 'extended' or 'community' repositories enabled for that platform to install the needed software. For example, to install expext-lite on ubuntu requires the ["Universe" repository](https://help.ubuntu.com/community/Repositories#Managing_Repositories) be enabled, and on RPM-based systems you might need the ["EPEL" repository](https://fedoraproject.org/wiki/EPEL).

### Prerequisites

Software requirements:
* ```git``` can be used to clone this repository and keep it up to date
* ```gatttool``` is a utility from the ```bluez``` linux bluetooth stack for BLE communications
* ```screen``` version 4.06 or newer is used for the interactive BLE and/or serial sessions
* ```Expect``` is the automation engine written in Tcl/Tk
* [```expect-lite```](http://expect-lite.sourceforge.net/expect-lite_install.html) is a compact front-end for ```Expect``` and the main script interpreter
* ```Dash``` is a minimal POSIX-compliant shell with no bash features installed as /bin/sh on Ubuntu systems

Additionally, the system must be configured with a bluetooth hardware device.

Example Ubuntu package installation, with repositories configured:
```
$ sudo apt install git bluez bluez-tools screen expect-lite
```
### Installing

Clone this repository onto the system or use the GitHub "clone or download" button for other options. E.g.: 

```
$ git clone https://github.com/WaterGuru/wg-firmware-test.git
$ cd wg-firmware-test
```
You can edit the file ```podnames``` to add test units or alias names using a text editor or online in GitHub before downloading. To scan the local environment for BLE addresses requires root (superuser) privilege:

```
$ sudo hcitool lescan
```

The scan will continue until Control-c is pressed. Look for the address in the terminal output and copy/paste into ```podnames``` along with any alias names for the unit on the same line.

## Running the tests

```runtest``` is used to run any script in the ```tests/``` directory. As input it requires at least a pod ID that is listed in ```podnames``` along with any critical test parameters. These can be specified in any order on the command line before ```runtest```. What follows after is the list of test script to run. E.g. to run all the [local operation](https://waterguru.testlodge.com/projects/27528/suites/130300?expand_section=140046#suite_section_140046) test section (with default parameters):

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
