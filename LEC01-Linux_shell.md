# CS246
# Lecture 01

### Linux Shell
- **Shell**
	- interface to the operating system
	- open programs, move files

- Graphical Shell 
	- graphical interface (win / mac)
	- drag / drop, clicks, etc.<br>
- $+$ very intuitive
- $-$ limited in efficiency

### Command Line Shell

- you type input (commands) on, a "command prompt"

- $-$ steep learning curve
- $+$ use a few basic commands to do more powerful things

- **Unix**
	- 70s
	- came with a "shell"
	- Stephen Bourne
	- C Shell (csh), Korn Shell (ksh)
	- Turo C Shell (tcsh)
	- Bourne Again SHell (BASH)

`echo $0`


### Linux File System
- filesystem
	- contains files
	- some files can comtain other files
	- directories
	- The filesystem forms a tree, rooted at a directory called the "root" directory `/`.

- path
	- a location of the file within the filesystem
	- like `/home/fangyu/cs246/a1`


### Some Basic Commands

`ls`

`ls -a` - display all files

`pwd` - present working directory

`cd` - change directory

`cd -` - go to the previous directory

`ctrl+c` - kill the process

`ctrl+d` - to indicate end of input, i.e. generate an EOF (end of file) signal 

### Output Redirection

- used to redirect the output of a command / program to a file (default is the screen)

- `command arguments > output.txt`
	- if it's a `>>` rather than `>`, it means to append rather then overwrite

### Input Redirection

- direct input into a program from a file

- `command arg1 arg2 ... < in.txt`

