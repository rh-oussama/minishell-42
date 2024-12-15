# Minishell - A Simple Shell Implementation in C

## Description
Minishell is a custom shell program built in C, designed to mimic basic shell functionalities such as command execution, input/output redirection, piping, and environment variable expansion. This project is a deep dive into process management, file descriptors, and shell-like behavior.

## Features

### Core Features
- Display a prompt when waiting for new commands.
- Maintain a working command history.
- Search and execute commands from the system PATH or relative/absolute paths.
- Handle basic quoting mechanisms (`'` and `"`) and command metacharacters.
- Implement basic redirections:
  - Input redirection (`<`)
  - Output redirection (`>`)
  - Here document redirection (`<<`)
  - Output append redirection (`>>`)
- Handle pipes (`|`) to connect multiple commands.
- Expand environment variables (e.g., `$HOME`) in commands.
- Expand `$?` to show the exit status of the last command.

### Interactive Mode Behaviors
- **Ctrl-C**: Display a new prompt on a new line.
- **Ctrl-D**: Exit the shell.
- **Ctrl-\**: Do nothing.

## Built-in Commands
- `echo` (with `-n` option)
- `cd` (relative or absolute path only)
- `pwd` (no options)
- `export` (no options)
- `unset` (no options)
- `env` (no options or arguments)
- `exit` (no options)

## Bonus Features
- Implement logical operators `&&` and `||` with parentheses for command priority.
- Support wildcard expansion for the current working directory (`*`).

## Requirements
- C programming language.
- Follow the Norm (coding standards).
- Memory management: No memory leaks, heap memory should be freed when needed.
- Your shell should be capable of managing file descriptors and processes.
- You should handle signals like `SIGINT` and `SIGQUIT`.

## Compilation
To compile the shell, run the following command:

```
make
```

This will compile the source files and generate the `minishell` executable.
