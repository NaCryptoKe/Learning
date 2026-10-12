#!/usr/bin/env bash
set -euo pipefail

ROOT="$HOME/C"

dirs=(
  "books/c-programming-a-modern-approach/notes"
  "books/c-programming-a-modern-approach/exercises"
  "books/the-c-programming-language/notes"
  "books/the-c-programming-language/exercises"
  "books/modern-c/notes"
  "books/modern-c/exercises"
  "fundamentals/types-and-expressions"
  "fundamentals/arrays-and-pointers"
  "fundamentals/functions"
  "fundamentals/structs-and-unions"
  "fundamentals/dynamic-memory"
  "experiments/undefined-behavior"
  "experiments/integer-conversions"
  "experiments/pointer-arithmetic"
  "experiments/compilation"
  "projects/vector"
  "projects/string-library"
  "projects/allocator"
  "references"
)

for dir in "${dirs[@]}"; do
  mkdir -p "$ROOT/$dir"
done

# Main README
cat >"$ROOT/README.md" <<'EOF'
# C Learning

A structured workspace for learning and mastering C.

## Structure
- books/       Book notes and exercise solutions
- fundamentals/ Small programs organized by concept
- experiments/ Experiments that test language behavior
- projects/    Larger C implementations
- references/  Reusable technical notes

## Workflow
1. Read and understand a concept.
2. Solve the relevant exercises.
3. Test the concept with a small experiment.
4. Apply it in a project.
5. Record unresolved questions.
EOF

# Book READMEs
cat >"$ROOT/books/c-programming-a-modern-approach/README.md" <<'EOF'
# C Programming: A Modern Approach

Author: K. N. King

Primary textbook. Work through the chapters and solve the exercises.

## Progress
- [ ] Record current chapter
- [ ] Complete exercises
- [ ] Review difficult concepts
EOF

cat >"$ROOT/books/the-c-programming-language/README.md" <<'EOF'
# The C Programming Language

Authors: Brian W. Kernighan and Dennis M. Ritchie

Use as a supplementary text to reinforce concepts.

## Progress
- [ ] Record current chapter
- [ ] Complete exercises
- [ ] Review difficult concepts
EOF

cat >"$ROOT/books/modern-c/README.md" <<'EOF'
# Modern C

Author: Jens Gustedt

Use to deepen understanding of modern C standards and language rules.

## Progress
- [ ] Record current chapter
- [ ] Complete exercises
- [ ] Review difficult concepts
EOF

# Experiment and project README templates
for dir in \
  fundamentals/types-and-expressions \
  fundamentals/arrays-and-pointers \
  fundamentals/functions \
  fundamentals/structs-and-unions \
  fundamentals/dynamic-memory \
  experiments/undefined-behavior \
  experiments/integer-conversions \
  experiments/pointer-arithmetic \
  experiments/compilation \
  projects/vector \
  projects/string-library \
  projects/allocator; do
  name="${dir##*/}"
  cat >"$ROOT/$dir/README.md" <<EOF
# $name

## Objective
Describe what you want to learn or build.

## Questions
- 

## Results
- 

## Next steps
- [ ] 
EOF
done

# Reference notes
cat >"$ROOT/references/c-standard-notes.md" <<'EOF'
# C Standard Notes

Record important rules from the C standard.

## Topic

## Rule

## Example

## References
EOF

cat >"$ROOT/references/compiler-commands.md" <<'EOF'
# Compiler Commands

## GCC
Compile:
gcc -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
    -g main.c -o main

Run:
./main

## Clang
clang -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
    -g main.c -o main
EOF

cat >"$ROOT/references/debugging.md" <<'EOF'
# Debugging Notes

## Bug
Describe the problem.

## Reproduction
Steps to reproduce it.

## Root cause
Explain why it happened.

## Fix
Explain the correction.

## Verification
Describe how you tested the fix.
EOF

# Basic Makefile
cat >"$ROOT/Makefile" <<'EOF'
CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g

.PHONY: help

help:
	@echo "C Learning Workspace"
	@echo "Use gcc to compile individual exercises."
	@echo "Example:"
	@echo '  $(CC) $(CFLAGS) path/to/main.c -o program'
EOF

printf '\nC learning workspace created at: %s\n\n' "$ROOT"
find "$ROOT" -print | sort
