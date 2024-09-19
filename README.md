# Find Command
This is a custom implementation of a `find`-like command for UNIX-like operating systems, written in C.


## Features
- Search for files by name.
- Support for wildcard patterns (`.` and `*`).
- Recursive search through directories.


## Installation
To compile and install the `find` command, follow these steps:
1. Clone the repository:
   ```bash
   git clone https://github.com/without-eyes/findCommand.git
   cd findCommand
   ```
2. Compile the program:
  ```bash
  make
  ```


## Usage
The basic syntax for using the find command is:
```bash
./find [file1] [file2] ... [fileN]
```


### Arguments
- file1, file2, ..., fileN: The specific file names or patterns to search for. Wildcards (. and *) can be used to match multiple files.

## Examples
Search for all files named "test.txt":
```bash
./find test.txt
```
Search for all files with names starting with "test":
```bash
/find test*
```
Search for all types of files with name "test.":
```bash
/find test..
```


## Implementation Details
The program uses standard C libraries such as dirent.h for directory traversal.
The code is designed to be simple and demonstrate basic file search functionality.


## License
This project is licensed under the MIT License. See the LICENSE file for details.
