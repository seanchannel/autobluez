# wg-firmware-test

Project to automate WaterGuru firmware testing. See [TestLodge](https://waterguru.testlodge.com/projects/27528/suites/130300) for source test plan.

## Tools
* ```expect-lite(1)``` - main automation engine
* ```git(1)``` - development and deployment
* Linux Bluez tools ```hcitool(1)``` and  ```gatttool(1)``` - BLE support
* Vim utility ```xxd(1)``` - translate Hex <--> ASCII
* Gnu ```screen(1)``` 4.06 or later
* ```picocom(1)``` - serial utility
* Awscli - S3 and Lambda support
* ```Jo(1)``` - JSON formatter 
* ```Dash(1)``` - a simple Posix shell

## Setup

1. installation requires enabling community / 3rd party repositories first. Ubuntu installation example:
```
	$ sudo apt install expect-lite git bluez-tools screen picocom awscli jo dash 
```
2. Configure ```hcitool(1)``` to allow non-root users (optional)
```
	$ sudo setcap 'cap_net_raw,cap_net_admin+eip' `which hcitool`
```
3. clone this repository to the linux test user home directory
4. (optional) link each file ```bashrc```, ```screenrc```, and ```podnames``` to dot-files in the test user home directory. E.g.:
```
	$ ln -s ~/wg-firmware-test/bashrc ~/.bash_aliases
	$ ln -s ~/wg-firmware-test/screenrc ~/.screenrc
	$ ln -s ~/wg-firmware-test/podnames ~/.podnames
```
5. [Configure AWS credentials](https://github.com/WaterGuru/wg-pod-tools) and request S3 and Lambda accessb as needed.


## What's in here

## Usage / examples
