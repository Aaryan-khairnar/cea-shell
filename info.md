Building a shell is a perfect choice. You’re basically recreating one of the oldest and most elegant ideas in Unix: a small program whose only job is to **launch other programs**. It’s like writing the conductor of an orchestra rather than an instrument.

A real shell has thousands of features, but the core mechanism is shockingly small. A minimal shell that actually runs commands only needs a handful of system calls and a few boring C utilities for string handling.

Think of the shell loop like a tiny operating system inside user space:

```
print prompt
read command
parse command
fork
child executes program
parent waits
repeat forever
```

Everything you need will fall into three groups: **process control**, **input/output**, and **string handling**.

Let’s walk through the toolbox.

---

First come the **process control functions**. These are the stars of the show.

`fork()`

Creates a child process by cloning the current process.

Library:

```c
#include <unistd.h>
```

Prototype:

```c
pid_t fork();
```

If it returns `0`, you're in the **child process**.
If it returns `>0`, you're in the **parent process**.

Your shell will call this every time the user runs a command.

---

`exec` family (you only need one of them)

These replace the current process with another program.

For a shell, the easiest is:

`execvp()`

Library:

```c
#include <unistd.h>
```

Prototype:

```c
int execvp(const char *file, char *const argv[]);
```

This searches the `PATH` automatically, so typing `ls` will find `/bin/ls`.

When `execvp()` succeeds, **your code disappears** and the new program takes over the process.

---

`wait()` or `waitpid()`

Parent process waits for the child to finish.

Library:

```c
#include <sys/wait.h>
```

Prototype:

```c
pid_t wait(int *status);
```

or

```c
pid_t waitpid(pid_t pid, int *status, int options);
```

For your first shell, `wait(NULL)` is enough.

---

`exit()`

Used if the shell itself needs to terminate.

Library:

```c
#include <stdlib.h>
```

Prototype:

```c
void exit(int status);
```

You’ll use this for the built-in command `exit`.

---

Now the second category: **input and output**.

Your shell must read commands from the user.

`printf()`

Library:

```c
#include <stdio.h>
```

Used to print the shell prompt:

```
myshell>
```

---

`fgets()`

Library:

```c
#include <stdio.h>
```

Prototype:

```c
char *fgets(char *str, int n, FILE *stream);
```

This reads the user’s command line from `stdin`.

---

`perror()`

Library:

```c
#include <stdio.h>
```

Prototype:

```c
void perror(const char *s);
```

Very useful when `execvp()` fails.

Example output:

```
exec failed: No such file or directory
```

---

Third category: **string manipulation**.

A shell must break a command like

```
ls -l /home
```

into separate tokens:

```
["ls", "-l", "/home"]
```

These functions help with that.

---

`strtok()`

Library:

```c
#include <string.h>
```

Prototype:

```c
char *strtok(char *str, const char *delim);
```

Used to split the command by spaces.

---

`strcmp()`

Library:

```c
#include <string.h>
```

Prototype:

```c
int strcmp(const char *s1, const char *s2);
```

Used for built-in commands like:

```
exit
cd
```

Example:

```
if(strcmp(cmd, "exit") == 0)
```

---

`strcspn()`

Library:

```c
#include <string.h>
```

Used to remove the newline that `fgets()` adds.

Example:

```
cmd[strcspn(cmd, "\n")] = 0;
```

---

Now for a few **very useful but optional** functions that make your shell more realistic.

---

`getpid()`

Library:

```c
#include <unistd.h>
```

Returns the process ID of your shell.

Fun for debugging.

---

`chdir()`

Library:

```c
#include <unistd.h>
```

Used to implement the built-in `cd` command.

Without this, your shell can't change directories.

---

`getcwd()`

Library:

```c
#include <unistd.h>
```

Lets you show the current directory in the prompt.

Example:

```
myshell:/home/user>
```

---

Finally, here’s the **complete header set** most minimal shells use:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
```

That’s enough to build a working shell.

---

So the **core functions you will likely use** are:

Process control
fork
execvp
wait or waitpid
exit

Input/output
printf
fgets
perror

String handling
strtok
strcmp
strcspn

Optional but useful
chdir
getcwd
getpid

---

What you’re about to build is historically important in a funny way. The very first Unix shell in the 1970s was only a few hundred lines long and followed almost exactly the structure you’re about to recreate. Every modern shell — bash, zsh, fish — still uses the same ancient `fork → exec → wait` dance.

Once your shell works, a bunch of Linux concepts suddenly become much clearer:

• why zombies exist
• how background jobs work
• how pipes connect processes
• why `ps` shows parent/child trees

You’ll literally be able to **see the operating system thinking**.

And the moment you run a command from your own shell and it works… that’s when Unix starts feeling less like a black box and more like a machine you can take apart and rebuild.
