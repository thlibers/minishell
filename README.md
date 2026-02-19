_This project has been created as part of the 42 curriculum by **nclavel**, **thlibers**_

# STILL IN BUILD

## Description:
A shell is a **CommandLine user Interface (CLI)**  who do the bridge between the user and the system by interpreting the command type by the user. A lot of shell different is available like sh, bash, zsh, fish and many more. Doing this project improve the understanding of how an UNIX system work and how a program can effictively treat a string to understand and exectue in such way as to do what the user want to do. <br>
Minishell is a **shell coded in pure C** with a multi-session history who keep every command type in memory, a multi-pipeing which allow to send the standard output of a command into the standard input of a second command, 7 builtin, ....

## Instruction:
1. Build the project with `make` 
```sh
make
```
2. Launch the shell
```sh
./minishell
```
- Remove every compilation object file
```sh
make clean
```
- Remove every compilation object file and remove the compiled file
```sh
make clean
```

## Ressources used:
- [Bash documentation](https://pubs.opengroup.org/onlinepubs/9699919799/functions/contents.html)
- [Tokenize a string](https://www.geeksforgeeks.org/cpp/string-tokenization-in-c/)
- [AST wikipedia](https://en.wikipedia.org/wiki/Abstract_syntax_tree)


## Available features:
- [x] Fully fonctional history
- [x] Fully fonctional builtin
- [ ] Fully fonctional pipe
- [ ] Heredoc support
- [ ] File redirection
- [ ] Wildcard expand
- [ ] Condition priority

## Technical choise
To facilitate the execution of the different command we have create an AST (Abstract Syntax Tree). {{{DEFINITION AST}}}

## Example:
![PLACEHOLDER COMPILATION GIF](img/placeholder.jpg) <br>
![PLACEHOLDER EXECUTION GIF](img/placeholder.jpg)