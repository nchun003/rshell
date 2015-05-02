# rshell
## UCR CS100 hw0

A basic unix command shell with the ability to print a command prompt as well as execute commands.

### Bugs

* Exit does not properly execute when there was an error before it being called.
* Must be space between || and && connectors in order for commands to execute correctly.
* ls bug: For ls -Rl directory in directory info not correctly displayed.
* ls bug: For ls -R extra newline before last directory files is displayed.

### Installation

In order to install this project(from the hammer server):
```
$ git clone https://github.com/nchun003/rshell.git
$ cd rshell
$ git checkout hw0
$ make
$ bin/rshell
```


