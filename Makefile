CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g

.PHONY: help

help:
	@echo "C Learning Workspace"
	@echo "Use gcc to compile individual exercises."
	@echo "Example:"
	@echo '  $(CC) $(CFLAGS) path/to/main.c -o program'
