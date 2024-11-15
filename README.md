# Get Next Line

This repository contains an implementation of the `get_next_line` function, which reads one line from a file descriptor at a time, making it useful for processing large files without reading them entirely into memory.

## Files Overview

- `get_next_line.c` - The implementation of the `get_next_line` function.
- `get_next_line_utils.c` - Utility functions used by `get_next_line`.
- `get_next_line.h` - Header file defining the function prototypes and necessary includes.
- `tests/` - A directory containing various test files for testing the `get_next_line` implementation.

### `main.c`

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int fd;
	char *line;
	int i = 1;

	while (i < argc)
    {
		fd = open(argv[i], O_RDONLY);
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("%s\n", line);
			free(line);
		}
		close(fd);
		i++;
    }
	return 0;
}
```

## How to Use

### 1. Clone the Repository

To clone this repository, use the following command:

```bash
git clone https://github.com/peda-cos/get_next_line.git
cd get_next_line
```

### 2. Compile the Code

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=21 main.c get_next_line.c get_next_line_utils.c
```

- `-Wall` - Enables most of the common warnings.
- `-Wextra` - Enables additional warnings.
- `-Werror` - Treats all warnings as errors.
- `-D BUFFER_SIZE=21` - Defines the `BUFFER_SIZE` macro to specify the buffer size used in `get_next_line`.

### 3. Run the Tests

To run the tests, use `valgrind` to check for memory leaks and errors, and pass all the test files as arguments to the compiled program:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out tests/*
```

This command will run the program, checking for memory leaks and other issues while processing each test file in the `tests/` directory.

- `-Wall` - Enables most of the common warnings.
- `-Wextra` - Enables additional warnings.
- `-Werror` - Treats all warnings as errors.
- `-D BUFFER_SIZE=21` - Defines the `BUFFER_SIZE` macro to specify the buffer size used in `get_next_line`.


### 4. Testing with Standard Input (stdin)

If you want to test with `stdin` (i.e., input from the terminal), modify the `main.c` file to receive file descriptor `fd = 0` (which refers to `stdin`). You can adjust the logic to test with other file descriptors as needed. You are confident in your ability to modify the code because, as a cadet, you're already incredible at this! 💪😎

### Test Files in `tests/`

Here’s a brief overview of the test files available in the `tests/` folder:

- `empty` - An empty file.
- `large_file.txt` - A large file to test performance with large inputs.
- `one_big_fat_line.txt` - A file with one large line of text.
- `over_buffer` - A file where the size of the content exceeds the buffer size.
- `Mr. Justice Maxell by Edgar Wallace.txt` - A text file from a public domain book.
- `65_line_nl`, `64_line_nl`, `63_line_nl` - Files with 65, 64, and 63 lines, each ending with a newline.
- `64_line`, `63_line`, `65_line` - Files with 64, 63, and 65 lines, without a newline at the end of the last line.
- `many_lines` - A file with many lines to test general functionality.
- `baudelaire.txt` - Another public domain text file for testing.
- `multi_in_one` - A file that contains multiple lines in one single line, to test multiline handling.
- `lorem_ipsum` - A file with "Lorem Ipsum" placeholder text.
- `empty_one` - A file with one empty line.
- `simple` - A simple test file with a few lines.

These test cases are designed to cover various edge cases, including files with no content, files with different line endings, and files with varying line lengths.

Notes
---

- Ensure that your `BUFFER_SIZE` is set appropriately for your test cases. The default in the example above is 21, but you can adjust it by modifying the `-D BUFFER_SIZE=21` line during compilation.
- You can also add more test files or modify existing ones in the `tests/` directory to suit your needs.

Good luck, cadet! You’ve got this. I’m confident you’ll nail it! 😄

![norminette](https://github.com/peda-cos/get_next_line/actions/workflows/main.yml/badge.svg)
