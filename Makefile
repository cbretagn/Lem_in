# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 12:01:52 by sadahan           #+#    #+#              #
#    Updated: 2019/11/13 15:01:11 by sadahan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = lem_in

HEADS = lem_in.h

CC = gcc

CFLAGS += -Wall -Werror -Wextra

SRCS =	check_file.c check_format.c dynamic_string.c

LIBFT = ./libft/libft.a

OBJS += $(SRCS:%.c=%.o)

.PHONY: all, clean, fclean, re

all: $(LIBFT) $(NAME)

$(LIBFT): 
			make -C libft all

%.o: %.c Makefile $(HEADS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I $(HEADS) -o $(NAME)

clean:	
		rm -f $(OBJS)
		make -C libft clean

fclean:	clean
		rm -f $(NAME)
		make -C libft fclean

re:		fclean all