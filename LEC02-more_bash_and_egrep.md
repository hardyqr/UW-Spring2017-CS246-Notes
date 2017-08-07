# CS246

#### output redirection
- direct the output of a program to a file rather than screen

```bash
command arg1 arg2 ... > filename
```

```bash
cat < file.txt

cat < in.txt > out.txt
// copies contens in in.txt into out.txt

```


#### input / output streams

- use `2>` to redirect stderr to files

- `2>&1` redirects stderr to stdout

#### wildcard matching

```bash
echo "*.txt"
echo '*.txt'
# both prints *.txt

echo *.txt # correct
```

#### Pipes
- pipe connects the stdout of one process to stdin of another process

- examples

how many words in the first 20 lines of `sample.txt`
```bash
head -20 sample .txt | wc -w
```


Suppose files `words1.txt`, `words2.txt`, etc. contain lists of words, one per line. Print a duplicate free list of all words in any of `words*.txt`.
```bash
cat words*.txt | sort | uniq
```

#### embedded command

```bash
echo "Today is $(date) and I am $(whoami)"
```

- notice that `$(-)`, `()` is a must. Simple quote would prevent embedded command from executing


#### searching within files, `egrep`

- `egrep` - extended global regular expression print
```bash
egrep PATTERN file(s)
```

- examples

```bash
egrep "cs246" index.shtml | wc -l

egrep "cs246|CS246" index.shtml
egrep "(cs|CS)246" index.shtml
# equivalent

egrep "(c|C)(s|S)246" index.shtml
# four combinations: cS, Cs, cs, CS 


egrep "[abc]" file.txt 
# choose one element from the set
# euqivalent to
egrep "a|b|c" file.txt

egrep "[^abc]" file.txt
# choose any one element that's not in the set

```
- `?` - zero or one of previous subexpression
	- `cs ?246` means `cs246` or `cs 246`
	- `(cs)?246` means `246` or `cs246` 

- `+` - one or more of previous subexpression

- `*` - zero or more of previous subexpression

- `.` - anyone character
	- `.*` - zero or more anyone of the character

- `\` - escape character with special meaning 
	- `\*` means match lines with the actual "\*"





















