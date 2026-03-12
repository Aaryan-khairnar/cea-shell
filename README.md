# OwO Shell

A minimal Unix shell written in C to explore **processes**, **forking**, and **execution** in Linux. Designed as a learning project for understanding the inner workings of a shell.

## Features

* Reads user input and parses commands.
* Executes programs using:

  * `fork()` – to create a child process.
  * `execvp()` – to run external programs.
  * `wait()` – to wait for the child process to finish.
* Implements built-in commands:

  * `cd [dir]` – change the working directory.
  * `exit` – exit the shell.
* Handles basic arguments for commands:

  ```bash
  ls -la
  echo hello world
  pwd
  ```
* Error handling for invalid directories and failed executions.

## Usage

Compile the shell:

```bash
gcc shell.c -o shell
```

Run the shell:

```bash
./shell
```

You will see the prompt:

```
OwO >
```

Type commands just like a normal terminal:

```bash
OwO > ls
OwO > pwd
OwO > cd /home/user
OwO > echo hello world
OwO > exit
```

## Implementation Details

* **Language**: C
* **Libraries Used**:

  * `<stdio.h>` – input/output
  * `<stdlib.h>` – memory, environment
  * `<unistd.h>` – `fork()`, `execvp()`, `chdir()`
  * `<string.h>` – string parsing with `strtok()`
  * `<sys/wait.h>` – `wait()` for child processes
* **Process Flow**:

  1. Shell prints prompt.
  2. Reads a line from stdin.
  3. Tokenizes the line into command + arguments.
  4. Handles built-in commands (`cd`, `exit`).
  5. Forks a child process for other commands.
  6. Child executes the command.
  7. Parent waits for the child to finish.
  8. Loop repeats.

## Notes

* Only supports **space-separated arguments**. Quotes, pipes, and redirection are not handled.
* `$HOME` is supported when running `cd` with no arguments.
* Meant as an **educational project** to understand Linux processes, not as a full-featured shell.

