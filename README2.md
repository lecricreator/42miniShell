---

# minishell

A simple command-line shell implementation in C, following the 42 school project guidelines.

## Table of Contents

1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Features](#features)
5. [Limitations](#limitations)
6. [Built-in Commands](#built-in-commands)
7. [External Functions](#external-functions)
8. [Dependencies](#dependencies)
9. [Testing](#testing)
10. [Examples](#examples)
12. [References](#references)
11. [Authors](#authors)

---

## Introduction

`minishell` is a lightweight Unix-like shell written in C. It supports basic command execution, history, environment variable expansion, redirections, pipes, and built-in commands, aiming to replicate core Bash behaviors under 42 school norms. This project have not implemented the bonus part. 
   
It is part of the 42 curriculum and focuses on mastering process control, environment management, and signal handling in UNIX.


## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/lecricreator/42miniShell
   cd minishell
   ```
2. Compile with Makefile:

   ```bash
   make
   ```

## Usage

While on a bash terminal, launch the shell:

```bash
./minishell
```

You will see a custom prompt. Enter commands as in Bash.

## Features

* Display a prompt and handle interactive input
* Command history (up/down arrow navigation)
* Search and execute programs via `$PATH` or absolute/relative paths
* Environment variable expansion (`$VAR`, `$?`)
* Handles proper environmet variable self-updating (`$PWD`, `$OLDPWD`, `$SHLVL`, etc)
* Handles no environment initializing
* Input/Output redirections: `<`, `>`, `>>`, `<<` (heredoc)
* Pipelines using `|`
* Single and double quote handling
* Signal handling: Ctrl-C (SIGINT), Ctrl-D (EOF), Ctrl-\ (SIGQUIT), all behave like in bash.
* Proper exit status management.

### Extra features (not demanded for the project)

* Declaration of non exported environment variables `VAR=VALUE`
* Declaration of temporaly environment variables `VAR=VALUE ./new_program`
* Concatenation of environment variables `VAR+=VALUE`
* Supports the special character `\` for ingnoring interpretation

## Limitations

* No support for unclosed quotes or unsupported special characters (`;` etc)
* No support for `&&` and `||` as they are required only as a bonus.
* Heredoc lines are not stored in history
* `readline()` memory leaks are not addressed

## Built-in Commands

| Command  | Description                                               |
| -------- | ----------------------------------------------------------|
| `echo`   | Prints arguments to standard output, supports `-n`        |
| `cd`     | Changes working directory (no options)                    |
| `pwd`    | Prints current working directory                          |
| `export` | Sets environment variables and marks to export(no options)|
| `unset`  | Removes environment variables (no options)                |
| `env`    | Displays environment variables                            |
| `exit`   | Exits the shell                                           |


## External Functions

external functions used:

```
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, waitpid, signal,
sigaction, sigemptyset, sigaddset, exit,
getcwd, chdir, stat, execve,
dup, dup2, pipe, 
```

## Dependencies

These are the libraries and external resources required to build and run `minishell`:

### Already provided whith this code
* **42 `libft`**: Custom C library providing utility functions (string manipulation, memory management, etc.).
* **`ft_printf`**: Custom implementation of `printf` for formatted output, supports diferent file descriptors.
### Not provided
* **GNU Readline**: For interactive input and command history (`readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`).
* **Standard C and POSIX libraries**: (`<unistd.h>`, `<stdlib.h>`,`<string.h>`,`<stdarg.h>`,`<limits.h>`, `<stdio.h>`, `<fcntl.h>`, `<sys/types.h>`,`<sys/stat.h>`,`<signal.h>`, etc.) used implicitly by allowed system calls.

## Testing

The `readline` function already causes leaks, so to avoid that while testing and properly check leaks on this code, we provide a `ignore_readline_leaks.supp` file, to use with the following valgrind script:
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=val_out.log --suppressions=ignore_readline_leaks.supp ./minishell
```
This will launch the shell with valgrind and send any valgrind issue to a `val_out.log` file.
Feel free to to test this with the following examples or just go crazy!.

## Examples

![Prompt Example](images/prompt_example.png)

```bash
Minishell $ echo "Hello, $USER"
Hello, yourusername
```

```bash
cd
env | grep PWD
cd -
env | grep PWD
cd ~
```

```bash
Minishell $ < test_file cat | grep "some text" | wc -w > output.txt
```

```bash
Minishell $ cat \<< eof \<< end > only_last_counts.txt
> this will be lost
> like tears in the rain
> eof
> but this will remain
> end
Minishell $ cat only_last_counts.txt 
but this will remain
```

```bash
cat | cat | cat | ls
ft_printf                   include  Makefile   README.md
ignore_readline_leaks.supp  libft    minishell  src



Minishell $ 
```

```bash
VAR=VALUE
echo $VAR
export
export VAR
export
export VAR+=" YOURSELF"
export
```
![Pipeline Example](images/pipeline_example.png)

## References

[bash manual](https://www.gnu.org/software/bash/manual/bash.html)

## Authors

* Oscar Drüke Santana [odruke-s@student.42lausanne.ch](mailto:odruke-s@student.42lausanne.ch)
* Louca Morales (`email@example.com`)
