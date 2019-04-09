# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astanton <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 12:36:48 by astanton          #+#    #+#              #
#    Updated: 2019/04/02 20:51:15 by astanton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = ./ft_ls.c ./free.c ./get_attributes.c ./print.c ./sort.c\
	   ./save_and_check_options.c ./save_dir_attr.c ./sort_massive.c\
	   ./save_file_attributes.c ./sort_dir.c ./max.c ./print1.c

OBJ =  ./ft_ls.o ./free.o ./get_attributes.o ./print.o ./sort.o\
	   ./save_and_check_options.o ./save_dir_attr.o ./sort_massive.o\
	   ./save_file_attributes.o ./sort_dir.o ./max.o ./print1.o

HDR = ./libft/includes/

FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft fclean && make -C libft
	gcc -c $(SRCS) -I $(HDR)
	gcc $(FLAG) -o ft_ls $(OBJ) -L ./libft -lft

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
