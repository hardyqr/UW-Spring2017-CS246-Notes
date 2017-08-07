# CS246
# Shell (contd.)


### `egrep` recap

- `?` - zero or one
- `*` - zero or more
- `+` - one or more
- `.` - any one character

- `^cs.*246$` - lines start with `cs` and end with `246`

- some examples

```bash
egrep "^(..)*$" file.txt
# fetch lines of even number of characters

egrep "^e....$" file.txt
# fetch lines that start with "e" and consist of five characters

# list files in current directory whose name contains exactly one "a"

ls | egrep "^[^a]*a[^a]*$"
```


### file permissions

```bash
ls -l 
# long listing
# prints 10 bits -rwxr-xr--
```

- first digit - type of the file
- 2,3,4 digits - user bits (owner's permissions)
	- can read, write, execute in our case
- 5,6,7 digits - group bits
	- can read and execute
- 8,9,10 digits - other bits
	- can only read

- only the owner can change file permissions with `chmod`
- syntax:
```bash
chomod MODE files(s)
```


### shell variables


### shell scripts
