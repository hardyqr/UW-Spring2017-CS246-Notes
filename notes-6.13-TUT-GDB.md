# CS246
# TUT GDB

### GDB Commands
`g++ -g file.cc -o test.out` - `-g` means make the out file debuggable

`gdb test.out`

`(gdb) break main` - set a breakpoint at main function
`(gdb) run`

- quit `quit`/`q`/`ctrl+D`

- `list n` - displays code around current posn (n lines)

- `backtrace` (`bt`) - gives you a stack trace

- `print` (`p`) - print the value of expr.

- `up` - go up on stack (like a previous function)

- `break f` - breakpoint at function f (`example.cc 25` - breaks at line 25 of example.cc)

- `next` (`n`) - run the next line of code

- `step` (`s`) - same as next, but goes inside function f (like, it would get into a `strcmp`. `next` won't )

- `continue` (`c`) - resume execution of the program

- `enable`/`disable` `b` - Enables / Disables breakpoint b

- `delete b` - deletes breakpoint b

- `watch expr` - pause a program whenever the memory at expr changes

- `display expr` - just like print, but it also executes every step

- `undisplay expr' - stop displaying

- `set expr` - manually set a new value to some variable (`set a = 3`)
