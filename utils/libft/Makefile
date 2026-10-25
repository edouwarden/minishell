# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enormand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 23:55:15 by enormand          #+#    #+#              #
#    Updated: 2024/11/19 23:55:15 by enormand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIB			= ar -rc
RM			= /bin/rm -f

INCS		= libft.h
SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c ft_gc.c

OBJS		= $(SRCS:.c=.o)
# Add these right after the OBJS definition
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
    @printf "\r\033[K[$(GREEN)%*s$(NC)] $(BLUE)100%%$(NC) $(YELLOW)Libft Compilation complete! $(NC)\n" \
    "$(BAR_WIDTH)" "$(shell printf '%*s' $(BAR_WIDTH) | tr ' ' '$(FILL_CHAR)')"
endef

define show_archiving
    @printf "$(YELLOW)Archiving objects into $(NAME)...$(NC)\n"
endef

# Modify the %.o rule to use the progress bar
%.o: %.c $(INCS)
	$(print_progress)
	@$(CC) $(CFLAGS) -c $< -o $@ 2>&1 || { printf "\n$(RED)Libft Compilation failed!$(NC)\n"; exit 1; }

# Update the $(NAME) rule to show completion and archiving
$(NAME):	$(OBJS)
			$(show_completion)
			$(show_archiving)
			@$(LIB) $(NAME) $(OBJS)
			@printf "$(GREEN)Libft successfully created!$(NC)\n"


OBJS		= $(SRCS:.c=.o)

all: 		$(NAME)

clean:
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

rebonus:	fclean bonus

.PHONY:		all clean fclean re bonus rebonus
