> program arg1 ... arg2 < input > output <br>

# today
- bash vars  
- exit codes  
- loops,ifs,tests  
- bash scripting  
- testing  

# bash vars
# exit codes
## in bash 
> `0` <br>
- no error
> 1-255  <br>
- some error
# loops,ifs,tests
> `seq 0 3`<br>
> `for var in $(seq 0 3); do echo $var; done` <br>
> `[ 4 -le 5 ]` <br>
output would be zeo

> `[ -r changeExtension.sh]; echo $?` <br>
Is the sh file exit and readable?

> `#!/bin/bash` <br>
> `#!/usr/bin/python` <br>

```shell
subroutine(){
   ...
}
subroutine
```

# bash scripting

# testing
black-box testing <br>
white-box tesing <br>

- general cases
- boundary/edge cases
- equivalence classes
test at least one case for each condition
- corner/weird cases



