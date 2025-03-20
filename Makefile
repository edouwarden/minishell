NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3

RM			=	rm -rf

SRCS		=	src/main.c \
				src/input_handling.c \
				src/error_handler.c \
				src/parsing/command_split.c \
				src/parsing/path_utils.c \
				src/parsing/command_execution.c \
				src/parsing/pipeline_execution.c \
				src/create.c \
				src/dollex.c \
				src/commands/echo.c \
				src/commands/env.c \
				src/commands/export.c \
				src/commands/ft_lstlast.c \
				src/commands/unset.c \
				src/commands/utils.c


OBJS		=	$(SRCS:.c=.o)

# Libft
LIBFT_DIR	=	utils/libft/
LIBFT		=	$(LIBFT_DIR)libft.a

LIBS		=	-lreadline -L$(LIBFT_DIR) -lft

%.o: %.c include/minishell.h Makefile
				@${CC} ${FLAGS} -I$(LIBFT_DIR) -c $< -o $@

$(NAME):		$(LIBFT) $(OBJS)
				@$(CC) $(OBJS) $(LIBS) -o $(NAME)
				@echo -e "$(NAME) created!"

$(LIBFT):
				@make -C $(LIBFT_DIR)

all:			$(NAME)

clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT_DIR)
				@echo -e "object files deleted!"

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@echo -e "all deleted!"

re:				fclean all

.PHONY:			all clean fclean re


