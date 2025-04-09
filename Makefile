NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3

DEBUG_FLAG	=

RM			=	rm -rf

SRCS		=	src/main.c \
				src/input_handling.c \
				src/errors/error_handler.c \
				src/errors/commands_errors.c \
				src/errors/major_errors.c \
				src/errors/parsing_errors.c \
				src/parsing/command_split.c \
				src/parsing/path_utils.c \
				src/commands/builtin_execution.c \
				src/parsing/pipeline_execution.c \
				src/env/create.c \
				src/env/env_manipulation.c \
				src/parsing/dollex.c \
				src/parsing/searching_things.c \
				src/commands/echo.c \
				src/commands/env.c \
				src/commands/convert_env_to_array.c \
				src/commands/export.c \
				utils/ft_lstlast.c \
				src/commands/unset.c \
				utils/utils.c \
				src/commands/cd.c \
				src/commands/pwd.c \
				src/parsing/redirection.c \
				src/commands/exit.c \
				utils/ft_debug.c \
				src/parsing/args_split.c \
				src/parsing/redirections/heredoc.c \
				src/parsing/redirections/input.c \
				src/parsing/redirections/output.c \
				src/parsing/commands_utils.c

OBJS		=	$(SRCS:.c=.o)

# Libft
LIBFT_DIR	=	utils/libft/
LIBFT		=	$(LIBFT_DIR)libft.a

LIBS		=	-lreadline -L$(LIBFT_DIR) -lft

# Progress bar settings
TOTAL_FILES := $(words $(SRCS))
BAR_WIDTH := 50
MAX_FILENAME := $(shell printf '%s\n' $(notdir $(SRCS)) | awk '{ print length }' | sort -nr | head -1)

# Colors
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
NC := \033[0m

# Progress bar characters
FILL_CHAR := \#
EMPTY_CHAR := -

# Function to count already compiled files
COUNT_COMPILED = $(shell ls $(OBJS) 2>/dev/null | wc -l | tr -d ' ')

define print_progress
	$(eval COMPILED=$(shell echo $$(($(COUNT_COMPILED)+1))))
	$(eval PERCENTAGE=$(shell echo $$(($(COMPILED)*100/$(TOTAL_FILES)))))
	$(eval FILLED=$(shell echo $$(($(PERCENTAGE)*$(BAR_WIDTH)/100))))
	$(eval EMPTY=$(shell echo $$(($(BAR_WIDTH)-$(FILLED)))))
	@printf "\r\033[K[$(GREEN)%*s$(NC)$(RED)%*s$(NC)] $(BLUE)%3d%%$(NC) $(YELLOW)Compiling %-$(MAX_FILENAME)s$(NC)" \
	"$(FILLED)" "$(shell printf '%*s' $(FILLED) | tr ' ' '$(FILL_CHAR)')" \
	"$(EMPTY)" "$(shell printf '%*s' $(EMPTY) | tr ' ' '$(EMPTY_CHAR)')" \
	"$(PERCENTAGE)" "$(notdir $<)"
endef

define show_completion
	@printf "\r\033[K[$(GREEN)%*s$(NC)] 🎉🎉 $(BLUE)100%%$(NC) $(YELLOW)Compilation complete! 🎉🎉$(NC)\n" \
	"$(BAR_WIDTH)" "$(shell printf '%*s' $(BAR_WIDTH) | tr ' ' '$(FILL_CHAR)')"
endef

%.o: %.c include/minishell.h Makefile
	$(print_progress)
	@${CC} ${FLAGS} ${DEBUG_FLAG} -I$(LIBFT_DIR) -c $< -o $@  2>&1 || { printf "\n$(RED)Compilation failed!$(NC)\n"; exit 1; }

$(NAME):		$(LIBFT) $(OBJS)
				$(show_completion)
				@$(CC) $(OBJS) $(LIBS) -o $(NAME)
				@printf "$(GREEN)Minishell successfully created!$(NC)\n"

$(LIBFT):
				@make -C $(LIBFT_DIR) -s

all:			$(NAME)

debug:			DEBUG_FLAG = -D DEBUG=1
debug:			fclean all
				@printf "$(YELLOW)Debug mode enabled (DEBUG=1)$(NC)\n"


clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT_DIR) -s
				@printf "$(RED)Object files deleted!$(NC)\n"

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT_DIR) -s
				@printf "$(RED)All build files deleted!$(NC)\n"

re:				fclean all

.PHONY:
