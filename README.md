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

 - so once a token gets "delimited", you immediately parse it, and a recognized `complete_command` gets immediatly executed before tokenization continues.

**2026.05.06. - 2026.05.07.**
- worked on the arena implementation:
  - added `arena_grow` function
  - reworked alignment to be a member of the struct: `arena->align` encodes the type of alignment (if the alignment is set to 0, it should be using default dynamic alignment)

**2026.05.12.**
- `env` has to be a built-in, which it isn't in `bash`
- added description of token recognition rules
- added description of shell grammar

**2026.05.13.**
- created a simple parser with flex and bison
  - got overwhelmed reading the generated `.c` files
- wrote makeshift `bnaf` format grammar rules

**2026.05.14. - 2026.05.16.**
- acquired rene's annotated bash manual pdf.
  - nice as an overview of what is actually relevant for minishell accoring to rene
- read from bash manual about execution, [3.7 Executing Commands](https://www.gnu.org/software/bash/manual/bash.html#Executing-Commands):
  - order of expansion for simple commands: [3.7.1 Simple Command Expansion](https://www.gnu.org/software/bash/manual/bash.html#Simple-Command-Expansion)
  - order of `PATH` search & command execution: [3.7.2 Command Search and Execution](https://www.gnu.org/software/bash/manual/bash.html#Command-Search-and-Execution)
  - commands in pipelines are always executed in a child, [3.2.3 Pipelines](https://www.gnu.org/software/bash/manual/bash.html#Pipelines): "Each command in a multi-command pipeline, where pipes are created, is executed in its own subshell, which is a separate process."
  - the shell has it's own execution environment, that consists of inheritances at invocation (`char **envp`) and modifications through builtins, like `cd` and `export`, or assignments `name=word`
  - commands other than builtins are executed in their seaprate execution environment (`child process`) with values inherited from the shell's environment ("variables marked for `export`"), everything copied by `fork()` (open fds, file creation mask) (additionally, but not required by the project: assignments before the command name, which are injected temporarily into the env for this one command)

**2026.05.17.**
- looked through the `makefiles` of people for inspiration (starred on github)
- used `declare` to see all shell variables listed, which nicely shows what the different attributes of shell variables are

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

**2026.05.17.**
- read about [`trap`](https://www.gnu.org/software/bash/manual/bash.html#index-trap): executes a given command when a given signal is intercepted.
- learned neat bash trick: `set -e; : ${parameter:?word}` to close the shell if the parameter doesn't exist in the execution environment.
- read about [`job control`](https://www.gnu.org/software/bash/manual/bash.html#Job-Control)

### Structure

*see [2.1 Shell Introduction](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_01)*
1. //TODO: write out the whole structure, first as graph, then as high abstraction pseudocode.

### Schedule

- starting on 2026.05.07. Nikita is on vacation until the 2026.05.22.

### TODO

#### minishell

**research & documentation**
- [ ] compile documentation on signals
- [ ] compile documentation on `curses.h` and `term.h`
- [p] research built-ins
- [ ] research interactive mode
- [ ] research `posix sh`
- [ ] research git workflow for working in a team
- [ ] research managing memory with multiple arenas, because there are actual multiple lifetimes
- [ ] research how to implement the variable content size for tokens in the context of expansion
- [ ] research how readline interacts with arenas and if it would even make sense to implement them
- [-] ~~compile documentation on `flex` and `bison`~~

**implementation**
- [ ] add github action workflow
- [ ] add push/pull mirroring on remote
- [ ] rework makefile to create/use separate folders (`src`, `include`, `bin`, `debug`, `test`)
- [ ] create harness for automatic unit testing (tdd)
- [ ] draft the data structure and core architecture
- [ ] finish writing the readme file
- [ ] consider error handling according to posix
- [x] ~~add github remote~~
- [x] ~~write a simple `flex` and `bison` based lexer and parser~~

**questions**
- [ ] what does this mean in the context of Shell Grammar: "This formal syntax shall take precedence over the preceding text syntax description"

#### longterm

- [ ] test automation for checking the repo before pushing
- [ ] create a dotfile repo
- [p] create a resources repo
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
**man pages**
- `man bash`
- `man readline`
- `man termios` - `tcgetattr`, `tcsetattr`

- `man chdir`

**pdfs**
- [Wang - Tutorial Flex Bison](../resources/wang-tutorial_flex_bison.pdf)
- [Levine - Flex & Bison](../resources/levine-flex&bison.pdf)
- [Aaby - Compiler Construction using Flex and Bison](../resources/aaby-compiler_construction_using_flex_and_bison.pdf)

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

- stack based parsing, similar to how bash does it, but with hard coded rules.

### Core Data Structure

```c
```

### Parsing

#### Token Recognition

Input is read in terms of lines in 2 different circumstances:

**here-doc processing**

**ordinary token recognition**
apply the first applicable rule from the list:

```
1.	if
		`cur_char` is `EOI`/`EOF`
	do
		delimit `cur_token`, if it exists
```

```
2.	if
		`prev_char` is part of `operator`
		&& `cur_char` is unquoted
		&& `cur_char` can be used with the `prev_char` to form an `operator`
	do
		add `cur_char` to the `cur_token`
```

```
3.	if
		`prev_char` is part of `operator`
		&& `cur_char` cannot be used with the `prev_char` to form an `operator`
	do
		delimit the `cur_token`
```

```
4.	if
		`cur_char` is a `quote_char`(`'`, `"`)
	do
		<add `cur_char` to the `cur_token`
		&& add following `char`s to the `cur_token` unmodified until the closing `quote_char` was found
		&& DO NOT DELIMIT `cur_token`
```

```
5.	if
		`cur_char` is beginning of variable expansion (`$`)
	do
		add `cur_char` to the `cur_token`
		&& add following `char`s to the `cur_token` unmodified while valid `name_chars`
```

```
6.	if`cur_char` is unquoted
		&& `cur_char` is start of an `operator`
	do	
		delimit `cur_token` if it exists
```

```
7.	if
		`cur_char` is unquoted
		&& `cur_char` is `blank` (` `, `\t`)
	do
		delimit `cur_token`
		&& discrad `cur_char`
```

```
8.	if
		`prev_char` is part of `word_token`
	do	
		add `cur_char` to the `cur_token`/`word_token`
```

```
9.	if
		`cur_char` is `comment_char` (`#`)
	do
		discard `cur_char`
		&& discrad `chars` until `\n`
```

```
10.	do
		`cur_char` is used as the start of a new `word_token`
```

Once delimited, a token get's lexed according to the Shell Grammar.

"In situations where the shell parses its input as a program, once a `complete_command` has been recognized by the grammar (see 2.10 Shell Grammar), the `complete_command` shall be executed before the next `complete_command` is tokenized and parsed."

#### Grammar
*see [2.10 Shell Grammar](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10)*

**Shell Grammar Lexical Conventions**
Lexing happens immediately following the `token` being delimited.

```
1.	if
		`cur_token` is `operator`
	do
		identify as corresponding `token_id`
```

```
2.	if
		`cur_token` is only `digits`
		&& `delimiter` is `<` or `>`
	do
		identify as `IO_NUMBER`
```

```
3.	do	# actually rule 4, but we do not implement `IO_LOCATION`
		identify as `TOKEN`
```

```ebnf
/* -------------------------------------------------------
       Selection of Grammar Symbols used in Minishell
   ------------------------------------------------------- */

%token  WORD				/* ".*" */
%token  ASSIGNMENT_WORD		/* 'NAME[=]WORD' */
%token  NAME				/* 'WORD("[a-zA-Z_][a-zA-Z0-9_]*")' */
%token  NEWLINE				/* '\n'*/
%token  IO_NUMBER			/* 'WORD("[0-9].*")'[GREAT|LESS]*/

%token	AND_IF	OR_IF	DLESS	DGREAT	LESS	GREAT	OPAR	CPAR
/*		'&&'	'||'	'<<'	'>>'	'<'		'>'		'('		')'		*/
```

**Shell Grammar Rules**

```
1. (rule 2 - redirection to or from `filename`)
	1.1. tilde expansion
	1.2. parameter/variable expansion
	1.3. quote removal		// actually 5th expansion, but we don't handle command substitution or arithmetic expansion
	1.4. filename expansion
	1.5. word splitting		// if more than one word, bash errors with: `bash: $var: ambiguous redirect`
```

```
2. (rule 3 - redirection from `here-doc`) 
	Quote removal of `WORD` after `DLESS` to determine `here-doc` `delimiter`
```

```
3. (rule 7 - assignment preceding command name)
	//TODO: continue writing
```

**documentation**
- [2.7 Redirections](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_07)
- [2.10.2 Shell Grammar Rules](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10_02)
- [3.45 Blank Character](https://pubs.opengroup.org/onlinepubs/9799919799/basedefs/V1_chap03.html#tag_03_45)



### Bash Specific Terms

**bash grammar**
the following chars don't have an explicit token they get assigned to in the grammar.

```
	'&'	'|'	'('	')'	'<'	'>'
```
- being single `char` tokens, they can just represent themselves?

#### metacharacters

*see [2. Definitions - metacharacter](https://www.gnu.org/software/bash/manual/bash.html#index-metacharacter)*
- characters that separate words when unquoted.
```
' ', '\t', '\n', '|', '&', ';', '(', ')', '<', '>'
```

#### operators

*see [2. Definitions - operator](https://www.gnu.org/software/bash/manual/bash.html#index-operator_002c-shell)*
- `operator`s contain at least one unquoted `metacharacter`

**control operators**
*see [2. Definitions - control operator](https://www.gnu.org/software/bash/manual/bash.html#index-control-operator)*
- 

**redirection operators**
*see [3.6 Redirections](https://www.gnu.org/software/bash/manual/bash.html#Redirections)*
- 

### Execution



### Signals

### Error Handling and Cleanup

---

## Resources

### Documentation and References

#### Special Thanks To

### AI Usage

AI tools were used mainly for interactive rubber ducking, and searching for information.

