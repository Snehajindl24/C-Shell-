
## C-Shell: A Custom-Built Shell in C 💻
Project Overview
C-Shell is a custom-designed command-line interface (CLI) built entirely in the C programming language. This project emulates the core functionality of a traditional Unix shell, providing a robust environment for executing commands, managing processes, and interacting with the file system. It serves as an excellent demonstration of low-level system programming, showcasing concepts like process creation, command parsing, and file I/O.

Key Features
Command Execution: The shell can parse and execute a variety of commands, including both built-in utilities and external programs.

Custom Utilities: Includes unique, custom-built commands like reveal and seek to perform specific file and directory operations.

Process Management: Manages child processes effectively, allowing for seamless command execution.

Logging System: A dedicated logging mechanism tracks important shell activities and command history in log.txt.

Modular Design: The project is structured with a clean, modular design, separating different functionalities into distinct files (e.g., log.c, main.c, procdore.c).

Robust Build System: A comprehensive makefile simplifies the compilation process, ensuring the project can be built and run with a single command.

How to Build and Run
Clone the Repository:

Bash

git clone https://github.com/Snehajindl24/C-Shell-.git
cd C-Shell-
Compile the Project:
Simply use the make command to compile all source files and link them into the final executable shell_program.

Bash

make
Run the Shell:
Execute the compiled program from the terminal.

Bash

./shell_program
File Structure
main.c: The main entry point of the shell, handling the primary command loop.

makefile: Automates the compilation and linking process.

log.c/log.h: Implements the logging functionality for recording shell events.

procdore.c/procdore.h: Manages process creation and execution.

reveal.c/reveal.h: Contains the source for a custom command to list directory contents.

seek.c/seek.h: Provides functionality for a custom command, likely for searching files or directories.

shell_program: The final compiled executable file.
