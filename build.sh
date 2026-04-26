#!/bin/bash

day='01'

bear -o compile_commands.json -- clang -std=c99 -lc -g ${day}/solution.c -o prog
