#!/bin/bash

echo "Compiling with different BUFFER_SIZE values..."

gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o test1
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o test42
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=4096 get_next_line.c get_next_line_utils.c main.c -o test4096

echo ""
echo "=== Testing BUFFER_SIZE = 1 ==="
time timeout 5s ./test1 || echo "TIMEOUT or ERROR"

echo ""
echo "=== Testing BUFFER_SIZE = 42 ==="
time ./test42

echo ""
echo "=== Testing BUFFER_SIZE = 4096 ==="
time ./test4096

rm test1 test42 test4096
