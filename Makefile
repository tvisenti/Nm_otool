# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/18 14:42:35 by tvisenti          #+#    #+#              #
#    Updated: 2017/10/25 16:05:03 by tvisenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

SRC_DIR	= ./src

SRC =	ft_nm.c \
		sort.c \
		display.c \
		arch_64.c \
		arch_32.c \
		arch_lib.c \
		arch_fat.c \
		utils.c

VPATH	= $(SRC_DIR)

O_DIR	= ./obj
OBJ		= $(addprefix $(O_DIR)/,$(SRC:.c=.o))
SRC_PATH= $(addprefix $(SRC_DIR)/, $(SRC))

CC = gcc

CFLAGS = -Wall -Werror -Wextra

HEADERS = -I includes/

I_LIBFT = -I libft/inc/

I_PRINTF = libft/ft_printf/libftprintf.a

LIBFT = $(I_LIBFT) -Llibft -lft

all : $(NAME)

$(NAME): obj $(OBJ) res
	@make -C libft
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(HEADERS) $(LIBFT) $(I_PRINTF)
	@echo "\033[1;34mNm_otool\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

obj/%.o: %.c
	@$(CC) $(WFLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

obj:
	@mkdir -p obj/

res:
	@mkdir -p res/
	@cat /usr/include/mach-o/loader.h > res/loader.h
	@cat /usr/include/mach-o/nlist.h > res/nlist.h
	@cat /usr/include/ar.h > res/ar.h

clean:
	@rm -rf $(OBJ) $(NAME)
	@echo "\033[1;34mNm_otool\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"

fclean: clean
	@make fclean -C libft
	@echo "\033[1;34mNm_otool\t\033[1;33mCleaning lib\t\033[0;32m-OK-\033[0m"
	@rm -rf $(O_DIR) res/

re: fclean all

norme:
	@make norme -C libft
	@echo "\033[1;34mNm_otool\t\033[1;33mNorminette\t\033[0;32m-OK-\033[0m"
	@norminette $(SRC_PATH)

.PHONY: re fclean clean all norme res
