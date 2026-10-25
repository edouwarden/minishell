#!/bin/sh
# Run the minishell test binary under valgrind from the repository root.

cd "$(dirname "$0")/../.." || exit 1

valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--suppressions=tests/valgrind/readline.supp \
	./minishell
