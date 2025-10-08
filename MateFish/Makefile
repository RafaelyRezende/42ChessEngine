# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/20 21:47:37 by gde-la-r          #+#    #+#              #
#    Updated: 2025/09/20 21:47:43 by gde-la-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= MateFish

CC = cc

MLX_DIR= ./libs/mlx

MLX= $(MLX_DIR)/libmlx.a

all: $(NAME)

$(MLX):
	if [ ! -d "$(MLX_DIR)" ]; then \
			git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
		@$(MAKE) -C $(MLX_DIR)

CFLAGS = -Wall -Werror -Wextra -Iincludes

LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm


SRCS_DIR = ./srcs/main.c \
	./srcs/check_moves.c \
	./srcs/interface/delta.c \
	./srcs/interface/free_displays.c \
	./srcs/interface/ft_pixelput.c \
	./srcs/interface/game_loop.c \
	./srcs/interface/get_time.c \
	./srcs/interface/init_window.c \
	./srcs/interface/interface.c \
	./srcs/interface/load_images.c \
	./srcs/interface/render_utils.c \
	./srcs/interface/drawboard.c \
	./srcs/interface/get_piece.c

OBJS_DIR = objs

INC_DIR = includes

$(NAME): $(SRCS_DIR) $(MLX)
	$(CC) $(CFLAGS) $(SRCS_DIR) -o $(NAME) $(LDFLAGS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(MLX_DIR)
clean:
	rm -rf $(OBJS_DIR)
re: fclean all
