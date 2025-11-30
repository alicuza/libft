#!/bin/env bash

cc test.c -o test
./test > og_test_cases
cc run_test.c -o run_test 2> printf_cc_error.log
./run_test > printf_behaviour.log
cc test_main.c -o test_main
./test_main > ft_test_cases
cc run_test_main.c ft_printf.c ft_printf_utils.c -L./libft -lft -o run_test_main
./run_test_main > ft_printf_behaviour.log
diff printf_behaviour.log ft_printf_behaviour.log
