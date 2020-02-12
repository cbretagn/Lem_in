# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/03 16:54:48 by cbretagn          #+#    #+#              #
#    Updated: 2020/02/12 15:36:30 by cbretagn         ###   ########.fr        #
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
			  connector_graph_struct.c\
			  get_connector_graph.c\
			  shortest_path.c\
			  utility_path_algo.c\
			  get_nb_ants.c\
			  edmond_karps1.c\
			  get_paths.c\
			  collisions.c\
			  main_for_test.c\
			#   print_path.c

OBJ_NAME	:= $(SRC_NAME:.c=.o)

SRC			= $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ			= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIB_PATH	= libft/libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -g -fsanitize=address

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
