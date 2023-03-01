# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llord <llord@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 08:45:10 by vjean             #+#    #+#              #
#    Updated: 2023/02/13 12:37:32 by llord            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
	ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memset.c ft_strdup.c ft_strlen.c\
	ft_memmove.c ft_strncmp.c ft_tolower.c ft_toupper.c ft_strlcat.c\
	ft_strlcpy.c ft_strchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_calloc.c\
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strrchr.c ft_itoa.c\
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
	ft_putnbr_fd.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c\
	ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c\
	ft_lstsize.c get_next_line.c get_next_line_utils.c ft_atol.c ft_free_tab.c\
	ft_strjoin_free.c ft_strtrim_free.c ft_count_char.c ft_free_null.c\
	ft_strcmp.c ft_isspace.c\

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

AR = ar rcs

RM = rm -f

OBJS = $(SRCS:%c=%o)

BONUS_OBJS = $(BONUS:.c=.o)

.c.o:
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		@ar rcs $(NAME) $(OBJS)

clean:
		@$(RM) $(OBJS)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

bonus: $(OBJS) $(BONUS_OBJS)
		@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus