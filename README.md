# Minishell

Minishell is a simplified Unix shell created as part of the 42 School curriculum. It replicates the core functionalities of a shell, allowing users to execute commands, manage processes, handle redirections, and more. The project emphasizes understanding process management, parsing, and system calls.

---

## Features

- **Interactive Shell:**
  - Prompt for user input.
  - Executes commands interactively.
  
- **Builtin Commands:**
  - `cd`, `echo`, `env`, `export`, `unset`, `pwd`, `exit`.

- **Environment Variable Expansion:**
  - Replace `$VAR` with its corresponding value from the environment.

- **Redirections and Pipes:**
  - Support for `>`, `<`, `>>`, and `|` to handle file redirection and chaining commands.

- **Signal Handling:**
  - Graceful handling of `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.

- **Error Handling:**
  - Lexical and syntax error detection with appropriate error messages.

- **Command Execution:**
  - Execution of external programs using `PATH` resolution.

---

## Installation

1. Clone the repository:
2. Go to minishell dir
3. run `make` to compile the project
4. type `./minishell` to run the project

## Installation

this project was developed by @RafiqAllali and i as part of the 1337 School curriculum
