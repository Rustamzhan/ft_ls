# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astanton <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 12:36:48 by astanton          #+#    #+#              #
#    Updated: 2019/04/11 17:24:03 by astanton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = src/ft_ls.c src/free.c src/get_attributes.c src/print.c src/sort.c\
	   src/save_and_check_options.c src/save_dir_attr.c src/sort_massive.c\
	   src/save_file_attributes.c src/sort_dir.c src/max.c src/trash.c\
	   src/sort_by_size.c

OBJ =  src/ft_ls.o src/free.o src/get_attributes.o src/print.o src/sort.o\
	   src/save_and_check_options.o src/save_dir_attr.o src/sort_massive.o\
	   src/save_file_attributes.o src/sort_dir.o src/max.o src/trash.o\
	   src/sort_by_size.o

HDR = ./libft/includes/

FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	gcc -o ft_ls $(OBJ) -L ./libft -lft

$(OBJ): %.o: %.c
	
	gcc $(FLAG) -c -I $(HDR) $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
