#!/bin/bash

# 명령 실행이 화면에 디스플레이 하는 기능
set -x 

gcc -c main.c
gcc -c add.c
gcc main.o add.o -o aaa
