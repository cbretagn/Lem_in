# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/03 16:54:48 by cbretagn          #+#    #+#              #
#    Updated: 2019/11/15 13:15:39 by sadahan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem_in

SRC_PATH	= src

OBJ_PATH	= obj

SRC_NAME	= parsing.c\
			  check_file.c\
			  check_format.c\
			  dynamic_string.c\
			  get_next_line.c\
			  hash_table.c\
			  create_del_struct.c\
			  main_for_test.c

OBJ_NAME	:= $(SRC_NAME:.c=.o)

SRC			= $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ			= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIB_PATH	= libft/libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g

.PHONY		: all clean fclean re

all			: $(NAME)

$(NAME)		: $(OBJ)
	make -C ./libft/
	$(CC) $(CFLAGS) -o $@ $^ $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
		mkdir $(OBJ_PATH) 2> /dev/null || true
		$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

analyze		:
	$(CC) -fsyntax-only $(CFLAGS) $(SRC)
	$(CC) --analyze $(CFLAGS) $(SRC)

clean		:
	rm -f $(OBJ)
	make clean -C ./libft/
	rmdir $(OBJ_PATH) 2> /dev/null || true

fclean		: clean
	rm -f $(NAME)
	make fclean -C ./libft/

re 			: fclean all
