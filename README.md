# autobluez

Project to automate bluetooth by scripting linux bluetooth tools. 

Caution: rough road ahead & you may want to explore several hundred other projects that do this with Python. This was intended as a prototype for a later python implementation but it was needed in production as-is. Also this is built around a specific product (cloned with permission) so it is not (yet) generalized.

## Usage

* Scripts in the ```tests``` directory are launched by ```runtest```. Default test values for all scripts are defined in ```parameters.sh``` and can be set on the command line at run time. A BLE short ID or serial port is required. Multiple scripts can be specified on the same command line.

* The file ```podnames``` lists aliases for BLE addresses. See shell functions in ```bashrc```

## Dependencies

Installing these tools requires enabling community / 3rd party repositories for your OS.

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
	$ ln -s ~/autobluez/bashrc ~/.bash_aliases
	$ ln -s ~/autobluez/screenrc ~/.screenrc
	$ ln -s ~/autobluez/podnames ~/.podnames
```
5. [Configure AWS credentials] and request S3 and Lambda access if needed.

