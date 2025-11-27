#!/bin/env bash

cc test.c -o test
./test > test_cases
cc run_test.c -o run_test
./run_test > printf_behaviour.log
