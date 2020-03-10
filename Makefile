# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadahan <sadahan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/03 16:54:48 by cbretagn          #+#    #+#              #
#    Updated: 2020/03/10 19:11:10 by sadahan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in

SRC_PATH	= src

OBJ_PATH	= obj

SRC_NAME	= parsing.c\
			  check_file.c\
			  check_format.c\
			  dynamic_string.c\
			  hash_table.c\
			  create_del_struct.c\
			  connector_graph_struct.c\
			  get_connector_graph.c\
			  utility_path_algo.c\
			  get_nb_ants.c\
			  main_for_test.c\
			  shortest_path.c\
			  util_ek_algo.c\
			  manage_pile.c\
			  edmonds_karp.c\
			  collisions.c\
			  edmonds_karp2.c\
			  get_real_route.c\
			  print_ants.c\
			  utility_print_ants.c\
			  handling_direct_routes.c\
			  debugger.c\
			  shortest_path_util.c\
			  handle_tubes.c\
			  find_routes.c\
			  utility_create_struct.c\
			  utility_path_ek.c

OBJ_NAME	:= $(SRC_NAME:.c=.o)

SRC			= $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ			= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIB_PATH	= libft/libft.a

CC			= clang

CFLAGS		= -Wall -Wextra -g -fsanitize=address,undefined

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
