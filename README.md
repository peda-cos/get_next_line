*This project has been created as part of the 42 curriculum by peda-cos*

# Get Next Line

A C function that reads a line from a file descriptor, one line at a time.

## Description

Get Next Line is a utility function that reads from a file descriptor and returns one line at a time. A line is defined as a sequence of characters ending with a newline character (`\n`) or the end of file (EOF). This project demonstrates the use of static variables in C to maintain state between function calls.

### Key Features

- Reads from any file descriptor (files, standard input, pipes)
- Returns one line per call, including the newline character when present
- Handles any buffer size (defined at compile time)
- Memory leak-free implementation
- Bonus: Supports multiple file descriptors simultaneously

## Instructions

### Compilation

Compile the mandatory part:
```bash
make
```

Compile with a custom buffer size:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c
```

Compile the bonus part:
```bash
make bonus
```

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Makefile Rules

- `make` or `make all` - Compile the mandatory part
- `make bonus` - Compile the bonus part (multiple file descriptors)
- `make clean` - Remove object files
- `make fclean` - Remove object files and the library
- `make re` - Recompile everything

## Resources

### Documentation

- [man 2 read](https://man7.org/linux/man-pages/man2/read.2.html) - System call for reading from file descriptors
- [man 3 malloc](https://man7.org/linux/man-pages/man3/malloc.3.html) - Memory allocation
- [Static variables in C](https://en.wikipedia.org/wiki/Static_variable) - Understanding static variables

### Articles & Tutorials

- [42 School's get_next_line guide](https://42-cursus.gitbook.io/guide/rank-01/get_next_line)
- [File descriptors explained](https://www.computerhope.com/jargon/f/file-descriptor.htm)

### AI Usage

This project was implemented without the assistance of AI code generation tools. AI was used solely for:
- Understanding the requirements from the project subject
- Researching best practices for static variable usage in C
- Debugging memory leak issues during testing

## Algorithm

### Overview

The algorithm uses a static buffer to store leftover characters from previous reads that belong to the next line. This is necessary because `read()` may read past the current newline, and we need to preserve those characters for the next call.

### Step-by-Step Process

1. **Reading Phase**: 
   - Check if the current buffer already contains a newline
   - If not, read `BUFFER_SIZE` bytes into a temporary buffer
   - Append the temporary buffer to the static buffer
   - Repeat until a newline is found or EOF is reached

2. **Extraction Phase**:
   - Find the position of the newline (or EOF)
   - Extract the line from the beginning to (and including) the newline
   - Return the extracted line

3. **Buffer Update Phase**:
   - Remove the extracted line from the static buffer
   - Keep only the remaining characters (next line content)
   - Free the old buffer and update the static pointer

### Static Variable Strategy

- **Mandatory**: Uses a single `static char *buffer` to store leftovers between calls
- **Bonus**: Uses a `static char *buffer[MAX_FD]` array to handle multiple file descriptors simultaneously, where each index corresponds to a specific fd

### Memory Management

- The temporary read buffer is freed after each call to `read_to_buffer()`
- The old buffer content is freed when updating to the new buffer
- `ft_strjoin()` frees the first string argument to prevent leaks
- Returns `NULL` on error, allowing the caller to handle cleanup

### Complexity Analysis

- **Time Complexity**: O(n) where n is the total bytes read, as each byte is processed exactly once
- **Space Complexity**: O(BUFFER_SIZE + line_length) for the temporary and static buffers
