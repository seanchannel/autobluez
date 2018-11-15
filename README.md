# wg-firmware-test

Scripts to automate firmware testing procedures. 

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

```runtest``` is used to run any script in the ```scripts/``` directory. As input it requires at least a pod name / ID that is listed in ```podnames``` along with any critical test parameters. These can be specified in any order on the command line before ```runtest```. What follows after ```runtest``` is the name of the test script to run. E.g.:

```
$ pod=220 ssid=Barnacle pswd=clearwater ./runtest wifi_setup
```

There are hard-coded defaults for parameters in the ```runtest``` file source. Parameters are named according to the ble command syntax. All of these may be specified as above on the command line.


### BLE Test Scripts

Here is a list of current scripts, what parameters they use, and what they do. All of these scripts send commands over BLE, verify the command is sent, and verify the pod returns expected notifications.

#### ```basic_info``` 
Check battery, time, and date, e.g.:
```
$ pod=squid ./runtest basic_info
```
* parameters: none
  * check battery level is between 5 and 6 volts
  * check a valid time is reported correctly formatted
  * check the date is reported correctly formatted

#### ```wifi_reset```
clear SSID & password
```
$ pod=squid ./runtest wifi_reset
```
* parameters: none
  * reset SSID and save, then verify
  * reset Wifi password and save, then verify

#### ```wifi_setup``` 
setup SSID & password
```
$ pod=squid ssid=WG2 pswd=clearwater ./runtest wifi_setup
```
* parameters: ```ssid```, ```pswd```
  * set the SSID, save, then verify (default: WG2)
  * set the Wifi password, save, then verify (default: clearwater)
  * run a Wifi test and verify success

#### ```log_upload``` 
upload the log
```
$ pod=squid ./runtest log_upload
```
* parameters: none
  * "zlog" command, then verify log upload is confirmed successful

#### ```version_test``` 
check version
```
$ pod=squid version=9.1.14 ./runtest version
```
* parameters: ```version```
  * "version" command & verify expected version (default: "9.1") 

#### ```mcu-fw-update``` 
install MCU firmware
```
$ pod=squid env=qa index=qa version=9.1.14 ./runtest mcu-fw-update
```
* parameters: ```env```, ```index```, ```version```
  * set the "fw env", then verify (default: prod)
  * set the "fw index", then verify (default: 9.1)
  * download firmware and verify it is confirmed successful
  * install the downloaded firmware, confirm "restarting"
  * disconnect and wait 1 minute, then reconnect
  * verify the expected version number reported (default: "9.1")

#### ```ble-fw-update``` 
install BLE firmware
```
$ pod=squid env=qa index=qa bleversion=11 ./runtest ble-fw-update
```
* parameters: ```bleversion```
  * download BLE firmware and verify it is confirmed successful
  * install the BLE firmware, restart the pod
  * disconnect and wait 1 minute, then reconnect
  * vefify the BLE version number reported (default: "9")

