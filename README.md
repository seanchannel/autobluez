# wg-firmware-test

Project to automate WaterGuru firmware test plans and test cases documented in [TestLodge](https://waterguru.testlodge.com/projects/27528/suites/130300).

## Usage

* Scripts in the ```tests``` directory are launched by ```runtest```. Default test values for all scripts are defined in ```parameters.sh``` and can be set arbitrarily at run time. A BLE short ID or serial port is required. Multiple scripts can be specified, e.g.:
```
pod=3F8B3A version=v12.0.10-30-g4efa895 ./runtest version_check sensors
```
* The file ```podnames``` is used with aliases in ```bashrc``` to send arbitrary commands over BLE for diagnostics and test development.
* Jenkins jobs are configured to run scripts automatically on test units. Jobs are backed up in a separate repository, [wg-jenkins-config](https://github.com/WaterGuru/wg-jenkins-config) 

## Dependencies

Installing these tools requires enabling community / 3rd party repositories for your OS. For Ubuntu edit /etc/apt/sources.list. For RPM based systems enable the EPEL repository. MacOS is limited to serial only but can use homebrew and macports for dependencies..

* ```expect-lite(1)``` - main automation engine
* ```git(1)``` - development and deployment
* Linux Bluez tools ```hcitool(1)``` and  ```gatttool(1)``` - BLE support
* Vim utility ```xxd(1)``` - translate Hex <--> ASCII
* Gnu ```screen(1)``` 4.06 or later
* ```picocom(1)``` - serial utility
* Awscli - S3 and Lambda support
* ```Jo(1)``` - JSON formatter 
* ```Dash(1)``` - a simple Posix shell

## Ubuntu Setup
1. install dependencies
```
	$ sudo apt install expect-lite git bluez-tools screen picocom awscli jo dash 
```
2. Configure ```hcitool(1)``` to allow non-root users (optional)
```
	$ sudo setcap 'cap_net_raw,cap_net_admin+eip' `which hcitool`
```
3. clone this repository into the test user home directory
4. link files to the test user home directory . E.g.:
```
	$ ln -s ~/wg-firmware-test/bashrc ~/.bash_aliases
	$ ln -s ~/wg-firmware-test/screenrc ~/.screenrc
	$ ln -s ~/wg-firmware-test/podnames ~/.podnames
```
5. [Configure AWS credentials](https://github.com/WaterGuru/wg-pod-tools) and request S3 and Lambda accessb as needed.

