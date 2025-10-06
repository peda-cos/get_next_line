# Get Next Line

A C implementation of a function that reads a line from a file descriptor, one line at a time. This project is part of the 42 School curriculum and demonstrates efficient file reading with dynamic memory management.

## 📋 Description

`get_next_line` is a function that returns a line read from a file descriptor. The function handles multiple file descriptors simultaneously and manages memory efficiently by using a static variable to preserve data between consecutive calls. Each call to the function returns the next line from the file, including the newline character (if present), until the end of the file is reached.

## 🛠 Technology Stack

- **Language**: C (C99 standard compliant)
- **System Calls**: `read`, `malloc`, `free`
- **Build System**: Manual compilation with gcc/clang
- **Testing**: Custom test files with various edge cases

### Technical Requirements
- Must compile with `-Wall -Wextra -Werror` flags
- No memory leaks allowed
- Configurable buffer size via `BUFFER_SIZE` macro
- Uses only allowed functions: `read`, `malloc`, `free`

## 🏗 Project Architecture

The project follows a modular architecture with clear separation of concerns:

### Core Components

1. **Main Function** (`get_next_line.c`)
   - Entry point that orchestrates line reading
   - Manages static backup buffer between calls
   - Handles file descriptor validation and buffer allocation

2. **Utility Functions** (`get_next_line_utils.c`)
   - `ft_strlen`: Calculate string length
   - `ft_strchr`: Search for character in string
   - `ft_strdup`: Duplicate string
   - `ft_strjoin`: Concatenate two strings
   - `ft_substr`: Extract substring

3. **Header File** (`get_next_line.h`)
   - Function prototypes
   - Library includes
   - Buffer size configuration

### Data Flow

```
File Descriptor → read() → Buffer → Backup (static) → Extract Line → Return
                                          ↓
                                    Store Remainder
```

## 🚀 Getting Started

### Prerequisites

- GCC or Clang compiler
- Make (optional, for automation)
- Standard C library

### Installation

1. Clone the repository:
```bash
git clone https://github.com/peda-cos/get_next_line.git
cd get_next_line
```

2. Compile the project:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test
```

You can adjust `BUFFER_SIZE` to any positive value:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c
```

### Basic Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## 📁 Project Structure

```
get_next_line/
├── get_next_line.c          # Main function implementation
├── get_next_line_utils.c    # Utility functions
├── get_next_line.h          # Header file with prototypes
├── LICENSE                  # MIT License
├── tests/                   # Test files directory
│   ├── simple              # Basic test case
│   ├── empty               # Empty file test
│   ├── empty_one           # Single newline test
│   ├── lorem_ipsum         # Standard text test
│   ├── many_lines          # Multiple lines test
│   ├── multi_in_one        # Multiple FDs test
│   ├── 63_line             # Edge case: 63 chars
│   ├── 63_line_nl          # Edge case: 63 chars + newline
│   ├── 64_line             # Edge case: 64 chars (BUFFER_SIZE)
│   ├── 64_line_nl          # Edge case: 64 chars + newline
│   ├── 65_line             # Edge case: 65 chars
│   ├── 65_line_nl          # Edge case: 65 chars + newline
│   ├── one_big_fat_line.txt # Very long line test
│   ├── large_file.txt      # Large file test
│   ├── baudelaire.txt      # Literary text
│   └── Mr. Justice Maxell by Edgar Wallace.txt
└── .github/
    └── workflows/
```

## ✨ Key Features

- **Line-by-Line Reading**: Efficiently reads files one line at a time
- **Configurable Buffer Size**: Adjustable `BUFFER_SIZE` for optimization
- **Multiple File Descriptors**: Can handle multiple files simultaneously
- **Memory Efficient**: Uses static variable to minimize allocations
- **Robust Error Handling**: Handles edge cases and invalid inputs gracefully
- **Newline Preservation**: Returns lines with their newline characters
- **EOF Detection**: Properly detects and handles end of file
- **No Memory Leaks**: Clean memory management with proper cleanup

## 💻 Development Workflow

### Coding Standards

The project follows strict 42 School coding standards:

#### Norm Compliance
- **File Structure**: Standard 42 header in all files
- **Function Length**: Maximum 25 lines per function
- **Line Length**: Maximum 80 characters per line
- **Functions per File**: Maximum 5 functions
- **Variable Declarations**: At the beginning of functions
- **Indentation**: Tabs (width: 4 spaces visual)

#### Naming Conventions
- Functions: `lowercase_with_underscores`
- Variables: Descriptive, lowercase names
- Macros: `UPPERCASE_WITH_UNDERSCORES`

#### Best Practices
- No global variables (except static when necessary)
- Proper memory management (no leaks)
- Comprehensive error checking
- Clear and logical code organization

### Memory Management Rules

1. **Allocation**: Always check return value of `malloc`
2. **Deallocation**: Free all allocated memory before returning
3. **Error Handling**: Free allocated memory on error paths
4. **Static Variables**: Properly manage static backup buffer

## 🧪 Testing

### Test Coverage

The project includes comprehensive test files covering:

1. **Basic Functionality**
   - Simple text files
   - Files with multiple lines
   - Lorem ipsum standard text

2. **Edge Cases**
   - Empty files
   - Single newline files
   - Lines exactly at buffer boundaries (63, 64, 65 chars)
   - Very long lines
   - Large files

3. **Special Cases**
   - Multiple file descriptors simultaneously
   - Literary texts (Baudelaire, Edgar Wallace)
   - Files without trailing newlines

### Running Tests

Create a test main file:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    int     i = 1;

    fd = open("tests/simple", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", i++, line);
        free(line);
    }
    close(fd);
    return (0);
}
```

Compile and run:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
./a.out
```

### Testing Different Buffer Sizes

Test with various buffer sizes to ensure robustness:
```bash
# Small buffer
cc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c

# Medium buffer
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Large buffer
cc -D BUFFER_SIZE=10000 get_next_line.c get_next_line_utils.c main.c
```

## 🤝 Contributing

Contributions are welcome! Please follow these guidelines:

1. **Code Style**: Follow 42 School norm standards
2. **Testing**: Test with multiple buffer sizes and edge cases
3. **Memory**: Ensure no memory leaks (use valgrind)
4. **Documentation**: Update README for significant changes

### Code Exemplars

When contributing, ensure your code follows these patterns:

```c
// Proper error handling with cleanup
static char *handle_error(char *allocated_memory)
{
    free(allocated_memory);
    return (NULL);
}

// Check allocation results
buffer = malloc(size);
if (!buffer)
    return (handle_error(previous_allocation));

// Static variable usage
static char *backup; // Preserves state between calls
```

### Pull Request Process

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -m 'Add improvement'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Copyright (c) 2025 Pedro Monteiro

## 👤 Author

**Pedro Monteiro (peda-cos)**
- GitHub: [@peda-cos](https://github.com/peda-cos)
- 42 Intra: peda-cos
- Email: peda-cos@student.42sp.org.br

## 🙏 Acknowledgments

- 42 School for the project specifications
- Fellow 42 students for testing and feedback
- The C programming community for best practices

## 📚 Resources

- [42 School](https://www.42.fr/)
- [C File I/O Documentation](https://man7.org/linux/man-pages/man2/read.2.html)
- [Memory Management in C](https://en.cppreference.com/w/c/memory)

---

**Note**: This project is part of the 42 School curriculum. The implementation must adhere to specific constraints and use only approved functions.
