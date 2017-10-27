# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/18 14:42:35 by tvisenti          #+#    #+#              #
#    Updated: 2017/10/26 16:22:29 by tvisenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_NM = 			ft_nm
NAME_OTOOL = 		ft_otool

SRC_DIR_NM =		./src/nm
SRC_DIR_OTOOL =	 	./src/otool

HEADERS =			-I./inc

OBJ_DIR_NM = 		./obj_nm
OBJ_DIR_OTOOL = 	./obj_otool

SRC_NM = 			ft_nm.c \
					sort.c \
					display.c \
					arch_64.c \
					arch_32.c \
					arch_lib.c \
					arch_fat.c \
					utils.c

SRC_OTOOL = 		ft_otool.c \
					sort.c \
					display.c \
					arch_64.c \
					arch_32.c \
					arch_lib.c \
					arch_fat.c \
					utils.c

OBJ_NM = 			$(addprefix $(OBJ_DIR_NM)/,$(SRC_NM:.c=.o))
OBJ_OTOOL = 		$(addprefix $(OBJ_DIR_OTOOL)/,$(SRC_OTOOL:.c=.o))

SRC_PATH_NM = 		$(addprefix $(SRC_DIR_NM)/, $(SRC_NM))
SRC_PATH_OTOOL =	$(addprefix $(SRC_DIR_OTOOL)/, $(SRC_OTOOL))

CC = 		gcc

FLAGS = 	-Wall -Werror -Wextra

I_LIBFT = 	-I libft/inc/

I_PRINTF = 	libft/ft_printf/libftprintf.a

LIBFT = 	$(I_LIBFT) -Llibft -lft

all: $(NAME_NM) $(NAME_OTOOL) res

$(NAME_NM): $(OBJ_NM)
	@make -C libft
	@$(CC) $(FLAGS) -o $@ $(OBJ_NM) $(HEADERS) $(LIBFT) $(I_PRINTF)
	@echo "\033[1;34mNm\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

$(NAME_OTOOL): $(OBJ_OTOOL)
	@make -C libft
	@$(CC) $(FLAGS) -o $@ $(OBJ_OTOOL) $(HEADERS) $(LIBFT) $(I_PRINTF)
	@echo "\033[1;34mOtool\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

$(OBJ_DIR_NM)/%.o: $(SRC_DIR_NM)/%.c
	@mkdir $(OBJ_DIR_NM) 2> /dev/null || true
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

$(OBJ_DIR_OTOOL)/%.o: $(SRC_DIR_OTOOL)/%.c
	@mkdir $(OBJ_DIR_OTOOL) 2> /dev/null || true
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

res:
	@mkdir -p res/
	@cat /usr/include/mach-o/loader.h > res/loader.h
	@cat /usr/include/mach-o/nlist.h > res/nlist.h
	@cat /usr/include/ar.h > res/ar.h

clean:
	@rm -rf $(OBJ_NM) $(OBJ_OTOOL) $(NAME_NM) $(NAME_OTOOL)
	@echo "\033[1;34mNm_otool\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"

fclean: clean
	@make fclean -C libft
	@echo "\033[1;34mNm_otool\t\033[1;33mCleaning lib\t\033[0;32m-OK-\033[0m"
	@rm -rf $(OBJ_DIR_NM) $(OBJ_DIR_OTOOL) res/

re: fclean all

norme:
	@make norme -C libft
	@echo "\033[1;34mNm_otool\t\033[1;33mNorminette\t\033[0;32m-OK-\033[0m"
	@norminette $(SRC_PATH_NM) $(SRC_PATH_OTOOL)

.PHONY: re fclean clean all norme res
