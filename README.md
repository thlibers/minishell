_This project has been created as part of the 42 curriculum by **nclavel**, **thlibers**_

<div align="center">
    <h1>STILL IN BUILD</h1>
    <img src=".images/logo.png"> <!--  Mettre le logo en vert + mettre le fond en transparent (nom = bloody) --->
</div>

## Description:
 <!--  Tournure de phrase a changer --->
Minishell is a **shell coded in C** with a full preservation history that keeps every command type in memory in a file, multi-piping which allows sending the standard output of a command into the standard input of another command, 7 built-in commands (cd, echo, export, unset, env, exit and pwd), ....

A shell is a **C**ommand**L**ine user **I**nterface ***(CLI)*** that bridges between the user and the system by interpreting the command typed by the user in his terminal. A lot of different shells are available, like sh, bash, zsh, fish and many more.

Doing this project has improved the understanding of how UNIX system works and how a program can effectively treat a string to understand and execute in such a way as to do what the user wants to do.

## Instruction:
1. Build the project using `make` 
```sh
make
# OR 
make minishell
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
make fclean
```
- Remove every compilation object file, remove the compiled file and rebuild the project
```sh
make re
```

## Available features:
- [ ] Fully fonctional piping system
- [x] Fully preservation history
- [x] Fully fonctional builtin
- [ ] Condition priority
- [ ] File redirection
- [x] Complete expand token
- [ ] Heredoc support
- [ ] Wildcard expand

## Technical choice
A lexer (also known as tokenizer) is a program that reads raw text character by character and breaks it down into meaningful chunks called tokens. We have used a lexer when the user have typed a commande line to split it token with the type T_WORD or any possible operator we have handle (see the list of available operator in [Available features section](https://github.com/thlibers/minishell?tab=readme-ov-file#available-features)).

<img src=".images/lexer.png" width=720><br>

To facilitate the execution of the different command we created an AST (Abstract Syntax Tree). An AST is a data structure shaped like a tree who are compose of a root (the original node), one/multiple branch (subnode) and leaf (node where data is stored)

<img src=".images/tree_scheme.png" width=720> <br>

## Example:
![PLACEHOLDER COMPILATION GIF](.images/placeholder.jpg) <br>
![PLACEHOLDER EXECUTION GIF](.images/placeholder.jpg)

## Ressources used:
- [Bash documentation](https://pubs.opengroup.org/onlinepubs/9699919799/functions/contents.html)
- [Readline documentation](https://web.mit.edu/gnu/doc/html/rlman_2.html#IDX113)
- [Function manual provided by linux](https://www.man7.org/linux/man-pages/index.html)
- [Tokenize a string](https://www.geeksforgeeks.org/cpp/string-tokenization-in-c/)
- [AST wikipedia](https://en.wikipedia.org/wiki/Abstract_syntax_tree)
- [Lexer analysis wikipedia](https://en.wikipedia.org/wiki/Lexical_analysis)
- [Our brain](https://github.com/thlibers/minishell)


<div align=center>
    <a href="https://github.com/thlibers/minishell/?tab=readme-ov-file#description">
        <ul>
            <b>
            <il>Made with ❤️ by</il>
            <il>thlibers</il> <!-- GOAT -->
            <il>nclavel</il>
            </b>
        </ul>
    </a>
</div>