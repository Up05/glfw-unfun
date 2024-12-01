#!/bin/sh
clear
gcc main.c glfw/glad.c -Iglfw -lglfw -lOpenGL -g -O0 -o main && ./main
