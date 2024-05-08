# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: filippo <filippo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 00:27:44 by filippo           #+#    #+#              #
#    Updated: 2024/05/08 03:15:01 by filippo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OBJ = $(SRC:.c=.o)

LIBFT =	libft_extended/libft.a

all: $(LIBFT) server client

server: server.o
	$(CC) $(CFLAGS) -o server server.o $(LIBFT)

client: client.o
	$(CC) $(CFLAGS) -o client client.o $(LIBFT)

$(LIBFT):
	$(MAKE) -C libft_extended

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C libft_extended
	rm -f $(OBJ) server.o client.o

fclean: clean
	$(MAKE) fclean -C libft_extended
	rm -f server client

re: fclean all