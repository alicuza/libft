_This project has been created as part of the 42 curriculum by nribakov, sancuta._

# minishell

## Notes:

### Journal

#### minishell

**2026.04.26.**
- read about readline
- set up the repo
- drafted minishell.h
- drafted main.c
- drafted README.md
- added documentation on the readline, posix standard, bash manual
- made todo lists for minishell, longterm
- added description

**2026.04.27.**
- read up on how to reopen closed stdin/out/err fds: `open(/dev/tty)`
- researched the allowed functions to a certain degree

**2026.04.28.**
- added some documentation for termcap library
- decided on using github, with feature branches and pull requests
- heard about interactive mode (when a program waits for inputs)

**2026.04.29.**
- read from posix: quoting, tokenizing, expansion, redirection
- tested stuff out, bash seems to closesly follow the posix version on these topics

**2026.04.30.**
- read from posix: interactive mode, command line editing (vi mode)

**2026.05.01. - 2026.05.04**
- read from posix: the IFS variable and it's effect on variable expansion
- read about the difference between env and set, environment and internal shell variables

**2026.05.05**
- read from posix, [2.3 Token Recognition](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_03):

```
Once a token is delimited, it is categorized as required by the grammar in 2.10 Shell Grammar.

In situations where the shell parses its input as a program, once a complete_command has been recognized by the grammar (see 2.10 Shell Grammar), the complete_command shall be executed before the next complete_command is tokenized and parsed.
```

  - so once a token gets "delimited", you immediately parse it, and a recognized command gets immediatly executed before tokenization continues.

**2026.05.06**
- fixed UB in `ft_memmove`, comparing pointers that are not necessarily pointing to the same object in memory. Cast to `intptr_t` first.
- first structure sketched: [Visualisation](https://excalidraw.com/#json=8BAFo2sDfsrJqzire7OOM,YjbRdUHRhwRBObV-QLgAXg)
  - tokens will reference slices of the input string, maintaining the original information such as type of quotes and expansion characters.
  - tokens resulting from expansion will be appended to the token arena and relinked through indices to maintain the correct order of operations.

#### personal
**2026.04.30**

```sh
# less colors for man pages
export LESS=-R

export LESS_TERMCAP_mb=$'\e[01;38;5;211m' # begin blinking
export LESS_TERMCAP_md=$'\e[01;38;5;116m' # begin bold
export LESS_TERMCAP_me=$'\e[0m'           # end mode

export LESS_TERMCAP_so=$'\e[30;38;5;222m' # begin standout-mode - info box
export LESS_TERMCAP_se=$'\e[0m'           # end standout-mode

export LESS_TERMCAP_us=$'\e[04;38;5;183m' # begin underline
export LESS_TERMCAP_ue=$'\e[0m'           # end underline
```

**documentation**
- `man console_codes`
- [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code)

### Structure

*see [2.1 Shell Introduction](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_01)*
*see [structure sketch](https://excalidraw.com/#json=8BAFo2sDfsrJqzire7OOM,YjbRdUHRhwRBObV-QLgAXg)*
1. //TODO: write out the whole structure, first as graph, then as high abstraction pseudocode.

### Schedule

- starting on 2026.05.07. Nikita is on vacation until the 2026.05.24.

### TODO

#### minishell

**research & documentation**
- [ ] compile documentation on signals
- [ ] compile documentation on `curses.h` and `term.h`
- [ ] research interactive mode
- [ ] research `posix sh`
- [ ] research git workflow for working in a team
- [ ] research managing memory with multiple arenas, because there are actual multiple lifetimes
- [ ] research how to implement the variable content size for tokens in the context of expansion
- [ ] research how readline interacts with arenas and if it would even make sense to implement them

**implementation**
- [d] add `arena_grow` function to arena library // on phone branch
- [d] add github remote, and github action workflow
- [ ] add push/pull mirroring on remote
- [ ] rework makefile to create/use separate folders (`src`, `include`, `bin`, `debug`, `test`)
- [ ] create harness for automatic unit testing (tdd)
- [ ] draft the data structure and core architecture
- [ ] finish writing the readme file
- [ ] consider error handling according to posix

#### longterm

- [ ] test automation for checking the repo before pushing
- [ ] create a dotfile repo
- [d] create a resources repo
- [ ] create a README.md template
- [ ] create a script to automate initializing a git repo with remotes and templates
- [ ] create templates for the header(s), main.c and README.md
- [ ] create project website with git pages
- [ ] play around with `sh vi mode`
- [ ] migrate libft to its own repo and extract history from the repos it is in now

### Documentation

#### online
**readline**
- [GNU Readline Library](https://tiswww.cwru.edu/php/chet/readline/rltop.html)
  - [The GNU Readline Library](https://tiswww.cwru.edu/php/chet/readline/readline.html)
  - [The GNU History Library](https://tiswww.case.edu/php/chet/readline/history.html)
  - [The GNU Readline User Interface](https://tiswww.case.edu/php/chet/readline/rluserman.html)

**termcap**
- [The Termcap Manual](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html)

**posix**
- [POSIX.1-2024](https://pubs.opengroup.org/onlinepubs/9799919799/)
  (same as "IEEE Std 1003.1-2024" and "The Open Group Standard Base Specifications, Issue 8")
  - [Shell & Utilities](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/toc.html)
    - [Consequences of Shell Errors](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_08_01)
  - [sh — shell, the standard command language interpreter](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sh.html)

**bash**
- [GNU Bash manual](https://www.gnu.org/software/bash/manual/bash.html)

**general**
- [Shell (Computing)](https://en.wikipedia.org/wiki/Shell_(computing))

**forgejo & codeberg**
- [Forgejo - Repository Mirrors](https://forgejo.org/docs/latest/user/repo-mirror)
- [Codeberg Pages](https://codeberg.page/)

#### local
- `man bash`
- `man readline`
- `man termios` - `tcgetattr`, `tcsetattr`

- `man chdir`

---

## Description

`minishell` is a miniature shell with a limited feature set. A shell is a program that manages the interaction between **user** and **system**. In a REPL (read-eval-print loop), the shell prompts the user for input, interprets the commands according to the command language syntax, and handles the output from the system.

---

## Table of Contents

- [Description](#description)
- [Instructions](#instructions)
  - [Compilation](#compilation)
  - [Usage](#usage)
  - [Functionality](#functionality)
- [Known Limitations](#known-limitations)
- [Algorithm and Data Structure](#algorithm-and-data-structure)
  - [Architecture Overview](#architecture-overview)
  - [Core Data Structure](#core-data-structure)
  - [Parsing](#parsing)
  - [Execution](#execution)
  - [Signals](#signals)
  - [Error Handling and Cleanup](#error-handling-and-cleanup)
- [Resources](#resources)
  - [Documentation and References](#documentation-and-references)
    - [Special Thanks To](#special-thanks-to)
  - [AI Usage](#ai-usage)

---

## Instructions

### Compilation

- `make` or `make all`: compiles `minishell`
- `make clean`: removes object and dependency files
- `make fclean`: additionally removes the binary and libs
- `make re`: recompiles the entire project from scratch
- `make debug`: compiles with the `-g` flag for debugging

**Dependencies:**
- libft (bundled)

### Usage

```bash
```

### Functionality

```bash
```

---

## Known Limitations

---

## Algorithm and Data Structure

### Architecture Overview

### Core Data Structure

```c
```

### Parsing

### Execution

### Signals

### Error Handling and Cleanup

---

## Resources

### Documentation and References

#### Special Thanks To

### AI Usage

AI tools were used mainly for interactive rubber ducking, and searching for information.

