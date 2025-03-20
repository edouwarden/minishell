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
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c

OBJS		= $(SRCS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS) $(INCS)
			@$(LIB)	$(NAME) $(OBJS)

.c.o: 		
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:		
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

rebonus:	fclean bonus

.PHONY:		all clean fclean re bonus rebonus