# rshell
## UCR CS100

A basic unix command shell with the ability to print a command prompt as well as execute commands.

### Bugs

* Exit does not properly execute when there was an error before it being called.
* Must be space between || and && connectors in order for commands to execute correctly.
* ls bug: For ls -Rl directory in directory info not correctly displayed.
* ls bug: For ls -R extra newline before last directory files is displayed.
* redirection bug: Cannot use more than one pipe.
* redirection bug: Cannot use input redirection with piping.
* redirection bug: Cannot use output redirection, piping and input redirection at the same time.
* cd bug: ^Z is not usable. 

### Installation

In order to install this project:
```
$ git clone https://github.com/nchun003/rshell.git
$ cd rshell
$ make
$ bin/rshell
```


