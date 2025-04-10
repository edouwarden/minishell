NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3

DEBUG_FLAG	=

RM			=	rm -rf

SRCS		=	src/main.c \
				src/1_env/create.c \
				src/1_env/env_manipulation.c \
				src/2_input/input_handling.c \
				src/2_input/signal_handling.c \
				src/2_input/string_utils.c \
				src/3_parsing/3_1dollex/dollex.c \
				src/3_parsing/3_1dollex/searching_things.c \
				src/3_parsing/3_2split_command/command_split.c \
				src/3_parsing/3_2split_command/redirection.c \
				src/3_parsing/3_2split_command/redirection_tokens.c \
				src/3_parsing/3_2split_command/redirection_utils.c \
				src/3_parsing/3_3split_args/args_split.c \
				src/3_parsing/commands_utils.c \
				src/4_execution/4_1pipeline/pipeline_process.c \
				src/4_execution/4_1pipeline/pipeline_setup.c \
				src/4_execution/4_2command/builtin_execution.c \
				src/4_execution/4_2command/command_execution.c \
				src/4_execution/4_2command/command_redirections.c \
				src/4_execution/4_2command/convert_env_to_array.c \
				src/4_execution/4_2command/path_utils.c \
				src/4_execution/4_2command/redirections/heredoc.c \
				src/4_execution/4_2command/redirections/input.c \
				src/4_execution/4_2command/redirections/output.c \
				src/5_builtins/cd.c \
				src/5_builtins/echo.c \
				src/5_builtins/env.c \
				src/5_builtins/export.c \
				src/5_builtins/exit.c \
				src/5_builtins/pwd.c \
				src/5_builtins/unset.c \
				src/errors/error_handler.c \
				src/errors/commands_errors.c \
				src/errors/major_errors.c \
				src/errors/parsing_errors.c \
				utils/ft_debug.c \
				utils/ft_lstlast.c \
				utils/utils.c 

OBJ_DIR		=	obj
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

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
COUNT_COMPILED = $(shell find $(OBJ_DIR) -name "*.o" 2>/dev/null | wc -l | tr -d ' ')

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

$(OBJ_DIR)/%.o: %.c include/minishell.h Makefile
	@mkdir -p $(dir $@)
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
				@$(RM) $(OBJ_DIR)
				@make clean -C $(LIBFT_DIR) -s
				@printf "$(RED)Object files deleted!$(NC)\n"

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT_DIR) -s
				@printf "$(RED)All build files deleted!$(NC)\n"

re:				fclean all

.PHONY: all clean fclean re debug
