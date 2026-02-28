_This project has been created as part of the 42 curriculum by **nclavel**, **thlibers**_

<div align="center">
    <h1>STILL IN BUILD</h1>
    <img src=".images/logo.png"> <!--  Mettre le logo en vert + mettre le fond en transparent (nom = bloody) --->
</div>

## Description:
 <!--  Tournure de phrase a changer --->
Minishell is a **shell coded in C**. To do this project we have reused the project called [pipex](https://github.com/thlibers/pipex_avec_bonus) done earlier on the 42 curriculum.

A shell is a **C**ommand**L**ine user **I**nterface ***(CLI)*** that bridges between the user and the system by interpreting the command typed by the user in his terminal. A lot of different shells are available, like sh, bash, zsh, fish and many more.

This project deepened our understanding of how UNIX systems work and how a program can parse and process a command string to execute what the user wants to do.

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
- [x] Use minishell on a non tty mode (partial support)
- [x] Fully fonctional piping system
- [x] Fully functional history
- [x] Fully fonctional builtin
- [x] Complete expand token
- [x] File redirection
- [x] Heredoc support
- [ ] Condition priority
- [ ] Wildcard expand

## Technical choice
A lexer (also called a tokenizer) reads raw text one character at a time and splits it into meaningful pieces called tokens. After the user types a command line, the lexer processes that input and produces tokens labeled with their exact types (see the list of operators in the ["Available features"](https://github.com/thlibers/minishell?tab=readme-ov-file#available-features) section) .

<img src=".images/lexer.png" width=720><br>

An Abstract Syntax Tree (AST) is a tree-shaped data structure used to represent commands for execution. It has a top node called a root, intermediate nodes called branches (subnodes), and leaf nodes where data are stored.

<img src=".images/ast.png" width=720> <br>

## Example:
<div align="center">
    <img width=64 src=".images/placeholder.jpg">
    <br><br>
    <img width=64 src=".images/placeholder.jpg">
</div>

## Ressources used:
- [Bash documentation](https://pubs.opengroup.org/onlinepubs/9699919799/functions/contents.html)
- [Readline documentation](https://web.mit.edu/gnu/doc/html/rlman_2.html#IDX113)
- [Function manual provided by linux](https://www.man7.org/linux/man-pages/index.html)
- [Tokenize a string](https://www.geeksforgeeks.org/cpp/string-tokenization-in-c/)
- [AST wikipedia](https://en.wikipedia.org/wiki/Abstract_syntax_tree)
- [Lexer analysis wikipedia](https://en.wikipedia.org/wiki/Lexical_analysis)
- [Piping in UNIX/Linux](https://www.geeksforgeeks.org/linux-unix/piping-in-unix-or-linux/)

<br>

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