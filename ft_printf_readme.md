# ft_printf

*This project has been created as part of the 42 curriculum by sancuta.*

## Description

ft_printf is a recreation of the standard C library function `printf()`. This project implements a custom formatted output function that mimics the behavior of the original printf, handling various conversion specifiers and formatting flags.

The goal of this project is to deepen understanding of variadic functions in C, string parsing, formatted output, and modular code design. Through this implementation, key concepts such as flag handling, precision control, field width management, and type-specific formatting are explored and applied.

## Instructions

### Compilation

To compile the library, run:

```bash
make
```

This will create the `libftprintf.a` static library in the root directory.

### Available Make Rules

- `make` or `make all` - Compiles the library
- `make clean` - Removes object files
- `make fclean` - Removes object files and the library
- `make re` - Recompiles the entire library from scratch
- `make bonus` - Compiles with bonus features (flags: `-`, `0`, `.`, `#`, `+`, ` `)

### Usage

Include the header in your C file:

```c
#include "ft_printf.h"
```

Compile your program with the library:

```bash
cc your_program.c -L. -lftprintf -o your_program
```

### Example

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s!\n", "world");
    ft_printf("Number: %d\n", 42);
    ft_printf("Hex: %x\n", 255);
    ft_printf("Pointer: %p\n", &main);
    return (0);
}
```

## Supported Conversion Specifiers

- `%c` - Single character
- `%s` - String
- `%p` - Pointer address (in hexadecimal)
- `%d` - Signed decimal integer
- `%i` - Signed integer (same as %d)
- `%u` - Unsigned decimal integer
- `%x` - Hexadecimal (lowercase)
- `%X` - Hexadecimal (uppercase)
- `%%` - Literal percent sign

## Bonus Features

The bonus implementation includes support for the following flags:

- `-` - Left-align the output within the field width
- `0` - Pad with zeros instead of spaces
- `.` - Precision specifier
- `#` - Alternative form (adds `0x` prefix for hex)
- `+` - Always show sign for numbers
- ` ` (space) - Add space before positive numbers
- Field width - Minimum number of characters to output

### Example with Flags

```c
ft_printf("%10d\n", 42);        // Right-aligned in 10 chars
ft_printf("%-10d\n", 42);       // Left-aligned in 10 chars
ft_printf("%010d\n", 42);       // Zero-padded
ft_printf("%+d\n", 42);         // Shows + sign
ft_printf("%#x\n", 255);        // Prints 0xff
ft_printf("%.5d\n", 42);        // Precision of 5
```

## Algorithm and Data Structure

### Architecture Overview

The implementation follows a modular, extensible design that separates concerns into distinct functional units:

1. **Main Entry Point** (`ft_printf.c`): Orchestrates the parsing and output process
2. **Format Specifier Parser** (`ft_get_form_spec.c`): Extracts formatting information
3. **Type-specific Handlers**: Separate functions for each conversion type
4. **Utility Functions**: Helper functions for common operations

### Core Data Structure

```c
typedef struct s_format_specifier
{
    int              field_width;  // Minimum field width
    int              precision;    // Precision for numbers/strings
    unsigned int     flag;         // Bitfield for flags
    int              conv_spec;    // Conversion specifier character
}   t_form_spec;
```

This structure encapsulates all formatting information for a single conversion specifier. Using a bitfield for flags allows efficient storage and checking of multiple boolean states.

### Flag Management

Flags are stored as bits in an unsigned integer, enabling:
- Efficient storage (multiple flags in one variable)
- Fast checking using bitwise operations (`&`, `|`)
- Easy combination and removal of flags

Example flags:
```c
#define FLAG_MINUS   1   // (1 << 0)
#define FLAG_ZERO    2   // (1 << 1)
#define FLAG_HASH    4   // (1 << 2)
#define FLAG_PLUS    8   // (1 << 3)
```

### Algorithm Flow

1. **String Iteration**: Loop through format string character by character
2. **Format Detection**: Check for `%` to identify format specifiers
3. **Parsing Phase**:
   - Extract flags (`-`, `0`, `#`, `+`, ` `)
   - Parse field width (numeric value)
   - Parse precision (after `.`)
   - Identify conversion specifier (`c`, `s`, `d`, `i`, `u`, `x`, `X`, `p`)
4. **Validation**: Mask flags based on allowed combinations for each conversion type
5. **Formatting Phase**:
   - Calculate required padding (spaces/zeros)
   - Determine sign placement
   - Handle left/right alignment
   - Output in correct order: padding → sign → zeros → value → padding
6. **Output**: Write formatted result using `write()` system call

### Number Conversion Strategy

For base conversion (decimal, hexadecimal), a recursive approach is used:

1. **Base Case**: Single digit - output directly
2. **Recursive Case**: Divide number by base, recurse, then output remainder
3. **Benefits**: Clean, minimal code; natural digit ordering

```c
static int recurse(unsigned long n, const char *base, unsigned long base_len, int i)
{
    if (n >= base_len)
        written = recurse(n / base_len, base, base_len, i);
    written = ft_putchar(base[n % base_len]);
    return (i + written);
}
```

### Design Justification

**Why this architecture?**

- **Modularity**: Each conversion type has its own function, making the code maintainable and testable
- **Extensibility**: Adding new conversion specifiers requires minimal changes
- **Separation of Concerns**: Parsing, validation, and output are separate phases
- **Efficiency**: Bitfields for flags minimize memory usage and enable fast operations
- **Safety**: Comprehensive error checking at each stage prevents undefined behavior

**Trade-offs considered:**

- **No buffering**: Simpler implementation, but multiple `write()` calls are less efficient than buffering (as specified in the project requirements)
- **Recursive number conversion**: Clean code at the cost of stack usage (acceptable for reasonable number sizes)
- **Individual handlers**: More code but better organization and maintainability

## Resources

### Documentation and References

- [printf man page](https://man7.org/linux/man-pages/man3/printf.3.html) - Official documentation for the standard printf function
- [Variadic Functions in C](https://en.cppreference.com/w/c/variadic) - Guide to va_start, va_arg, va_end
- [C Formatted Output](https://www.cplusplus.com/reference/cstdio/printf/) - Detailed format specifier reference
- [Bitwise Operations in C](https://www.programiz.com/c-programming/bitwise-operators) - Understanding flag management
- [42 Norm](https://github.com/42School/norminette) - Coding standard requirements

### AI Usage

AI tools were used in the following limited capacity during this project:

- **Debugging assistance**: When encountering segmentation faults or unexpected behavior, AI was consulted to understand potential causes after exhausting manual debugging
- **Documentation review**: Clarifying ambiguous aspects of the printf specification and edge cases
- **Code review**: Checking for potential memory leaks and norm violations

**What AI was NOT used for:**
- Writing the core logic or algorithms
- Implementing the parsing or formatting functions
- Generating the overall architecture or design decisions

The majority of the implementation was developed through:
- Manual reading of documentation
- Iterative testing and debugging
- Peer discussions and code reviews
- Trial and error with different approaches

This approach ensured deep understanding of variadic functions, format parsing, and the intricacies of printf behavior.